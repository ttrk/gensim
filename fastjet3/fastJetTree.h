#ifndef TREEHEADERS_FASTJETTREE_H_
#define TREEHEADERS_FASTJETTREE_H_

#include <TTree.h>
#include <TBranch.h>

#include <vector>

class fastJetTree {
public :
  fastJetTree() {

    jetpt = 0;
    jeteta = 0;
    jetphi = 0;

  };
  ~fastJetTree(){};
  void setupTreeForReading(TTree *t);
  void branchTree(TTree *t);
  void clearEvent();

  // Declaration of leaf types
  Int_t           nJet;
  std::vector<float>   *jetpt;
  std::vector<float>   *jeteta;
  std::vector<float>   *jetphi;

  // List of branches
  TBranch        *b_nJet;   //!
  TBranch        *b_jetpt;   //!
  TBranch        *b_jeteta;   //!
  TBranch        *b_jetphi;   //!
};

void fastJetTree::setupTreeForReading(TTree *t)
{
    // Set branch addresses and branch pointers
    if (t->GetBranch("nJet")) t->SetBranchAddress("nJet", &nJet, &b_nJet);
    if (t->GetBranch("jetpt")) t->SetBranchAddress("jetpt", &jetpt, &b_jetpt);
    if (t->GetBranch("jeteta")) t->SetBranchAddress("jeteta", &jeteta, &b_jeteta);
    if (t->GetBranch("jetphi")) t->SetBranchAddress("jetphi", &jetphi, &b_jetphi);
}

void fastJetTree::branchTree(TTree *t)
{
    t->Branch("nJet", &nJet);
    t->Branch("jetpt", &jetpt);
    t->Branch("jeteta", &jeteta);
    t->Branch("jetphi", &jetphi);
}

void fastJetTree::clearEvent()
{
    nJet = 0;
    jetpt->clear();
    jeteta->clear();
    jetphi->clear();
}

#endif /* TREEHEADERS_FASTJETTREE_H_ */
