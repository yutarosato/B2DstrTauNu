#include "scan_significance.h"

const Bool_t   fl_message   = true;
const Bool_t   fl_save      = true; // outfile.eps and outfile.root
const Char_t*  tname        = "h15";
const Char_t*  infile       = "~/dstrtaunu/modules/dstrtaunu/hbk/store/hbk8_merge_cut/gMC_*s0[012345]*.root";
const Double_t scale_factor = 6; // N -> N/scale
const Char_t*  branch       = "atan(cosdll)";
//const Char_t*  branch       = "atan(rm_bdir)";
const Int_t    tag_sig      = 0;
const Int_t    tag_bkg      = 1;
const Char_t*  region_cut   = "eecl<0.4";

const Int_t    xbin       =  64;
//const Int_t    xbin       =  128;
const Double_t xmin       = -1.6;
const Double_t xmax       =  1.6;

// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++      
const Int_t nh = 3;
TH1D** hist;
TH1D** hist_norm;
const Char_t* type_label[nh] = {
  "sig.",
  "norm.",
  "other",
};
const Char_t* c_type [nh] = { 
    "self==1", // sig
    "self==2", // tag
    "self<1", // other
};

// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

void make_eff_pur_sign( TGraph* graph_eff, TGraphErrors* graph_sign, Double_t* summary,
			TH1D* hist_sig, TH1D* hist_bkg ){
  Double_t max_nbcut  = 0;
  Double_t max_eff    = 0;
  Double_t max_purity = 0;
  Double_t max_sign   = 0;
  Double_t max_signE  = 0;
  Double_t max_rej    = 0;
  Double_t max_nsig   = 0;
  Double_t max_nbkg   = 0;
  
  Double_t entry_nsig = hist_sig->Integral();
  Double_t entry_nbkg = hist_bkg->Integral();

  for( Int_t x=0; x<xbin; x++ ){
    Double_t nsig_err  = 0;
    Double_t nbkg_err  = 0;
    //Double_t nsig      = hist_sig->IntegralAndError( x+1, xbin, nsig_err );
    //Double_t nbkg      = hist_bkg->IntegralAndError( x+1, xbin, nbkg_err );
    Double_t nsig      = hist_sig->IntegralAndError( 1, x+1, nsig_err );
    Double_t nbkg      = hist_bkg->IntegralAndError( 1, x+1, nbkg_err );

    if( nsig+nbkg==0 ) continue;

    Double_t eff       = nsig/entry_nsig;
    Double_t purity    = nsig/(nsig+nbkg);
    Double_t sign      = nsig/sqrt(nsig+nbkg);
    Double_t round_sig = nsig==0 ? 0 : sign/nsig - sign*sign*sign/nsig/nsig/2.0;
    Double_t round_bkg = nsig==0 ? 0 : -sign*sign*sign/nsig/nsig/2.0;
    Double_t signE     = sqrt( round_sig*round_sig*nsig_err*nsig_err + round_bkg*round_bkg*nbkg_err*nbkg_err );
    Double_t rej       = (1-nbkg)/entry_nbkg;

    graph_eff ->SetPoint     ( graph_eff ->GetN(),   purity,                       eff   );
    graph_sign->SetPoint     ( graph_sign->GetN(),   hist_sig->GetBinLowEdge(x+1), sign  );
    graph_sign->SetPointError( graph_sign->GetN()-1,                            0, signE );

    if( sign > max_sign ){
      max_nbcut  = hist_sig->GetBinLowEdge(x+1);
      max_eff    = eff;
      max_purity = purity;
      max_sign   = sign;
      max_signE  = signE;
      max_rej    = rej;
      max_nsig   = nsig;
      max_nbkg   = nbkg;
    }
  }
  std::cout << "---------------[sig : specified bkg]----------------" << std::endl
	    << "     NB cut value : " << max_nbcut  << std::endl
	    << "       efficiency : " << max_eff    << std::endl
	    << "           purity : " << max_purity << std::endl
	    << " max significance : " << max_sign   << " +- " << max_signE << std::endl
	    << "  rejection ratio : " << max_rej    << std::endl
	    << " S = " << max_nsig << " ( <- " << entry_nsig << " )" << std::endl
	    << " B = " << max_nbkg << " ( <- " << entry_nbkg << " )" << std::endl;
  summary[0] = max_nbcut;
  summary[1] = max_eff;
  summary[2] = max_purity;
  summary[3] = max_sign;
  summary[4] = max_signE;
  summary[5] = max_rej;
  summary[6] = max_nsig;
  summary[7] = max_nbkg;
  summary[8] = entry_nsig;
  summary[9] = entry_nbkg;

  return;
}

// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

void make_eff_pur_sign( TGraph* graph_eff, TGraphErrors* graph_sign, Double_t* summary,
			TH1D* hist_sig ){
  Double_t max_nbcut  = 0;
  Double_t max_eff    = 0;
  Double_t max_purity = 0;
  Double_t max_sign   = 0;
  Double_t max_signE  = 0;
  Double_t max_rej    = 0;
  Double_t max_nsig   = 0;
  Double_t max_nbkg   = 0;

  Double_t entry_nsig = hist_sig->Integral();
  Double_t entry_nbkg = 0;
  for( Int_t i=0; i<nh; i++ ) entry_nbkg += hist[i]->Integral();
  entry_nbkg -= entry_nsig;
  
  for( Int_t x=0; x<xbin; x++ ){
    Double_t nsig_err = 0;
    Double_t tmp_ntot_err = 0;
    Double_t ntot_err = 0;
    //Double_t nsig     = hist_sig->IntegralAndError( x+1, xbin, nsig_err );
    Double_t nsig     = hist_sig->IntegralAndError( 1, x+1, nsig_err );
    Double_t ntot     = 0;
    for( Int_t i=0; i<nh; i++ ){
      //ntot += hist[i]->IntegralAndError( x+1, xbin, tmp_ntot_err );
      ntot += hist[i]->IntegralAndError( 1, x+1, tmp_ntot_err );
      ntot_err += tmp_ntot_err*tmp_ntot_err;
    }
    ntot_err = sqrt(ntot_err);
    if( ntot==0 ) continue;

    Double_t eff      = nsig/entry_nsig;
    Double_t purity   = nsig/ntot;

    Double_t sign      = nsig/sqrt(ntot);
    Double_t round_sig = nsig==0 ? 0 : sign/nsig - sign*sign*sign/nsig/nsig/2.0;
    Double_t round_tot = nsig==0 ? 0 : -sign*sign*sign/nsig/nsig/2.0;
    Double_t signE     = sqrt( round_sig*round_sig*nsig_err*nsig_err + round_tot*round_tot*ntot_err*ntot_err );
    Double_t rej       = (1-(ntot-nsig))/entry_nbkg;

    graph_eff ->SetPoint     ( graph_eff ->GetN(),   purity,                       eff   );
    graph_sign->SetPoint     ( graph_sign->GetN(),   hist_sig->GetBinLowEdge(x+1), sign  );
    graph_sign->SetPointError( graph_sign->GetN()-1,                            0, signE );

    if( sign > max_sign ){
      max_nbcut  = hist_sig->GetBinLowEdge(x+1);
      max_eff    = eff;
      max_purity = purity;
      max_sign   = sign;
      max_signE  = signE;
      max_rej    = rej;
      max_nsig   = nsig;
      max_nbkg   = ntot-nsig;
    }
  }
  
  std::cout << "-----------------[sig : total bkg]------------------" << std::endl
	    << "     NB cut value : " << max_nbcut  << std::endl
	    << "       efficiency : " << max_eff    << std::endl
	    << "           purity : " << max_purity << std::endl
	    << " max significance : " << max_sign   << " +- " << max_signE << std::endl
	    << "  rejection ratio : " << max_rej    << std::endl
    	    << " S = " << max_nsig << " ( <- " << entry_nsig << " )" << std::endl
	    << " B = " << max_nbkg << " ( <- " << entry_nbkg << " )" << std::endl;

  summary[0] = max_nbcut;
  summary[1] = max_eff;
  summary[2] = max_purity;
  summary[3] = max_sign;
  summary[4] = max_signE;
  summary[5] = max_rej;
  summary[6] = max_nsig;
  summary[7] = max_nbkg;
  summary[8] = entry_nsig;
  summary[9] = entry_nbkg;

  return;
}

// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
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
  std::stringstream sTmp;
  sTmp.str("");
  sTmp.clear();
  sTmp << "(" << region_cut << ")";

  TTree* tree = chain->CopyTree( sTmp.str().c_str() );
  std::cout << " -> " << tree->GetEntries() << " events (after event selection)" << std::endl;

  // ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

  THStack* hs   = new THStack( "significance", Form("significance (%s);%s",region_cut,branch) );
  hist = makeHist( "h", xbin, xmin, xmax, nh );
  TLegend* leg  = new TLegend( 0.75,0.75,0.99,0.99 );
  for( Int_t i=0; i<nh; i++ ){
    tree->Project( Form("h_%d",i), branch, Form("%s", c_type[i]) );
    hist[i]->SetLineColor(i+1);
    hist[i]->SetFillColor(i+1);
    hist[i]->Sumw2();
    hist[i]->Scale(1/scale_factor);
    hs->Add( hist[i] );
    leg->AddEntry( hist[i], type_label[i], "F" );
    std::cout << std::setw(2)  << std::right << i << " : "
	      << std::setw(20) << std::right << type_label[i]                  << " :"
	      << std::setw(5)  << std::right << hist[i]->GetEntries()          << " events("
	      << std::setw(5)  << std::right << hist[i]->GetBinContent(0)      << ", "
	      << std::setw(5)  << std::right << hist[i]->Integral()            << " , "
	      << std::setw(5)  << std::right << hist[i]->GetBinContent(xbin+1) << ")"
	      << std::endl;
  }
  // ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  THStack* hs_norm    = new THStack( "NB", Form("%s (Normalizaed);%s",            branch,branch) );
  THStack* hs_norm_sb = new THStack( "NB", Form("%s (sig : bkg) (Normalizaed);%s",branch,branch) );
  hist_norm = new TH1D*[nh];
  for( Int_t i=0; i<nh; i++ ){
    hist_norm[i] = new TH1D(*hist[i]);
    hist_norm[i]->Scale(1/hist_norm[i]->Integral());
    hist_norm[i]->SetFillColor(0);
    hs_norm->Add( hist_norm[i] );
    if( i==tag_sig || i==tag_bkg ) hs_norm_sb->Add( hist_norm[i] );
    }

  // ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

  TGraph*       g1_eff  = new TGraph();
  TGraph*       g2_eff  = new TGraph();
  TGraphErrors* g1_sign = new TGraphErrors();
  TGraphErrors* g2_sign = new TGraphErrors();
  Double_t      summary1[10]; // 0(branch cut), 1(efficiency), 2(purity), 3(significance), 4(significanceE), 5(rejection ratio), 
  Double_t      summary2[10]; // 6(sig after cut), 7(bkg after cut), 8(sig before cut), 9(bkg before cut)
  make_eff_pur_sign( g1_eff, g1_sign, summary1, hist[0]          ); // efficiency   v.s. purity, significance v.s. branch
  make_eff_pur_sign( g2_eff, g2_sign, summary2, hist[0], hist[1] );

  g1_eff ->SetMarkerStyle(1);
  g1_eff ->SetMarkerColor(2);
  g1_eff ->SetLineColor  (2);
  g1_sign->SetMarkerStyle(1);
  g1_sign->SetMarkerColor(2);
  g1_sign->SetLineColor  (2);
  g2_eff ->SetMarkerStyle(1);
  g2_eff ->SetMarkerColor(3);
  g2_eff ->SetLineColor  (3);
  g2_sign->SetMarkerStyle(1);
  g2_sign->SetMarkerColor(3);
  g2_sign->SetLineColor  (3);

  TMarker* p1_eff  = new TMarker(summary1[2], summary1[1], 28 );
  TMarker* p2_eff  = new TMarker(summary2[2], summary2[1], 28 );
  p1_eff->SetMarkerSize(1.7);
  p2_eff->SetMarkerSize(1.7);

  
  // ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  TCanvas* c1 = Canvas( "c1", "c1", 3, 2 );
  c1->cd(1);
  hs->Draw("no hist");
  leg->Draw();

  c1->cd(2);
  gPad->DrawFrame( 0, 0, 1, 1, "purity v.s. efficiency; purity; efficiency" );
  g1_eff->Draw("PLsame");
  g2_eff->Draw("PLsame");
  p1_eff->Draw();
  p2_eff->Draw();

  TText* tex1 = new TText();
  tex1->SetTextColor(2);
  tex1->SetTextSize(0.04);
  tex1->DrawTextNDC( 0.15,0.90, Form("%s > %.2f : eff = %.2f, purity = %.2f", branch, summary1[0], summary1[1], summary1[2]) );
  tex1->DrawTextNDC( 0.15,0.86, Form("   significance = %.1f (S = %.0f, B = %.0f)", summary1[3], summary1[6], summary1[7] ) );
  TText* tex2 = new TText();
  tex2->SetTextColor(3);
  tex2->SetTextSize(0.04);
  tex2->DrawTextNDC( 0.15,0.82, Form("%s > %.2f : eff = %.2f, purity = %.2f", branch, summary2[0], summary2[1], summary2[2]) );
  tex2->DrawTextNDC( 0.15,0.78, Form("   significance = %.1f (S = %.0f, B = %.0f)", summary2[3], summary2[6], summary2[7] ) );
  
  c1->cd(3);
  TMultiGraph* mg = new TMultiGraph( "significance", Form("significance v.s. %s; %s; significance",branch, branch) );
  mg->Add( g1_sign );
  mg->Add( g2_sign );
  mg->Draw("APL");

  c1->cd(4);
  hs_norm->Draw("no hist nostack");

  c1->cd(5);
  hs_norm_sb->Draw("no hist nostack");
  
  c1->Update();
  if( fl_save ){
    c1->Print( Form("pic/scan_1d_%s.eps",  branch)  );
    c1->Print( Form("pic/scan_1d_%s.root", branch) );
  }
  

  std::cout << "finish" << std::endl;
  if( !gROOT->IsBatch() ) app.Run();
    
  return 0;
}

