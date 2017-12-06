/*
 * code to analyze the general info about a process.
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
#include "dictionary/dict4RootDct.cc"
#include "utils/pythiaUtil.h"
#include "../utilities/physicsUtil.h"
#include "../utilities/th1Util.h"
#include "../utilities/systemUtil.h"

#include <iostream>
#include <string>
#include <vector>

int main(int argc, char* argv[]) {
    std::cout << "running eventInfoAna()" << std::endl;

    std::string inputFileName = "pythiaEvents.root";
    if (argc > 0) {
        inputFileName = argv[1];
    }

    std::string outputFileName = "eventInfoAna_out.root";
    if (argc > 1) {
        outputFileName = argv[2];
    }

    // comma separated list of process codes
    std::vector<int> processCodes;
    if (argc > 2) {
        std::vector<std::string> processCodesStr = split(argv[3], ",");
        for (int i = 0; i < processCodesStr.size(); ++i) {
            processCodes.push_back(std::atoi(processCodesStr.at(i).c_str()));
        }

        if (std::string(argv[3]).size() > 0 && processCodes.size() == 0)
            processCodes.push_back(std::atoi(argv[3]));
    }
    int nProcessCodes = processCodes.size();

    std::cout << "##### Parameters #####" << std::endl;
    std::cout << "inputFileName = " << inputFileName.c_str() << std::endl;
    std::cout << "outputFileName = " << outputFileName.c_str() << std::endl;
    std::cout << "processCodes = { ";
    for (int i = 0; i < nProcessCodes; ++i) {
        std::cout << processCodes.at(i) << " ";
    }
    std::cout << "}" << std::endl;
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

    enum INCOMINGPARTONS {
        kInclusive,
        kQuark,
        kGluon,
        kdQ,
        kuQ,
        ksQ,
        kudsQ,
        kcbQ,
        kN_INCOMINGPARTONS
    };
    std::string incomingPartonsStr[kN_INCOMINGPARTONS] = {"parton", "q", "g", "dQ", "uQ", "sQ", "udsQ", "bcQ"};
    std::string incomingPartonsLabel[kN_INCOMINGPARTONS] = {"q/g", "q", "g", "d", "u", "s", "u/d/s", "b/c"};

    TH2D* h2_pdf_x[kN_INCOMINGPARTONS];

    for (int i = 0; i < kN_INCOMINGPARTONS; ++i) {

        int nBins_x = 100;
        std::vector<double> binsXVec = calcBinsLogScale(0.001, 1, nBins_x);
        double binsArrX[nBins_x+1];
        std::copy(binsXVec.begin(), binsXVec.end(), binsArrX);

        int nBins_y = 100;
        /*
        std::vector<double> binsYVec = calcBinsLogScale(0.0001, 100, nBins_y);
        double binsArrY[nBins_y+1];
        std::copy(binsYVec.begin(), binsYVec.end(), binsArrY);
        */

        h2_pdf_x[i] = new TH2D(Form("h2_pdf_x_%s", incomingPartonsStr[i].c_str()),
                Form(";x_{%s};PDF", incomingPartonsLabel[i].c_str()),
                nBins_x, binsArrX, nBins_y, 0, 1);
    }

    int nEvents = treeEvt->GetEntries();
    std::cout << "nEvents = " << nEvents << std::endl;
    std::cout << "Loop STARTED" << std::endl;
    for (int iEvent = 0; iEvent < nEvents; ++iEvent) {

        treeEvt->GetEntry(iEvent);
        treeEvtParton->GetEntry(iEvent);
        treeEvtInfo->GetEntry(iEvent);

        bool passedProcess = (nProcessCodes == 0);
        for (int i = 0; i < nProcessCodes; ++i) {
            if (processCodes[i] == -1 ||
                processCodes[i] == info->code())  {
                passedProcess = true;
                break;
            }
        }
        if (!passedProcess)  continue;

        std::vector<Pythia8::Particle> incomingPartons;
        incomingPartons.push_back(Pythia8::Particle(info->id1()));
        incomingPartons.push_back(Pythia8::Particle(info->id2()));

        int nIncoming = 2;
        for (int i = 0; i < nIncoming; ++i) {

            double scalePDF = 1;
            if (isGluon(incomingPartons[i]) || incomingPartons[i].idAbs() == 3)  scalePDF = 0.05;

            double x = info->x1();
            double pdf = info->pdf1();
            if (i == 1) {
                x = info->x2();
                pdf = info->pdf2();
            }

            h2_pdf_x[kInclusive]->Fill(x, scalePDF*pdf);
            if (isQuark(incomingPartons[i]))  h2_pdf_x[kQuark]->Fill(x, scalePDF*pdf);
            if (isGluon(incomingPartons[i]))  h2_pdf_x[kGluon]->Fill(x, scalePDF*pdf);
            if (incomingPartons[i].idAbs() == 1)  h2_pdf_x[kdQ]->Fill(x, scalePDF*pdf);
            if (incomingPartons[i].idAbs() == 2)  h2_pdf_x[kuQ]->Fill(x, scalePDF*pdf);
            if (incomingPartons[i].idAbs() == 3)  h2_pdf_x[ksQ]->Fill(x, scalePDF*pdf);
            if (incomingPartons[i].idAbs() == 1 ||
                incomingPartons[i].idAbs() == 2 ||
                incomingPartons[i].idAbs() == 3)  h2_pdf_x[kudsQ]->Fill(x, scalePDF*pdf);
            if (incomingPartons[i].idAbs() == 4 ||
                incomingPartons[i].idAbs() == 5)  h2_pdf_x[kcbQ]->Fill(x, scalePDF*pdf);
        }
    }
    std::cout << "Loop ENDED" << std::endl;
    std::cout << "Closing the input file" << std::endl;
    inputFile->Close();

    // Save histogram on file and close file.
    std::cout << "saving histograms" << std::endl;

    outputFile->Write("", TObject::kOverwrite);
    std::cout << "Closing the output file" << std::endl;
    outputFile->Close();

    std::cout << "running eventInfoAna() - END" << std::endl;

    return 0;
}