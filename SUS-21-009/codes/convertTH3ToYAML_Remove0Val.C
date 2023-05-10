void convertTH3ToYAML_Remove0Val(TString fname, TString histName){
  TString fname2, name3, name4, modelName;
  if(fname.Contains("T5bbbbZg")){ name3 = "Acc X Eff for T5bbbbZg"; fname2 = "AccXEff_T5bbbbZg_"; modelName = "T5bbbbZg";}
  else if(fname.Contains("T5qqqqHg")){ name3 = "Acc X Eff for T5qqqqHg"; fname2 = "AccXEff_T5qqqqHg_"; modelName = "T5qqqqHg";}
  else if(fname.Contains("T5ttttZg")){ name3 = "Acc X Eff for T5ttttZg"; fname2 = "AccXEff_T5ttttZg_"; modelName = "T5ttttZg";}
  else if(fname.Contains("T6ttZg")){ name3 = "Acc X Eff for T6ttZg"; fname2 = "AccXEff_T6ttZg_"; modelName = "T6ttZg";}
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
  else { name4="SR"; fname2=histName+".yaml";}
  //  name3 = name3+name4;
  
  //  fname = "../"+fname;
  TFile *f = TFile::Open(fname);
  TH3F *h3 = (TH3F*)f->Get(histName);

  TString xName = "$m_{\\tilde{g}$";
  if(fname.Contains("T6ttZg")) xName = "$m_{\\tilde{t}}$";
  TString yName = "$m_{\\tilde{\\chi}^{0}_{1}}$";
  TString zName = "Bin index";

  TString headerY = "- header:\n    name: "+yName+"\n    units: GeV\n  values:\n";
  TString headerZ = "- header:\n    name: "+zName+"\n    units: GeV\n  values:\n";
  TString cntHeader = "- header:\n    name: Acceptance x Efficiency\n  values:\n";
  TString headerX = "independent_variables:\n- header:\n    name: "+xName+"\n    units: GeV\n  values:\n";

  TString opText = "dependent_variables:\n";

  TString submissionText = "\n---\nname: "+name3+"\n";
  submissionText+="location: Additional information\n";
  submissionText+="description:  Acceptance times efficiency values with statistical uncertainties for "+modelName+" in the "+name4+" region.\n";
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
  int nZ = h3->GetNbinsZ();
  cout<<"nX = "<<h3->GetNbinsX()<<" , ";
  cout<<"nY = "<<h3->GetNbinsY()<<" , ";
  cout<<"nZ = "<<h3->GetNbinsZ()<<" , "<<endl;
  float val;
  nX=600,nY=600,nZ=46;
  int maxDM = 0;
  if(modelName=="T5qqqqHg") maxDM = 124;
  ofstream ofile(fname2);
  ofile<<headerX;
  int a=0,b=0,q[2],l[2],count=0;
  for(int i=301;i<=nX;i=i+1){
    for(int j=11;j<=nY;j=j+1){
      if(h3->GetBinContent(i,j,2)>0) {
	count++;
	q[0]=i,l[0]=j;
	if(count==1) {l[1]=l[0];continue;}
      }
      for(int k=1;k<=nZ;k++){
        val = h3->GetBinContent(i,j,k);
	if(val<=0) continue;
	if(val>0)
	  {
	    //	    cout<<i<<" "<<h3->GetXaxis()->GetBinLowEdge(q[0])<<" "<<h3->GetXaxis()->GetBinLowEdge(q[0]+10)<<" "<<h3->GetYaxis()->GetBinLowEdge(l[1])<<" "<<h3->GetYaxis()->GetBinLowEdge(l[0])<<" "<<h3->GetZaxis()->GetBinLowEdge(k)<<" "<<h3->GetZaxis()->GetBinLowEdge(k+1)<<" "<<val<<" "<<endl;
	    ofile<<"  - high: "<<h3->GetXaxis()->GetBinLowEdge(q[0]+10)<<"\n    low: "<<h3->GetXaxis()->GetBinLowEdge(q[0])<<endl;
	  }
      }
      q[1]=i,l[1]=j;
    }
  }


  ofile<<headerY;
  count=0;
  for(int i=301;i<=nX;i=i+1){
    for(int j=11;j<=nY;j=j+1){
      if(h3->GetBinContent(i,j,2)>0) {
        count++;
        l[0]=j;
        if(count==1) {l[1]=l[0];continue;}
      } 
      for(int k=1;k<=nZ;k++){
	val = h3->GetBinContent(i,j,k);
        if(val<=0) continue;
        if(val>0)
          {
            ofile<<"  - high: "<<h3->GetXaxis()->GetBinLowEdge(l[0])<<"\n    low: "<<h3->GetXaxis()->GetBinLowEdge(l[1])<<endl;
          }
      } 
      l[1]=j;
    }
  }
  
  ofile<<headerZ;
  count=0;
  for(int i=301;i<=nX;i=i+1){
    for(int j=11;j<=nY;j=j+1){
      if(h3->GetBinContent(i,j,2)>0) {
        count++;
        if(count==1) continue;
      }
      for(int k=1;k<=nZ;k++){
	val = h3->GetBinContent(i,j,k);
	if(val<=0) continue;
        if(val>0){
	    ofile<<"  - high: "<<h3->GetZaxis()->GetBinLowEdge(k+1)<<"\n    low: "<<h3->GetZaxis()->GetBinLowEdge(k)<<endl;
	}
      }
    }
  }

  ofile<<"dependent_variables:\n";
  ofile<<cntHeader;
  count=0;
  for(int i=301;i<=nX;i=i+1){
    for(int j=11;j<=nY;j=j+1){
      if(h3->GetBinContent(i,j,2)>0) {
        count++;
	if(count==1) continue;
      }
      for(int k=1;k<=nZ;k++){
	
	float err = h3->GetBinError(i,j,k);
	val = h3->GetBinContent(i,j,k);
        if(val<=0) continue;
	if(val < 1e-13){ val = 1e-12; err = 1e-12;}
        if(val>0){
	  ofile<<"  - errors:\n";
	  ofile<<"    - label: stat\n";
	  ofile<<"      symerror: "<<err<<endl;
	  ofile<<"    value: "<<val<<endl;
	}
	//if(err > 1e-12) ofile<<"      symerror: "<<err<<endl;
	// else ofile<<"      symerror: '~'"<<endl;
	// if(val > 1e-12) ofile<<"    value: "<<val<<endl;
	// else ofile<<"    value: '~'"<<endl;
      }
    }
  }
   
  //  cout<<headerY<<headerZ<<cntHeader<<headerX<<endl;
  cout<<submissionText;
  //  cout<<submissionText;
  

}
