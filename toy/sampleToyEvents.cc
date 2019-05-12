#include "TROOT.h"
#include "TTree.h"
#include "TFile.h"
#include "TSystem.h"
#include "TVirtualPad.h"
#include "TApplication.h"
#include "TH1.h"
#include "TH1D.h"
#include "TH2D.h"
#include "TF1.h"
#include "TRandom3.h"
#include "TMath.h"

#include "../utilities/particleTree.h"
#include "../utilities/physicsUtil.h"
#include "../utilities/systemUtil.h"
#include "../utilities/ArgumentParser.h"

#include <iostream>
#include <iomanip>
#include <string>
#include <vector>

std::vector<std::string> argOptions;

/*
 * code to sample toy AA events (in particular Hydjet) using input centrality, multiplicity, pt, eta distibutions
 */
void sampleToyEvents(int mode = 0, std::string outputFileName = "sampleHydjet_out.root",
                       int nEvents = 10);

void sampleToyEvents(int mode, std::string outputFileName,
                       int nEvents)
{
    std::cout << "running sampleToyEvents()" << std::endl;

    std::cout << "##### Parameters #####" << std::endl;
    std::cout << "mode = " << mode << std::endl;
    std::cout << "outputFileName = " << outputFileName.c_str() << std::endl;
    std::cout << "nEvents = " << nEvents << std::endl;
    std::cout << "##### Parameters - END #####" << std::endl;

    enum MODES {
        k_sampleHydjet,
        k_sampleThermalPt,
        kN_MODES
    };
    std::string modeLabels[kN_MODES] = {"Hydjet", "Thermal"};
    std::cout << "Sampling mode is " << modeLabels[mode] << std::endl;

    std::string inputFileName = (ArgumentParser::ParseOptionInputSingle("--inputFile", argOptions).size() > 0) ?
            ArgumentParser::ParseOptionInputSingle("--inputFile", argOptions).c_str() : "NULL";

    int minCent = (ArgumentParser::ParseOptionInputSingle("--minCent", argOptions).size() > 0) ?
            std::atoi(ArgumentParser::ParseOptionInputSingle("--minCent", argOptions).c_str()) : 0;
    int maxCent = (ArgumentParser::ParseOptionInputSingle("--maxCent", argOptions).size() > 0) ?
            std::atoi(ArgumentParser::ParseOptionInputSingle("--maxCent", argOptions).c_str()) : 100;

    int multCh = (ArgumentParser::ParseOptionInputSingle("--multCh", argOptions).size() > 0) ?
            std::atoi(ArgumentParser::ParseOptionInputSingle("--multCh", argOptions).c_str()) : -1;
    double dNdEta = (ArgumentParser::ParseOptionInputSingle("--dNdEta", argOptions).size() > 0) ?
                    std::atof(ArgumentParser::ParseOptionInputSingle("--dNdEta", argOptions).c_str()) : -1;
    double maxEta = (ArgumentParser::ParseOptionInputSingle("--maxEta", argOptions).size() > 0) ?
                        std::atof(ArgumentParser::ParseOptionInputSingle("--maxEta", argOptions).c_str()) : 3;
    double meanPt = (ArgumentParser::ParseOptionInputSingle("--meanPt", argOptions).size() > 0) ?
                std::atof(ArgumentParser::ParseOptionInputSingle("--meanPt", argOptions).c_str()) : 0;
    double minPt = (ArgumentParser::ParseOptionInputSingle("--minPt", argOptions).size() > 0) ?
            std::atof(ArgumentParser::ParseOptionInputSingle("--minPt", argOptions).c_str()) : 0;

    std::string eventInfoTreeName = (ArgumentParser::ParseOptionInputSingle("--eventInfoTree", argOptions).size() > 0) ?
            ArgumentParser::ParseOptionInputSingle("--eventInfoTree", argOptions).c_str() : "evtInfo";
    std::string partTreeName = (ArgumentParser::ParseOptionInputSingle("--particleTree", argOptions).size() > 0) ?
            ArgumentParser::ParseOptionInputSingle("--particleTree", argOptions).c_str() : "evt";

    int rndSeedCent = (ArgumentParser::ParseOptionInputSingle("--rndSeedCent", argOptions).size() > 0) ?
            std::atoi(ArgumentParser::ParseOptionInputSingle("--rndSeedCent", argOptions).c_str()) : 12345;
    int rndSeedParticle = (ArgumentParser::ParseOptionInputSingle("--rndSeedParticle", argOptions).size() > 0) ?
            std::atoi(ArgumentParser::ParseOptionInputSingle("--rndSeedParticle", argOptions).c_str()) : 6789;

    std::cout << "##### Optional Arguments #####" << std::endl;
    std::cout << "inputFile = " << inputFileName.c_str() << std::endl;
    std::cout << "minCent = " << minCent << std::endl;
    std::cout << "maxCent = " << maxCent << std::endl;
    std::cout << "multCh = " << multCh << std::endl;
    std::cout << "dNdEta = " << dNdEta << std::endl;
    std::cout << "meanPt = " << meanPt << std::endl;
    std::cout << "minPt = " << minPt << std::endl;
    std::cout << "eventInfoTree = " << eventInfoTreeName.c_str() << std::endl;
    std::cout << "partTree = " << partTreeName.c_str() << std::endl;
    std::cout << "rndSeedCent = " << rndSeedCent << std::endl;
    std::cout << "rndSeedParticle = " << rndSeedParticle << std::endl;
    std::cout << "##### Optional Arguments - END #####" << std::endl;

    if (multCh > 0 && dNdEta > 0) {
        std::cout << "ERROR : Conflicting options. Cannot have both multCh and dNdEta non-zero. At most one of them can be non-zero." << std::endl;
        std::cout << "multCh = " << multCh << std::endl;
        std::cout << "dNdEta = " << dNdEta << std::endl;
        std::cout << "Exiting" << std::endl;
        return;
    }

    // Set up the ROOT TFile and TTree.
    TFile* inputFile = 0;
    if (inputFileName != "NULL") {
        inputFile = TFile::Open(inputFileName.c_str(),"READ");
    }

    // TH1 objects
    TH1::SetDefaultSumw2();

    int nCharge = 0;
    std::vector<int> centMins;
    std::vector<int> centMaxs;
    int nCent = 0;

    int n_hiBinVSngen = 0;
    int n_etaVSpt = 0;

    std::vector<std::string> h2DPaths_hiBinVSngen;
    std::vector<std::string> h2DPaths_etaVSpt;

    std::vector<TH2D*> vecH2D_hiBinVSngen;
    std::vector<TH2D*> vecH2D_etaVSpt;

    if (mode == k_sampleHydjet) {
        std::vector<std::string> strCharge = {"charged", "neutral"};
        nCharge = strCharge.size();
        std::vector<std::string> strCent = {"cent010", "cent1030", "cent3050", "cent50100"};
        centMins = {0, 10, 30, 50};
        centMaxs = {10, 30, 50, 100};
        nCent = strCent.size();

        n_hiBinVSngen = nCharge;
        n_etaVSpt = nCharge*nCent;

        h2DPaths_hiBinVSngen.resize(n_hiBinVSngen);
        h2DPaths_etaVSpt.resize(n_etaVSpt);

        for (int i = 0; i < nCharge; ++i) {
            h2DPaths_hiBinVSngen[i] = Form("h2D_hiBinVSngen_%s", strCharge[i].c_str());
            for (int j = 0; j < nCent; ++j) {
                h2DPaths_etaVSpt[i + nCharge*j] = Form("h2D_etaVSpt_%s_%s", strCent[j].c_str(), strCharge[i].c_str());
            }
        }

        vecH2D_hiBinVSngen.resize(n_hiBinVSngen);
        for (int i = 0; i < n_hiBinVSngen; ++i) {
            vecH2D_hiBinVSngen[i] = 0;
            vecH2D_hiBinVSngen[i] = (TH2D*)inputFile->Get(h2DPaths_hiBinVSngen[i].c_str());
        }

        vecH2D_etaVSpt.resize(n_etaVSpt);
        for (int i = 0; i < n_etaVSpt; ++i) {
            vecH2D_etaVSpt[i] = 0;
            vecH2D_etaVSpt[i] = (TH2D*)inputFile->Get(h2DPaths_etaVSpt[i].c_str());
        }

        // remove the centralities which are not in the desired range
        for (int i = 0; i < n_hiBinVSngen; ++i) {
            for (int iBinY = 1; iBinY <= vecH2D_hiBinVSngen[i]->GetNbinsX(); ++iBinY) {
                double hiBinTmp = vecH2D_hiBinVSngen[i]->GetYaxis()->GetBinLowEdge(iBinY);

                if (!(minCent*2 <= hiBinTmp && hiBinTmp < maxCent*2)) {
                    for (int iBinX = 1; iBinX <= vecH2D_hiBinVSngen[i]->GetNbinsX(); ++iBinX) {
                        vecH2D_hiBinVSngen[i]->SetBinContent(iBinX, iBinY, 0);
                        vecH2D_hiBinVSngen[i]->SetBinError(iBinX, iBinY, 0);
                    }
                }
            }
        }
    }

    TF1* fncPt = 0;
    std::vector<int> mults;
    if (mode == k_sampleThermalPt) {
        // taken from https://github.com/JetQuenchingTools/JetToyHI/blob/c80710caee0c3687707e5d676f3a97dda7c73a25/include/thermalEvent.hh#L45
        fncPt = new TF1("fncPt","[0]*TMath::Power([1], 2)*x*TMath::Exp(-[1]*x)", 0.2, 200);
        fncPt->SetParNames("Amplitude", "b (GeV/c)^{-1}");
        fncPt->SetParameters(1., 2./meanPt);

        int multNeutral = 0;
        double ratioChNeutral = 0.5;
        if (multCh > -1) {
            multNeutral = multCh * ratioChNeutral;
            mults = {multCh, multNeutral};
        }
        else if (dNdEta > -1) {
            int nTmp = (int) (dNdEta*2*maxEta);
            multNeutral = nTmp * ratioChNeutral;
            mults = {nTmp, multNeutral};
        }
        nCharge = mults.size();
    }

    std::vector<TH1D*> vecH1D_ngen;
    vecH1D_ngen.resize(nCharge);
    //std::fill_n(vecH1D_ngen.begin(), nCharge, 0);

    TFile* outputFile = new TFile(outputFileName.c_str(), "UPDATE");

    TTree* eventInfoTree = new TTree(eventInfoTreeName.c_str(), Form("Info about %s events with Cent:%d-%d", modeLabels[mode].c_str(),
                                                                                                             minCent, maxCent));
    int hiBin;
    eventInfoTree->Branch("hiBin", &hiBin);

    TTree* partTree = new TTree(partTreeName.c_str(), Form("%s particles from Cent:%d-%d", modeLabels[mode].c_str(),
                                                                                           minCent, maxCent));
    particleTree partt;
    partt.branchTree(partTree);

    TRandom3 rand1(rndSeedCent);

    TRandom3 rand2(rndSeedParticle);

    gRandom->SetSeed(rndSeedParticle);
    int eventsAnalyzed = 0;
    std::cout << "nEvents = " << nEvents << std::endl;
    std::cout << "Loop STARTED" << std::endl;
    for (int iEvent = 0; iEvent < nEvents; ++iEvent) {

        if (iEvent % 10000 == 0)  {
          std::cout << "current entry = " <<iEvent<<" out of "<<nEvents<<" : "<<std::setprecision(2)<<(double)iEvent/nEvents*100<<" %"<<std::endl;
        }

        hiBin = (int)std::floor(rand1.Uniform(minCent*2, maxCent*2));

        partt.clearEvent();

        eventsAnalyzed++;

        if (mode == k_sampleHydjet) {

            int iCent4 = 0;
            for (int i = 0; i < nCent; ++i) {
                if (hiBin < centMaxs[i]*2) {
                    iCent4 = i;
                    break;
                }
            }

            for (int iCh = 0; iCh < nCharge; ++iCh) {
                int binY = vecH2D_hiBinVSngen[iCh]->GetYaxis()->FindBin(hiBin);

                vecH1D_ngen[iCh] = (TH1D*)vecH2D_hiBinVSngen[iCh]->ProjectionX(Form("vecH1D_ngen_%d", iCh), binY, binY);
                int iHist_etaVSpt = iCh + iCent4*n_hiBinVSngen;

                int ngen = (int)std::floor(vecH1D_ngen[iCh]->GetRandom());
                for (int i = 0; i < ngen; ++i) {
                    double eta;
                    double pt;
                    vecH2D_etaVSpt[iHist_etaVSpt]->GetRandom2(pt, eta);

                    if (pt < minPt) continue;

                    double phi = rand2.Uniform(-1*TMath::Pi(), TMath::Pi());

                    partt.pt->push_back(pt);
                    partt.eta->push_back(eta);
                    partt.phi->push_back(phi);
                    partt.chg->push_back(((iCh == 0) ? 1 : 0));
                    partt.n++;
                }
            }
        }
        else if (mode == k_sampleThermalPt) {
            for (int iCh = 0; iCh < nCharge; ++iCh) {

                for (int i = 0; i < mults[iCh]; ++i) {

                    double pt = fncPt->GetRandom();
                    if (pt < minPt) continue;

                    double eta = rand2.Uniform(-maxEta, maxEta);
                    double phi = rand2.Uniform(-1*TMath::Pi(), TMath::Pi());

                    partt.pt->push_back(pt);
                    partt.eta->push_back(eta);
                    partt.phi->push_back(phi);

                    partt.chg->push_back(((iCh == 0) ? 1 : 0));
                    partt.n++;
                }
            }
        }

        eventInfoTree->Fill();
        partTree->Fill();
    }
    std::cout << "Loop ENDED" << std::endl;
    std::cout << "eventsAnalyzed = " << eventsAnalyzed << std::endl;

    for (int i = 0; i < (int)vecH1D_ngen.size(); ++i) {
        if (vecH1D_ngen[i] != 0) {
            vecH1D_ngen[i]->Delete();
        }
    }

    if (inputFile != 0) {
        std::cout<<"Closing the input file"<<std::endl;
        inputFile->Close();
    }

    outputFile->Write("", TObject::kOverwrite);
    std::cout<<"Closing the output file"<<std::endl;
    outputFile->Close();

    std::cout << "running sampleToyEvents() - END" << std::endl;
}

int main(int argc, char* argv[]) {

    std::vector<std::string> argStr = ArgumentParser::ParseParameters(argc, argv);
    int nArgStr = argStr.size();

    argOptions = ArgumentParser::ParseOptions(argc, argv);

    if (nArgStr == 4) {
        sampleToyEvents(std::atoi(argv[1]), argv[2], std::atoi(argv[3]));
        return 0;
    }
    else if (nArgStr == 3) {
        sampleToyEvents(std::atoi(argv[1]), argv[2]);
        return 0;
    }
    else if (nArgStr == 2) {
        sampleToyEvents(std::atoi(argv[1]));
        return 0;
    }
    else {
        std::cout << "Usage : \n" <<
                "./sampleToyEvents.exe <mode> <outputFileName> <nEvents>"
                << std::endl;
        std::cout << "Options are" << std::endl;
        std::cout << "inputFile=<file containing distributions to be sampled>" << std::endl;
        std::cout << "minCent=<minimum centrality>" << std::endl;
        std::cout << "maxCent=<maximum centrality>" << std::endl;
        std::cout << "multCh=<number of charged particles>" << std::endl;
        std::cout << "dNdEta=<number of charged particles per unit eta>" << std::endl;
        std::cout << "maxEta=<maximum |eta| of particles>" << std::endl;
        std::cout << "meanPt=<average of pt spectrum to be sampled>" << std::endl;
        std::cout << "minPt=<minimum pT to be written>" << std::endl;
        std::cout << "eventInfoTree=<path to tree containing event information>" << std::endl;
        std::cout << "partTree=<path to tree containing particles>" << std::endl;
        std::cout << "rndSeedCent=<random number seed reserved for centrality>" << std::endl;
        std::cout << "rndSeedParticle=<random number seed reserved for particles>" << std::endl;

        return 1;
    }
}
