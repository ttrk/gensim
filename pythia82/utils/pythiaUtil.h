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
bool isNeutrino(Pythia8::Particle particle);
bool isCharged(Pythia8::Particle particle, Pythia8::ParticleData& particleData);
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

bool isNeutrino(Pythia8::Particle particle)
{
    return (particle.idAbs() == 12 || particle.idAbs() == 14 || particle.idAbs() == 16);
}

bool isCharged(Pythia8::Particle particle, Pythia8::ParticleData& particleData)
{
    return (particleData.charge(particle.id()) != 0);
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

