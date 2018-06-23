/*
 * utilities related to Pythia.
 */

#include "Pythia8/Pythia.h"
#include "Pythia8/Event.h"
#include "Pythia8/ParticleData.h"
#include "Pythia8/Basics.h"

#include "../../utilities/systemUtil.h"

#include <string>
#include <vector>
#include <iostream>

#ifndef PYTHIAUTIL_H_
#define PYTHIAUTIL_H_

/*
 * object to filter Pythia events based on particle/event info
 */
struct pythiaFilter {
    pythiaFilter() {
        processCode = -1;
        idAbs = 999999;
        id = -999999;
        minPt = 0;
        maxPt = -1;
        minEta = -999999;
        maxEta = 999999;
        minY = -999999;
        maxY = 999999;
        minPhi = -999999;
        maxPhi = 999999;
        minP = 0;
        maxP = -1;
        statusAbs = 0;
        status = 0;
        motherIdAbs = {};
        motherId = {};
    }
    void parseFilter(std::string pythiaFilterStr) {
        std::vector<std::string> filterArgs = split(pythiaFilterStr, ";");
        parseFilter(filterArgs);
    }
    void parseFilter(std::vector<std::string> filterArgs) {

        for (std::vector<std::string>::iterator it = filterArgs.begin(); it != filterArgs.end(); ++it) {
            std::string filterArg = trim((*it));
            std::string filterArgVal = trim(filterArg.substr(filterArg.find("=")+1));

            if (filterArg.find("processCode") == 0) {
                processCode = std::atoi(filterArgVal.c_str());
            }
            else if (filterArg.find("idAbs") == 0) {
                idAbs = std::atoi(filterArgVal.c_str());
            }
            else if (filterArg.find("id") == 0) {
                id = std::atoi(filterArgVal.c_str());
            }
            else if (filterArg.find("minPt") == 0) {
                minPt = std::atof(filterArgVal.c_str());
            }
            else if (filterArg.find("maxPt") == 0) {
                maxPt = std::atof(filterArgVal.c_str());
            }
            else if (filterArg.find("minEta") == 0) {
                minEta = std::atof(filterArgVal.c_str());
            }
            else if (filterArg.find("maxEta") == 0) {
                maxEta = std::atof(filterArgVal.c_str());
            }
            else if (filterArg.find("minY") == 0) {
                minY = std::atof(filterArgVal.c_str());
            }
            else if (filterArg.find("maxY") == 0) {
                maxY = std::atof(filterArgVal.c_str());
            }
            else if (filterArg.find("minPhi") == 0) {
                minPhi = std::atof(filterArgVal.c_str());
            }
            else if (filterArg.find("maxPhi") == 0) {
                maxPhi = std::atof(filterArgVal.c_str());
            }
            else if (filterArg.find("minP") == 0) {
                minP = std::atof(filterArgVal.c_str());
            }
            else if (filterArg.find("maxP") == 0) {
                maxP = std::atof(filterArgVal.c_str());
            }
            else if (filterArg.find("statusAbs") == 0) {
                statusAbs = std::atoi(filterArgVal.c_str());
            }
            else if (filterArg.find("status") == 0) {
                status = std::atoi(filterArgVal.c_str());
            }
            else if (filterArg.find("motherIdAbs") == 0) {

                // motherId is a list starting with "{" and ending with "}"
                // Ex. motherId={1,2,3,21,22,-1,-2,-3}
                size_t posStart = filterArgVal.find("{");     // a valid list starts with '{' and ends with '}'
                size_t posEnd   = filterArgVal.rfind("}");     // a valid list starts with '{' and ends with '}'
                std::string filterArgValTmp = filterArgVal.substr(posStart+1, posEnd-posStart-1);
                std::vector<std::string> filterArgVals = split(filterArgValTmp, ",", false);
                if (filterArgVals.size() == 0) filterArgVals = {filterArgValTmp};

                for (std::vector<std::string>::iterator it = filterArgVals.begin(); it != filterArgVals.end(); ++it) {
                    motherIdAbs.push_back(std::atoi((*it).c_str()));
                }
            }
            else if (filterArg.find("motherId") == 0) {

                // motherId is a list starting with "{" and ending with "}"
                // Ex. motherId={1,2,3,21,22,-1,-2,-3}
                size_t posStart = filterArgVal.find("{");     // a valid list starts with '{' and ends with '}'
                size_t posEnd   = filterArgVal.rfind("}");     // a valid list starts with '{' and ends with '}'
                std::string filterArgValTmp = filterArgVal.substr(posStart+1, posEnd-posStart-1);
                std::vector<std::string> filterArgVals = split(filterArgValTmp, ",", false);
                if (filterArgVals.size() == 0) filterArgVals = {filterArgValTmp};

                for (std::vector<std::string>::iterator it = filterArgVals.begin(); it != filterArgVals.end(); ++it) {
                    motherId.push_back(std::atoi((*it).c_str()));
                }
            }
        }
    }
    std::string print() {

        std::string result;

        result.append(Form("processCode = %d\n", processCode));
        result.append(Form("idAbs = %d\n", idAbs));
        result.append(Form("id = %d\n", id));
        result.append(Form("minPt = %.3f\n", minPt));
        result.append(Form("maxPt = %.3f\n", maxPt));
        result.append(Form("minEta = %.3f\n", minEta));
        result.append(Form("maxEta = %.3f\n", maxEta));
        result.append(Form("minY = %.3f\n", minY));
        result.append(Form("maxY = %.3f\n", maxY));
        result.append(Form("minPhi = %.3f\n", minPhi));
        result.append(Form("maxPhi = %.3f\n", maxPhi));
        result.append(Form("minP = %.3f\n", minP));
        result.append(Form("maxP = %.3f\n", maxP));
        result.append(Form("statusAbs = %d\n", statusAbs));
        result.append(Form("status = %d\n", status));
        result.append("motherIdAbs = {");
        for (int i = 0; i < motherIdAbs.size(); ++i) {
            if (i < motherIdAbs.size() - 1)
                result.append(Form("%d, ", motherIdAbs[i]));
            else
                result.append(Form("%d", motherIdAbs[i]));
        }
        result.append("}\n");
        result.append("motherId = {");
        for (int i = 0; i < motherId.size(); ++i) {
            if (i < motherId.size() - 1)
                result.append(Form("%d, ", motherId[i]));
            else
                result.append(Form("%d", motherId[i]));
        }
        result.append("}");
        // do not put a new line to the end of the last line
        return result;
    }

    bool eventPassedFilter(Pythia8::Info& info) {
        if (processCode != -1 && processCode != info.code()) return false;

        return true;
    }
    bool particlePassedFilter(Pythia8::Event& event, int iPart) {

        if (idAbs != 999999 && idAbs != event[iPart].idAbs()) return false;
        if (id != -999999 && id != event[iPart].id()) return false;
        if (minPt > 0 && minPt > event[iPart].pT()) return false;
        if (maxPt > 0 && maxPt < event[iPart].pT()) return false;
        if (minEta > event[iPart].eta()) return false;
        if (maxEta < event[iPart].eta()) return false;
        if (minY > event[iPart].y()) return false;
        if (maxY < event[iPart].y()) return false;
        if (minPhi > event[iPart].phi()) return false;
        if (maxPhi < event[iPart].phi()) return false;
        if (minP > 0 && minP > event[iPart].pAbs()) return false;
        if (maxP > 0 && maxP < event[iPart].pAbs()) return false;
        if (statusAbs != 0 && statusAbs != event[iPart].statusAbs()) return false;
        if (status != 0 && status != event[iPart].status()) return false;

        if (motherIdAbs.size() > 0) {
            int iMom1 = event[iPart].mother1();
            int iMom2 = event[iPart].mother2();

            bool passedMotherIdAbs = false;
            for (std::vector<int>::iterator it = motherIdAbs.begin(); it != motherIdAbs.end(); ++it) {
                if ((*it) == event[iMom1].idAbs() || (*it) == event[iMom2].idAbs()) {
                    passedMotherIdAbs = true;
                    break;
                }
            }

            if (!passedMotherIdAbs) return false;
        }
        if (motherId.size() > 0) {
            int iMom1 = event[iPart].mother1();
            int iMom2 = event[iPart].mother2();

            bool passedMotherId = false;
            for (std::vector<int>::iterator it = motherId.begin(); it != motherId.end(); ++it) {
                if ((*it) == event[iMom1].id() || (*it) == event[iMom2].id()) {
                    passedMotherId = true;
                    break;
                }
            }

            if (!passedMotherId) return false;
        }

        return true;
    }
    bool passedFilter(Pythia8::Event& event, Pythia8::Info& info) {

        if (!eventPassedFilter(info)) return false;

        return passedFilter(event);
    }
    bool passedFilter(Pythia8::Event& event) {
        int nEventSize = event.size();
        for (int i = 0; i < nEventSize; ++i) {
            if (particlePassedFilter(event, i)) return true;
        }

        return false;
    }

    int processCode;
    int idAbs;
    int id;
    double minPt;
    double maxPt;
    double minEta;
    double maxEta;
    double minY;
    double maxY;
    double minPhi;
    double maxPhi;
    double minP;
    double maxP;
    int statusAbs;
    int status;
    std::vector<int> motherIdAbs;
    std::vector<int> motherId;
};

bool isParton(Pythia8::Particle particle);
bool isQuark(Pythia8::Particle particle);
bool isGluon(Pythia8::Particle particle);
bool isGamma(Pythia8::Particle particle);
bool isZboson(Pythia8::Particle particle);
bool isNeutrino(Pythia8::Particle particle);
bool isCharged(Pythia8::Particle particle, Pythia8::ParticleData& particleData);
bool hasDaughter(Pythia8::Particle particle);
bool isAncestor(Pythia8::Event* evtPtr, int iParticle, int iAncestor);
std::vector<int> daughterList(Pythia8::Event* evtPtr, int iPart);
std::vector<int> daughterListRecursive(Pythia8::Event* evtPtr, int iPart);
void fillPartonLevelEvent(Pythia8::Event& event, Pythia8::Event& partonLevelEvent);
void fillFinalEvent(Pythia8::Event& event, Pythia8::Event& finalEvent);

bool isParton(Pythia8::Particle particle)
{
    return ((particle.idAbs() > 0 && particle.idAbs() < 9) || (particle.id() == 21));
}

bool isQuark(Pythia8::Particle particle)
{
    return (particle.idAbs() > 0 && particle.idAbs() < 9);
}

bool isGluon(Pythia8::Particle particle)
{
    return (particle.id() == 21);
}

bool isGamma(Pythia8::Particle particle)
{
    return (particle.id() == 22);
}

bool isZboson(Pythia8::Particle particle)
{
    return (particle.id() == 23);
}

bool isNeutrino(Pythia8::Particle particle)
{
    return (particle.idAbs() == 12 || particle.idAbs() == 14 || particle.idAbs() == 16);
}

bool isCharged(Pythia8::Particle particle, Pythia8::ParticleData& particleData)
{
    return (particleData.charge(particle.id()) != 0);
}

bool hasDaughter(Pythia8::Particle particle)
{
    return (particle.daughter1() != 0 || particle.daughter2() != 0);
}

/*
 * re-implementation of the following : bool Particle::isAncestor(int iAncestor);
 * uses an external Event* evtPtr, the rest is same as the original function
 *
 * Check whether a given particle is an arbitrarily-steps-removed
 * mother to another. For the parton -> hadron transition, only
 * first-rank hadrons are associated with the respective end quark.
 */
bool isAncestor(Pythia8::Event* evtPtr, int iParticle, int iAncestor)
{

  // Begin loop to trace upwards from the daughter.
  if (evtPtr == 0) return false;
  int iUp = iParticle;
  int sizeNow = (*evtPtr).size();
  for ( ; ; ) {

    // If positive match then done.
    if (iUp == iAncestor) return true;

    // If out of range then failed to find match.
    if (iUp <= 0 || iUp > sizeNow) return false;

    // If unique mother then keep on moving up the chain.
    int mother1up = (*evtPtr)[iUp].mother1();
    int mother2up = (*evtPtr)[iUp].mother2();
    if (mother2up == mother1up || mother2up == 0) {iUp = mother1up; continue;}

    // If many mothers, except hadronization, then fail tracing.
    int statusUp = (*evtPtr)[iUp].statusAbs();
    if (statusUp < 81 || statusUp > 86) return false;

    // For hadronization step, fail if not first rank, else move up.
    if (statusUp == 82) {
      iUp = (iUp + 1 < sizeNow && (*evtPtr)[iUp + 1].mother1() == mother1up)
          ? mother1up : mother2up; continue;
    }
    if (statusUp == 83) {
      if ((*evtPtr)[iUp - 1].mother1() == mother1up) return false;
      iUp = mother1up; continue;
    }
    if (statusUp == 84) {
      if (iUp + 1 < sizeNow && (*evtPtr)[iUp + 1].mother1() == mother1up)
        return false;
      iUp = mother1up; continue;
    }

    // Fail for ministring -> one hadron and for junctions.
    return false;

  }
  // End of loop. Should never reach beyond here.
  return false;
}

/*
 * re-implementation of the following : vector<int> Particle::daughterList();
 * uses an external Event* evtPtr, the rest is same as the original function
 *
 * Find complete list of daughters.
 */
std::vector<int> daughterList(Pythia8::Event* evtPtr, int iPart)
{

    // Vector of all the daughters; created empty. Done if no event pointer.
    std::vector<int> daughterVec;
    if (evtPtr == 0) return daughterVec;

    // Simple cases: no or one daughter.
    if ((*evtPtr)[iPart].daughter1() == 0 && (*evtPtr)[iPart].daughter2() == 0) ;
    else if ((*evtPtr)[iPart].daughter2() == 0 || (*evtPtr)[iPart].daughter2() == (*evtPtr)[iPart].daughter1())
        daughterVec.push_back((*evtPtr)[iPart].daughter1());

    // A range of daughters.
    else if ((*evtPtr)[iPart].daughter2() > (*evtPtr)[iPart].daughter1())
        for (int iRange = (*evtPtr)[iPart].daughter1(); iRange <= (*evtPtr)[iPart].daughter2(); ++iRange)
            daughterVec.push_back(iRange);

    // Two separated daughters.
    else {
        daughterVec.push_back((*evtPtr)[iPart].daughter2());
        daughterVec.push_back((*evtPtr)[iPart].daughter1());
    }

    // Special case for two incoming beams: attach further
    // initiators and remnants that have beam as mother.
    if (std::abs((*evtPtr)[iPart].status()) == 12 || std::abs((*evtPtr)[iPart].status()) == 13) {
        int i = iPart;
        for (int iDau = i + 1; iDau < evtPtr->size(); ++iDau)
            if ((*evtPtr)[iDau].mother1() == i) {
                bool isIn = false;
                for (int iIn = 0; iIn < int(daughterVec.size()); ++iIn)
                    if (iDau == daughterVec[iIn]) isIn = true;
                if (!isIn) daughterVec.push_back(iDau);
            }
    }

    // Done.
    return daughterVec;

}

/*
 * re-implementation of the following : vector<int> Particle::daughterListRecursive();
 * uses an external Event* evtPtr, the rest is same as the original function
 *
 * Find complete list of daughters recursively, i.e. including subsequent
 * generations. Is intended specifically for resonance decays.
 */
std::vector<int> daughterListRecursive(Pythia8::Event* evtPtr, int iPart)
{

    // Vector of all the daughters; created empty. Done if no event pointer.
    std::vector<int> daughterVec;
    if (evtPtr == 0) return daughterVec;

    // Find first generation of daughters.
    daughterVec = daughterList(evtPtr, iPart);

    // Recursively add daughters of unstable particles.
    int size = daughterVec.size();
    for (int iDau = 0; iDau < size; ++iDau) {
        int iPartNow = daughterVec[iDau];
        Pythia8::Particle& partNow = (*evtPtr)[iPartNow];
        if (!partNow.isFinal()) {
            vector<int> grandDauVec = daughterList(evtPtr, iPartNow);
            for (int i = 0; i < int(grandDauVec.size()); ++i)
                daughterVec.push_back( grandDauVec[i] );
            size += grandDauVec.size();
        }
    }

    // Done.
    return daughterVec;
}

/*
 * derived from main73.cc example
 * generic function to extract the particles that existed right before the hadronization machinery was invoked
 */
void fillPartonLevelEvent(Pythia8::Event& event, Pythia8::Event& partonLevelEvent)
{
    // Copy over all particles that existed right before hadronization.
    partonLevelEvent.reset();
    int nEventSize = event.size();
    for (int i = 0; i < nEventSize; ++i) {

        if (event[i].isFinalPartonLevel()) {
            int iNew = partonLevelEvent.append(event[i]);

            // Set copied properties more appropriately :
            // positive status, original location as "mother", and with no daughters.
            partonLevelEvent[iNew].statusPos();
            partonLevelEvent[iNew].mothers(i, i);
            partonLevelEvent[iNew].daughters(0, 0);
        }
    }
}

/*
 * derived from main73.cc example
 * generic function to extract the particles that exist after the hadronization machinery.
 */
void fillFinalEvent(Pythia8::Event& event, Pythia8::Event& finalEvent)
{
    finalEvent.reset();
    int nEventSize = event.size();
    for (int i = 0; i < nEventSize; ++i) {

        if (event[i].isFinal()) {
            int iNew = finalEvent.append(event[i]);

            finalEvent[iNew].mothers(i, i);
        }
    }
}

#endif /* PYTHIAUTIL_H_ */

