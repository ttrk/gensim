/*
 * code to analyze hard scattering events that produce jets.
 * Different types of analysis can be performed. Ex : V+jet, leading jet, dijet, inclusive jet
 * Integer codes for analysis types :
 * 0 = V+jet
 * 1 = leading jet
 * 2 = dijet
 * 3 = inclusive jet
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
#include "TLorentzVector.h"

// dictionary to read Pythia8::Event
#include "../dictionary/dict4RootDct.cc"
#include "../utils/pythiaUtil.h"
#include "../../fastjet3/fastJetTree.h"
#include "../../utilities/physicsUtil.h"
#include "../../utilities/th1Util.h"

#include <iostream>
#include <iomanip>
#include <string>
#include <vector>

void qcdAna(std::string eventFileName = "events.root", std::string jetFileName = "jets.root",
                  std::string jetTreeName = "ak3jets", std::string outputFileName = "qcdAna_out.root",
                  int anaType = 0, int processType = 0, int ewBosonType = 1);

void qcdAna(std::string eventFileName, std::string jetFileName, std::string jetTreeName, std::string outputFileName,
                  int anaType, int processType, int ewBosonType)
{
    std::cout << "running qcdAna()" << std::endl;

    std::cout << "##### Parameters #####" << std::endl;
    std::cout << "eventFileName = " << eventFileName.c_str() << std::endl;
    std::cout << "jetFileName = " << jetFileName.c_str() << std::endl;
    std::cout << "jetTreeName = " << jetTreeName.c_str() << std::endl;
    std::cout << "outputFileName = " << outputFileName.c_str() << std::endl;
    std::cout << "anaType = " << anaType << std::endl;
    std::cout << "processType = " << processType << std::endl;
    std::cout << "ewBosonType = " << ewBosonType << std::endl;
    std::cout << "##### Parameters - END #####" << std::endl;

    // Set up the ROOT TFile and TTree.
    TFile* eventFile = TFile::Open(eventFileName.c_str(),"READ");
    Pythia8::Event* eventAll = 0;

    std::string evtTreePath = "evt";
    TTree* treeEvt = (TTree*)eventFile->Get(evtTreePath.c_str());
    treeEvt->SetBranchAddress("event", &eventAll);

    Pythia8::Event* eventParton = 0;
    std::string evtPartonTreePath = "evtParton";
    TTree* treeEvtParton = (TTree*)eventFile->Get(evtPartonTreePath.c_str());
    treeEvtParton->SetBranchAddress("event", &eventParton);

    Pythia8::Info *info = 0;
    TTree* treeEvtInfo = (TTree*)eventFile->Get("evtInfo");
    treeEvtInfo->SetBranchAddress("info", &info);

    Pythia8::Event* event = eventAll;
    Pythia8::Event* eventParticle = eventAll;

    TFile *jetFile = TFile::Open(jetFileName.c_str(),"READ");
    fastJetTree fjt;
    TTree *jetTree = (TTree*)jetFile->Get(jetTreeName.c_str());
    fjt.setupTreeForReading(jetTree);

    std::string akStr = "ak";
    std::string jetStr = "jets";
    int jetStrPos = jetTreeName.find(jetStr.c_str());
    std::string jetRStr = jetTreeName.substr(akStr.size(), jetStrPos - akStr.size());
    double jetR = std::atof(jetRStr.c_str()) / 10;
    double jetR2 = jetR * jetR;

    std::cout << "##### Parameters (cont'd.) #####" << std::endl;
    std::cout << "jetR = " << jetR << std::endl;
    std::cout << "##### Parameters (cont'd.) - END #####" << std::endl;


    std::cout << "initialize the Pythia class to obtain info that is not accessible through event TTree." << std::endl;
    std::cout << "##### Pythia initialize #####" << std::endl;
    Pythia8::Pythia pythia;
    std::cout << "##### Pythia initialize - END #####" << std::endl;

    TFile* outputFile = new TFile(outputFileName.c_str(), "RECREATE");

    TH1::SetDefaultSumw2();

    enum ANALYSISTYPES {
        k_vJet,
        k_leadJet,
        k_dijet,
        k_inclusiveJet,
        kN_ANALYSISTYPES
    };

    enum PROCESSTYPES {
        kQCD_all = 0,
        kQCD_x2qg = 1001,  // codes = 113
        kQCD_x2gg = 1002,  // codes = 111, 115
        kQCD_x2qq = 1003,  // codes = 112, 114, 116, 121, 122, 123, 124
        kQCD_gg2gg = 111,
        kQCD_gg2qqbar = 112,
        kQCD_qg2qg = 113,
        kQCD_qq2qq = 114,
        kQCD_qqbar2gg = 115,
        kQCD_qqbar2qqbarNew = 116,
        kN_PROCESSTYPES
    };

    enum EWBOSONTYPES {
        kHardPhoton,
        kOutgoingHardPhoton,
        kOutgoingMaxPhoton,
        kOutgoingMaxPhotonIso,
        kHardZ,
        kOutgoingHardZ,
        kOutgoingZll,
        kN_EWBOSONTYPES
    };

    bool vIsPho = (ewBosonType == kHardPhoton ||
                   ewBosonType == kOutgoingHardPhoton ||
                   ewBosonType == kOutgoingMaxPhoton ||
                   ewBosonType == kOutgoingMaxPhotonIso);
    bool vIsZ = (ewBosonType == kHardZ ||
                 ewBosonType == kOutgoingHardZ ||
                 ewBosonType == kOutgoingZll);
    bool doVectorBoson = (vIsPho || vIsZ);

    // EW boson histograms
    int nBinsX_pt = 40;
    double axis_pt_min = 0;
    double axis_pt_max = 200+axis_pt_min;
    int nBinsX_eta = 20;
    double axis_eta_min = 0;
    double axis_eta_max = 5;
    int nBinsX_phi = 20;
    int nBinsX_Xjv = 16;
    double axis_Xjv_min = 0;
    double axis_Xjv_max = 2;

    // jet histograms
    int nBinsX_jetPt = 36;
    double axis_jetPt_min = 30;
    double axis_jetPt_max = 180+axis_jetPt_min;

    int nBinsX_ratio_pt = 50;
    double axis_ratio_pt_min = 0;
    double axis_ratio_pt_max = 2;

    std::string strV = "V";
    if (vIsPho) {
        strV = "#gamma";
    }
    else if (vIsZ) {
        strV = "Z";
    }
    std::string strVPt = Form("p_{T}^{%s}", strV.c_str());
    std::string strVEta = Form("#eta^{%s}", strV.c_str());
    std::string strVPhi = Form("#phi^{%s}", strV.c_str());

    TH1D* h_vPt = new TH1D("h_vPt",Form(";%s;", strVPt.c_str()), nBinsX_pt, axis_pt_min, axis_pt_max);
    TH1D* h_vEta = new TH1D("h_vEta",Form(";|%s|;", strVEta.c_str()), nBinsX_eta, axis_eta_min, axis_eta_max);
    TH2D* h2_vEta_vPt = new TH2D("h2_vEta_vPt",Form(";|%s|;%s", strVEta.c_str(), strVPt.c_str()),
            nBinsX_eta, axis_eta_min, axis_eta_max, nBinsX_pt, axis_pt_min, axis_pt_max);

    // event info
    TH2D* h2_qscale_vPt = new TH2D("h2_qscale_vPt", Form(";%s;Q", strVPt.c_str()), nBinsX_pt, axis_pt_min, axis_pt_max, nBinsX_pt, axis_pt_min, axis_pt_max);
    TH2D* h2_qscale_vEta = new TH2D("h2_qscale_vEta", Form(";|%s|;Q", strVEta.c_str()), nBinsX_eta, axis_eta_min, axis_eta_max, nBinsX_pt, axis_pt_min, axis_pt_max);

    enum JETFLAVORS {
        kInclusive,
        kQuark,
        kGluon,
        kN_JETFLAVORS
    };
    std::string jetFlavorsStr[kN_JETFLAVORS] = {"jet", "qjet", "gjet"};
    std::string jetFlavorsLabel[kN_JETFLAVORS] = {"jet", "q-jet", "g-jet"};

    std::string partonFlavorsStr[kN_JETFLAVORS] = {"qg", "q", "g"};
    std::string partonFlavorsLabel[kN_JETFLAVORS] = {"parton", "quark", "gluon"};

    enum PARTICLETYPES {
        kFinal,
        kFinalCh,
        kParton,
        kPartonHard,
        kN_PARTICLETYPES
    };
    std::string particleTypesStr[kN_PARTICLETYPES] = {"final", "finalCh", "parton", "partonHard"};
    std::string particleTypesLabel[kN_PARTICLETYPES] = {"final^{0,#pm}", "final^{#pm}", "q/g", "q/g"};

    enum PTSORTING {
        kPt1st,
        kPt2nd,
        kPt3rd,
        kPt4thPlus,
        kN_PTSORTING
    };
    std::string ptSortingsStr[kN_PTSORTING] = {"pt1st", "pt2nd", "pt3rd", "pt4thplus"};
    std::string ptSortingsLabel[kN_PTSORTING] = {"p_{T}^{lead}", "p_{T}^{sublead}", "p_{T}^{3rd}", "p_{T}^{4th +}"};

    enum FFDEFNS {
        kxijet,
        kxiV,
        kN_FFDEFNS
    };
    std::string ffDefnsStr[kN_FFDEFNS] = {"xijet", "xiV"};
    std::string ffDefnsLabel[kN_FFDEFNS] = {"#xi^{jet}", Form("#xi^{%s}_{T}", strV.c_str())};

    int nBinsX_xijet = 10;
    double axis_xijet_min = 0;
    double axis_xijet_max = 5;

    double axis_js_min = 0;
    double axis_js_max = 0.6;
    int nBinsX_js = round(axis_js_max / 0.05);

    // EW boson histograms
    TH1D* h_vPt_jet[kN_JETFLAVORS];
    // jet histograms
    TH1D* h_jetPt[kN_JETFLAVORS];
    TH1D* h_jetPt_qgFrac[kN_JETFLAVORS];
    TH1D* h_jetEta[kN_JETFLAVORS];
    TH2D* h2_jetEta_jetPt[kN_JETFLAVORS];
    TH1D* h_partonPt[kN_JETFLAVORS];
    TH1D* h_partonPt_qgFrac[kN_JETFLAVORS];
    TH2D* h2_jetPt_vs_jetPtPartonPtRatio[kN_JETFLAVORS];
    TH1D* h_jetPt_vs_jetPtPartonPtRatioMean[kN_JETFLAVORS];
    TH2D* h2_partonPt_vs_jetPtPartonPtRatio[kN_JETFLAVORS];
    TH1D* h_partonPt_vs_jetPtPartonPtRatioMean[kN_JETFLAVORS];
    TH2D* h2_partonOutPt_vs_jetPtPartonPtRatio[kN_JETFLAVORS];
    TH1D* h_partonOutPt_vs_jetPtPartonPtRatioMean[kN_JETFLAVORS];
    // subleading jet histograms
    TH1D* h_jet2Pt[kN_JETFLAVORS];
    TH1D* h_jet2Pt_qgFrac[kN_JETFLAVORS];       // qg-fraction of subleading jet as fnc of pt
    TH1D* h_jet2Eta[kN_JETFLAVORS];
    TH2D* h2_jet2Eta_jet2Pt[kN_JETFLAVORS];
    TH1D* h_jetPt_qgJ2[kN_JETFLAVORS];         // leading jet pt filled for a given flavor of subleading jet
    TH1D* h_jetPt_qgJ2Frac[kN_JETFLAVORS];     // qg-fraction of subleading jet as fnc of leading jet pt
    //
    TH2D* h2_Xj_vPt[kN_JETFLAVORS];
    TH2D* h2_Xj_vEta[kN_JETFLAVORS];
    TH2D* h2_Xj_detajV[kN_JETFLAVORS];
    TH2D* h2_Xj_dphijV[kN_JETFLAVORS];
    // V-jet histograms
    TH1D* h_detajV[kN_JETFLAVORS];
    TH1D* h_dphijV[kN_JETFLAVORS];
    TH1D* h_Xj[kN_JETFLAVORS];
    TH1D* h_NjV[kN_JETFLAVORS];
    TH2D* h2_vEta_jetEta[kN_JETFLAVORS];
    TH2D* h2_vPhi_jetPhi[kN_JETFLAVORS];
    TH2D* h2_qscale_detajV[kN_JETFLAVORS];
    // EW boson histograms split for parton types
    TH1D* h_vPt_qgFrac[kN_JETFLAVORS];
    // jet fragmentation function (FF) and jet shape (JS) histograms split by particle types
    TH1D* h_ff[kN_JETFLAVORS][kN_PARTICLETYPES][kN_FFDEFNS];
    TH1D* h_js[kN_JETFLAVORS][kN_PARTICLETYPES];
    TH1D* h_js_normJet[kN_JETFLAVORS][kN_PARTICLETYPES];
    TH1D* h_partID[kN_JETFLAVORS][kN_PARTICLETYPES];
    TH1D* h_ff_ptSort[kN_JETFLAVORS][kN_PARTICLETYPES][kN_FFDEFNS][kN_PTSORTING];
    TH1D* h_ff_ptSort_daughter[kN_JETFLAVORS][kN_PARTICLETYPES][kN_FFDEFNS][kN_PTSORTING];
    TH1D* h_js_ptSort[kN_JETFLAVORS][kN_PARTICLETYPES][kN_PTSORTING];
    TH1D* h_js_ptSort_normJet[kN_JETFLAVORS][kN_PARTICLETYPES][kN_PTSORTING];
    TH1D* h_js_ptSort_daughter[kN_JETFLAVORS][kN_PARTICLETYPES][kN_PTSORTING];
    TH1D* h_js_ptSort_daughter_normJet[kN_JETFLAVORS][kN_PARTICLETYPES][kN_PTSORTING];
    // particle-jet correlations
    TH1D* h_dphij_particle[kN_JETFLAVORS][kN_PARTICLETYPES];
    TH1D* h_detaj_particle[kN_JETFLAVORS][kN_PARTICLETYPES];
    for (int i = 0; i < kN_JETFLAVORS; ++i) {

        std::string lblJetPt = Form("p_{T}^{%s}", jetFlavorsLabel[i].c_str());
        std::string lblJetEta = Form("#eta^{%s}", jetFlavorsLabel[i].c_str());
        std::string lblJetPhi = Form("#phi^{%s}", jetFlavorsLabel[i].c_str());

        std::string lblJetPtPartonPtRatio = "p_{T}^{jet} / p_{T}^{parton}";
        std::string lblPartonPt = Form("p_{T}^{%s}", partonFlavorsLabel[i].c_str());
        std::string lblPartonOutPt = Form("p_{T}^{outgoing %s}", partonFlavorsLabel[i].c_str());

        std::string lblJet2Pt = Form("p_{T}^{sublead %s}", jetFlavorsLabel[i].c_str());
        std::string lblJet2Eta = Form("#eta^{sublead %s}", jetFlavorsLabel[i].c_str());

        std::string lblXjV = Form("x_{%s%s} = %s/%s", jetFlavorsLabel[i].c_str(), strV.c_str(), lblJetPt.c_str(), strVPt.c_str());
        std::string lblDetajV = Form("#Delta#eta_{%s%s} = |%s - %s|",
                jetFlavorsLabel[i].c_str(), strV.c_str(), lblJetEta.c_str(), strVEta.c_str());
        std::string lblDphijV = Form("#Delta#phi_{%s%s} = |%s - %s|",
                jetFlavorsLabel[i].c_str(), strV.c_str(), lblJetPhi.c_str(), strVPhi.c_str());

        h_vPt_jet[i] = new TH1D(Form("h_vPt_%s", jetFlavorsStr[i].c_str()),
                Form(";%s (recoil is %s);", strVPt.c_str(), jetFlavorsLabel[i].c_str()),
                nBinsX_pt, axis_pt_min, axis_pt_max);

        h_jetPt[i] = new TH1D(Form("h_%sPt", jetFlavorsStr[i].c_str()),
                Form(";%s;", lblJetPt.c_str()),
                nBinsX_jetPt, axis_jetPt_min, axis_jetPt_max);

        h_jetEta[i] = new TH1D(Form("h_%sEta", jetFlavorsStr[i].c_str()),
                Form(";|%s|;", lblJetEta.c_str()),
                nBinsX_eta, axis_eta_min, axis_eta_max);

        h2_jetEta_jetPt[i] = new TH2D(Form("h2_%sEta_%sPt", jetFlavorsStr[i].c_str(), jetFlavorsStr[i].c_str()),
                Form(";|%s|;%s", lblJetEta.c_str(), lblJetPt.c_str()),
                nBinsX_eta, axis_eta_min, axis_eta_max, nBinsX_jetPt, axis_jetPt_min, axis_jetPt_max);

        h_partonPt[i] = new TH1D(Form("h_%sPt", partonFlavorsStr[i].c_str()),
                Form(";%s;", lblPartonPt.c_str()),
                nBinsX_jetPt, axis_jetPt_min, axis_jetPt_max);

        h2_jetPt_vs_jetPtPartonPtRatio[i] = new TH2D(Form("h2_%sPt_vs_jetPtPartonPtRatio", jetFlavorsStr[i].c_str()),
                Form(";%s;%s", lblJetPt.c_str(), lblJetPtPartonPtRatio.c_str()),
                nBinsX_jetPt, axis_jetPt_min, axis_jetPt_max, nBinsX_ratio_pt, axis_ratio_pt_min, axis_ratio_pt_max);

        h2_partonPt_vs_jetPtPartonPtRatio[i] = new TH2D(Form("h2_%sPt_vs_jetPtPartonPtRatio", partonFlavorsStr[i].c_str()),
                Form(";%s;%s", lblPartonPt.c_str(), lblJetPtPartonPtRatio.c_str()),
                nBinsX_jetPt, axis_jetPt_min, axis_jetPt_max, nBinsX_ratio_pt, axis_ratio_pt_min, axis_ratio_pt_max);

        h2_partonOutPt_vs_jetPtPartonPtRatio[i] = new TH2D(Form("h2_%sOutPt_vs_jetPtPartonPtRatio", partonFlavorsStr[i].c_str()),
                Form(";%s;%s", lblPartonOutPt.c_str(), lblJetPtPartonPtRatio.c_str()),
                nBinsX_jetPt, axis_jetPt_min, axis_jetPt_max, nBinsX_ratio_pt, axis_ratio_pt_min, axis_ratio_pt_max);

        h_jet2Pt[i] = new TH1D(Form("h_%s2Pt", jetFlavorsStr[i].c_str()),
                Form(";%s;", lblJet2Pt.c_str()),
                nBinsX_jetPt, axis_jetPt_min, axis_jetPt_max);

        h_jet2Eta[i] = new TH1D(Form("h_%s2Eta", jetFlavorsStr[i].c_str()),
                Form(";|%s|;", lblJet2Eta.c_str()),
                nBinsX_eta, axis_eta_min, axis_eta_max);

        h2_jet2Eta_jet2Pt[i] = new TH2D(Form("h2_%s2Eta_%s2Pt", jetFlavorsStr[i].c_str(), jetFlavorsStr[i].c_str()),
                Form(";|%s|;%s", lblJet2Eta.c_str(), lblJet2Pt.c_str()),
                nBinsX_eta, axis_eta_min, axis_eta_max, nBinsX_jetPt, axis_jetPt_min, axis_jetPt_max);

        h_jetPt_qgJ2[i] = new TH1D(Form("h_jetPt_%sJ2", jetFlavorsStr[i].c_str()),
                ";p_{T}^{jet};",
                nBinsX_jetPt, axis_jetPt_min, axis_jetPt_max);

        h2_Xj_vPt[i] = new TH2D(Form("h2_X%s_vPt", jetFlavorsStr[i].c_str()),
                Form(";%s;%s", jetFlavorsLabel[i].c_str(), lblXjV.c_str(), strVPt.c_str()),
                nBinsX_Xjv, axis_Xjv_min, axis_Xjv_max, nBinsX_pt, axis_pt_min, axis_pt_max);

        h2_Xj_vEta[i] = new TH2D(Form("h2_X%s_vEta", jetFlavorsStr[i].c_str()),
                Form(";%s;|%s|", lblXjV.c_str(), strVEta.c_str()),
                nBinsX_Xjv, axis_Xjv_min, axis_Xjv_max, nBinsX_eta, axis_eta_min, axis_eta_max);

        h2_Xj_detajV[i] = new TH2D(Form("h2_X%s_deta%sV", jetFlavorsStr[i].c_str(), jetFlavorsStr[i].c_str()),
                Form(";%s;%s", lblXjV.c_str(), lblDetajV.c_str()),
                nBinsX_Xjv, axis_Xjv_min, axis_Xjv_max, nBinsX_eta, axis_eta_min, axis_eta_max);

        h2_Xj_dphijV[i] = new TH2D(Form("h2_X%s_dphi%sV", jetFlavorsStr[i].c_str(), jetFlavorsStr[i].c_str()),
                Form(";%s;%s", lblXjV.c_str(), lblDphijV.c_str()),
                nBinsX_Xjv, axis_Xjv_min, axis_Xjv_max, nBinsX_phi, 7 * TMath::Pi() / 8, TMath::Pi()+1e-12);

        h_detajV[i] = new TH1D(Form("h_deta%sV", jetFlavorsStr[i].c_str()),
                Form(";%s;", lblDetajV.c_str()),
                nBinsX_eta, axis_eta_min, 1.5*axis_eta_max);

        h_dphijV[i] = new TH1D(Form("h_dphi%sV", jetFlavorsStr[i].c_str()),
                Form(";%s;", lblDphijV.c_str()),
                nBinsX_phi, 0, TMath::Pi()+1e-12);

        h_Xj[i] = new TH1D(Form("h_X%s", jetFlavorsStr[i].c_str()),
                Form(";%s;", lblXjV.c_str()),
                nBinsX_Xjv, axis_Xjv_min, axis_Xjv_max);

        h_NjV[i] = new TH1D(Form("h_N%sV", jetFlavorsStr[i].c_str()),
                Form(";N^{%s};", jetFlavorsLabel[i].c_str()),
                10, 0, 10);

        h2_vEta_jetEta[i] = new TH2D(Form("h2_vEta_%sEta", jetFlavorsStr[i].c_str()),
                Form(";%s;%s", strVEta.c_str(), lblJetEta.c_str()),
                nBinsX_eta, -1*axis_eta_max, axis_eta_max, nBinsX_eta, -1*axis_eta_max, axis_eta_max);

        h2_vPhi_jetPhi[i] = new TH2D(Form("h2_vPhi_%sPhi", jetFlavorsStr[i].c_str()),
                Form(";%s;%s", strVPhi.c_str(), lblJetPhi.c_str()),
                nBinsX_phi, -TMath::Pi(), TMath::Pi(), nBinsX_phi, -TMath::Pi(), TMath::Pi());

        h2_qscale_detajV[i] = new TH2D(Form("h2_qscale_deta%sV", jetFlavorsStr[i].c_str()),
                Form(";%s;Q", lblDetajV.c_str()),
                nBinsX_eta, axis_eta_min, axis_eta_max, nBinsX_pt, axis_pt_min, axis_pt_max);

        h_vPt_qgFrac[i] = new TH1D(Form("h_vPt_%sFrac", jetFlavorsStr[i].c_str()),
                Form(";%s;", strVPt.c_str()),
                nBinsX_pt, axis_pt_min, axis_pt_max);

        for (int j = 0; j < kN_PARTICLETYPES; ++j) {

            for (int iFF = 0; iFF < kN_FFDEFNS; ++iFF) {

                std::string pVecStr = "#bf{p}^{jet}";
                std::string ptrkVecStr = Form("#bf{p}^{%s}", particleTypesLabel[j].c_str());
                std::string ffStr = Form("#xi^{jet} = ln (|%s|^{2} / %s #bf{#dot} %s)",
                                         pVecStr.c_str(), ptrkVecStr.c_str(), pVecStr.c_str());
                if (iFF == kxiV) {
                    pVecStr = Form("#bf{p}^{%s}_{T}", strV.c_str());
                    ptrkVecStr = Form("#bf{p}^{%s}_{T}", particleTypesLabel[j].c_str());
                    ffStr = Form("#xi^{%s}_{T} = ln ( -|%s|^{2} / %s #bf{#dot} %s)", strV.c_str(),
                            pVecStr.c_str(), ptrkVecStr.c_str(), pVecStr.c_str());
                }

                h_ff[i][j][iFF] = new TH1D(Form("h_%s_%s_%s", ffDefnsStr[iFF].c_str(), jetFlavorsStr[i].c_str(), particleTypesStr[j].c_str()),
                        Form("%s jet - particles are %s;%s;", jetFlavorsLabel[i].c_str(), particleTypesLabel[j].c_str(), ffStr.c_str()),
                        nBinsX_xijet, axis_xijet_min, axis_xijet_max);

                for (int k = 0; k < kN_PTSORTING; ++k) {

                    h_ff_ptSort[i][j][iFF][k] = new TH1D(Form("h_%s_%s_%s_%s",
                            ffDefnsStr[iFF].c_str(), jetFlavorsStr[i].c_str(), particleTypesStr[j].c_str(), ptSortingsStr[k].c_str()),
                            Form("%s jet - particles are %s, %s;%s;",
                            jetFlavorsLabel[i].c_str(), particleTypesLabel[j].c_str(), ptSortingsLabel[k].c_str(), ffStr.c_str()),
                            nBinsX_xijet, axis_xijet_min, axis_xijet_max);

                    if (j == kFinal || j == kFinalCh) {
                        h_ff_ptSort_daughter[i][j][iFF][k] = new TH1D(Form("h_%s_%s_%s_%s_daughter",
                                ffDefnsStr[iFF].c_str(), jetFlavorsStr[i].c_str(), particleTypesStr[j].c_str(), ptSortingsStr[k].c_str()),
                                Form("%s jet - particles are %s, %s;%s;",
                                jetFlavorsLabel[i].c_str(), particleTypesLabel[j].c_str(), ptSortingsLabel[k].c_str(), ffStr.c_str()),
                                nBinsX_xijet, axis_xijet_min, axis_xijet_max);
                    }
                }
            }


            h_js[i][j] = new TH1D(Form("h_js_%s_%s", jetFlavorsStr[i].c_str(), particleTypesStr[j].c_str()),
                                Form("%s jet - particles are %s;r;#rho(r)", jetFlavorsLabel[i].c_str(), particleTypesLabel[j].c_str()),
                                nBinsX_js, axis_js_min, axis_js_max);

            h_partID[i][j] = new TH1D(Form("h_partID_%s_%s", jetFlavorsStr[i].c_str(), particleTypesStr[j].c_str()),
                                            Form("%s jet - particles are %s;|PDG code|;", jetFlavorsLabel[i].c_str(), particleTypesLabel[j].c_str()),
                                            5000, 0, 5000);

            for (int k = 0; k < kN_PTSORTING; ++k) {

                h_js_ptSort[i][j][k] = new TH1D(Form("h_js_%s_%s_%s",
                        jetFlavorsStr[i].c_str(), particleTypesStr[j].c_str(), ptSortingsStr[k].c_str()),
                        Form("%s jet - particles are %s, %s;r;#rho(r)",
                        jetFlavorsLabel[i].c_str(), ptSortingsLabel[k].c_str(), particleTypesLabel[j].c_str()),
                        nBinsX_js, axis_js_min, axis_js_max);

                if (j == kFinal || j == kFinalCh) {
                    h_js_ptSort_daughter[i][j][k] = new TH1D(Form("h_js_%s_%s_%s_daughter",
                            jetFlavorsStr[i].c_str(), particleTypesStr[j].c_str(), ptSortingsStr[k].c_str()),
                            Form("%s jet - particles are %s, %s;r;#rho(r)",
                            jetFlavorsLabel[i].c_str(), ptSortingsLabel[k].c_str(), particleTypesLabel[j].c_str()),
                            nBinsX_js, axis_js_min, axis_js_max);
                }
            }

            h_dphij_particle[i][j] = new TH1D(Form("h_dphij_particle_%s_%s", jetFlavorsStr[i].c_str(), particleTypesStr[j].c_str()),
                                Form("%s jet - particles are %s;|#phi^{jet} - #phi^{%s}|;", jetFlavorsLabel[i].c_str(), particleTypesLabel[j].c_str(), particleTypesLabel[j].c_str()),
                                nBinsX_js*4, axis_js_min, axis_js_max);

            h_detaj_particle[i][j] = new TH1D(Form("h_detaj_particle_%s_%s", jetFlavorsStr[i].c_str(), particleTypesStr[j].c_str()),
                                Form("%s jet - particles are %s;|#eta^{jet} - #eta^{%s}|;", jetFlavorsLabel[i].c_str(), particleTypesLabel[j].c_str(), particleTypesLabel[j].c_str()),
                                nBinsX_js*4, axis_js_min, axis_js_max);
        }
    }

    // vJet cuts
    double minVPt = 60;
    double maxVEta = 1.44;
    double minDphijV = 7 * TMath::Pi() / 8;
    double minDR2jv = 0.8 * 0.8;
    double minVJetPt = axis_jetPt_min;
    double maxJetEta = 1.6;

    double minLeptonPt = 10;
    double maxLeptonEta = 2.4;

    // dijet cuts
    double minDphiDijet = 2 * TMath::Pi() / 3;
    double minLeadJetPt = 50;
    double minSubleadJetPt = axis_jetPt_min;

    // particle cuts
    double minPartPt = 1;
    double maxPartEta = 2.4;
    double max_dR_jet_particle = jetR;
    double max_dR2_jet_particle = max_dR_jet_particle * max_dR_jet_particle;

    int eventsAnalyzed = 0;
    int nEvents = treeEvt->GetEntries();
    int nEventsJets = jetTree->GetEntries();
    std::cout << "nEvents = " << nEvents << std::endl;
    std::cout << "nEventsJets = " << nEventsJets << std::endl;
    if (nEvents != nEventsJets) {
        std::cout << "nEvents and nEventsJets are not same." << std::endl;
        std::cout << "exiting." << std::endl;
        return;
    }
    std::cout << "Loop STARTED" << std::endl;
    for (int iEvent = 0; iEvent < nEvents; ++iEvent) {

        if (iEvent % 10000 == 0)  {
          std::cout << "current entry = " <<iEvent<<" out of "<<nEvents<<" : "<<std::setprecision(2)<<(double)iEvent/nEvents*100<<" %"<<std::endl;
        }

        treeEvt->GetEntry(iEvent);
        treeEvtParton->GetEntry(iEvent);
        treeEvtInfo->GetEntry(iEvent);
        jetTree->GetEntry(iEvent);

        if (processType == kQCD_all) {

        }
        else if (processType == kQCD_x2qg) {
            if (info->code() != kQCD_qg2qg) continue;
        }
        else if (processType == kQCD_x2gg) {
            if (info->code() != kQCD_gg2gg && info->code() != kQCD_qqbar2gg) continue;
        }
        else if (processType == kQCD_x2qq) {
            if (info->code() != kQCD_gg2qqbar &&
                info->code() != kQCD_qq2qq &&
                info->code() != kQCD_qqbar2qqbarNew &&
                !(info->code() >= 121 && info->code() <= 124)) continue;
        }
        else if (processType == kQCD_gg2gg ||
                 processType == kQCD_gg2qqbar ||
                 processType == kQCD_qg2qg ||
                 processType == kQCD_qq2qq ||
                 processType == kQCD_qqbar2gg ||
                 processType == kQCD_qqbar2qqbarNew) {

            if (info->code() != processType) continue;
        }
        else {
            continue;
        }

        // jet analysis
        // particles from hard scattering are at index 5 and 6
        int ip1 = 5;
        int ip2 = 6;
        int iHardV = -1;
        int iV = -1;

        double vPt = -1;
        double vEta = -999999;
        double vPhi = -999999;

        if (anaType == k_vJet) {
            if (vIsPho) {
                if ((isGamma((*event)[ip1])) && (isParton((*event)[ip2])))
                    iHardV = ip1;
                else if ((isGamma((*event)[ip2])) && (isParton((*event)[ip1])))
                    iHardV = ip2;
                if ((ewBosonType == kHardPhoton || ewBosonType == kOutgoingHardPhoton) && iHardV == -1) continue;
            }
            else if (vIsZ) {
                if ((isZboson((*event)[ip1])) && (isParton((*event)[ip2])))
                    iHardV = ip1;
                else if ((isZboson((*event)[ip2])) && (isParton((*event)[ip1])))
                    iHardV = ip2;
                if ((ewBosonType == kHardZ || ewBosonType == kOutgoingHardZ) && iHardV == -1) continue;
            }

            iV = iHardV;
            if (ewBosonType == kOutgoingHardPhoton || ewBosonType == kOutgoingHardZ) {
                int eventPartonSize = eventParton->size();
                // search the hard scattering photon in outgoing particles
                int iOutV = -1;
                int nOutVCand = 0;
                for (int i = 0; i < eventPartonSize; ++i) {

                    if (ewBosonType == kOutgoingHardPhoton) {
                        if (!isGamma((*eventParton)[i]))  continue;
                    }
                    else if (ewBosonType == kOutgoingHardZ) {
                        if (!isZboson((*eventParton)[i]))  continue;
                    }
                    int indexOrig = (*eventParton)[i].mother1();

                    if (hasDaughter((*event)[indexOrig]))  continue;

                    // must be a daughter of the hard scattering particle
                    if (!isAncestor(event, indexOrig, iHardV))  continue;

                    nOutVCand++;
                    iOutV = indexOrig;
                }
                // there must be exactly one outgoing, final photon
                if (iOutV == -1 || nOutVCand != 1)  continue;

                iV = iOutV;
            }
            else if (ewBosonType == kOutgoingMaxPhoton || ewBosonType == kOutgoingMaxPhotonIso) {
                int eventSize = event->size();
                // search the highest-pt photon in outgoing particles
                int iOutPho = -1;
                double maxPt = 0;
                for (int i = 0; i < eventSize; ++i) {

                    if (!((*event)[i].isFinal()))  continue;
                    if (!isGamma((*event)[i]))  continue;
                    if (hasDaughter((*event)[i]))  continue;

                    if ((*event)[i].pT() > maxPt) {
                        iOutPho = i;
                        maxPt = (*event)[i].pT();
                    }
                }
                if (iOutPho == -1)  continue;

                iV = iOutPho;
            }
            else if (ewBosonType == kOutgoingZll) {
                int eventSize = event->size();
                // search the ll pair whose mass is closest to Z mass in PDG
                double zMassPDG = 91.1876;
                double deltaMass = 999999;
                bool foundZ = false;

                for (int i = 0; i < eventSize; ++i) {

                    if (!((*event)[i].isFinal()))  continue;
                    if (!isChLepton((*event)[i]))  continue;
                    if (hasDaughter((*event)[i]))  continue;

                    if (!((*event)[i].pT() > minLeptonPt))  continue;
                    if (!(TMath::Abs((*event)[i].eta()) < maxLeptonEta))  continue;

                    for (int j = i+1; j < eventSize; ++j) {

                        // must be pairs of anti-particles
                        if (!((*event)[j].id() == -1*(*event)[i].id()))  continue;

                        if (!((*event)[j].isFinal()))  continue;
                        if (!isChLepton((*event)[j]))  continue;
                        if (hasDaughter((*event)[j]))  continue;

                        if (!((*event)[j].pT() > minLeptonPt))  continue;
                        if (!(TMath::Abs((*event)[j].eta()) < maxLeptonEta))  continue;

                        TLorentzVector vecL1;
                        TLorentzVector vecL2;

                        vecL1.SetPtEtaPhiM((*event)[i].pT(), (*event)[i].eta(), (*event)[i].phi(), (*event)[i].m0());
                        vecL2.SetPtEtaPhiM((*event)[j].pT(), (*event)[j].eta(), (*event)[j].phi(), (*event)[j].m0());

                        TLorentzVector vecL1L2 = vecL1 + vecL2;

                        if (!(vecL1L2.M() >= 60 && vecL1L2.M() <= 120))  continue;

                        if (TMath::Abs(vecL1L2.M() - zMassPDG) < deltaMass) {
                            foundZ = true;
                            deltaMass = TMath::Abs(vecL1L2.M() - zMassPDG);
                            vPt = vecL1L2.Pt();
                            vEta = vecL1L2.Eta();
                            vPhi = vecL1L2.Phi();
                        }
                    }
                }

                if (!foundZ)  continue;
            }

            if (ewBosonType != kOutgoingZll) {
                vPt = (*event)[iV].pT();
                vEta = (*event)[iV].eta();
                vPhi = (*event)[iV].phi();
            }
        }

        eventsAnalyzed++;

        TLorentzVector vecTPho;
        vecTPho.SetPtEtaPhiM(vPt, 0, vPhi, 0);

        int iParton = -1;
        int iPartonOut = -1;
        int iQG = -1;
        std::vector<int> typesQG;
        int nTypesQG = -1;

        double maxJetPt = -1;
        int iMaxJet = -1;

        double maxJet2Pt = -1;
        int iMaxJet2 = -1;
        int iPartonJ2 = -1;
        int iPartonJ2Out = -1;
        int iQGJet2 = -1;
        std::vector<int> typesQGJ2;
        int nTypesQGJ2 = -1;

        if (anaType == k_vJet) {

            if (vIsPho) {
                if (!(TMath::Abs(vEta) < maxVEta)) continue;
                if (ewBosonType == kOutgoingMaxPhotonIso) {
                    double isoCal = isolationEt(event, iV, 0.4, true, true);
                    if (!(isoCal < 5)) continue;
                }
            }
            else if (vIsZ) {
                if (!(TMath::Abs(vEta) < maxVEta)) continue;
            }

            h_vPt->Fill(vPt);
            if (!(vPt > minVPt)) continue;

            h_vEta->Fill(TMath::Abs(vEta));
            h2_vEta_vPt->Fill(TMath::Abs(vEta), vPt);
            h2_qscale_vPt->Fill(vPt, event->scale());
            h2_qscale_vEta->Fill(TMath::Abs(vEta), event->scale());

            iParton = (iHardV == ip1) ? ip2 : ip1;
            if (ewBosonType == kOutgoingMaxPhoton || ewBosonType == kOutgoingMaxPhotonIso || ewBosonType == kOutgoingZll) {
                // associated parton is the one that is farthest away in phi
                double dphiParton1 = std::acos(cos(vPhi - (*event)[ip1].phi()));
                double dphiParton2 = std::acos(cos(vPhi - (*event)[ip2].phi()));
                iParton = (dphiParton1 > dphiParton2) ? ip1 : ip2;
            }
            iPartonOut = getIndexLeadingOutDaughter(event, eventParton, iParton);
            iQG = (isQuark((*event)[iParton])) ? kQuark : kGluon;

            typesQG = {kInclusive, iQG};
            nTypesQG = typesQG.size();

            for (int j = 0; j < nTypesQG; ++j) {
                int k = typesQG[j];
                h_vPt_jet[k]->Fill(vPt);
            }
        }
        else if (anaType == k_leadJet || anaType == k_dijet) {

            maxJetPt = -1;
            iMaxJet = -1;

            for (int i = 0; i < fjt.nJet; ++i) {

                double jetpt = (*fjt.jetpt)[i];
                double jeteta = (*fjt.jeteta)[i];
                double jetphi = (*fjt.jetphi)[i];

                if (!(TMath::Abs(jeteta) < maxJetEta)) continue;

                if (jetpt > maxJetPt) {
                    maxJetPt = jetpt;
                    iMaxJet = i;
                }
            }

            // associated parton is the one that is closest in eta-phi
            double dR2parton1 = getDR2((*fjt.jeteta)[iMaxJet], (*fjt.jetphi)[iMaxJet], (*event)[ip1].eta(), (*event)[ip1].phi());
            double dR2parton2 = getDR2((*fjt.jeteta)[iMaxJet], (*fjt.jetphi)[iMaxJet], (*event)[ip2].eta(), (*event)[ip2].phi());
            iParton = (dR2parton1 < dR2parton2) ? ip1 : ip2;
            iPartonOut = getIndexLeadingOutDaughter(event, eventParton, iParton);

            if (isQuark((*event)[iParton])) {
                typesQG = {kInclusive, kQuark};
            }
            else if (isGluon((*event)[iParton])) {
                typesQG = {kInclusive, kGluon};
            }
            else {
                typesQG = {kInclusive};
            }
            nTypesQG = typesQG.size();

            if (anaType == k_dijet) {
                for (int i = 0; i < fjt.nJet; ++i) {

                    if (i == iMaxJet) continue;

                    double jetpt = (*fjt.jetpt)[i];
                    double jeteta = (*fjt.jeteta)[i];
                    double jetphi = (*fjt.jetphi)[i];

                    if (!(TMath::Abs(jeteta) < maxJetEta)) continue;

                    if (!(std::acos(cos(jetphi - (*fjt.jetphi)[iMaxJet])) > minDphiDijet)) continue;

                    if (jetpt > maxJet2Pt) {
                        maxJet2Pt = jetpt;
                        iMaxJet2 = i;
                    }
                }

                // associated parton is the one that is closest in eta-phi
                // It is not assumed that the parton associated to the subleading jet is the one that recoils from the one for leading jet
                // Subleading jet and leading jet having the same associated parton is not excluded.
                double dR2parton1 = getDR2((*fjt.jeteta)[iMaxJet2], (*fjt.jetphi)[iMaxJet2], (*event)[ip1].eta(), (*event)[ip1].phi());
                double dR2parton2 = getDR2((*fjt.jeteta)[iMaxJet2], (*fjt.jetphi)[iMaxJet2], (*event)[ip2].eta(), (*event)[ip2].phi());
                iPartonJ2 = (dR2parton1 < dR2parton2) ? ip1 : ip2;
                iPartonJ2Out = getIndexLeadingOutDaughter(event, eventParton, iPartonJ2);

                if (isQuark((*event)[iPartonJ2])) {
                    typesQGJ2 = {kInclusive, kQuark};
                }
                else if (isGluon((*event)[iPartonJ2])) {
                    typesQGJ2 = {kInclusive, kGluon};
                }
                else {
                    typesQGJ2 = {kInclusive};
                }
                nTypesQGJ2 = typesQGJ2.size();
            }
        }

        int njetaway = 0;
        for (int i = 0; i < fjt.nJet; ++i) {

            double jetpt = (*fjt.jetpt)[i];
            double jeteta = (*fjt.jeteta)[i];
            double jetphi = (*fjt.jetphi)[i];

            double detaj = -999999;
            double dphij = -999999;
            double xj = -1;

            if (anaType == k_vJet) {
                if (!(jetpt > minVJetPt))  continue;
                if (!(TMath::Abs(jeteta) < maxJetEta)) continue;
                if (getDR2(vEta, vPhi, jeteta, jetphi) < minDR2jv)  continue;

                detaj = TMath::Abs(vEta - jeteta);
                dphij = std::acos(cos(vPhi - jetphi));
                xj = jetpt / vPt;

                for (int j = 0; j < nTypesQG; ++j) {
                    int k = typesQG[j];
                    h_dphijV[k]->Fill(dphij);
                }

                if (!(dphij > minDphijV)) continue;
                njetaway++;
            }
            else if (anaType == k_leadJet) {
                if (i != iMaxJet) continue;
            }
            else if (anaType == k_dijet) {
                if (i != iMaxJet && i != iMaxJet2) continue;
            }
            else if (anaType == k_inclusiveJet) {
                if (!(jetpt > minVJetPt))  continue;
                if (!(TMath::Abs(jeteta) < maxJetEta)) continue;

                // associated parton is the one that is closest in eta-phi
                double dR2parton1 = getDR2(jeteta, jetphi, (*event)[ip1].eta(), (*event)[ip1].phi());
                double dR2parton2 = getDR2(jeteta, jetphi, (*event)[ip2].eta(), (*event)[ip2].phi());
                iParton = (dR2parton1 < dR2parton2) ? ip1 : ip2;
                iPartonOut = getIndexLeadingOutDaughter(event, eventParton, iParton);

                if (isQuark((*event)[iParton])) {
                    typesQG = {kInclusive, kQuark};
                }
                else if (isGluon((*event)[iParton])) {
                    typesQG = {kInclusive, kGluon};
                }
                else {
                    typesQG = {kInclusive};
                }
                nTypesQG = typesQG.size();
            }

            if (anaType == k_vJet ||
                    anaType == k_leadJet ||
                    anaType == k_inclusiveJet ||
                    (anaType == k_dijet && i == iMaxJet)) {

                for (int jQG = 0; jQG < nTypesQG; ++jQG) {

                    int k = typesQG[jQG];

                    h_jetPt[k]->Fill(jetpt);
                    h_jetEta[k]->Fill(TMath::Abs(jeteta));
                    h2_jetEta_jetPt[k]->Fill(TMath::Abs(jeteta), jetpt);

                    double partonPt = (*event)[iParton].pT();
                    double jetPtPartonPtRatio = jetpt / partonPt;
                    double partonOutPt = (*event)[iPartonOut].pT();

                    h_partonPt[k]->Fill(partonPt);
                    h2_jetPt_vs_jetPtPartonPtRatio[k]->Fill(jetpt, jetPtPartonPtRatio);
                    h2_partonPt_vs_jetPtPartonPtRatio[k]->Fill(partonPt, jetPtPartonPtRatio);
                    h2_partonOutPt_vs_jetPtPartonPtRatio[k]->Fill(partonOutPt, jetPtPartonPtRatio);

                    if (anaType == k_vJet) {
                        h2_Xj_vPt[k]->Fill(xj, vPt);
                        h2_Xj_vEta[k]->Fill(xj, vEta);
                        h2_Xj_detajV[k]->Fill(xj, detaj);
                        h2_Xj_dphijV[k]->Fill(xj, dphij);
                        h_detajV[k]->Fill(detaj);
                        h_Xj[k]->Fill(xj);
                        h2_vEta_jetEta[k]->Fill(vEta, jeteta);
                        h2_vPhi_jetPhi[k]->Fill(vPhi, jetphi);
                        h2_qscale_detajV[k]->Fill(detaj, event->scale());
                        h_vPt_qgFrac[k]->Fill(vPt);
                    }
                }
            }
            if (anaType == k_dijet && i == iMaxJet2) {

                for (int jQG = 0; jQG < nTypesQGJ2; ++jQG) {

                    int kJ2 = typesQGJ2[jQG];
                    h_jet2Pt[kJ2]->Fill(jetpt);
                    h_jet2Eta[kJ2]->Fill(TMath::Abs(jeteta));
                    h2_jet2Eta_jet2Pt[kJ2]->Fill(TMath::Abs(jeteta), jetpt);

                    h_jetPt_qgJ2[kJ2]->Fill(maxJetPt);

                    if (!(jetpt > minSubleadJetPt))  continue;
                    if (!(maxJetPt > minLeadJetPt))  continue;

                    double maxJetPhi = (*fjt.jetphi)[iMaxJet];

                    detaj = TMath::Abs(maxJetEta - jeteta);
                    dphij = std::acos(cos(maxJetPhi - jetphi));
                    xj = jetpt / maxJetPt;

                    h_detajV[kJ2]->Fill(detaj);
                    h_dphijV[kJ2]->Fill(dphij);
                    h_Xj[kJ2]->Fill(xj);
                }
            }

            TLorentzVector vecJet;
            vecJet.SetPtEtaPhiM(jetpt, jeteta, jetphi, 0);
            for (int iPartType = 0; iPartType < kN_PARTICLETYPES; ++iPartType) {

                eventParticle = eventAll;
                if (iPartType == PARTICLETYPES::kParton || iPartType == PARTICLETYPES::kPartonHard) {
                    eventParticle = eventParton;
                }

                std::vector<std::pair<double, int>> pairs_pt_index_ff;
                std::vector<std::pair<double, int>> pairs_pt_index_js;

                int eventParticleSize = eventParticle->size();
                for (int j = 0; j < eventParticleSize; ++j) {

                    if (iPartType == PARTICLETYPES::kFinal) {
                        if (!((*eventParticle)[j].isFinal())) continue;
                    }
                    else if (iPartType == PARTICLETYPES::kFinalCh) {
                        if (!((*eventParticle)[j].isFinal() && isCharged((*eventParticle)[j], pythia.particleData))) continue;
                    }
                    else if (iPartType == PARTICLETYPES::kPartonHard) {
                        int iOrig = (*eventParticle)[j].mother1();
                        if (!(isAncestor(eventAll, iOrig, 5) || isAncestor(eventAll, iOrig, 6))) continue;
                    }

                    if (!((*eventParticle)[j].pT() > minPartPt)) continue;
                    if (!(TMath::Abs((*eventParticle)[j].eta()) < maxPartEta))  continue;

                    double partPt = (*eventParticle)[j].pT();
                    double partEta = (*eventParticle)[j].eta();
                    double partPhi = (*eventParticle)[j].phi();

                    double dR_jet_particle = getDR(jeteta, jetphi, partEta, partPhi);
                    for (int jQG = 0; jQG < nTypesQG; ++jQG) {
                        int k = typesQG[jQG];
                        h_js[k][iPartType]->Fill(dR_jet_particle, partPt / jetpt);

                        h_dphij_particle[k][iPartType]->Fill(TMath::Abs(getDPHI(jetphi, partPhi)));
                        h_detaj_particle[k][iPartType]->Fill(TMath::Abs(getDETA(jeteta, partEta)));
                    }
                    if (dR_jet_particle < max_dR_jet_particle) {
                        // consider only pairs inside jet cone
                        pairs_pt_index_js.push_back(std::make_pair(partPt, j));
                    }
                    else {
                        continue;
                    }

                    for (int iFF = 0; iFF < kN_FFDEFNS; ++iFF) {

                        if (iFF == kxiV && anaType != k_vJet) continue;

                        double z = 0;
                        TLorentzVector vecPart;
                        if (iFF == kxijet) {
                            vecPart.SetPtEtaPhiM(partPt, partEta, partPhi, 0);
                            double angle = vecJet.Angle(vecPart.Vect());
                            z = vecPart.P() * cos(angle) / vecJet.P();
                        }
                        else if (iFF == kxiV) {
                            vecPart.SetPtEtaPhiM(partPt, 0, partPhi, 0);
                            double angle = vecTPho.Angle(vecPart.Vect());
                            z = partPt * fabs(cos(angle)) / vPt;
                        }
                        double xi = log(1.0/z);

                        for (int jQG = 0; jQG < nTypesQG; ++jQG) {
                            int k = typesQG[jQG];

                            h_ff[k][iPartType][iFF]->Fill(xi);

                            if (iFF == 0) {
                                h_partID[k][iPartType]->Fill(TMath::Abs((*eventParticle)[j].id()));
                            }
                        }
                    }
                    pairs_pt_index_ff.push_back(std::make_pair(partPt, j));
                }

                std::vector<int> usedDaughterIndices_ff[kN_PARTICLETYPES];
                std::vector<int> usedDaughterIndices_js[kN_PARTICLETYPES];

                int nPairs = -1;
                // pt sorted jet shape
                std::sort(pairs_pt_index_js.begin(), pairs_pt_index_js.end());
                nPairs = pairs_pt_index_js.size();
                for (int jPair = 0; jPair < nPairs; ++jPair) {

                    int j = pairs_pt_index_js[jPair].second;

                    double partPt = (*eventParticle)[j].pT();
                    double partEta = (*eventParticle)[j].eta();
                    double partPhi = (*eventParticle)[j].phi();

                    double dR_jet_particle = getDR(jeteta, jetphi, partEta, partPhi);

                    for (int jQG = 0; jQG < nTypesQG; ++jQG) {
                        int k = typesQG[jQG];

                        if (jPair == nPairs - 1) {
                            h_js_ptSort[k][iPartType][kPt1st]->Fill(dR_jet_particle, partPt / jetpt);
                        }
                        else if (jPair == nPairs - 2) {
                            h_js_ptSort[k][iPartType][kPt2nd]->Fill(dR_jet_particle, partPt / jetpt);
                        }
                        else if (jPair == nPairs - 3) {
                            h_js_ptSort[k][iPartType][kPt3rd]->Fill(dR_jet_particle, partPt / jetpt);
                        }
                        else {
                            h_js_ptSort[k][iPartType][kPt4thPlus]->Fill(dR_jet_particle, partPt / jetpt);
                        }
                    }

                    if (iPartType == kParton) {
                        int iOrig = (*eventParticle)[j].mother1();

                        std::vector<int> daughters = daughterListRecursive(eventAll, iOrig);
                        int nDaughters = daughters.size();

                        for (int jChild = 0; jChild < nDaughters; ++jChild) {

                            int iChild = daughters[jChild];

                            std::vector<int> childTypes = {PARTICLETYPES::kFinal, PARTICLETYPES::kFinalCh};
                            int nChildTypes = childTypes.size();

                            for (int childType = 0; childType < nChildTypes; ++childType) {

                                if (childType == PARTICLETYPES::kFinal) {
                                    if (!((*eventAll)[iChild].isFinal())) continue;
                                }
                                else if (childType == PARTICLETYPES::kFinalCh) {
                                    if (!((*eventAll)[iChild].isFinal() && isCharged((*eventAll)[iChild], pythia.particleData))) continue;
                                }

                                if (!((*eventAll)[iChild].pT() > minPartPt)) continue;
                                if (!(TMath::Abs((*eventAll)[iChild].eta()) < maxPartEta))  continue;

                                double childPt = (*eventAll)[iChild].pT();
                                double childEta = (*eventAll)[iChild].eta();
                                double childPhi = (*eventAll)[iChild].phi();

                                double dR_jet_child = getDR(jeteta, jetphi, childEta, childPhi);

                                // One final particle can be daughter of multiple partons. Use a particle only once.
                                // Priority is given to mother parton with lower pt.
                                if (std::find(usedDaughterIndices_js[childType].begin(), usedDaughterIndices_js[childType].end(), iChild) != usedDaughterIndices_js[childType].end()) continue;
                                usedDaughterIndices_js[childType].push_back(iChild);

                                for (int jQG = 0; jQG < nTypesQG; ++jQG) {
                                    int k = typesQG[jQG];

                                    if (jPair == nPairs - 1) {
                                        h_js_ptSort_daughter[k][childType][kPt1st]->Fill(dR_jet_child, childPt / jetpt);
                                    }
                                    else if (jPair == nPairs - 2) {
                                        h_js_ptSort_daughter[k][childType][kPt2nd]->Fill(dR_jet_child, childPt / jetpt);
                                    }
                                    else if (jPair == nPairs - 3) {
                                        h_js_ptSort_daughter[k][childType][kPt3rd]->Fill(dR_jet_child, childPt / jetpt);
                                    }
                                    else {
                                        h_js_ptSort_daughter[k][childType][kPt4thPlus]->Fill(dR_jet_child, childPt / jetpt);
                                    }
                                }
                            }
                        }
                    }
                }

                // pt sorted FF
                std::sort(pairs_pt_index_ff.begin(), pairs_pt_index_ff.end());
                nPairs = pairs_pt_index_ff.size();
                for (int jPair = 0; jPair < nPairs; ++jPair) {

                    int j = pairs_pt_index_ff[jPair].second;

                    double partPt = (*eventParticle)[j].pT();
                    double partEta = (*eventParticle)[j].eta();
                    double partPhi = (*eventParticle)[j].phi();

                    for (int iFF = 0; iFF < kN_FFDEFNS; ++iFF) {

                        if (iFF == kxiV && anaType != k_vJet) continue;

                        double z = 0;
                        TLorentzVector vecPart;
                        if (iFF == kxijet) {
                            vecPart.SetPtEtaPhiM(partPt, partEta, partPhi, 0);
                            double angle = vecJet.Angle(vecPart.Vect());
                            z = vecPart.P() * cos(angle) / vecJet.P();
                        }
                        else if (iFF == kxiV) {
                            vecPart.SetPtEtaPhiM(partPt, 0, partPhi, 0);
                            double angle = vecTPho.Angle(vecPart.Vect());
                            z = partPt * fabs(cos(angle)) / vPt;
                        }
                        double xi = log(1.0/z);

                        for (int jQG = 0; jQG < nTypesQG; ++jQG) {
                            int k = typesQG[jQG];

                            if (jPair == nPairs - 1) {
                                h_ff_ptSort[k][iPartType][iFF][kPt1st]->Fill(xi);
                            }
                            else if (jPair == nPairs - 2) {
                                h_ff_ptSort[k][iPartType][iFF][kPt2nd]->Fill(xi);
                            }
                            else if (jPair == nPairs - 3) {
                                h_ff_ptSort[k][iPartType][iFF][kPt3rd]->Fill(xi);
                            }
                            else {
                                h_ff_ptSort[k][iPartType][iFF][kPt4thPlus]->Fill(xi);
                            }
                        }
                    }

                    if (iPartType == kParton) {
                        int iOrig = (*eventParticle)[j].mother1();

                        std::vector<int> daughters = daughterListRecursive(eventAll, iOrig);
                        int nDaughters = daughters.size();

                        for (int jChild = 0; jChild < nDaughters; ++jChild) {

                            int iChild = daughters[jChild];

                            std::vector<int> childTypes = {PARTICLETYPES::kFinal, PARTICLETYPES::kFinalCh};
                            int nChildTypes = childTypes.size();

                            for (int childType = 0; childType < nChildTypes; ++childType) {

                                if (childType == PARTICLETYPES::kFinal) {
                                    if (!((*eventAll)[iChild].isFinal())) continue;
                                }
                                else if (childType == PARTICLETYPES::kFinalCh) {
                                    if (!((*eventAll)[iChild].isFinal() && isCharged((*eventAll)[iChild], pythia.particleData))) continue;
                                }

                                if (!((*eventAll)[iChild].pT() > minPartPt)) continue;
                                if (!(TMath::Abs((*eventAll)[iChild].eta()) < maxPartEta))  continue;

                                double childPt = (*eventAll)[iChild].pT();
                                double childEta = (*eventAll)[iChild].eta();
                                double childPhi = (*eventAll)[iChild].phi();

                                double dR_jet_child = getDR(jeteta, jetphi, childEta, childPhi);
                                if (!(dR_jet_child < max_dR_jet_particle))  continue;

                                // One final particle can be daughter of multiple partons. Use a particle only once.
                                // Priority is given to mother parton with lower pt.
                                if (std::find(usedDaughterIndices_ff[childType].begin(), usedDaughterIndices_ff[childType].end(), iChild) != usedDaughterIndices_ff[childType].end()) continue;
                                usedDaughterIndices_ff[childType].push_back(iChild);

                                for (int iFF = 0; iFF < kN_FFDEFNS; ++iFF) {

                                    if (iFF == kxiV && anaType != k_vJet) continue;

                                    double z = 0;
                                    TLorentzVector vecPart;
                                    if (iFF == kxijet) {
                                        vecPart.SetPtEtaPhiM(childPt, childEta, childPhi, 0);
                                        double angle = vecJet.Angle(vecPart.Vect());
                                        z = vecPart.P() * cos(angle) / vecJet.P();
                                    }
                                    else if (iFF == kxiV) {
                                        vecPart.SetPtEtaPhiM(childPt, 0, childPhi, 0);
                                        double angle = vecTPho.Angle(vecPart.Vect());
                                        z = childPt * fabs(cos(angle)) / vPt;
                                    }
                                    double xi = log(1.0/z);

                                    for (int jQG = 0; jQG < nTypesQG; ++jQG) {
                                        int k = typesQG[jQG];

                                        if (jPair == nPairs - 1) {
                                            h_ff_ptSort_daughter[k][childType][iFF][kPt1st]->Fill(xi);
                                        }
                                        else if (jPair == nPairs - 2) {
                                            h_ff_ptSort_daughter[k][childType][iFF][kPt2nd]->Fill(xi);
                                        }
                                        else if (jPair == nPairs - 3) {
                                            h_ff_ptSort_daughter[k][childType][iFF][kPt3rd]->Fill(xi);
                                        }
                                        else {
                                            h_ff_ptSort_daughter[k][childType][iFF][kPt4thPlus]->Fill(xi);
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }

        for (int jQG = 0; jQG < nTypesQG; ++jQG) {
            int k = typesQG[jQG];

            h_NjV[k]->Fill(njetaway);
        }
    }
    std::cout << "Loop ENDED" << std::endl;
    std::cout << "eventsAnalyzed = " << eventsAnalyzed << std::endl;
    std::cout << "Closing the event file" << std::endl;
    eventFile->Close();
    std::cout << "Closing the jet file" << std::endl;
    jetFile->Close();

    // Save histogram on file and close file.
    std::cout << "saving histograms" << std::endl;

    double binMinVPt = h_vPt->FindBin(minVPt);
    h_vPt->Scale(1./h_vPt->Integral(binMinVPt, h_vPt->GetNbinsX()+1), "width");
    h_vEta->Scale(1./h_vEta->Integral(), "width");

    for (int i = 0; i < kN_JETFLAVORS; ++i) {

        double nV = h_vPt_jet[i]->GetEntries();
        double nJet = h_jetPt[i]->GetEntries();

        h_jetPt_qgFrac[i] = (TH1D*)h_jetPt[i]->Clone(Form("h_%sPt_qgFrac", jetFlavorsStr[i].c_str()));
        h_jetPt_qgFrac[i]->SetYTitle("Fraction relative to quark+gluon");

        h_partonPt_qgFrac[i] = (TH1D*)h_partonPt[i]->Clone(Form("h_%sPt_qgFrac", partonFlavorsStr[i].c_str()));
        h_partonPt_qgFrac[i]->SetYTitle("Fraction relative to quark+gluon");

        if (i != kInclusive) {
            h_jetPt_qgFrac[i]->Divide(h_jetPt_qgFrac[kInclusive]);
            h_partonPt_qgFrac[i]->Divide(h_partonPt_qgFrac[kInclusive]);
        }

        double normJet = nJet;
        if (anaType == k_vJet) {

            h_vPt_jet[i]->Scale(1./nV, "width");

            normJet = nV;

            h_detajV[i]->Scale(1./normJet, "width");
            h_dphijV[i]->Scale(1./normJet, "width");
            h_Xj[i]->Scale(1./normJet, "width");
            h_NjV[i]->Scale(1./normJet, "width");
        }
        else if (anaType == k_dijet) {
            h_jet2Pt_qgFrac[i] = (TH1D*)h_jet2Pt[i]->Clone(Form("h_%s2Pt_qgFrac", jetFlavorsStr[i].c_str()));
            h_jet2Pt_qgFrac[i]->SetYTitle("Fraction relative to quark+gluon");

            h_jetPt_qgJ2Frac[i] = (TH1D*)h_jetPt_qgJ2[i]->Clone(Form("h_jetPt_%sJ2Frac", jetFlavorsStr[i].c_str()));
            h_jetPt_qgJ2Frac[i]->SetYTitle("Fraction of recoil jet relative to quark+gluon");

            if (i != kInclusive) {
                h_jet2Pt_qgFrac[i]->Divide(h_jet2Pt_qgFrac[kInclusive]);
                h_jetPt_qgJ2Frac[i]->Divide(h_jetPt_qgJ2Frac[kInclusive]);
            }

            h_detajV[i]->Scale(1./h_detajV[i]->Integral(), "width");
            h_dphijV[i]->Scale(1./h_dphijV[i]->Integral(), "width");
            h_Xj[i]->Scale(1./h_Xj[i]->Integral(), "width");
        }

        h_jetPt[i]->Scale(1./normJet, "width");
        h_jetEta[i]->Scale(1./normJet, "width");

        h_jet2Pt[i]->Scale(1./normJet, "width");
        h_jet2Eta[i]->Scale(1./normJet, "width");
        h_jetPt_qgJ2[i]->Scale(1./normJet, "width");

        std::string hNameTmp = "";
        int nBinsTmp = -1;

        hNameTmp = h2_jetPt_vs_jetPtPartonPtRatio[i]->GetName();
        hNameTmp = replaceAll(hNameTmp, "jetPtPartonPtRatio", "jetPtPartonPtRatioMean");
        hNameTmp = replaceAll(hNameTmp, "h2_", "h_");
        h_jetPt_vs_jetPtPartonPtRatioMean[i] = (TH1D*)h2_jetPt_vs_jetPtPartonPtRatio[i]->ProjectionX(hNameTmp.c_str());
        setBinsFromTH2sliceMean(h_jetPt_vs_jetPtPartonPtRatioMean[i], h2_jetPt_vs_jetPtPartonPtRatio[i]);

        hNameTmp = h2_partonPt_vs_jetPtPartonPtRatio[i]->GetName();
        hNameTmp = replaceAll(hNameTmp, "jetPtPartonPtRatio", "jetPtPartonPtRatioMean");
        hNameTmp = replaceAll(hNameTmp, "h2_", "h_");
        h_partonPt_vs_jetPtPartonPtRatioMean[i] = (TH1D*)h2_partonPt_vs_jetPtPartonPtRatio[i]->ProjectionX(hNameTmp.c_str());
        setBinsFromTH2sliceMean(h_partonPt_vs_jetPtPartonPtRatioMean[i], h2_partonPt_vs_jetPtPartonPtRatio[i]);

        hNameTmp = h2_partonOutPt_vs_jetPtPartonPtRatio[i]->GetName();
        hNameTmp = replaceAll(hNameTmp, "jetPtPartonPtRatio", "jetPtPartonPtRatioMean");
        hNameTmp = replaceAll(hNameTmp, "h2_", "h_");
        h_partonOutPt_vs_jetPtPartonPtRatioMean[i] = (TH1D*)h2_partonOutPt_vs_jetPtPartonPtRatio[i]->ProjectionX(hNameTmp.c_str());
        setBinsFromTH2sliceMean(h_partonOutPt_vs_jetPtPartonPtRatioMean[i], h2_partonOutPt_vs_jetPtPartonPtRatio[i]);

        for (int j = 0; j < kN_PARTICLETYPES; ++j) {

            for (int iFF = 0; iFF < kN_FFDEFNS; ++iFF) {

                if (iFF == kxiV && anaType != k_vJet) continue;

                h_ff[i][j][iFF]->Scale(1./nJet, "width");
                if (iFF == 0) {
                    h_partID[i][j]->Scale(1./nJet);
                }

                for (int k = 0; k < kN_PTSORTING; ++k) {
                    h_ff_ptSort[i][j][iFF][k]->Scale(1./nJet, "width");

                    if (j == kFinal || j == kFinalCh) {
                        h_ff_ptSort_daughter[i][j][iFF][k]->Scale(1./nJet, "width");
                    }
                }
            }

            h_js_normJet[i][j] = (TH1D*)h_js[i][j]->Clone(Form("%s_normJet", h_js[i][j]->GetName()));

            double intJetCone = h_js[i][j]->Integral(1, h_js[i][j]->FindBin(jetR)-1);
            h_js[i][j]->Scale(1./intJetCone, "width");
            h_js_normJet[i][j]->Scale(1./nJet, "width");

            for (int k = 0; k < kN_PTSORTING; ++k) {

                h_js_ptSort_normJet[i][j][k] = (TH1D*)h_js_ptSort[i][j][k]->Clone(
                        Form("%s_normJet", h_js_ptSort[i][j][k]->GetName()));

                h_js_ptSort[i][j][k]->Scale(1./intJetCone, "width");
                h_js_ptSort_normJet[i][j][k]->Scale(1./nJet, "width");

                if (j == kFinal || j == kFinalCh) {
                    h_js_ptSort_daughter_normJet[i][j][k] = (TH1D*)h_js_ptSort_daughter[i][j][k]->Clone(
                            Form("%s_normJet", h_js_ptSort_daughter[i][j][k]->GetName()));

                    h_js_ptSort_daughter[i][j][k]->Scale(1./intJetCone, "width");
                    h_js_ptSort_daughter_normJet[i][j][k]->Scale(1./nJet, "width");
                }
            }

            h_dphij_particle[i][j]->Scale(1./nJet, "width");
            h_detaj_particle[i][j]->Scale(1./nJet, "width");
        }

        if (anaType == k_vJet) {
            if (i != kInclusive) {
                h_vPt_qgFrac[i]->Divide(h_vPt_qgFrac[kInclusive]);
            }
        }
    }

    outputFile->Write("", TObject::kOverwrite);
    std::cout << "Closing the output file" << std::endl;
    outputFile->Close();

    std::cout << "running qcdAna() - END" << std::endl;
}

int main(int argc, char* argv[]) {

    if (argc == 8) {
        qcdAna(argv[1], argv[2], argv[3], argv[4], std::atoi(argv[5]), std::atoi(argv[6]), std::atoi(argv[7]));
        return 0;
    }
    else if (argc == 7) {
        qcdAna(argv[1], argv[2], argv[3], argv[4], std::atoi(argv[5]), std::atoi(argv[6]));
        return 0;
    }
    else if (argc == 6) {
        qcdAna(argv[1], argv[2], argv[3], argv[4], std::atoi(argv[5]));
        return 0;
    }
    else if (argc == 5) {
        qcdAna(argv[1], argv[2], argv[3], argv[4]);
        return 0;
    }
    else if (argc == 4) {
        qcdAna(argv[1], argv[2], argv[3]);
        return 0;
    }
    else if (argc == 3) {
        qcdAna(argv[1], argv[2]);
        return 0;
    }
    else if (argc == 2) {
        qcdAna(argv[1]);
        return 0;
    }
    else {
        std::cout << "Usage : \n" <<
                "./qcdAna.exe <eventFileName> <jetFileName> <jetTreeName> <outputFileName> <anaType> <processType> <ewBosonType>"
                << std::endl;
        return 1;
    }
}
