/*
 * utilities related to physics.
 */

#include <TMath.h>
#include <TRandom3.h>

#include <string>
#include <vector>
#include <iostream>

#ifndef PHYSICSUTIL_H_
#define PHYSICSUTIL_H_

double getDETA(double eta1, double eta2);
double getDPHI(double phi1, double phi2);
double getAbsDPHI(double phi1, double phi2);
double getDR(double eta1, double phi1, double eta2, double phi2);
double getDR2(double eta1, double phi1, double eta2, double phi2);
double getResolution(double pt, double C, double S, double N);
double getEnergySmearingFactor(TRandom3 &rand, double pt, double C, double S, double N);
double getAngleSmearing(TRandom3 &rand, double pt, double C, double S, double N);
double correctPhiRange(double phi);

double getDETA(double eta1, double eta2)
{
    return eta1 - eta2;
}

/*
 * TMath::Pi() is given here
 * https://root.cern.ch/doc/master/TMath_8h_source.html#l00044
 * inline Double_t Pi() { return 3.14159265358979323846; }
 */
double getDPHI(double phi1, double phi2)
{
    double dphi = phi1 - phi2;
    if (dphi > 3.14159265358979323846)
        dphi -= 2*3.14159265358979323846;
    if (dphi <= -1*3.14159265358979323846)
        dphi += 2*3.14159265358979323846;
    if (TMath::Abs(dphi) > 3.14159265358979323846) {
        std::cout << "Error in dphi calculation : |dphi| > PI" << std::endl;
        std::cout << "dphi is set to -999." << std::endl;
        return -999;
    }

    return dphi;
}

double getAbsDPHI(double phi1, double phi2)
{
    return TMath::Abs(getDPHI(phi1, phi2)) ;
}

double getDR(double eta1, double phi1, double eta2, double phi2)
{
    double deta = eta1-eta2;
    double dphi = getDPHI(phi1, phi2);
    return TMath::Sqrt(deta*deta + dphi*dphi);
}

double getDR2(double eta1, double phi1, double eta2, double phi2)
{
    double deta = eta1-eta2;
    double dphi = getDPHI(phi1, phi2);
    return (deta*deta + dphi*dphi);
}

/*
 * calculate resolution using CSN parameterization
 */
double getResolution(double pt, double C, double S, double N)
{
    return TMath::Sqrt( C*C + (S*S)/pt + (N*N)/(pt*pt) );
}

double getEnergySmearingFactor(TRandom3 &rand, double pt, double C, double S, double N)
{
    double sigma = getResolution(pt, C, S, N);

    double smearFactor = -1;
    while (smearFactor < 0) {
        smearFactor = rand.Gaus(1, sigma);
    }

    return smearFactor;
}

double getAngleSmearing(TRandom3 &rand, double pt, double C, double S, double N)
{
    double sigma = getResolution(pt, C, S, N);

    return rand.Gaus(0, sigma);
}

double correctPhiRange(double phi)
{
    while (TMath::Abs(phi) > TMath::Pi())
    {
        if ( phi >    TMath::Pi() )  phi -= 2*TMath::Pi();
        if ( phi < -1*TMath::Pi() )  phi += 2*TMath::Pi();
    }
    return phi;
}

#endif /* PHYSICSUTIL_H_ */

