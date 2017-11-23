/*
 * utilities related to Pythia.
 */

#include "Pythia8/Pythia.h"
#include "Pythia8/Event.h"
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

#endif /* PYTHIAUTIL_H_ */

