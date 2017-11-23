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
#include "TMath.h"
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
    std::cout << "running photonPartonAna()" << std::endl;

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
    int nBinsX_phi = 20;
    int nBinsX_phoqgX = 20;
    double axis_phoqgX_min = 0;
    double axis_phoqgX_max = 2;
    TH1D* h_phoPt = new TH1D("h_phoPt",";p_{T}^{#gamma};", nBinsX_pt, axis_pt_min, axis_pt_max);
    TH1D* h_phoEta = new TH1D("h_phoEta",";|#eta^{#gamma}|;", nBinsX_eta, axis_eta_min, axis_eta_max);
    TH2D* h2_phoEta_phoPt = new TH2D("h2_phoEta_phoPt",";|#eta^{#gamma}|;p_{T}^{#gamma}",
            nBinsX_eta, axis_eta_min, axis_eta_max, nBinsX_pt, axis_pt_min, axis_pt_max);

    // event info
    TH2D* h2_qscale_phoPt = new TH2D("h2_qscale_phoPt", ";p_{T}^{#gamma};Q", nBinsX_pt, axis_pt_min, axis_pt_max, nBinsX_pt, axis_pt_min, axis_pt_max);
    TH2D* h2_qscale_phoEta = new TH2D("h2_qscale_phoEta", ";|#eta^{#gamma}|;Q", nBinsX_eta, axis_eta_min, axis_eta_max, nBinsX_pt, axis_pt_min, axis_pt_max);

    enum PARTONTYPES {
        kInclusive,
        kQuark,
        kGluon,
        kN_PARTONTYPES
    };
    std::string partonTypesStr[kN_PARTONTYPES] = {"parton", "q", "g"};
    std::string partonTypesLabel[kN_PARTONTYPES] = {"q/g", "q", "g"};

    // parton histograms
    TH1D* h_qgPt[kN_PARTONTYPES];
    TH1D* h_qgEta[kN_PARTONTYPES];
    TH2D* h2_qgEta_qgPt[kN_PARTONTYPES];
    // photon-parton histograms
    TH1D* h_phoqgDeta[kN_PARTONTYPES];
    TH1D* h_phoqgDphi[kN_PARTONTYPES];
    TH1D* h_phoqgX[kN_PARTONTYPES];
    TH2D* h2_phoEta_qgEta[kN_PARTONTYPES];
    TH2D* h2_phoPhi_qgPhi[kN_PARTONTYPES];
    TH2D* h2_qscale_phoqgDeta[kN_PARTONTYPES];
    // photon histograms split for parton types
    TH1D* h_phoPt_qgRatio[kN_PARTONTYPES];
    for (int i = 0; i < kN_PARTONTYPES; ++i) {
        h_qgPt[i] = new TH1D(Form("h_%sPt", partonTypesStr[i].c_str()),
                Form(";p_{T}^{%s};", partonTypesLabel[i].c_str()),
                nBinsX_pt, axis_pt_min, axis_pt_max);

        h_qgEta[i] = new TH1D(Form("h_%sEta", partonTypesStr[i].c_str()),
                Form(";|#eta^{%s}|;", partonTypesLabel[i].c_str()),
                nBinsX_eta, axis_eta_min, axis_eta_max);

        h2_qgEta_qgPt[i] = new TH2D(Form("h2_%sEta_%sPt", partonTypesStr[i].c_str(), partonTypesStr[i].c_str()),
                Form(";|#eta^{%s}|;p_{T}^{%s}", partonTypesLabel[i].c_str(), partonTypesLabel[i].c_str()),
                nBinsX_eta, axis_eta_min, axis_eta_max, nBinsX_pt, axis_pt_min, axis_pt_max);

        h_phoqgDeta[i] = new TH1D(Form("h_pho%sDeta", partonTypesStr[i].c_str()),
                Form(";#Delta#eta_{#gamma %s} = |#eta^{#gamma} - #eta^{%s}|;", partonTypesLabel[i].c_str(), partonTypesLabel[i].c_str()),
                nBinsX_eta, axis_eta_min, 1.5*axis_eta_max);

        h_phoqgDphi[i] = new TH1D(Form("h_pho%sDphi", partonTypesStr[i].c_str()),
                Form(";#Delta#phi_{#gamma %s} = |#phi^{#gamma} - #phi^{%s}|;", partonTypesLabel[i].c_str(), partonTypesLabel[i].c_str()),
                nBinsX_phi, 0, TMath::Pi()+1e-12);

        h_phoqgX[i] = new TH1D(Form("h_pho%sX", partonTypesStr[i].c_str()),
                Form(";X_{#gamma %s} = p_{T}^{%s}/p_{T}^{#gamma};", partonTypesLabel[i].c_str(), partonTypesLabel[i].c_str()),
                nBinsX_phoqgX, axis_phoqgX_min, axis_phoqgX_max);

        h2_phoEta_qgEta[i] = new TH2D(Form("h2_phoEta_%sEta", partonTypesStr[i].c_str()),
                Form(";#eta^{#gamma};#eta^{%s}", partonTypesLabel[i].c_str()),
                nBinsX_eta, -1*axis_eta_max, axis_eta_max, nBinsX_eta, -1*axis_eta_max, axis_eta_max);

        h2_phoPhi_qgPhi[i] = new TH2D(Form("h2_phoPhi_%sPhi", partonTypesStr[i].c_str()),
                Form(";#phi^{#gamma};#phi^{%s}", partonTypesLabel[i].c_str()),
                nBinsX_phi, -TMath::Pi(), TMath::Pi(), nBinsX_phi, -TMath::Pi(), TMath::Pi());

        h2_qscale_phoqgDeta[i] = new TH2D(Form("h2_qscale_pho%sDeta", partonTypesStr[i].c_str()),
                Form(";#Delta#eta_{#gamma %s} = |#eta^{#gamma} - #eta^{%s}|;Q", partonTypesLabel[i].c_str(), partonTypesLabel[i].c_str()),
                nBinsX_eta, axis_eta_min, axis_eta_max, nBinsX_pt, axis_pt_min, axis_pt_max);

        h_phoPt_qgRatio[i] = new TH1D(Form("h_phoPt_%sRatio", partonTypesStr[i].c_str()),
                ";p_{T}^{#gamma};",
                nBinsX_pt, axis_pt_min, axis_pt_max);
    }

    int nEvents = T->GetEntries();
    std::cout << "nEvents = " << nEvents << std::endl;
    std::cout << "Loop STARTED" << std::endl;
    for (int iEvent = 0; iEvent < nEvents; ++iEvent) {

        T->GetEntry(iEvent);

        // hard scatterer analysis
        // outgoing particles are at index 5 and 6
        int ip1 = 5;
        int ip2 = 6;
        int iPho = -1;
        if ((isGamma((*event)[ip1])) && (isParton((*event)[ip2])))
            iPho = ip1;
        else if ((isGamma((*event)[ip2])) && (isParton((*event)[ip1])))
            iPho = ip2;
        if (iPho == -1) continue;

        int iParton = (iPho == ip1) ? ip2 : ip1;

        double phoPt = (*event)[iPho].pT();
        double phoEta = (*event)[iPho].eta();
        double phoPhi = (*event)[iPho].phi();

        h_phoPt->Fill(phoPt);
        h_phoEta->Fill(TMath::Abs(phoEta));
        h2_phoEta_phoPt->Fill(TMath::Abs(phoEta), phoPt);
        h2_qscale_phoPt->Fill(phoPt, event->scale());
        h2_qscale_phoEta->Fill(TMath::Abs(phoEta), event->scale());

        double qgPt = (*event)[iParton].pT();
        double qgEta = (*event)[iParton].eta();
        double qgPhi = (*event)[iParton].phi();

        double phoqgDeta = TMath::Abs(phoEta - qgEta);
        double phoqgDphi = std::acos(cos(phoPhi - qgPhi));
        double phoqgX = qgPt / phoPt;

        h_qgPt[kInclusive]->Fill(qgPt);
        h_qgEta[kInclusive]->Fill(TMath::Abs(qgEta));
        h2_qgEta_qgPt[kInclusive]->Fill(TMath::Abs(qgEta), qgPt);
        h_phoqgDeta[kInclusive]->Fill(phoqgDeta);
        h_phoqgDphi[kInclusive]->Fill(phoqgDphi);
        h_phoqgX[kInclusive]->Fill(phoqgX);
        h2_phoEta_qgEta[kInclusive]->Fill(phoEta, qgEta);
        h2_phoPhi_qgPhi[kInclusive]->Fill(phoPhi, qgPhi);
        h2_qscale_phoqgDeta[kInclusive]->Fill(phoqgDeta, event->scale());
        h_phoPt_qgRatio[kInclusive]->Fill(phoPt);

        int iQG = (isQuark((*event)[iParton])) ? kQuark : kGluon;

        h_qgPt[iQG]->Fill(qgPt);
        h_qgEta[iQG]->Fill(TMath::Abs(qgEta));
        h2_qgEta_qgPt[iQG]->Fill(TMath::Abs(qgEta), qgPt);
        h_phoqgDeta[iQG]->Fill(phoqgDeta);
        h_phoqgDphi[iQG]->Fill(phoqgDphi);
        h_phoqgX[iQG]->Fill(phoqgX);
        h2_phoEta_qgEta[iQG]->Fill(phoEta, qgEta);
        h2_phoPhi_qgPhi[iQG]->Fill(phoPhi, qgPhi);
        h2_qscale_phoqgDeta[iQG]->Fill(phoqgDeta, event->scale());
        h_phoPt_qgRatio[iQG]->Fill(phoPt);
    }
    std::cout << "Loop ENDED" << std::endl;
    std::cout << "Closing the input file" << std::endl;
    inputFile->Close();

    // Save histogram on file and close file.
    std::cout << "saving histograms" << std::endl;

    h_phoPt->Scale(1./h_phoPt->Integral(), "width");
    h_phoEta->Scale(1./h_phoEta->Integral(), "width");

    for (int i = 0; i < kN_PARTONTYPES; ++i) {

        h_qgPt[i]->Scale(1./h_qgPt[i]->Integral(), "width");
        h_qgEta[i]->Scale(1./h_qgEta[i]->Integral(), "width");
        h_phoqgDeta[i]->Scale(1./h_phoqgDeta[i]->Integral(), "width");
        h_phoqgDphi[i]->Scale(1./h_phoqgDphi[i]->Integral(), "width");
        h_phoqgX[i]->Scale(1./h_phoqgX[i]->Integral(), "width");

        if (i != kInclusive) {
            h_phoPt_qgRatio[i]->Divide(h_phoPt_qgRatio[kInclusive]);
        }
    }

    outputFile->Write("", TObject::kOverwrite);
    std::cout << "Closing the output file" << std::endl;
    outputFile->Close();

    std::cout << "running photonPartonAna() - END" << std::endl;

    return 0;
}
