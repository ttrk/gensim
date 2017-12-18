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
#include <iomanip>
#include <string>
#include <vector>

void eventInfoAna(std::string inputFileName = "pythiaEvents.root", std::string outputFileName = "eventInfoAna_out.root",
                  std::string processList = "", int qMin = 0, int qMax = -1);

void eventInfoAna(std::string inputFileName, std::string outputFileName, std::string processList, int qMin, int qMax)
{
    std::cout << "running eventInfoAna()" << std::endl;

    // comma separated list of process codes
    std::vector<int> processCodes;
    std::vector<std::string> processCodesStr = split(processList, ",");
    for (int i = 0; i < processCodesStr.size(); ++i) {
        processCodes.push_back(std::atoi(processCodesStr.at(i).c_str()));
    }
    if (std::string(processList).size() > 0 && processCodes.size() == 0)
        processCodes.push_back(std::atoi(processList.c_str()));

    int nProcessCodes = processCodes.size();

    std::cout << "##### Parameters #####" << std::endl;
    std::cout << "inputFileName = " << inputFileName.c_str() << std::endl;
    std::cout << "outputFileName = " << outputFileName.c_str() << std::endl;
    std::cout << "processCodes = { ";
    for (int i = 0; i < nProcessCodes; ++i) {
        std::cout << processCodes.at(i) << " ";
    }
    std::cout << "}" << std::endl;
    std::cout << "qMin = " << qMin << std::endl;
    std::cout << "qMax = " << qMax << std::endl;
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
    std::vector<double> binsXVec = {};
    std::vector<double> binsYVec = {};

    int nBinsX_q = 200;
    double axis_q_min = 0;
    double axis_q_max = 1000+axis_q_min;

    TH1D* h_q = new TH1D("h_q", ";Q (GeV);", nBinsX_q, axis_q_min, axis_q_max);

    int nBins_x1Overx2 = 50;
    binsYVec = calcBinsLogScale(5*0.0001, 5*1000, nBins_x1Overx2);
    double binsArrY[nBins_x1Overx2+1];
    std::copy(binsYVec.begin(), binsYVec.end(), binsArrY);
    TH2D* h2_q_x1overx2 = new TH2D("h2_q_x1overx2", ";Q (GeV);x_{1} / x_{2}",
            nBinsX_q, axis_q_min, axis_q_max, nBins_x1Overx2, binsArrY);

    TH1D* h_nMPI = new TH1D("h_nMPI", ";nMPI;", 25, 0, 25);
    TH1D* h_nISR = new TH1D("h_nISR", ";nISR;", 45, 0, 45);
    TH1D* h_nFSR = new TH1D("h_nFSR", ";nFSR;", 50, 0, 250);

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
        binsXVec = calcBinsLogScale(0.001, 1, nBins_x);
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

        bool passedProcess = (nProcessCodes == 0);
        for (int i = 0; i < nProcessCodes; ++i) {
            if (processCodes[i] == -1 ||
                processCodes[i] == info->code())  {
                passedProcess = true;
                break;
            }
        }
        if (!passedProcess)  continue;

        if (info->QFac() < qMin)  continue;
        if (qMax != -1 && info->QFac() >= qMax)  continue;

        eventsAnalyzed++;

        h_q->Fill(info->QFac());
        h2_q_x1overx2->Fill(info->QFac(), info->x1() / info->x2());

        h_nMPI->Fill(info->nMPI());
        h_nISR->Fill(info->nISR());
        h_nFSR->Fill(info->nFSRinProc());

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
    std::cout << "eventsAnalyzed = " << eventsAnalyzed << std::endl;
    std::cout << "Closing the input file" << std::endl;
    inputFile->Close();

    h_q->Scale(1./h_q->Integral(), "width");

    h_nMPI->Scale(1./h_nMPI->Integral(), "width");
    h_nISR->Scale(1./h_nISR->Integral(), "width");
    h_nFSR->Scale(1./h_nFSR->Integral(), "width");

    // Save histogram on file and close file.
    std::cout << "saving histograms" << std::endl;

    outputFile->Write("", TObject::kOverwrite);
    std::cout << "Closing the output file" << std::endl;
    outputFile->Close();

    std::cout << "running eventInfoAna() - END" << std::endl;
}

int main(int argc, char* argv[]) {

    if (argc == 6) {
        eventInfoAna(argv[1], argv[2], argv[3], std::atoi(argv[4]), std::atoi(argv[5]));
        return 0;
    }
    else if (argc == 5) {
        eventInfoAna(argv[1], argv[2], argv[3], std::atoi(argv[4]));
        return 0;
    }
    else if (argc == 4) {
        eventInfoAna(argv[1], argv[2], argv[3]);
        return 0;
    }
    else if (argc == 3) {
        eventInfoAna(argv[1], argv[2]);
        return 0;
    }
    else if (argc == 2) {
        eventInfoAna(argv[1]);
        return 0;
    }
    else {
        std::cout << "Usage : \n" <<
                "./eventInfoAna.exe <inputFileName> <outputFileName> <processList>"
                << std::endl;
        return 1;
    }
}
