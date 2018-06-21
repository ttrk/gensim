// generates Pythia events using a card file and writes the events to a ROOT file.
// modified version of main92.cc example where generation parameters are read from card and the output ROOT file is given as an argument

// Header file to access Pythia 8 program elements.
#include "Pythia8/Pythia.h"

// ROOT, for saving Pythia events as trees in a file.
#include "TTree.h"
#include "TFile.h"

#include "dictionary/dict4Root.h"
#include "dictionary/dict4RootDct.cc"
// dictionary is needed to avoid the following error :
// Error in <TTree::Branch>: The pointer specified for event is not of a class known to ROOT
#include "utils/pythiaUtil.h"
#include "../utilities/systemUtil.h"

#include <iostream>
#include <iomanip>
#include <string>
#include <vector>

std::vector<std::string> argOptions;

void pythiaGenerateAndWrite(std::string cardFileName = "mycard.cmnd", std::string outFileName = "pythiaGenerateAndWrite.root", std::string particleFilter = "");

void pythiaGenerateAndWrite(std::string cardFileName, std::string outFileName, std::string particleFilter)
{
    std::cout << "running pythiaGenerateAndWrite()" << std::endl;

    // Generator.
    Pythia8::Pythia pythia;
    // Read in commands from external file.
    pythia.readFile(cardFileName.c_str());

    // Extract settings to be used in the main program.
    int nEvent = pythia.mode("Main:numberOfEvents");
    int nAbort = pythia.mode("Main:timesAllowErrors");

    // Initialize.
    pythia.init();

    std::cout << "##### Basic Parameters #####" << std::endl;
    std::cout << "cardFileName = " << cardFileName.c_str() << std::endl;
    std::cout << "outFileName = " << outFileName.c_str() << std::endl;
    std::cout << "nEvent = " << nEvent << std::endl;
    std::cout << "nAbort = " << nAbort << std::endl;
    std::cout << "eCM = " << pythia.info.eCM() << std::endl;
    std::cout << "##### Basic Parameters - END #####" << std::endl;

    // Set up the ROOT TFile and TTree.
    TFile *outFile = TFile::Open(outFileName.c_str(), "RECREATE");
    Pythia8::Event *event = &pythia.event;
    TTree *treeEvt = new TTree("evt","event tree");
    treeEvt->Branch("event",&event);

    // Parton Level event records.
    Pythia8::Event eventPartonLevel;
    eventPartonLevel.init("Parton Level event record", &pythia.particleData);
    TTree *treeEvtParton = new TTree("evtParton","parton level event tree");
    treeEvtParton->Branch("event", &eventPartonLevel);

    // general information about the event
    Pythia8::Info *info = &pythia.info;
    TTree *treeEvtInfo = new TTree("evtInfo","event info tree");
    treeEvtInfo->Branch("info",&info);

    std::cout << "##### Pythia Filters #####" << std::endl;
    std::vector<pythiaFilter> filters;
    int nFilters = 0;

    int indexArgPythiaFilter = -1;
    for (int i = 0; i < argOptions.size(); ++i) {
        if (argOptions[i].find("--pythiaFilter") == 0) {
            indexArgPythiaFilter = i;
            break;
        }
    }
    if (indexArgPythiaFilter >= 0) {
        std::string pythiaFiltersStr = replaceAll(argOptions[indexArgPythiaFilter], "--pythiaFilter:", "");
        std::vector<std::string> pythiaFilterStrVec = split(pythiaFiltersStr, ":", false);
        if (pythiaFilterStrVec.size() == 0) pythiaFilterStrVec = {pythiaFiltersStr};

        for (int i = 0; i < pythiaFilterStrVec.size(); ++i) {
            pythiaFilter filterTmp;
            filterTmp.parseFilter(pythiaFilterStrVec[i]);
            filters.push_back(filterTmp);
        }
    }
    nFilters = filters.size();
    for (int i = 0; i < nFilters; ++i) {
        std::cout << "## Filter " << i+1 << std::endl;
        std::cout << filters[i].print() << std::endl;
    }
    std::cout << "##### Pythia Filters - END #####" << std::endl;

    int iAbort = 0;
    int eventsGenerated = 0;
    int eventsFinal = 0;
    std::cout << "Loop START" << std::endl;
    int iEvent = 0;
    while (iEvent < nEvent) {

        if (iEvent % 10000 == 0)  {
          std::cout << "current entry = " <<iEvent<<" out of "<<nEvent<<" : "<<std::setprecision(2)<<(double)iEvent/nEvent*100<<" %"<<std::endl;
        }

        // Generate events. Quit if many failures.
        if (!pythia.next()) {
            if (++iAbort < nAbort) continue;
            cout << " Event generation aborted prematurely, owing to error!\n";
            break;
        }
        eventsGenerated++;

        bool passedFilters = true;
        for (int iFilter = 0; iFilter < nFilters; ++iFilter) {
            if (!filters[iFilter].passedFilter(*event, *info)) {
                passedFilters = false;
                break;
            }
        }
        if (!passedFilters) continue;

        eventsFinal++;

        fillPartonLevelEvent(*event, eventPartonLevel);

        // Fill the pythia event into the TTree.
        // Warning: the files will rapidly become large if all events
        // are saved. In some cases it may be convenient to do some
        // processing of events and only save those that appear
        // interesting for future analyses.
        treeEvt->Fill();
        treeEvtParton->Fill();
        treeEvtInfo->Fill();

        iEvent++;
    }
    std::cout << "Loop END" << std::endl;
    std::cout << "eventsGenerated = " << eventsGenerated << std::endl;
    std::cout << "eventsFinal = " << eventsFinal << std::endl;
    // Statistics on event generation.
    pythia.stat();

    treeEvt->Print();
    treeEvt->Write("", TObject::kOverwrite);
    treeEvtParton->Write("", TObject::kOverwrite);
    treeEvtInfo->Write("", TObject::kOverwrite);

    std::cout<<"Closing the output file"<<std::endl;
    outFile->Close();

    std::cout << "running pythiaGenerateAndWrite() - END" << std::endl;
}

int main(int argc, char* argv[]) {

    argOptions.clear();
    for (int i = 0; i < argc; ++i) {

        std::string tmp = argv[i];
        // an option starts with "--"
        if (tmp.find("--") == 0)  argOptions.push_back(tmp);
    }

    if (argc >= 3) {
        pythiaGenerateAndWrite(argv[1], argv[2]);
        return 0;
    }
    else if (argc == 2) {
        pythiaGenerateAndWrite(argv[1]);
        return 0;
    }
    else {
        std::cout << "Usage : \n" <<
                "./pythiaGenerateAndWrite.exe <inputFileName> <outputFileName> [options]"
                << std::endl;
        return 1;
    }
}
