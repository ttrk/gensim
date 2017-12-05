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

    enum STATUSES {
        kHard,
        kOut,
        kN_STATUSES
    };
    std::string statusesStr[kN_STATUSES] = {"sHard", "sOut"};

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

    std::string strPho = "#gamma";
    std::string strPhoPt = Form("p_{T}^{%s}", strPho.c_str());
    std::string strPhoEta = Form("#eta^{%s}", strPho.c_str());
    std::string strPhoPhi = Form("#phi^{%s}", strPho.c_str());
    std::string strPhoY = Form("y^{%s}", strPho.c_str());

    TH1D* h_phoPt[kN_STATUSES];
    TH1D* h_phoEta[kN_STATUSES];
    TH1D* h_phoY[kN_STATUSES];
    TH2D* h2_phoEta_phoPt[kN_STATUSES];
    TH2D* h2_phoY_phoPt[kN_STATUSES];

    for (int i = 0; i < kN_STATUSES; ++i) {

        h_phoPt[i] = new TH1D(Form("h_%s_phoPt", statusesStr[i].c_str()), Form(";%s;", strPhoPt.c_str()),
                nBinsX_pt, axis_pt_min, axis_pt_max);
        h_phoEta[i] = new TH1D(Form("h_%s_phoEta", statusesStr[i].c_str()), Form(";|%s|;", strPhoEta.c_str()),
                nBinsX_eta, axis_eta_min, axis_eta_max);
        h_phoY[i] = new TH1D(Form("h_%s_phoY", statusesStr[i].c_str()), Form(";|%s|;", strPhoY.c_str()),
                nBinsX_eta, axis_eta_min, axis_eta_max);

        h2_phoEta_phoPt[i] = new TH2D(Form("h2_%s_phoEta_phoPt", statusesStr[i].c_str()),
                Form(";|%s|;%s", strPhoEta.c_str(), strPhoPt.c_str()),
                nBinsX_eta, axis_eta_min, axis_eta_max, nBinsX_pt, axis_pt_min, axis_pt_max);
        h2_phoY_phoPt[i] = new TH2D(Form("h2_%s_phoY_phoPt", statusesStr[i].c_str()),
                Form(";|%s|;%s", strPhoY.c_str(), strPhoPt.c_str()),
                nBinsX_eta, axis_eta_min, axis_eta_max, nBinsX_pt, axis_pt_min, axis_pt_max);
    }

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

        std::string strPartonPt = Form("p_{T}^{%s}", partonTypesLabel[i].c_str());
        std::string strPartonEta = Form("#eta^{%s}", partonTypesLabel[i].c_str());
        std::string strPartonPhi = Form("#phi^{%s}", partonTypesLabel[i].c_str());
        std::string strPartonY = Form("y^{%s}", partonTypesLabel[i].c_str());

        std::string strPhoPartonX = Form("x_{%s%s} = %s/%s", partonTypesLabel[i].c_str(), strPho.c_str(), strPartonPt.c_str(), strPhoPt.c_str());
        std::string strPhoPartonDeta = Form("#Delta#eta_{%s%s} = |%s - %s|",
                partonTypesLabel[i].c_str(), strPho.c_str(), strPartonEta.c_str(), strPhoEta.c_str());
        std::string strPhoPartonDphi = Form("#Delta#phi_{%s%s} = |%s - %s|",
                partonTypesLabel[i].c_str(), strPho.c_str(), strPartonPhi.c_str(), strPhoPhi.c_str());
        std::string strPhoPartonDy = Form("#Deltay_{%s%s} = |%s - %s|",
                partonTypesLabel[i].c_str(), strPho.c_str(), strPartonY.c_str(), strPhoY.c_str());

        h_qgPt[i] = new TH1D(Form("h_%sPt", partonTypesStr[i].c_str()),
                Form(";%s;", strPartonPt.c_str()),
                nBinsX_pt, axis_pt_min, axis_pt_max);

        h_qgEta[i] = new TH1D(Form("h_%sEta", partonTypesStr[i].c_str()),
                Form(";|%s|;", strPartonEta.c_str()),
                nBinsX_eta, axis_eta_min, axis_eta_max);

        h_qgY[i] = new TH1D(Form("h_%sY", partonTypesStr[i].c_str()),
                Form(";|%s|;", strPartonY.c_str()),
                nBinsX_eta, axis_eta_min, axis_eta_max);

        h2_qgEta_qgPt[i] = new TH2D(Form("h2_%sEta_%sPt", partonTypesStr[i].c_str(), partonTypesStr[i].c_str()),
                Form(";|%s|;%s", strPartonEta.c_str(), strPartonPt.c_str()),
                nBinsX_eta, axis_eta_min, axis_eta_max, nBinsX_pt, axis_pt_min, axis_pt_max);

        h2_qgY_qgPt[i] = new TH2D(Form("h2_%sY_%sPt", partonTypesStr[i].c_str(), partonTypesStr[i].c_str()),
                Form(";|%s|;%s", strPartonY.c_str(), strPartonPt.c_str()),
                nBinsX_eta, axis_eta_min, axis_eta_max, nBinsX_pt, axis_pt_min, axis_pt_max);

        h_phoqgDeta[i] = new TH1D(Form("h_pho%sDeta", partonTypesStr[i].c_str()),
                Form(";%s;", strPhoPartonDeta.c_str()),
                nBinsX_eta, axis_eta_min, 1.5*axis_eta_max);

        h_phoqgDphi[i] = new TH1D(Form("h_pho%sDphi", partonTypesStr[i].c_str()),
                Form(";%s;", strPhoPartonDphi.c_str()),
                nBinsX_phi, 0, TMath::Pi()+1e-12);

        h_phoqgDy[i] = new TH1D(Form("h_pho%sDy", partonTypesStr[i].c_str()),
                Form(";%s;", strPhoPartonDy.c_str()),
                nBinsX_eta, axis_eta_min, 1.5*axis_eta_max);

        h_phoqgX[i] = new TH1D(Form("h_pho%sX", partonTypesStr[i].c_str()),
                Form(";%s;", strPhoPartonX.c_str()),
                nBinsX_phoqgX, axis_phoqgX_min, axis_phoqgX_max);

        h2_phoEta_qgEta[i] = new TH2D(Form("h2_phoEta_%sEta", partonTypesStr[i].c_str()),
                Form(";%s;%s", strPhoEta.c_str(), strPartonEta.c_str()),
                nBinsX_eta, -1*axis_eta_max, axis_eta_max, nBinsX_eta, -1*axis_eta_max, axis_eta_max);

        h2_phoPhi_qgPhi[i] = new TH2D(Form("h2_phoPhi_%sPhi", partonTypesStr[i].c_str()),
                Form(";%s;%s", strPhoPhi.c_str(), strPartonPhi.c_str()),
                nBinsX_phi, -TMath::Pi(), TMath::Pi(), nBinsX_phi, -TMath::Pi(), TMath::Pi());

        h2_phoY_qgY[i] = new TH2D(Form("h2_phoY_%sY", partonTypesStr[i].c_str()),
                Form(";%s;%s", strPhoY.c_str(), strPartonY.c_str()),
                nBinsX_eta, -1*axis_eta_max, axis_eta_max, nBinsX_eta, -1*axis_eta_max, axis_eta_max);

        h2_qscale_phoqgDeta[i] = new TH2D(Form("h2_qscale_pho%sDeta", partonTypesStr[i].c_str()),
                Form(";%s;Q", strPhoPartonDeta.c_str()),
                nBinsX_eta, axis_eta_min, axis_eta_max, nBinsX_pt, axis_pt_min, axis_pt_max);

        h_phoPt_qgRatio[i] = new TH1D(Form("h_phoPt_%sRatio", partonTypesStr[i].c_str()),
                Form(";%s;", strPhoPt.c_str()),
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
        // outgoing particles of the hardest subprocess are at index 5 and 6
        int ip1H = 5;
        int ip2H = 6;
        int iPhoH = -1;
        if ((isGamma((*event)[ip1H])) && (isParton((*event)[ip2H])))
            iPhoH = ip1H;
        else if ((isGamma((*event)[ip2H])) && (isParton((*event)[ip1H])))
            iPhoH = ip2H;
        if (iPhoH == -1) continue;

        int iPartonH = (iPhoH == ip1H) ? ip2H : ip1H;

        int eventPartonSize = eventParton->size();
        // search the hard scattering photon in outgoing particles
        int iOutPho = -1;
        int nOutPhoCand = 0;
        for (int i = 0; i < eventPartonSize; ++i) {

            if (!isGamma((*eventParton)[i]))  continue;
            int indexOrig = (*eventParton)[i].mother1();

            if (hasDaughter((*event)[indexOrig]))  continue;

            // must be a daughter of the hard scattering particle
            if (!isAncestor(event, indexOrig, iPhoH))  continue;

            nOutPhoCand++;
            iOutPho = indexOrig;
        }
        // there must be exactly one outgoing, final photon
        if (iOutPho == -1 || nOutPhoCand != 1)  continue;

        std::vector<double> phoPt(kN_STATUSES, -1);
        std::vector<double> phoEta(kN_STATUSES, -1);
        std::vector<double> phoPhi(kN_STATUSES, -1);
        std::vector<double> phoY(kN_STATUSES, -1);

        std::vector<int> indicesPho = {iPhoH, iOutPho};
        for (int i = 0; i < kN_STATUSES; ++i) {
            int j = indicesPho[i];

            phoPt[i] = (*event)[j].pT();
            phoEta[i] = (*event)[j].eta();
            phoPhi[i] = (*event)[j].phi();
            phoY[i] = (*event)[j].y();
        }

        for (int i = 0; i < kN_STATUSES; ++i) {

            h_phoPt[i]->Fill(phoPt[i]);
            h_phoEta[i]->Fill(TMath::Abs(phoEta[i]));
            h_phoY[i]->Fill(TMath::Abs(phoY[i]));
            h2_phoEta_phoPt[i]->Fill(TMath::Abs(phoEta[i]), phoPt[i]);
            h2_phoY_phoPt[i]->Fill(TMath::Abs(phoY[i]), phoPt[i]);
        }
        h2_qscale_phoPt->Fill(phoPt[kHard], event->scale());
        h2_qscale_phoEta->Fill(TMath::Abs(phoEta[kHard]), event->scale());

        double hardQG_e = (*event)[iPartonH].e();
        double hardQG_pt = (*event)[iPartonH].pT();
        double hardQG_eta = (*event)[iPartonH].eta();
        double hardQG_phi = (*event)[iPartonH].phi();
        double hardQG_y = (*event)[iPartonH].y();

        double hardPhoQG_deta = TMath::Abs(phoEta[kHard] - hardQG_eta);
        double hardPhoQG_dphi = std::acos(cos(phoPhi[kHard] - hardQG_phi));
        double hardPhoQG_dy = TMath::Abs(phoY[kHard] - hardQG_y);
        double hardPhoQG_X = hardQG_pt / phoPt[kHard];

        int iQG = (isQuark((*event)[iPartonH])) ? kQuark : kGluon;

        std::vector<int> typesQG = {kInclusive, iQG};
        int nTypesQG = typesQG.size();

        for (int j = 0; j < nTypesQG; ++j) {
            int k = typesQG[j];

            h_qgPt[k]->Fill(hardQG_pt);
            h_qgEta[k]->Fill(TMath::Abs(hardQG_eta));
            h_qgY[k]->Fill(TMath::Abs(hardQG_y));
            h2_qgEta_qgPt[k]->Fill(TMath::Abs(hardQG_eta), hardQG_pt);
            h2_qgY_qgPt[k]->Fill(TMath::Abs(hardQG_y), hardQG_pt);
            h_phoqgDeta[k]->Fill(hardPhoQG_deta);
            h_phoqgDphi[k]->Fill(hardPhoQG_dphi);
            h_phoqgDy[k]->Fill(hardPhoQG_dy);
            h_phoqgX[k]->Fill(hardPhoQG_X);
            h2_phoEta_qgEta[k]->Fill(phoEta[kHard], hardQG_eta);
            h2_phoPhi_qgPhi[k]->Fill(phoPhi[kHard], hardQG_phi);
            h2_phoY_qgY[k]->Fill(phoY[kHard], hardQG_y);
            h2_qscale_phoqgDeta[k]->Fill(hardPhoQG_deta, event->scale());
            h_phoPt_qgRatio[k]->Fill(phoPt[kHard]);
        }

        for (int i = 0; i < eventPartonSize; ++i) {
            int indexOrig = (*eventParton)[i].mother1();

            if (isAncestor(event, indexOrig, iPartonH)) {
                double parton_qg_dR = getDR(hardQG_eta, hardQG_phi, (*event)[indexOrig].eta(), (*event)[indexOrig].phi());
                double wE = (*event)[indexOrig].e() / hardQG_e;

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

    for (int i = 0; i < kN_STATUSES; ++i) {

        h_phoPt[i]->Scale(1./h_phoPt[i]->Integral(), "width");
        h_phoEta[i]->Scale(1./h_phoEta[i]->Integral(), "width");
        h_phoY[i]->Scale(1./h_phoY[i]->Integral(), "width");
    }

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
