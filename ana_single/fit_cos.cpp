
#include "draws_.h"
#include "draws_roofit_.h"
#include "draws_single.h"

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
using namespace RooFit;
const Bool_t fl_line = true;
const Char_t* wbr       = "w1_mc*w1_bf*w2_mc*w2_bf"; // (A+a) * (B+b) = AB + aB + Ab + ab
const Char_t* wbrEstat2 = "pow(w1_mc_estat*w2_mc,2) + pow(w1_mc*w2_mc_estat,2)";
const Char_t* wbrEsyst  = "w1_mc_esyst*w2_mc + w1_mc*w2_mc_esyst";

//const Char_t* selection = "1";
const Char_t* selection = "l1pid>0.90";
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// d mass
const Char_t*  d_brname     = "d1_m";
const Char_t*  d_axisname = "m_{D} [GeV]";
//const Int_t    d_xbin     =  200;
//const Double_t d_xmin = 1.80;
//const Double_t d_xmax = 1.90;
//const Double_t d_xmin     = 1.77;
//const Double_t d_xmax     = 1.92;
//const Int_t    d_xbin     =  300;
const Double_t d_xmin     = 1.72;
const Double_t d_xmax     = 1.98;
const Int_t    d_xbin     =  520;
      Double_t d_xmin_fit = 1.80;
      Double_t d_xmax_fit = 1.90;

// delta m
const Char_t*  dstr_brname   = "dm1";
const Char_t*  dstr_axisname = "#Deltam [GeV]";
      Double_t dstr_xmin     = PDGmass::pip;
      Double_t dstr_th       = PDGmass::pip;
//const Int_t    dstr_xbin     =  220;
//      Double_t dstr_xmax     = 0.150;
const Int_t    dstr_xbin     =  220;
      Double_t dstr_xmax     = 0.152;

// cos
const Char_t*  cos_brname   = "cosdl1";
const Char_t*  cos_axisname = "cos#theta_{B-D*l}";
const Int_t    cos_xbin     =   120;
const Double_t cos_xmin     = -10.0;
const Double_t cos_xmax     =   5.0;
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//Double_t func_deltam_threshold_slowpip( const Double_t x, const Double_t p0, const Double_t p1, const Double_t p2 ){
//Double_t func_deltam_threshold_slowpip( const Double_t x, const Double_t p0, const Double_t p1 ){
Double_t func_deltam_threshold_slowpip( const Double_t x ){
  Double_t p[3];
  //p[0] = p0; // parameter
  //p[1] = p1; // parameter
  //p[2] = p2; // parameter
  Double_t th = PDGmass::pip;
  Double_t f;
  if( x>th ){
    //f = p[0]*pow(x-th, 1/2.0) + p[1]*pow(x-th, 1/4.0) + p[2]*pow(x-th, 1/8.0); // threshold function in delta-M fitting
    //f = p[0]*pow(x-th, 1/2.0) + p[1]*pow(x-th, 1/4.0) + p[2]*pow(x-th, 2.0); // threshold function in delta-M fitting
    //f = p[0]*pow(x-th, 1/2.0) + p[1]*pow(x-th, 1/4.0); // threshold function in delta-M fitting
    f = pow(x-th, 1/2.0); // threshold function in delta-M fitting
  }else{
    f = 0;
  }
  return f;
}

//Double_t func_deltam_threshold_slowpi0( const Double_t x, const Double_t p0, const Double_t p1, const Double_t p2 ){
//Double_t func_deltam_threshold_slowpi0( const Double_t x, const Double_t p0, const Double_t p1 ){
Double_t func_deltam_threshold_slowpi0( const Double_t x ){
  Double_t p[3];
  //p[0] = p0; // parameter
  //p[1] = p1; // parameter
  //p[2] = p2; // parameter
  Double_t th = PDGmass::pi0;
  Double_t f;
  if( x>th ){
    f = pow(x-th, 1/2.0); // threshold function in delta-M fitting
  }else{
    f = 0;
  }
  return f;
}

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
Int_t main( Int_t argc, Char_t** argv ){
  gROOT->SetBatch(true); // tmpppppp
  TApplication app( "app", &argc, argv );
  TStyle* sty = Style(10);
  sty->SetTitleOffset(1.0,"y");
  sty->SetOptStat(0);
  sty->SetLabelSize(0.030,"xyz");
  sty->SetTitleSize(0.045,"xyz");
  sty->SetOptFit(11);
  sty->SetStatW(0.16);
  sty->SetMarkerSize(0.4);
  //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  if( app.Argc()!=3 ) std::cerr << "Wrong input"      << std::endl
				<< " Usage : "        << app.Argv(0)
				<< "(int)fl_dec (int) fl_lep"
				<< std::endl
				<< "fl_lep : 10(e), 1(mu)"
				<< std::endl, abort();
  Int_t fl_dec    = atoi(app.Argv(1));
  Int_t fl_lep    = atoi(app.Argv(2));
  Int_t fl_slowpi = ( nominal_dmass(fl_dec)>1.866 ? 0 : 1 ); // 0(D+pi0), 1(D0pi+)
  if( !fl_slowpi ){
    dstr_xmin  = PDGmass::pi0;
    dstr_th    = PDGmass::pi0;
    dstr_xmax -= 0.005;
  }
  Double_t nominal_deltam = ( fl_slowpi ? PDGmass::dstrp - PDGmass::d0 : PDGmass::dstrp - PDGmass::dp );
  //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  // <Read Data file>
  TChain* c_dt = new TChain(treename);
  std::cout << "[DT] "
    //<< c_dt->Add("~/dstrtaunu/modules/dstrtaunu/hbk_single/through_cut_FitRange/RD.root" ) << " files -> ";
    //<< c_dt->Add("~/dstrtaunu/modules/dstrtaunu/hbk_single/through_cut_FitRange/gMC_*.root") << " files -> ";
	    << c_dt->Add("~/dstrtaunu/ana/manip/tmp/FitRange_1200/gMC_*.root") << " files -> ";
    //<< c_dt->Add("~/dstrtaunu/modules/dstrtaunu/hbk_single/through_cut_loose_D_Dstr/RD.root" ) << " files -> ";
  std::cout << c_dt->GetEntries() << " entries" << std::endl;

  TChain* c_mc = new TChain(treename);
  std::cout << "[MC] "
	    << c_mc->Add("~/dstrtaunu/ana/manip/tmp/FitRange_1200/gMC_*.root") << " files -> ";
  //<< c_mc->Add("~/dstrtaunu/modules/dstrtaunu/hbk_single/through_cut_FitRange/gMC_*.root") << " files -> ";
  //<< c_mc->Add("~/dstrtaunu/modules/dstrtaunu/hbk_single/through_cut_loose_D_Dstr/gMC_*.root") << " files -> ";
  std::cout << c_mc->GetEntries() << " entries" << std::endl;

  //TTree* tree = c_mc->CopyTree( Form("((rm_d1==%d)&&(rm_l1==%d)&&(%s)&&(%s)&&(self==2))", fl_dec,fl_lep,makeCut_dmass_single().c_str(),makeCut_deltam_single().c_str()) );
  TTree* tree = c_mc->CopyTree( Form("((rm_d1==%d)&&(rm_l1==%d)&&(%s)&&(%s)&&(%s)&&(self==2))", fl_dec,fl_lep,selection,
				     makeCut_dmass_single(0.015, 0.015, 0.045, 0.030,0.015, 0.015, 0.036, 0.024).c_str(),
				     makeCut_deltam_single(0.0025, 0.0025, 0.0020, 0.0020).c_str()
				     ) );
  
  
  //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  // <OBSERVABLES>
  RooRealVar* dmass  = new RooRealVar( "d1_m",   "m_{D} [GeV]",       d_xmin,    d_xmax    );
  RooRealVar* deltam = new RooRealVar( "dm1",    "#Deltam [GeV]",     dstr_xmin, dstr_xmax );
  RooRealVar* cosbdl = new RooRealVar( "cosdl1", "cos#theta_{B-D*l}", cos_xmin,  cos_xmax  );
  //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  // <Hist-Data>
  TH1D* d_hist    = new TH1D( "d_hist",    Form("dec(%d)",fl_dec),    d_xbin,    d_xmin,    d_xmax );
  TH1D* dstr_hist = new TH1D( "dstr_hist", Form("dec(%d)",fl_dec), dstr_xbin, dstr_xmin, dstr_xmax );
  TH1D* cos_hist  = new TH1D( "cos_hist",  Form("dec(%d)",fl_dec),  cos_xbin,  cos_xmin,  cos_xmax );
  c_dt->Project( "d_hist",    d_brname,    Form("(rm_d1==%d)&&(rm_l1==%d)&&(%s)      &&(dm1<%f)", fl_dec,fl_lep,selection,                                                                                     dstr_xmax                                                     ) );
  c_dt->Project( "dstr_hist", dstr_brname, Form("(rm_d1==%d)&&(rm_l1==%d)&&(%s)&&(%s)&&(dm1<%f)", fl_dec,fl_lep,selection,makeCut_dmass_single(0.015, 0.015, 0.045, 0.030,0.015, 0.015, 0.036, 0.024).c_str(), dstr_xmax                                                     ) );
  c_dt->Project( "cos_hist",  cos_brname,  Form("(rm_d1==%d)&&(rm_l1==%d)&&(%s)&&(%s)&&(%s)",     fl_dec,fl_lep,selection,makeCut_dmass_single(0.015, 0.015, 0.045, 0.030,0.015, 0.015, 0.036, 0.024).c_str(), makeCut_deltam_single(0.0025, 0.0025, 0.0020, 0.0020).c_str() ) );
  
  d_hist   ->Print();
  dstr_hist->Print();
  cos_hist ->Print();
  RooDataHist* d_roohist    = new RooDataHist( "d_roohist",    "d_roohist",    *dmass,  d_hist    );
  RooDataHist* dstr_roohist = new RooDataHist( "dstr_roohist", "dstr_roohist", *deltam, dstr_hist );
  RooDataHist* cos_roohist  = new RooDataHist( "cos_roohist",  "cos_roohist",  *cosbdl, cos_hist  );

  //TTree* d_tree    = c_dt->CopyTree( Form("(rm_d1==%d)&&(rm_l1==%d)",            fl_dec,fl_lep                                                               ) );
  //TTree* dstr_tree = c_dt->CopyTree( Form("(rm_d1==%d)&&(rm_l1==%d)&&(%s)",      fl_dec,fl_lep,makeCut_dmass_single().c_str()                                ) );
  //TTree* cos_tree  = c_dt->CopyTree( Form("(rm_d1==%d)&&(rm_l1==%d)&&(%s)&&(%s)",fl_dec,fl_lep,makeCut_dmass_single().c_str(),makeCut_deltam_single().c_str()) );
  //RooDataSet* d_roohist    = new RooDataSet( "d_roohist",    "d_roohist",    d_tree,    RooArgSet(*dmass)  );
  //RooDataSet* dstr_roohist = new RooDataSet( "dstr_roohist", "dstr_roohist", dstr_tree, RooArgSet(*deltam) ); 
  //RooDataSet* cos_roohist  = new RooDataSet( "cos_roohist",  "cos_roohist",  cos_tree,  RooArgSet(*cosbdl) );

  //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  TCanvas* can = Canvas( "can", "can", 2, 2 );

  //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  TFile file_dmass ( Form("pdf/dmass/d1_m_%d.root", fl_dec ) );
  TFile file_deltam( Form("pdf/deltam/dm1_%d.root", fl_dec ) );
  if( file_dmass.IsZombie () ) std::cerr << "[ABORT] can not find input-file for dmass-PDF"  << std::endl, abort();
  if( file_deltam.IsZombie() ) std::cerr << "[ABORT] can not find input-file for deltam-PDF" << std::endl, abort();
  TF1* hz_d_func_pdf    = (TF1*)file_dmass.Get ( Form("func_sig_dt_%d",fl_dec) );    hz_d_func_pdf->SetRange(   d_xmin,   d_xmax);
  TF1* hz_dstr_func_pdf = (TF1*)file_deltam.Get( Form("func_sig_dt_%d",fl_dec) ); hz_dstr_func_pdf->SetRange(dstr_xmin,dstr_xmax);
  Int_t sel_fun_d    = ( (fl_dec>999 || nominal_dmass(fl_dec)==PDGmass::dp) ? 30000 : 30 );
  Int_t sel_fun_dstr = 40000;
  TF1*    d_func_pdf = new TF1(    "d_func_sig_dt", make_func(sel_fun_d   ),    d_xmin,   d_xmax, n_fitfunc_par(sel_fun_d   ) );
  TF1* dstr_func_pdf = new TF1( "dstr_func_sig_dt", make_func(sel_fun_dstr), dstr_xmin,dstr_xmax, n_fitfunc_par(sel_fun_dstr) );
  if(    d_func_pdf->GetNpar() !=    hz_d_func_pdf->GetNpar() ) std::cerr << "[ABORT] Wrong # of parameters for D mass " << std::endl, abort();
  if( dstr_func_pdf->GetNpar() != hz_dstr_func_pdf->GetNpar() ) std::cerr << "[ABORT] Wrong # of parameters for Deltam " << std::endl, abort();
  for( Int_t i=0; i<n_fitfunc_par(sel_fun_d   ); i++ )    d_func_pdf->SetParameter(i,    hz_d_func_pdf->GetParameter(i));
  for( Int_t i=0; i<n_fitfunc_par(sel_fun_dstr); i++ ) dstr_func_pdf->SetParameter(i, hz_dstr_func_pdf->GetParameter(i));
  
  d_func_pdf   ->Print();
  dstr_func_pdf->Print();
  //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  can->cd(1);
  if     ( fl_dec==200 || fl_dec==1200 ){ d_xmin_fit = 1.81; d_xmax_fit = 1.94; }
  else if( fl_dec==2                   ){ d_xmin_fit = 1.78; d_xmax_fit = 1.92; }
  else                                  { d_xmin_fit = 1.78; d_xmax_fit = 1.94; }
  // <PDF COMPONENT>
  RooAbsPdf*  d_pdf_sig = bindPdf( d_func_pdf, *dmass );

  RooRealVar*    d_pol_c1  = new RooRealVar ( "c_{1,d}", "c_{1,d}",  0.1, -40, 40 );
  RooRealVar*    d_pol_c2  = new RooRealVar ( "c_{2,d}", "c_{2,d}", -1.0, -30, 30 );
  RooPolynomial* d_pdf_bkg = new RooPolynomial( "d_bkg","d_bkg", *dmass, RooArgList(*d_pol_c1, *d_pol_c2) );
  if( fl_dec!=310 ){
    d_pol_c2->setVal(0.0);
    d_pol_c2->setConstant(kTRUE);
  }
  
  Double_t d_init_nbkg = ( d_hist->GetBinContent(d_hist->FindBin(d_xmin_fit)) + d_hist->GetBinContent(d_hist->FindBin(d_xmax_fit-0.0000001)))*d_xbin*(d_xmax_fit-d_xmin_fit)/(d_xmax-d_xmin)/2.0;
  Double_t d_init_nsig = fabs( d_hist->Integral( d_hist->FindBin(d_xmin_fit), d_hist->FindBin(d_xmax_fit) ) - d_init_nbkg );
  d_init_nbkg = ( d_hist->GetBinContent(d_hist->FindBin(d_xmin_fit)) + d_hist->GetBinContent(d_hist->FindBin(d_xmax_fit-0.0000001)))*d_xbin/2.0;
  if( d_init_nsig <1000 ) d_init_nsig = 1000;

  std::cout << "d_init_nbkg = "   << d_init_nbkg   << ", "
	    << "d_init_nsig = "   << d_init_nsig   << std::endl;
  RooRealVar* d_nsig = new RooRealVar ( "N_{sig,d}", "N_{sig,d}", d_init_nsig, 0.0*d_init_nsig, 10.0*d_init_nsig );
  RooRealVar* d_nbkg = new RooRealVar ( "N_{bkg,d}", "N_{bkg,d}", d_init_nbkg, 0.2*d_init_nbkg, 10.0*d_init_nbkg );
  RooAddPdf*  d_pdf  = new RooAddPdf  ( "d_pdf", "d_pdf", RooArgList(*d_pdf_sig, *d_pdf_bkg), RooArgList(*d_nsig, *d_nbkg) );

  dmass->setRange( "d_fitrange", d_xmin_fit, d_xmax_fit );
  d_pdf_sig->setNormRange("d_fitrange");
  //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  //RooFitResult* d_fit_result = d_pdf->fitTo( *d_roohist, Extended(), Save(true) );
  RooFitResult* d_fit_result = d_pdf->fitTo( *d_roohist, Extended(), Range("d_fitrange"), Save(true) );
  
  RooPlot* d_frame = dmass->frame();
  d_frame->GetXaxis()->CenterTitle();
  d_frame->GetYaxis()->CenterTitle();
  d_frame->SetTitleOffset( 1.00,"x" );
  d_frame->SetTitleOffset( 1.25,"y" );
  d_frame->SetTitle( Form("dec(%d), lep(%d)",fl_dec,fl_lep) );
  d_roohist->plotOn( d_frame, Binning(d_xbin), LineWidth(1) );
  d_pdf->plotOn( d_frame, ProjWData(*d_roohist),                         LineStyle(1), LineColor(3), LineWidth(1) );
  d_pdf->plotOn( d_frame, ProjWData(*d_roohist), Components(*d_pdf_sig), LineStyle(1), LineColor(2), LineWidth(1) );
  d_pdf->plotOn( d_frame, ProjWData(*d_roohist), Components(*d_pdf_bkg), LineStyle(1), LineColor(4), LineWidth(1) );
  d_pdf->paramOn( d_frame, Format("NELU", AutoPrecision(2)), Layout(0.50, 1.00, 1.00), ShowConstants(kFALSE) );
  d_frame->Draw();

  Double_t d_range_L = 0.015;
  Double_t d_range_H = 0.015;
  if( fl_dec > 999 ){
    if( fl_slowpi==1 ){ // D0 decays with pi0
      d_range_L = 0.045;
      d_range_H = 0.030;
    }else{ // D+ decays with pi0
      d_range_L = 0.036;
      d_range_H = 0.024;
    }
  }
  //TLine* d_l_L = new TLine( nominal_dmass(fl_dec)-d_range_L, 0.0, nominal_dmass(fl_dec)-d_range_L, 0.2*d_hist->GetMaximum() );
  //TLine* d_l_H = new TLine( nominal_dmass(fl_dec)+d_range_H, 0.0, nominal_dmass(fl_dec)+d_range_H, 0.2*d_hist->GetMaximum() );
  TLine* d_l_L = new TLine( nominal_eff_dmass(fl_dec)-d_range_L, 0.0, nominal_eff_dmass(fl_dec)-d_range_L, 0.2*d_hist->GetMaximum() );
  TLine* d_l_H = new TLine( nominal_eff_dmass(fl_dec)+d_range_H, 0.0, nominal_eff_dmass(fl_dec)+d_range_H, 0.2*d_hist->GetMaximum() );
  if( fl_line ) d_l_L->Draw("same");
  if( fl_line ) d_l_H->Draw("same");
  
  // calculate # of sig/bkg events in signal d mass region
  dmass->setRange( "d_integralRange_signal", nominal_dmass(fl_dec)-d_range_L, nominal_dmass(fl_dec)+d_range_H );
  Double_t d_nsig_range_signal = (*d_pdf_sig).createIntegral( *dmass, NormSet(*dmass), Range("d_integralRange_signal") )->getVal() * d_nsig->getVal();
  Double_t d_nbkg_range_signal = (*d_pdf_bkg).createIntegral( *dmass, NormSet(*dmass), Range("d_integralRange_signal") )->getVal() * d_nbkg->getVal();
  TText* tex = new TText();
  tex->SetTextColor(2);
  tex->SetTextSize(0.03);
  tex->DrawTextNDC( 0.18,0.30, Form("sig = %.0f",d_nsig_range_signal) );
  tex->DrawTextNDC( 0.18,0.26, Form("bkg = %.0f",d_nbkg_range_signal) );

  //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  can->cd(2);
  // <PDF COMPONENT>
  RooAbsPdf*  dstr_pdf_sig = bindPdf( dstr_func_pdf, *deltam );

  RooRealVar* dstr_th_c1   = new RooRealVar ( "c_{1,dstr}", "c_{1,dstr}",  0.1,  0.0, 8.0 );
  RooRealVar* dstr_th_c2   = new RooRealVar ( "c_{2,dstr}", "c_{2,dstr}",  0.6, -0.3, 5.0 );
  RooRealVar* dstr_th_c3   = new RooRealVar ( "c_{3,dstr}", "c_{3,dstr}",  0.0, -0.3, 2.0 );
  dstr_th_c1->setVal(1.0); dstr_th_c1->setConstant(kTRUE);
  dstr_th_c2->setVal(0.0); dstr_th_c2->setConstant(kTRUE);
  
  //RooAbsPdf*  dstr_pdf_bkg = ( fl_slowpi ? bindPdf( "dstr_bkg", func_deltam_threshold_slowpip, *deltam, *dstr_th_c1, *dstr_th_c2, *dstr_th_c3 ) : bindPdf( "dstr_bkg", func_deltam_threshold_slowpi0, *deltam, *dstr_th_c1, *dstr_th_c2, *dstr_th_c3 ) );
  //RooAbsPdf*  dstr_pdf_bkg = ( fl_slowpi ? bindPdf( "dstr_bkg", func_deltam_threshold_slowpip, *deltam, *dstr_th_c1, *dstr_th_c2 ) : bindPdf( "dstr_bkg", func_deltam_threshold_slowpi0, *deltam, *dstr_th_c1, *dstr_th_c2 ) );
  RooAbsPdf*  dstr_pdf_bkg = ( fl_slowpi ? bindPdf( "dstr_bkg", func_deltam_threshold_slowpip, *deltam ) : bindPdf( "dstr_bkg", func_deltam_threshold_slowpi0, *deltam ) );

  TH1D* dstr_hist_dside = new TH1D( "dstr_hist_dside", Form("dec(%d)",fl_dec), dstr_xbin, dstr_xmin, dstr_xmax );
  if     ( fl_dec==200 || fl_dec==1200 ) c_dt->Project( "dstr_hist_dside", dstr_brname, Form("(rm_d1==%d)&&(rm_l1==%d)&&(%s)&&(%s)",fl_dec,fl_lep,selection,"((1.80<d1_m&&d1_m<1.82)||(1.89<d1_m&&d1_m<1.98))") ); // dmass sideband region
  else if( fl_dec==2                   ) c_dt->Project( "dstr_hist_dside", dstr_brname, Form("(rm_d1==%d)&&(rm_l1==%d)&&(%s)&&(%s)",fl_dec,fl_lep,selection,"((1.72<d1_m&&d1_m<1.82)||(1.89<d1_m&&d1_m<1.92))") ); // dmass sideband region
  else                                   c_dt->Project( "dstr_hist_dside", dstr_brname, Form("(rm_d1==%d)&&(rm_l1==%d)&&(%s)&&(%s)",fl_dec,fl_lep,selection,"((1.72<d1_m&&d1_m<1.82)||(1.89<d1_m&&d1_m<1.98))") ); // dmass sideband region
  RooDataHist* dstr_roohist_dside = new RooDataHist( "dstr_hist_dside", "dstr_hist_dside", *deltam, dstr_hist_dside     );
  RooHistPdf*  dstr_pdf_dside     = new RooHistPdf ( "dstr_pdf_dside",  "dstr_pdf_dside",  *deltam, *dstr_roohist_dside );

  // fix # of d-mass sideband event and estimate initial values for sig/bkg events
  Double_t dstr_init_ndside = d_nbkg_range_signal;
  Double_t dstr_init_nbkg   = 0.40*fabs(dstr_hist->Integral() - dstr_init_ndside);
  Double_t dstr_init_nsig   = 1.00*fabs(dstr_hist->Integral() - dstr_init_ndside);
  std::cout << "dstr_init_nsig = "   << dstr_init_nsig   << ", "
	    << "dstr_init_nbkg = "   << dstr_init_nbkg   << ", "
	    << "dstr_init_ndside = " << dstr_init_ndside << " ("
	    << dstr_roohist_dside->sumEntries() << " : ratio = "
	    << dstr_roohist_dside->sumEntries()/dstr_init_ndside
	    << ")"
	    << std::endl;

  // calculate # of sig/bkg/dmass-side events in signal deltam region.
  RooRealVar* dstr_nsig      = new RooRealVar ( "N_{sig,dstr}",   "N_{sig,dstr}",   dstr_init_nsig, -0.5*dstr_init_nsig,  5.0*dstr_init_nsig );
  RooRealVar* dstr_nbkg      = new RooRealVar ( "N_{bkg,dstr}",   "N_{bkg,dstr}",   dstr_init_nbkg, -5.0*dstr_init_nbkg, 15.0*dstr_init_nbkg );

  RooRealVar*  dstr_ndside             = new RooRealVar ( "N_{dside,dstr}",         "N_{dside,dstr}",          dstr_init_ndside, 0.3*dstr_init_ndside, 2.0*dstr_init_ndside );
  RooRealVar*  dstr_ndside_const_mean  = new RooRealVar( "dstr_ndside_const_mean",  "dstr_ndside_const_mean",  dstr_init_ndside                                             );
  RooRealVar*  dstr_ndside_const_sigma = new RooRealVar( "dstr_ndside_const_sigma", "dstr_ndside_const_sigma", dstr_init_ndside*(d_nbkg->getError()/d_nbkg->getVal())       );
  if( sqrt(dstr_ndside_const_mean->getVal()) > dstr_ndside_const_sigma->getVal() ) dstr_ndside_const_sigma->setVal(sqrt(dstr_ndside_const_mean->getVal()));
  RooGaussian* fconst_dstr_ndside      = new RooGaussian("fconst_dstr_ndside","fconst_dstr_ndside", *dstr_ndside, *dstr_ndside_const_mean, *dstr_ndside_const_sigma         );

  RooAddPdf*  dstr_pdf    = new RooAddPdf( "dstr_pdf", "dstr_pdf", RooArgList(*dstr_pdf_sig, *dstr_pdf_bkg, *dstr_pdf_dside), RooArgList(*dstr_nsig, *dstr_nbkg, *dstr_ndside) );
  //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  //RooFitResult* dstr_fit_result = dstr_pdf->fitTo( *dstr_roohist, Extended(), Save(true) );
  //dstr_nbkg->setConstant(kTRUE); RooFitResult* dstr_fit_result = dstr_pdf->fitTo( *dstr_roohist, Extended(), Range(( fl_slowpi ? PDGmass::pip : PDGmass::pi0 ),dstr_xmax), Save(true) );
  RooFitResult* dstr_fit_result = dstr_pdf->fitTo( *dstr_roohist, Extended(), Range(( fl_slowpi ? PDGmass::pip : PDGmass::pi0 ),dstr_xmax), Save(true), ExternalConstraints(*fconst_dstr_ndside) );
  //dstr_ndside->setConstant(kTRUE); RooFitResult* dstr_fit_result = dstr_pdf->fitTo( *dstr_roohist, Extended(), Range(( fl_slowpi ? PDGmass::pip : PDGmass::pi0 ),dstr_xmax), Save(true) );

  RooPlot* dstr_frame = deltam->frame();
  dstr_frame->GetXaxis()->CenterTitle();
  dstr_frame->GetYaxis()->CenterTitle();
  dstr_frame->SetTitleOffset( 1.00,"x" );
  dstr_frame->SetTitleOffset( 1.25,"y" );
  dstr_frame->SetTitle( Form("dec(%d), lep(%d)",fl_dec,fl_lep) );
  dstr_roohist->plotOn( dstr_frame, Binning(dstr_xbin), LineWidth(1) );
  dstr_pdf->plotOn( dstr_frame, ProjWData(*dstr_roohist),                              LineStyle(1), LineColor(3), LineWidth(1) );
  dstr_pdf->plotOn( dstr_frame, ProjWData(*dstr_roohist), Components(*dstr_pdf_sig),   LineStyle(1), LineColor(2), LineWidth(1) );
  dstr_pdf->plotOn( dstr_frame, ProjWData(*dstr_roohist), Components(*dstr_pdf_bkg),   LineStyle(1), LineColor(4), LineWidth(1) );
  dstr_pdf->plotOn( dstr_frame, ProjWData(*dstr_roohist), Components(*dstr_pdf_dside), LineStyle(1), LineColor(5), LineWidth(1) );
  dstr_pdf->paramOn( dstr_frame, Format("NELU", AutoPrecision(2)), Layout(0.50, 1.00, 1.00), ShowConstants(kFALSE) );
  dstr_frame->Draw();

  Double_t dstr_range   = ( fl_slowpi ? 0.0025 : 0.0020 );
  TLine* dstr_l_L = new TLine( nominal_deltam-dstr_range, 0.0, nominal_deltam-dstr_range, 0.2*dstr_hist->GetMaximum() );
  TLine* dstr_l_H = new TLine( nominal_deltam+dstr_range, 0.0, nominal_deltam+dstr_range, 0.2*dstr_hist->GetMaximum() );
  if( fl_line ) dstr_l_L->Draw("same");
  if( fl_line ) dstr_l_H->Draw("same");

  // calculate # of bkg [ (fakeD*+trueD) and (fakeD)] in signal deltam region
  deltam->setRange( "dstr_integralRange_signal", nominal_deltam-dstr_range, nominal_deltam+dstr_range );
  Double_t dstr_nsig_range_signal   = (*dstr_pdf_sig  ).createIntegral( *deltam, NormSet(*deltam), Range("dstr_integralRange_signal") )->getVal() * dstr_nsig  ->getVal();
  Double_t dstr_nbkg_range_signal   = (*dstr_pdf_bkg  ).createIntegral( *deltam, NormSet(*deltam), Range("dstr_integralRange_signal") )->getVal() * dstr_nbkg  ->getVal();
  Double_t dstr_ndside_range_signal = (*dstr_pdf_dside).createIntegral( *deltam, NormSet(*deltam), Range("dstr_integralRange_signal") )->getVal() * dstr_ndside->getVal();
  Double_t dstr_ratio_range_signal = dstr_nbkg_range_signal/(dstr_ndside_range_signal+dstr_nbkg_range_signal);
  tex->DrawTextNDC( 0.18,0.30, Form("sig = %.0f",  dstr_nsig_range_signal  ) );
  tex->DrawTextNDC( 0.18,0.26, Form("bkg = %.0f",  dstr_nbkg_range_signal  ) );
  tex->DrawTextNDC( 0.18,0.22, Form("dside = %.0f",dstr_ndside_range_signal) );

  // calculate # of bkg [ (fakeD*+trueD) and (fakeD)] in sideband deltam region
  //deltam->setRange( "dstr_integralRange_side", dstr_th, dstr_th==PDGmass::pip ? 0.142 : 0.138 ); // deltam sideband region
  if( fl_slowpi ){ // D0 with slow pi+
    deltam->setRange( "dstr_integralRange_side1", dstr_th, 0.142 ); // deltam sideband region
    deltam->setRange( "dstr_integralRange_side2", 0.148,   0.152 ); // deltam sideband region
  }else{ // D+ with slow pi0
    deltam->setRange( "dstr_integralRange_side1", dstr_th, 0.138 ); // deltam sideband region
    deltam->setRange( "dstr_integralRange_side2", 0.143,   0.147 ); // deltam sideband region    
  }
  
  //Double_t dstr_nbkg_range_side   = (*dstr_pdf_bkg  ).createIntegral( *deltam, NormSet(*deltam), Range("dstr_integralRange_side") )->getVal() * dstr_nbkg  ->getVal();
  //Double_t dstr_ndside_range_side = (*dstr_pdf_dside).createIntegral( *deltam, NormSet(*deltam), Range("dstr_integralRange_side") )->getVal() * dstr_ndside->getVal();
  Double_t dstr_nbkg_range_side   = (*dstr_pdf_bkg  ).createIntegral( *deltam, NormSet(*deltam), Range("dstr_integralRange_side1,dstr_integralRange_side2") )->getVal() * dstr_nbkg  ->getVal();
  Double_t dstr_ndside_range_side = (*dstr_pdf_dside).createIntegral( *deltam, NormSet(*deltam), Range("dstr_integralRange_side1,dstr_integralRange_side2") )->getVal() * dstr_ndside->getVal();
  Double_t dstr_ratio_range_side  = dstr_nbkg_range_side/(dstr_ndside_range_side+dstr_nbkg_range_side);
  std::cout << "dstr_nbkg_range_signal   = " << dstr_nbkg_range_signal     << std::endl
	    << "dstr_ndside_range_signal = " << dstr_ndside_range_signal   << std::endl
	    << "ratio = "                    << dstr_ratio_range_signal    << std::endl
	    << "dstr_nbkg_range_side   = "   << dstr_nbkg_range_side       << std::endl
	    << "dstr_ndside_range_side = "   << dstr_ndside_range_side     << std::endl
	    << "ratio = "                    << dstr_ratio_range_side      << std::endl;

  
  //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  can->cd(3);
  TH1D* cos_hist_sig  = new TH1D( "cos_hist_sig",  Form("dec(%d)",fl_dec), cos_xbin, cos_xmin, cos_xmax );
  TH1D* cos_hist_sig2 = new TH1D( "cos_hist_sig2", Form("dec(%d)",fl_dec), cos_xbin, cos_xmin, cos_xmax );
  c_mc->Project( "cos_hist_sig",  cos_brname, Form("((rm_l1==%d)&&(%s)&&(%s)&&(%s)&&(self==2))",              fl_lep,selection,makeCut_dmass_single().c_str(),makeCut_deltam_single().c_str()       ) ); // cos theta shape : independent to D decay
  c_mc->Project( "cos_hist_sig2", cos_brname, Form("((rm_l1==%d)&&(%s)&&(%s)&&(%s)&&(self==2))&&(rm_d1==%d)", fl_lep,selection,makeCut_dmass_single().c_str(),makeCut_deltam_single().c_str(),fl_dec) ); // cos theta shape for each D decay
  RooDataHist* cos_roohist_sig = new RooDataHist( "cos_hist_sig", "cos_hist_sig", *cosbdl, cos_hist_sig     );
  RooHistPdf*  cos_pdf_sig     = new RooHistPdf ( "cos_pdf_sig",  "cos_pdf_sig",  *cosbdl, *cos_roohist_sig );

  TH1D* cos_hist_bkg = new TH1D( "cos_hist_bkg", Form("dec(%d)",fl_dec), cos_xbin, cos_xmin, cos_xmax );
  c_mc->Project( "cos_hist_bkg", cos_brname, Form("((rm_d1==%d)&&(rm_l1==%d)&&(%s)&&(%s)&&(%s)&&(d1self==1&&dst1self==1&&self!=2))*(%s)", fl_dec,fl_lep,selection,makeCut_dmass_single().c_str(),makeCut_deltam_single().c_str(),wbr) );
  RooDataHist* cos_roohist_bkg = new RooDataHist( "cos_hist_bkg", "cos_hist_bkg", *cosbdl, cos_hist_bkg     );
  RooHistPdf*  cos_pdf_bkg     = new RooHistPdf ( "cos_pdf_bkg",  "cos_pdf_bkg",  *cosbdl, *cos_roohist_bkg );

  TH1D* cos_hist_dside = new TH1D( "cos_hist_dside", Form("dec(%d)",fl_dec), cos_xbin, cos_xmin, cos_xmax );
  if     ( fl_dec==200 || fl_dec==1200 ) c_dt->Project( "cos_hist_dside", cos_brname, Form("(rm_d1==%d)&&(rm_l1==%d)&&(%s)&&(%s)", fl_dec,fl_lep,selection,"((1.80<d1_m&&d1_m<1.82)||(1.89<d1_m&&d1_m<1.98))") ); // dmass sideband region
  else if( fl_dec==2                   ) c_dt->Project( "cos_hist_dside", cos_brname, Form("(rm_d1==%d)&&(rm_l1==%d)&&(%s)&&(%s)", fl_dec,fl_lep,selection,"((1.72<d1_m&&d1_m<1.82)||(1.89<d1_m&&d1_m<1.92))") ); // dmass sideband region
  else                                   c_dt->Project( "cos_hist_dside", cos_brname, Form("(rm_d1==%d)&&(rm_l1==%d)&&(%s)&&(%s)", fl_dec,fl_lep,selection,"((1.72<d1_m&&d1_m<1.82)||(1.89<d1_m&&d1_m<1.98))") ); // dmass sideband region
  RooDataHist* cos_roohist_dside = new RooDataHist( "cos_hist_dside", "cos_hist_dside", *cosbdl, cos_hist_dside     );
  RooHistPdf*  cos_pdf_dside     = new RooHistPdf ( "cos_pdf_dside",  "cos_pdf_dside",  *cosbdl, *cos_roohist_dside );

  TH1D* cos_hist_dstrside = new TH1D( "cos_hist_dstrside", Form("dec(%d)",fl_dec), cos_xbin, cos_xmin, cos_xmax );
  c_dt->Project( "cos_hist_dstrside", cos_brname, Form("(rm_d1==%d)&&(rm_l1==%d)&&(%s)&&(%s)&&(%s)", fl_dec, fl_lep, selection, makeCut_dmass_single().c_str(), dstr_th==PDGmass::pip ? "(dm1<0.142||(0.148<dm1&&dm1<0.152))" : "(dm1<0.138||(0.143<dm1&&dm1<0.147))") ); // deltam sideband region
  RooDataHist* cos_roohist_dstrside = new RooDataHist( "cos_hist_dstrside", "cos_hist_dstrside", *cosbdl, cos_hist_dstrside     );
  RooHistPdf*  cos_pdf_dstrside     = new RooHistPdf ( "cos_pdf_dstrside",  "cos_pdf_dstrside",  *cosbdl, *cos_roohist_dstrside );

  // total : dstr_nbkg_range_signal(fake D*) + dstr_ndside_range_signal(fakeD)
  Double_t cos_init_ndstrside = dstr_nbkg_range_signal*(dstr_nbkg_range_side+dstr_ndside_range_side)/dstr_nbkg_range_side; // (fake D + fake D*)
  Double_t cos_init_ndside    = dstr_ndside_range_signal - dstr_nbkg_range_signal*dstr_ndside_range_side/dstr_nbkg_range_side; // fake D
  Double_t cos_init_nsumside  = cos_init_ndstrside + cos_init_ndside;
  Double_t cos_init_nbkg      = 0.50*fabs( cos_hist->Integral() - cos_init_ndside - cos_init_ndstrside );
  Double_t cos_init_nsig      = 0.60*fabs( cos_hist->Integral() - cos_init_ndside - cos_init_ndstrside );

  TH1D* cos_hist_sumside = new TH1D( "cos_hist_totside", Form("dec(%d)",fl_dec), cos_xbin, cos_xmin, cos_xmax );
  cos_hist_dside   ->Scale( cos_init_ndside   /cos_hist_dside   ->Integral() );
  cos_hist_dstrside->Scale( cos_init_ndstrside/cos_hist_dstrside->Integral() );
  cos_hist_sumside->Add( cos_hist_dside    );
  cos_hist_sumside->Add( cos_hist_dstrside );
  RooDataHist* cos_roohist_sumside = new RooDataHist( "cos_hist_sumside", "cos_hist_sumside", *cosbdl, cos_hist_sumside     );
  RooHistPdf*  cos_pdf_sumside     = new RooHistPdf ( "cos_pdf_sumside",  "cos_pdf_sumside",  *cosbdl, *cos_roohist_sumside );

  std::cout << "cos_init_ndstrside = "
	    << std::setw(15) << std::right << cos_init_ndstrside << " ("
	    << std::setw(15) << std::right << cos_roohist_dstrside->sumEntries()
	    << " : ratio = "
	    << cos_roohist_dstrside->sumEntries()/ cos_init_ndstrside
	    << ")" << std::endl;
  std::cout << "cos_init_ndside    = "
	    << std::setw(15) << std::right << cos_init_ndside    << " ("
	    << std::setw(15) << std::right << cos_roohist_dside->sumEntries()
	    << " : ratio = "
	    << cos_roohist_dside->sumEntries()/ cos_init_ndside
	    << ")" << std::endl;
  if( cos_init_ndside < 0 ) std::cout << "[WARNING] minus cos_init_ndside value : " << cos_init_ndside << std::endl;

  RooRealVar* cos_nsig      = new RooRealVar( "N_{sig,cos}",      "N_{sig,cos}",      cos_init_nsig,  -0.1*cos_init_nsig, 6.0*cos_init_nsig );
  RooRealVar* cos_nbkg      = new RooRealVar( "N_{bkg,cos}",      "N_{bkg,cos}",      cos_init_nbkg,  -2.0*cos_init_nbkg, 6.0*cos_init_nbkg );

  RooRealVar*  cos_ndside             = new RooRealVar( "N_{dside,cos}",          "N_{dside,cos}",          cos_init_ndside, 0.3*cos_init_ndside, 2.0*cos_init_ndside       );
  RooRealVar*  cos_ndside_const_mean  = new RooRealVar( "cos_ndside_const_mean",  "cos_ndside_const_mean",  cos_init_ndside                                                 );
  RooRealVar*  cos_ndside_const_sigma = new RooRealVar( "cos_ndside_const_sigma", "cos_ndside_const_sigma", cos_init_ndside*(dstr_ndside->getError()/dstr_ndside->getVal()) );
  RooGaussian* fconst_cos_ndside      = new RooGaussian("fconst_cos_ndside","fconst_cos_ndside", *cos_ndside, *cos_ndside_const_mean, *cos_ndside_const_sigma               );
  if( sqrt(cos_ndside_const_mean->getVal()) > cos_ndside_const_sigma->getVal() ) cos_ndside_const_sigma->setVal(sqrt(cos_ndside_const_mean->getVal()));

  RooRealVar*  cos_ndstrside             = new RooRealVar( "N_{dstrside,cos}",          "N_{dstrside,cos}",          cos_init_ndstrside, 0.3*cos_init_ndstrside, 2.0*cos_init_ndstrside );
  RooRealVar*  cos_ndstrside_const_mean  = new RooRealVar( "cos_ndstrside_const_mean",  "cos_ndstrside_const_mean",  cos_init_ndstrside                                                 );
  RooRealVar*  cos_ndstrside_const_sigma = new RooRealVar( "cos_ndstrside_const_sigma", "cos_ndstrside_const_sigma", cos_init_ndstrside*(dstr_ndside->getError()/dstr_ndside->getVal()) ); // approximately determined from  dmass sideband's error
  if( sqrt(cos_ndstrside_const_mean->getVal()) > cos_ndstrside_const_sigma->getVal() ) cos_ndstrside_const_sigma->setVal(sqrt(cos_ndstrside_const_mean->getVal()));
  RooGaussian* fconst_cos_ndstrside      = new RooGaussian("fconst_cos_ndstrside","fconst_cos_ndstrside", *cos_ndstrside, *cos_ndstrside_const_mean, *cos_ndstrside_const_sigma         );

  RooRealVar*  cos_nsumside             = new RooRealVar( "N_{side,cos}",          "N_{side,cos}",          cos_init_nsumside, 0.3*cos_init_nsumside, 2.0*cos_init_nsumside );
  RooRealVar*  cos_nsumside_const_mean  = new RooRealVar( "cos_nsumside_const_mean",  "cos_nsumside_const_mean",  cos_init_nsumside                                                );
  RooRealVar*  cos_nsumside_const_sigma = new RooRealVar( "cos_nsumside_const_sigma", "cos_nsumside_const_sigma", cos_init_nsumside*(cos_ndside->getError()/dstr_ndside->getVal()) ); // approximately determined from  dmass sideband's error
  if( sqrt(cos_nsumside_const_mean->getVal()) > cos_nsumside_const_sigma->getVal() ) cos_nsumside_const_sigma->setVal(sqrt(cos_nsumside_const_mean->getVal()));
  RooGaussian* fconst_cos_nsumside      = new RooGaussian("fconst_cos_nsumside","fconst_cos_nsumside", *cos_nsumside, *cos_nsumside_const_mean, *cos_nsumside_const_sigma          );

  //RooAddPdf*  cos_pdf       = new RooAddPdf ( "cos_pdf", "cos_pdf", RooArgList(*cos_pdf_sig, *cos_pdf_bkg, *cos_pdf_dside, *cos_pdf_dstrside), RooArgList(*cos_nsig, *cos_nbkg, *cos_ndside, *cos_ndstrside) );
  RooAddPdf*  cos_pdf       = new RooAddPdf ( "cos_pdf", "cos_pdf", RooArgList(*cos_pdf_sig, *cos_pdf_bkg, *cos_pdf_sumside), RooArgList(*cos_nsig, *cos_nbkg, *cos_nsumside) );
  
  //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  //cos_ndside->setConstant(kTRUE); cos_ndstrside->setConstant(kTRUE); RooFitResult* cos_fit_result = cos_pdf->fitTo( *cos_roohist, Extended(), Save(true) );
  //RooFitResult* cos_fit_result = cos_pdf->fitTo( *cos_roohist, Extended(), ExternalConstraints( RooArgList(*fconst_cos_ndside,*fconst_cos_ndstrside)), Save(true) );
  RooFitResult* cos_fit_result = cos_pdf->fitTo( *cos_roohist, Extended(), ExternalConstraints(*fconst_cos_nsumside), Save(true) );
  //cos_nsumside->setConstant(kTRUE); RooFitResult* cos_fit_result = cos_pdf->fitTo( *cos_roohist, Extended(), Save(true) );

  RooPlot* cos_frame = cosbdl->frame();
  cos_frame->GetXaxis()->CenterTitle();
  cos_frame->GetYaxis()->CenterTitle();
  cos_frame->SetTitleOffset( 1.00,"x" );
  cos_frame->SetTitleOffset( 1.25,"y" );
  cos_frame->SetTitle( Form("dec(%d), lep(%d)",fl_dec,fl_lep) );
  cos_roohist->plotOn( cos_frame, Binning(cos_xbin), LineWidth(1) );
  cos_pdf->plotOn( cos_frame, ProjWData(*cos_roohist),                                LineStyle(1), LineColor(3), LineWidth(1) );
  cos_pdf->plotOn( cos_frame, ProjWData(*cos_roohist), Components(*cos_pdf_sig),      LineStyle(1), LineColor(2), LineWidth(1) );
  cos_pdf->plotOn( cos_frame, ProjWData(*cos_roohist), Components(*cos_pdf_bkg),      LineStyle(1), LineColor(4), LineWidth(1) );
  //cos_pdf->plotOn( cos_frame, ProjWData(*cos_roohist), Components(*cos_pdf_dside   ), LineStyle(7), LineColor(6), LineWidth(1) );
  //cos_pdf->plotOn( cos_frame, ProjWData(*cos_roohist), Components(*cos_pdf_dstrside), LineStyle(7), LineColor(7), LineWidth(1) );
  cos_pdf->plotOn( cos_frame, ProjWData(*cos_roohist), Components(*cos_pdf_sumside   ), LineStyle(1), LineColor(5), LineWidth(1) );
  //cos_pdf->plotOn( cos_frame, ProjWData(*cos_roohist), Components(RooArgSet(*cos_pdf_dside,*cos_pdf_dstrside)), LineStyle(1), LineColor(5), LineWidth(1) );
  cos_pdf->paramOn( cos_frame, Format("NELU", AutoPrecision(2)), Layout(0.50, 1.00, 1.00), ShowConstants(kFALSE) );
  cos_frame->Draw();

  //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  can->cd(4);
  RooPlot* cos_frame2 = cosbdl->frame();
  cos_frame2->GetXaxis()->CenterTitle();
  cos_frame2->GetYaxis()->CenterTitle();
  cos_frame2->SetTitleOffset( 1.00,"x" );
  cos_frame2->SetTitleOffset( 1.25,"y" );
  cos_frame2->SetTitle( Form("dec(%d), lep(%d)",fl_dec,fl_lep) );
  cos_roohist->plotOn( cos_frame2, Binning(cos_xbin), LineWidth(1) );
  cos_pdf->plotOn( cos_frame2, ProjWData(*cos_roohist), Components(*cos_pdf_sig), LineStyle(1), LineColor(2), LineWidth(1) );
  cos_frame2->Draw();

  // comparison with MC
  TFile file_syst_kpi( "pdf/syst/syst_kpi.root" ); if( file_syst_kpi.IsZombie() ) std::cerr << "[ABORT] can not find input-file for syst-kpi" << std::endl, abort();
  TFile file_syst_ks ( "pdf/syst/syst_ks.root"  ); if( file_syst_ks.IsZombie () ) std::cerr << "[ABORT] can not find input-file for syst-ks"  << std::endl, abort();
  TFile file_syst_pi0( "pdf/syst/syst_pi0.root" ); if( file_syst_pi0.IsZombie() ) std::cerr << "[ABORT] can not find input-file for syst-pi0" << std::endl, abort();
  TFile file_syst_lep( "pdf/syst/syst_lep.root" ); if( file_syst_lep.IsZombie() ) std::cerr << "[ABORT] can not find input-file for syst-lep" << std::endl, abort();


  Double_t scale_kpi = 1.0; Double_t scaleE_kpi = 0.0;
  Double_t scale_ks  = 1.0; Double_t scaleE_ks  = 0.0;
  Double_t scale_pi0 = 1.0; Double_t scaleE_pi0 = 0.0;
  Double_t scale_lep = 1.0; Double_t scaleE_lep = 0.0;

  TH1D* hist_syst_kpi = (TH1D*)file_syst_kpi.Get( "kpi_1_2" ); if( hist_syst_kpi->IsZombie() ) std::cerr << "[ABORT] can not find histogram for syst-kpi" << std::endl, abort();
  TH1D* hist_syst_ks  = (TH1D*)file_syst_ks.Get ( "ks_2"    ); if( hist_syst_ks ->IsZombie() ) std::cerr << "[ABORT] can not find histogram for syst-ks"  << std::endl, abort();
  TH1D* hist_syst_pi0 = (TH1D*)file_syst_pi0.Get( "pi0_2"   ); if( hist_syst_pi0->IsZombie() ) std::cerr << "[ABORT] can not find histogram for syst-pi0" << std::endl, abort();
  TH1D* hist_syst_lep = (TH1D*)file_syst_lep.Get( "lep"     ); if( hist_syst_lep->IsZombie() ) std::cerr << "[ABORT] can not find histogram for syst-lep" << std::endl, abort();

  scale_kpi  = hist_syst_kpi->GetBinContent( dec_index(fl_dec)+1 );
  scaleE_kpi = hist_syst_kpi->GetBinError  ( dec_index(fl_dec)+1 );
  scale_ks   = hist_syst_ks ->GetBinContent( dec_index(fl_dec)+1 );
  scaleE_ks  = hist_syst_ks ->GetBinError  ( dec_index(fl_dec)+1 );
  scale_pi0  = hist_syst_pi0->GetBinContent( dec_index(fl_dec)+1 );
  scaleE_pi0 = hist_syst_pi0->GetBinError  ( dec_index(fl_dec)+1 );
  scale_lep  = hist_syst_lep->GetBinContent( fl_lep==1 ? 6 : 2   ); // 1(e,svd1), 2(e,svd2), 3(mu,svd1), 4(mu,e1-39), 5(mu,e41-49), 6(mu,e51-65)
  scaleE_lep = hist_syst_lep->GetBinError  ( fl_lep==1 ? 6 : 2   );


  Float_t w1_mc, w1_bf, w1_mc_estat, w1_mc_esyst;
  Float_t w2_mc, w2_bf, w2_mc_estat, w2_mc_esyst;
  tree->SetBranchAddress( "w1_mc",       &w1_mc       );
  tree->SetBranchAddress( "w1_bf",       &w1_bf       );
  tree->SetBranchAddress( "w1_mc_estat", &w1_mc_estat );
  tree->SetBranchAddress( "w1_mc_esyst", &w1_mc_esyst );
  tree->SetBranchAddress( "w2_mc",       &w2_mc       );
  tree->SetBranchAddress( "w2_bf",       &w2_bf       );
  tree->SetBranchAddress( "w2_mc_estat", &w2_mc_estat );
  tree->SetBranchAddress( "w2_mc_esyst", &w2_mc_esyst );

  Int_t    nevt = 0;
  Double_t syst_model_scale      = 0;
  Double_t syst_model_scaleEstat = 0;
  Double_t syst_model_scaleEsyst = 0;
  while( tree->GetEntry(nevt,0) ){
    syst_model_scale      += w1_bf*w2_bf*w1_mc*w2_mc;
    syst_model_scaleEstat += pow(w1_bf*w2_bf,2) * ( pow(w1_mc_estat*w2_mc,2) + pow(w1_mc*w2_mc_estat,2) );
    syst_model_scaleEsyst +=     w1_bf*w2_bf    * (     w1_mc_esyst*w2_mc    +     w1_mc*w2_mc_esyst    );
    nevt++;
  }
  syst_model_scale      /= (Double_t)nevt;
  syst_model_scaleEstat  = sqrt(syst_model_scaleEstat);
  syst_model_scaleEstat /= (Double_t)nevt;
  syst_model_scaleEsyst /= (Double_t)nevt;
  
  Double_t syst_model_scaleE = sqrt( pow(syst_model_scaleEstat,2) + pow(syst_model_scaleEsyst,2) );

  std::cout << "syst_model_scale = "
	    << syst_model_scale << " +- " << syst_model_scaleE
	    << " ( "
	    << syst_model_scaleEstat << " [stat] +- "
	    << syst_model_scaleEsyst << " [syst] )"
	    << std::endl;
  
  Double_t syst_pid_scale  = scale_kpi*scale_ks*scale_pi0*scale_lep;
  Double_t syst_pid_scaleE = syst_pid_scale*sqrt( pow(scaleE_kpi/scale_kpi,2) +
						  pow(scaleE_ks /scale_ks, 2) +
						  pow(scaleE_pi0/scale_pi0,2) +
						  pow(scaleE_lep/scale_lep,2) +
						  pow(0.0035*(d_dec_K[dec_index(fl_dec)]+d_dec_pi[dec_index(fl_dec)]),2) ); // tracking eff (0.35% per track)
  std::cout << "syst_pid_scale = " << std::setw(12) << std::right << syst_pid_scale << " +- " << std::setw(12) << std::right << syst_pid_scaleE << std::endl
	    << "           kpi : " << std::setw(12) << std::right << scale_kpi      << " +- " << std::setw(12) << std::right << scaleE_kpi      << std::endl
	    << "           ks  : " << std::setw(12) << std::right << scale_ks       << " +- " << std::setw(12) << std::right << scaleE_ks       << std::endl
	    << "           pi0 : " << std::setw(12) << std::right << scale_pi0      << " +- " << std::setw(12) << std::right << scaleE_pi0      << std::endl
	    << "           lep : " << std::setw(12) << std::right << scale_lep      << " +- " << std::setw(12) << std::right << scaleE_lep      << std::endl;


  Double_t syst_tot_scale  = syst_model_scale * syst_pid_scale;
  Double_t syst_tot_scaleE = syst_tot_scale* sqrt( pow(syst_model_scaleE/syst_model_scale,2) + pow(syst_pid_scaleE/syst_pid_scale,2) );

  std::cout << "syst_tot_scale = "
	    << syst_tot_scale << " +- " << syst_tot_scaleE
	    << std::endl;


  Double_t nsig_mc  = syst_tot_scale*cos_hist_sig2->Integral();
  Double_t nsig_mcE = syst_tot_scale*cos_hist_sig2->Integral()*sqrt( 1/cos_hist_sig2->Integral() + pow(syst_tot_scaleE/syst_tot_scale,2) );
  std::cout << "nsig(mc expected) = " << nsig_mc << " +- " << nsig_mcE << std::endl;


  //cos_hist_sig2->Sumw2();  //  DO NOT USE
  for( Int_t ix=0; ix< cos_xbin; ix ++ ){
    cos_hist_sig2->SetBinError( ix+1, sqrt( pow(cos_hist_sig2->GetBinError  (ix+1)*syst_tot_scale, 2) +
					    pow(cos_hist_sig2->GetBinContent(ix+1)*syst_tot_scaleE,2)
					    ) );
  }
  cos_hist_sig2->Scale( syst_tot_scale );

  cos_hist_sig2->SetLineColor  (3);
  cos_hist_sig2->SetMarkerColor(3);

  cos_hist_sig2->Draw("Esame"); // mc


  Double_t nsig_dt  = cos_nsig->getVal();
  Double_t nsig_dtE = cos_nsig->getError();
  Double_t R_nsig   = nsig_dt/nsig_mc; // data/mc
  Double_t R_nsigE  = R_nsig*sqrt( pow(nsig_dtE/nsig_dt,2) + pow(nsig_mcE/nsig_mc,2) );
  tex->DrawTextNDC( 0.18,0.85, Form("sig( MC  ) = %.0f +- %.0f",  nsig_mc, nsig_mcE) );
  tex->DrawTextNDC( 0.18,0.81, Form("sig(Data ) = %.0f +- %.0f",  nsig_dt, nsig_dtE) );
  tex->DrawTextNDC( 0.18,0.77, Form("R(Data/MC) = %.3f +- %.3f",  R_nsig,  R_nsigE ) );

  cosbdl->setRange( "SNestimateregion", -1.0, 1.0 );
  Double_t SN_total = (*cos_pdf    ).createIntegral( *cosbdl, NormSet(*cosbdl), Range("SNestimateregion") )->getVal() * ( cos_nsig->getVal() + cos_nbkg->getVal() + cos_nsumside->getVal() );
  Double_t SN_sig   = (*cos_pdf_sig).createIntegral( *cosbdl, NormSet(*cosbdl), Range("SNestimateregion") )->getVal() * ( cos_nsig->getVal() );
  Double_t SN_bkg   = SN_total - SN_bkg;
  
  std::cout << std::setw(12) << std::right << dec_index(fl_dec)
	    << std::setw(12) << std::right << fl_dec
	    << std::setw(12) << std::right << fl_lep
	    << std::setw(12) << std::right << R_nsig
	    << std::setw(12) << std::right << R_nsigE
	    << std::setw(12) << std::right << nsig_dt
	    << std::setw(12) << std::right << nsig_dtE
	    << std::setw(12) << std::right << nsig_mc
	    << std::setw(12) << std::right << nsig_mcE;
  std::cout << std::setw(12) << std::right << SN_sig/SN_total
	    << std::setw(12) << std::right << SN_sig
	    << std::setw(12) << std::right << SN_bkg;
  if( fl_lep==10 ) std::cout << " HOGEEE";
  else             std::cout << " HOGEMU";
  std::cout << std::endl;


  //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  d_fit_result   ->Print("v");
  dstr_fit_result->Print("v");
  cos_fit_result ->Print("v");
  //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  can->Update();
  can->Print( Form("pic/%s_%d_%d.ps", cos_brname,fl_dec,fl_lep) ); 
  std::cout << "finish" << std::endl;
  if( !gROOT->IsBatch() ) app.Run();
  return 0;
}

