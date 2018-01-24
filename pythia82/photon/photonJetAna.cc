/*
 * code to analyze photon+jet events
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

#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include "../../utilities/physicsUtil.h"

void photonJetAna(std::string eventFileName = "promptPhoton.root", std::string jetFileName = "jets.root",
                  std::string jetTreeName = "ak3jets", std::string outputFileName = "photonJetAna_out.root", int iStatusPhoton = 1);

void photonJetAna(std::string eventFileName, std::string jetFileName, std::string jetTreeName, std::string outputFileName,
                  int iStatusPhoton)
{
    std::cout << "running photonJetAna()" << std::endl;

    std::cout << "##### Parameters #####" << std::endl;
    std::cout << "eventFileName = " << eventFileName.c_str() << std::endl;
    std::cout << "jetFileName = " << jetFileName.c_str() << std::endl;
    std::cout << "jetTreeName = " << jetTreeName.c_str() << std::endl;
    std::cout << "outputFileName = " << outputFileName.c_str() << std::endl;
    std::cout << "iStatusPhoton = " << iStatusPhoton << std::endl;
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

    enum STATUSES {
        kHard,
        kOut,
        kN_STATUSES
    };

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

    TH1D* h_phoPt = new TH1D("h_phoPt",Form(";%s;", strPhoPt.c_str()), nBinsX_pt, axis_pt_min, axis_pt_max);
    TH1D* h_phoEta = new TH1D("h_phoEta",Form(";|%s|;", strPhoEta.c_str()), nBinsX_eta, axis_eta_min, axis_eta_max);
    TH2D* h2_phoEta_phoPt = new TH2D("h2_phoEta_phoPt",Form(";|%s|;%s", strPhoEta.c_str(), strPhoPt.c_str()),
            nBinsX_eta, axis_eta_min, axis_eta_max, nBinsX_pt, axis_pt_min, axis_pt_max);

    // event info
    TH2D* h2_qscale_phoPt = new TH2D("h2_qscale_phoPt", Form(";%s;Q", strPhoPt.c_str()), nBinsX_pt, axis_pt_min, axis_pt_max, nBinsX_pt, axis_pt_min, axis_pt_max);
    TH2D* h2_qscale_phoEta = new TH2D("h2_qscale_phoEta", Form(";|%s|;Q", strPhoEta.c_str()), nBinsX_eta, axis_eta_min, axis_eta_max, nBinsX_pt, axis_pt_min, axis_pt_max);

    enum PARTONTYPES {
        kInclusive,
        kQuark,
        kGluon,
        kN_PARTONTYPES
    };
    std::string partonTypesStr[kN_PARTONTYPES] = {"parton", "q", "g"};
    std::string partonTypesLabel[kN_PARTONTYPES] = {"q/g", "q", "g"};

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
        kxipho,
        kN_FFDEFNS
    };
    std::string ffDefnsStr[kN_FFDEFNS] = {"xijet", "xipho"};
    std::string ffDefnsLabel[kN_FFDEFNS] = {"#xi^{jet}", Form("#xi^{%s}_{T}", strPho.c_str())};

    int nBinsX_xijet = 10;
    double axis_xijet_min = 0;
    double axis_xijet_max = 5;

    double axis_js_min = 0;
    double axis_js_max = 0.6;
    int nBinsX_js = round(axis_js_max / 0.05);

    // photon histograms
    TH1D* h_phoPt_qg[kN_PARTONTYPES];
    // parton histograms
    TH1D* h_qgPt[kN_PARTONTYPES];
    TH1D* h_qgEta[kN_PARTONTYPES];
    TH2D* h2_qgEta_qgPt[kN_PARTONTYPES];
    TH2D* h2_phoqgX_phoPt[kN_PARTONTYPES];
    TH2D* h2_phoqgX_phoEta[kN_PARTONTYPES];
    TH2D* h2_phoqgX_phoqgDeta[kN_PARTONTYPES];
    TH2D* h2_phoqgX_phoqgDphi[kN_PARTONTYPES];
    // photon-parton histograms
    TH1D* h_phoqgDeta[kN_PARTONTYPES];
    TH1D* h_phoqgDphi[kN_PARTONTYPES];
    TH1D* h_phoqgX[kN_PARTONTYPES];
    TH1D* h_phoqgNjet[kN_PARTONTYPES];
    TH2D* h2_phoEta_qgEta[kN_PARTONTYPES];
    TH2D* h2_phoPhi_qgPhi[kN_PARTONTYPES];
    TH2D* h2_qscale_phoqgDeta[kN_PARTONTYPES];
    // photon histograms split for parton types
    TH1D* h_phoPt_qgRatio[kN_PARTONTYPES];
    // jet FF histograms split by particle types
    TH1D* h_ff[kN_PARTONTYPES][kN_PARTICLETYPES][kN_FFDEFNS];
    TH1D* h_jetshape[kN_PARTONTYPES][kN_PARTICLETYPES];
    TH1D* h_jetshape_normJet[kN_PARTONTYPES][kN_PARTICLETYPES];
    TH1D* h_ff_ptSort[kN_PARTONTYPES][kN_PARTICLETYPES][kN_FFDEFNS][kN_PTSORTING];
    TH1D* h_ff_ptSort_daughter[kN_PARTONTYPES][kN_PARTICLETYPES][kN_FFDEFNS][kN_PTSORTING];
    TH1D* h_jetshape_ptSort[kN_PARTONTYPES][kN_PARTICLETYPES][kN_PTSORTING];
    TH1D* h_jetshape_ptSort_normJet[kN_PARTONTYPES][kN_PARTICLETYPES][kN_PTSORTING];
    TH1D* h_jetshape_ptSort_daughter[kN_PARTONTYPES][kN_PARTICLETYPES][kN_PTSORTING];
    TH1D* h_jetshape_ptSort_daughter_normJet[kN_PARTONTYPES][kN_PARTICLETYPES][kN_PTSORTING];
    for (int i = 0; i < kN_PARTONTYPES; ++i) {

        std::string strPartonPt = Form("p_{T}^{%s}", partonTypesLabel[i].c_str());
        std::string strPartonEta = Form("#eta^{%s}", partonTypesLabel[i].c_str());
        std::string strPartonPhi = Form("#phi^{%s}", partonTypesLabel[i].c_str());

        std::string strPhoPartonX = Form("x_{%s%s} = %s/%s", partonTypesLabel[i].c_str(), strPho.c_str(), strPartonPt.c_str(), strPhoPt.c_str());
        std::string strPhoPartonDeta = Form("#Delta#eta_{%s%s} = |%s - %s|",
                partonTypesLabel[i].c_str(), strPho.c_str(), strPartonEta.c_str(), strPhoEta.c_str());
        std::string strPhoPartonDphi = Form("#Delta#phi_{%s%s} = |%s - %s|",
                partonTypesLabel[i].c_str(), strPho.c_str(), strPartonPhi.c_str(), strPhoPhi.c_str());

        h_phoPt_qg[i] = new TH1D(Form("h_phoPt_%s", partonTypesStr[i].c_str()),
                Form(";%s (recoil is %s);", strPhoPt.c_str(), partonTypesLabel[i].c_str()),
                nBinsX_pt, axis_pt_min, axis_pt_max);

        h_qgPt[i] = new TH1D(Form("h_%sPt", partonTypesStr[i].c_str()),
                Form(";%s;", strPartonPt.c_str()),
                nBinsX_pt, axis_pt_min, axis_pt_max);

        h_qgEta[i] = new TH1D(Form("h_%sEta", partonTypesStr[i].c_str()),
                Form(";|%s|;", strPartonEta.c_str()),
                nBinsX_eta, axis_eta_min, axis_eta_max);

        h2_qgEta_qgPt[i] = new TH2D(Form("h2_%sEta_%sPt", partonTypesStr[i].c_str(), partonTypesStr[i].c_str()),
                Form(";|%s|;%s", strPartonEta.c_str(), strPartonPt.c_str()),
                nBinsX_eta, axis_eta_min, axis_eta_max, nBinsX_pt, axis_pt_min, axis_pt_max);

        h2_phoqgX_phoPt[i] = new TH2D(Form("h2_pho%sX_phoPt", partonTypesStr[i].c_str()),
                Form(";%s;%s", partonTypesLabel[i].c_str(), strPhoPartonX.c_str(), strPhoPt.c_str()),
                nBinsX_phoqgX, axis_phoqgX_min, axis_phoqgX_max, nBinsX_pt, axis_pt_min, axis_pt_max);

        h2_phoqgX_phoEta[i] = new TH2D(Form("h2_pho%sX_phoEta", partonTypesStr[i].c_str()),
                Form(";%s;|%s|", strPhoPartonX.c_str(), strPhoEta.c_str()),
                nBinsX_phoqgX, axis_phoqgX_min, axis_phoqgX_max, nBinsX_eta, axis_eta_min, axis_eta_max);

        h2_phoqgX_phoqgDeta[i] = new TH2D(Form("h2_pho%sX_pho%sDeta", partonTypesStr[i].c_str(), partonTypesStr[i].c_str()),
                Form(";%s;%s", strPhoPartonX.c_str(), strPhoPartonDeta.c_str()),
                nBinsX_phoqgX, axis_phoqgX_min, axis_phoqgX_max, nBinsX_eta, axis_eta_min, axis_eta_max);

        h2_phoqgX_phoqgDphi[i] = new TH2D(Form("h2_pho%sX_pho%sDphi", partonTypesStr[i].c_str(), partonTypesStr[i].c_str()),
                Form(";%s;%s", strPhoPartonX.c_str(), strPhoPartonDphi.c_str()),
                nBinsX_phoqgX, axis_phoqgX_min, axis_phoqgX_max, nBinsX_phi, 7 * TMath::Pi() / 8, TMath::Pi()+1e-12);

        h_phoqgDeta[i] = new TH1D(Form("h_pho%sDeta", partonTypesStr[i].c_str()),
                Form(";%s;", strPhoPartonDeta.c_str()),
                nBinsX_eta, axis_eta_min, 1.5*axis_eta_max);

        h_phoqgDphi[i] = new TH1D(Form("h_pho%sDphi", partonTypesStr[i].c_str()),
                Form(";%s;", strPhoPartonDphi.c_str()),
                nBinsX_phi, 0, TMath::Pi()+1e-12);

        h_phoqgX[i] = new TH1D(Form("h_pho%sX", partonTypesStr[i].c_str()),
                Form(";%s;", strPhoPartonX.c_str()),
                nBinsX_phoqgX, axis_phoqgX_min, axis_phoqgX_max);

        h_phoqgNjet[i] = new TH1D(Form("h_pho%sNjet", partonTypesStr[i].c_str()),
                Form(";%s;", "nJet"),
                10, 0, 10);

        h2_phoEta_qgEta[i] = new TH2D(Form("h2_phoEta_%sEta", partonTypesStr[i].c_str()),
                Form(";%s;%s", strPhoEta.c_str(), strPartonEta.c_str()),
                nBinsX_eta, -1*axis_eta_max, axis_eta_max, nBinsX_eta, -1*axis_eta_max, axis_eta_max);

        h2_phoPhi_qgPhi[i] = new TH2D(Form("h2_phoPhi_%sPhi", partonTypesStr[i].c_str()),
                Form(";%s;%s", strPhoPhi.c_str(), strPartonPhi.c_str()),
                nBinsX_phi, -TMath::Pi(), TMath::Pi(), nBinsX_phi, -TMath::Pi(), TMath::Pi());

        h2_qscale_phoqgDeta[i] = new TH2D(Form("h2_qscale_pho%sDeta", partonTypesStr[i].c_str()),
                Form(";%s;Q", strPhoPartonDeta.c_str()),
                nBinsX_eta, axis_eta_min, axis_eta_max, nBinsX_pt, axis_pt_min, axis_pt_max);

        h_phoPt_qgRatio[i] = new TH1D(Form("h_phoPt_%sRatio", partonTypesStr[i].c_str()),
                Form(";%s;", strPhoPt.c_str()),
                nBinsX_pt, axis_pt_min, axis_pt_max);

        for (int j = 0; j < kN_PARTICLETYPES; ++j) {

            for (int iFF = 0; iFF < kN_FFDEFNS; ++iFF) {

                std::string pVecStr = "#bf{p}^{jet}";
                std::string ptrkVecStr = Form("#bf{p}^{%s}", particleTypesLabel[j].c_str());
                std::string ffStr = Form("#xi^{jet} = ln (|%s|^{2} / %s #bf{#dot} %s)",
                                         pVecStr.c_str(), ptrkVecStr.c_str(), pVecStr.c_str());
                if (iFF == kxipho) {
                    pVecStr = Form("#bf{p}^{%s}_{T}", strPho.c_str());
                    ptrkVecStr = Form("#bf{p}^{%s}_{T}", particleTypesLabel[j].c_str());
                    ffStr = Form("#xi^{%s}_{T} = ln ( -|%s|^{2} / %s #bf{#dot} %s)", strPho.c_str(),
                            pVecStr.c_str(), ptrkVecStr.c_str(), pVecStr.c_str());
                }

                h_ff[i][j][iFF] = new TH1D(Form("h_%s_%s_%s", ffDefnsStr[iFF].c_str(), partonTypesStr[i].c_str(), particleTypesStr[j].c_str()),
                        Form("%s jet - particles are %s;%s;", partonTypesLabel[i].c_str(), particleTypesLabel[j].c_str(), ffStr.c_str()),
                        nBinsX_xijet, axis_xijet_min, axis_xijet_max);

                for (int k = 0; k < kN_PTSORTING; ++k) {

                    h_ff_ptSort[i][j][iFF][k] = new TH1D(Form("h_%s_%s_%s_%s",
                            ffDefnsStr[iFF].c_str(), partonTypesStr[i].c_str(), particleTypesStr[j].c_str(), ptSortingsStr[k].c_str()),
                            Form("%s jet - particles are %s, %s;%s;",
                            partonTypesLabel[i].c_str(), particleTypesLabel[j].c_str(), ptSortingsLabel[k].c_str(), ffStr.c_str()),
                            nBinsX_xijet, axis_xijet_min, axis_xijet_max);

                    if (j == kFinal || j == kFinalCh) {
                        h_ff_ptSort_daughter[i][j][iFF][k] = new TH1D(Form("h_%s_%s_%s_%s_daughter",
                                ffDefnsStr[iFF].c_str(), partonTypesStr[i].c_str(), particleTypesStr[j].c_str(), ptSortingsStr[k].c_str()),
                                Form("%s jet - particles are %s, %s;%s;",
                                partonTypesLabel[i].c_str(), particleTypesLabel[j].c_str(), ptSortingsLabel[k].c_str(), ffStr.c_str()),
                                nBinsX_xijet, axis_xijet_min, axis_xijet_max);
                    }
                }
            }


            h_jetshape[i][j] = new TH1D(Form("h_jetshape_%s_%s", partonTypesStr[i].c_str(), particleTypesStr[j].c_str()),
                                Form("%s jet - particles are %s;r;#rho(r)", partonTypesLabel[i].c_str(), particleTypesLabel[j].c_str()),
                                nBinsX_js, axis_js_min, axis_js_max);

            for (int k = 0; k < kN_PTSORTING; ++k) {

                h_jetshape_ptSort[i][j][k] = new TH1D(Form("h_jetshape_%s_%s_%s",
                        partonTypesStr[i].c_str(), particleTypesStr[j].c_str(), ptSortingsStr[k].c_str()),
                        Form("%s jet - particles are %s, %s;r;#rho(r)",
                        partonTypesLabel[i].c_str(), ptSortingsLabel[k].c_str(), particleTypesLabel[j].c_str()),
                        nBinsX_js, axis_js_min, axis_js_max);

                if (j == kFinal || j == kFinalCh) {
                    h_jetshape_ptSort_daughter[i][j][k] = new TH1D(Form("h_jetshape_%s_%s_%s_daughter",
                            partonTypesStr[i].c_str(), particleTypesStr[j].c_str(), ptSortingsStr[k].c_str()),
                            Form("%s jet - particles are %s, %s;r;#rho(r)",
                            partonTypesLabel[i].c_str(), ptSortingsLabel[k].c_str(), particleTypesLabel[j].c_str()),
                            nBinsX_js, axis_js_min, axis_js_max);
                }
            }
        }
    }

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
        jetTree->GetEntry(iEvent);

        // jet analysis
        // outgoing particles are at index 5 and 6
        int ip1 = 5;
        int ip2 = 6;
        int iPhoH = -1;
        if ((isGamma((*event)[ip1])) && (isParton((*event)[ip2])))
            iPhoH = ip1;
        else if ((isGamma((*event)[ip2])) && (isParton((*event)[ip1])))
            iPhoH = ip2;
        if (iPhoH == -1) continue;

        int iParton = (iPhoH == ip1) ? ip2 : ip1;
        int iQG = (isQuark((*event)[iParton])) ? kQuark : kGluon;

        int iPho = iPhoH;
        if (iStatusPhoton == kOut) {
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

            iPho = iOutPho;
        }

        eventsAnalyzed++;

        double phoPt = (*event)[iPho].pT();
        double phoEta = (*event)[iPho].eta();
        double phoPhi = (*event)[iPho].phi();

        TLorentzVector vecTPho;
        vecTPho.SetPtEtaPhiM(phoPt, 0, phoPhi, 0);

        if (!(phoPt > 60)) continue;
        if (!(TMath::Abs(phoEta) < 1.44)) continue;

        h_phoPt->Fill(phoPt);
        h_phoEta->Fill(TMath::Abs(phoEta));
        h2_phoEta_phoPt->Fill(TMath::Abs(phoEta), phoPt);
        h2_qscale_phoPt->Fill(phoPt, event->scale());
        h2_qscale_phoEta->Fill(TMath::Abs(phoEta), event->scale());

        std::vector<int> typesQG = {kInclusive, iQG};
        int nTypesQG = typesQG.size();

        for (int j = 0; j < nTypesQG; ++j) {
            int k = typesQG[j];
            h_phoPt_qg[k]->Fill(phoPt);
        }

        int njetaway = 0;
        for (int i = 0; i < fjt.nJet; ++i) {

            double jetpt = (*fjt.jetpt)[i];
            double jeteta = (*fjt.jeteta)[i];
            double jetphi = (*fjt.jetphi)[i];

            if (!(jetpt > 30))  continue;
            if (!(TMath::Abs(jeteta) < 1.6)) continue;
            if (getDR2(phoEta, phoPhi, jeteta, jetphi) < 0.64)  continue;

            double detajg = TMath::Abs(phoEta - jeteta);
            double dphijg = std::acos(cos(phoPhi - jetphi));
            double xjg = jetpt / phoPt;

            for (int j = 0; j < nTypesQG; ++j) {
                int k = typesQG[j];
                h_phoqgDphi[k]->Fill(dphijg);
            }

            if (!(std::acos(cos(phoPhi - jetphi)) > 7 * TMath::Pi() / 8)) continue;
            njetaway++;

            for (int jQG = 0; jQG < nTypesQG; ++jQG) {
                int k = typesQG[jQG];
                h_qgPt[k]->Fill(jetpt);
                h_qgEta[k]->Fill(TMath::Abs(jeteta));
                h2_qgEta_qgPt[k]->Fill(TMath::Abs(jeteta), jetpt);
                h2_phoqgX_phoPt[k]->Fill(xjg, phoPt);
                h2_phoqgX_phoEta[k]->Fill(xjg, phoEta);
                h2_phoqgX_phoqgDeta[k]->Fill(xjg, detajg);
                h2_phoqgX_phoqgDphi[k]->Fill(xjg, dphijg);
                h_phoqgDeta[k]->Fill(detajg);
                h_phoqgX[k]->Fill(xjg);
                h2_phoEta_qgEta[k]->Fill(phoEta, jeteta);
                h2_phoPhi_qgPhi[k]->Fill(phoPhi, jetphi);
                h2_qscale_phoqgDeta[k]->Fill(detajg, event->scale());
                h_phoPt_qgRatio[k]->Fill(phoPt);
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
                        if (!(*eventParticle)[j].isFinal()) continue;
                    }
                    else if (iPartType == PARTICLETYPES::kFinalCh) {
                        if (!((*eventParticle)[j].isFinal() && isCharged((*eventParticle)[j], pythia.particleData))) continue;
                    }
                    else if (iPartType == PARTICLETYPES::kPartonHard) {
                        int iOrig = (*eventParticle)[j].mother1();
                        if (!(isAncestor(eventAll, iOrig, 5) || isAncestor(eventAll, iOrig, 6))) continue;
                    }

                    if ((!(*eventParticle)[j].pT() > 1)) continue;

                    double partPt = (*eventParticle)[j].pT();
                    double partEta = (*eventParticle)[j].eta();
                    double partPhi = (*eventParticle)[j].phi();

                    double dR_jet_particle = getDR(jeteta, jetphi, partEta, partPhi);
                    for (int jQG = 0; jQG < nTypesQG; ++jQG) {
                        int k = typesQG[jQG];
                        h_jetshape[k][iPartType]->Fill(dR_jet_particle, partPt / jetpt);
                    }
                    if (dR_jet_particle < jetR) {
                        // consider only pairs inside jet cone
                        pairs_pt_index_js.push_back(std::make_pair(partPt, j));
                    }

                    if (!(dR_jet_particle < jetR))  continue;

                    for (int iFF = 0; iFF < kN_FFDEFNS; ++iFF) {

                        double z = 0;
                        TLorentzVector vecPart;
                        if (iFF == kxijet) {
                            vecPart.SetPtEtaPhiM(partPt, partEta, partPhi, 0);
                            double angle = vecJet.Angle(vecPart.Vect());
                            z = vecPart.P() * cos(angle) / vecJet.P();
                        }
                        else if (iFF == kxipho) {
                            vecPart.SetPtEtaPhiM(partPt, 0, partPhi, 0);
                            double angle = vecTPho.Angle(vecPart.Vect());
                            z = partPt * fabs(cos(angle)) / phoPt;
                        }
                        double xi = log(1.0/z);

                        for (int jQG = 0; jQG < nTypesQG; ++jQG) {
                            int k = typesQG[jQG];

                            h_ff[k][iPartType][iFF]->Fill(xi);
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
                            h_jetshape_ptSort[k][iPartType][kPt1st]->Fill(dR_jet_particle, partPt / jetpt);
                        }
                        else if (jPair == nPairs - 2) {
                            h_jetshape_ptSort[k][iPartType][kPt2nd]->Fill(dR_jet_particle, partPt / jetpt);
                        }
                        else if (jPair == nPairs - 3) {
                            h_jetshape_ptSort[k][iPartType][kPt3rd]->Fill(dR_jet_particle, partPt / jetpt);
                        }
                        else {
                            h_jetshape_ptSort[k][iPartType][kPt4thPlus]->Fill(dR_jet_particle, partPt / jetpt);
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
                                    if (!(*eventAll)[iChild].isFinal()) continue;
                                }
                                else if (childType == PARTICLETYPES::kFinalCh) {
                                    if (!((*eventAll)[iChild].isFinal() && isCharged((*eventAll)[iChild], pythia.particleData))) continue;
                                }

                                if ((!(*eventAll)[iChild].pT() > 1)) continue;

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
                                        h_jetshape_ptSort_daughter[k][childType][kPt1st]->Fill(dR_jet_child, childPt / jetpt);
                                    }
                                    else if (jPair == nPairs - 2) {
                                        h_jetshape_ptSort_daughter[k][childType][kPt2nd]->Fill(dR_jet_child, childPt / jetpt);
                                    }
                                    else if (jPair == nPairs - 3) {
                                        h_jetshape_ptSort_daughter[k][childType][kPt3rd]->Fill(dR_jet_child, childPt / jetpt);
                                    }
                                    else {
                                        h_jetshape_ptSort_daughter[k][childType][kPt4thPlus]->Fill(dR_jet_child, childPt / jetpt);
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

                        double z = 0;
                        TLorentzVector vecPart;
                        if (iFF == kxijet) {
                            vecPart.SetPtEtaPhiM(partPt, partEta, partPhi, 0);
                            double angle = vecJet.Angle(vecPart.Vect());
                            z = vecPart.P() * cos(angle) / vecJet.P();
                        }
                        else if (iFF == kxipho) {
                            vecPart.SetPtEtaPhiM(partPt, 0, partPhi, 0);
                            double angle = vecTPho.Angle(vecPart.Vect());
                            z = partPt * fabs(cos(angle)) / phoPt;
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
                                    if (!(*eventAll)[iChild].isFinal()) continue;
                                }
                                else if (childType == PARTICLETYPES::kFinalCh) {
                                    if (!((*eventAll)[iChild].isFinal() && isCharged((*eventAll)[iChild], pythia.particleData))) continue;
                                }

                                if ((!(*eventAll)[iChild].pT() > 1)) continue;

                                double childPt = (*eventAll)[iChild].pT();
                                double childEta = (*eventAll)[iChild].eta();
                                double childPhi = (*eventAll)[iChild].phi();

                                double dR_jet_child = getDR(jeteta, jetphi, childEta, childPhi);
                                if (!(dR_jet_child < jetR))  continue;

                                // One final particle can be daughter of multiple partons. Use a particle only once.
                                // Priority is given to mother parton with lower pt.
                                if (std::find(usedDaughterIndices_ff[childType].begin(), usedDaughterIndices_ff[childType].end(), iChild) != usedDaughterIndices_ff[childType].end()) continue;
                                usedDaughterIndices_ff[childType].push_back(iChild);

                                for (int iFF = 0; iFF < kN_FFDEFNS; ++iFF) {

                                    double z = 0;
                                    TLorentzVector vecPart;
                                    if (iFF == kxijet) {
                                        vecPart.SetPtEtaPhiM(childPt, childEta, childPhi, 0);
                                        double angle = vecJet.Angle(vecPart.Vect());
                                        z = vecPart.P() * cos(angle) / vecJet.P();
                                    }
                                    else if (iFF == kxipho) {
                                        vecPart.SetPtEtaPhiM(childPt, 0, childPhi, 0);
                                        double angle = vecTPho.Angle(vecPart.Vect());
                                        z = childPt * fabs(cos(angle)) / phoPt;
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

            h_phoqgNjet[k]->Fill(njetaway);
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

    h_phoPt->Scale(1./h_phoPt->Integral(), "width");
    h_phoEta->Scale(1./h_phoEta->Integral(), "width");

    for (int i = 0; i < kN_PARTONTYPES; ++i) {

        double nPho = h_phoPt_qg[i]->GetEntries();
        double nJet = h_qgPt[i]->GetEntries();

        h_phoPt_qg[i]->Scale(1./h_phoPt_qg[i]->Integral(), "width");

        h_qgPt[i]->Scale(1./nPho, "width");
        h_qgEta[i]->Scale(1./nPho, "width");
        h_phoqgDeta[i]->Scale(1./nPho, "width");
        h_phoqgDphi[i]->Scale(1./nPho, "width");
        h_phoqgX[i]->Scale(1./nPho, "width");
        h_phoqgNjet[i]->Scale(1./nPho, "width");

        for (int j = 0; j < kN_PARTICLETYPES; ++j) {

            for (int iFF = 0; iFF < kN_FFDEFNS; ++iFF) {
                h_ff[i][j][iFF]->Scale(1./nJet, "width");

                for (int k = 0; k < kN_PTSORTING; ++k) {
                    h_ff_ptSort[i][j][iFF][k]->Scale(1./nJet, "width");

                    if (j == kFinal || j == kFinalCh) {
                        h_ff_ptSort_daughter[i][j][iFF][k]->Scale(1./nJet, "width");
                    }
                }
            }

            h_jetshape_normJet[i][j] = (TH1D*)h_jetshape[i][j]->Clone(Form("%s_normJet", h_jetshape[i][j]->GetName()));

            double intJetCone = h_jetshape[i][j]->Integral(1, h_jetshape[i][j]->FindBin(jetR)-1);
            h_jetshape[i][j]->Scale(1./intJetCone, "width");
            h_jetshape_normJet[i][j]->Scale(1./nJet, "width");

            for (int k = 0; k < kN_PTSORTING; ++k) {

                h_jetshape_ptSort_normJet[i][j][k] = (TH1D*)h_jetshape_ptSort[i][j][k]->Clone(
                        Form("%s_normJet", h_jetshape_ptSort[i][j][k]->GetName()));

                h_jetshape_ptSort[i][j][k]->Scale(1./intJetCone, "width");
                h_jetshape_ptSort_normJet[i][j][k]->Scale(1./nJet, "width");

                if (j == kFinal || j == kFinalCh) {
                    h_jetshape_ptSort_daughter_normJet[i][j][k] = (TH1D*)h_jetshape_ptSort_daughter[i][j][k]->Clone(
                            Form("%s_normJet", h_jetshape_ptSort_daughter[i][j][k]->GetName()));

                    h_jetshape_ptSort_daughter[i][j][k]->Scale(1./intJetCone, "width");
                    h_jetshape_ptSort_daughter_normJet[i][j][k]->Scale(1./nJet, "width");
                }
            }
        }

        if (i != kInclusive) {
            h_phoPt_qgRatio[i]->Divide(h_phoPt_qgRatio[kInclusive]);
        }
    }

    outputFile->Write("", TObject::kOverwrite);
    std::cout << "Closing the output file" << std::endl;
    outputFile->Close();

    std::cout << "running photonJetAna() - END" << std::endl;
}

int main(int argc, char* argv[]) {

    if (argc == 6) {
        photonJetAna(argv[1], argv[2], argv[3], argv[4], std::atoi(argv[5]));
        return 0;
    }
    else if (argc == 5) {
        photonJetAna(argv[1], argv[2], argv[3], argv[4]);
        return 0;
    }
    else if (argc == 4) {
        photonJetAna(argv[1], argv[2], argv[3]);
        return 0;
    }
    else if (argc == 3) {
        photonJetAna(argv[1], argv[2]);
        return 0;
    }
    else if (argc == 2) {
        photonJetAna(argv[1]);
        return 0;
    }
    else {
        std::cout << "Usage : \n" <<
                "./photonJetAna.exe <eventFileName> <jetFileName> <jetTreeName> <outputFileName>"
                << std::endl;
        return 1;
    }
}
