#include <iostream>
#include <fstream>
#include "TH2D.h"
#include "TFile.h"

using namespace std;

void histtoText(TString infile, TString ofile)
{
  TFile* f = new TFile(infile);
  TH1D *zin = (TH1D*)f->Get("Zin");
  TH1D *ll = (TH1D*)f->Get("LL");
  TH1D *fr = (TH1D*)f->Get("FR");
  TH1D *multi = (TH1D*)f->Get("QCD");
  TH1D *total = (TH1D*)f->Get("TotalBG");
  TH1D *hd = (TH1D*)f->Get("DataFit");
  TFile *f1 = new TFile("../rootfiles/T5bbbbZg_2200_200_FastSim_v18.root");
  TH1D *s1 = (TH1D*)f1->Get("AllSBins_v6_CD_EW_50bin_dphi");
  TFile *f2 = new TFile("../rootfiles/T5bbbbZg_2200_2100_FastSim_v18.root");
  TH1D *s2 = (TH1D*)f2->Get("AllSBins_v6_CD_EW_50bin_dphi");
  TFile *f3 = new TFile("../rootfiles/TChiWG_0_1000_FastSim_v18.root");
  TH1D *s3 = (TH1D*)f3->Get("AllSBins_v6_CD_EW_50bin_dphi");
  //  TGraph* graph=(TGraph*)file->Get(name);
  ofstream outfile(ofile);


    // Loop over the bins and write the bin content to the text file
    for (int i = 1; i <= zin->GetNbinsX(); i++)
      {
	outfile<<i<<" "<<ll->GetBinContent(i)<<" "<<ll->GetBinError(i)<<" "<<fr->GetBinContent(i)<<" "<<fr->GetBinError(i)<<" "<<zin->GetBinContent(i)<<" "<<zin->GetBinError(i)<<" "<<multi->GetBinContent(i)<<" "<<multi->GetBinError(i)<<" "<<total->GetBinContent(i)<<" "<<total->GetBinError(i)<<" "<<hd->GetBinContent(i)<<" "<<s1->GetBinContent(i+1)<<" "<<s1->GetBinError(i+1)<<" "<<s2->GetBinContent(i+1)<<" "<<s2->GetBinError(i+1)<<" "<<s3->GetBinContent(i+1)<<" "<<s3->GetBinError(i+1)<<endl;
      }
    //}
    // Close the output file and the ROOT file
  outfile.close();
  f->Close();
}
