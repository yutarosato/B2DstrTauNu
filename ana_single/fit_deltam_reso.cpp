#include "draws_.h"
#include "draws_single.h"

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
using namespace CTGRY_DSTR;
const Char_t*  brname   = "dm1";
const Char_t*  axisname = "#Deltam [GeV]";
Int_t    xbin     = 330;
Double_t xmin     = 0.139;
Double_t xmax     = 0.150;
Double_t xmin_fit = 0.139;
Double_t xmax_fit = 0.150;
Int_t    fl_dec   = 0;
const Char_t* selection = "abs(cosdl1)<1.0";
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
void manip_func( TF1* func ){
  func->SetParLimits( 1, 0.0, 1.0 );
  //func->FixParameter( 3, func->GetParameter(3) );
  //func->SetParLimits( 2, 0.00008, 0.005 );
  func->SetParLimits( 4, 0.0,   100.0 ); // alpha_l
  func->SetParLimits( 5, 0.0,   100.0 ); // n_l
  func->SetParLimits( 6, 0.0,    10.0 ); // R_sigma_l
  func->SetParLimits( 7, 0.0,   100.0 ); // alpha_h
  func->SetParLimits( 8, 0.0,   100.0 ); // n_h
  func->SetParLimits( 9, 0.0,    10.0 ); // R_sigma_h

  if( fl_dec==1110 || fl_dec==102 ){
    func->FixParameter( 1, 0.0    );
    func->FixParameter( 2, 0.0005 );
  }

  return;
}

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
Int_t main( Int_t argc, Char_t** argv ){
  gROOT->SetBatch(true); // tmpppppp
  TApplication app( "app", &argc, argv );
  TStyle* sty = Style();
  sty->SetTitleOffset(1.0,"y");
  sty->SetOptStat(0);
  //sty->SetOptFit(0);
  sty->SetLabelSize(0.035,"xyz");
  sty->SetStatW(0.16);
  //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  if( app.Argc()!=4 ) std::cerr << "Wrong input"      << std::endl
				<< " Usage : "        << app.Argv(0)
				<< "(int)fl_dec (int)sel_fun_sig (int)sel_fun_bkg" << std::endl
				<< "sel_fun_sig : 40000(cb with both-tail + gauss)"
				<< "sel_fun_bkg : 81(threshold function)" << std::endl
				<< std::endl, abort();
  //Int_t fl_dec = atoi(app.Argv(1));
  fl_dec = atoi(app.Argv(1));

  Int_t sel_fun_sig = atoi(app.Argv(2));
  Int_t sel_fun_bkg = atoi(app.Argv(3));
  Int_t sel_fun_tot = sel_fun_sig + sel_fun_bkg;

  Double_t threshold = PDGmass::pip;
  Double_t mean      = PDGmass::dstrp - PDGmass::d0;
  if( fl_dec==201 || fl_dec==1110 || fl_dec==310 || fl_dec==110 || fl_dec==102 || fl_dec==411 ){
    threshold = PDGmass::pi0;
    mean      = PDGmass::dstrp - PDGmass::dp;
    xmin     -= 0.005;
    xmax     -= 0.005;
    xmin_fit -= 0.005;
    xmax_fit -= 0.005;
  }
  Double_t cnt_xmin = xmin;
  Double_t cnt_xmax = xmax;
  //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  TChain* c_dt = new TChain(treename);
  std::cout << "[DT] "
	    << c_dt->Add("~/dstrtaunu/modules/dstrtaunu/hbk_single/store/hbk18/through_cut_looseDstr/RD.root" ) << " files -> ";
  std::cout << c_dt->GetEntries() << " entries" << std::endl;
  TChain* c_mc = new TChain(treename);
  std::cout << "[MC] "
	    << c_mc->Add("~/dstrtaunu/modules/dstrtaunu/hbk_single/store/hbk18/through_cut_looseDstr/gMC_*.root") << " files -> ";
  std::cout << c_mc->GetEntries() << " entries" << std::endl;
  //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  TH1D**        hist   = new TH1D*[nhist]; // 0(rd), 1(tota-mc), 2-?(mc)
  THStack*      mh     = new THStack();
  TLegend*      leg    = new TLegend( 0.70,0.65,0.99,0.99 );
  makeHist( fl_dec, c_dt, c_mc, hist, mh, leg,
	    brname, axisname, xbin, xmin, xmax, selection,
	    nhist, ctgry_name, ctgry_sel, ctgry_lcol, ctgry_fcol );
  
  TCanvas* can = Canvas( "can", "can", 2, 2 );
  can->cd(1);
  
  TPad* padU1 = makePadU( "padU1", "padU1" );
  padU1->Draw();
  padU1->cd(0);
  mh->SetMaximum( 1.4*hist[1]->GetMaximum() );
  mh->Draw("hist");
  mh->GetXaxis()->SetLabelSize(0);
  mh->GetXaxis()->SetTitleSize(0);
  mh->SetTitle( Form("dec(%d)",fl_dec) );
  hist[1]->DrawCopy("sameE2"); // mc(total)
  hist[0]->DrawCopy("PEsame"); // dt
  leg->Draw();

  TPad* padD1 = makePadD( "padD1", "padD1" );
  padD1->Draw();
  padD1->cd(0);

  TGraph* res1 = Residual(hist[0], hist[1], axisname );
  res1->Draw("APE");
  TLine* line1 = new TLine(xmin, 0.0, xmax, 0.0);
  line1->Draw();

  //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  // MC (only signal)
  can->cd(3);

  TPad* padU3 = makePadU( "padU3", "padU3" );
  padU3->Draw();
  padU3->cd(0);

  TH1D* hist_sig = (TH1D*)hist[0]->Clone();
  hist_sig->Reset(); // (clear all of bin contents and remaining binning, style, etc.)
  hist_sig->SetTitle( Form("h%d_%d [%s]",fl_dec, 1, "mc(true)") );
  hist_sig->Add( hist[2] );
  hist_sig->Add( hist[3] );
  hist_sig->Add( hist[5] );
  hist_sig->Draw();
  TF1* func_sig_mc = new TF1( "func_sig_mc", make_func(sel_fun_sig),xmin,xmax,n_fitfunc_par(sel_fun_sig) );
  //Double_t sigma = 0.0004;
  Double_t sigma = 0.0005;
  Double_t area  = hist_sig->GetMaximum()*sqrt(TMath::TwoPi())*sigma;
  std::cout << "mean = " << mean << std::endl;
  std::cout << "area = " << area << std::endl;
  
  func_sig_mc->SetParNames  (  "S", "R_{S}", "#sigma", "#mu", "#alpha_{l}","n_{l}", "R_{#sigma_{l}}","#alpha_{h}","n_{h}", "R_{#sigma_{h}}" );
  func_sig_mc->SetParameters( area,     0.4,   sigma,   mean,          1.0,    1.3,              2.0,         1.6,    1.5,              2.5 );
  if( fl_dec==102 ) func_sig_mc->SetParLimits( 2, 0.00010, 0.005 ); // sigma
  func_sig_mc->SetParLimits( 5, 0.0,    100.0 ); // n
  func_sig_mc->SetParLimits( 8, 0.0,    100.0 ); // n
  
  func_sig_mc->SetLineColor(3);
  func_sig_mc->SetLineWidth(2);
  Double_t init_var[n_fitfunc_par(sel_fun_sig)];
  for( Int_t m=0; m<n_fitfunc_par(sel_fun_sig); m++ ) init_var[m] = func_sig_mc->GetParameter(m);
  iterative_fit( hist_sig, func_sig_mc, n_fitfunc_par(sel_fun_sig), init_var, "PRE0", manip_func );
  func_sig_mc->Draw("LsameS");
  
  TPad* padD3 = makePadD( "padD3", "padD3" );
  padD3->Draw();
  padD3->cd(0);

  TGraph* res3 = Residual(hist_sig, func_sig_mc, axisname );
  res3->Draw("APE");
  TLine* line3 = new TLine(xmin, 0.0, xmax, 0.0);
  line3->Draw();
  //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  // MC (total)

  can->cd(4);
  TPad* padU4 = makePadU( "padU4", "padU4" );
  padU4->Draw();
  padU4->cd(0);

  hist[1]->SetMinimum(0);
  hist[1]->SetMaximum( 1.3*hist[1]->GetMaximum() );
  hist[1]->Draw("E2"); // mc(total)
  mh->Draw("histsame");
  hist[1]->Draw("sameE2"); // mc(total)
  TF1* func_tot_mc = new TF1( "func_tot_mc", make_func(sel_fun_tot),xmin_fit,xmax_fit,n_fitfunc_par(sel_fun_tot) );
  Double_t slope  = (hist[1]->GetBinContent(xbin) - hist[1]->GetBinContent(1))/(xmax-xmin);
  Double_t offset = hist[1]->GetBinContent(1) - slope*xmin;
  Double_t shape  = -20;
  Double_t s_bkg  = hist[1]->GetBinContent(xbin)/( pow(xmax-threshold,0.5) + shape*pow(xmax-threshold,1.5) );
  area  = func_sig_mc->GetParameter(0);
  sigma = func_sig_mc->GetParameter(2);

  func_tot_mc->SetParNames  (  "S", "R_{S}", "#sigma", "#mu", "#alpha_{l}","n_{l}", "R_{#sigma_{l}}","#alpha_{h}","n_{h}", "R_{#sigma_{h}}", "S_{bkg}" );
  func_tot_mc->SetParameters( area,     0.7,    sigma,  mean,          1.4,    1.2,              1.8,         1.7,    1.1,              2.5,  s_bkg    );
  func_tot_mc->SetParName  ( 11, "th"      );
  func_tot_mc->SetParName  ( 12, "shape"   );
  func_tot_mc->SetParName  ( 13, "shape2"  );
  func_tot_mc->FixParameter( 11, threshold );
  func_tot_mc->SetParameter( 12, shape     );
  func_tot_mc->SetParameter( 13, 0         );

  for( Int_t i=1; i<n_fitfunc_par(sel_fun_sig); i++ ) func_tot_mc->FixParameter(i, func_sig_mc->GetParameter(i));
  func_tot_mc->ReleaseParameter(2);    

  func_tot_mc->SetLineColor(3);
  func_tot_mc->SetLineWidth(2);
  hist[1]->Fit(func_tot_mc,"L0","",xmin_fit,xmax_fit);
  func_tot_mc->Draw("LsameS");

  TF1* func_bkg_mc = new TF1( "func_bkg_mc", make_func(sel_fun_bkg),xmin_fit,xmax_fit,n_fitfunc_par(sel_fun_bkg) );
  func_bkg_mc->SetParNames  ( "S", "threshold", "k" );
  func_bkg_mc->SetParameters( func_tot_mc->GetParameter(10), func_tot_mc->GetParameter(11), func_tot_mc->GetParameter(12) , func_tot_mc->GetParameter(13) );

  func_bkg_mc->SetLineColor(7);
  func_bkg_mc->SetLineWidth(2);
  func_bkg_mc->Draw("Lsame");

  TPad* padD4 = makePadD( "padD4", "padD4" );
  padD4->Draw();
  padD4->cd(0);

  TGraph* res4 = Residual(hist[1], func_tot_mc, axisname );
  res4->Draw("APE");
  TLine* line4 = new TLine(xmin, 0.0, xmax, 0.0);
  line4->Draw();

  //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  ///*
  Double_t ntot_func  = func_tot_mc->Integral     (cnt_xmin, cnt_xmax)/((xmax-xmin)/xbin);
  Double_t ntot_funcE = func_tot_mc->IntegralError(cnt_xmin, cnt_xmax)/((xmax-xmin)/xbin);
  Double_t nbkg_func  = func_bkg_mc->Integral     (cnt_xmin, cnt_xmax)/((xmax-xmin)/xbin);
  Double_t nsig_func  = ntot_func - nbkg_func;
  std::cout << "[Estimeted in " << cnt_xmin  << " ~ "  << cnt_xmax   << " GeV]" << std::endl;
  std::cout << "N(tot,func) = " << ntot_func << " +- " << ntot_funcE << std::endl;
  std::cout << "N(sig,func) = " << nsig_func << " +- " << nsig_func*func_tot_mc->GetParError(0)/func_tot_mc->GetParameter(0) << std::endl;
  std::cout << "N(bkg,func) = " << nbkg_func                         << std::endl;

  Double_t ntot_hist = hist[1]->Integral( hist[1]->FindBin(cnt_xmin), hist[1]->FindBin(cnt_xmax-1e-6) );
  Double_t nsig_hist =
    hist[2]->Integral( hist[2]->FindBin(cnt_xmin), hist[2]->FindBin(cnt_xmax-1e-6) ) + 
    hist[3]->Integral( hist[3]->FindBin(cnt_xmin), hist[3]->FindBin(cnt_xmax-1e-6) );
  Double_t nbkg_hist = ntot_hist - nsig_hist;
  std::cout << "N(tot,hist) = " << ntot_hist << " +- " << sqrt(ntot_hist) << std::endl;
  std::cout << "N(sig,hist) = " << nsig_hist << " +- " << sqrt(nsig_hist) << std::endl;
  std::cout << "N(bkg,hist) = " << nbkg_hist << " +- " << sqrt(nbkg_hist) << std::endl;
  std::cout << "N(sig,func-hist) = " << nsig_func - nsig_hist << std::endl;
  //*/
  //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  // Data (total)
  can->cd(2);
  TPad* padU2 = makePadU( "padU2", "padU2" );
  padU2->Draw();
  padU2->cd(0);
  hist[0]->SetMaximum( 1.3*hist[0]->GetMaximum() );
  hist[0]->Draw();
  TF1* func_tot_dt = new TF1( "func_tot_dt", make_func(sel_fun_tot),xmin_fit,xmax_fit,n_fitfunc_par(sel_fun_tot) );
  slope  = (hist[0]->GetBinContent(xbin) - hist[0]->GetBinContent(1))/(xmax-xmin);
  offset = hist[0]->GetBinContent(1) - slope*xmin;
  s_bkg  = hist[0]->GetBinContent(xbin)/( pow(xmax-threshold,0.5) + shape*pow(xmax-threshold,1.5) );

  func_tot_dt->SetParNames  (  "S", "R_{S}", "#sigma", "#mu", "#alpha_{l}","n_{l}", "R_{#sigma_{l}}","#alpha_{h}","n_{h}", "R_{#sigma_{h}}", "S_{bkg}" );
  func_tot_dt->SetParameters( area,     0.7,    sigma,  mean,          1.0,    1.3,              2.0,         1.0,    1.3,              2.0,  s_bkg    );
  func_tot_dt->SetParName  ( 11, "th"      );
  func_tot_dt->SetParName  ( 12, "shape"   );
  func_tot_dt->SetParName  ( 13, "shape2"  );
  func_tot_dt->FixParameter( 11, threshold );
  func_tot_dt->SetParameter( 12, shape     );
  func_tot_dt->SetParameter( 13, 0         );

  for( Int_t i=1; i<n_fitfunc_par(sel_fun_sig); i++ ) func_tot_dt->FixParameter(i, func_sig_mc->GetParameter(i));
  func_tot_dt->ReleaseParameter(2);    
  func_tot_dt->ReleaseParameter(3);

  func_tot_dt->SetLineColor(3);
  func_tot_dt->SetLineWidth(2);
  hist[0]->Fit( func_tot_dt, "L0","",xmin_fit,xmax_fit );
  func_tot_dt->Draw("LsameS");
  
  TF1* func_bkg_dt = new TF1( "func_bkg_dt", make_func(sel_fun_bkg),xmin_fit,xmax_fit,n_fitfunc_par(sel_fun_bkg) );
  func_bkg_dt->SetParNames  ( "S", "threshold", "k" );
  func_bkg_dt->SetParameters( func_tot_dt->GetParameter(10), func_tot_dt->GetParameter(11), func_tot_dt->GetParameter(12), func_tot_dt->GetParameter(13) );

  func_bkg_dt->SetLineColor(7);
  func_bkg_dt->SetLineWidth(2);
  func_bkg_dt->Draw("Lsame");

  TPad* padD2 = makePadD( "padD2", "padD2" );
  padD2->Draw();
  padD2->cd(0);

  TGraph* res2 = Residual(hist[0], func_tot_dt, axisname );
  res2->Draw("APE");
  TLine* line2 = new TLine(xmin, 0.0, xmax, 0.0);
  line2->Draw();

  //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  Double_t range   = 0.0025;
  Double_t nbkg_d0 = func_bkg_dt->Integral( (PDGmass::dstrp-PDGmass::d0)-range, (PDGmass::dstrp-PDGmass::d0)+range )/((xmax-xmin)/xbin);
  Double_t nbkg_dp = func_bkg_dt->Integral( (PDGmass::dstrp-PDGmass::dp)-range, (PDGmass::dstrp-PDGmass::dp)+range )/((xmax-xmin)/xbin);
  Double_t ntot_d0 = func_tot_dt->Integral( (PDGmass::dstrp-PDGmass::d0)-range, (PDGmass::dstrp-PDGmass::d0)+range )/((xmax-xmin)/xbin);
  Double_t ntot_dp = func_tot_dt->Integral( (PDGmass::dstrp-PDGmass::dp)-range, (PDGmass::dstrp-PDGmass::dp)+range )/((xmax-xmin)/xbin);
  Double_t nsig_d0 = ntot_d0 - nbkg_d0;
  Double_t nsig_dp = ntot_dp - nbkg_dp;

  std::cout << "[D0] " 
	    << std::setw(8) << std::right << ntot_d0 << " (tot) = "
	    << std::setw(8) << std::right << nsig_d0 << " (sig) + "
	    << std::setw(8) << std::right << nbkg_d0 << " (bkg)" << std::endl;
  std::cout << "[D+] " 
	    << std::setw(8) << std::right << ntot_dp << " (tot) = "
	    << std::setw(8) << std::right << nsig_dp << " (sig) + "
	    << std::setw(8) << std::right << nbkg_dp << " (bkg)" << std::endl;

  std::cout << std::setw(12) << std::right << dec_index(fl_dec)
	    << std::setw( 5) << std::right << fl_dec
	    << std::setw( 6) << std::right << sel_fun_sig
	    << std::setw(15) << std::right << func_tot_dt->GetParameter(2)/func_tot_mc->GetParameter(2)
	    << std::setw(15) << std::right << func_tot_dt->GetParameter(2)/func_tot_mc->GetParameter(2)*sqrt( pow ( func_tot_dt->GetParError(2)/func_tot_dt->GetParameter(2), 2 )
													      +pow( func_tot_mc->GetParError(2)/func_tot_mc->GetParameter(2), 2 )
													      )
	    << std::setw(15) << std::right << func_sig_mc->GetParameter(2)
	    << std::setw(15) << std::right << func_sig_mc->GetParError (2)
	    << std::setw(15) << std::right << func_tot_dt->GetParameter(3)
	    << std::setw(15) << std::right << func_tot_dt->GetParError (3);
  if     ( fl_dec==421 || fl_dec==411 ) std::cout << std::endl;
  else if( threshold==PDGmass::pip    ) std::cout << " HOGE1" << std::endl;
  else                                  std::cout << " HOGE2" << std::endl;
  //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  TFile outfile( Form("pic/%s_%d.root", brname,fl_dec), "RECREATE" );
  can->Write();
  //TF1* func_sig_save_dt = new TF1( Form("func_sig_dt_%d",fl_dec), make_func(sel_fun_sig),xmin,xmax,n_fitfunc_par(sel_fun_sig) );
  //TF1* func_sig_save_mc = new TF1( Form("func_sig_mc_%d",fl_dec), make_func(sel_fun_sig),xmin,xmax,n_fitfunc_par(sel_fun_sig) );
  TF1* func_sig_save_dt = new TF1( Form("func_sig_dt_%d",fl_dec), make_func(sel_fun_sig),0.134,0.155,n_fitfunc_par(sel_fun_sig) );
  TF1* func_sig_save_mc = new TF1( Form("func_sig_mc_%d",fl_dec), make_func(sel_fun_sig),0.134,0.155,n_fitfunc_par(sel_fun_sig) );
  for( Int_t i=0; i<n_fitfunc_par(sel_fun_sig); i++ ) func_sig_save_dt->SetParameter(i, func_sig_mc->GetParameter(i));
  for( Int_t i=0; i<n_fitfunc_par(sel_fun_sig); i++ ) func_sig_save_mc->SetParameter(i, func_sig_mc->GetParameter(i));
  //func_sig_save_dt->SetParameter( 2, func_sig_mc->GetParameter(2) * (func_tot_dt->GetParameter(2)/func_tot_mc->GetParameter(2)) );
  //func_sig_save_dt->SetParameter( 3, func_tot_dt->GetParameter(3) );
  if( threshold==PDGmass::pip ){
    func_sig_save_dt->SetParameter( 2, func_sig_mc->GetParameter(2) *  1.26479 ); // 20150326
    func_sig_save_dt->SetParameter( 3, 0.145346 );
  }else{
    func_sig_save_dt->SetParameter( 2, func_sig_mc->GetParameter(2) *  0.99473 ); // 20150326
    func_sig_save_dt->SetParameter( 3, 0.140645 );
  }

  func_sig_save_dt->Write();
  func_sig_save_mc->Write();
  outfile.Close();
  //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  can->Print( Form("pic/%s_%d_%d_%d.ps", brname,fl_dec,sel_fun_sig,sel_fun_bkg) ); 
  std::cout << "finish" << std::endl;
  if( !gROOT->IsBatch() ) app.Run();
  return 0;
}

