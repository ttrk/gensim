### Creating the dictionary
A dictionary is needed to save Pythia events to a ROOT file. Run the following to create the dictionary files :

  ```bash
  ./setupDict4Root.sh <pythiaExamplesDir>
  ```

### Creating the shared object
A shared object is needed to read stored Pythia events in a ROOT session. Run the following to create the shared object :

  ```bash
  ./makeSharedObject.sh
  ```

Load the shared object to read Pythia events :
  ```bash
  $ root -l
  .L /path-to-base/pythia82/dictionary/dict4Root.so
  eventTree->Scan("event.size():entry:entry.pT():entry.eta():entry.phi():entry.id():entry.idAbs():entry.status()")
  ```
