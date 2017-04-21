#include "draws_.h"

const char*    infile = "~/dstrtaunu/modules/dstrtaunu/hbk_single/through_cut/gMC_*.root";
const char*    tname  = "h17";
const Int_t    xbin = 120;
const Double_t xmin = -10;
const Double_t xmax =   5;
const Char_t*  brname = "cosdl1";
// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

TH1D* makeHistPdf( TChain* chain, const Int_t fl_dec, const Int_t fl_lep, const Int_t fl_col ){
  TH1D* hist = new TH1D( Form("%d_%d",fl_dec,fl_lep), Form("%d_%d",fl_dec,fl_lep), xbin, xmin, xmax );
  chain->Project( Form("%d_%d",fl_dec,fl_lep), brname, Form("rm_d1==%d&&rm_l1==%d",fl_dec,fl_lep) );
  hist->SetLineColor  (fl_col);
  hist->SetMarkerColor(fl_col);
  hist->Sumw2();
  return hist;
}

Int_t main( Int_t argc, Char_t** argv ){
  TApplication app( "app", &argc, argv );
  TStyle* sty = Style();
  sty->SetOptStat(0);
  sty->SetMarkerStyle(1);

  TChain* chain = new TChain(tname);
  std::cout << "[REC] "
	    << chain->Add( infile ) << " files, ";
  std::cout << chain->GetEntries()  << " entries"
	    << std::endl;

  // ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  TCanvas* can = Canvas( "can","can", 1, 1 );
  const Int_t nhist = 2;

  TH1D**   hist = new TH1D*[nhist];
  hist[0] = makeHistPdf( chain, 1210, 1, 1 );
  hist[1] = makeHistPdf( chain, 1200, 1, 2 );
  //hist[2] = makeHistPdf( chain, 1200, 1, 3 );
  //hist[3] = makeHistPdf( chain,  301, 1, 4 );
  //hist[1] = makeHistPdf( chain,    2, 1, 2 );
  //hist[2] = makeHistPdf( chain,  200, 1, 3 );
  //hist[3] = makeHistPdf( chain, 1010, 1, 4 );

  // 2 body (101, 2, 1010) : (200)
  // 3 body (1101) : (210) : (1200) : (12 same with Kpi)
  // 4 body (301 same with 1101?) : (1210 same with 1200)

  can->cd(1);
  for( Int_t ih=0; ih<nhist; ih++ ) hist[ih]->DrawNormalized( ih ? "same" : "" );
  can->Update();

  std::cout << "finish" << std::endl;
  if( !gROOT->IsBatch() ) app.Run();

  return 0;
}
