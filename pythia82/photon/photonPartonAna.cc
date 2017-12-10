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
#include "../../utilities/physicsUtil.h"
#include "../../utilities/th1Util.h"

#include <iostream>
#include <string>
#include <vector>

void photonPartonAna(std::string inputFileName = "promptPhoton.root", std::string outputFileName = "photonPartonAna_out.root",
                     int iStatusPhoton = 0, int iStatusParton = 0);

void photonPartonAna(std::string inputFileName, std::string outputFileName, int iStatusPhoton, int iStatusParton)
{
    std::cout << "running photonPartonAna()" << std::endl;

    std::cout << "##### Parameters #####" << std::endl;
    std::cout << "inputFileName = " << inputFileName.c_str() << std::endl;
    std::cout << "outputFileName = " << outputFileName.c_str() << std::endl;
    std::cout << "iStatusPhoton = " << iStatusPhoton << std::endl;
    std::cout << "iStatusParton = " << iStatusParton << std::endl;
    std::cout << "##### Parameters - END #####" << std::endl;

    TFile *inputFile = TFile::Open(inputFileName.c_str(),"READ");
    Pythia8::Event *event = 0;
    TTree *treeEvt = (TTree*)inputFile->Get("evt");
    treeEvt->SetBranchAddress("event", &event);

    Pythia8::Event *eventParton = 0;
    TTree* treeEvtParton = (TTree*)inputFile->Get("evtParton");
    treeEvtParton->SetBranchAddress("event", &eventParton);

    Pythia8::Info *info = 0;
    TTree* treeEvtInfo = (TTree*)inputFile->Get("evtInfo");
    treeEvtInfo->SetBranchAddress("info", &info);

    TFile* outputFile = new TFile(outputFileName.c_str(), "RECREATE");

    TH1::SetDefaultSumw2();

    enum STATUSES {
        kHard,
        kOut,
        kN_STATUSES
    };
    std::string statusesStr[kN_STATUSES] = {"sHard", "sOut"};

    // photon histograms
    int nBinsX_pt = 36;
    double axis_pt_min = 60;
    double axis_pt_max = 180+axis_pt_min;
    int nBinsX_eta = 20;
    double axis_eta_min = 0;
    double axis_eta_max = 5;
    int nBinsX_phi = 20;
    int nBinsX_phoqgX = 16;
    double axis_phoqgX_min = 0;
    double axis_phoqgX_max = 2;

    int nBinsX_ratio_pt = 50;
    double axis_ratio_pt_min = 0;
    double axis_ratio_pt_max = 2;

    int nBinsX_diff_eta = 50;
    double axis_diff_eta_max = 0.5;
    double axis_diff_eta_min = -1*axis_diff_eta_max;
    int nBinsX_diff_phi = 50;
    double axis_diff_phi_max = 0.5;
    double axis_diff_phi_min = -1*axis_diff_phi_max;

    std::string strPho = "#gamma";
    std::string strPhoPt = Form("p_{T}^{%s}", strPho.c_str());
    std::string strPhoEta = Form("#eta^{%s}", strPho.c_str());
    std::string strPhoPhi = Form("#phi^{%s}", strPho.c_str());
    std::string strPhoY = Form("y^{%s}", strPho.c_str());

    TH1D* h_phoPt = new TH1D("h_phoPt", Form(";%s;", strPhoPt.c_str()),
                nBinsX_pt, axis_pt_min, axis_pt_max);
    TH1D* h_phoEta = new TH1D("h_phoEta", Form(";|%s|;", strPhoEta.c_str()),
                nBinsX_eta, axis_eta_min, axis_eta_max);
    TH1D* h_phoY = new TH1D("h_phoY", Form(";|%s|;", strPhoY.c_str()),
                nBinsX_eta, axis_eta_min, axis_eta_max);

    TH2D* h2_phoEta_phoPt = new TH2D("h2_phoEta_phoPt",
                Form(";|%s|;%s", strPhoEta.c_str(), strPhoPt.c_str()),
                nBinsX_eta, axis_eta_min, axis_eta_max, nBinsX_pt, axis_pt_min, axis_pt_max);
    TH2D* h2_phoY_phoPt = new TH2D("h2_phoY_phoPt",
                Form(";|%s|;%s", strPhoY.c_str(), strPhoPt.c_str()),
                nBinsX_eta, axis_eta_min, axis_eta_max, nBinsX_pt, axis_pt_min, axis_pt_max);

    // event info
    TH2D* h2_qscale_phoPt = new TH2D("h2_qscale_phoPt", ";p_{T}^{#gamma};Q", nBinsX_pt, axis_pt_min, axis_pt_max, nBinsX_pt, axis_pt_min, axis_pt_max);
    TH2D* h2_qscale_phoEta = new TH2D("h2_qscale_phoEta", ";|#eta^{#gamma}|;Q", nBinsX_eta, axis_eta_min, axis_eta_max, nBinsX_pt, axis_pt_min, axis_pt_max);

    // ratio / difference of outgoing photon and hard process photon pt / eta / phi
    TH2D* h2_pt_phoPt_ratio_sOut_sHard = new TH2D("h2_pt_phoPt_ratio_sOut_sHard",
            Form(";%s (hard process);%s (outgoing) / %s (hard process)", strPhoPt.c_str(), strPhoPt.c_str(), strPhoPt.c_str()),
            nBinsX_pt, axis_pt_min, axis_pt_max, nBinsX_ratio_pt, axis_ratio_pt_min, axis_ratio_pt_max);
    TH2D* h2_pt_phoEta_diff_sOut_sHard = new TH2D("h2_pt_phoEta_diff_sOut_sHard",
            Form(";%s;%s (outgoing) - %s (hard process)", strPhoPt.c_str(), strPhoEta.c_str(), strPhoEta.c_str()),
            nBinsX_pt, axis_pt_min, axis_pt_max, nBinsX_diff_eta, axis_diff_eta_min, axis_diff_eta_max);
    TH2D* h2_pt_phoPhi_diff_sOut_sHard = new TH2D("h2_pt_phoPhi_diff_sOut_sHard",
            Form(";%s;%s (outgoing) - %s (hard process)", strPhoPt.c_str(), strPhoPhi.c_str(), strPhoPhi.c_str()),
            nBinsX_pt, axis_pt_min, axis_pt_max, nBinsX_diff_phi, axis_diff_phi_min, axis_diff_phi_max);
    TH2D* h2_nMPI_phoPt_ratio_sOut_sHard = new TH2D("h2_nMPI_phoPt_ratio_sOut_sHard",
            Form(";nMPI;%s (outgoing) / %s (hard process)", strPhoPt.c_str(), strPhoPt.c_str(), strPhoPt.c_str()),
            25, 0, 25, nBinsX_ratio_pt, axis_ratio_pt_min, axis_ratio_pt_max);
    TH2D* h2_nISR_phoPt_ratio_sOut_sHard = new TH2D("h2_nISR_phoPt_ratio_sOut_sHard",
            Form(";nISR;%s (outgoing) / %s (hard process)", strPhoPt.c_str(), strPhoPt.c_str(), strPhoPt.c_str()),
            45, 0, 45, nBinsX_ratio_pt, axis_ratio_pt_min, axis_ratio_pt_max);
    TH2D* h2_nFSR_phoPt_ratio_sOut_sHard = new TH2D("h2_nFSR_phoPt_ratio_sOut_sHard",
            Form(";nFSR;%s (outgoing) / %s (hard process)", strPhoPt.c_str(), strPhoPt.c_str(), strPhoPt.c_str()),
            50, 0, 250, nBinsX_ratio_pt, axis_ratio_pt_min, axis_ratio_pt_max);

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
    TH1D* h_phoqgMeanEta[kN_PARTONTYPES];
    TH2D* h2_phoEta_qgEta[kN_PARTONTYPES];
    TH2D* h2_phoPhi_qgPhi[kN_PARTONTYPES];
    TH2D* h2_phoY_qgY[kN_PARTONTYPES];
    TH2D* h2_qscale_phoqgDeta[kN_PARTONTYPES];
    TH2D* h2_phoqgMeanEta_x1overx2[kN_PARTONTYPES];
    // photon histograms split for parton types
    TH1D* h_phoPt_qgRatio[kN_PARTONTYPES];
    // ratio / difference of outgoing parton and hard process parton pt / eta / phi
    TH2D* h2_pt_qgPt_ratio_sOut_sHard[kN_PARTONTYPES];
    TH2D* h2_pt_qgEta_diff_sOut_sHard[kN_PARTONTYPES];
    TH2D* h2_pt_qgPhi_diff_sOut_sHard[kN_PARTONTYPES];
    TH2D* h2_nMPI_qgPt_ratio_sOut_sHard[kN_PARTONTYPES];
    TH2D* h2_nISR_qgPt_ratio_sOut_sHard[kN_PARTONTYPES];
    TH2D* h2_nFSR_qgPt_ratio_sOut_sHard[kN_PARTONTYPES];
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
        std::string strPhoPartonDeta = Form("#Delta#eta_{%s %s} = |%s - %s|",
                partonTypesLabel[i].c_str(), strPho.c_str(), strPartonEta.c_str(), strPhoEta.c_str());
        std::string strPhoPartonDphi = Form("#Delta#phi_{%s %s} = |%s - %s|",
                partonTypesLabel[i].c_str(), strPho.c_str(), strPartonPhi.c_str(), strPhoPhi.c_str());
        std::string strPhoPartonDy = Form("#Deltay_{%s %s} = |%s - %s|",
                partonTypesLabel[i].c_str(), strPho.c_str(), strPartonY.c_str(), strPhoY.c_str());
        std::string strPhoPartonMeanEta = Form("#eta_{ave %s %s} = (%s + %s) / 2",
                partonTypesLabel[i].c_str(), strPho.c_str(), strPartonEta.c_str(), strPhoEta.c_str());
        std::string strPhoPartonMeanEtaAbs = Form("|#eta_{ave %s %s}| = |%s + %s| / 2",
                        partonTypesLabel[i].c_str(), strPho.c_str(), strPartonEta.c_str(), strPhoEta.c_str());

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

        h_phoqgMeanEta[i] = new TH1D(Form("h_pho%sMeanEta", partonTypesStr[i].c_str()),
                Form(";%s;", strPhoPartonMeanEtaAbs.c_str()),
                nBinsX_eta, 0, 0.8*axis_eta_max);

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

        int nBins_x1Overx2 = 50;
        std::vector<double> binsVec = calcBinsLogScale(0.001, 1000, nBins_x1Overx2);
        double binsArr[nBins_x1Overx2+1];
        std::copy(binsVec.begin(), binsVec.end(), binsArr);
        h2_phoqgMeanEta_x1overx2[i] = new TH2D(Form("h2_pho%sMeanEta_x1overx2", partonTypesStr[i].c_str()),
                Form(";%s;x_{1} / x_{2}", strPhoPartonMeanEta.c_str()),
                nBinsX_eta, -0.8*axis_eta_max, 0.8*axis_eta_max, nBins_x1Overx2, binsArr);

        h_phoPt_qgRatio[i] = new TH1D(Form("h_phoPt_%sRatio", partonTypesStr[i].c_str()),
                Form(";%s;", strPhoPt.c_str()),
                nBinsX_pt, axis_pt_min, axis_pt_max);

        h2_pt_qgPt_ratio_sOut_sHard[i] = new TH2D(Form("h2_pt_%sPt_ratio_sOut_sHard", partonTypesStr[i].c_str()),
                Form(";%s (hard process);%s (outgoing) / %s (hard process)", strPartonPt.c_str(), strPartonPt.c_str(), strPartonPt.c_str()),
                nBinsX_pt, axis_pt_min, axis_pt_max, nBinsX_ratio_pt, axis_ratio_pt_min, axis_ratio_pt_max);

        h2_pt_qgEta_diff_sOut_sHard[i] = new TH2D(Form("h2_pt_%sEta_diff_sOut_sHard", partonTypesStr[i].c_str()),
                Form(";%s;%s (outgoing) - %s (hard process)", strPartonPt.c_str(), strPartonEta.c_str(), strPartonEta.c_str()),
                nBinsX_pt, axis_pt_min, axis_pt_max, nBinsX_diff_eta, axis_diff_eta_min, axis_diff_eta_max);

        h2_pt_qgPhi_diff_sOut_sHard[i] = new TH2D(Form("h2_pt_%sPhi_diff_sOut_sHard", partonTypesStr[i].c_str()),
                Form(";%s;%s (outgoing) - %s (hard process)", strPartonPt.c_str(), strPartonPhi.c_str(), strPartonPhi.c_str()),
                nBinsX_pt, axis_pt_min, axis_pt_max, nBinsX_diff_phi, axis_diff_phi_min, axis_diff_phi_max);

        h2_nMPI_qgPt_ratio_sOut_sHard[i] = new TH2D(Form("h2_nMPI_%sPt_ratio_sOut_sHard", partonTypesStr[i].c_str()),
                Form(";nMPI;%s (outgoing) / %s (hard process)", strPartonPt.c_str(), strPartonPt.c_str(), strPartonPt.c_str()),
                25, 0, 25, nBinsX_ratio_pt, axis_ratio_pt_min, axis_ratio_pt_max);

        h2_nISR_qgPt_ratio_sOut_sHard[i] = new TH2D(Form("h2_nISR_%sPt_ratio_sOut_sHard", partonTypesStr[i].c_str()),
                Form(";nISR;%s (outgoing) / %s (hard process)", strPartonPt.c_str(), strPartonPt.c_str(), strPartonPt.c_str()),
                45, 0, 45, nBinsX_ratio_pt, axis_ratio_pt_min, axis_ratio_pt_max);

        h2_nFSR_qgPt_ratio_sOut_sHard[i] = new TH2D(Form("h2_nFSR_%sPt_ratio_sOut_sHard", partonTypesStr[i].c_str()),
                Form(";nFSR;%s (outgoing) / %s (hard process)", strPartonPt.c_str(), strPartonPt.c_str(), strPartonPt.c_str()),
                50, 0, 250, nBinsX_ratio_pt, axis_ratio_pt_min, axis_ratio_pt_max);

        for (int j = 0; j < kN_PARTONTYPES; ++j) {
            h_finalqg_qg_dR[i][j] = new TH1D(Form("h_final%s_%s_dR", partonTypesStr[j].c_str(), partonTypesStr[i].c_str()),
                    Form(";#DeltaR_{%s final %s};", partonTypesLabel[i].c_str(), partonTypesLabel[j].c_str()), nBinsX_eta, 0, 1.5);

            h_finalqg_qg_dR_wE[i][j] = new TH1D(Form("h_final%s_%s_dR_wE", partonTypesStr[j].c_str(), partonTypesStr[i].c_str()),
                    Form(";#DeltaR_{%s final %s};", partonTypesLabel[i].c_str(), partonTypesLabel[j].c_str()), nBinsX_eta, 0, 1.5);
        }
    }

    int eventsAnalyzed = 0;
    int nEvents = treeEvt->GetEntries();
    std::cout << "nEvents = " << nEvents << std::endl;
    std::cout << "Loop STARTED" << std::endl;
    for (int iEvent = 0; iEvent < nEvents; ++iEvent) {

        treeEvt->GetEntry(iEvent);
        treeEvtParton->GetEntry(iEvent);
        treeEvtInfo->GetEntry(iEvent);

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

        eventsAnalyzed++;

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
        if ((iOutPho == -1 || nOutPhoCand != 1) && iStatusPhoton == kOut)  continue;

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

        h_phoPt->Fill(phoPt[iStatusPhoton]);
        h_phoEta->Fill(TMath::Abs(phoEta[iStatusPhoton]));
        h_phoY->Fill(TMath::Abs(phoY[iStatusPhoton]));
        h2_phoEta_phoPt->Fill(TMath::Abs(phoEta[iStatusPhoton]), phoPt[iStatusPhoton]);
        h2_phoY_phoPt->Fill(TMath::Abs(phoY[iStatusPhoton]), phoPt[iStatusPhoton]);

        h2_qscale_phoPt->Fill(phoPt[iStatusPhoton], event->scale());
        h2_qscale_phoEta->Fill(TMath::Abs(phoEta[iStatusPhoton]), event->scale());

        h2_pt_phoPt_ratio_sOut_sHard->Fill(phoPt[kHard], phoPt[kOut] / phoPt[kHard]);
        h2_pt_phoEta_diff_sOut_sHard->Fill(phoPt[kHard], phoEta[kOut] - phoEta[kHard]);
        h2_pt_phoPhi_diff_sOut_sHard->Fill(phoPt[kHard], getDPHI(phoPhi[kOut], phoPhi[kHard]));
        h2_nMPI_phoPt_ratio_sOut_sHard->Fill(info->nMPI(), phoPt[kOut] / phoPt[kHard]);
        h2_nISR_phoPt_ratio_sOut_sHard->Fill(info->nISR(), phoPt[kOut] / phoPt[kHard]);
        h2_nFSR_phoPt_ratio_sOut_sHard->Fill(info->nFSRinProc(), phoPt[kOut] / phoPt[kHard]);

        // search the hard scattering parton in final parton level particles
        int iOutParton = -1;
        double ptMax = -1;
        for (int i = 0; i < eventPartonSize; ++i) {

            if (!isParton((*eventParton)[i]))  continue;
            int indexOrig = (*eventParton)[i].mother1();

            // must be a daughter of the hard scattering particle
            if (!isAncestor(event, indexOrig, iPartonH))  continue;

            if ((*event)[indexOrig].pT() > ptMax) {
                iOutParton = indexOrig;
                ptMax = (*event)[indexOrig].pT();
            }
        }
        // there must be exactly one outgoing, final parton
        if (iOutParton == -1 && iStatusParton == kOut)  continue;

        std::vector<double> qgE(kN_STATUSES, -1);
        std::vector<double> qgPt(kN_STATUSES, -1);
        std::vector<double> qgEta(kN_STATUSES, -1);
        std::vector<double> qgPhi(kN_STATUSES, -1);
        std::vector<double> qgY(kN_STATUSES, -1);

        std::vector<int> indicesParton = {iPartonH, iOutParton};
        for (int i = 0; i < kN_STATUSES; ++i) {
            int j = indicesParton[i];

            qgE[i] = (*event)[j].e();
            qgPt[i] = (*event)[j].pT();
            qgEta[i] = (*event)[j].eta();
            qgPhi[i] = (*event)[j].phi();
            qgY[i] = (*event)[j].y();
        }

        double phoqgDeta = TMath::Abs(phoEta[iStatusPhoton] - qgEta[iStatusParton]);
        double phoqgDphi = std::acos(cos(phoPhi[iStatusPhoton] - qgPhi[iStatusParton]));
        double phoqgDy = TMath::Abs(phoY[iStatusPhoton] - qgY[iStatusParton]);
        double phoqgX = qgPt[iStatusParton] / phoPt[iStatusPhoton];
        double phoqgMeanEta = 0.5*(phoEta[iStatusPhoton] + qgEta[iStatusParton]);

        int iQG = (isQuark((*event)[iPartonH])) ? kQuark : kGluon;

        std::vector<int> typesQG = {kInclusive, iQG};
        int nTypesQG = typesQG.size();

        for (int j = 0; j < nTypesQG; ++j) {
            int k = typesQG[j];

            h_qgPt[k]->Fill(qgPt[iStatusParton]);
            h_qgEta[k]->Fill(TMath::Abs(qgEta[iStatusParton]));
            h_qgY[k]->Fill(TMath::Abs(qgY[iStatusParton]));
            h2_qgEta_qgPt[k]->Fill(TMath::Abs(qgEta[iStatusParton]), qgPt[iStatusParton]);
            h2_qgY_qgPt[k]->Fill(TMath::Abs(qgY[iStatusParton]), qgPt[iStatusParton]);
            h_phoqgDeta[k]->Fill(phoqgDeta);
            h_phoqgDphi[k]->Fill(phoqgDphi);
            h_phoqgDy[k]->Fill(phoqgDy);
            h_phoqgX[k]->Fill(phoqgX);
            h_phoqgMeanEta[k]->Fill(TMath::Abs(phoqgMeanEta));
            h2_phoEta_qgEta[k]->Fill(phoEta[iStatusPhoton], qgEta[iStatusParton]);
            h2_phoPhi_qgPhi[k]->Fill(phoPhi[iStatusPhoton], qgPhi[iStatusParton]);
            h2_phoY_qgY[k]->Fill(phoY[iStatusPhoton], qgY[iStatusParton]);
            h2_qscale_phoqgDeta[k]->Fill(phoqgDeta, event->scale());
            h2_phoqgMeanEta_x1overx2[k]->Fill(phoqgMeanEta, info->x1()/info->x2());
            h_phoPt_qgRatio[k]->Fill(phoPt[iStatusPhoton]);
            h2_pt_qgPt_ratio_sOut_sHard[k]->Fill(qgPt[kHard], qgPt[kOut] / qgPt[kHard]);
            h2_pt_qgEta_diff_sOut_sHard[k]->Fill(qgPt[kHard], qgEta[kOut] - qgEta[kHard]);
            h2_pt_qgPhi_diff_sOut_sHard[k]->Fill(qgPt[kHard], getDPHI(qgPhi[kOut], qgPhi[kHard]));
            h2_nMPI_qgPt_ratio_sOut_sHard[k]->Fill(info->nMPI(), qgPt[kOut] / qgPt[kHard]);
            h2_nISR_qgPt_ratio_sOut_sHard[k]->Fill(info->nISR(), qgPt[kOut] / qgPt[kHard]);
            h2_nFSR_qgPt_ratio_sOut_sHard[k]->Fill(info->nFSRinProc(), qgPt[kOut] / qgPt[kHard]);
        }

        for (int i = 0; i < eventPartonSize; ++i) {
            int indexOrig = (*eventParton)[i].mother1();

            if (isAncestor(event, indexOrig, iPartonH)) {
                double parton_qg_dR = getDR(qgEta[iStatusParton], qgPhi[iStatusParton], (*event)[indexOrig].eta(), (*event)[indexOrig].phi());
                double wE = (*event)[indexOrig].e() / qgE[iStatusParton];

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
    std::cout << "eventsAnalyzed = " << eventsAnalyzed << std::endl;
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
        h_phoqgMeanEta[i]->Scale(1./h_phoqgMeanEta[i]->Integral(), "width");

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
}

int main(int argc, char* argv[]) {

    if (argc == 5) {
        photonPartonAna(argv[1], argv[2], std::atoi(argv[3]), std::atoi(argv[4]));
        return 0;
    }
    else if (argc == 4) {
        photonPartonAna(argv[1], argv[2], std::atoi(argv[3]));
        return 0;
    }
    else if (argc == 3) {
        photonPartonAna(argv[1], argv[2]);
        return 0;
    }
    else if (argc == 2) {
        photonPartonAna(argv[1]);
        return 0;
    }
    else {
        std::cout << "Usage : \n" <<
                "./photonPartonAna.exe <inputFileName> <outputFileName> <iStatusPhoton> <iStatusParton>"
                << std::endl;
        return 1;
    }
}
