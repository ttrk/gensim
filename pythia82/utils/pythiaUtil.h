/*
 * utilities related to Pythia.
 */

#include "Pythia8/Pythia.h"
#include "Pythia8/Event.h"
#include "Pythia8/ParticleData.h"
#include "Pythia8/Basics.h"

#include <string>
#include <vector>
#include <iostream>

#ifndef PYTHIAUTIL_H_
#define PYTHIAUTIL_H_

bool isParton(Pythia8::Particle particle);
bool isQuark(Pythia8::Particle particle);
bool isGluon(Pythia8::Particle particle);
bool isGamma(Pythia8::Particle particle);
bool isZboson(Pythia8::Particle particle);
bool isNeutrino(Pythia8::Particle particle);
bool isCharged(Pythia8::Particle particle, Pythia8::ParticleData& particleData);
bool hasDaughter(Pythia8::Particle particle);
bool isAncestor(Pythia8::Event* evtPtr, int iParticle, int iAncestor);
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
 * derived from main73.cc example
 * generic function to extract the particles that existed right before the hadronization machinery was invoked
 */
void fillPartonLevelEvent(Pythia8::Event& event, Pythia8::Event& partonLevelEvent)
{
    // Copy over all particles that existed right before hadronization.
    partonLevelEvent.reset();
    int nEventSize = event.size();
    for (int i = 0; i < nEventSize; ++i)

        if (event[i].isFinalPartonLevel()) {
            int iNew = partonLevelEvent.append(event[i]);

            // Set copied properties more appropriately :
            // positive status, original location as "mother", and with no daughters.
            partonLevelEvent[iNew].statusPos();
            partonLevelEvent[iNew].mothers(i, i);
            partonLevelEvent[iNew].daughters(0, 0);
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
    for (int i = 0; i < nEventSize; ++i)

        if (event[i].isFinal()) {
            int iNew = finalEvent.append(event[i]);

            finalEvent[iNew].mothers(i, i);
        }
}

#endif /* PYTHIAUTIL_H_ */

