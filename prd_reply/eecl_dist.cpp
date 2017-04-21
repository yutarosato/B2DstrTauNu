#include "draws_.h"

const Char_t* pdf_dir = "../nominal_fit/pdf/";
const Int_t   fl_lep  = 0;
const Int_t   npdf    = 10;
const Char_t* pdf_name[npdf] = { "other", "sig", "nor", "dstst", "doubled", "fake_other", "fake_sig", "fake_nor", "fake_dstst", "fake_doubled" };
const Double_t nstream_dststmc = 2.7118;
const Double_t nstream_npmc    = 40;
const Double_t nstream_gmc     = 10;

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
Int_t main( Int_t argc, Char_t** argv ){
  gROOT->SetBatch(!true); // tmpppppp
  TApplication app( "app", &argc, argv );
  TStyle* sty = Style(10);
  sty->SetTitleOffset(1.0,"z");
  sty->SetPadTickX(1);
  sty->SetPadTickY(1);
  sty->SetTickLength( 0.02, "XY" );

  //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  // <PDF>
  TFile** pdf_file      = new TFile*[npdf];
  TH2D**  pdf_hist_2d   = new TH2D* [npdf];
  TH1D**  pdf_hist_eecl = new TH1D* [npdf];

  for( Int_t ipdf=0; ipdf<npdf; ipdf++ ){
    pdf_file[ipdf] = new TFile( Form("%s/makepdf_%s_lep%d_0p0.root", pdf_dir, pdf_name[ipdf], fl_lep) );
    if( pdf_file[ipdf]->IsZombie() ) std::cerr << "[ABORT] can not find pdf-file for " << pdf_name[ipdf] << std::endl, abort();

    pdf_hist_2d  [ipdf] = (TH2D*)pdf_file[ipdf]->Get( Form("nb_eecl_%s_lep%d",    pdf_name[ipdf], fl_lep) );
    if( pdf_hist_2d  [ipdf]== NULL ) std::cerr << "[ABORT] can not find  2d  histogram for " << pdf_name[ipdf] << std::endl, abort();
    pdf_hist_eecl[ipdf] = pdf_hist_2d[ipdf]->ProjectionY("_py");
    
  }

  //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  TH1D* hist_sig = new TH1D(*pdf_hist_eecl[1]); // sig
  TH1D* hist_nor = new TH1D(*pdf_hist_eecl[2]); // nor
  TH1D* hist_bkg = new TH1D(*pdf_hist_eecl[0]); // other
  hist_bkg->Add( pdf_hist_eecl[3], nstream_dststmc/nstream_gmc ); // D**
  hist_bkg->Add( pdf_hist_eecl[4] ); // DD
  hist_bkg->Add( pdf_hist_eecl[5] ); // fake(other)
  //hist_bkg->Add( pdf_hist_eecl[6],  nstream_npmc/nstream_gmc ); // fake(sig)
  //hist_bkg->Add( pdf_hist_eecl[7] ); // fake(nor)
  hist_bkg->Add( pdf_hist_eecl[8],  nstream_dststmc/nstream_gmc ); // fake(D**)
  hist_bkg->Add( pdf_hist_eecl[9] ); // fake(DD)

  //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++  
  TCanvas* can = Canvas( "can","can", 1, 1, 510, 710 );
  can->Draw();
  hist_sig->SetMarkerColor(2); hist_sig->SetLineColor(2);
  hist_nor->SetMarkerColor(1); hist_nor->SetLineColor(1); hist_nor->SetMarkerStyle(24);
  hist_bkg->SetMarkerColor(3); hist_bkg->SetLineColor(3); hist_bkg->SetMarkerStyle(26);
  
  //hist_nor->Draw();
  //hist_sig->Draw("same");
  //hist_bkg->Draw("same");

  hist_nor->DrawNormalized();
  hist_sig->DrawNormalized("same");
  hist_bkg->DrawNormalized("same");
  hist_nor->DrawNormalized("same");
  //+++++++++++++++++++++++++++++++++++++++++++++++++
  can->Update();
  can->Print("pic/eecl_dist.eps");
  std::cout << "finish" << std::endl;
  if( !gROOT->IsBatch() ) app.Run();
  return 0;

}
