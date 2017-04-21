#include "draws_.h"
#include "draws_fit_.h"
#include "draws_roofit_.h"

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//const Char_t* selection           = "nb_mode0_test13_nor>0.8 && eecl<1.2";
const Char_t* selection           = "eecl<1.2";
//const Char_t* selection           = "eecl<0.5";
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
const Bool_t  fl_use_dststmc   = true;
const Char_t*  infile_gmc      = "/home/belle/syutaro/dstrtaunu/modules/dstrtaunu/hbk/merge_noremcut/gMC_*s0[0-9]*.root";
const Double_t nstream_gmc     = 10;
const Char_t*  infile_dststmc  = "/home/belle/syutaro/dstrtaunu/modules/dstrtaunu/hbk/DssMC_weight_nb_noremcut/DssMC_*.root";
const Double_t nstream_dststmc = 2.7118;
const Char_t*  infile_dt       = "/home/belle/syutaro/dstrtaunu/modules/dstrtaunu/hbk/merge_noremcut/RD_*.root";

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
Int_t main( Int_t argc, Char_t** argv ){
  //gROOT->SetBatch(true); // tmpppppp
  TApplication app( "app", &argc, argv );
  TStyle* sty = Style(10);
  sty->SetTitleOffset(1.0,"z");
  //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  Read_Data( calib_file, true );
  std::stringstream sTmp;

  //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  // <TChain>
  sTmp.str("");
  sTmp.clear();
  sTmp << selection;
  sTmp << " && " << makeCut_dststmc( fl_use_dststmc ).c_str();
  std::cout << "[Cut] " << sTmp.str().c_str() << std::endl;
  
  TChain* c_gmc = new TChain(treename);
  std::cout << "[infile_gmc] " << infile_gmc << std::endl;
  std::cout << c_gmc->Add(infile_gmc)  << " files, ";
  std::cout << c_gmc->GetEntries()     << " entries, ";
  std::cout << nstream_gmc             << " streams";

  TTree* c_gmc_cut = c_gmc->CopyTree( sTmp.str().c_str() );
  std::cout << " -> " << c_gmc_cut->GetEntries() << " entries" << std::endl;

  TChain* c_dststmc = new TChain(treename);
  std::cout << "[infile_dststmc] " << infile_dststmc << std::endl;
  std::cout << c_dststmc->Add(infile_dststmc) << " files, ";
  std::cout << c_dststmc->GetEntries()        << " entries, ";
  std::cout << nstream_dststmc                << " streams";

  TTree* c_dststmc_cut = c_dststmc->CopyTree( sTmp.str().c_str() );
  std::cout << " -> " << c_dststmc_cut->GetEntries() << " entries" << std::endl;

  TChain* c_dt = new TChain(treename);
  std::cout << "[infile_dt] " << infile_dt << std::endl;
  std::cout << c_dt->Add(infile_dt)   << " files, ";
  std::cout << c_dt->GetEntries()     << " entries ";

  TTree* c_dt_cut = c_dt->CopyTree( selection );
  std::cout << " -> " << c_dt_cut->GetEntries() << " entries" << std::endl;

  //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  const Int_t nhist = 3; // 0(trk), 1(pi0), 2(ks)
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
  }
  
  //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  for( Int_t ievt=0; ievt<c_gmc_cut->GetEntries(); ievt++ ){
    Double_t weight = cal_weight( c_gmc_cut, ievt, (Double_t)nstream_gmc );
    c_gmc_cut->GetEntry(ievt);
    Int_t remtrk = (Int_t)c_gmc_cut->GetLeaf("remtrk"  )->GetValue();
    Int_t rempi0 = (Int_t)c_gmc_cut->GetLeaf("rempi0_1")->GetValue();
    Int_t remks  = (Int_t)c_gmc_cut->GetLeaf("remks"   )->GetValue();
    if(              rempi0==0 && remks==0 ) hist_mc[0]->Fill( remtrk, weight );
    if( remtrk==0              && remks==0 ) hist_mc[1]->Fill( rempi0, weight );
    if( remtrk==0 && rempi0==0             ) hist_mc[2]->Fill( remks,  weight );
  }

  for( Int_t ievt=0; ievt<c_dststmc_cut->GetEntries(); ievt++ ){
    Double_t weight = cal_weight( c_dststmc_cut, ievt, (Double_t)nstream_dststmc );
    c_dststmc_cut->GetEntry(ievt);
    Int_t remtrk = (Int_t)c_dststmc_cut->GetLeaf("remtrk"  )->GetValue();
    Int_t rempi0 = (Int_t)c_dststmc_cut->GetLeaf("rempi0_1")->GetValue();
    Int_t remks  = (Int_t)c_dststmc_cut->GetLeaf("remks"   )->GetValue();
    if(              rempi0==0 && remks==0 ) hist_mc[0]->Fill( remtrk, weight );
    if( remtrk==0              && remks==0 ) hist_mc[1]->Fill( rempi0, weight );
    if( remtrk==0 && rempi0==0             ) hist_mc[2]->Fill( remks,  weight );
  }

  for( Int_t ievt=0; ievt<c_dt_cut->GetEntries(); ievt++ ){
    c_dt_cut->GetEntry(ievt);
    Int_t remtrk = (Int_t)c_dt_cut->GetLeaf("remtrk"  )->GetValue();
    Int_t rempi0 = (Int_t)c_dt_cut->GetLeaf("rempi0_1")->GetValue();
    Int_t remks  = (Int_t)c_dt_cut->GetLeaf("remks"   )->GetValue();
    if(              rempi0==0 && remks==0 ) hist_dt[0]->Fill( remtrk );
    if( remtrk==0              && remks==0 ) hist_dt[1]->Fill( rempi0 );
    if( remtrk==0 && rempi0==0             ) hist_dt[2]->Fill( remks  );
  }
  //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  TCanvas* can = Canvas( "can","can", nhist, 1 );
  can->Draw();
  for( Int_t ihist=0; ihist<nhist; ihist++ ){
    can->cd(ihist+1);
    hist_mc[ihist]->Draw("hist");
    hist_dt[ihist]->Draw("histsame");
    hist_mc[ihist]->Print("all");
    hist_dt[ihist]->Print("all");
  }

  TLegend* leg = new TLegend( 0.55,0.45,0.80,0.65 );
  leg->AddEntry( hist_mc[0], "MC",   "PL" );
  leg->AddEntry( hist_dt[0], "Data", "PL" );
  leg->Draw();

  can->Update();
  can->Print("pic/cnt_multiplicity.eps");
  //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  std::cout << "finish" << std::endl;
  if( !gROOT->IsBatch() ) app.Run();

  return 0;

}
