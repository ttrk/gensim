/*
 * code to modify a spectrum/distribution with a given distribution
 * Ex. smearing energy spectrum with detector resolution
 * fnc1 : spectrum to be modified
 * fnc2 : modifier
 */

#include <TFile.h>
#include <TTree.h>
#include <TH1.h>
#include <TH1D.h>
#include <TH2D.h>
#include <TF1.h>
#include <TMath.h>

#include <string>
#include <vector>
#include <iostream>

#include "../utilities/systemUtil.h"

void setTH1D(TH1D* h);
void modifySpectrum(std::string fnc1, std::string fnc2, std::string outputFile = "modifySpectrum.root");

void modifySpectrum(std::string fnc1, std::string fnc2, std::string outputFile)
{
    std::cout<<"running modifySpectrum()"<<std::endl;
    std::cout<<"fnc1 = " << fnc1.c_str() << std::endl;
    std::cout<<"fnc2 = " << fnc2.c_str() << std::endl;

    std::vector<std::string> fncStrVec = {fnc1, fnc2};

    TFile* output = TFile::Open(outputFile.c_str(),"RECREATE");
    output->cd();

    // TH1 objects
    TH1::SetDefaultSumw2();

    std::vector<TF1*> f1s(2, 0);
    std::vector<TH1D*> h1Ds(2, 0);
    int nBinsX = 1000;

    for (int i = 0; i < 2; ++i) {

        std::cout << "### Parsing info for function " << i+1 << " ###" << std::endl;

        std::vector<std::string> fncInfo = split(fncStrVec[i], ";", false);
        int nFncInfo = fncInfo.size();
        if (nFncInfo < 3) {
            std::cout << "nFncInfo = " << nFncInfo << std::endl;
            std::cout << "A function must have at least 3 pieces of info : formula, xMin, xMax" << std::endl;
            std::cout << "Exiting" << std::endl;
            return;
        }
        f1s[i] = new TF1(Form("f_%d", i), fncInfo[0].c_str());
        f1s[i]->SetRange(std::atof(fncInfo[1].c_str()), std::atof(fncInfo[2].c_str()));

        std::cout << "formula = " << f1s[i]->GetExpFormula() << std::endl;
        std::cout << "xMin = " << f1s[i]->GetXmin() << std::endl;
        std::cout << "xMax = " << f1s[i]->GetXmax() << std::endl;

        int nParFnc = f1s[i]->GetNpar();
        if (i == 0 && nFncInfo - 3 != nParFnc) {
            std::cout << "Function 1 : Number of parameter values provided do not match the number of parameters in the formula" << std::endl;
            std::cout << "Number of values provided = " << nFncInfo - 3 << std::endl;
            std::cout << "Number of parameters in the formula = " << nParFnc << std::endl;
            std::cout << "Exiting" << std::endl;
            return;
        }
        else if (i == 1 && nFncInfo - 3 != nParFnc - 1) {
            // For 2nd function values of parameters must be provided except for one of them
            // The value of 2nd function's last parameter is sampled from the 1st function, no value should be provided for it.
            std::cout << "Function 2 : Number of fixed parameter values provided do not match the number of parameters in the formula" << std::endl;
            std::cout << "Number of values provided = " << nFncInfo - 3 << std::endl;
            std::cout << "Number of parameters in the formula = " << nParFnc << std::endl;
            std::cout << "Exiting" << std::endl;
            return;
        }
        for (int j = 0; j < nParFnc; ++j) {

            if (i == 1 && j == nParFnc - 1) continue;

            f1s[i]->SetParameter(j, std::atof(fncInfo[j+3].c_str()));

            std::cout << Form("par[%d] = ", j) << f1s[i]->GetParameter(j) << std::endl;
        }

        h1Ds[i] = new TH1D(Form("h_%d", i), "", nBinsX, f1s[0]->GetXmin(), f1s[0]->GetXmax());
        if (i == 0) {
            for (int iBin = 1; iBin <= h1Ds[i]->GetNbinsX(); ++iBin) {
                double x = h1Ds[i]->GetBinCenter(iBin);
                h1Ds[i]->SetBinContent(iBin, f1s[i]->Eval(x));
                h1Ds[i]->SetBinError(iBin, 0.00001);
            }
        }
        setTH1D(h1Ds[i]);

        f1s[i]->Write("",TObject::kOverwrite);
        h1Ds[i]->Write("",TObject::kOverwrite);
    }

    TH1D* hOut = new TH1D("hOut", "", nBinsX, f1s[0]->GetXmin(), f1s[0]->GetXmax());

    int nRnd1 = 10000;
    int nRnd2 = 100;
    for (int r1 = 0; r1 < nRnd1; ++r1) {
        double x = f1s[0]->GetRandom(f1s[0]->GetXmin(), f1s[0]->GetXmax());

        f1s[1]->SetParameter(f1s[1]->GetNpar() - 1, x);
        for (int r2 = 0; r2 < nRnd2; ++r2) {
            double tmp = x * f1s[1]->GetRandom(f1s[1]->GetXmin(), f1s[1]->GetXmax());
            hOut->Fill(tmp);
        }
    }
    setTH1D(hOut);
    hOut->Write("",TObject::kOverwrite);

    std::cout<<"Closing the output file."<<std::endl;
    output->Close();
    std::cout<<"running modifySpectrum() - END"<<std::endl;
}

int main(int argc, char** argv)
{
    if (argc == 4) {
        modifySpectrum(argv[1], argv[2], argv[3]);
        return 0;
    }
    else {
        std::cout << "Usage : \n" <<
                "./modifySpectrum.exe <fnc1> <fnc2> <outputFile>"
                << std::endl;
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

