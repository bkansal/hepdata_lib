void convertTH2ToYAML_Remove0Val(TString fname, TString histName){
  TString fname2, name3, name4, modelName;
  if(fname.Contains("T5bbbbZg")){ name3 = "Figure 9 (top left) "; fname2 = "AccXEff_T5bbbbZg_"; modelName = "T5bbbbZg";}
  else if(fname.Contains("T5ttttZg")){ name3 = "Figure 9 (bottom left) "; fname2 = "AccXEff_T5ttttZg_"; modelName = "T5ttttZg";}
  else if(fname.Contains("T5qqqqHg")){ name3 = "Figure 9 (top right) "; fname2 = "AccXEff_T5qqqqHg_"; modelName = "T5qqqqHg";}
  else if(fname.Contains("T6ttZg")){ name3 = "Figure 9 (bottom right) "; fname2 = "AccXEff_T6ttZg_"; modelName = "T6ttZg";}

  else{
    name3 = "Short description";
    fname2 = fname;
    fname2.ReplaceAll(".root","");
    modelName = "modelName";
  }

  if(histName.Contains("WHSR")){ name4="WHSR"; fname2+="WHSR.yaml";}
  else if(histName.Contains("WSR")){ name4="WSR"; fname2+="WSR.yaml";}
  else if(histName.Contains("HSR")){ name4="HSR"; fname2+="HSR.yaml";}
  else if(histName.Contains("bVeto")){ name4="b-Veto"; fname2+="bVeto.yaml";}
  else { name4="Observed xsec"; fname2=modelName+"_xsec_obs.yaml";}
  name4 = name3+name4;
  
  //  fname = "../"+fname;
  TFile *f = TFile::Open(fname);
  TH2D *h3 = (TH2D*)f->Get(histName);

  TString xName = "$m_{\\tilde{g}}$";
  if(fname.Contains("T6ttZg")) xName = "$m_{\\tilde{t}}$";
  TString yName = "$m_{\\tilde{\\chi}^{0}_{1}}$";

  TString headerY = "- header:\n    name: "+yName+"\n    units: GeV\n  values:\n";
  TString cntHeader = "- header:\n    name: $\\sigma_{observed}$\n    units: pb\n  values:\n";
  TString headerX = "independent_variables:\n- header:\n    name: "+xName+"\n    units: GeV\n  values:\n";
  TString opText = "dependent_variables:\n";

  TString submissionText = "\n---\nname: "+name4+".\n";
  submissionText+="location: Data from "+name3+", located on page 17.\n";
  submissionText+="description: The 95% CL observed upper limits on the production cross sections for "+xName+" in "+modelName+".\n";
  submissionText+="keywords:\n";
  submissionText+="- name: reactions\n  values:\n  - p p\n";
  submissionText+="- name: observables\n  values:\n  - cross-section\n";
  submissionText+="- name: cmenergies\n  values:\n  - '13000'\n";
  submissionText+="- name: phrases\n  values:\n  - SUSY\n  - Supersymmetry\n  - Strong production\n  - Proton-Proton\n  - Scattering\n";
  submissionText+="data_file: "+fname2+"\n";


  // int nX = 3;
  // int nY = 3;

  int nX = h3->GetNbinsX();
  int nY = h3->GetNbinsY();
  cout<<"nX = "<<h3->GetNbinsX()<<" , ";
  cout<<"nY = "<<h3->GetNbinsY()<<" , ";
  float val;
  int maxDM = 0;
  if(modelName=="T5qqqqHg") maxDM = 124;
  ofstream ofile(fname2);
  ofile<<headerX;
  int a=0,b=0;
  int k[2],l[2],count=0, countx=0, county=0;
  for (int i = 300; i <= h3->GetNbinsX(); i=i+1)
    {
      for (int j = 2; j <= h3->GetNbinsY(); j=j+1)
	{
          float val = h3->GetBinContent(i,j);
          float valerr = h3->GetBinError(i,j);
          if(val>0)
            {
              count++;
              k[0]=i,l[0]=j;
              if(count==1) {l[1]=l[0]; continue;}
	      // cout<<i<<" "<<h3->GetXaxis()->GetBinLowEdge(k[0])<<" "<<h3->GetXaxis()->GetBinLowEdge(k[0]+50)<<" "<<h3->GetYaxis()->GetBinLowEdge(l[1])<<" "<<h3->GetYaxis()->GetBinLowEdge(l[0])<<" "<<val<<" "<<endl;
	      ofile<<"  - high: "<<h3->GetXaxis()->GetBinLowEdge(k[0]+50)<<"\n    low: "<<h3->GetXaxis()->GetBinLowEdge(k[0])<<endl;
                k[1]=i,l[1]=j;
	    }
	}
    }
  
  ofile<<headerY;
  count=0;
    for (int i = 300; i <= h3->GetNbinsX(); i=i+1)
    {
      for (int j = 2; j <= h3->GetNbinsY(); j=j+1)
        {
          float val = h3->GetBinContent(i,j);
          float valerr = h3->GetBinError(i,j);
          if(val>0)
	    {
              count++;
              k[0]=i,l[0]=j;
	      if(count==1) {l[1]=l[0]; continue;}
              ofile<<"  - high: "<<h3->GetYaxis()->GetBinLowEdge(l[0])<<"\n    low: "<<h3->GetYaxis()->GetBinLowEdge(l[1])<<endl;
	      k[1]=i,l[1]=j;
            }
        }
    }


  ofile<<"dependent_variables:\n";
  ofile<<cntHeader;
  count=0;
  for (int i = 300; i <= h3->GetNbinsX(); i=i+1)
    {
      for (int j = 2; j <= h3->GetNbinsY(); j=j+1)
        {
          float val = h3->GetBinContent(i,j);
          float valerr = h3->GetBinError(i,j);

	  if(val>0){
	    count++;
	    k[0]=i,l[0]=j;
	    if(count==1) continue;
	    ofile<<"  - errors:\n";
	    ofile<<"    - label: stat\n";
	    ofile<<"      symerror: "<<valerr<<endl;
	    ofile<<"    value: "<<val<<endl;
	    k[1]=i,l[1]=j;
	  }
	//if(err > 1e-12) ofile<<"      symerror: "<<err<<endl;
	// else ofile<<"      symerror: '~'"<<endl;
	// if(val > 1e-12) ofile<<"    value: "<<val<<endl;
	// else ofile<<"    value: '~'"<<endl;
	}
    }
  
  
  //cout<<headerY<<headerZ<<cntHeader<<headerX<<endl;
  cout<<submissionText;
  
}
