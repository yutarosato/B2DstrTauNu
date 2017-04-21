//const Char_t* selection = "atan(cosdll)<-0.8";
const Char_t* selection = "nb_mode0_test13_nor>0.8";
const Int_t xbin = 24;
const Double_t xmin = 0.0;
const Double_t xmax = 1.2;

void plot_eecl(){

  TChain* c_gmc  = new TChain("h15"); std::cout << c_gmc ->Add("hbk/hbk_mode0_test13_nor_setAA_HH/gMC_*.root")     << " files, "; std::cout << c_gmc ->GetEntries() << " entries" << std::endl;
  TChain* c_stst = new TChain("h15"); std::cout << c_stst->Add("hbk_dstst/hbk_mode0_test13_nor_setAA_HH/*.root")   << " files, "; std::cout << c_stst->GetEntries() << " entries" << std::endl;
  TChain* c_pipi = new TChain("h15"); std::cout << c_pipi->Add("hbk_dstpipi/hbk_mode0_test13_nor_setAA_HH/*.root") << " files, "; std::cout << c_pipi->GetEntries() << " entries" << std::endl;

  // for estimation of scale factor between gMC and D** MC --> scale(D**MC,1set/gMC,1stream) ~ 12.5
  std::cout << "[gmc, D**] " << c_gmc ->GetEntries( Form("self==-5 && %s",                                                selection) ) << std::endl;
  std::cout << "[gmc, D1'] " << c_gmc ->GetEntries( Form("self==-5 && %s && (abs(rootdf1)==20413 || abs(rootdf2)==20413)",selection) ) << std::endl;
  std::cout << "[gmc, D1 ] " << c_gmc ->GetEntries( Form("self==-5 && %s && (abs(rootdf1)==10413 || abs(rootdf2)==10413)",selection) ) << std::endl;
  std::cout << "[gmc, D0*] " << c_gmc ->GetEntries( Form("self==-5 && %s && (abs(rootdf1)==10411 || abs(rootdf2)==10411)",selection) ) << std::endl;
  std::cout << "[gmc, D2*] " << c_gmc ->GetEntries( Form("self==-5 && %s && (abs(rootdf1)==  415 || abs(rootdf2)==  415)",selection) ) << std::endl;
  std::cout << "[D**, D1'] " << c_stst->GetEntries( Form("self==-5 && %s && (abs(rootdf1)==20413 || abs(rootdf2)==20413)",selection) ) << std::endl;
  std::cout << "[D**, D1 ] " << c_stst->GetEntries( Form("self==-5 && %s && (abs(rootdf1)==10413 || abs(rootdf2)==10413)",selection) ) << std::endl;
  std::cout << "[D**, D0*] " << c_stst->GetEntries( Form("self==-5 && %s && (abs(rootdf1)==10411 || abs(rootdf2)==10411)",selection) ) << std::endl;
  std::cout << "[D**, D2*] " << c_stst->GetEntries( Form("self==-5 && %s && (abs(rootdf1)==  415 || abs(rootdf2)==  415)",selection) ) << std::endl;

  // Br(B->D** lnu) in Belle MC : 2.68 %, where D** is 4 states with L=1
  // missing Br(b->c lnu) : 1.694% + 0.224%(multibody D1 decay) = 1.918%
  // D*+ pi+ pi- : 3
  // D*+ pi0 pi0 : 2
  // D*0 pi+ pi0 : 2
  // assuming isospin invariance
  
  TCanvas* can = new TCanvas( "can", "can", 600, 1000 );
  can->Divide(1,3);
  can->Draw();
  
  // ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  const Int_t nhist1 = 4;
  TH1D** eecl1 = new TH1D*[nhist1];
  for( Int_t ihist=0; ihist<nhist1; ihist++ ) eecl1[ihist] = new TH1D( Form("eecl1_%d",ihist), Form("eecl1_%d",ihist), xbin, xmin, xmax );
  c_gmc ->Project( "eecl1_0", "eecl", Form("%s && self==-5",selection) );
  c_stst->Project( "eecl1_1", "eecl", Form("%s",            selection) );
  c_pipi->Project( "eecl1_2", "eecl", Form("%s",            selection) );
  c_gmc ->Project( "eecl1_3", "eecl", Form("%s && self==1", selection) );
  for( Int_t ihist=0; ihist<nhist1; ihist++ ){
    eecl1[ihist]->SetLineColor(1+1.6*ihist);
    eecl1[ihist]->Sumw2();
    eecl1[ihist]->SetXTitle("E_{ECL} [GeV]");
    std::cout << eecl1[ihist]->GetEntries() << " events" << std::endl;
  }

  can->cd(1);
  for( Int_t ihist=0; ihist<nhist1; ihist++ ){
    if     ( ihist==0 ) eecl1[ihist]->Scale(1/6.0);
    else if( ihist==1 ) eecl1[ihist]->Scale(1/12.5/2.0);
    else if( ihist==2 ) eecl1[ihist]->Scale(1/12.5/2.0/(2.68/1.694));
    else if( ihist==3 ) eecl1[ihist]->Scale(1/6.0);
    eecl1[ihist]->SetMaximum(40);
    eecl1[ihist]->Draw( ihist==0 ? "histE" : "Esame" );
    //eecl1[ihist]->DrawNormalized( ihist==0 ? "histE" : "Esame" );
  }

  // ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  const Int_t nhist2 = 3;
  TH1D** eecl2 = new TH1D*[nhist2];
  for( Int_t ihist=0; ihist<nhist2; ihist++ ) eecl2[ihist] = new TH1D( Form("eecl2_%d",ihist), Form("eecl2_%d",ihist), xbin, xmin, xmax );
  c_pipi->Project( "eecl2_0", "eecl", Form("%s && ( (nb1pip==0 && nb1pi0==2) || (nb2pip==0 && nb2pi0==2) )",selection) );
  c_pipi->Project( "eecl2_1", "eecl", Form("%s && ( (nb1pip==1 && nb1pi0==1) || (nb2pip==1 && nb2pi0==1) )",selection) );
  c_pipi->Project( "eecl2_2", "eecl", Form("%s && ( (nb1pip==2 && nb1pi0==0) || (nb2pip==2 && nb2pi0==0) )",selection) );
  for( Int_t ihist=0; ihist<nhist2; ihist++ ){
    eecl2[ihist]->Sumw2();
    eecl2[ihist]->Scale(1/12.5/2.0/(2.68/1.694));
    eecl2[ihist]->SetLineColor(1+1.6*ihist);
    eecl2[ihist]->SetXTitle("E_{ECL} [GeV]");
  }
  can->cd(2);
  for( Int_t ihist=0; ihist<nhist2; ihist++ ) eecl2[ihist]->Draw( ihist==0 ? "histE" : "Esame" );

  can->cd(3);
  c_pipi->Draw("neecl_12>>neecl(20,0,10)", Form("%s && ( (nb1pip==0 && nb1pi0==2) || (nb2pip==0 && nb2pi0==2) )",selection), "texthist" );
  neecl->SetMarkerSize(3.0);
  neecl->SetMarkerColor(2);
  neecl->Draw("TEXThist");

  return;
}
