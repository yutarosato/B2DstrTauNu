void draws_ck(){
  const Int_t   nvar    = 3;
  const Int_t   fl_mode = 0;
  const Char_t* type    = "nor";
  const Char_t* tag     = "test13";
  TChain* c_sig = new TChain("h15");
  TChain* c_bkg = new TChain("h15");
  std::cout << Form("[sig,mode%d] ",fl_mode) << c_sig->Add( Form("check/ck_mode%d_%s_%s_flsb1.root", fl_mode, tag, type) ) << std::endl;
  std::cout << Form("[bkg,mode%d] ",fl_mode) << c_bkg->Add( Form("check/ck_mode%d_%s_%s_flsb0.root", fl_mode, tag, type) ) << std::endl;
  std::cout << "[sig] " << c_sig->GetEntries() << std::endl;
  std::cout << "[bkg] " << c_bkg->GetEntries() << std::endl;
  TCanvas* c = new TCanvas("c","c",1600,1200);
  c->Divide(3,2);

  Double_t* xmin = new Double_t[nvar];
  Double_t* xmax = new Double_t[nvar];
  for( Int_t j=0; j<nvar; j++ ){
    xmin[j] =  10000;
    xmax[j] = -10000;
  }
  for( Int_t i=0; i<c_sig->GetEntries(); i++ ){
    c_sig->GetEntry(i);
    for( Int_t j=0; j<nvar; j++ ){
      if( c_sig->GetLeaf( Form("var%d",j) )->GetValue() == -999 ){ std::cout << "continue(sig, " << j << ")" << std::endl;  continue;}
      if( c_sig->GetLeaf( Form("var%d",j) )->GetValue() < xmin[j] ) xmin[j] = c_sig->GetLeaf( Form("var%d",j) )->GetValue();
      if( c_sig->GetLeaf( Form("var%d",j) )->GetValue() > xmax[j] ) xmax[j] = c_sig->GetLeaf( Form("var%d",j) )->GetValue();
    }
  }

  for( Int_t i=0; i<c_bkg->GetEntries(); i++ ){
    c_bkg->GetEntry(i);
    for( Int_t j=0; j<nvar; j++ ){
      if( c_bkg->GetLeaf( Form("var%d",j) )->GetValue() == -999 ){ std::cout << "continue(bkg," << j << ")" << std::endl;  continue;}
      if( c_bkg->GetLeaf( Form("var%d",j) )->GetValue() < xmin[j] ) xmin[j] = c_bkg->GetLeaf( Form("var%d",j) )->GetValue();
      if( c_bkg->GetLeaf( Form("var%d",j) )->GetValue() > xmax[j] ) xmax[j] = c_bkg->GetLeaf( Form("var%d",j) )->GetValue();
    }
  }
  
  TH1D**    h_sig = new TH1D*   [nvar];
  TH1D**    h_bkg = new TH1D*   [nvar];
  THStack** hs    = new THStack*[nvar];
  for( Int_t j=0; j<nvar; j++ ){
    hs   [j] = new THStack( Form("h%d",j),    Form("h%d",j)                             );
    if( j==1 ){
      h_sig[j] = new TH1D   ( Form("h%d_sig",j),Form("h%d_sig",j),100,-1.8, 1.8 );
      h_bkg[j] = new TH1D   ( Form("h%d_bkg",j),Form("h%d_bkg",j),100,-1.8, 1.8 );
    }else{
      h_sig[j] = new TH1D   ( Form("h%d_sig",j),Form("h%d_sig",j),100,xmin[j],xmax[j]+1.0 );
      h_bkg[j] = new TH1D   ( Form("h%d_bkg",j),Form("h%d_bkg",j),100,xmin[j],xmax[j]+1.0 );
    }
    if( j==1 ){
      c_sig->Project( Form("h%d_sig",j), Form("atan(var%d)",j) );
      c_bkg->Project( Form("h%d_bkg",j), Form("atan(var%d)",j) );
    }else{
      c_sig->Project( Form("h%d_sig",j), Form("var%d",j) );
      c_bkg->Project( Form("h%d_bkg",j), Form("var%d",j) );
    }
    h_sig[j]->Sumw2(); h_sig[j]->Scale( 1/h_sig[j]->GetEntries() );
    h_bkg[j]->Sumw2(); h_bkg[j]->Scale( 1/h_bkg[j]->GetEntries() );
    
    c->cd(j+1);
    h_sig[j]->SetLineColor(1);
    h_bkg[j]->SetLineColor(2);
    hs[j]->Add( h_sig[j] );
    hs[j]->Add( h_bkg[j] );
    hs[j]->Draw("nostackhistE");
  }
  c->Print("pic/check.ps");

  return;
}
