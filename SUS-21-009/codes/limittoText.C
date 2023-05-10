#include <iostream>
#include <fstream>
#include "TH2D.h"
#include "TFile.h"

using namespace std;

void limittoText(TString infile, TString ofile, TString name)
{
  TString name1, name2, name3;

  if(name.Contains("exp"))  name1="exp", name2="exp16pc", name3="exp84pc";//exp obs exp16pc exp84pc obs_up obs_dn
  else if(name.Contains("obs")) name1="obs", name2="obs_up", name3="obs_dn"; 
  TFile* file = new TFile(infile);
  TGraph* graph1=(TGraph*)file->Get(name1);
  TGraph *graph2,*graph3;
  if(infile.Contains("T5") || infile.Contains("T6") || (infile.Contains("TChi") && name.Contains("exp"))){
    graph2=(TGraph*)file->Get(name2);
    graph3=(TGraph*)file->Get(name3);
  }
  ofstream outfile(ofile);
  //  strcpy(str, "-");
  float val = atof("-");
  val=-1;
  //  if(infile.Contains("T5") || infile.Contains("T6")){
    // Loop over the bins and write the bin content to the text file
    if(infile.Contains("T5") || infile.Contains("T6") || (infile.Contains("TChi") && name.Contains("exp"))){

      for (int i = 1; i <= graph1->GetN(); i++)
	{
	  double x, y;
	  graph1->GetPoint(i, x, y);
	  outfile<< x << " " << y<<" " <<val<<" "<<val<<endl;
	}
      
      for (int i = 1; i <= graph2->GetN(); i++)
	{
	  double x, y;
	  graph2->GetPoint(i, x, y);
	  outfile<< x << " " <<val<<" "<< y<<" "<<val<< endl;
	}
      for (int i = 1; i <= graph3->GetN(); i++)
	{
	  double x, y;
	  graph3->GetPoint(i, x, y);
	  outfile<< x <<" "<<val<<" "<<val<<" "<<y<< endl;
	}
    }
    else{
      for (int i = 1; i <= graph1->GetN(); i++)
        {
          double x, y;
          graph1->GetPoint(i, x, y);
          outfile<< x << " " << y<<endl;
        }

    }

    //}
    // Close the output file and the ROOT file
  outfile.close();
  file->Close();
}
