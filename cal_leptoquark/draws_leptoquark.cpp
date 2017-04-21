#include "draws_.h"
#include "draws_leptoquark.h"

///* // for LQ
const Int_t    np   =    60; // # of scan point
const Double_t xmin = -0.20;
const Double_t xmax =  0.40;
//*/
/* // for each operators
const Int_t    np   =   500; // # of scan point
//const Double_t xmin = -5.00;
//const Double_t xmax =  5.00;
*/
const Int_t    nt   =   500; // # of random number for error band
TGraphErrors* makeRdstr_LQ(
			   Double_t rho_A1_2, Double_t a_3, Double_t R11, Double_t R21, Double_t mbPmc, Double_t mbMmc,
			   Double_t factor_Re_CS1, Double_t factor_Im_CS1, Double_t factor_Re_CS2, Double_t factor_Im_CS2,
			   Double_t factor_Re_CV1, Double_t factor_Im_CV1, Double_t factor_Re_CV2, Double_t factor_Im_CV2,
			   Double_t factor_Re_CT,  Double_t factor_Im_CT
){
  TGraphErrors* g = new TGraphErrors();
  for( Int_t ip=0; ip<np+1; ip++ ){
    Double_t x = xmin + ip*(xmax-xmin)/(Double_t)np;
    Double_t f = cal_rdst_full( rho_A1_2, a_3, R11, R21, mbPmc, mbMmc,
				x*factor_Re_CS1, x*factor_Im_CS1, x*factor_Re_CS2, x*factor_Im_CS2,
				x*factor_Re_CV1, x*factor_Im_CV1, x*factor_Re_CV2, x*factor_Im_CV2,
				x*factor_Re_CT,  x*factor_Im_CT
				);
    g->SetPoint( g->GetN(), x, f );
    //std::cout << x << " : " << f << std::endl;
  }
  g->SetTitle( Form("CS1(%.2f,%.2f) CS2(%.2f,%.2f) CV1(%.2f,%.2f) CV2(%.2f,%.2f) CT(%.2f,%.2f)",
		    factor_Re_CS1, factor_Im_CS1,
		    factor_Re_CS2, factor_Im_CS2,
		    factor_Re_CV1, factor_Im_CV1,
		    factor_Re_CV2, factor_Im_CV2,
		    factor_Re_CT,  factor_Im_CT
		    )
	       );
  g->GetXaxis()->SetTitle("Parameter");
  g->GetYaxis()->SetTitle("R(D*)");
  return g;
}

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

TGraphErrors* makeRdstr_LQ(
			   Double_t rho_A1_2,   Double_t a_3,   Double_t R11,   Double_t R21,   Double_t mbPmc,   Double_t mbMmc,
			   Double_t rho_A1_2_E, Double_t a_3_E, Double_t R11_E, Double_t R21_E, Double_t mbPmc_E, Double_t mbMmc_E,
			   Double_t factor_Re_CS1, Double_t factor_Im_CS1, Double_t factor_Re_CS2, Double_t factor_Im_CS2,
			   Double_t factor_Re_CV1, Double_t factor_Im_CV1, Double_t factor_Re_CV2, Double_t factor_Im_CV2,
			   Double_t factor_Re_CT,  Double_t factor_Im_CT
			   ){
  TGraphErrors* g = new TGraphErrors();
  TCanvas* tmpcan = Canvas( "tmpcan", "tmpcan" );

  tmpcan->Draw();

  for( Int_t ip=0; ip<np+1; ip++ ){
    Double_t x = xmin + ip*(xmax-xmin)/(Double_t)np;
    Double_t f = cal_rdst_full( rho_A1_2, a_3, R11, R21, mbPmc, mbMmc,
				x*factor_Re_CS1, x*factor_Im_CS1, x*factor_Re_CS2, x*factor_Im_CS2,
				x*factor_Re_CV1, x*factor_Im_CV1, x*factor_Re_CV2, x*factor_Im_CV2,
				x*factor_Re_CT,  x*factor_Im_CT
				);

    TH1D* tmphist = new TH1D("tmphist","tmphist", 100, 0, 0 );
    for( Int_t it=0; it<nt; it++ ){
      Double_t tmp_rho_A1_2 = rho_A1_2 + gRandom->Gaus( 0.0, rho_A1_2_E );
      //Double_t tmp_a_3      = a_3      + gRandom->Gaus( 0.0, a_3_E      );
      Double_t tmp_a_3      = a_3      + gRandom->Uniform( -a_3_E, a_3_E );
      Double_t tmp_R11      = R11      + gRandom->Gaus( 0.0, R11_E      );
      Double_t tmp_R21      = R21      + gRandom->Gaus( 0.0, R21_E      );
      Double_t tmp_mbPmc    = mbPmc    + gRandom->Gaus( 0.0, mbPmc_E    );
      Double_t tmp_mbMmc    = mbMmc    + gRandom->Gaus( 0.0, mbMmc_E    );
      Double_t tmpf = cal_rdst_full( tmp_rho_A1_2, tmp_a_3, tmp_R11, tmp_R21, tmp_mbPmc, tmp_mbMmc,
				     x*factor_Re_CS1, x*factor_Im_CS1, x*factor_Re_CS2, x*factor_Im_CS2,
				     x*factor_Re_CV1, x*factor_Im_CV1, x*factor_Re_CV2, x*factor_Im_CV2,
				     x*factor_Re_CT,  x*factor_Im_CT
				     );
      tmphist->Fill( tmpf );
    }
    tmphist->Fit("gaus","Q");
    Double_t err = tmphist->GetFunction("gaus")->GetParameter(2);
    g->SetPoint     ( g->GetN(),     x, f   );
    g->SetPointError( g->GetN()-1, 0.0, err );

    //std::cout << std::setw(10) << std::right << x   << " : "
    //<< std::setw(10) << std::right << f   << " +- "
    //<< std::setw(10) << std::right << err << std::endl;

    /* for just checking
    if( ip==0 || ip==nt-1 ){
      tmphist->DrawCopy();
      tmpcan->Update();
      tmpcan->WaitPrimitive();
    }
    */
    
    delete tmphist;
  }
  g->SetTitle( Form("CS1(%.2f,%.2f) CS2(%.2f,%.2f) CV1(%.2f,%.2f) CV2(%.2f,%.2f) CT(%.2f,%.2f)",
		    factor_Re_CS1, factor_Im_CS1,
		    factor_Re_CS2, factor_Im_CS2,
		    factor_Re_CV1, factor_Im_CV1,
		    factor_Re_CV2, factor_Im_CV2,
		    factor_Re_CT,  factor_Im_CT
		    )
	       );
  g->GetXaxis()->SetTitle("Parameter");
  g->GetYaxis()->SetTitle("R(D*)");

  delete tmpcan;

  return g;
}

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

TGraph* makeBand( TGraphErrors* g, Int_t col ){
  TGraph* band = new TGraph();
  band->SetFillColor(col);
  for( Int_t ip=0;           ip<g->GetN(); ip++ ) band->SetPoint( band->GetN(), g->GetX()[ip], ( g->GetEY()[ip] < 0.10 ? g->GetY()[ip] + g->GetEY()[ip] : g->GetY()[ip] + 0.10 ) );
  for( Int_t ip=g->GetN()-1; ip>=0;        ip-- ) band->SetPoint( band->GetN(), g->GetX()[ip], ( g->GetEY()[ip] < 0.10 ? g->GetY()[ip] - g->GetEY()[ip] : g->GetY()[ip] + 0.10 ) );

  for( Int_t ip=0; ip<g->GetN(); ip++ ) g->SetPointError( ip, 0.0, 0.0 );

  band->GetXaxis()->SetTitle("Parameter");
  band->GetYaxis()->SetTitle("R(D*)");

  return band;
}

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

const Bool_t fl_plot_exp = true; // plot our result ?
Int_t main( Int_t argc, Char_t** argv ){
  //gROOT->SetBatch(true); // tmpppppp
  TApplication app( "app", &argc, argv );
  TStyle* sty = Style(1);
  sty->SetTitleSize(0.05,"xy");
  sty->SetTitleOffset(1.1,"xy");
  sty->SetLineWidth(2);

  //unsigned int seed = time(NULL);
  unsigned int seed = 10000;
  gRandom->SetSeed( seed );
  //++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  // form factor parameters
  const Int_t npar_ff = 6;
  //Double_t FF  [npar_ff] = { 1.207,    1.0, 1.403, 0.854,   6.2, 3.45 }; // used by Sakaki-kun // tmpppppp
  //Double_t FF_E[npar_ff] = { 0.026,    1.0, 0.033, 0.020,   0.4, 0.05 }; // used by Sakaki-kun // tmpppppp
  // quark masses at the m_b scale taken from PRD77, 113016 (2008)
  // m_b = 4.20+/-0.07 GeV/c^2, m_c = 0.901+0.111-0.113 GeV/c^2
  Double_t FF  [npar_ff] = { 1.207,    1.0, 1.403, 0.854,   5.101, 3.299 }; // used in EvtGen
  Double_t FF_E[npar_ff] = { 0.026,    1.0, 0.033, 0.020,   0.133, 0.133 }; // used in EvtGen
  
  Double_t rho_A1_2 = FF[0]; Double_t rho_A1_2_E = FF_E[0];
  Double_t a_3      = FF[1]; Double_t a_3_E      = FF_E[1];
  Double_t R11      = FF[2]; Double_t R11_E      = FF_E[2];
  Double_t R21      = FF[3]; Double_t R21_E      = FF_E[3];
  Double_t mbPmc    = FF[4]; Double_t mbPmc_E    = FF_E[4];
  Double_t mbMmc    = FF[5]; Double_t mbMmc_E    = FF_E[5];

  //++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  //                                                                         [  CS1 ]   [  CS2 ]  [  CV1 ]  [  CV2 ]  [  CT  ]
  //TGraphErrors* g_78p = makeRdstr_LQ( rho_A1_2, a_3, R11, R21, mbPmc, mbMmc, 0.0, 0.0,  7.8, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0 );
  //TGraphErrors* g_78m = makeRdstr_LQ( rho_A1_2, a_3, R11, R21, mbPmc, mbMmc, 0.0, 0.0, -7.8, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0 );

  //                                                                                                                            [  CS1 ]   [  CS2 ]  [  CV1 ]  [  CV2 ]  [  CT  ]
  TGraphErrors* g_78p = makeRdstr_LQ( rho_A1_2, a_3, R11, R21, mbPmc, mbMmc, rho_A1_2_E, a_3_E, R11_E, R21_E, mbPmc_E, mbMmc_E, 0.0, 0.0,  7.8, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0 );
  TGraphErrors* g_78m = makeRdstr_LQ( rho_A1_2, a_3, R11, R21, mbPmc, mbMmc, rho_A1_2_E, a_3_E, R11_E, R21_E, mbPmc_E, mbMmc_E, 0.0, 0.0, -7.8, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0 );
  TGraphErrors* g_S1  = makeRdstr_LQ( rho_A1_2, a_3, R11, R21, mbPmc, mbMmc, rho_A1_2_E, a_3_E, R11_E, R21_E, mbPmc_E, mbMmc_E, 1.0, 0.0,  0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0 );
  TGraphErrors* g_S2  = makeRdstr_LQ( rho_A1_2, a_3, R11, R21, mbPmc, mbMmc, rho_A1_2_E, a_3_E, R11_E, R21_E, mbPmc_E, mbMmc_E, 0.0, 0.0,  1.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0 );
  TGraphErrors* g_V1  = makeRdstr_LQ( rho_A1_2, a_3, R11, R21, mbPmc, mbMmc, rho_A1_2_E, a_3_E, R11_E, R21_E, mbPmc_E, mbMmc_E, 0.0, 0.0,  0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 0.0 );
  TGraphErrors* g_V2  = makeRdstr_LQ( rho_A1_2, a_3, R11, R21, mbPmc, mbMmc, rho_A1_2_E, a_3_E, R11_E, R21_E, mbPmc_E, mbMmc_E, 0.0, 0.0,  0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0 );
  TGraphErrors* g_T   = makeRdstr_LQ( rho_A1_2, a_3, R11, R21, mbPmc, mbMmc, rho_A1_2_E, a_3_E, R11_E, R21_E, mbPmc_E, mbMmc_E, 0.0, 0.0,  0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0 );

  g_78p->SetLineColor(2);
  g_78m->SetLineColor(3);

  g_S1->SetLineColor(11); g_S1->SetLineWidth(1);
  g_S2->SetLineColor(12); g_S2->SetLineWidth(1);
  g_V1->SetLineColor( 3); g_V1->SetLineWidth(1);
  g_V2->SetLineColor(16); g_V2->SetLineWidth(1);
  g_T ->SetLineColor(14); g_T ->SetLineWidth(1);



  TGraph* g_78p_band = makeBand( g_78p, 13 ); // light red
  TGraph* g_78m_band = makeBand( g_78m, 15 ); // very light blue

  TGraph* g_S1_band = makeBand( g_S1, 11 ); // gray
  TGraph* g_S2_band = makeBand( g_S2, 12 ); // light purple
  TGraph* g_V1_band = makeBand( g_V1,  3 ); // blue 
  TGraph* g_V2_band = makeBand( g_V2, 16 ); // light green
  TGraph* g_T_band  = makeBand( g_T,  14 ); // light orange


  //++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  // < OUR RESULTS >
  TLine*  rl  = new TLine( xmin, 0.302, xmax, 0.302 );
  rl->SetLineStyle(2);
  
  TGraph* rg  = new TGraph();
  rg->SetPoint(0, xmin, 0.302 - sqrt(pow(0.030,2)+pow(0.011,2)) );
  rg->SetPoint(1, xmax, 0.302 - sqrt(pow(0.030,2)+pow(0.011,2)) );
  rg->SetPoint(2, xmax, 0.302 + sqrt(pow(0.030,2)+pow(0.011,2)) );
  rg->SetPoint(3, xmin, 0.302 + sqrt(pow(0.030,2)+pow(0.011,2)) );
  rg->SetFillColor(9);

  //++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  TLegend* leg1  = new TLegend( 0.35,0.65,0.70,0.88 );
  if( fl_plot_exp ) leg1->AddEntry( rg, "Exp.", "F" );
  leg1->AddEntry( g_78p_band, "C_{S2} = +7.8 C_{T} ", "F" );
  leg1->AddEntry( g_78m_band, "C_{S2} = -7.8 C_{T} ", "F" );

  //TLegend* leg2  = new TLegend( 0.75,0.15,0.88,0.40 );
  TLegend* leg2  = new TLegend( 0.35,0.65,0.50,0.88 );
  if( fl_plot_exp ) leg2->AddEntry( rg, "Exp.", "F" );
  leg2->AddEntry( g_S1_band, "C_{S1}", "F" );
  leg2->AddEntry( g_S2_band, "C_{S2}", "F" );
  leg2->AddEntry( g_V1_band, "C_{V1}", "F" );
  leg2->AddEntry( g_V2_band, "C_{V2}", "F" );
  leg2->AddEntry( g_T_band,  "C_{T}",  "F" );

  //++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  TCanvas* can = Canvas( "can","can", 2,1 );
  can->Draw();

  can->cd(1);
  TMultiGraph* mg1 = new TMultiGraph();
  mg1->SetTitle( "R(D*) in Leptoquark Model;Parameter (C_{T});R(D*)" );
  if( fl_plot_exp ) mg1->Add( rg, "F" );
  mg1->Add( g_78p_band, "F" );
  mg1->Add( g_78m_band, "F" );
  mg1->Add( g_78p,      "L" );
  mg1->Add( g_78m,      "L" );
  mg1->Draw("A");
  mg1->GetXaxis()->SetLimits( xmin, xmax );
  mg1->SetMinimum( 0.0 );
  mg1->Draw("A");
  if( fl_plot_exp ) rl->Draw("Lsame");
  leg1->Draw();

  can->cd(2);
  TMultiGraph* mg2 = new TMultiGraph();
  mg2->SetTitle( "R(D*) with each operators;Parameter (C_{X});R(D*)" );
  if( fl_plot_exp ) mg2->Add( rg, "F" );
  mg2->Add( g_S1_band, "F" );
  mg2->Add( g_S2_band, "F" );
  mg2->Add( g_V1_band, "F" );
  mg2->Add( g_V2_band, "F" );
  mg2->Add( g_T_band,  "F" );
  mg2->Add( g_S1,      "L" );
  mg2->Add( g_S2,      "L" );
  mg2->Add( g_V1,      "L" );
  mg2->Add( g_V2,      "L" );
  mg2->Add( g_T,       "L" );
  mg2->Draw("A");
  mg2->GetXaxis()->SetLimits( xmin, xmax );
  mg2->SetMinimum( 0.1 );
  mg2->SetMaximum( 0.5 );
  mg2->Draw("A");
  if( fl_plot_exp ) rl->Draw("Lsame");
  leg2->Draw();


  can->Update();
  can->Print("pic/draws_LQ.eps");

  std::cout << "finish" << std::endl;
  if( !gROOT->IsBatch() ) app.Run();

 return 0;
}
