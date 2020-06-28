/*
 * code to analyze the two particles outgoing from hard process.
 * One hard scatterer is called "tag", the other is "probe".
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
#include "../../utilities/systemUtil.h"
#include "../../utilities/ArgumentParser.h"

#include <iostream>
#include <iomanip>
#include <string>
#include <vector>

std::vector<std::string> argOptions;

void hardScatteringAna(std::string inputFileName, std::string outputFileName = "hardScatteringAna_out.root");

void hardScatteringAna(std::string inputFileName, std::string outputFileName)
{
    std::cout << "running hardScatteringAna()" << std::endl;

    std::cout << "##### Parameters #####" << std::endl;
    std::cout << "inputFileName = " << inputFileName.c_str() << std::endl;
    std::cout << "outputFileName = " << outputFileName.c_str() << std::endl;
    std::cout << "##### Parameters - END #####" << std::endl;

    std::string tagParticle = (ArgumentParser::ParseOptionInputSingle("--tag", argOptions).size() > 0) ?
            ArgumentParser::ParseOptionInputSingle("--tag", argOptions).c_str() : "parton";

    int iStatusTag = (ArgumentParser::ParseOptionInputSingle("--tagStatus", argOptions).size() > 0) ?
            std::atoi(ArgumentParser::ParseOptionInputSingle("--tagStatus", argOptions).c_str()) : 0;

    int iStatusProbe = (ArgumentParser::ParseOptionInputSingle("--probeStatus", argOptions).size() > 0) ?
            std::atoi(ArgumentParser::ParseOptionInputSingle("--probeStatus", argOptions).c_str()) : 0;

    double tagMinPt = (ArgumentParser::ParseOptionInputSingle("--tagMinPt", argOptions).size() > 0) ?
            std::atof(ArgumentParser::ParseOptionInputSingle("--tagMinPt", argOptions).c_str()) : -1;

    double tagMaxEta = (ArgumentParser::ParseOptionInputSingle("--tagMaxEta", argOptions).size() > 0) ?
            std::atof(ArgumentParser::ParseOptionInputSingle("--tagMaxEta", argOptions).c_str()) : 999999;

    std::cout << "##### Optional Arguments #####" << std::endl;
    std::cout << "tagParticle = " << tagParticle.c_str() << std::endl;
    std::cout << "iStatusTag = " << iStatusTag << std::endl;
    std::cout << "iStatusProbe = " << iStatusProbe << std::endl;
    std::cout << "tagMinPt = " << tagMinPt << std::endl;
    std::cout << "tagMaxEta = " << tagMaxEta << std::endl;
    std::cout << "##### Optional Arguments - END #####" << std::endl;

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

    enum TAGS {
        kParton,
        kQuark,
        kGluon,
        kGamma,
        kLeadGamma,
        kZ0,
        kN_TAGS
    };
    std::string tagsStr[kN_TAGS] = {"parton", "quark", "gluon", "gamma", "leadgamma", "Z"};

    std::vector<std::string> tagsStrVec(std::begin(tagsStr), std::end(tagsStr));
    int tagCode = findPositionInVector(tagsStrVec, tagParticle);

    if (tagCode < 0 || tagCode >= kN_TAGS) {
        std::cout << "Tag : " << tagParticle.c_str() << " is not recognized as a valid tag. Exiting." << std::endl;
        return;
    }

    enum STATUSES {
        kHard,
        kOut,
        kN_STATUSES
    };
    std::string statusesStr[kN_STATUSES] = {"sHard", "sOut"};

    // histograms for "tag"
    // tag depends on process.
    // for dijet, tag is the leading parton
    // for V+jet, tag is the EW boson
    int nBinsX_pt = 40;
    double axis_pt_min = 0;
    double axis_pt_max = 200+axis_pt_min;
    int nBinsX_eta = 20;
    double axis_eta_min = 0;
    double axis_eta_max = 5;
    int nBinsX_phi = 20;
    int nBinsX_Xj = 16;
    double axis_Xj_min = 0;
    double axis_Xj_max = 2;

    int nBinsX_ratio_pt = 50;
    double axis_ratio_pt_min = 0;
    double axis_ratio_pt_max = 2;

    int nBinsX_diff_eta = 50;
    double axis_diff_eta_max = 0.5;
    double axis_diff_eta_min = -1*axis_diff_eta_max;
    int nBinsX_diff_phi = 50;
    double axis_diff_phi_max = 0.5;
    double axis_diff_phi_min = -1*axis_diff_phi_max;

    std::string strP1 = "particle";
    if (tagCode == TAGS::kParton) {
        strP1 = "q/g";
    }
    else if (tagCode == TAGS::kQuark) {
        strP1 = "q";
    }
    else if (tagCode == TAGS::kGluon) {
        strP1 = "g";
    }
    else if (tagCode == TAGS::kGamma || tagCode == TAGS::kLeadGamma) {
        strP1 = "#gamma";
    }
    else if (tagCode == TAGS::kZ0) {
        strP1 = "Z^{0}";
    }
    std::string strP1Pt = Form("p_{T}^{%s}", strP1.c_str());
    std::string strP1Eta = Form("#eta^{%s}", strP1.c_str());
    std::string strP1Phi = Form("#phi^{%s}", strP1.c_str());
    std::string strP1Y = Form("y^{%s}", strP1.c_str());

    TH1D* h_p1Pt = new TH1D("h_p1Pt", Form(";%s;", strP1Pt.c_str()),
                nBinsX_pt, axis_pt_min, axis_pt_max);
    TH1D* h_p1Eta = new TH1D("h_p1Eta", Form(";|%s|;", strP1Eta.c_str()),
                nBinsX_eta, axis_eta_min, axis_eta_max);
    TH1D* h_p1Y = new TH1D("h_p1Y", Form(";|%s|;", strP1Y.c_str()),
                nBinsX_eta, axis_eta_min, axis_eta_max);

    TH2D* h2_p1Eta_p1Pt = new TH2D("h2_p1Eta_p1Pt",
                Form(";|%s|;%s", strP1Eta.c_str(), strP1Pt.c_str()),
                nBinsX_eta, axis_eta_min, axis_eta_max, nBinsX_pt, axis_pt_min, axis_pt_max);
    TH2D* h2_p1Y_p1Pt = new TH2D("h2_p1Y_p1Pt",
                Form(";|%s|;%s", strP1Y.c_str(), strP1Pt.c_str()),
                nBinsX_eta, axis_eta_min, axis_eta_max, nBinsX_pt, axis_pt_min, axis_pt_max);

    // event info
    TH2D* h2_qscale_p1Pt = new TH2D("h2_qscale_p1Pt", Form(";p_{T}^{%s};Q", strP1.c_str()), nBinsX_pt, axis_pt_min, axis_pt_max, nBinsX_pt, axis_pt_min, axis_pt_max);
    TH2D* h2_qscale_p1Eta = new TH2D("h2_qscale_p1Eta", Form(";|#eta^{%s}|;Q", strP1.c_str()), nBinsX_eta, axis_eta_min, axis_eta_max, nBinsX_pt, axis_pt_min, axis_pt_max);

    // ratio / difference of outgoing photon and hard process photon pt / eta / phi
    TH2D* h2_pt_p1Pt_ratio_sOut_sHard = new TH2D("h2_pt_p1Pt_ratio_sOut_sHard",
            Form(";%s (hard process);%s (outgoing) / %s (hard process)", strP1Pt.c_str(), strP1Pt.c_str(), strP1Pt.c_str()),
            nBinsX_pt, axis_pt_min, axis_pt_max, nBinsX_ratio_pt, axis_ratio_pt_min, axis_ratio_pt_max);
    TH2D* h2_pt_p1Eta_diff_sOut_sHard = new TH2D("h2_pt_p1Eta_diff_sOut_sHard",
            Form(";%s (hard process);%s (outgoing) - %s (hard process)", strP1Pt.c_str(), strP1Eta.c_str(), strP1Eta.c_str()),
            nBinsX_pt, axis_pt_min, axis_pt_max, nBinsX_diff_eta, axis_diff_eta_min, axis_diff_eta_max);
    TH2D* h2_pt_p1Phi_diff_sOut_sHard = new TH2D("h2_pt_p1Phi_diff_sOut_sHard",
            Form(";%s (hard process);%s (outgoing) - %s (hard process)", strP1Pt.c_str(), strP1Phi.c_str(), strP1Phi.c_str()),
            nBinsX_pt, axis_pt_min, axis_pt_max, nBinsX_diff_phi, axis_diff_phi_min, axis_diff_phi_max);
    TH2D* h2_nMPI_p1Pt_ratio_sOut_sHard = new TH2D("h2_nMPI_p1Pt_ratio_sOut_sHard",
            Form(";nMPI;%s (outgoing) / %s (hard process)", strP1Pt.c_str(), strP1Pt.c_str(), strP1Pt.c_str()),
            25, 0, 25, nBinsX_ratio_pt, axis_ratio_pt_min, axis_ratio_pt_max);
    TH2D* h2_nISR_p1Pt_ratio_sOut_sHard = new TH2D("h2_nISR_p1Pt_ratio_sOut_sHard",
            Form(";nISR;%s (outgoing) / %s (hard process)", strP1Pt.c_str(), strP1Pt.c_str(), strP1Pt.c_str()),
            45, 0, 45, nBinsX_ratio_pt, axis_ratio_pt_min, axis_ratio_pt_max);
    TH2D* h2_nFSR_p1Pt_ratio_sOut_sHard = new TH2D("h2_nFSR_p1Pt_ratio_sOut_sHard",
            Form(";nFSR;%s (outgoing) / %s (hard process)", strP1Pt.c_str(), strP1Pt.c_str(), strP1Pt.c_str()),
            50, 0, 250, nBinsX_ratio_pt, axis_ratio_pt_min, axis_ratio_pt_max);

    enum PARTONTYPES {
        kQG,
        kQ,
        kG,
        kN_PARTONTYPES
    };
    std::string partonTypesStr[kN_PARTONTYPES] = {"parton", "q", "g"};
    std::string partonTypesLabel[kN_PARTONTYPES] = {"q/g", "q", "g"};

    // histograms for energy and multiplicity distribution of final partons as func. of angle with the initial tag
    // active only if tag is a parton
    TH1D* h_finalqg_p1_dR[kN_PARTONTYPES];
    TH1D* h_finalqg_p1_dR_wE[kN_PARTONTYPES];
    TH1D* h_finalqg_p1_dR_cdf[kN_PARTONTYPES];
    TH1D* h_finalqg_p1_dR_wE_cdf[kN_PARTONTYPES];
    for (int i = 0; i < kN_PARTONTYPES; ++i) {
        h_finalqg_p1_dR[i] = new TH1D(Form("h_final%s_p1_dR", partonTypesStr[i].c_str()),
                Form(";#DeltaR_{%s final %s};", strP1.c_str(), partonTypesLabel[i].c_str()), nBinsX_eta, 0, 1.5);

        h_finalqg_p1_dR_wE[i] = new TH1D(Form("h_final%s_p1_dR_wE", partonTypesStr[i].c_str()),
                Form(";#DeltaR_{%s final %s};", strP1.c_str(), partonTypesLabel[i].c_str()), nBinsX_eta, 0, 1.5);
    }

    // histograms for "probe"
    // probe depends on process.
    // for dijet, probe is the subleading parton
    // for V+jet, probe is the parton recoiling from EW boson
    TH1D* h_p2Pt[kN_PARTONTYPES];
    TH1D* h_p2Eta[kN_PARTONTYPES];
    TH1D* h_p2Y[kN_PARTONTYPES];
    TH2D* h2_p2Eta_p2Pt[kN_PARTONTYPES];
    TH2D* h2_p2Y_p2Pt[kN_PARTONTYPES];
    // tag-probe histograms
    TH1D* h_deta_p1p2[kN_PARTONTYPES];
    TH1D* h_dphi_p1p2[kN_PARTONTYPES];
    TH1D* h_dy_p1p2[kN_PARTONTYPES];
    TH1D* h_Xj[kN_PARTONTYPES];
    TH1D* h_meanEta_p1p2[kN_PARTONTYPES];
    TH2D* h2_p1Eta_p2Eta[kN_PARTONTYPES];
    TH2D* h2_p1Phi_p2Phi[kN_PARTONTYPES];
    TH2D* h2_p1Y_p2Y[kN_PARTONTYPES];
    TH2D* h2_qscale_deta_p1p2[kN_PARTONTYPES];
    TH2D* h2_meanEta_p1p2_x1overx2[kN_PARTONTYPES];
    TH2D* h2_deta_p1p2_x1overx2[kN_PARTONTYPES];
    // ratio / difference of outgoing probe and hard process probe pt / eta / phi
    TH2D* h2_pt_p2Pt_ratio_sOut_sHard[kN_PARTONTYPES];
    TH2D* h2_pt_p2Eta_diff_sOut_sHard[kN_PARTONTYPES];
    TH2D* h2_pt_p2Phi_diff_sOut_sHard[kN_PARTONTYPES];
    TH2D* h2_pt_deta_p1p2_diff_sOut_sHard[kN_PARTONTYPES];
    TH2D* h2_pt_dphi_p1p2_diff_sOut_sHard[kN_PARTONTYPES];
    TH2D* h2_nMPI_p2Pt_ratio_sOut_sHard[kN_PARTONTYPES];
    TH2D* h2_nISR_p2Pt_ratio_sOut_sHard[kN_PARTONTYPES];
    TH2D* h2_nFSR_p2Pt_ratio_sOut_sHard[kN_PARTONTYPES];
    // histograms for energy and multiplicity distribution of final partons as func. of angle with the initial probe
    // active only if probe is a parton
    TH1D* h_finalqg_p2_dR[kN_PARTONTYPES][kN_PARTONTYPES];
    TH1D* h_finalqg_p2_dR_wE[kN_PARTONTYPES][kN_PARTONTYPES];
    TH1D* h_finalqg_p2_dR_cdf[kN_PARTONTYPES][kN_PARTONTYPES];
    TH1D* h_finalqg_p2_dR_wE_cdf[kN_PARTONTYPES][kN_PARTONTYPES];
    for (int i = 0; i < kN_PARTONTYPES; ++i) {

        std::string strPartonPt = Form("p_{T}^{%s}", partonTypesLabel[i].c_str());
        std::string strPartonEta = Form("#eta^{%s}", partonTypesLabel[i].c_str());
        std::string strPartonPhi = Form("#phi^{%s}", partonTypesLabel[i].c_str());
        std::string strPartonY = Form("y^{%s}", partonTypesLabel[i].c_str());

        std::string strPhoPartonX = Form("x_{%s%s} = %s/%s", partonTypesLabel[i].c_str(), strP1.c_str(), strPartonPt.c_str(), strP1Pt.c_str());
        std::string strPhoPartonDetaShort = Form("#Delta#eta_{%s %s}", partonTypesLabel[i].c_str(), strP1.c_str());
        std::string strPhoPartonDeta = Form("%s = |%s - %s|", strPhoPartonDetaShort.c_str(), strPartonEta.c_str(), strP1Eta.c_str());
        std::string strPhoPartonDphiShort = Form("#Delta#phi_{%s %s}", partonTypesLabel[i].c_str(), strP1.c_str());
        std::string strPhoPartonDphi = Form("%s = |%s - %s|", strPhoPartonDphiShort.c_str(), strPartonPhi.c_str(), strP1Phi.c_str());
        std::string strPhoPartonDy = Form("#Deltay_{%s %s} = |%s - %s|",
                strP1Y.c_str(), partonTypesLabel[i].c_str(), strP1Y.c_str(), strPartonY.c_str());
        std::string strPhoPartonMeanEta = Form("#eta_{ave %s %s} = (%s + %s) / 2",
                strP1.c_str(), partonTypesLabel[i].c_str(), strP1Eta.c_str(), strPartonEta.c_str());
        std::string strPhoPartonMeanEtaAbs = Form("|#eta_{ave %s %s}| = |%s + %s| / 2",
                strP1.c_str(), partonTypesLabel[i].c_str(), strP1Eta.c_str(), strPartonEta.c_str());
        std::string strPhoPartonDiffEta = Form("#eta_{diff %s %s} = (%s - %s) / 2",
                strP1.c_str(), partonTypesLabel[i].c_str(), strP1Eta.c_str(), strPartonEta.c_str());

        h_p2Pt[i] = new TH1D(Form("h_p2Pt_%s", partonTypesStr[i].c_str()),
                Form(";%s;", strPartonPt.c_str()),
                nBinsX_pt, axis_pt_min, axis_pt_max);

        h_p2Eta[i] = new TH1D(Form("h_p2Eta_%s", partonTypesStr[i].c_str()),
                Form(";|%s|;", strPartonEta.c_str()),
                nBinsX_eta, axis_eta_min, axis_eta_max);

        h_p2Y[i] = new TH1D(Form("h_p2Y_%s", partonTypesStr[i].c_str()),
                Form(";|%s|;", strPartonY.c_str()),
                nBinsX_eta, axis_eta_min, axis_eta_max);

        h2_p2Eta_p2Pt[i] = new TH2D(Form("h2_p2Eta_p2Pt_%s", partonTypesStr[i].c_str()),
                Form(";|%s|;%s", strPartonEta.c_str(), strPartonPt.c_str()),
                nBinsX_eta, axis_eta_min, axis_eta_max, nBinsX_pt, axis_pt_min, axis_pt_max);

        h2_p2Y_p2Pt[i] = new TH2D(Form("h2_p2Y_p2Pt_%s", partonTypesStr[i].c_str()),
                Form(";|%s|;%s", strPartonY.c_str(), strPartonPt.c_str()),
                nBinsX_eta, axis_eta_min, axis_eta_max, nBinsX_pt, axis_pt_min, axis_pt_max);

        h_deta_p1p2[i] = new TH1D(Form("h_deta_p1p2_%s", partonTypesStr[i].c_str()),
                Form(";%s;", strPhoPartonDeta.c_str()),
                nBinsX_eta, axis_eta_min, 1.5*axis_eta_max);

        h_dphi_p1p2[i] = new TH1D(Form("h_dphi_p1p2_%s", partonTypesStr[i].c_str()),
                Form(";%s;", strPhoPartonDphi.c_str()),
                nBinsX_phi, 0, TMath::Pi()+1e-12);

        h_dy_p1p2[i] = new TH1D(Form("h_dy_p1p2_%s", partonTypesStr[i].c_str()),
                Form(";%s;", strPhoPartonDy.c_str()),
                nBinsX_eta, axis_eta_min, 1.5*axis_eta_max);

        h_Xj[i] = new TH1D(Form("h_Xj_%s", partonTypesStr[i].c_str()),
                Form(";%s;", strPhoPartonX.c_str()),
                nBinsX_Xj, axis_Xj_min, axis_Xj_max);

        h_meanEta_p1p2[i] = new TH1D(Form("h_meanEta_p1p2_%s", partonTypesStr[i].c_str()),
                Form(";%s;", strPhoPartonMeanEtaAbs.c_str()),
                nBinsX_eta, 0, 0.8*axis_eta_max);

        h2_p1Eta_p2Eta[i] = new TH2D(Form("h2_p1Eta_p2Eta_%s", partonTypesStr[i].c_str()),
                Form(";%s;%s", strP1Eta.c_str(), strPartonEta.c_str()),
                nBinsX_eta, -1*axis_eta_max, axis_eta_max, nBinsX_eta, -1*axis_eta_max, axis_eta_max);

        h2_p1Phi_p2Phi[i] = new TH2D(Form("h2_p1Phi_p2Phi_%s", partonTypesStr[i].c_str()),
                Form(";%s;%s", strP1Phi.c_str(), strPartonPhi.c_str()),
                nBinsX_phi, -TMath::Pi(), TMath::Pi(), nBinsX_phi, -TMath::Pi(), TMath::Pi());

        h2_p1Y_p2Y[i] = new TH2D(Form("h2_p1Y_p2Y_%s", partonTypesStr[i].c_str()),
                Form(";%s;%s", strP1Y.c_str(), strPartonY.c_str()),
                nBinsX_eta, -1*axis_eta_max, axis_eta_max, nBinsX_eta, -1*axis_eta_max, axis_eta_max);

        h2_qscale_deta_p1p2[i] = new TH2D(Form("h2_qscale_deta_p1p2_%s", partonTypesStr[i].c_str()),
                Form(";%s;Q", strPhoPartonDeta.c_str()),
                nBinsX_eta, axis_eta_min, axis_eta_max, nBinsX_pt, axis_pt_min, axis_pt_max);

        int nBins_x1Overx2 = 50;
        std::vector<double> binsVec = calcBinsLogScale(0.001, 1000, nBins_x1Overx2);
        double binsArr[nBins_x1Overx2+1];
        std::copy(binsVec.begin(), binsVec.end(), binsArr);
        h2_meanEta_p1p2_x1overx2[i] = new TH2D(Form("h2_meanEta_p1p2_%s_x1overx2", partonTypesStr[i].c_str()),
                Form(";%s;x_{1} / x_{2}", strPhoPartonMeanEta.c_str()),
                nBinsX_eta, -0.8*axis_eta_max, 0.8*axis_eta_max, nBins_x1Overx2, binsArr);

        h2_deta_p1p2_x1overx2[i] = new TH2D(Form("h2_deta_p1p2_%s_x1overx2", partonTypesStr[i].c_str()),
                Form(";%s;x_{1} / x_{2}", strPhoPartonDiffEta.c_str()),
                nBinsX_eta, -0.8*axis_eta_max, 0.8*axis_eta_max, nBins_x1Overx2, binsArr);

        h2_pt_p2Pt_ratio_sOut_sHard[i] = new TH2D(Form("h2_pt_p2Pt_%s_ratio_sOut_sHard", partonTypesStr[i].c_str()),
                Form(";%s (hard process);%s (outgoing) / %s (hard process)", strPartonPt.c_str(), strPartonPt.c_str(), strPartonPt.c_str()),
                nBinsX_pt, axis_pt_min, axis_pt_max, nBinsX_ratio_pt, axis_ratio_pt_min, axis_ratio_pt_max);

        h2_pt_p2Eta_diff_sOut_sHard[i] = new TH2D(Form("h2_pt_p2Eta_%s_diff_sOut_sHard", partonTypesStr[i].c_str()),
                Form(";%s (hard process);%s (outgoing) - %s (hard process)", strPartonPt.c_str(), strPartonEta.c_str(), strPartonEta.c_str()),
                nBinsX_pt, axis_pt_min, axis_pt_max, nBinsX_diff_eta, axis_diff_eta_min, axis_diff_eta_max);

        h2_pt_p2Phi_diff_sOut_sHard[i] = new TH2D(Form("h2_pt_p2Phi_%s_diff_sOut_sHard", partonTypesStr[i].c_str()),
                Form(";%s (hard process);%s (outgoing) - %s (hard process)", strPartonPt.c_str(), strPartonPhi.c_str(), strPartonPhi.c_str()),
                nBinsX_pt, axis_pt_min, axis_pt_max, nBinsX_diff_phi, axis_diff_phi_min, axis_diff_phi_max);

        h2_pt_deta_p1p2_diff_sOut_sHard[i] = new TH2D(Form("h2_pt_deta_p1p2_%s_diff_sOut_sHard", partonTypesStr[i].c_str()),
                Form(";%s (hard process);%s (outgoing) - %s (hard process)", strP1Pt.c_str(), strPhoPartonDetaShort.c_str(), strPhoPartonDetaShort.c_str()),
                nBinsX_pt, axis_pt_min, axis_pt_max, nBinsX_diff_eta, axis_diff_eta_min, axis_diff_eta_max);

        h2_pt_dphi_p1p2_diff_sOut_sHard[i] = new TH2D(Form("h2_pt_dphi_p1p2_%s_diff_sOut_sHard", partonTypesStr[i].c_str()),
                Form(";%s (hard process);%s (outgoing) - %s (hard process)", strP1Pt.c_str(), strPhoPartonDphiShort.c_str(), strPhoPartonDphiShort.c_str()),
                nBinsX_pt, axis_pt_min, axis_pt_max, nBinsX_diff_phi, axis_diff_phi_min, axis_diff_phi_max);

        h2_nMPI_p2Pt_ratio_sOut_sHard[i] = new TH2D(Form("h2_nMPI_p2Pt_%s_ratio_sOut_sHard", partonTypesStr[i].c_str()),
                Form(";nMPI;%s (outgoing) / %s (hard process)", strPartonPt.c_str(), strPartonPt.c_str(), strPartonPt.c_str()),
                25, 0, 25, nBinsX_ratio_pt, axis_ratio_pt_min, axis_ratio_pt_max);

        h2_nISR_p2Pt_ratio_sOut_sHard[i] = new TH2D(Form("h2_nISR_p2Pt_%s_ratio_sOut_sHard", partonTypesStr[i].c_str()),
                Form(";nISR;%s (outgoing) / %s (hard process)", strPartonPt.c_str(), strPartonPt.c_str(), strPartonPt.c_str()),
                45, 0, 45, nBinsX_ratio_pt, axis_ratio_pt_min, axis_ratio_pt_max);

        h2_nFSR_p2Pt_ratio_sOut_sHard[i] = new TH2D(Form("h2_nFSR_p2Pt_%s_ratio_sOut_sHard", partonTypesStr[i].c_str()),
                Form(";nFSR;%s (outgoing) / %s (hard process)", strPartonPt.c_str(), strPartonPt.c_str(), strPartonPt.c_str()),
                50, 0, 250, nBinsX_ratio_pt, axis_ratio_pt_min, axis_ratio_pt_max);

        for (int j = 0; j < kN_PARTONTYPES; ++j) {
            h_finalqg_p2_dR[i][j] = new TH1D(Form("h_final%s_p2_%s_dR", partonTypesStr[j].c_str(), partonTypesStr[i].c_str()),
                    Form(";#DeltaR_{%s final %s};", partonTypesLabel[i].c_str(), partonTypesLabel[j].c_str()), nBinsX_eta, 0, 1.5);

            h_finalqg_p2_dR_wE[i][j] = new TH1D(Form("h_final%s_p2_%s_dR_wE", partonTypesStr[j].c_str(), partonTypesStr[i].c_str()),
                    Form(";#DeltaR_{%s final %s};", partonTypesLabel[i].c_str(), partonTypesLabel[j].c_str()), nBinsX_eta, 0, 1.5);
        }
    }

    enum PARTONTYPES2 {
        kQG2 = PARTONTYPES::kQG,
        kQ2 = PARTONTYPES::kQ,
        kG2 = PARTONTYPES::kG,
        kudsQ,
        kbctQ,
        kcQ,
        kbQ,
        kN_PARTONTYPES2
    };
    std::string partonTypes2Str[kN_PARTONTYPES2] = {"parton", "q", "g", "uds", "bct", "c", "b"};
    std::string partonTypes2Label[kN_PARTONTYPES2] = {"q/g", "q", "g", "u/d/s", "b/c/t", "c", "b"};

    // tag histograms split for parton types
    TH1D* h_p1Pt_p2Frac[kN_PARTONTYPES2];
    TH1D* h_p1Eta_p2Frac[kN_PARTONTYPES2];
    TH1D* h_p1Y_p2Frac[kN_PARTONTYPES2];

    for (int i = 0; i < kN_PARTONTYPES2; ++i) {

        h_p1Pt_p2Frac[i] = new TH1D(Form("h_p1Pt_p2Frac_%s", partonTypes2Str[i].c_str()),
                Form(";%s;", strP1Pt.c_str()),
                200, 0, 1000);
        h_p1Eta_p2Frac[i] = new TH1D(Form("h_p1Eta_p2Frac_%s", partonTypes2Str[i].c_str()),
                Form(";|%s|;", strP1Eta.c_str()),
                50, 0, 5);
        h_p1Y_p2Frac[i] = new TH1D(Form("h_p1Y_p2Frac_%s", partonTypes2Str[i].c_str()),
                Form(";|%s|;", strP1Y.c_str()),
                50, 0, 5);
    }

    int eventsAnalyzed = 0;
    int nEvents = treeEvt->GetEntries();
    std::cout << "nEvents = " << nEvents << std::endl;
    std::cout << "Loop STARTED" << std::endl;
    for (int iEvent = 0; iEvent < nEvents; ++iEvent) {

        if (iEvent % 10000 == 0)  {
          std::cout << "current entry = " <<iEvent<<" out of "<<nEvents<<" : "<<std::setprecision(2)<<(double)iEvent/nEvents*100<<" %"<<std::endl;
        }

        treeEvt->GetEntry(iEvent);
        treeEvtParton->GetEntry(iEvent);
        treeEvtInfo->GetEntry(iEvent);

        // hard scatterer analysis
        // outgoing particles of the hardest subprocess are at index 5 and 6
        int iH1 = 5;
        int iH2 = 6;

        // leading hard scatterer (tag) is the one whose outgoing daughter has the largest pt
        // the other hard scatterer is subleading (probe)
        int iTag = -1;
        int iTagOutgoing = -1;
        double ptTagOutgoing = -1;
        int nTagOutCand = 0;

        if (tagCode == TAGS::kGamma) {
            if ((isGamma((*event)[iH1])) && (isParton((*event)[iH2])))
                iTag = iH1;
            else if ((isGamma((*event)[iH2])) && (isParton((*event)[iH1])))
                iTag = iH2;
        }
        else if (tagCode == TAGS::kZ0) {
            if ((isZboson((*event)[iH1])) && (isParton((*event)[iH2])))
                iTag = iH1;
            else if ((isZboson((*event)[iH2])) && (isParton((*event)[iH1])))
                iTag = iH2;
        }

        int eventPartonSize = eventParton->size();
        if (iTag == -1) {
            // find the leading outgoing daughter and thus identify the "tag"
            for (int i = 0; i < eventPartonSize; ++i) {

                // should not have a daughter in parton-level particles
                if (hasDaughter((*eventParton)[i]))  continue;

                int indexOrig = (*eventParton)[i].mother1();
                // must be a daughter of the hard scattering particle
                if (!isAncestor(event, indexOrig, iH1) && !isAncestor(event, indexOrig, iH2))  continue;

                // mother hard scatterer
                int iHmother = (isAncestor(event, indexOrig, iH1)) ? iH1 : iH2;

                bool passedTagCode = true;
                if (tagCode == TAGS::kParton || tagCode == TAGS::kQuark || tagCode == TAGS::kGluon){
                    passedTagCode = isParton((*event)[iHmother]);
                }
                else if (tagCode == TAGS::kGamma){
                    passedTagCode = isGamma((*event)[iHmother]);
                }
                else if (tagCode == TAGS::kLeadGamma){
                    passedTagCode = (isGamma((*event)[iHmother]) || isParton((*event)[iHmother]));
                }
                else if (tagCode == TAGS::kZ0){
                    passedTagCode = isZboson((*event)[iHmother]);
                }

                if (passedTagCode) {
                    nTagOutCand++;

                    if ((*event)[indexOrig].pT() > ptTagOutgoing) {

                        ptTagOutgoing = (*event)[indexOrig].pT();
                        iTagOutgoing = indexOrig;
                        iTag = iHmother;
                    }
                }
            }
        }

        if (iTag == -1) continue;

        /*
         * if tag is required to be quark or gluon, then the leading parton must be of that flavor
         */
        if (tagCode == TAGS::kQuark){
            if (!isQuark((*event)[iTag])) continue;
        }
        else if (tagCode == TAGS::kGluon){
            if (!isGluon((*event)[iTag])) continue;
        }

        int iProbe = (iTag == iH1) ? iH2 : iH1;
        int iProbeOutgoing = -1;
        double ptProbeOutgoing = -1;
        // "tag" is identified, the other hard scatterer is "probe" by definition
        // find the "probe"s leading outgoing daughter
        for (int i = 0; i < eventPartonSize; ++i) {

            // should not have a daughter in parton-level particles
            if (hasDaughter((*eventParton)[i]))  continue;

            int indexOrig = (*eventParton)[i].mother1();
            // must be a daughter of the "probe" hard scattering
            if (!isAncestor(event, indexOrig, iProbe))  continue;

            if ((*event)[indexOrig].pT() > ptProbeOutgoing) {

                ptProbeOutgoing = (*event)[indexOrig].pT();
                iProbeOutgoing = indexOrig;
            }
        }

        if (iTag == -1 || iProbe == -1) continue;
        eventsAnalyzed++;

        if (iTagOutgoing == -1 && iStatusTag == kOut)  continue;

        std::vector<double> p1E(kN_STATUSES, -1);
        std::vector<double> p1Pt(kN_STATUSES, -1);
        std::vector<double> p1Eta(kN_STATUSES, -1);
        std::vector<double> p1Phi(kN_STATUSES, -1);
        std::vector<double> p1Y(kN_STATUSES, -1);

        std::vector<int> indicesTag = {iTag, iTagOutgoing};
        for (int i = 0; i < kN_STATUSES; ++i) {
            int j = indicesTag[i];
            if (j == -1) continue;

            p1E[i] = (*event)[j].e();
            p1Pt[i] = (*event)[j].pT();
            p1Eta[i] = (*event)[j].eta();
            p1Phi[i] = (*event)[j].phi();
            p1Y[i] = (*event)[j].y();
        }

        if (TMath::Abs(p1Eta[iStatusTag]) < tagMaxEta) {
            h_p1Pt->Fill(p1Pt[iStatusTag]);
        }
        if (p1Pt[iStatusTag] > tagMinPt) {
            h_p1Eta->Fill(TMath::Abs(p1Eta[iStatusTag]));
        }

        if (!(p1Pt[iStatusTag] > tagMinPt))  continue;
        if (!(TMath::Abs(p1Eta[iStatusTag]) < tagMaxEta))  continue;

        h_p1Y->Fill(TMath::Abs(p1Y[iStatusTag]));
        h2_p1Eta_p1Pt->Fill(TMath::Abs(p1Eta[iStatusTag]), p1Pt[iStatusTag]);
        h2_p1Y_p1Pt->Fill(TMath::Abs(p1Y[iStatusTag]), p1Pt[iStatusTag]);

        h2_qscale_p1Pt->Fill(p1Pt[iStatusTag], event->scale());
        h2_qscale_p1Eta->Fill(TMath::Abs(p1Eta[iStatusTag]), event->scale());

        h2_pt_p1Pt_ratio_sOut_sHard->Fill(p1Pt[kHard], p1Pt[kOut] / p1Pt[kHard]);
        h2_pt_p1Eta_diff_sOut_sHard->Fill(p1Pt[kHard], p1Eta[kOut] - p1Eta[kHard]);
        h2_pt_p1Phi_diff_sOut_sHard->Fill(p1Pt[kHard], getDPHI(p1Phi[kOut], p1Phi[kHard]));
        h2_nMPI_p1Pt_ratio_sOut_sHard->Fill(info->nMPI(), p1Pt[kOut] / p1Pt[kHard]);
        h2_nISR_p1Pt_ratio_sOut_sHard->Fill(info->nISR(), p1Pt[kOut] / p1Pt[kHard]);
        h2_nFSR_p1Pt_ratio_sOut_sHard->Fill(info->nFSRinProc(), p1Pt[kOut] / p1Pt[kHard]);

        if (tagCode == TAGS::kParton || tagCode == TAGS::kQuark || tagCode == TAGS::kGluon) {

            for (int i = 0; i < eventPartonSize; ++i) {
                int indexOrig = (*eventParton)[i].mother1();

                if (isAncestor(event, indexOrig, iTag)) {
                    double parton_qg_dR = getDR(p1Eta[iStatusTag], p1Phi[iStatusTag], (*event)[indexOrig].eta(), (*event)[indexOrig].phi());
                    double wE = (*event)[indexOrig].e() / p1E[iStatusTag];

                    int iFinalQG = (isQuark((*event)[indexOrig])) ? PARTONTYPES::kQ : PARTONTYPES::kG;
                    std::vector<int> typesFinalQG = {kQG, iFinalQG};
                    int nTypesFinalQG = typesFinalQG.size();

                    for (int j2 = 0; j2 < nTypesFinalQG; ++j2) {
                        int k2 = typesFinalQG[j2];

                        h_finalqg_p1_dR[k2]->Fill(parton_qg_dR);
                        h_finalqg_p1_dR_wE[k2]->Fill(parton_qg_dR, wE);
                    }
                }
            }
        }

        if (iProbeOutgoing == -1 && iStatusProbe == kOut)  continue;

        std::vector<double> p2E(kN_STATUSES, -1);
        std::vector<double> p2Pt(kN_STATUSES, -1);
        std::vector<double> p2Eta(kN_STATUSES, -1);
        std::vector<double> p2Phi(kN_STATUSES, -1);
        std::vector<double> p2Y(kN_STATUSES, -1);

        std::vector<int> indicesProbe = {iProbe, iProbeOutgoing};
        for (int i = 0; i < kN_STATUSES; ++i) {
            int j = indicesProbe[i];
            if (j == -1) continue;

            p2E[i] = (*event)[j].e();
            p2Pt[i] = (*event)[j].pT();
            p2Eta[i] = (*event)[j].eta();
            p2Phi[i] = (*event)[j].phi();
            p2Y[i] = (*event)[j].y();
        }

        double deta_p1p2 = TMath::Abs(p1Eta[iStatusTag] - p2Eta[iStatusProbe]);
        double dphi_p1p2 = std::acos(cos(p1Phi[iStatusTag] - p2Phi[iStatusProbe]));
        double dy_p1p2 = TMath::Abs(p1Y[iStatusTag] - p2Y[iStatusProbe]);
        double Xj_p1p2 = p2Pt[iStatusProbe] / p1Pt[iStatusTag];
        double meanEta_p1p2 = 0.5*(p1Eta[iStatusTag] + p2Eta[iStatusProbe]);
        double diffEta_p1p2 = 0.5*(p1Eta[iStatusTag] - p2Eta[iStatusProbe]);

        int iQG = (isQuark((*event)[iProbe])) ? PARTONTYPES::kQ : PARTONTYPES::kG;

        std::vector<int> typesQG = {kQG, iQG};
        int nTypesQG = typesQG.size();

        for (int j = 0; j < nTypesQG; ++j) {
            int k = typesQG[j];

            h_p2Pt[k]->Fill(p2Pt[iStatusProbe]);
            h_p2Eta[k]->Fill(TMath::Abs(p2Eta[iStatusProbe]));
            h_p2Y[k]->Fill(TMath::Abs(p2Y[iStatusProbe]));
            h2_p2Eta_p2Pt[k]->Fill(TMath::Abs(p2Eta[iStatusProbe]), p2Pt[iStatusProbe]);
            h2_p2Y_p2Pt[k]->Fill(TMath::Abs(p2Y[iStatusProbe]), p2Pt[iStatusProbe]);
            h_deta_p1p2[k]->Fill(deta_p1p2);
            h_dphi_p1p2[k]->Fill(dphi_p1p2);
            h_dy_p1p2[k]->Fill(dy_p1p2);
            h_Xj[k]->Fill(Xj_p1p2);
            h_meanEta_p1p2[k]->Fill(TMath::Abs(meanEta_p1p2));
            h2_p1Eta_p2Eta[k]->Fill(p1Eta[iStatusTag], p2Eta[iStatusProbe]);
            h2_p1Phi_p2Phi[k]->Fill(p1Phi[iStatusTag], p2Phi[iStatusProbe]);
            h2_p1Y_p2Y[k]->Fill(p1Y[iStatusTag], p2Y[iStatusProbe]);
            h2_qscale_deta_p1p2[k]->Fill(deta_p1p2, event->scale());
            h2_meanEta_p1p2_x1overx2[k]->Fill(meanEta_p1p2, info->x1()/info->x2());
            h2_deta_p1p2_x1overx2[k]->Fill(diffEta_p1p2, info->x1()/info->x2());
            h2_pt_p2Pt_ratio_sOut_sHard[k]->Fill(p2Pt[kHard], p2Pt[kOut] / p2Pt[kHard]);
            h2_pt_p2Eta_diff_sOut_sHard[k]->Fill(p2Pt[kHard], p2Eta[kOut] - p2Eta[kHard]);
            h2_pt_p2Phi_diff_sOut_sHard[k]->Fill(p2Pt[kHard], getDPHI(p2Phi[kOut], p2Phi[kHard]));
            h2_pt_deta_p1p2_diff_sOut_sHard[k]->Fill(p1Pt[iStatusTag], (p1Eta[kOut] - p2Eta[kOut])-(p1Eta[kHard] - p2Eta[kHard]));
            h2_pt_dphi_p1p2_diff_sOut_sHard[k]->Fill(p1Pt[iStatusTag], getDPHI(p1Phi[kOut]-p1Phi[kHard], p2Phi[kOut]-p2Phi[kHard]));
            h2_nMPI_p2Pt_ratio_sOut_sHard[k]->Fill(info->nMPI(), p2Pt[kOut] / p2Pt[kHard]);
            h2_nISR_p2Pt_ratio_sOut_sHard[k]->Fill(info->nISR(), p2Pt[kOut] / p2Pt[kHard]);
            h2_nFSR_p2Pt_ratio_sOut_sHard[k]->Fill(info->nFSRinProc(), p2Pt[kOut] / p2Pt[kHard]);
        }

        for (int j = 0; j < kN_PARTONTYPES2; ++j) {

            if (j == PARTONTYPES2::kQG2 && !(isParton((*event)[iProbe])))  continue;
            else if (j == PARTONTYPES2::kQ2 && !(isQuark((*event)[iProbe])))  continue;
            else if (j == PARTONTYPES2::kG2 && !(isGluon((*event)[iProbe])))  continue;
            else if (j == PARTONTYPES2::kudsQ && !((*event)[iProbe].idAbs() >= 1 && (*event)[iProbe].idAbs() <= 3))  continue;
            else if (j == PARTONTYPES2::kbctQ && !((*event)[iProbe].idAbs() >= 4 && (*event)[iProbe].idAbs() <= 8))  continue;
            else if (j == PARTONTYPES2::kcQ && !((*event)[iProbe].idAbs() == 4))  continue;
            else if (j == PARTONTYPES2::kbQ && !((*event)[iProbe].idAbs() == 5))  continue;

            h_p1Pt_p2Frac[j]->Fill(p1Pt[iStatusTag]);
            h_p1Eta_p2Frac[j]->Fill(TMath::Abs(p1Eta[iStatusTag]));
            h_p1Y_p2Frac[j]->Fill(TMath::Abs(p1Y[iStatusTag]));
        }

        for (int i = 0; i < eventPartonSize; ++i) {
            int indexOrig = (*eventParton)[i].mother1();

            if (isAncestor(event, indexOrig, iProbe)) {
                double parton_qg_dR = getDR(p2Eta[iStatusProbe], p2Phi[iStatusProbe], (*event)[indexOrig].eta(), (*event)[indexOrig].phi());
                double wE = (*event)[indexOrig].e() / p2E[iStatusProbe];

                int iFinalQG = (isQuark((*event)[indexOrig])) ? PARTONTYPES::kQ : PARTONTYPES::kG;
                std::vector<int> typesFinalQG = {kQG, iFinalQG};
                int nTypesFinalQG = typesFinalQG.size();

                for (int j1 = 0; j1 < nTypesQG; ++j1) {
                    int k1 = typesQG[j1];

                    for (int j2 = 0; j2 < nTypesFinalQG; ++j2) {
                        int k2 = typesFinalQG[j2];

                        h_finalqg_p2_dR[k1][k2]->Fill(parton_qg_dR);
                        h_finalqg_p2_dR_wE[k1][k2]->Fill(parton_qg_dR, wE);
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

    double nPartonsP1 = h2_qscale_p1Pt->GetEntries();

    h_p1Pt->Scale(1./h_p1Pt->Integral(), "width");
    h_p1Eta->Scale(1./h_p1Eta->Integral(), "width");
    h_p1Y->Scale(1./h_p1Y->Integral(), "width");

    for (int j = 0; j < kN_PARTONTYPES; ++j) {
        h_finalqg_p1_dR_cdf[j] = (TH1D*)h_finalqg_p1_dR[j]->GetCumulative(true, "_cdf");
        h_finalqg_p1_dR_wE_cdf[j] = (TH1D*)h_finalqg_p1_dR_wE[j]->GetCumulative(true, "_cdf");

        setConstantBinError(h_finalqg_p1_dR_cdf[j], 0.0001);
        setConstantBinError(h_finalqg_p1_dR_wE_cdf[j], 0.0001);

        h_finalqg_p1_dR[j]->Scale(1./nPartonsP1, "width");
        h_finalqg_p1_dR_wE[j]->Scale(1./nPartonsP1, "width");
        h_finalqg_p1_dR_cdf[j]->Scale(1./nPartonsP1);
        h_finalqg_p1_dR_wE_cdf[j]->Scale(1./nPartonsP1);
    }

    for (int i = 0; i < kN_PARTONTYPES; ++i) {

        double nPartons = h_p2Pt[i]->GetEntries();

        h_p2Pt[i]->Scale(1./h_p2Pt[i]->Integral(), "width");
        h_p2Eta[i]->Scale(1./h_p2Eta[i]->Integral(), "width");
        h_p2Y[i]->Scale(1./h_p2Y[i]->Integral(), "width");
        h_deta_p1p2[i]->Scale(1./h_deta_p1p2[i]->Integral(), "width");
        h_dphi_p1p2[i]->Scale(1./h_dphi_p1p2[i]->Integral(), "width");
        h_dy_p1p2[i]->Scale(1./h_dy_p1p2[i]->Integral(), "width");
        h_Xj[i]->Scale(1./h_Xj[i]->Integral(), "width");
        h_meanEta_p1p2[i]->Scale(1./h_meanEta_p1p2[i]->Integral(), "width");

        for (int j = 0; j < kN_PARTONTYPES; ++j) {
            h_finalqg_p2_dR_cdf[i][j] = (TH1D*)h_finalqg_p2_dR[i][j]->GetCumulative(true, "_cdf");
            h_finalqg_p2_dR_wE_cdf[i][j] = (TH1D*)h_finalqg_p2_dR_wE[i][j]->GetCumulative(true, "_cdf");

            setConstantBinError(h_finalqg_p2_dR_cdf[i][j], 0.0001);
            setConstantBinError(h_finalqg_p2_dR_wE_cdf[i][j], 0.0001);

            h_finalqg_p2_dR[i][j]->Scale(1./nPartons, "width");
            h_finalqg_p2_dR_wE[i][j]->Scale(1./nPartons, "width");
            h_finalqg_p2_dR_cdf[i][j]->Scale(1./nPartons);
            h_finalqg_p2_dR_wE_cdf[i][j]->Scale(1./nPartons);
        }
    }

    for (int i = 0; i < kN_PARTONTYPES2; ++i) {

        if (i != PARTONTYPES2::kQG2) {
            h_p1Pt_p2Frac[i]->Divide(h_p1Pt_p2Frac[PARTONTYPES2::kQG2]);
            h_p1Eta_p2Frac[i]->Divide(h_p1Eta_p2Frac[PARTONTYPES2::kQG2]);
            h_p1Y_p2Frac[i]->Divide(h_p1Y_p2Frac[PARTONTYPES2::kQG2]);
        }
    }

    outputFile->Write("", TObject::kOverwrite);
    std::cout << "Closing the output file" << std::endl;
    outputFile->Close();

    std::cout << "running hardScatteringAna() - END" << std::endl;
}

int main(int argc, char* argv[]) {

    std::vector<std::string> argStr = ArgumentParser::ParseParameters(argc, argv);
    int nArgStr = argStr.size();

    argOptions = ArgumentParser::ParseOptions(argc, argv);

    if (nArgStr == 3) {
        hardScatteringAna(argStr.at(1), argStr.at(2));
    }
    else if (nArgStr == 2) {
        hardScatteringAna(argStr.at(1));
    }
    else {
        std::cout << "Usage : \n" <<
                "./hardScatteringAna.exe <inputFileName> <outputFileName> [options]"
                << std::endl;
        std::cout << "Options are" << std::endl;
        std::cout << "--tag=<label for tag particle>" << std::endl;
        std::cout << "--tagStatus=<code for status of tag particle>" << std::endl;
        std::cout << "--probeStatus=<code for status of probe particle>" << std::endl;
        std::cout << "--tagMinPt=<min pT for tag particle>" << std::endl;
        std::cout << "--tagMaxEta=<max |eta| for tag particle>" << std::endl;
        return 1;
    }
    return 0;
}
