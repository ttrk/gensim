/*
 * code to modify a spectrum/distribution with a given distribution
 * Ex. smearing energy spectrum with detector resolution
 * input 1 : spectrum to be modified
 * input 2 : modifier
 */

#include <TFile.h>
#include <TTree.h>
#include <TH1.h>
#include <TH1D.h>
#include <TH2D.h>
#include <TF1.h>
#include <TFormula.h>
#include <TMath.h>

#include <string>
#include <vector>
#include <iostream>

#include "../utilities/systemUtil.h"
#include "../utilities/mathUtil.h"
#include "../utilities/physicsUtil.h"
#include "../utilities/ArgumentParser.h"

enum MODES {
    kSpectrumIsTF1,
    kSpectrumIsTH1,
    kN_MODES
};

enum INPUTS {
    kSpectrum,
    kModifier,
    kN_INPUTS
};

enum FNCS {
    kDSCB,
    kN_FNCS
};

const std::string inputsStr[kN_INPUTS] = {"Spectrum", "Modifier"};
const std::string fncsStr[kN_FNCS] = {"DSCB"};

std::vector<std::string> argOptions;

void setTH1D(TH1D* h);
void modifySpectrum(int mode, std::string spectrumStr, std::string modifierStr, std::string outputFile = "modifySpectrum.root");

void modifySpectrum(int mode, std::string spectrumStr, std::string modifierStr, std::string outputFile)
{
    std::cout<<"running modifySpectrum()"<<std::endl;

    std::cout << "##### Parameters #####" << std::endl;
    std::cout<<"mode = " << mode << std::endl;
    std::cout<< inputsStr[kSpectrum].c_str() << " = " << spectrumStr.c_str() << std::endl;
    std::cout<< inputsStr[kModifier].c_str() << " = " << modifierStr.c_str() << std::endl;
    std::cout << "##### Parameters - END #####" << std::endl;

    if (mode >= kN_MODES) {
        std::cout << "mode must be smaller than " << kN_MODES << std::endl;
        std::cout << "Exiting" << std::endl;
        return;
    }

    std::string operation = (ArgumentParser::ParseOptionInputSingle("--operation", argOptions).size() > 0) ?
            ArgumentParser::ParseOptionInputSingle("--operation", argOptions).c_str() : "MUL";

    bool correctPhi = (ArgumentParser::ParseOptionInputSingle("--correctPhi", argOptions).size() > 0) ?
            (std::atoi(ArgumentParser::ParseOptionInputSingle("--correctPhi", argOptions).c_str()) > 0) : false;

    std::cout << "##### Optional Arguments #####" << std::endl;
    std::cout << "operation = " << operation.c_str() << std::endl;
    std::cout << "correctPhi = " << correctPhi << std::endl;
    std::cout << "##### Optional Arguments - END #####" << std::endl;

    std::vector<std::string> fncStrVec = {spectrumStr, modifierStr};

    TFile* input = 0;

    TFile* output = TFile::Open(outputFile.c_str(),"RECREATE");
    output->cd();

    // TH1 objects
    TH1::SetDefaultSumw2();

    std::vector<TF1*> f1s(kN_INPUTS, 0);
    std::vector<TH1D*> h1Ds(kN_INPUTS, 0);
    std::vector<TH1D*> h1DsSubRange(kN_INPUTS, 0);
    int nBinsX = 1000;
    double h1D_xMin = 0;
    double h1D_xMax = 0;
    double range_xMin = 0;
    double range_xMax = 0;

    for (int i = 0; i < kN_INPUTS; ++i) {

        std::cout << "### Parsing info for " << inputsStr[i].c_str() << " ###" << std::endl;

        std::vector<std::string> fncInfo = split(fncStrVec[i], ";", false);
        int nFncInfo = fncInfo.size();

        if (i == kSpectrum && mode == kSpectrumIsTH1) {
            if (nFncInfo < 4) {
                std::cout << "Spectrum is given as TH1" << std::endl;
                std::cout << "nFncInfo = " << nFncInfo << std::endl;
                std::cout << "An histograms must have at least 3 pieces of info : path to File, path in file, xMin, xMax" << std::endl;
                std::cout << "Exiting" << std::endl;
                return;
            }

            input = TFile::Open(fncInfo[0].c_str(),"READ");
            input->cd();
            h1Ds[i] = (TH1D*)(input->Get(fncInfo[1].c_str()))->Clone(Form("h_%d", i));
            output->cd();

            double xMinTmp = std::atof(fncInfo[2].c_str());
            double xMaxTmp = std::atof(fncInfo[3].c_str());
            if (xMaxTmp > xMinTmp)  {
                h1Ds[i]->GetXaxis()->SetRangeUser(xMinTmp, xMaxTmp);
            }

            h1D_xMin = h1Ds[i]->GetXaxis()->GetXmin();
            h1D_xMax = h1Ds[i]->GetXaxis()->GetXmax();
            range_xMin = h1D_xMin;
            range_xMax = h1D_xMax;
        }
        else {
            if (nFncInfo < 3) {
                std::cout << "nFncInfo = " << nFncInfo << std::endl;
                std::cout << "A function must have at least 3 pieces of info : formula, xMin, xMax" << std::endl;
                std::cout << "Exiting" << std::endl;
            }

            std::cout << "fncInfo[0] = " << fncInfo[0].c_str() << std::endl;
            int nParFnc = 0;
            if (fncInfo[0] == fncsStr[kDSCB].c_str()) {
                f1s[i] = new TF1(Form("f_%d", i), fnc_DSCB, 0, 1, getFncNpar(fnc_DSCB));
                std::cout << "formula = " << "DSCB" << std::endl;
                nParFnc = getFncNpar(fnc_DSCB);
            }
            else {
                f1s[i] = new TF1(Form("f_%d", i), fncInfo[0].c_str());
                std::cout << "formula = " << f1s[i]->GetExpFormula() << std::endl;
                nParFnc = f1s[i]->GetNpar();
            }
            f1s[i]->SetRange(std::atof(fncInfo[1].c_str()), std::atof(fncInfo[2].c_str()));
            std::cout << "xMin = " << f1s[i]->GetXmin() << std::endl;
            std::cout << "xMax = " << f1s[i]->GetXmax() << std::endl;


            if (fncInfo[0] != fncsStr[kDSCB].c_str()) {
                if (i == kSpectrum && nFncInfo - 3 != nParFnc) {
                    std::cout << "Function 1 : Number of parameter values provided do not match the number of parameters in the formula" << std::endl;
                    std::cout << "Number of values provided = " << nFncInfo - 3 << std::endl;
                    std::cout << "Number of parameters in the formula = " << nParFnc << std::endl;
                    std::cout << "Exiting" << std::endl;
                    return;
                }
                else if (i == kModifier && nFncInfo - 3 != nParFnc - 1) {
                    // For 2nd function values of parameters must be provided except for one of them
                    // The value of 2nd function's last parameter is sampled from the 1st function, no value should be provided for it.
                    std::cout << "Function 2 : Number of fixed parameter values provided do not match the number of parameters in the formula" << std::endl;
                    std::cout << "Number of values provided = " << nFncInfo - 3 << std::endl;
                    std::cout << "Number of parameters in the formula = " << nParFnc << std::endl;
                    std::cout << "Exiting" << std::endl;
                    return;
                }
            }
            if (fncInfo[0] == fncsStr[kDSCB].c_str() && nFncInfo - 3 != 7) {
                std::cout << "DSCB : Number of parameter values provided do not match the number of parameters in the formula" << std::endl;
                std::cout << "Number of values provided = " << nFncInfo - 3 << std::endl;
                std::cout << "Number of parameters for DSCB = " << 7 << std::endl;
                std::cout << "Exiting" << std::endl;
                return;
            }

            for (int j = 0; j < nParFnc; ++j) {

                if (fncInfo[0] == fncsStr[kDSCB].c_str()) {
                }
                else if (i == kModifier && j == nParFnc - 1) {
                    continue;
                }

                f1s[i]->SetParameter(j, std::atof(fncInfo[j+3].c_str()));

                std::cout << Form("par[%d] = ", j) << f1s[i]->GetParameter(j) << std::endl;
            }

            if (i == kSpectrum) {
                h1D_xMin = f1s[kSpectrum]->GetXmin();
                h1D_xMax = f1s[kSpectrum]->GetXmax();
                range_xMin = h1D_xMin;
                range_xMax = h1D_xMax;
            }

            h1Ds[i] = new TH1D(Form("h_%d", i), "", nBinsX, h1D_xMin, h1D_xMax);
            if (i == kSpectrum) {
                for (int iBin = 1; iBin <= h1Ds[i]->GetNbinsX(); ++iBin) {
                    double x = h1Ds[i]->GetBinCenter(iBin);
                    h1Ds[i]->SetBinContent(iBin, f1s[i]->Eval(x));
                    h1Ds[i]->SetBinError(iBin, 0.000000000001 * h1Ds[i]->GetBinContent(iBin));
                }
            }
        }
        setTH1D(h1Ds[i]);

        int nBinsTmp = h1Ds[kSpectrum]->FindBin(h1D_xMax) - h1Ds[kSpectrum]->FindBin(h1D_xMin);
        h1DsSubRange[i] = new TH1D(Form("h_%d_subRange", i), "", nBinsTmp, h1D_xMin, h1D_xMax);
        if (i == kSpectrum) {
            for (int iBin = 1; iBin <= h1DsSubRange[i]->GetNbinsX(); ++iBin) {
                if (h1DsSubRange[i]->GetBinLowEdge(iBin) >= range_xMin && h1DsSubRange[i]->GetBinLowEdge(iBin) < range_xMax) {
                    double x = h1DsSubRange[i]->GetBinCenter(iBin);
                    h1DsSubRange[i]->SetBinContent(iBin, h1Ds[i]->GetBinContent(h1Ds[i]->FindBin(x)));
                    h1DsSubRange[i]->SetBinError(iBin, h1Ds[i]->GetBinError(h1Ds[i]->FindBin(x)));
                }
            }
        }
        setTH1D(h1DsSubRange[i]);

        if (f1s[i] != 0)  f1s[i]->Write("",TObject::kOverwrite);
        if (h1Ds[i] != 0)  h1Ds[i]->Write("",TObject::kOverwrite);
        if (h1DsSubRange[i] != 0)  h1DsSubRange[i]->Write("",TObject::kOverwrite);
    }

    TH1D* hOut = new TH1D("hOut", "", h1Ds[kSpectrum]->GetNbinsX(), h1D_xMin, h1D_xMax);

    std::vector<int> nRnds(kN_INPUTS, 0);
    nRnds[kSpectrum] = 10000;
    nRnds[kModifier] = 100;
    for (int r1 = 0; r1 < nRnds[kSpectrum]; ++r1) {
        double x = 0;
        if (mode == kSpectrumIsTF1)  {
            x = f1s[kSpectrum]->GetRandom(f1s[kSpectrum]->GetXmin(), f1s[kSpectrum]->GetXmax());
        }
        else if (mode == kSpectrumIsTH1)  {
            x = h1DsSubRange[kSpectrum]->GetRandom();
        }

        f1s[kModifier]->SetParameter(f1s[kModifier]->GetNpar() - 1, x);
        for (int r2 = 0; r2 < nRnds[kModifier]; ++r2) {
            double tmp = -1;
            double rndTmp = f1s[kModifier]->GetRandom(f1s[kModifier]->GetXmin(), f1s[kModifier]->GetXmax());
            if (operation == "MUL") {
                tmp = x * rndTmp;
            }
            else if (operation == "ADD") {
                tmp = x + rndTmp;
            }

            if (correctPhi) {
                tmp = TMath::Abs(correctPhiRange(tmp));
            }

            hOut->Fill(tmp);
        }
    }

    for (int i = 0; i < kN_INPUTS; ++i) {
        if (f1s[i] != 0)  f1s[i]->Write("",TObject::kOverwrite);
    }

    hOut->Scale(h1DsSubRange[kSpectrum]->Integral() / hOut->GetEntries());

    setTH1D(hOut);
    hOut->Write("",TObject::kOverwrite);

    std::cout<<"Closing the output file."<<std::endl;
    output->Close();
    std::cout<<"running modifySpectrum() - END"<<std::endl;
}

int main(int argc, char** argv)
{
    std::vector<std::string> argStr = ArgumentParser::ParseParameters(argc, argv);
    int nArgStr = argStr.size();

    argOptions = ArgumentParser::ParseOptions(argc, argv);

    if (nArgStr == 5) {
        modifySpectrum(std::atoi(argv[1]), argv[2], argv[3], argv[4]);
        return 0;
    }
    else {
        std::cout << "Usage : \n" <<
                "./modifySpectrum.exe <mode> <spectrum> <modifier> <outputFile>"
                << std::endl;

        std::cout << "Options are" << std::endl;
        std::cout << "operation=<operation used in modifying a value. Eg. MUL for multiplication, ADD for addition" << std::endl;
        std::cout << "correctPhi=<flag whether the modified value should be corrected into [-pi, pi] range. "
                     "This is useful if an angle distribution is modified" << std::endl;

        return 1;
    }
}

void setTH1D(TH1D* h)
{
    h->SetMarkerStyle(kFullCircle);
    h->SetMarkerColor(kBlack);

    h->SetTitleOffset(1.25, "X");
    h->SetTitleOffset(1.5, "Y");
}

