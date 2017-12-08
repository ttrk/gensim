// Header file to access Pythia 8 program elements.
#include "Pythia8/Pythia.h"
#include "Pythia8/Event.h"
#include "Pythia8/Basics.h"

#include "TROOT.h"
#include "TTree.h"
#include "TFile.h"
#include "TSystem.h"
#include "TVirtualPad.h"
#include "TApplication.h"
#include "TRandom3.h"

// dictionary to read Pythia8::Event
#include "dictionary/dict4RootDct.cc"
#include "utils/pythiaUtil.h"
#include "../fastjet3/fastJetTree.h"
#include "../utilities/physicsUtil.h"
#include "../utilities/systemUtil.h"

#include "fastjet/ClusterSequence.hh"
#include "fastjet/PseudoJet.hh"

#include <iostream>
#include <string>
#include <vector>

// types of particles to be used in jet clustering
enum CONSTITUENTS {
    kFinal,         // final state particles (after hadronization)
    kFinalCh,       // charged final state particles
    kParton,        // final partons (before hadronization)
    kPartonHard,    // final partons originating from one of the hard scatterers
    kN_CONSTITUENTS
};

void pythiaClusterJets(std::string inputFileName = "pythiaEvents.root", std::string outputFileName = "pythiaClusterJets_out.root",
                       int dR = 3, int minJetPt = 5, int constituentType = 0, std::string jetptCSN = "0,0,0");

void pythiaClusterJets(std::string inputFileName, std::string outputFileName, int dR, int minJetPt, int constituentType, std::string jetptCSN)
{
    std::cout << "running pythiaClusterJets()" << std::endl;

    double jetRadius = (double)dR / 10;

    std::cout << "##### Parameters #####" << std::endl;
    std::cout << "inputFileName = " << inputFileName.c_str() << std::endl;
    std::cout << "outputFileName = " << outputFileName.c_str() << std::endl;
    std::cout << "jetRadius = " << jetRadius << std::endl;
    std::cout << "minJetPt = " << minJetPt << std::endl;
    std::cout << "constituentType = " << constituentType << std::endl;
    std::cout << "jetptCSN = " << jetptCSN.c_str() << std::endl;
    std::cout << "##### Parameters - END #####" << std::endl;

    // Set up the ROOT TFile and TTree.
    TFile* inputFile = TFile::Open(inputFileName.c_str(),"READ");
    Pythia8::Event* eventAll = 0;

    std::string evtTreePath = "evt";
    TTree* treeEvt = (TTree*)inputFile->Get(evtTreePath.c_str());
    treeEvt->SetBranchAddress("event", &eventAll);

    Pythia8::Event* eventParton = 0;
    std::string evtPartonTreePath = "evtParton";
    TTree* treeEvtParton = (TTree*)inputFile->Get(evtPartonTreePath.c_str());
    treeEvtParton->SetBranchAddress("event", &eventParton);

    Pythia8::Event* event = eventAll;
    if (constituentType == CONSTITUENTS::kParton || constituentType == CONSTITUENTS::kPartonHard) {
        event = eventParton;
    }

    std::cout << "initialize the Pythia class to obtain info that is not accessible through event TTree." << std::endl;
    std::cout << "##### Pythia initialize #####" << std::endl;
    Pythia8::Pythia pythia;
    std::cout << "##### Pythia initialize - END #####" << std::endl;

    TFile* outputFile = new TFile(outputFileName.c_str(), "UPDATE");

    fastjet::JetDefinition* fjJetDefn = 0;
    fjJetDefn = new fastjet::JetDefinition(fastjet::antikt_algorithm, jetRadius);

    std::string jetTreeName = Form("ak%djets", dR);
    std::string jetTreeTitle = Form("jets with R = %.1f", jetRadius);
    if (constituentType == CONSTITUENTS::kFinalCh) {
        jetTreeName = Form("ak%djetsCh", dR);
        jetTreeTitle = Form("charged particle jets with R = %.1f", jetRadius);
    }
    else if (constituentType == CONSTITUENTS::kParton) {
        jetTreeName = Form("ak%djetsParton", dR);
        jetTreeTitle = Form("partonic jets with R = %.1f", jetRadius);
    }
    else if (constituentType == CONSTITUENTS::kPartonHard) {
        jetTreeName = Form("ak%djetsPartonHard", dR);
        jetTreeTitle = Form("partonic jets from hard scattering with R = %.1f", jetRadius);
    }
    // comma separated list for CSN parameters
    std::vector<double> csn;
    std::vector<std::string> csnStr = split(jetptCSN, ",");
    bool smearJetPt = false;
    for (int i = 0; i < csnStr.size(); ++i) {
        double val = std::atof(csnStr.at(i).c_str());
        csn.push_back(val);
        smearJetPt |= (val > 0);
    }
    smearJetPt &= ((int)csn.size() == 3);
    // apply smearing if any of the C, S, N is > 0.
    if (smearJetPt)  {
        jetTreeName.append("Smeared");
        jetTreeTitle.append(Form(", smeared with C = %f, S = %f, N = %f", csn.at(0), csn.at(1), csn.at(2)));
    }

    std::cout << "jetTreeName = " << jetTreeName.c_str() << std::endl;
    std::cout << "jetTreeTitle = " << jetTreeTitle.c_str() << std::endl;

    TTree* jetTree = new TTree(jetTreeName.c_str(), jetTreeTitle.c_str());
    fastJetTree fjt;
    fjt.branchTree(jetTree);

    // Fastjet input
    std::vector<fastjet::PseudoJet> fjParticles;

    std::cout << "Clustering with " << fjJetDefn->description().c_str() << std::endl;

    TRandom3 rand(12345);
    int eventsAnalyzed = 0;
    int nEvents = treeEvt->GetEntries();
    std::cout << "nEvents = " << nEvents << std::endl;
    std::cout << "Loop STARTED" << std::endl;
    for (int iEvent = 0; iEvent < nEvents; ++iEvent) {

        fjt.clearEvent();
        treeEvt->GetEntry(iEvent);
        treeEvtParton->GetEntry(iEvent);

        eventsAnalyzed++;

        // Reset Fastjet input
        fjParticles.resize(0);

        int eventSize = event->size();
        for (int i = 0; i < eventSize; ++i) {

            if (constituentType == CONSTITUENTS::kFinal) {
                if (!(*event)[i].isFinal()) continue;
            }
            else if (constituentType == CONSTITUENTS::kFinalCh) {
                if (!((*event)[i].isFinal() && isCharged((*event)[i], pythia.particleData))) continue;
            }
            else if (constituentType == CONSTITUENTS::kPartonHard) {
                int iOrig = (*event)[i].mother1();
                if (!(isAncestor(eventAll, iOrig, 5) || isAncestor(eventAll, iOrig, 6))) continue;
            }

            // No neutrinos
            if (isNeutrino((*event)[i]))     continue;

            // Only |eta| < 5
            if (std::fabs((*event)[i].eta()) > 5) continue;

            // Store as input to Fastjet
            fastjet::PseudoJet fjParticle((*event)[i].px(),
                                          (*event)[i].py(),
                                          (*event)[i].pz(),
                                          (*event)[i].e());
            fjParticle.set_user_index(i);

            fjParticles.push_back(fjParticle);
        }

        // Run Fastjet algorithm
        fastjet::ClusterSequence clustSeq(fjParticles, *fjJetDefn);


        // Extract inclusive jets sorted by pT (note the minimum pT)
        std::vector<fastjet::PseudoJet> inclusiveJets = clustSeq.inclusive_jets(minJetPt);
        std::vector<fastjet::PseudoJet> sortedJets    = sorted_by_pt(inclusiveJets);

        int nSortedJets = sortedJets.size();
        for (int i = 0; i < nSortedJets; ++i) {

            double sf = smearJetPt ? getEnergySmearingFactor(rand, sortedJets[i].pt(), csn[0], csn[1], csn[2]) : 1;

            fjt.rawpt->push_back(sortedJets[i].pt());
            fjt.jetpt->push_back(sf * sortedJets[i].pt());
            fjt.jeteta->push_back(sortedJets[i].eta());
            fjt.jetphi->push_back(sortedJets[i].phi_std());
            fjt.nJet++;
        }

        jetTree->Fill();
    }
    std::cout << "Loop ENDED" << std::endl;
    std::cout << "eventsAnalyzed = " << eventsAnalyzed << std::endl;
    std::cout<<"Closing the input file"<<std::endl;
    inputFile->Close();

    outputFile->Write("", TObject::kOverwrite);
    std::cout<<"Closing the output file"<<std::endl;
    outputFile->Close();

    std::cout << "running pythiaClusterJets() - END" << std::endl;
}

int main(int argc, char* argv[]) {

    if (argc == 7) {
        pythiaClusterJets(argv[1], argv[2], std::atoi(argv[3]), std::atoi(argv[4]), std::atoi(argv[5]), argv[6]);
        return 0;
    }
    else if (argc == 6) {
        pythiaClusterJets(argv[1], argv[2], std::atoi(argv[3]), std::atoi(argv[4]), std::atoi(argv[5]));
        return 0;
    }
    else if (argc == 5) {
        pythiaClusterJets(argv[1], argv[2], std::atoi(argv[3]), std::atoi(argv[4]));
        return 0;
    }
    else if (argc == 4) {
        pythiaClusterJets(argv[1], argv[2], std::atoi(argv[3]));
        return 0;
    }
    else if (argc == 3) {
        pythiaClusterJets(argv[1], argv[2]);
        return 0;
    }
    else if (argc == 2) {
        pythiaClusterJets(argv[1]);
        return 0;
    }
    else {
        std::cout << "Usage : \n" <<
                "./pythiaClusterJets.exe <inputFileName> <outputFileName> <jetRadius> <minJetPt> <constituentType> <jetptCSN>"
                << std::endl;
        return 1;
    }
}
