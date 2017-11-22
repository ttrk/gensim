/*
 * code to analyze the two particles outgoing from hard process where one of the particles is assumed to be photon.
 */
// Header file to access Pythia 8 program elements.
#include "Pythia8/Pythia.h"
#include "Pythia8/Event.h"
#include "Pythia8/Basics.h"

#include "TROOT.h"
#include "TTree.h"
#include "TFile.h"
#include "TSystem.h"
#include "TH1.h"
#include "TH1D.h"
#include "TH2D.h"
#include "TVirtualPad.h"
#include "TApplication.h"

// dictionary to read Pythia8::Event
#include "../dictionary/dict4RootDct.cc"
#include "../utils/pythiaUtil.h"

#include <iostream>
#include <string>
#include <vector>

int main(int argc, char* argv[]) {

    std::string inputFileName = "promptPhoton.root";
    if (argc > 0) {
        inputFileName = argv[1];
    }

    std::string outputFileName = "photonPartonAna_out.root";
    if (argc > 1) {
        outputFileName = argv[2];
    }

    std::cout << "##### Parameters #####" << std::endl;
    std::cout << "inputFileName = " << inputFileName.c_str() << std::endl;
    std::cout << "outputFileName = " << outputFileName.c_str() << std::endl;
    std::cout << "##### Parameters - END #####" << std::endl;

    TFile *inputFile = TFile::Open(inputFileName.c_str(),"READ");
    Pythia8::Event *event = 0;
    TTree *T = (TTree*)inputFile->Get("T");
    T->SetBranchAddress("event", &event);

    TFile* outputFile = new TFile(outputFileName.c_str(), "RECREATE");

    TH1::SetDefaultSumw2();

    // photon histograms
    int nBinsX_pt = 30;
    double axis_pt_min = 60;
    double axis_pt_max = 150+axis_pt_min;
    int nBinsX_eta = 20;
    double axis_eta_min = 0;
    double axis_eta_max = 5;
    TH1D* h_pt_pho = new TH1D("h_pt_pho",";p_{T}^{#gamma};", nBinsX_pt, axis_pt_min, axis_pt_max);
    TH1D* h_eta_pho = new TH1D("h_eta_pho",";|#eta^{#gamma}|;", nBinsX_eta, axis_eta_min, axis_eta_max);
    TH1D* h_pt_pho_ratio_q = new TH1D("h_pt_pho_ratio_q",";p_{T}^{#gamma};", nBinsX_pt, axis_pt_min, axis_pt_max);
    TH1D* h_pt_pho_ratio_g = new TH1D("h_pt_pho_ratio_g",";p_{T}^{#gamma};", nBinsX_pt, axis_pt_min, axis_pt_max);

    // parton histograms
    TH1D* h_pt_parton = new TH1D("h_pt_parton",";p_{T}^{q/g};", nBinsX_pt, axis_pt_min, axis_pt_max);
    TH1D* h_eta_parton = new TH1D("h_eta_parton",";|#eta^{q/g}|;", nBinsX_eta, axis_eta_min, axis_eta_max);
    TH1D* h_pt_q = new TH1D("h_pt_q",";p_{T}^{q};", nBinsX_pt, axis_pt_min, axis_pt_max);
    TH1D* h_eta_q = new TH1D("h_eta_q",";|#eta^{q}|;", nBinsX_eta, axis_eta_min, axis_eta_max);
    TH1D* h_pt_g = new TH1D("h_pt_g",";p_{T}^{g};", nBinsX_pt, axis_pt_min, axis_pt_max);
    TH1D* h_eta_g = new TH1D("h_eta_g",";|#eta^{g}|;", nBinsX_eta, axis_eta_min, axis_eta_max);

    // photon-parton histograms
    TH1D* h_deta_pho_parton = new TH1D("h_deta_pho_parton",";#Delta#eta_{#gamma q/g} = |#eta^{#gamma} - #eta^{q/g}|;", nBinsX_eta, 0, 1.5*axis_eta_max);
    TH1D* h_deta_pho_q = new TH1D("h_deta_pho_q",";#Delta#eta_{#gamma q} = |#eta^{#gamma} - #eta^{q}|;", nBinsX_eta, 0, 1.5*axis_eta_max);
    TH1D* h_deta_pho_g = new TH1D("h_deta_pho_g",";#Delta#eta_{#gamma g} = |#eta^{#gamma} - #eta^{g}|;", nBinsX_eta, 0, 1.5*axis_eta_max);

    // event info
    TH2D* h2_qscale_pt_pho = new TH2D("h2_qscale_pt_pho", ";p_{T}^{#gamma};Q", nBinsX_pt, axis_pt_min, axis_pt_max, nBinsX_pt, axis_pt_min, axis_pt_max);
    TH2D* h2_qscale_eta_pho = new TH2D("h2_qscale_eta_pho", ";|#eta^{#gamma}|;Q", nBinsX_eta, axis_eta_min, axis_eta_max, nBinsX_pt, axis_pt_min, axis_pt_max);
    TH2D* h2_qscale_deta_pho_parton = new TH2D("h2_qscale_deta_pho_parton", ";#Delta#eta_{#gamma q/g} = |#eta^{#gamma} - #eta^{q/g}|;Q", nBinsX_eta, axis_eta_min, axis_eta_max, nBinsX_pt, axis_pt_min, axis_pt_max);

    int nEvents = T->GetEntries();
    std::cout << "nEvents = " << nEvents << std::endl;
    std::cout << "Loop STARTED" << std::endl;
    for (int iEvent = 0; iEvent < nEvents; ++iEvent) {

        T->GetEntry(iEvent);

        // hard scatterer analysis
        // outgoing particles are at index 5 and 6
        int ip1 = 5;
        int ip2 = 6;
        int iGamma = -1;
        iGamma = (isGamma((*event)[ip1])) ? ip1 : ip2;
        if ((isGamma((*event)[ip1])) && ((*event)[ip2].isParton()))
            iGamma = ip1;
        else if ((isGamma((*event)[ip2])) && ((*event)[ip1].isParton()))
            iGamma = ip2;
        if (iGamma == -1) continue;

        int iParton = (iGamma == ip1) ? ip2 : ip1;

        double pt_pho = (*event)[iGamma].pT();
        double eta_pho = (*event)[iGamma].eta();

        h_pt_pho->Fill(pt_pho);
        h_eta_pho->Fill(TMath::Abs(eta_pho));
        h2_qscale_pt_pho->Fill(pt_pho, event->scale());
        h2_qscale_eta_pho->Fill(TMath::Abs(eta_pho), event->scale());

        double pt_parton = (*event)[iParton].pT();
        double eta_parton = (*event)[iParton].eta();

        double deta_pho_parton = TMath::Abs(eta_pho - eta_parton);
        h2_qscale_deta_pho_parton->Fill(deta_pho_parton, event->scale());

        h_pt_parton->Fill(pt_parton);
        h_eta_parton->Fill(TMath::Abs(eta_parton));
        h_deta_pho_parton->Fill(deta_pho_parton);
        if (isQuark((*event)[iParton])) {
            h_pt_q->Fill(pt_parton);
            h_eta_q->Fill(TMath::Abs(eta_parton));
            h_pt_pho_ratio_q->Fill(pt_pho);
            h_deta_pho_q->Fill(deta_pho_parton);
        }
        else if (isGluon((*event)[iParton])) {
            h_pt_g->Fill(pt_parton);
            h_eta_g->Fill(TMath::Abs(eta_parton));
            h_pt_pho_ratio_g->Fill(pt_pho);
            h_deta_pho_g->Fill(deta_pho_parton);
        }
    }
    std::cout << "Loop ENDED" << std::endl;
    std::cout << "Closing the input file" << std::endl;
    inputFile->Close();

    // Save histogram on file and close file.
    std::cout << "saving histograms" << std::endl;

    h_pt_pho_ratio_q->Divide(h_pt_pho);
    h_pt_pho_ratio_g->Divide(h_pt_pho);

    h_pt_pho->Scale(1./h_pt_pho->Integral(), "width");
    h_eta_pho->Scale(1./h_eta_pho->Integral(), "width");

    h_pt_parton->Scale(1./h_pt_parton->Integral(), "width");
    h_eta_parton->Scale(1./h_eta_parton->Integral(), "width");
    h_pt_q->Scale(1./h_pt_q->Integral(), "width");
    h_eta_q->Scale(1./h_eta_q->Integral(), "width");
    h_pt_g->Scale(1./h_pt_g->Integral(), "width");
    h_eta_g->Scale(1./h_eta_g->Integral(), "width");

    h_deta_pho_parton->Scale(1./h_deta_pho_parton->Integral(), "width");
    h_deta_pho_q->Scale(1./h_deta_pho_q->Integral(), "width");
    h_deta_pho_g->Scale(1./h_deta_pho_g->Integral(), "width");

    outputFile->Write("", TObject::kOverwrite);
    std::cout << "Closing the output file" << std::endl;
    outputFile->Close();

    return 0;
}
