#include "draws_.h"
#include "draws_had_.h"

Int_t main( Int_t argc, Char_t** argv ){
  TApplication app( "app", &argc, argv );
  TStyle* sty = Style(0);
  sty->SetOptStat(0);
  sty->SetMarkerSize(0.4);
  //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  // <Read Data>
  const Char_t*  treename    = "h18";
  const Char_t*  infile_dt   = "~/dstrtaunu/modules/dstrtaunu/hbk_hadtag/merge_noremcut/RD_*.root";
  const Char_t*  infile_gmc  = "~/dstrtaunu/modules/dstrtaunu/hbk_hadtag/merge_noremcut/gMC_*.root";
  const Double_t nstream_gmc = 6;
  const Char_t*  selection   = "1";

  //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  // <TChain>
  std::stringstream sTmp;
  sTmp << selection;
  std::cout << "[Cut] " << sTmp.str().c_str() << std::endl;
  
  TChain* c_gmc = new TChain(treename);
  std::cout << "[infile_gmc] " << infile_gmc << std::endl;
  std::cout << c_gmc->Add(infile_gmc)  << " files, ";
  std::cout << c_gmc->GetEntries()     << " entries, ";
  std::cout << nstream_gmc             << " streams";

  TTree* c_gmc_cut = c_gmc->CopyTree( sTmp.str().c_str() );
  std::cout << " -> " << c_gmc_cut->GetEntries() << " entries" << std::endl;

  TChain* c_dt = new TChain(treename);
  std::cout << "[infile_dt] " << infile_dt << std::endl;
  std::cout << c_dt->Add(infile_dt)   << " files, ";
  std::cout << c_dt->GetEntries()     << " entries ";

  TTree* c_dt_cut = c_dt->CopyTree( selection );
  std::cout << " -> " << c_dt_cut->GetEntries() << " entries" << std::endl;
  //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  const Int_t nhist = 3;
  const Char_t* histname[nhist] = {    "trk",     "pi0",    "ks" };
  const Char_t* axisname[nhist] = {  "Track", "#pi^{0}", "K_{S}" };
  TH1D** hist_mc = new TH1D*[nhist];
  TH1D** hist_dt = new TH1D*[nhist];
  for( Int_t ihist=0; ihist<nhist; ihist++ ){
    hist_mc[ihist] = new TH1D( Form("%s_mc",histname[ihist]), Form("%s (mc)",histname[ihist]), 10, 0, (Double_t)10 );
    hist_dt[ihist] = new TH1D( Form("%s_dt",histname[ihist]), Form("%s (dt)",histname[ihist]), 10, 0, (Double_t)10 );
    hist_mc[ihist]->SetXTitle( axisname[ihist] );
    hist_dt[ihist]->SetXTitle( axisname[ihist] );
    hist_mc[ihist]->SetLineColor  (3);
    hist_mc[ihist]->SetMarkerColor(3);
    hist_dt[ihist]->SetLineColor  (2);
    hist_dt[ihist]->SetMarkerColor(2);
    hist_mc[ihist]->Sumw2();
    hist_dt[ihist]->Sumw2();
  }
  //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  for( Int_t ievt=0; ievt<c_gmc_cut->GetEntries(); ievt++ ){
    c_gmc_cut->GetEntry(ievt);
    Double_t weight = 1.0;
    Int_t    hush   = (Int_t)c_gmc_cut->GetLeaf("tbdecay"  )->GetValue();
    Double_t nb     =        c_gmc_cut->GetLeaf("tnboutde" )->GetValue();
    weight = tagcorr( hush, nb );
    weight /= nstream_gmc;

    Double_t q2     =        c_gmc_cut->GetLeaf("q2rec"    )->GetValue();
    Double_t mbc    =        c_gmc_cut->GetLeaf("tmbc"     )->GetValue();
    Double_t eecl   =        c_gmc_cut->GetLeaf("eecl"     )->GetValue();
    Double_t dm     =        c_gmc_cut->GetLeaf("dm1"      )->GetValue();
    Int_t    d_lund = (Int_t)c_gmc_cut->GetLeaf("rm_d1lun" )->GetValue(); // 411(D+), 421(D0)
    Int_t    remtrk = (Int_t)c_gmc_cut->GetLeaf("remtrk"   )->GetValue();
    Int_t    rempi0 = (Int_t)c_gmc_cut->GetLeaf("rempi0"   )->GetValue();
    Int_t    remks  = (Int_t)c_gmc_cut->GetLeaf("remks"    )->GetValue();

    if( abs(d_lund)==421 && 0.0025 > fabs(dm - (PDGmass::d0 + PDGmass::pip)) ) continue;
    if( abs(d_lund)==411 && 0.0020 > fabs(dm - (PDGmass::dp + PDGmass::pi0)) ) continue;
    if( q2   > 3.0  ) continue;
    if( mbc  < 5.27 ) continue;
    if( eecl > 1.2  ) continue;
    if(              rempi0==0 && remks==0 ) hist_mc[0]->Fill( remtrk, weight );
    if( remtrk==0              && remks==0 ) hist_mc[1]->Fill( rempi0, weight );
    if( remtrk==0 && rempi0==0             ) hist_mc[2]->Fill( remks,  weight );
  }

  for( Int_t ievt=0; ievt<c_dt_cut->GetEntries(); ievt++ ){
    c_dt_cut->GetEntry(ievt);
    
    Double_t q2     =        c_dt_cut->GetLeaf("q2rec"    )->GetValue();
    Double_t mbc    =        c_dt_cut->GetLeaf("tmbc"     )->GetValue();
    Double_t eecl   =        c_dt_cut->GetLeaf("eecl"     )->GetValue();
    Double_t dm     =        c_dt_cut->GetLeaf("dm1"      )->GetValue();
    Int_t    d_lund = (Int_t)c_dt_cut->GetLeaf("rm_d1lun" )->GetValue(); // 411(D+), 421(D0)
    Int_t    remtrk = (Int_t)c_dt_cut->GetLeaf("remtrk"   )->GetValue();
    Int_t    rempi0 = (Int_t)c_dt_cut->GetLeaf("rempi0"   )->GetValue();
    Int_t    remks  = (Int_t)c_dt_cut->GetLeaf("remks"    )->GetValue();
    
    if( abs(d_lund)==421 && 0.0025 > fabs(dm - (PDGmass::d0 + PDGmass::pip)) ) continue;
    if( abs(d_lund)==411 && 0.0020 > fabs(dm - (PDGmass::dp + PDGmass::pi0)) ) continue;
    if( q2   > 3.0  ) continue;
    if( mbc  < 5.27 ) continue;
    if( eecl > 1.2  ) continue;
    if(              rempi0==0 && remks==0 ) hist_dt[0]->Fill( remtrk );
    if( remtrk==0              && remks==0 ) hist_dt[1]->Fill( rempi0 );
    if( remtrk==0 && rempi0==0             ) hist_dt[2]->Fill( remks  );
  }
  //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  for( Int_t ihist=0; ihist<nhist; ihist++ ){
    hist_mc[ihist]->Print();
    hist_dt[ihist]->Print();

    //hist_mc[ihist]->Scale( hist_dt[ihist]->Integral()/hist_mc[ihist]->Integral() );

    hist_mc[ihist]->Scale( 1.0/hist_mc[ihist]->Integral() );
    hist_dt[ihist]->Scale( 1.0/hist_dt[ihist]->Integral() );
  }
  //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  TCanvas* can = Canvas( "can","can", nhist, 1 );
  can->Draw();
  for( Int_t ihist=0; ihist<nhist; ihist++ ){
    can->cd(ihist+1);
    hist_dt[ihist]->Draw("histE");
    hist_mc[ihist]->Draw("histEsame");
  }
  hist_mc[1]->Print("all");
  hist_dt[1]->Print("all");

  TLegend* leg = new TLegend( 0.55,0.55,0.80,0.75 );
  leg->AddEntry( hist_dt[0], "Data", "PL" );
  leg->AddEntry( hist_mc[0], "MC",   "PL" );
  leg->Draw();

  can->Update();
  can->Print("pic/cnt_multiplicity_hadtag.eps");

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  std::cout << "finish" << std::endl;
  app.Run();
  return 0;
}
