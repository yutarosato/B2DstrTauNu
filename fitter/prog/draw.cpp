const Double_t scale = sqrt(10.0);
const Double_t smval = 0.252;

void Adjust( TGraphErrors* g ){
  const Double_t offset = smval - g->GetY()[0];
  for( Int_t ip=0; ip<g->GetN(); ip++ ) g->SetPoint( ip, g->GetX()[ip], g->GetY()[ip]+offset );
  return;
}

TGraph* makeBand( TGraphErrors* g ){
  TGraph* band = new TGraph();
  band->SetFillColor(5);
  
  for( Int_t ip=0;           ip<g->GetN(); ip++ ) band->SetPoint( band->GetN(), g->GetX()[ip], g->GetY()[ip] + scale*g->GetEY()[ip] );
  for( Int_t ip=g->GetN()-1; ip>=0;        ip-- ) band->SetPoint( band->GetN(), g->GetX()[ip], g->GetY()[ip] - scale*g->GetEY()[ip] );
  for( Int_t ip=0;           ip<g->GetN(); ip++ ) g->SetPointError( ip, 0.0, 0.0 );

  return band;
}


void draw(){
  gStyle->SetOptStat(0);
  gStyle->SetTitleOffset(1.2,"x");
  gStyle->SetTitleOffset(1.7,"y");
  gStyle->SetPadLeftMargin(0.12);
  TGraphErrors* g = new TGraphErrors("tmp_sm_np.dat","%lg %lg %lg");
  //TGraphErrors* g = new TGraphErrors("tmp_np_np.dat","%lg %lg %lg");
  Adjust(g);
  g->SetMarkerStyle(20);
  g->SetMarkerSize(0.6);
  g->SetLineColor(2);
  g->SetMarkerColor(2);
  //g->Print();

  TGraph* g_band = makeBand( g );
  //g_band->Print();


  TLine* smline = new TLine( 0.0, 0.252, 1.0, 0.252 );
  smline->SetLineColor(4);
  smline->SetLineStyle(2);
  //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  const Int_t   npoint       = 11;
  Double_t      x   [npoint] = {    0.0,     0.1,    0.2,     0.3,    0.4,     0.5,     0.6,    0.7,     0.8,     0.9,    1.0 };
  Double_t      nsig[npoint] = { 190.19, 191.578, 191.03, 190.815, 190.53, 189.296, 186.536, 183.72, 180.403, 178.872, 176.94 };
  TGraphErrors* eff          = new TGraphErrors();
  eff->SetMarkerStyle(20);
  eff->SetMarkerSize(0.6);
  eff->SetLineColor(2);
  eff->SetMarkerColor(2);
  for( Int_t ip=0; ip<npoint; ip++ ){
    eff->SetPoint( eff->GetN(), x[ip], nsig[ip]/nsig[0] );
  }


  //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  TCanvas* can = new TCanvas("can","can", 1200, 600 );

  can->Divide(2,1);
  can->Draw();

  can->cd(1);
  can->cd(1)->SetGridy(1);
  TH2D* waku1 = new TH2D("eff","efficiency ratio of type-II 2HDM to SM;tan#beta/m_{H+} [GeV^{-1}];#varepsilon^{type-II 2HDM}/#varepsilon^{SM}", 2, 0.0, 1.0, 2, 0.80, 1.20 );
  waku1->Draw();  
  eff->Draw("PCsame");
  
  can->cd(2);
  TH2D* waku2 = new TH2D("rdstr","Expected R(D*) as a function of tan#beta/m_{H+};tan#beta/m_{H+} [GeV^{-1}];R(D*)", 2, 0.0, 1.0, 2, 0.17, 0.33 );
  waku2->Draw();  
  g_band->Draw("Fsame");
  smline->Draw("Lsame");
  g     ->Draw("PCsame");

  /*
  TGraphErrors* gnp = new TGraphErrors("tmp_np_np.dat","%lg %lg %lg");
  gnp->SetMinimum(0.20);
  gnp->SetMaximum(0.30);
  gnp->Draw("APEL");
  gnp->Print();
  */
  return;
}
