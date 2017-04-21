void hist(){

  TGraph* g_sig = new TGraph("tmp_nsig.dat");
  TGraph* g_nor = new TGraph("tmp_nnor.dat");
  std::cout << g_sig->GetN() << std::endl;
  std::cout << g_nor->GetN() << std::endl;
  TH1D* h_sig1 = new TH1D( "sig1", "sig1", 100,  100,  250 );
  TH1D* h_sig2 = new TH1D( "sig2", "sig2", 100,  100,  250 );
  TH1D* h_nor1 = new TH1D( "nor1", "nor1", 100, 2500, 3100 );
  TH1D* h_nor2 = new TH1D( "nor2", "nor2", 100, 2500, 3100 );
  TH1D* h_tot1 = new TH1D( "tot1", "tot1", 100, 2600, 3350 );
  TH1D* h_tot2 = new TH1D( "tot2", "tot2", 100, 2600, 3350 );

  for( Int_t i=0; i<g_sig->GetN(); i++ ){
    if( i<g_sig->GetN()/2 ) h_sig1->Fill( g_sig->GetY()[i] );
    else                    h_sig2->Fill( g_sig->GetY()[i] );
  }

  for( Int_t i=0; i<g_nor->GetN(); i++ ){
    if( i<g_nor->GetN()/2 ) h_nor1->Fill( g_nor->GetY()[i] );
    else                    h_nor2->Fill( g_nor->GetY()[i] );
  }

  if( g_sig->GetN() != g_nor->GetN() ) std::cerr << "wrong entry" << std::endl, abort();
  for( Int_t i=0; i<g_nor->GetN(); i++ ){
    if( i<g_nor->GetN()/2 ) h_tot1->Fill( g_sig->GetY()[i] + g_nor->GetY()[i] );
    else                    h_tot2->Fill( g_sig->GetY()[i] + g_nor->GetY()[i] );
  }

  TCanvas* can = new TCanvas( "can", "can", 1500, 1000 );
  can->Divide(3,2);
  can->cd(1); g_sig->Draw("AP");
  can->cd(2); g_nor->Draw("AP");
  can->cd(3);
  h_sig1->SetLineColor(2);
  h_sig2->SetLineColor(2);
  h_sig2->SetLineStyle(2);
  h_sig1->Draw();
  h_sig2->Draw("same");

  can->cd(4);
  h_nor1->SetLineColor(4);
  h_nor2->SetLineColor(4);
  h_nor2->SetLineStyle(2);
  h_nor1->Draw();
  h_nor2->Draw("same");

  can->cd(5);
  h_tot1->Draw();
  h_tot2->SetLineStyle(2);
  h_tot2->Draw("same");

  return;
}
