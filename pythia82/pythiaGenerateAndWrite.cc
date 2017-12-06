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

int main(int argc, char* argv[]) {

    // Read in commands from external file.
    std::string cardFileName = "mycard.cmnd";
    if (argc > 1) {
        cardFileName = argv[1];
    }

    std::string outFileName = "pythiaGenerateAndWrite.root";
    if (argc > 2) {
        outFileName = argv[2];
    }

    // Generator.
    Pythia8::Pythia pythia;
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

    int iAbort = 0;
    std::cout << "Loop START" << std::endl;
    for (int iEvent = 0; iEvent < nEvent; ++iEvent) {
        // Generate events. Quit if many failures.
        if (!pythia.next()) {
            if (++iAbort < nAbort) continue;
            cout << " Event generation aborted prematurely, owing to error!\n";
            break;
        }

        fillPartonLevelEvent(*event, eventPartonLevel);

        // Fill the pythia event into the TTree.
        // Warning: the files will rapidly become large if all events
        // are saved. In some cases it may be convenient to do some
        // processing of events and only save those that appear
        // interesting for future analyses.
        treeEvt->Fill();
        treeEvtParton->Fill();
        treeEvtInfo->Fill();
    }
    std::cout << "Loop END" << std::endl;

    // Statistics on event generation.
    pythia.stat();

    treeEvt->Print();
    treeEvt->Write("", TObject::kOverwrite);
    treeEvtParton->Write("", TObject::kOverwrite);
    treeEvtInfo->Write("", TObject::kOverwrite);

    std::cout<<"Closing the output file"<<std::endl;
    outFile->Close();

    return 0;
}
