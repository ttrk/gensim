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

using namespace Pythia8;

int main(int argc, char* argv[]) {

    // Read in commands from external file.
    std::string cardFileName = "mycard.cmnd";
    if (argc > 0) {
        cardFileName = argv[1];
    }

    std::string outFileName = "pythiaGenerateAndWrite.root";
    if (argc > 1) {
        outFileName = argv[2];
    }

    // Generator.
    Pythia pythia;
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
    Event *event = &pythia.event;
    TTree *T = new TTree("T","ev1 Tree");
    T->Branch("event",&event);

    // Begin event loop.
    int iAbort = 0;
    for (int iEvent = 0; iEvent < nEvent; ++iEvent) {
        // Generate events. Quit if many failures.
        if (!pythia.next()) {
            if (++iAbort < nAbort) continue;
            cout << " Event generation aborted prematurely, owing to error!\n";
            break;
        }

        // Fill the pythia event into the TTree.
        // Warning: the files will rapidly become large if all events
        // are saved. In some cases it may be convenient to do some
        // processing of events and only save those that appear
        // interesting for future analyses.
        T->Fill();

        // End event loop.
    }

    // Statistics on event generation.
    pythia.stat();

    //  Write tree.
    T->Print();
    T->Write("", TObject::kOverwrite);

    std::cout<<"Closing the output file"<<std::endl;
    outFile->Close();

    // Done.
    return 0;
}
