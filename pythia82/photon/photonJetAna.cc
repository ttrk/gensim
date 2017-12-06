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
#include <string>
#include <vector>
#include "../../utilities/physicsUtil.h"

void photonJetAna(std::string eventFileName = "promptPhoton.root", std::string jetFileName = "jets.root",
                  std::string jetTreeName = "ak3jets", std::string outputFileName = "photonJetAna_out.root");

void photonJetAna(std::string eventFileName, std::string jetFileName, std::string jetTreeName, std::string outputFileName)
{
    std::cout << "running photonJetAna()" << std::endl;

    std::cout << "##### Parameters #####" << std::endl;
    std::cout << "eventFileName = " << eventFileName.c_str() << std::endl;
    std::cout << "jetFileName = " << jetFileName.c_str() << std::endl;
    std::cout << "jetTreeName = " << jetTreeName.c_str() << std::endl;
    std::cout << "outputFileName = " << outputFileName.c_str() << std::endl;
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
        kHadron,
        kHadronCh,
        kParton,
        kPartonHard,
        kN_PARTICLETYPES
    };
    std::string particleTypesStr[kN_PARTICLETYPES] = {"hadron", "hadronCh", "parton", "partonHard"};
    std::string particleTypesLabel[kN_PARTICLETYPES] = {"h^{0,#pm}", "h^{#pm}", "q/g", "q/g"};
    int nBinsX_xijet = 10;
    double axis_xijet_min = 0;
    double axis_xijet_max = 5;

    double axis_js_min = 0;
    double axis_js_max = 1.0;
    int nBinsX_js = axis_js_max / 0.05;

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
    TH2D* h2_phoEta_qgEta[kN_PARTONTYPES];
    TH2D* h2_phoPhi_qgPhi[kN_PARTONTYPES];
    TH2D* h2_qscale_phoqgDeta[kN_PARTONTYPES];
    // photon histograms split for parton types
    TH1D* h_phoPt_qgRatio[kN_PARTONTYPES];
    // jet FF histograms split by particle types
    TH1D* h_xijet[kN_PARTONTYPES][kN_PARTICLETYPES];
    TH1D* h_jetshape[kN_PARTONTYPES][kN_PARTICLETYPES];
    TH1D* h_jetshape_normJet[kN_PARTONTYPES][kN_PARTICLETYPES];
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

            std::string pjetVecStr = "#bf{p}^{jet}";
            std::string ptrkVecStr = Form("#bf{p}^{%s}", particleTypesLabel[j].c_str());
            std::string xiJetStr = Form("#xi^{jet} = ln (|%s|^{2} / %s #bf{#dot} %s)",
                                        pjetVecStr.c_str(), ptrkVecStr.c_str(), pjetVecStr.c_str());
            h_xijet[i][j] = new TH1D(Form("h_xijet_%s_%s", partonTypesStr[i].c_str(), particleTypesStr[j].c_str()),
                    Form("%s jet - particles are %s;%s;", partonTypesLabel[i].c_str(), particleTypesLabel[j].c_str(), xiJetStr.c_str()),
                    nBinsX_xijet, axis_xijet_min, axis_xijet_max);

            h_jetshape[i][j] = new TH1D(Form("h_jetshape_%s_%s", partonTypesStr[i].c_str(), particleTypesStr[j].c_str()),
                                Form("%s jet - particles are %s;r;#rho(r)", partonTypesLabel[i].c_str(), particleTypesLabel[j].c_str()),
                                nBinsX_js, axis_js_min, axis_js_max);
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

        treeEvt->GetEntry(iEvent);
        treeEvtParton->GetEntry(iEvent);
        jetTree->GetEntry(iEvent);

        // jet analysis
        // outgoing particles are at index 5 and 6
        int ip1 = 5;
        int ip2 = 6;
        int iPho = -1;
        if ((isGamma((*event)[ip1])) && (isParton((*event)[ip2])))
            iPho = ip1;
        else if ((isGamma((*event)[ip2])) && (isParton((*event)[ip1])))
            iPho = ip2;
        if (iPho == -1) continue;

        eventsAnalyzed++;

        int iParton = (iPho == ip1) ? ip2 : ip1;
        int iQG = (isQuark((*event)[iParton])) ? kQuark : kGluon;

        double phoPt = (*event)[iPho].pT();
        double phoEta = (*event)[iPho].eta();
        double phoPhi = (*event)[iPho].phi();

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

                int eventParticleSize = eventParticle->size();
                for (int j = 0; j < eventParticleSize; ++j) {

                    if (iPartType == PARTICLETYPES::kHadron) {
                        if (!(*eventParticle)[j].isFinal()) continue;
                    }
                    else if (iPartType == PARTICLETYPES::kHadronCh) {
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

                    if (!(dR_jet_particle < jetR))  continue;

                    TLorentzVector vecPart;
                    vecPart.SetPtEtaPhiM(partPt, partEta, partPhi, 0);

                    double angle = vecJet.Angle(vecPart.Vect());
                    double z = vecPart.P() * cos(angle) / vecJet.P();
                    double xi = log(1.0/z);
                    for (int jQG = 0; jQG < nTypesQG; ++jQG) {
                        int k = typesQG[jQG];
                        h_xijet[k][iPartType]->Fill(xi);
                    }
                }
            }
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

        for (int j = 0; j < kN_PARTICLETYPES; ++j) {
            h_xijet[i][j]->Scale(1./nJet, "width");

            h_jetshape_normJet[i][j] = (TH1D*)h_jetshape[i][j]->Clone(Form("%s_normJet", h_jetshape[i][j]->GetName()));

            h_jetshape[i][j]->Scale(1./h_jetshape[i][j]->Integral(1, h_jetshape[i][j]->FindBin(jetR)-1), "width");
            h_jetshape_normJet[i][j]->Scale(1./nJet, "width");
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

    if (argc == 5) {
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
