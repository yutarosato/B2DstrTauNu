void plot_strange_peak(){

  TChain* c = new TChain("h15");
  std::cout << c->Add( "hbk/hbk_mode0_test13_nor_setAA_HH_sig100_nor99/*.root" ) << std::endl;
  std::cout << c->GetEntries() << std::endl;

  const Int_t nhist = 3;
  TH1D** evis   = new TH1D*[nhist];
  TH1D** mmiss  = new TH1D*[nhist];
  TH1D** cosdll = new TH1D*[nhist];
  for( Int_t ihist=0; ihist<nhist; ihist++ ) evis  [ihist] = new TH1D( Form("evis%d",  ihist), Form("evis%d",  ihist), 100,    5,  12 );
  for( Int_t ihist=0; ihist<nhist; ihist++ ) mmiss [ihist] = new TH1D( Form("mmiss%d", ihist), Form("mmiss%d", ihist), 100,   -5,  30 );
  for( Int_t ihist=0; ihist<nhist; ihist++ ) cosdll[ihist] = new TH1D( Form("cosdll%d",ihist), Form("cosdll%d",ihist), 100, -1.6, 1.6 );
  //for( Int_t ihist=0; ihist<nhist; ihist++ ) cosdll[ihist] = new TH1D( Form("cosdll%d",ihist), Form("cosdll%d",ihist), 200, -50, 5 );

  c->Project( Form("evis%d",   0), "evis2",                            "self==1"                           );
  c->Project( Form("evis%d",   1), "evis2",                            "self==1&&nb_mode0_test13_nor<-0.2" );
  c->Project( Form("evis%d",   2), "evis2",                            "self==2"                           );
  c->Project( Form("mmiss%d",  0), "mmiss2*mmiss2*mmiss2/abs(mmiss2)", "self==1"                           );
  c->Project( Form("mmiss%d",  1), "mmiss2*mmiss2*mmiss2/abs(mmiss2)", "self==1&&nb_mode0_test13_nor<-0.2" );
  c->Project( Form("mmiss%d",  2), "mmiss2*mmiss2*mmiss2/abs(mmiss2)", "self==2"                           );
  c->Project( Form("cosdll%d", 0), "atan(cosdll)",                     "self==1"                           );
  c->Project( Form("cosdll%d", 1), "atan(cosdll)",                     "self==1&&nb_mode0_test13_nor<-0.2" );
  c->Project( Form("cosdll%d", 2), "atan(cosdll)",                     "self==2"                           );
  //c->Project( Form("cosdll%d", 0), "cosdll",                     "self==1"                           );
  //c->Project( Form("cosdll%d", 1), "cosdll",                     "self==1&&nb_mode0_test13_nor<-0.2" );
  //c->Project( Form("cosdll%d", 2), "cosdll",                     "self==2"                           );
  
  for( Int_t ihist=0; ihist<nhist; ihist++ ){
    evis  [ihist]->SetLineColor(1.6*ihist+1);
    mmiss [ihist]->SetLineColor(1.6*ihist+1);
    cosdll[ihist]->SetLineColor(1.6*ihist+1);
    evis  [ihist]->Sumw2();
    mmiss [ihist]->Sumw2();
    cosdll[ihist]->Sumw2();
    evis  [ihist]->Scale( 1.0/evis  [ihist]->GetEntries() );
    mmiss [ihist]->Scale( 1.0/mmiss [ihist]->GetEntries() );
    cosdll[ihist]->Scale( 1.0/cosdll[ihist]->GetEntries() );
  }
  const Int_t nvar = 3;
  THStack** mh = new THStack*[nvar];
  for( Int_t ivar=0; ivar<nvar; ivar++ ) mh[ivar] = new THStack( Form("mh%d",ivar), Form("mh%d",ivar) );

  for( Int_t ihist=0; ihist<nhist; ihist++ ) mh[0]->Add( evis  [ihist] );
  for( Int_t ihist=0; ihist<nhist; ihist++ ) mh[1]->Add( mmiss [ihist] );
  for( Int_t ihist=0; ihist<nhist; ihist++ ) mh[2]->Add( cosdll[ihist] );


  
  TCanvas* can = new TCanvas( "can", "can", 600, 1000 );
  can->Divide(1,3);
  can->Draw();
  can->cd(1); mh[0]->Draw("nostackhistE");
  can->cd(2); mh[1]->Draw("nostackhistE");
  can->cd(3); mh[2]->Draw("nostackhistE");
  


}
