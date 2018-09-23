/*
 * class to read TTree for jetphox events
 */
#ifndef JETPHOXTREE_H_
#define JETPHOXTREE_H_

#include <TTree.h>
#include <TBranch.h>
#include <Riostream.h>
#include <TList.h>
#include <TVectorT.h>

#include <vector>

const unsigned int max_ntrack = 200;
const unsigned int max_nb_member = 4500;

class jetphoxTree {
public :
  jetphoxTree() {
  };
  ~jetphoxTree(){};
  void setupTreeForReading(TTree *t);
  void branchTree(TTree *t);
  void clearEvent();
  void getHeaderInfo(TTree *t);

  double p(int iObj);
  double pt(int iObj);
  double y(int iObj);
  double eta(int iObj);
  double phi(int iObj);

  // objects for header information
  float nb_evt;
  float xsec;
  float sqrt_s;

  // Declaration of leaf types
  int           iprov;
  int           ntrack;
  int           nb_member;
  double        x3;
  double        energy[max_ntrack];   //[ntrack]
  double        px[max_ntrack];   //[ntrack]
  double        py[max_ntrack];   //[ntrack]
  double        pz[max_ntrack];   //[ntrack]
  float         pdf_weight[max_nb_member];   //[nb_member]

  // List of branches
  TBranch        *b_iprov;   //!
  TBranch        *b_ntrack;   //!
  TBranch        *b_nb_member;   //!
  TBranch        *b_x3;   //!
  TBranch        *b_energy;   //!
  TBranch        *b_px;   //!
  TBranch        *b_py;   //!
  TBranch        *b_pz;   //!
  TBranch        *b_pdf_weight;   //!
};

void jetphoxTree::setupTreeForReading(TTree *t)
{
    // Set branch addresses and branch pointers
    t->SetBranchAddress("iprov", &iprov, &b_iprov);
    t->SetBranchAddress("ntrack", &ntrack, &b_ntrack);
    t->SetBranchAddress("nb_member", &nb_member, &b_nb_member);
    t->SetBranchAddress("x3", &x3, &b_x3);
    t->SetBranchAddress("energy", energy, &b_energy);
    t->SetBranchAddress("px", px, &b_px);
    t->SetBranchAddress("py", py, &b_py);
    t->SetBranchAddress("pz", pz, &b_pz);
    t->SetBranchAddress("pdf_weight", pdf_weight, &b_pdf_weight);
}

void jetphoxTree::branchTree(TTree *t)
{
    t->Branch("iprov",&iprov,"iprov/I");
    t->Branch("ntrack",&ntrack,"ntrack/I");
    t->Branch("nb_member",&nb_member,"nb_member/I");
    t->Branch("x3",&x3,"x3/F");
    t->Branch("energy",energy,"energy[max_ntrack]/F");
    t->Branch("px",px,"px[max_ntrack]/F");
    t->Branch("py",py,"py[max_ntrack]/F");
    t->Branch("pz",pz,"pz[max_ntrack]/F");
    t->Branch("pdf_weight",pdf_weight,"pdf_weight[max_nb_member]/F");
    t->Branch("energy",energy,"energy[max_ntrack]/F");
    t->Branch("energy",energy,"energy[max_ntrack]/F");
}

void jetphoxTree::clearEvent()
{
    ntrack = 0;
    nb_member = 0;
}

void jetphoxTree::getHeaderInfo(TTree* t)
{
    TList* list = t->GetUserInfo();
    list->Print();
    TVectorT<float> &v = *((TVectorT<float>*)(list->At(0)));
    nb_evt = v[0];
    xsec = v[1];
    sqrt_s = v[2];

    list->Delete();
}

/*
 * magnitude of 3-momentum
 */
double jetphoxTree::p(int iObj)
{
    return std::sqrt(px[iObj]*px[iObj] + py[iObj]*py[iObj] + pz[iObj]*pz[iObj]);
}

double jetphoxTree::pt(int iObj)
{
    return std::sqrt(px[iObj]*px[iObj] + py[iObj]*py[iObj]);
}

double jetphoxTree::y(int iObj)
{
    return 0.5 * std::log( (energy[iObj]+pz[iObj]) / (energy[iObj]-pz[iObj]) );
}

double jetphoxTree::eta(int iObj)
{
    double pTmp = p(iObj);
    return 0.5 * std::log( (pTmp+pz[iObj]) / (pTmp-pz[iObj]) );
}

/*
 * TVector3::Phi()
 * https://root.cern.ch/doc/master/TVector3_8cxx_source.html#l00230
 * TMath::ATan2(Double_t y, Double_t x)
 * https://root.cern.ch/doc/master/TMath_8h_source.html#l00667
 */
double jetphoxTree::phi(int iObj)
{
    return (px[iObj] == 0.0 && py[iObj] == 0.0) ? 0.0 : TMath::ATan2(py[iObj], px[iObj]);
}

#endif /* JETPHOXTREE_H_ */
