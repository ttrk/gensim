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

// dictionary to read Pythia8::Event
#include "dictionary/dict4RootDct.cc"
#include "../fastjet3/fastJetTree.h"

#include "fastjet/ClusterSequence.hh"
#include "fastjet/PseudoJet.hh"

#include <iostream>
#include <string>
#include <vector>

using namespace Pythia8;

void pythiaClusterJets(std::string inputFileName = "pythiaEvents.root", std::string outputFileName = "pythiaClusterJets_out.root",
                       int dR = 3, int minJetPt = 5);

void pythiaClusterJets(std::string inputFileName, std::string outputFileName, int dR, int minJetPt)
{
    double jetRadius = (double)dR / 10;

    std::cout << "##### Parameters #####" << std::endl;
    std::cout << "inputFileName = " << inputFileName.c_str() << std::endl;
    std::cout << "outputFileName = " << outputFileName.c_str() << std::endl;
    std::cout << "jetRadius = " << jetRadius << std::endl;
    std::cout << "minJetPt = " << minJetPt << std::endl;
    std::cout << "##### Parameters - END #####" << std::endl;

    // Set up the ROOT TFile and TTree.
    TFile *inputFile = TFile::Open(inputFileName.c_str(),"READ");
    Pythia8::Event *event = 0;
    TTree *T = (TTree*)inputFile->Get("T");
    T->SetBranchAddress("event", &event);

    // Create file on which histogram(s) can be saved.
    TFile* outputFile = new TFile(outputFileName.c_str(), "RECREATE");

    fastjet::JetDefinition* fjJetDefn = 0;
    fjJetDefn = new fastjet::JetDefinition(fastjet::antikt_algorithm, jetRadius);

    TTree* jetTreeOut = new TTree("jetTree", Form("jets with radius = %.1f", jetRadius));
    fastJetTree fjt;
    fjt.branchTree(jetTreeOut);

    // Fastjet input
    std::vector<fastjet::PseudoJet> fjParticles;

    // print out some infos
    std::cout << "Clustering with " << fjJetDefn->description().c_str() << std::endl;

    int nEvents = T->GetEntries();
    std::cout << "nEvents = " << nEvents << std::endl;

    // Begin event loop.
    for (int iEvent = 0; iEvent < nEvents; ++iEvent) {

        fjt.clearEvent();
        std::cout << "iEvent = " << iEvent << std::endl;
        T->GetEntry(iEvent);

        // Reset Fastjet input
        fjParticles.resize(0);

        int eventSize = event->size();
        for (int i = 0; i < eventSize; ++i) {

            // Final state only
            if (!(*event)[i].isFinal())        continue;

            // No neutrinos
            if ((*event)[i].idAbs() == 12 || (*event)[i].idAbs() == 14 ||
                (*event)[i].idAbs() == 16)     continue;

            // Only |eta| < 3.6
            if (std::fabs((*event)[i].eta()) > 3.6) continue;

            // Store as input to Fastjet
            fastjet::PseudoJet fjParticle((*event)[i].px(),
                                          (*event)[i].py(),
                                          (*event)[i].pz(),
                                          (*event)[i].e());
            fjParticle.set_user_index(i);

            fjParticles.push_back(fjParticle);
        }

        // Run Fastjet algorithm
        std::vector<fastjet::PseudoJet> inclusiveJets, sortedJets;
        fastjet::ClusterSequence clustSeq(fjParticles, *fjJetDefn);

        // Extract inclusive jets sorted by pT (note minimum pT of 20.0 GeV)
        inclusiveJets = clustSeq.inclusive_jets(minJetPt);
        sortedJets    = sorted_by_pt(inclusiveJets);

        int nSortedJets = sortedJets.size();
        std::cout << "nSortedJets = " << nSortedJets << std::endl;

        for (int i = 0; i < nSortedJets; ++i) {

            std::cout << "iJet = " << i << std::endl;
            std::cout << "jet pt = " << sortedJets[i].pt() << std::endl;
            std::cout << "jet eta = " << sortedJets[i].eta() << std::endl;
            std::cout << "jet phi = " << sortedJets[i].phi_std() << std::endl;
            //std::cout << "jet area = " << sortedJets[i].area() << std::endl;

            fjt.jetpt->push_back(sortedJets[i].pt());
            fjt.jeteta->push_back(sortedJets[i].eta());
            fjt.jetphi->push_back(sortedJets[i].phi_std());
            fjt.nJet++;

        }

        jetTreeOut->Fill();
    }

    std::cout<<"Closing the input file"<<std::endl;
    inputFile->Close();

    outputFile->Write("", TObject::kOverwrite);
    std::cout<<"Closing the output file"<<std::endl;
    outputFile->Close();

    inputFile->Close();
}

int main(int argc, char* argv[]) {

    if (argc == 5) {
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
                "./pythiaClusterJets.exe <inputFileName> <outputFileName> <jetRadius> <minJetPt>"
                << std::endl;
        return 1;
    }
}
