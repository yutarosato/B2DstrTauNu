#include "cal_signif_sigregion_pi0mass.h"

const Bool_t   fl_message   = true;
//const Bool_t   fl_save      = true; // outfile.eps and outfile.root
const Char_t*  tname        = "h15";
//const Char_t*  infile       = "~/dstrtaunu/ana/NB/hbk/hbk_mode0_test13_nor/gMC_*s0[012345]*.root";
//const Char_t*  infile       = "~/dstrtaunu/ana/NB/hbk/hbk_bcs_mode0_test13_nor/gMC_*s0[012345]*.root";
//const Char_t*  infile       = "~/dstrtaunu/ana/NB/hbk/hbk_bcs_rnd_mode0_test13_nor/gMC_*s0[012345]*.root";
const Char_t*  infile       = "~/dstrtaunu/ana/NB/hbk/hbk_bcs_vtx_mode0_test13_nor/gMC_*s0[012345]*.root";
const Double_t scale_factor = 6; // N -> N/scale
const Char_t* sigregion_cut = "(nb_mode0_test13_nor > 0.8 && eecl<0.5)";
//const Char_t* sigregion_cut = "(nb_mode0_test13_nor > 0.8 && eecl<0.3)";

// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
Int_t main( Int_t argc, Char_t** argv ){
  TApplication app( "app", &argc, argv );
  Style(10);
  //gROOT->SetBatch(true); // tmpppppp
  
  TChain* chain = new TChain( tname );
  Int_t nfile = chain->Add( infile );
  Int_t nevt  = chain->GetEntries();

  std::cout << "[infile] "
	    << nfile << " files, "
	    << nevt  << " events, "
	    << infile << std::endl;
  std::cout << "[scale factor] " << scale_factor << std::endl;
  // ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

  TGraphErrors* g1 = new TGraphErrors();
  g1->SetPoint( g1->GetN(), 0.010, cal_signif(chain, 0.010, 0.010, 0.010, 0.010) ); g1->SetPointError( g1->GetN()-1, 0.0, cal_signifE(chain, 0.010, 0.010, 0.010, 0.010) );
  g1->SetPoint( g1->GetN(), 0.015, cal_signif(chain, 0.015, 0.010, 0.010, 0.010) ); g1->SetPointError( g1->GetN()-1, 0.0, cal_signifE(chain, 0.015, 0.010, 0.010, 0.010) );
  g1->SetPoint( g1->GetN(), 0.020, cal_signif(chain, 0.020, 0.010, 0.010, 0.010) ); g1->SetPointError( g1->GetN()-1, 0.0, cal_signifE(chain, 0.020, 0.010, 0.010, 0.010) );
  g1->SetPoint( g1->GetN(), 0.025, cal_signif(chain, 0.025, 0.010, 0.010, 0.010) ); g1->SetPointError( g1->GetN()-1, 0.0, cal_signifE(chain, 0.025, 0.010, 0.010, 0.010) );
  g1->SetPoint( g1->GetN(), 0.030, cal_signif(chain, 0.030, 0.010, 0.010, 0.010) ); g1->SetPointError( g1->GetN()-1, 0.0, cal_signifE(chain, 0.030, 0.010, 0.010, 0.010) );
  g1->SetTitle( "low edge of pi0 from D" );

  TGraphErrors* g2 = new TGraphErrors();
  g2->SetPoint( g2->GetN(), 0.010, cal_signif(chain, 0.010, 0.010, 0.010, 0.010) ); g2->SetPointError( g2->GetN()-1, 0.0, cal_signifE(chain, 0.010, 0.010, 0.010, 0.010) );
  g2->SetPoint( g2->GetN(), 0.015, cal_signif(chain, 0.010, 0.015, 0.010, 0.010) ); g2->SetPointError( g2->GetN()-1, 0.0, cal_signifE(chain, 0.010, 0.015, 0.010, 0.010) );
  g2->SetPoint( g2->GetN(), 0.020, cal_signif(chain, 0.010, 0.020, 0.010, 0.010) ); g2->SetPointError( g2->GetN()-1, 0.0, cal_signifE(chain, 0.010, 0.020, 0.010, 0.010) );
  g2->SetPoint( g2->GetN(), 0.025, cal_signif(chain, 0.010, 0.025, 0.010, 0.010) ); g2->SetPointError( g2->GetN()-1, 0.0, cal_signifE(chain, 0.010, 0.025, 0.010, 0.010) );
  g2->SetPoint( g2->GetN(), 0.030, cal_signif(chain, 0.010, 0.030, 0.010, 0.010) ); g2->SetPointError( g2->GetN()-1, 0.0, cal_signifE(chain, 0.010, 0.030, 0.010, 0.010) );
  g2->SetTitle( "high edge of pi0 from D" );

  TGraphErrors* g3 = new TGraphErrors();
  g3->SetPoint( g3->GetN(), 0.010, cal_signif(chain, 0.010, 0.010, 0.010, 0.010) ); g3->SetPointError( g3->GetN()-1, 0.0, cal_signifE(chain, 0.010, 0.010, 0.010, 0.010) );
  g3->SetPoint( g3->GetN(), 0.015, cal_signif(chain, 0.010, 0.010, 0.015, 0.010) ); g3->SetPointError( g3->GetN()-1, 0.0, cal_signifE(chain, 0.010, 0.010, 0.015, 0.010) );
  g3->SetPoint( g3->GetN(), 0.020, cal_signif(chain, 0.010, 0.010, 0.020, 0.010) ); g3->SetPointError( g3->GetN()-1, 0.0, cal_signifE(chain, 0.010, 0.010, 0.020, 0.010) );
  g3->SetPoint( g3->GetN(), 0.025, cal_signif(chain, 0.010, 0.010, 0.025, 0.010) ); g3->SetPointError( g3->GetN()-1, 0.0, cal_signifE(chain, 0.010, 0.010, 0.025, 0.010) );
  g3->SetPoint( g3->GetN(), 0.030, cal_signif(chain, 0.010, 0.010, 0.030, 0.010) ); g3->SetPointError( g3->GetN()-1, 0.0, cal_signifE(chain, 0.010, 0.010, 0.030, 0.010) );
  g3->SetTitle( "low edge of pi0 from D*" );

  TGraphErrors* g4 = new TGraphErrors();
  g4->SetPoint( g4->GetN(), 0.010, cal_signif(chain, 0.010, 0.010, 0.010, 0.010) ); g4->SetPointError( g4->GetN()-1, 0.0, cal_signifE(chain, 0.010, 0.010, 0.010, 0.010) );
  g4->SetPoint( g4->GetN(), 0.015, cal_signif(chain, 0.010, 0.010, 0.010, 0.015) ); g4->SetPointError( g4->GetN()-1, 0.0, cal_signifE(chain, 0.010, 0.010, 0.010, 0.015) );
  g4->SetPoint( g4->GetN(), 0.020, cal_signif(chain, 0.010, 0.010, 0.010, 0.020) ); g4->SetPointError( g4->GetN()-1, 0.0, cal_signifE(chain, 0.010, 0.010, 0.010, 0.020) );
  g4->SetPoint( g4->GetN(), 0.025, cal_signif(chain, 0.010, 0.010, 0.010, 0.025) ); g4->SetPointError( g4->GetN()-1, 0.0, cal_signifE(chain, 0.010, 0.010, 0.010, 0.025) );
  g4->SetPoint( g4->GetN(), 0.030, cal_signif(chain, 0.010, 0.010, 0.010, 0.030) ); g4->SetPointError( g4->GetN()-1, 0.0, cal_signifE(chain, 0.010, 0.010, 0.010, 0.030) );
  g4->SetTitle( "high edge of pi0 from D*" );
	       


  TCanvas* can = Canvas( "can", "can", 2, 2 );
  can->cd(1); g1->Draw("AP");
  can->cd(2); g2->Draw("AP");
  can->cd(3); g3->Draw("AP");
  can->cd(4); g4->Draw("AP");

  // ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  std::cout << "finish" << std::endl;
  if( !gROOT->IsBatch() ) app.Run();
    
  return 0;
}

Double_t cal_signif( TChain* chain, Double_t mass_L, Double_t mass_H, Double_t mass_L_slow, Double_t mass_H_slow, Bool_t fl_error ){

  Double_t nsig_true  = chain->GetEntries( Form("(%s)&&(%s)&&(%s)&&(self==1)",                                       sigregion_cut, makeCut_pi0mass_d(mass_L, mass_H).c_str(), makeCut_pi0mass_dstr(mass_L_slow, mass_H_slow).c_str()) );
  Double_t nsig_false = chain->GetEntries( Form("(%s)&&(%s)&&(%s)&&(self==0&&gm_semi>0&&!(taulep1==0&&taulep2==0))", sigregion_cut, makeCut_pi0mass_d(mass_L, mass_H).c_str(), makeCut_pi0mass_dstr(mass_L_slow, mass_H_slow).c_str()) );
  Double_t nsig_cftau = chain->GetEntries( Form("(%s)&&(%s)&&(%s)&&(self==0&&gm_semi>0&& (taulep1==0&&taulep2==0))", sigregion_cut, makeCut_pi0mass_d(mass_L, mass_H).c_str(), makeCut_pi0mass_dstr(mass_L_slow, mass_H_slow).c_str()) );
  Double_t nnor_true  = chain->GetEntries( Form("(%s)&&(%s)&&(%s)&&(self==2)",                                       sigregion_cut, makeCut_pi0mass_d(mass_L, mass_H).c_str(), makeCut_pi0mass_dstr(mass_L_slow, mass_H_slow).c_str()) );
  Double_t nnor_false = chain->GetEntries( Form("(%s)&&(%s)&&(%s)&&(self==0&&gm_semi<0)",                            sigregion_cut, makeCut_pi0mass_d(mass_L, mass_H).c_str(), makeCut_pi0mass_dstr(mass_L_slow, mass_H_slow).c_str()) );
  Double_t nother     = chain->GetEntries( Form("(%s)&&(%s)&&(%s)&&(self<0)",                                        sigregion_cut, makeCut_pi0mass_d(mass_L, mass_H).c_str(), makeCut_pi0mass_dstr(mass_L_slow, mass_H_slow).c_str()) );

  if( fl_message && !fl_error ) std::cout << "nsig_true = "  << nsig_true/scale_factor  << ", "
					  << "nsig_false = " << nsig_false/scale_factor << ", "
					  << "nsig_cftau = " << nsig_cftau/scale_factor << std::endl
					  << "nnor_true = "  << nnor_true/scale_factor  << ", "
					  << "nnor_false = " << nnor_false/scale_factor << ", "
					  << "nother = "     << nother/scale_factor     << std::endl;
  
  //Double_t sig = nsig_true + nsig_false + nsig_cftau;
  //Double_t bkg = nnor_true + nnor_false + nother;
  Double_t sig = nsig_true;
  Double_t bkg = nsig_false + nsig_cftau + nnor_true + nnor_false + nother;

  Double_t sigE = sqrt(sig);
  Double_t bkgE = sqrt(bkg);

  sig  /= scale_factor; // bug fixed @20140124
  sigE /= scale_factor;
  bkg  /= scale_factor;
  bkgE /= scale_factor;
  if( fl_message && !fl_error ) std::cout << "sig = " << sig << " +- " << sigE << ", "
					  << "bkg = " << bkg << " +- " << bkgE << std::endl;
  
    
  Double_t signif_ds = 1.0/sqrt(sig+bkg) - 0.5*sig*pow(sig+bkg,-3.0/2.0);
  Double_t signif_db =                   - 0.5*sig*pow(sig+bkg,-3.0/2.0);
  Double_t signif    = sig/sqrt(sig+bkg);
  Double_t signifE   = sqrt( pow(signif_ds, 2)*pow(sigE,2) + pow(signif_db, 2)*pow(bkgE,2) );
  
  
  if( fl_message && !fl_error ) std::cout << "signif = " << signif << " +- " << signifE
					  << std::endl   << std::endl;
  
  if( fl_error ) return signifE;
  else           return signif;
}

Double_t cal_signifE( TChain* chain, Double_t mass_L, Double_t mass_H, Double_t mass_L_slow, Double_t mass_H_slow ){
  Double_t signifE = cal_signif( chain, mass_L, mass_H, mass_L_slow, mass_H_slow, true );

  return signifE;
}
