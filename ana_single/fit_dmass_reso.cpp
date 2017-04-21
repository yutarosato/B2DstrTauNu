#include "draws_.h"
#include "draws_single.h"

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
using namespace CTGRY_D;
const Char_t*  brname   = "d1_m";
const Char_t*  axisname = "m_{D} [GeV]";
const Int_t    xbin     =  200;
const Double_t xmin     = 1.80;
const Double_t xmax     = 1.90;
//const Int_t    xbin     =  300;
//const Double_t xmin     = 1.77;
//const Double_t xmax     = 1.92;

Double_t cnt_xmin = 1.80;
Double_t cnt_xmax = 1.90;
Double_t fit_xmin = 1.80;
Double_t fit_xmax = 1.90;
const Char_t* selection = "abs(cosdl1)<1.0";
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
void manip_func( TF1* func ){
  //func->FixParameter( 3, func->GetParameter(3) );
  func->SetParLimits( 2, 0.0,   50.0 );
  func->SetParLimits( 6, 0.0,   50.0 );
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
  sty->SetLabelSize(0.035,"xyz");
  sty->SetOptFit(11);
  sty->SetStatW(0.16);
  //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  if( app.Argc()!=4 ) std::cerr << "Wrong input"      << std::endl
				<< " Usage : "        << app.Argv(0)
				<< "(int)fl_dec (int)sel_fun_sig (int)sel_fun_bkg" << std::endl
				<< "sel_fun_sig : 30(triple gaussian), 30000(cb with both-tailfor asymmetric scale factor), 33000(cb with both-tailfor symmetric scale factor)" << std::endl
				<< "sel_fun_bkg : 1(1st polynomial), 2(2nd polynomial)" << std::endl
				<< std::endl, abort();
  Int_t fl_dec      = atoi(app.Argv(1));
  Int_t sel_fun_sig = atoi(app.Argv(2));
  Int_t sel_fun_bkg = atoi(app.Argv(3));

  Int_t sel_fun_tot = sel_fun_sig + sel_fun_bkg;
  if( fl_dec==200 ) fit_xmin = 1.82;
 
  //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  TChain* c_dt = new TChain(treename);
  std::cout << "[DT] "
	    << c_dt->Add("~/dstrtaunu/modules/dstrtaunu/hbk_single/store/hbk18/through_cut_looseD/RD.root" ) << " files -> ";
  std::cout << c_dt->GetEntries() << " entries" << std::endl;

  TChain* c_mc = new TChain(treename);
  std::cout << "[MC] "
	    << c_mc->Add("~/dstrtaunu/modules/dstrtaunu/hbk_single/store/hbk18/through_cut_looseD/gMC_*.root") << " files -> ";
  std::cout << c_mc->GetEntries() << " entries" << std::endl;
  //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  TH1D**        hist   = new TH1D*[nhist]; // 0(rd), 1(tota-mc), 2-X(mc)
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
  //hist_sig->SetMaximum( 1.8*hist_sig->GetMaximum() );
  hist_sig->Draw();
  TF1* func_sig_mc = new TF1( "func_sig_mc", make_func(sel_fun_sig),xmin,xmax,n_fitfunc_par(sel_fun_sig) );
  Double_t sigma = 0.004;
  Double_t area  = hist_sig->GetMaximum()*sqrt(TMath::TwoPi())*sigma;
  Double_t mean  = nominal_dmass( fl_dec );
  if( sel_fun_sig==30 ){
    func_sig_mc->SetParNames  (  "S", "R_{S_{1}}", "R_{S_{2}}", "#mu", "#sigma", "R_{#sigma_{2}}", "R_{#sigma_{3}}" );
    func_sig_mc->SetParameters( area,         0.6,         0.3,  mean,    sigma,              2.0,             40.0 );
    func_sig_mc->SetParLimits( 1, 0.0,   1.0 );
    func_sig_mc->SetParLimits( 2, 0.0,   1.0 );
    func_sig_mc->SetParLimits( 5, 1.0, 100.0 );
    func_sig_mc->SetParLimits( 6, 1.0, 100.0 );
  }else if( sel_fun_sig==30000 ){
    func_sig_mc->SetParNames  (  "S","#alpha_{l}","n_{l}", "#mu", "#sigma_{l}","#alpha_{h}","n_{h}","#sigma_{h}" );
    //func_sig_mc->SetParameters( area,         1.0,    1.3,  mean,        sigma,         3.0,    2.0,       sigma );
    func_sig_mc->SetParameters( area,         1.3,    1.6,  mean,        sigma,         6.0,    5.0,       sigma );
    func_sig_mc->SetParLimits( 2, 0.0,   50.0 );
    func_sig_mc->SetParLimits( 6, 0.0,   50.0 );
  }else if( sel_fun_sig==33000 ){
    func_sig_mc->SetParNames  (  "S","#alpha_{l}","n_{l}", "#mu", "#sigma","#alpha_{h}","n_{h}","r_{#sigma}" );
    func_sig_mc->SetParameters( area,         1.0,    1.3,  mean,    sigma,         1.0,    1.3,        1.0  );
  }else{
    std::cerr << "[ABORT] Wrong fitting function : " << sel_fun_sig << std::endl, abort();
  }
  
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
  //hist[1]->SetMaximum( 1.8*hist[1]->GetMaximum() );
  hist[1]->Draw("E2"); // mc(total)
  mh->Draw("histsame");
  hist[1]->Draw("sameE2"); // mc(total)
  TF1* func_tot_mc = new TF1( "func_tot_mc", make_func(sel_fun_tot),xmin,xmax,n_fitfunc_par(sel_fun_tot) );

  area  = func_sig_mc->GetParameter(0);
  sigma = func_sig_mc->GetParameter(4);
  
  Double_t slope;
  Double_t offset;
  Double_t second;
  if( sel_fun_bkg==1 ){
    slope = (hist[1]->GetBinContent(xbin) - hist[1]->GetBinContent(1))/(xmax-xmin);
    offset = hist[1]->GetBinContent(1) - slope*xmin;
  }else{
    /*
    second =  -39400;
    slope  =  144300;
    offset = -130200;
    Double_t scale = (second*xmin*xmin + slope*xmin + offset)/hist[1]->GetBinContent(1);
    second *= scale;
    slope  *= scale;
    offset *= scale;
    */
    ///*
    double max = (hist[1]->GetBinContent(xbin) - hist[1]->GetBinContent(1))/2.0;
    second = (hist[1]->GetBinContent(1) - max)/(xmin - 3.6*0.9);
    //second *=4;
    slope  = -3.6*second;
    offset = max + 3.6*3.6/4.0*second;
    //*/
    second = -39400;
    slope  = 144300;
    offset = -130200;
  }


  if( sel_fun_tot==32 ){
    func_tot_mc->SetParNames  (  "S", "R_{S_{1}}", "R_{S_{2}}", "#mu", "#sigma", "R_{#sigma_{2}}", "R_{#sigma_{3}}", "second", "slope", "offset" );
    func_tot_mc->SetParameters( area,         0.6,         0.3,  mean,    sigma,              2.0,             40.0,  second,   slope,   offset  );
    for( Int_t i=1; i<n_fitfunc_par(sel_fun_sig); i++ ) func_tot_mc->FixParameter(i, func_sig_mc->GetParameter(i));
  }else if( sel_fun_tot==31 ){
    func_tot_mc->SetParNames  (  "S", "R_{S_{1}}", "R_{S_{2}}", "#mu", "#sigma", "R_{#sigma_{2}}", "R_{#sigma_{3}}", "slope", "offset" );
    func_tot_mc->SetParameters( area,         0.6,         0.3,  mean,    sigma,              2.0,             40.0,  slope,   offset  );
    for( Int_t i=1; i<n_fitfunc_par(sel_fun_sig); i++ ) func_tot_mc->FixParameter(i, func_sig_mc->GetParameter(i));
  }else if( sel_fun_tot==30002 ){
    func_tot_mc->SetParNames  (  "S","#alpha_{l}","n_{l}", "#mu", "#sigma_{l}","#alpha_{h}","n_{h}","#sigma_{h}", "second", "slope", "offset" );
    func_tot_mc->SetParameters( area,         1.0,    1.3,  mean,        sigma,         1.0,    1.3,       sigma,  second,   slope,   offset  );
    //func_tot_mc->SetParameters( area,         1.0,    1.3,  mean,        sigma,         1.0,    1.3,       sigma,        -39400,   144300,  -130200  ); // tmppppp
    for( Int_t i=1; i<n_fitfunc_par(sel_fun_sig); i++ ) func_tot_mc->FixParameter(i, func_sig_mc->GetParameter(i));
  }else if( sel_fun_tot==30001 ){
    func_tot_mc->SetParNames  (  "S","#alpha_{l}","n_{l}", "#mu", "#sigma_{l}","#alpha_{h}","n_{h}","#sigma_{h}", "slope", "offset" );
    func_tot_mc->SetParameters( area,         1.0,    1.3,  mean,        sigma,         1.0,    1.3,       sigma,  slope,   offset  );
    for( Int_t i=1; i<n_fitfunc_par(sel_fun_sig); i++ ) func_tot_mc->FixParameter(i, func_sig_mc->GetParameter(i));
  }else if( sel_fun_tot==33002 ){
    func_tot_mc->SetParNames  (  "S","#alpha_{l}","n_{l}", "#mu", "#sigma","#alpha_{h}","n_{h}","r_{#sigma}", "second", "slope", "offset" );
    func_tot_mc->SetParameters( area,         1.0,    1.3,  mean,    sigma,         1.0,    1.3,       sigma,  second,   slope,   offset  );
    //func_tot_mc->SetParameters( area,         1.0,    1.3,  mean,        sigma,         1.0,    1.3,       1.0,        -39400,   144300,  -130200  ); // tmppppp
    for( Int_t i=1; i<n_fitfunc_par(sel_fun_sig); i++ ) func_tot_mc->FixParameter(i, func_sig_mc->GetParameter(i));
  }else if( sel_fun_tot==33001 ){
    func_tot_mc->SetParNames  (  "S","#alpha_{l}","n_{l}", "#mu", "#sigma","#alpha_{h}","n_{h}","r_{#sigma}", "slope", "offset" );
    func_tot_mc->SetParameters( area,         1.0,    1.3,  mean,    sigma,         1.0,    1.3,         1.0,  slope,   offset  );
    for( Int_t i=1; i<n_fitfunc_par(sel_fun_sig); i++ ) func_tot_mc->FixParameter(i, func_sig_mc->GetParameter(i));
  }else{
    std::cerr << "[ABORT] Wrong fitting function : " << sel_fun_tot << std::endl, abort();
  }
    

  func_tot_mc->SetLineColor(3);
  func_tot_mc->SetLineWidth(2);
  hist[1]->Fit( func_tot_mc, "L0", "", fit_xmin, fit_xmax );
  if( sel_fun_sig==   30 ){
    func_tot_mc->ReleaseParameter(4);
  }else if( sel_fun_sig==30000 ){
    func_tot_mc->ReleaseParameter(4);
    func_tot_mc->ReleaseParameter(7);
  }else if( sel_fun_sig==33000 ){
    func_tot_mc->ReleaseParameter(4);
  }else{
    std::cerr << "[ABORT] Wrong fitting function : " << sel_fun_tot << std::endl, abort();
  }
  hist[1]->Fit( func_tot_mc, "L0", "", fit_xmin, fit_xmax );

  
  func_tot_mc->Draw("LsameS");

  TF1* func_bkg_mc = new TF1( "func_bkg_mc", make_func(sel_fun_bkg),xmin,xmax,n_fitfunc_par(sel_fun_bkg) );
  if( sel_fun_bkg==1 ) func_bkg_mc->SetParNames  (           "slope", "offset" );
  else                 func_bkg_mc->SetParNames  ( "second", "slope", "offset" );
  if( sel_fun_tot==31 ){
    if( sel_fun_bkg==1 ) func_bkg_mc->SetParameters( func_tot_mc->GetParameter(7), func_tot_mc->GetParameter(8) );
    else                 func_bkg_mc->SetParameters( func_tot_mc->GetParameter(7), func_tot_mc->GetParameter(8), func_tot_mc->GetParameter(9) );
  }else{
    if( sel_fun_bkg==1 ) func_bkg_mc->SetParameters( func_tot_mc->GetParameter(8), func_tot_mc->GetParameter(9) );
    else                 func_bkg_mc->SetParameters( func_tot_mc->GetParameter(8), func_tot_mc->GetParameter(9), func_tot_mc->GetParameter(10) );
  }

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
  Double_t ntot_func  = func_tot_mc->Integral     (cnt_xmin, cnt_xmax)/((xmax-xmin)/xbin);
  Double_t ntot_funcE = func_tot_mc->IntegralError(cnt_xmin, cnt_xmax)/((xmax-xmin)/xbin);
  Double_t nbkg_func  = func_bkg_mc->Integral     (cnt_xmin, cnt_xmax)/((xmax-xmin)/xbin);
  Double_t nsig_func  = ntot_func - nbkg_func;
  std::cout << "[Estimeted in " << cnt_xmin  << " ~ "  << cnt_xmax   << " GeV]" << std::endl;
  std::cout << "N(tot,func) = " << ntot_func << " +- " << ntot_funcE << std::endl;
  std::cout << "N(sig,func) = " << nsig_func << " +- " << nsig_func*func_tot_mc->GetParError(0)/func_tot_mc->GetParameter(0) << std::endl;
  std::cout << "N(bkg,func) = " << nbkg_func << std::endl;

  Double_t ntot_hist = hist[1]->Integral( hist[1]->FindBin(cnt_xmin), hist[1]->FindBin(cnt_xmax-1e-6) );
  Double_t nsig_hist =
    hist[2]->Integral( hist[2]->FindBin(cnt_xmin), hist[2]->FindBin(cnt_xmax-1e-6) ) + 
    hist[3]->Integral( hist[3]->FindBin(cnt_xmin), hist[3]->FindBin(cnt_xmax-1e-6) );
  Double_t nbkg_hist = ntot_hist - nsig_hist;
  std::cout << "N(tot,hist) = " << ntot_hist << " +- " << sqrt(ntot_hist) << std::endl;
  std::cout << "N(sig,hist) = " << nsig_hist << " +- " << sqrt(nsig_hist) << std::endl;
  std::cout << "N(bkg,hist) = " << nbkg_hist << " +- " << sqrt(nbkg_hist) << std::endl;
  std::cout << "N(sig,func-hist) = " << nsig_func - nsig_hist << std::endl;
  
  //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  // Data (total)
  can->cd(2);
  TPad* padU2 = makePadU( "padU2", "padU2" );
  padU2->Draw();
  padU2->cd(0);
  //hist[0]->SetMaximum( 1.8*hist[0]->GetMaximum() );
  hist[0]->Draw();
  TF1* func_tot_dt = new TF1( "func_tot_dt", make_func(sel_fun_tot),xmin,xmax,n_fitfunc_par(sel_fun_tot) );
  sigma  = func_sig_mc->GetParameter(4);

  if( sel_fun_bkg==1 ){
    slope = (hist[0]->GetBinContent(xbin) - hist[0]->GetBinContent(1))/(xmax-xmin);
    offset = hist[0]->GetBinContent(1) - slope*xmin;
  }else{
    /*
    second =  -39400;
    slope  =  144300;
    offset = -130200;
    Double_t scale = (second*xmin*xmin + slope*xmin + offset)/hist[1]->GetBinContent(1);
    second *= scale;
    slope  *= scale;
    offset *= scale;
    */
    ///*
    double max = (hist[0]->GetBinContent(xbin) - hist[0]->GetBinContent(1))/2.0;
    second = (hist[0]->GetBinContent(1) - max)/(xmin - 3.6*0.9);
    //second *=4;
    slope  = -3.6*second;
    offset = max + 3.6*3.6/4.0*second;
    //*/
    second = -27970;
    slope  = 102200;
    offset = -91670;
  }

  if( sel_fun_tot==32 ){
    func_tot_dt->SetParNames  (  "S", "R_{S_{1}}", "R_{S_{2}}", "#mu", "#sigma", "R_{#sigma_{2}}", "R_{#sigma_{3}}", "second", "slope", "offset" );
    func_tot_dt->SetParameters( area,         0.6,         0.3,  mean,    sigma,              2.0,             40.0,        0,  slope,   offset  );
    for( Int_t i=1; i<n_fitfunc_par(sel_fun_sig); i++ ) func_tot_dt->FixParameter(i, func_sig_mc->GetParameter(i));
  }else if( sel_fun_tot==31 ){
    func_tot_dt->SetParNames  (  "S", "R_{S_{1}}", "R_{S_{2}}", "#mu", "#sigma", "R_{#sigma_{2}}", "R_{#sigma_{3}}", "slope", "offset" );
    func_tot_dt->SetParameters( area,         0.6,         0.3,  mean,    sigma,              2.0,             40.0,  slope,   offset  );
    for( Int_t i=1; i<n_fitfunc_par(sel_fun_sig); i++ ) func_tot_dt->FixParameter(i, func_sig_mc->GetParameter(i));
  }else if( sel_fun_tot==30002 ){
    func_tot_dt->SetParNames  (  "S","#alpha_{l}","n_{l}", "#mu", "#sigma_{l}","#alpha_{h}","n_{h}","#sigma_{h}", "second", "slope", "offset" );
    func_tot_dt->SetParameters( area,         1.0,    1.3,  mean,        sigma,         1.0,    1.3,       sigma,  second,   slope,   offset  );
    //func_tot_dt->SetParameters( area,         1.0,    1.3,  mean,        sigma,         1.0,    1.3,       sigma,        -27973, 102151, -91670 ); // tmppppp
    for( Int_t i=1; i<n_fitfunc_par(sel_fun_sig); i++ ) func_tot_dt->FixParameter(i, func_sig_mc->GetParameter(i));
  }else if( sel_fun_tot==30001 ){
    func_tot_dt->SetParNames  (  "S","#alpha_{l}","n_{l}", "#mu", "#sigma_{l}","#alpha_{h}","n_{h}","#sigma_{h}", "slope", "offset" );
    func_tot_dt->SetParameters( area,         1.0,    1.3,  mean,        sigma,         1.0,    1.3,       sigma,  slope,   offset  );
    for( Int_t i=1; i<n_fitfunc_par(sel_fun_sig); i++ ) func_tot_dt->FixParameter(i, func_sig_mc->GetParameter(i));
  }else if( sel_fun_tot==33002 ){
    func_tot_dt->SetParNames  (  "S","#alpha_{l}","n_{l}", "#mu", "#sigma","#alpha_{h}","n_{h}","r_{#sigma}", "second", "slope", "offset" );
    func_tot_dt->SetParameters( area,         1.0,    1.3,  mean,    sigma,         1.0,    1.3,         1.0,  second,   slope,   offset  );
    //func_tot_dt->SetParameters( area,         1.0,    1.3,  mean,        sigma,         1.0,    1.3,         1.0,        -46489, 170479, -154670 ); // tmppppp
    for( Int_t i=1; i<n_fitfunc_par(sel_fun_sig); i++ ) func_tot_dt->FixParameter(i, func_sig_mc->GetParameter(i));
  }else if( sel_fun_tot==33001 ){
    func_tot_dt->SetParNames  (  "S","#alpha_{l}","n_{l}", "#mu", "#sigma","#alpha_{h}","n_{h}","r_{#sigma}", "slope", "offset" );
    func_tot_dt->SetParameters( area,         1.0,    1.3,  mean,    sigma,         1.0,    1.3,         1.0,  slope,   offset  );
    //func_tot_dt->SetParameters( area,         1.0,    1.3,  mean,        sigma,         1.0,    1.3,         1.0,        -46489, 170479, -154670 ); // tmppppp
    for( Int_t i=1; i<n_fitfunc_par(sel_fun_sig); i++ ) func_tot_dt->FixParameter(i, func_sig_mc->GetParameter(i));
  }else{
    std::cerr << "[ABORT] Wrong fitting function : " << sel_fun_tot << std::endl, abort();
  }
  
  func_tot_dt->SetLineColor(3);
  func_tot_dt->SetLineWidth(2);
  hist[0]->Fit( func_tot_dt, "L0", "", fit_xmin, fit_xmax );
  if( sel_fun_sig==   30 ){
    func_tot_dt->ReleaseParameter(4);
  }else if( sel_fun_sig==30000 ){
    func_tot_dt->ReleaseParameter(4);
    func_tot_dt->ReleaseParameter(7);
  }else if( sel_fun_sig==33000 ){
    func_tot_dt->ReleaseParameter(4);
  }else{
    std::cerr << "[ABORT] Wrong fitting function : " << sel_fun_sig << std::endl, abort();
  }
  hist[0]->Fit( func_tot_dt, "L0", "", fit_xmin, fit_xmax );
  func_tot_dt->Draw("LsameS");
  
  TF1* func_bkg_dt = new TF1( "func_bkg_dt", make_func(sel_fun_bkg),xmin,xmax,n_fitfunc_par(sel_fun_bkg) );
  if( sel_fun_bkg==1 ) func_bkg_dt->SetParNames  (           "slope", "offset" );
  else                 func_bkg_dt->SetParNames  ( "second", "slope", "offset" );
  if( sel_fun_tot==31 ){
    if( sel_fun_bkg==1 ) func_bkg_dt->SetParameters( func_tot_dt->GetParameter(7), func_tot_dt->GetParameter(8) );
    else                 func_bkg_dt->SetParameters( func_tot_dt->GetParameter(7), func_tot_dt->GetParameter(8), func_tot_dt->GetParameter(9) );
  }else{
    if( sel_fun_bkg==1 ) func_bkg_dt->SetParameters( func_tot_dt->GetParameter(8), func_tot_dt->GetParameter(9) );
    else                 func_bkg_dt->SetParameters( func_tot_dt->GetParameter(8), func_tot_dt->GetParameter(9), func_tot_dt->GetParameter(10) );
  }
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
  Double_t range   = 0.015;
  Double_t nbkg_d0 = func_bkg_dt->Integral( PDGmass::d0-range, PDGmass::d0+range )/((xmax-xmin)/xbin);
  Double_t nbkg_dp = func_bkg_dt->Integral( PDGmass::dp-range, PDGmass::dp+range )/((xmax-xmin)/xbin);
  Double_t ntot_d0 = func_tot_dt->Integral( PDGmass::d0-range, PDGmass::d0+range )/((xmax-xmin)/xbin);
  Double_t ntot_dp = func_tot_dt->Integral( PDGmass::dp-range, PDGmass::dp+range )/((xmax-xmin)/xbin);
  Double_t nsig_d0 = ntot_d0 - nbkg_d0;
  Double_t nsig_dp = ntot_dp - nbkg_dp;

  std::cout << "[D0] " 
	    << std::setw( 8) << std::right << ntot_d0 << " (tot) = "
	    << std::setw( 8) << std::right << nsig_d0 << " (sig) + "
	    << std::setw( 8) << std::right << nbkg_d0 << " (bkg)" << std::endl;
  std::cout << "[D+] " 
	    << std::setw( 8) << std::right << ntot_dp << " (tot) = "
	    << std::setw( 8) << std::right << nsig_dp << " (sig) + "
	    << std::setw( 8) << std::right << nbkg_dp << " (bkg)" << std::endl;
  if( sel_fun_sig==30 ) std::cout << std::setw(12) << std::right << dec_index(fl_dec)
				  << std::setw( 5) << std::right << fl_dec
				  << std::setw( 6) << std::right << sel_fun_sig
				  << std::setw(15) << std::right << func_tot_dt->GetParameter(4)/func_tot_mc->GetParameter(4)
				  << std::setw(15) << std::right << func_tot_dt->GetParameter(4)/func_tot_mc->GetParameter(4)*sqrt( pow( func_tot_dt->GetParError(4)/func_tot_dt->GetParameter(4), 2 )
																    +pow( func_tot_mc->GetParError(4)/func_tot_mc->GetParameter(4), 2 )
																    )
				  << std::setw(15) << std::right << func_sig_mc->GetParameter(4)
				  << std::setw(15) << std::right << func_sig_mc->GetParError (4)
				  << " HOGE1" << std::endl;
  else if( sel_fun_sig==30000) std::cout << std::setw(12) << std::right << dec_index(fl_dec)
					 << std::setw( 5) << std::right << fl_dec
					 << std::setw( 6) << std::right << sel_fun_sig
					 << std::setw(15) << std::right << func_tot_dt->GetParameter(4)/func_tot_mc->GetParameter(4)
					 << std::setw(15) << std::right << func_tot_dt->GetParameter(4)/func_tot_mc->GetParameter(4)*sqrt( pow( func_tot_dt->GetParError(4)/func_tot_dt->GetParameter(4), 2 )
																	   +pow( func_tot_mc->GetParError(4)/func_tot_mc->GetParameter(4), 2 )
																	   )
					 << std::setw(15) << std::right << func_tot_dt->GetParameter(7)/func_tot_mc->GetParameter(7)
					 << std::setw(15) << std::right << func_tot_dt->GetParameter(7)/func_tot_mc->GetParameter(7)*sqrt( pow( func_tot_dt->GetParError(7)/func_tot_dt->GetParameter(7), 2 )
																	   +pow( func_tot_mc->GetParError(7)/func_tot_mc->GetParameter(7), 2 )
																	   )
					 << std::setw(15) << std::right << func_sig_mc->GetParameter(4)
					 << std::setw(15) << std::right << func_sig_mc->GetParError (4)
					 << std::setw(15) << std::right << func_sig_mc->GetParameter(7)
					 << std::setw(15) << std::right << func_sig_mc->GetParError (7)
					 << " HOGE2" << std::endl;
  //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  TFile outfile( Form("pic/%s_%d.root", brname,fl_dec), "RECREATE" );
  can->Write();
  //TF1* func_sig_save_dt = new TF1( Form("func_sig_dt_%d",fl_dec), make_func(sel_fun_sig),xmin,xmax,n_fitfunc_par(sel_fun_sig) );
  //TF1* func_sig_save_mc = new TF1( Form("func_sig_mc_%d",fl_dec), make_func(sel_fun_sig),xmin,xmax,n_fitfunc_par(sel_fun_sig) );
  TF1* func_sig_save_dt = new TF1( Form("func_sig_dt_%d",fl_dec), make_func(sel_fun_sig),1.70,2.00,n_fitfunc_par(sel_fun_sig) );
  TF1* func_sig_save_mc = new TF1( Form("func_sig_mc_%d",fl_dec), make_func(sel_fun_sig),1.70,2.00,n_fitfunc_par(sel_fun_sig) );
  for( Int_t i=0; i<n_fitfunc_par(sel_fun_sig); i++ ) func_sig_save_dt->SetParameter(i, func_sig_mc->GetParameter(i));
  for( Int_t i=0; i<n_fitfunc_par(sel_fun_sig); i++ ) func_sig_save_mc->SetParameter(i, func_sig_mc->GetParameter(i));
  if( sel_fun_sig==30 ){
    //func_sig_save_dt->SetParameter( 4, func_sig_mc->GetParameter(4) * (func_tot_dt->GetParameter(4)/func_tot_mc->GetParameter(4)) );
    func_sig_save_dt->SetParameter( 4, func_sig_mc->GetParameter(4) *  1.175 ); // SCALING
  }else if( sel_fun_sig==30000 ){
    //func_sig_save_dt->SetParameter( 4, func_sig_mc->GetParameter(4) * (func_tot_dt->GetParameter(4)/func_tot_mc->GetParameter(4)) );
    //func_sig_save_dt->SetParameter( 7, func_sig_mc->GetParameter(7) * (func_tot_dt->GetParameter(7)/func_tot_mc->GetParameter(7)) );
    func_sig_save_dt->SetParameter( 4, func_sig_mc->GetParameter(4) * 1.176 ); // SCALING
    func_sig_save_dt->SetParameter( 7, func_sig_mc->GetParameter(7) * 1.084 ); // SCALING
  }else{
    std::cerr << "[ABORT] Wrong fitting function : " << sel_fun_sig << std::endl, abort();
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

