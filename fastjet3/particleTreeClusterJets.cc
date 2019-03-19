#include "TROOT.h"
#include "TTree.h"
#include "TFile.h"
#include "TSystem.h"
#include "TVirtualPad.h"
#include "TApplication.h"
#include "TRandom3.h"
#include "TLorentzVector.h"

#include "fastJetTree.h"
#include "../utilities/physicsUtil.h"
#include "../utilities/systemUtil.h"
#include "../utilities/particleTree.h"

#include "fastjet/ClusterSequence.hh"
#include "fastjet/PseudoJet.hh"

#include <iostream>
#include <iomanip>
#include <string>
#include <vector>

// types of particles to be used in jet clustering
enum JETTYPES {
    kFinal,         // final state particles (after hadronization)
    kFinalCh,       // charged final state particles
    kFinal_WTA,         // final state particles (after hadronization)
    kN_JETTYPES
};

void particleTreeClusterJets(std::string inputFileName = "particleTree.root", std::string outputFileName = "particleTreeClusterJets_out.root",
                             std::string treePath = "evtHydjet", int dR = 3, int minJetPt = 5, int jetType = 0, std::string jetptCSN = "0,0,0", std::string jetphiCSN = "0,0,0");

void particleTreeClusterJets(std::string inputFileName, std::string outputFileName, std::string treePath,
                       int dR, int minJetPt, int jetType,
                       std::string jetptCSN, std::string jetphiCSN)
{
    std::cout << "running particleTreeClusterJets()" << std::endl;

    double jetRadius = (double)dR / 10;

    std::cout << "##### Parameters #####" << std::endl;
    std::cout << "inputFileName = " << inputFileName.c_str() << std::endl;
    std::cout << "outputFileName = " << outputFileName.c_str() << std::endl;
    std::cout << "treePath = " << treePath.c_str() << std::endl;
    std::cout << "jetRadius = " << jetRadius << std::endl;
    std::cout << "minJetPt = " << minJetPt << std::endl;
    std::cout << "jetType = " << jetType << std::endl;
    std::cout << "jetptCSN = " << jetptCSN.c_str() << std::endl;
    std::cout << "jetphiCSN = " << jetphiCSN.c_str() << std::endl;
    std::cout << "##### Parameters - END #####" << std::endl;

    // Set up the ROOT TFile and TTree.
    TFile* inputFile = TFile::Open(inputFileName.c_str(),"READ");

    bool useChParticles = (jetType == JETTYPES::kFinalCh);

    particleTree particles;

    TTree* treeParticles = 0;
    treeParticles = (TTree*)inputFile->Get(treePath.c_str());
    particles.setupTreeForReading(treeParticles);

    TFile* outputFile = new TFile(outputFileName.c_str(), "UPDATE");

    int recombScheme = fastjet::E_scheme;
    if (jetType == JETTYPES::kFinal_WTA) {
        recombScheme = fastjet::WTA_pt_scheme;
    }

    fastjet::JetDefinition* fjJetDefn = 0;
    fjJetDefn = new fastjet::JetDefinition(fastjet::antikt_algorithm, jetRadius);
    fjJetDefn->set_recombination_scheme((fastjet::RecombinationScheme)recombScheme);

    std::string jetTreeName = Form("ak%djets", dR);
    std::string jetTreeTitle = Form("jets with R = %.1f", jetRadius);
    if (jetType == JETTYPES::kFinalCh) {
        jetTreeName = Form("ak%djetsCh", dR);
        jetTreeTitle = Form("charged particle jets with R = %.1f", jetRadius);
    }
    else if (jetType == JETTYPES::kFinal_WTA) {
        jetTreeName = Form("ak%djetsWTA", dR);
        jetTreeTitle = Form("jets with R = %.1f, WTA", jetRadius);
    }
    // comma separated list for CSN parameters
    std::vector<double> csnPt;
    std::vector<std::string> csnStr;

    // energy smearing
    csnStr = split(jetptCSN, ",");
    bool smearJetPt = false;
    for (int i = 0; i < (int)csnStr.size(); ++i) {
        double val = std::atof(csnStr.at(i).c_str());
        csnPt.push_back(val);
        smearJetPt |= (val > 0);
    }
    smearJetPt &= ((int)csnPt.size() == 3);

    // angle smearing
    std::vector<double> csnPhi;
    csnStr = split(jetphiCSN, ",");
    bool smearJetPhi = false;
    for (int i = 0; i < (int)csnStr.size(); ++i) {
        double val = std::atof(csnStr.at(i).c_str());
        csnPhi.push_back(val);
        smearJetPhi |= (val > 0);
    }
    smearJetPhi &= ((int)csnPhi.size() == 3);

    // apply smearing if any of the C, S, N is > 0.
    if (smearJetPt || smearJetPhi)  {
        jetTreeName.append("Smeared");
        if (smearJetPt)  jetTreeTitle.append(Form(", pt smeared with C = %.2f, S = %.2f, N = %.2f", csnPt.at(0), csnPt.at(1), csnPt.at(2)));
        if (smearJetPhi)  jetTreeTitle.append(Form(", phi smeared with C = %.2f, S = %.2f, N = %.2f", csnPhi.at(0), csnPhi.at(1), csnPhi.at(2)));
    }

    std::cout << "jetTreeName = " << jetTreeName.c_str() << std::endl;
    std::cout << "jetTreeTitle = " << jetTreeTitle.c_str() << std::endl;

    TTree* jetTree = new TTree(jetTreeName.c_str(), jetTreeTitle.c_str());
    fastJetTree fjt;
    fjt.branchTree(jetTree);

    // Fastjet input
    std::vector<fastjet::PseudoJet> fjParticles;

    std::cout << "Clustering with " << fjJetDefn->description().c_str() << std::endl;

    TRandom3 rand1(12345);
    TRandom3 rand2(6789);
    int eventsAnalyzed = 0;
    int nEvents = treeParticles->GetEntries();
    std::cout << "nEvents = " << nEvents << std::endl;
    std::cout << "Loop STARTED" << std::endl;
    for (int iEvent = 0; iEvent < nEvents; ++iEvent) {

        if (iEvent % 10000 == 0)  {
          std::cout << "current entry = " <<iEvent<<" out of "<<nEvents<<" : "<<std::setprecision(2)<<(double)iEvent/nEvents*100<<" %"<<std::endl;
        }

        fjt.clearEvent();
        treeParticles->GetEntry(iEvent);

        eventsAnalyzed++;

        // Reset Fastjet input
        fjParticles.resize(0);

        for (int i = 0; i < particles.n; ++i) {

            if (useChParticles) {
                if ((*particles.chg)[i] == 0) continue;
            }

            // Only |eta| < 5
            if (std::fabs((*particles.eta)[i]) > 5) continue;

            TLorentzVector vec4;
            vec4.SetPtEtaPhiM((*particles.pt)[i], (*particles.eta)[i], (*particles.phi)[i], 0);

            // Store as input to Fastjet
            fastjet::PseudoJet fjParticle(vec4.Px(),
                    vec4.Py(),
                    vec4.Pz(),
                    vec4.E());

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

            double sf = smearJetPt ? getEnergySmearingFactor(rand1, sortedJets[i].pt(), csnPt[0], csnPt[1], csnPt[2]) : 1;
            double sPhi = smearJetPhi ? getAngleSmearing(rand2, sortedJets[i].pt(), csnPhi[0], csnPhi[1], csnPhi[2]) : 0;

            fjt.rawpt->push_back(sortedJets[i].pt());
            fjt.jetpt->push_back(sf * sortedJets[i].pt());
            fjt.jeteta->push_back(sortedJets[i].eta());
            fjt.rawphi->push_back(sortedJets[i].phi_std());
            fjt.jetphi->push_back(correctPhiRange(sortedJets[i].phi_std() + sPhi));
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

    std::cout << "running particleTreeClusterJets() - END" << std::endl;
}

int main(int argc, char* argv[]) {

    if (argc == 9) {
        particleTreeClusterJets(argv[1], argv[2], argv[3], std::atoi(argv[4]), std::atoi(argv[5]), std::atoi(argv[6]), argv[7], argv[8]);
        return 0;
    }
    else if (argc == 8) {
        particleTreeClusterJets(argv[1], argv[2], argv[3], std::atoi(argv[4]), std::atoi(argv[5]), std::atoi(argv[6]), argv[7]);
        return 0;
    }
    else if (argc == 7) {
        particleTreeClusterJets(argv[1], argv[2], argv[3], std::atoi(argv[4]), std::atoi(argv[5]), std::atoi(argv[6]));
        return 0;
    }
    else if (argc == 6) {
        particleTreeClusterJets(argv[1], argv[2], argv[3], std::atoi(argv[4]), std::atoi(argv[5]));
        return 0;
    }
    else if (argc == 5) {
        particleTreeClusterJets(argv[1], argv[2], argv[3], std::atoi(argv[4]));
        return 0;
    }
    else if (argc == 4) {
        particleTreeClusterJets(argv[1], argv[2], argv[3]);
        return 0;
    }
    else if (argc == 3) {
        particleTreeClusterJets(argv[1], argv[2]);
        return 0;
    }
    else if (argc == 2) {
        particleTreeClusterJets(argv[1]);
        return 0;
    }
    else {
        std::cout << "Usage : \n" <<
                "./particleTreeClusterJets.exe <inputFileName> <outputFileName> <treePath> <jetRadius> <minJetPt> <jetType> <jetptCSN> <jetphiCSN>"
                << std::endl;
        return 1;
    }
}
