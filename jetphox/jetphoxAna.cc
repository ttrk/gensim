/*
 * code to analyze jetphox events
 */
#include "TROOT.h"
#include "TTree.h"
#include "TFile.h"
#include "TSystem.h"
#include "TMath.h"
#include "TH1.h"
#include "TH1D.h"
#include "TH2D.h"
#include "TLorentzVector.h"

#include "jetphoxTree.h"

#include <iostream>
#include <iomanip>
#include <string>
#include <vector>

void jetphoxAna(std::string inputFileName = "jetphox_ntuple.root", std::string outputFileName = "jetphoxAna_out.root");

void jetphoxAna(std::string inputFileName, std::string outputFileName)
{
    std::cout << "running jetphoxAna()" << std::endl;

    std::cout << "##### Parameters #####" << std::endl;
    std::cout << "inputFileName = " << inputFileName.c_str() << std::endl;
    std::cout << "outputFileName = " << outputFileName.c_str() << std::endl;
    std::cout << "##### Parameters - END #####" << std::endl;

    // Set up the ROOT TFile and TTree.
    TFile* inputFile = TFile::Open(inputFileName.c_str(),"READ");

    jetphoxTree jpt;
    TTree *treeEvt = (TTree*)inputFile->Get("t2");
    jpt.setupTreeForReading(treeEvt);

    TFile* outputFile = new TFile(outputFileName.c_str(), "RECREATE");

    TH1::SetDefaultSumw2();

    // photon histograms
    int nBinsX_pt = 40;
    double axis_pt_min = 0;
    double axis_pt_max = 200+axis_pt_min;
    int nBinsX_eta = 20;
    double axis_eta_min = -5;
    double axis_eta_max = 5;

    std::string strPho = "#gamma";
    std::string strPhoPt = Form("p_{T}^{%s}", strPho.c_str());
    std::string strPhoEta = Form("#eta^{%s}", strPho.c_str());
    //std::string strPhoPhi = Form("#phi^{%s}", strPho.c_str());

    TH1D* h_phoPt = new TH1D("h_phoPt",Form(";%s;", strPhoPt.c_str()), nBinsX_pt, axis_pt_min, axis_pt_max);
    TH1D* h_phoEta = new TH1D("h_phoEta",Form(";%s;", strPhoEta.c_str()), nBinsX_eta, axis_eta_min, axis_eta_max);

    int eventsAnalyzed = 0;
    int nEvents = treeEvt->GetEntries();
    std::cout << "nEvents = " << nEvents << std::endl;
    std::cout << "Loop STARTED" << std::endl;
    for (int iEvent = 0; iEvent < nEvents; ++iEvent) {

        if (iEvent % 10000 == 0)  {
          std::cout << "current entry = " <<iEvent<<" out of "<<nEvents<<" : "<<std::setprecision(2)<<(double)iEvent/nEvents*100<<" %"<<std::endl;
        }

        treeEvt->GetEntry(iEvent);

        if (!(jpt.ntrack > 0)) continue;

        eventsAnalyzed++;

        double phoPt = std::sqrt(jpt.px[0]*jpt.px[0] + jpt.py[0]*jpt.py[0]);
        double phoEta = 0.5 * std::log((jpt.energy[0]+jpt.pz[0])/(jpt.energy[0]-jpt.pz[0]));
        //double phoPhi = (*event)[iPho].phi();

        //if (!(TMath::Abs(phoEta) < 1.44)) continue;

        h_phoPt->Fill(phoPt);
        h_phoEta->Fill(phoEta);
    }
    std::cout << "Loop ENDED" << std::endl;
    std::cout << "eventsAnalyzed = " << eventsAnalyzed << std::endl;
    std::cout << "Closing the input file" << std::endl;
    inputFile->Close();

    // Save histogram on file and close file.
    std::cout << "saving histograms" << std::endl;

    h_phoPt->Scale(1./h_phoPt->Integral(), "width");
    h_phoEta->Scale(1./h_phoEta->Integral(), "width");

    outputFile->Write("", TObject::kOverwrite);
    std::cout << "Closing the output file" << std::endl;
    outputFile->Close();

    std::cout << "running jetphoxAna() - END" << std::endl;
}

int main(int argc, char* argv[]) {

    if (argc == 3) {
        jetphoxAna(argv[1], argv[2]);
        return 0;
    }
    else if (argc == 2) {
        jetphoxAna(argv[1]);
        return 0;
    }
    else {
        std::cout << "Usage : \n" <<
                "./jetphoxAna.exe <inputFileName> <outputFileName>"
                << std::endl;
        return 1;
    }
}
