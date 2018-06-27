#ifndef PARTICLETREE_H_
#define PARTICLETREE_H_

#include <TTree.h>
#include <TBranch.h>

#include <vector>

class particleTree {
public :
  particleTree() {

    pt = 0;
    eta = 0;
    phi = 0;
    chg = 0;

  };
  ~particleTree(){};
  void setupTreeForReading(TTree *t);
  void branchTree(TTree *t);
  void clearEvent();

  // Declaration of leaf types
  Int_t           n;
  std::vector<float>   *pt;
  std::vector<float>   *eta;
  std::vector<float>   *phi;
  std::vector<float>   *chg;    // charge

  // List of branches
  TBranch        *b_n;   //!
  TBranch        *b_pt;   //!
  TBranch        *b_eta;   //!
  TBranch        *b_phi;   //!
  TBranch        *b_chg;   //!
};

void particleTree::setupTreeForReading(TTree *t)
{
    // Set branch addresses and branch pointers
    if (t->GetBranch("n")) t->SetBranchAddress("n", &n, &b_n);
    if (t->GetBranch("pt")) t->SetBranchAddress("pt", &pt, &b_pt);
    if (t->GetBranch("eta")) t->SetBranchAddress("eta", &eta, &b_eta);
    if (t->GetBranch("phi")) t->SetBranchAddress("phi", &phi, &b_phi);
    if (t->GetBranch("chg")) t->SetBranchAddress("chg", &chg, &b_chg);
}

void particleTree::branchTree(TTree *t)
{
    t->Branch("n", &n);
    t->Branch("pt", &pt);
    t->Branch("eta", &eta);
    t->Branch("phi", &phi);
    t->Branch("chg", &chg);
}

void particleTree::clearEvent()
{
    n = 0;
    pt->clear();
    eta->clear();
    phi->clear();
    chg->clear();
}

#endif /* PARTICLETREE_H_ */
