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
#include "../utils/physicsUtil.h"

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
    TTree *treeEvt = (TTree*)inputFile->Get("evt");
    treeEvt->SetBranchAddress("event", &event);

    Pythia8::Event *eventParton = 0;
    TTree* treeEvtParton = (TTree*)inputFile->Get("evtParton");
    treeEvtParton->SetBranchAddress("event", &eventParton);

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
    int nBinsX_phoqgX = 16;
    double axis_phoqgX_min = 0;
    double axis_phoqgX_max = 2;
    TH1D* h_phoPt = new TH1D("h_phoPt",";p_{T}^{#gamma};", nBinsX_pt, axis_pt_min, axis_pt_max);
    TH1D* h_phoEta = new TH1D("h_phoEta",";|#eta^{#gamma}|;", nBinsX_eta, axis_eta_min, axis_eta_max);
    TH1D* h_phoY = new TH1D("h_phoY",";|y^{#gamma}|;", nBinsX_eta, axis_eta_min, axis_eta_max);
    TH2D* h2_phoEta_phoPt = new TH2D("h2_phoEta_phoPt",";|#eta^{#gamma}|;p_{T}^{#gamma}",
            nBinsX_eta, axis_eta_min, axis_eta_max, nBinsX_pt, axis_pt_min, axis_pt_max);
    TH2D* h2_phoY_phoPt = new TH2D("h2_phoY_phoPt",";|y^{#gamma}|;p_{T}^{#gamma}",
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
    TH1D* h_qgY[kN_PARTONTYPES];
    TH2D* h2_qgEta_qgPt[kN_PARTONTYPES];
    TH2D* h2_qgY_qgPt[kN_PARTONTYPES];
    // photon-parton histograms
    TH1D* h_phoqgDeta[kN_PARTONTYPES];
    TH1D* h_phoqgDphi[kN_PARTONTYPES];
    TH1D* h_phoqgDy[kN_PARTONTYPES];
    TH1D* h_phoqgX[kN_PARTONTYPES];
    TH2D* h2_phoEta_qgEta[kN_PARTONTYPES];
    TH2D* h2_phoPhi_qgPhi[kN_PARTONTYPES];
    TH2D* h2_phoY_qgY[kN_PARTONTYPES];
    TH2D* h2_qscale_phoqgDeta[kN_PARTONTYPES];
    // photon histograms split for parton types
    TH1D* h_phoPt_qgRatio[kN_PARTONTYPES];
    // histograms for energy and multiplicity distribution of final partons as func. of angle with the initial parton
    TH1D* h_finalqg_qg_dR[kN_PARTONTYPES][kN_PARTONTYPES];
    TH1D* h_finalqg_qg_dR_wE[kN_PARTONTYPES][kN_PARTONTYPES];
    TH1D* h_finalqg_qg_dR_cdf[kN_PARTONTYPES][kN_PARTONTYPES];
    TH1D* h_finalqg_qg_dR_wE_cdf[kN_PARTONTYPES][kN_PARTONTYPES];
    for (int i = 0; i < kN_PARTONTYPES; ++i) {
        h_qgPt[i] = new TH1D(Form("h_%sPt", partonTypesStr[i].c_str()),
                Form(";p_{T}^{%s};", partonTypesLabel[i].c_str()),
                nBinsX_pt, axis_pt_min, axis_pt_max);

        h_qgEta[i] = new TH1D(Form("h_%sEta", partonTypesStr[i].c_str()),
                Form(";|#eta^{%s}|;", partonTypesLabel[i].c_str()),
                nBinsX_eta, axis_eta_min, axis_eta_max);

        h_qgY[i] = new TH1D(Form("h_%sY", partonTypesStr[i].c_str()),
                Form(";|y^{%s}|;", partonTypesLabel[i].c_str()),
                nBinsX_eta, axis_eta_min, axis_eta_max);

        h2_qgEta_qgPt[i] = new TH2D(Form("h2_%sEta_%sPt", partonTypesStr[i].c_str(), partonTypesStr[i].c_str()),
                Form(";|#eta^{%s}|;p_{T}^{%s}", partonTypesLabel[i].c_str(), partonTypesLabel[i].c_str()),
                nBinsX_eta, axis_eta_min, axis_eta_max, nBinsX_pt, axis_pt_min, axis_pt_max);

        h2_qgY_qgPt[i] = new TH2D(Form("h2_%sY_%sPt", partonTypesStr[i].c_str(), partonTypesStr[i].c_str()),
                Form(";|y^{%s}|;p_{T}^{%s}", partonTypesLabel[i].c_str(), partonTypesLabel[i].c_str()),
                nBinsX_eta, axis_eta_min, axis_eta_max, nBinsX_pt, axis_pt_min, axis_pt_max);

        h_phoqgDeta[i] = new TH1D(Form("h_pho%sDeta", partonTypesStr[i].c_str()),
                Form(";#Delta#eta_{%s#gamma} = |#eta^{%s} - #eta^{#gamma}|;", partonTypesLabel[i].c_str(), partonTypesLabel[i].c_str()),
                nBinsX_eta, axis_eta_min, 1.5*axis_eta_max);

        h_phoqgDphi[i] = new TH1D(Form("h_pho%sDphi", partonTypesStr[i].c_str()),
                Form(";#Delta#phi_{%s#gamma} = |#phi^{%s} - #phi^{#gamma}|;", partonTypesLabel[i].c_str(), partonTypesLabel[i].c_str()),
                nBinsX_phi, 0, TMath::Pi()+1e-12);

        h_phoqgDy[i] = new TH1D(Form("h_pho%sDy", partonTypesStr[i].c_str()),
                Form(";#Deltay_{%s#gamma} = |y^{%s} - y^{#gamma}|;", partonTypesLabel[i].c_str(), partonTypesLabel[i].c_str()),
                nBinsX_eta, axis_eta_min, 1.5*axis_eta_max);

        h_phoqgX[i] = new TH1D(Form("h_pho%sX", partonTypesStr[i].c_str()),
                Form(";x_{%s#gamma} = p_{T}^{%s}/p_{T}^{#gamma};", partonTypesLabel[i].c_str(), partonTypesLabel[i].c_str()),
                nBinsX_phoqgX, axis_phoqgX_min, axis_phoqgX_max);

        h2_phoEta_qgEta[i] = new TH2D(Form("h2_phoEta_%sEta", partonTypesStr[i].c_str()),
                Form(";#eta^{#gamma};#eta^{%s}", partonTypesLabel[i].c_str()),
                nBinsX_eta, -1*axis_eta_max, axis_eta_max, nBinsX_eta, -1*axis_eta_max, axis_eta_max);

        h2_phoPhi_qgPhi[i] = new TH2D(Form("h2_phoPhi_%sPhi", partonTypesStr[i].c_str()),
                Form(";#phi^{#gamma};#phi^{%s}", partonTypesLabel[i].c_str()),
                nBinsX_phi, -TMath::Pi(), TMath::Pi(), nBinsX_phi, -TMath::Pi(), TMath::Pi());

        h2_phoY_qgY[i] = new TH2D(Form("h2_phoY_%sY", partonTypesStr[i].c_str()),
                Form(";y^{#gamma};y^{%s}", partonTypesLabel[i].c_str()),
                nBinsX_eta, -1*axis_eta_max, axis_eta_max, nBinsX_eta, -1*axis_eta_max, axis_eta_max);

        h2_qscale_phoqgDeta[i] = new TH2D(Form("h2_qscale_pho%sDeta", partonTypesStr[i].c_str()),
                Form(";#Delta#eta_{%s#gamma} = |#eta^{%s} - #eta^{#gamma}|;Q", partonTypesLabel[i].c_str(), partonTypesLabel[i].c_str()),
                nBinsX_eta, axis_eta_min, axis_eta_max, nBinsX_pt, axis_pt_min, axis_pt_max);

        h_phoPt_qgRatio[i] = new TH1D(Form("h_phoPt_%sRatio", partonTypesStr[i].c_str()),
                ";p_{T}^{#gamma};",
                nBinsX_pt, axis_pt_min, axis_pt_max);

        for (int j = 0; j < kN_PARTONTYPES; ++j) {
            h_finalqg_qg_dR[i][j] = new TH1D(Form("h_final%s_%s_dR", partonTypesStr[j].c_str(), partonTypesStr[i].c_str()),
                    Form(";#DeltaR_{%s final %s};", partonTypesLabel[i].c_str(), partonTypesLabel[j].c_str()), nBinsX_eta, 0, 1.5);

            h_finalqg_qg_dR_wE[i][j] = new TH1D(Form("h_final%s_%s_dR_wE", partonTypesStr[j].c_str(), partonTypesStr[i].c_str()),
                    Form(";#DeltaR_{%s final %s};", partonTypesLabel[i].c_str(), partonTypesLabel[j].c_str()), nBinsX_eta, 0, 1.5);
        }
    }

    int nEvents = treeEvt->GetEntries();
    std::cout << "nEvents = " << nEvents << std::endl;
    std::cout << "Loop STARTED" << std::endl;
    for (int iEvent = 0; iEvent < nEvents; ++iEvent) {

        treeEvt->GetEntry(iEvent);
        treeEvtParton->GetEntry(iEvent);

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
        double phoY = (*event)[iPho].y();

        h_phoPt->Fill(phoPt);
        h_phoEta->Fill(TMath::Abs(phoEta));
        h_phoY->Fill(TMath::Abs(phoY));
        h2_phoEta_phoPt->Fill(TMath::Abs(phoEta), phoPt);
        h2_phoY_phoPt->Fill(TMath::Abs(phoY), phoPt);
        h2_qscale_phoPt->Fill(phoPt, event->scale());
        h2_qscale_phoEta->Fill(TMath::Abs(phoEta), event->scale());

        double qgE = (*event)[iParton].e();
        double qgPt = (*event)[iParton].pT();
        double qgEta = (*event)[iParton].eta();
        double qgPhi = (*event)[iParton].phi();
        double qgY = (*event)[iParton].y();

        double phoqgDeta = TMath::Abs(phoEta - qgEta);
        double phoqgDphi = std::acos(cos(phoPhi - qgPhi));
        double phoqgDy = TMath::Abs(phoY - qgY);
        double phoqgX = qgPt / phoPt;

        int iQG = (isQuark((*event)[iParton])) ? kQuark : kGluon;

        std::vector<int> typesQG = {kInclusive, iQG};
        int nTypesQG = typesQG.size();

        for (int j = 0; j < nTypesQG; ++j) {
            int k = typesQG[j];

            h_qgPt[k]->Fill(qgPt);
            h_qgEta[k]->Fill(TMath::Abs(qgEta));
            h_qgY[k]->Fill(TMath::Abs(qgY));
            h2_qgEta_qgPt[k]->Fill(TMath::Abs(qgEta), qgPt);
            h2_qgY_qgPt[k]->Fill(TMath::Abs(qgY), qgPt);
            h_phoqgDeta[k]->Fill(phoqgDeta);
            h_phoqgDphi[k]->Fill(phoqgDphi);
            h_phoqgDy[k]->Fill(phoqgDy);
            h_phoqgX[k]->Fill(phoqgX);
            h2_phoEta_qgEta[k]->Fill(phoEta, qgEta);
            h2_phoPhi_qgPhi[k]->Fill(phoPhi, qgPhi);
            h2_phoY_qgY[k]->Fill(phoY, qgY);
            h2_qscale_phoqgDeta[k]->Fill(phoqgDeta, event->scale());
            h_phoPt_qgRatio[k]->Fill(phoPt);
        }

        int eventPartonSize = eventParton->size();
        for (int i = 0; i < eventPartonSize; ++i) {
            int indexOrig = (*eventParton)[i].mother1();

            if (isAncestor(event, indexOrig, iParton)) {
                double parton_qg_dR = getDR(qgEta, qgPhi, (*event)[indexOrig].eta(), (*event)[indexOrig].phi());
                double wE = (*event)[indexOrig].e() / qgE;

                int iFinalQG = (isQuark((*event)[indexOrig])) ? kQuark : kGluon;
                std::vector<int> typesFinalQG = {kInclusive, iFinalQG};
                int nTypesFinalQG = typesFinalQG.size();

                for (int j1 = 0; j1 < nTypesQG; ++j1) {
                    int k1 = typesQG[j1];

                    for (int j2 = 0; j2 < nTypesFinalQG; ++j2) {
                        int k2 = typesFinalQG[j2];

                        h_finalqg_qg_dR[k1][k2]->Fill(parton_qg_dR);
                        h_finalqg_qg_dR_wE[k1][k2]->Fill(parton_qg_dR, wE);
                    }
                }
            }
        }
    }
    std::cout << "Loop ENDED" << std::endl;
    std::cout << "Closing the input file" << std::endl;
    inputFile->Close();

    // Save histogram on file and close file.
    std::cout << "saving histograms" << std::endl;

    h_phoPt->Scale(1./h_phoPt->Integral(), "width");
    h_phoEta->Scale(1./h_phoEta->Integral(), "width");
    h_phoY->Scale(1./h_phoY->Integral(), "width");

    for (int i = 0; i < kN_PARTONTYPES; ++i) {

        double nPartons = h_qgPt[i]->GetEntries();

        h_qgPt[i]->Scale(1./h_qgPt[i]->Integral(), "width");
        h_qgEta[i]->Scale(1./h_qgEta[i]->Integral(), "width");
        h_qgY[i]->Scale(1./h_qgY[i]->Integral(), "width");
        h_phoqgDeta[i]->Scale(1./h_phoqgDeta[i]->Integral(), "width");
        h_phoqgDphi[i]->Scale(1./h_phoqgDphi[i]->Integral(), "width");
        h_phoqgDy[i]->Scale(1./h_phoqgDy[i]->Integral(), "width");
        h_phoqgX[i]->Scale(1./h_phoqgX[i]->Integral(), "width");

        for (int j = 0; j < kN_PARTONTYPES; ++j) {
            h_finalqg_qg_dR_cdf[i][j] = (TH1D*)h_finalqg_qg_dR[i][j]->GetCumulative(true, "_cdf");
            h_finalqg_qg_dR_wE_cdf[i][j] = (TH1D*)h_finalqg_qg_dR_wE[i][j]->GetCumulative(true, "_cdf");

            h_finalqg_qg_dR[i][j]->Scale(1./nPartons, "width");
            h_finalqg_qg_dR_wE[i][j]->Scale(1./nPartons, "width");
            h_finalqg_qg_dR_cdf[i][j]->Scale(1./nPartons);
            h_finalqg_qg_dR_wE_cdf[i][j]->Scale(1./nPartons);
        }

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
