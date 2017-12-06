/*
 * short example code to run FastJet, taken from http://fastjet.fr/quickstart.html
 */
#include "fastjet/ClusterSequence.hh"
#include <iostream>

int main () {
    std::vector<fastjet::PseudoJet> particles;
    // an event with three particles:   px    py  pz      E
    particles.push_back( fastjet::PseudoJet(   99.0,  0.1,  0, 100.0) );
    particles.push_back( fastjet::PseudoJet(    4.0, -0.1,  0,   5.0) );
    particles.push_back( fastjet::PseudoJet(  -99.0,    0,  0,  99.0) );

    // choose a jet definition
    double R = 0.7;
    fastjet::JetDefinition jet_def(fastjet::antikt_algorithm, R);

    // run the clustering, extract the jets
    fastjet::ClusterSequence cs(particles, jet_def);
    std::vector<fastjet::PseudoJet> jets = sorted_by_pt(cs.inclusive_jets());

    // print out some infos
    std::cout << "Clustering with " << jet_def.description() << std::endl;

    // print the jets
    std::cout <<   "        pt y phi" << std::endl;
    for (unsigned i = 0; i < jets.size(); i++) {
        std::cout << "jet " << i << ": "<< jets[i].pt() << " "
                << jets[i].rap() << " " << jets[i].phi() << std::endl;
        std::vector<fastjet::PseudoJet> constituents = jets[i].constituents();
        for (unsigned j = 0; j < constituents.size(); j++) {
            std::cout << "    constituent " << j << "'s pt: " << constituents[j].pt()
                   << std::endl;
        }
    }
} 
