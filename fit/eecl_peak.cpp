#include "draws_.h"

const Char_t*  treename   = "h15";
const Char_t*  infilename = "/home/belle/syutaro/dstrtaunu/modules/dstrtaunu/hbk/merge_cut_bcs_vtx/gMC_*s0[0-9]*.root";
const Double_t nstream    = 10;

const Int_t    nlep = 3;
const Int_t    xbin = 24;
const Double_t xmin = 0.0;
const Double_t xmax = 1.2;
const Char_t*  brname1 = "eecl";
const Char_t*  brname2 = "eeclth1";

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
TH1D* makehist( TChain* chain, const Char_t* name, const Int_t fl_nb, const Int_t fl_self, const Int_t fl_l, const Char_t* fl_brname, const Int_t col, const Int_t fl_scale=1 ){
  TH1D* hist = new TH1D( name, "", xbin, xmin, xmax );
  std::stringstream sTmp;
  if     ( fl_nb== 0 ) sTmp << "1";
  else if( fl_nb > 0 ) sTmp << "nb_mode0_test13_nor > 0.8";
  else                 sTmp << "nb_mode0_test13_nor < 0.8";
  sTmp << " && self==" << fl_self;
  if( fl_l==1 || fl_l==10 ) sTmp << Form( "&& ( (cosdll==cosdl1 && rm_l1==%d) || (cosdll==cosdl2  && rm_l2==%d) )", fl_l, fl_l );
  chain->Project( name, fl_brname, sTmp.str().c_str() );
  hist->SetXTitle( "E_{ECL} [GeV]" );
  hist->SetLineColor  (col);
  hist->SetMarkerColor(col);
  hist->SetMarkerStyle(20);
  hist->SetMarkerSize(0.8);
  hist->SetMinimum(0.0);
  hist->Sumw2();
  if     ( fl_scale==1 ) hist->Scale( 1.0/hist->Integral() );
  else if( fl_scale==2 ) hist->Scale( 1.0/nstream          );
     
  return hist;
}

Int_t main( Int_t argc, Char_t** argv ){

  TApplication app( "app", &argc, argv );
  TStyle* sty = Style();
  sty->SetOptStat(0);
  //gROOT->SetBatch(true); // tmpppppp

  //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  // <TChain>
  TChain* chain = new TChain( treename );  
  std::cout << chain->Add( infilename  ) << " files"   << std::endl;
  std::cout << chain->GetEntries()       << " entries" << std::endl;
  //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  /*
  // sig  : nor
  // eecl : eeclth1
  // tot, neg, pos (NB)
  // e : mu
  //                                                                nb  self lep   eecl   col, scale
  TH1D* hist_sig_tot_eecl2 = makehist( chain, "hist_sig_tot_eecl1",  0,  1,   -1, brname2, 2, 1 );
  TH1D* hist_nor_pos_eecl2 = makehist( chain, "hist_nor_pos_eecl1",  1,  2,   -1, brname2, 4, 1 );
  TH1D* hist_nor_neg_eecl2 = makehist( chain, "hist_nor_neg_eecl1", -1,  2,   -1, brname2, 3, 1 );

  TH1D* hist_sig_e_tot_eecl2 = makehist( chain, "hist_sig_e_tot_eecl1",  0,  1,   10, brname2, 2, 1 );
  TH1D* hist_nor_e_pos_eecl2 = makehist( chain, "hist_nor_e_pos_eecl1",  1,  2,   10, brname2, 4, 1 );
  TH1D* hist_nor_e_neg_eecl2 = makehist( chain, "hist_nor_e_neg_eecl1", -1,  2,   10, brname2, 3, 1 );

  TH1D* hist_sig_m_tot_eecl2 = makehist( chain, "hist_sig_m_tot_eecl1",  0,  1,    1, brname2, 2, 1 );
  TH1D* hist_nor_m_pos_eecl2 = makehist( chain, "hist_nor_m_pos_eecl1",  1,  2,    1, brname2, 4, 1 );
  TH1D* hist_nor_m_neg_eecl2 = makehist( chain, "hist_nor_m_neg_eecl1", -1,  2,    1, brname2, 3, 1 );

  //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

  // <CANVAS>
  TCanvas* can = Canvas( "can","can", 3, 1 );
  can->Draw();
  can->cd(1);
  hist_sig_tot_eecl2->SetMaximum(0.30);
  hist_sig_tot_eecl2->DrawClone("PE    ");
  hist_nor_pos_eecl2->DrawClone("PEsame");
  hist_nor_neg_eecl2->DrawClone("PEsame");

  can->cd(2);
  hist_sig_e_tot_eecl2->SetMaximum(0.30);
  hist_sig_e_tot_eecl2->DrawClone("PE    ");
  hist_nor_e_pos_eecl2->DrawClone("PEsame");
  hist_nor_e_neg_eecl2->DrawClone("PEsame");

  can->cd(3);
  hist_sig_m_tot_eecl2->SetMaximum(0.30);
  hist_sig_m_tot_eecl2->DrawClone("PE    ");
  hist_nor_m_pos_eecl2->DrawClone("PEsame");
  hist_nor_m_neg_eecl2->DrawClone("PEsame");
  */
  //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  ///*
  //                                                                    nb  self lep   eecl   col, scale
  TH1D* hist_nor_pos_eecl1   = makehist( chain, "hist_nor_pos_eecl1",    1,  2,   -1, brname1, 2, 2 );
  TH1D* hist_nor_e_pos_eecl1 = makehist( chain, "hist_nor_e_pos_eecl1",  1,  2,   10, brname1, 2, 2 );
  TH1D* hist_nor_m_pos_eecl1 = makehist( chain, "hist_nor_m_pos_eecl1",  1,  2,    1, brname1, 2, 2 );
  TH1D* hist_nor_pos_eecl2   = makehist( chain, "hist_nor_pos_eecl2",    1,  2,   -1, brname2, 3, 2 );
  TH1D* hist_nor_e_pos_eecl2 = makehist( chain, "hist_nor_e_pos_eecl2",  1,  2,   10, brname2, 3, 2 );
  TH1D* hist_nor_m_pos_eecl2 = makehist( chain, "hist_nor_m_pos_eecl2",  1,  2,    1, brname2, 3, 2 );


  TH1D* hist_nor_neg_eecl1   = makehist( chain, "hist_nor_neg_eecl1",   -1,  2,   -1, brname1, 2, 2 );
  TH1D* hist_nor_e_neg_eecl1 = makehist( chain, "hist_nor_e_neg_eecl1", -1,  2,   10, brname1, 2, 2 );
  TH1D* hist_nor_m_neg_eecl1 = makehist( chain, "hist_nor_m_neg_eecl1", -1,  2,    1, brname1, 2, 2 );
  TH1D* hist_nor_neg_eecl2   = makehist( chain, "hist_nor_neg_eecl2",   -1,  2,   -1, brname2, 3, 2 );
  TH1D* hist_nor_e_neg_eecl2 = makehist( chain, "hist_nor_e_neg_eecl2", -1,  2,   10, brname2, 3, 2 );
  TH1D* hist_nor_m_neg_eecl2 = makehist( chain, "hist_nor_m_neg_eecl2", -1,  2,    1, brname2, 3, 2 );


  //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  // <CANVAS>
  TCanvas* can = Canvas( "can","can", 3, 2 );
  can->Draw();
  can->cd(1);
  hist_nor_pos_eecl2->SetLineWidth(2);
  hist_nor_pos_eecl2->Draw("PE");
  hist_nor_pos_eecl1->Draw("PEsame");

  can->cd(2);
  hist_nor_e_pos_eecl2->SetLineWidth(2);
  hist_nor_e_pos_eecl2->Draw("PE");
  hist_nor_e_pos_eecl1->Draw("PEsame");

  can->cd(3);
  hist_nor_m_pos_eecl2->SetLineWidth(2);
  hist_nor_m_pos_eecl2->Draw("PE");
  hist_nor_m_pos_eecl1->Draw("PEsame");

  can->cd(4);
  hist_nor_neg_eecl2->SetLineWidth(2);
  hist_nor_neg_eecl2->Draw("PE");
  hist_nor_neg_eecl1->Draw("PEsame");

  can->cd(5);
  hist_nor_e_neg_eecl2->SetLineWidth(2);
  hist_nor_e_neg_eecl2->Draw("PE");
  hist_nor_e_neg_eecl1->Draw("PEsame");

  can->cd(6);
  hist_nor_m_neg_eecl2->SetLineWidth(2);
  hist_nor_m_neg_eecl2->Draw("PE");
  hist_nor_m_neg_eecl1->Draw("PEsame");
  //*/
  //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

  can->Update();
  can->Print( Form("pic/eecl_peak.eps") );
  std::cout << "finish" << std::endl;
  if( !gROOT->IsBatch() ) app.Run();

  return 0;

}
