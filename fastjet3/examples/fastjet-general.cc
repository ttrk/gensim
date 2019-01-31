/*
 * Code to cluster the given set of particles into jets using fastjet. The following can be given as parameter
  - distance parameter (cone size)
  - jet algorithm
  - recombination scheme
   All input is given in a text file. Output is printed to stdout.
 */
#include "fastjet/ClusterSequence.hh"
#include "TLorentzVector.h"

#include "../../utilities/systemUtil.h"

#include <iostream>
#include <string>
#include <vector>

std::vector<double> parseListOfNumbers(std::string str);
int getJetAlgorithm(std::string str);
int getRecombinationScheme(std::string str);

int main (int argc, char* argv[]) {

    if (argc != 2) {
        std::cout << "Usage :"<< std::endl;
        std::cout << "./fastjet-general.exe <inputFile>" << std::endl;
        return 1;
    }

    std::string inputFile = argv[1];

    std::cout << "inputFile = " << inputFile.c_str() << std::endl;

    std::vector<TLorentzVector> lorentzVecs;
    std::string strR = "";
    std::string strJetAlgo = "";
    std::string strRecombScheme = "";

    // Assumptions for lines in input file
    // The portion following a "#" is ignored.
    // Any comma separated list of 4 numbers is pt, eta, phi, mass of a particle
    // Last line starting with "R:" gives distance parameter. "R=0.3" means R is 0.3
    // Last line starting with "JetAlgorithm:<x>" gives algorithm. Only an element of JetAlgorithm enum is a valid <x>
    // Last line starting with "RecombinationScheme:<x>" gives algorithm. Only an element of RecombinationScheme enum is a valid <x>
    std::ifstream inFile(inputFile.c_str());
    std::string strLine;
    if (inFile.is_open()) {
        while (getline(inFile,strLine)) {
            std::string comment = "#";
            if (trim(strLine).find(comment.c_str()) == 0) continue;  //skip all lines starting with comment

            size_t posLast = strLine.find(comment);    // allow inline comment signs with #
            std::string in = trim(strLine.substr(0, posLast));

            std::vector<double> tmpV = parseListOfNumbers(in);
            if (tmpV.size() == 4) {
                TLorentzVector v;
                v.SetPtEtaPhiM(tmpV[0], tmpV[1], tmpV[2], tmpV[3]);
                lorentzVecs.push_back(v);
            }
            else if (startsWith(in, "R:")) {
                size_t posTmp = std::string("R:").size();
                strR = trim(in.substr(posTmp));
            }
            else if (startsWith(in, "JetAlgorithm:")) {
                size_t posTmp = std::string("JetAlgorithm:").size();
                strJetAlgo = trim(in.substr(posTmp));
            }
            else if (startsWith(in, "RecombinationScheme:")) {
                size_t posTmp = std::string("RecombinationScheme:").size();
                strRecombScheme = trim(in.substr(posTmp));
            }
        }
    }

    double R = 0.3;
    int jetAlgo = -1;
    int recombScheme = -1;

    if (strR.size() == 0) {
        std::cout << "No or invalid distance parameter is given. Using default : R = " << R << std::endl;
    }
    else {
        R = std::atof(strR.c_str());
        std::cout << "R = " << R << std::endl;
    }

    jetAlgo = getJetAlgorithm(strJetAlgo);
    if (jetAlgo == -1) {
        std::cout << "No or invalid jet algorithm is given : " << strJetAlgo.c_str() << std::endl;
        jetAlgo = fastjet::JetAlgorithm::antikt_algorithm;
        std::cout << "Using default : jet algorithm = antikt_algorithm" << std::endl;
    }
    else {
        std::cout << "jet algorithm = " << strJetAlgo.c_str() << std::endl;
    }

    recombScheme = getRecombinationScheme(strRecombScheme);
    if (recombScheme == -1) {
        std::cout << "No or invalid recombination scheme is given : " << strRecombScheme.c_str() << std::endl;
        recombScheme = fastjet::RecombinationScheme::E_scheme;
        std::cout << "Using default : recombination scheme = E_scheme" << std::endl;
    }
    else {
        std::cout << "recombination scheme = " << strRecombScheme.c_str() << std::endl;
    }

    std::cout << "List of given particles : {pt, eta, phi, mass} --> {px, py, pz, E}" << std::endl;
    int nParticles = lorentzVecs.size();
    std::cout << "nParticles = " << nParticles << std::endl;
    for (int i = 0; i < nParticles; ++i) {
        std::string particleStr = Form("particle %d : ", i);
        std::string strVec1 = Form("{ %f , %f , %f , %f }", lorentzVecs[i].Pt(), lorentzVecs[i].Eta(), lorentzVecs[i].Phi(), lorentzVecs[i].M());
        std::string strVec2 = Form("{ %f , %f , %f , %f }", lorentzVecs[i].Px(), lorentzVecs[i].Py(), lorentzVecs[i].Pz(), lorentzVecs[i].E());

        particleStr += Form("%s --> %s", strVec1.c_str(), strVec2.c_str());
        std::cout << particleStr << std::endl;
    }


    std::vector<fastjet::PseudoJet> pseudoJets;
    for (int i = 0; i < nParticles; ++i) {
        pseudoJets.push_back(fastjet::PseudoJet(lorentzVecs[i].Px(),  lorentzVecs[i].Py(),  lorentzVecs[i].Pz(), lorentzVecs[i].E()));
    }

    fastjet::JetDefinition jet_def((fastjet::JetAlgorithm)jetAlgo, R);
    jet_def.set_recombination_scheme((fastjet::RecombinationScheme)recombScheme);

    // run the clustering, extract the jets
    fastjet::ClusterSequence cs(pseudoJets, jet_def);
    std::vector<fastjet::PseudoJet> jets = sorted_by_pt(cs.inclusive_jets());

    std::cout << "Clustering with " << jet_def.description() << std::endl;

    std::cout << "List of clustered jets : {pt, eta, phi}" << std::endl;
    std::cout << "and their constituents : {pt, eta, phi, mass}" << std::endl;

    int nJets = jets.size();
    for (int i = 0; i < nJets; i++) {
        std::string strJet = Form("{ %f , %f , %f }", jets[i].pt(), jets[i].eta(), jets[i].phi_std());
        std::cout << "jet " << i << " : " << strJet.c_str() << std::endl;
        std::vector<fastjet::PseudoJet> constituents = jets[i].constituents();
        int nConstituents = constituents.size();
        for (int j = 0; j < nConstituents; ++j) {
            std::string strConst = Form("{ %f , %f , %f , %f }", constituents[j].pt(), constituents[j].eta(), constituents[j].phi_std(), constituents[j].m());
            std::cout << "    constituent " << j << " : " << strConst.c_str() << std::endl;
        }
    }

    return 0;
} 

std::vector<double> parseListOfNumbers(std::string str)
{
    if(str.empty())
        return {};

    std::vector<std::string> strVec = split(str, ",", false);
    int n = strVec.size();

    std::vector<double> list;
    for (int i = 0; i < n; ++i) {
        double val = std::atof(strVec[i].c_str());
        list.push_back(val);
    }

    return list;
}

int getJetAlgorithm(std::string str)
{
    int res = -1;

    if (str == "kt_algorithm") {
        res = fastjet::JetAlgorithm::kt_algorithm;
    }
    else if (str == "cambridge_algorithm") {
        res = fastjet::JetAlgorithm::cambridge_algorithm;
    }
    else if (str == "antikt_algorithm") {
        res = fastjet::JetAlgorithm::antikt_algorithm;
    }
    else if (str == "genkt_algorithm") {
        res = fastjet::JetAlgorithm::genkt_algorithm;
    }
    else if (str == "cambridge_for_passive_algorithm") {
        res = fastjet::JetAlgorithm::cambridge_for_passive_algorithm;
    }
    else if (str == "genkt_for_passive_algorithm") {
        res = fastjet::JetAlgorithm::genkt_for_passive_algorithm;
    }
    else if (str == "ee_kt_algorithm") {
        res = fastjet::JetAlgorithm::ee_kt_algorithm;
    }
    else if (str == "ee_genkt_algorithm") {
        res = fastjet::JetAlgorithm::ee_genkt_algorithm;
    }
    else if (str == "plugin_algorithm") {
        res = fastjet::JetAlgorithm::plugin_algorithm;
    }
    else if (str == "undefined_jet_algorithm") {
        res = fastjet::JetAlgorithm::undefined_jet_algorithm;
    }

    return res;
}

int getRecombinationScheme(std::string str)
{
    int res = -1;

    if (str == "E_scheme") {
        res = fastjet::RecombinationScheme::E_scheme;
    }
    else if (str == "pt_scheme") {
        res = fastjet::RecombinationScheme::pt_scheme;
    }
    else if (str == "pt2_scheme") {
        res = fastjet::RecombinationScheme::pt2_scheme;
    }
    else if (str == "Et_scheme") {
        res = fastjet::RecombinationScheme::Et_scheme;
    }
    else if (str == "Et2_scheme") {
        res = fastjet::RecombinationScheme::Et2_scheme;
    }
    else if (str == "BIpt_scheme") {
        res = fastjet::RecombinationScheme::BIpt_scheme;
    }
    else if (str == "BIpt2_scheme") {
        res = fastjet::RecombinationScheme::BIpt2_scheme;
    }
    else if (str == "WTA_pt_scheme") {
        res = fastjet::RecombinationScheme::WTA_pt_scheme;
    }
    else if (str == "WTA_modp_scheme") {
        res = fastjet::RecombinationScheme::WTA_modp_scheme;
    }
    else if (str == "external_scheme") {
        res = fastjet::RecombinationScheme::external_scheme;
    }

    return res;
}
