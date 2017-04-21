#include "draws_.h"
#include "draws_npcurve_.h"

const Int_t   smpoint  = 3;
const Char_t* model    = "R_{2}-LQ";
const Char_t* param    = "C_{T}";
const Char_t* unit     = "";
const Char_t* filename = "R2LQ";
const Double_t xmin       = -0.150;
const Double_t xmax       =  0.400;
const Double_t ymin_eff   =  0.85;
const Double_t ymax_eff   =  1.20;
const Double_t ymin_rdstr =  0.10;
const Double_t ymax_rdstr =  0.65;

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Int_t main( Int_t argc, Char_t** argv ){
  //gROOT->SetBatch(true); // tmpppppp
  TApplication app( "app", &argc, argv );
  gStyle->SetOptStat(0);
  gStyle->SetPadBottomMargin(0.15);
  gStyle->SetPadLeftMargin  (0.15);
  gStyle->SetTitleOffset(1.1,"x");
  gStyle->SetTitleOffset(1.1,"y");
  gStyle->SetTitleSize(0.055,"xyz");

  //unsigned int seed = time(NULL);
  unsigned int seed = 10000;
  gRandom->SetSeed( seed );

  //++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  TGraphErrors** g           = new TGraphErrors*[ng];
  TGraph**       g_band_stat = new TGraph*      [ng];
  TGraph**       g_band_tot  = new TGraph*      [ng];
  for( Int_t ig=0; ig<ng; ig++ ){
    g[ig] = new TGraphErrors( Form("dat/tmp_%s_lep%d.dat",filename,fl_lep[ig]), "%lg %lg %lg");
    g_band_stat[ig] = makeBand( g[ig], 5 );
    AddSystematic( g[ig], syst[ig] );
    g_band_tot[ig] = makeBand( g[ig], kOrange-0 );
    for( Int_t ip=0; ip<g[ig]->GetN(); ip++ ) g[ig]->SetPointError( ip, 0.0, 0.0 );
    g[ig]->SetMarkerStyle(20);
    g[ig]->SetMarkerSize(0.6);
    g[ig]->SetLineColor  (2);
    g[ig]->SetMarkerColor(2);
    g[ig]->SetLineWidth(2);
    //g          [ig]->Print();
    //g_band_stat[ig]->Print();
    //g_band_tot [ig]->Print();
  }

  //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  //TLine* smline = new TLine( xmin, 0.252, xmax, 0.252 );
  TLine* smline = new TLine( xmin, 0.252703, xmax, 0.252703 );
  smline->SetLineColor(4);
  smline->SetLineStyle(2);
  smline->SetLineWidth(1);

  TLine** expline = new TLine*[ng];
  for( Int_t ig=0; ig<ng; ig++ ){
    expline[ig] = new TLine( xmin, g[ig]->GetY()[smpoint], xmax, g[ig]->GetY()[smpoint] );
    expline[ig]->SetLineColor(2);
    expline[ig]->SetLineStyle(2);
  }

  //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
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

  /* just a test
  std::cout << cal_rdst_full( rho_A1_2, a_3, R11, R21, mbPmc, mbMmc, 0.0, 0.0,  0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0 ) << std::endl; // tmppppp
  Double_t taumass = 1.77682; // GeV
  Double_t bmass   = 4.20; // m_b(MSbar) = 4.20 +/- 0.07 GeV
  Double_t cmass   = 0.901; // m_c(MSbar) = 0.901 +0.111/-0.113 GeV
  Double_t Hpmass  = 3.5;
  Double_t tanb    = 2.5;
  Double_t cs1 = -taumass*bmass*pow( tanb/Hpmass, 2 );
  Double_t cs2 = -taumass*cmass/pow(Hpmass,2);
  printf("      SM    = %.6f\n", cal_rdst_full( rho_A1_2, a_3, R11, R21, mbPmc, mbMmc, 0.0, 0.0,  0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0 ) );
  printf("2HDM(CS2=0) = %.6f\n", cal_rdst_full( rho_A1_2, a_3, R11, R21, mbPmc, mbMmc, cs1, 0.0,  0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0 ) );
  printf("2HDM(full)  = %.6f\n", cal_rdst_full( rho_A1_2, a_3, R11, R21, mbPmc, mbMmc, cs1, 0.0,  cs2, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0 ) );
  abort();
  */
  //                                                                                                                            [  CS1 ]   [  CS2 ]  [  CV1 ]  [  CV2 ]  [  CT  ]
  TGraphErrors* g_78p = makeRdstr_LQ( rho_A1_2, a_3, R11, R21, mbPmc, mbMmc, rho_A1_2_E, a_3_E, R11_E, R21_E, mbPmc_E, mbMmc_E, 0.0, 0.0,  7.8, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0 ); // R2-LQ
  g_78p->SetLineColor(4);
  g_78p->SetLineWidth(2);
  TGraph* g_78p_band  = makeBand( g_78p, 7 );
  TGraph* g_78p_band2 = makeBand( g_78p, 7 );
  g_78p_band2->SetFillColor(1);
  g_78p_band2->SetFillStyle(3005);
  
  for( Int_t ip=0; ip<g_78p_band->GetN()/2; ip++ ) g_78p->SetPointError( ip, 0.0, 0.0 );

  //                                                                                                                            [  CS1 ]   [  CS2 ]  [  CV1 ]  [  CV2 ]  [  CT  ]
  //TGraphErrors* g_78m = makeRdstr_LQ( rho_A1_2, a_3, R11, R21, mbPmc, mbMmc, rho_A1_2_E, a_3_E, R11_E, R21_E, mbPmc_E, mbMmc_E, 0.0, 0.0, -7.8, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0 ); // L1-LQ
  //g_78m->SetLineColor(4);
  //g_78m->SetLineWidth(2);
  //TGraph* g_78m_band = makeBand( g_78m, 7 );
  //for( Int_t ip=0; ip<g_78m_band->GetN()/2; ip++ ) g_78m->SetPointError( ip, 0.0, 0.0 );


  //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  const Int_t npoint  = 11; // last component is dummy data for smooth curve
  Double_t x [npoint] = { -0.150, -0.100, -0.040, 0.000, 0.090, 0.180, 0.260, 0.340, 0.360, 0.400, 1.00};
  Double_t nsig[ng][npoint] = { // R2-LQ
    { 184.774, 184.667,  185.75,  186.799, 197.638, 212.066, 216.185, 214.672, 214.014, 212.252, 212.252  },
    { 116.304, 115.978,  115.868, 116.126, 121.977, 131.454, 135.512, 135.446, 135.235, 134.385, 134.385  },
    {  68.4701, 68.689,   69.882,  70.6731, 75.6613, 80.6114, 80.6731, 79.2256, 78.7794, 77.8678, 77.8678 },
  };
  Double_t nsigE[ng][npoint] = { // R2-LQ
    { 0.818649, 0.707212, 0.502613, 0.0, 0.871104, 1.20702,  1.32805,  1.38448,  1.39405,  1.40256, 1.40256  },
    { 0.660194, 0.569491, 0.403,    0.0, 0.677816, 0.94972,  1.0586,   1.1078,   1.1159,   1.12378, 1.12378  },
    { 0.484077, 0.41932,  0.300351, 0.0, 0.547163, 0.744931, 0.801937, 0.830402, 0.835554, 0.839218,0.839218 },
  };

  TLegend* leg  = new TLegend( 0.60,0.20,0.85,0.45 );
  TGraphErrors** eff       = new TGraphErrors*[ng];
  TGraph**       eff_band  = new TGraph*      [ng];
  TGraph**       eff_band1 = new TGraph*      [ng];
  TGraph**       eff_band2 = new TGraph*      [ng];
  for( Int_t ig=0; ig<ng; ig++ ){
    eff[ig] = new TGraphErrors();
    eff[ig]->SetMarkerStyle(20);
    eff[ig]->SetMarkerSize(0.6);
    eff[ig]->SetLineColor  ( ig==2 ? 4 : ig+1 );
    eff[ig]->SetMarkerColor( ig==2 ? 4 : ig+1 );
    eff[ig]->SetLineWidth(2);
    for( Int_t ip=0; ip<npoint; ip++ ){
      eff[ig]->SetPoint     ( eff[ig]->GetN(),   x[ip], nsig [ig][ip]/nsig[ig][smpoint] );
      eff[ig]->SetPointError( eff[ig]->GetN()-1,   0.0, nsigE[ig][ip]/nsig[ig][smpoint] );
    }
    if     ( ig==0 ){ eff_band[0] = makeBand( eff[0], kGray    ); eff_band[0]->SetFillStyle(1001); }
    else if( ig==1 ){ eff_band[1] = makeBand( eff[1], kPink+6  ); eff_band[1]->SetFillStyle(1001); }
    else if( ig==2 ){ eff_band[2] = makeBand( eff[2], kAzure+8 ); eff_band[2]->SetFillStyle(1001); }
    for( Int_t ip=0; ip<npoint; ip++ ) eff[ig]->SetPointError( ip, 0.0, 0.0 );

    eff_band1[ig] = new TGraph();
    eff_band2[ig] = new TGraph();
    eff_band1[ig]->SetLineColor( eff_band[ig]->GetFillColor() );
    eff_band2[ig]->SetLineColor( eff_band[ig]->GetFillColor() );
    for( Int_t ip=0; ip<npoint; ip++ ){
      eff_band1[ig]->SetPoint( eff_band1[ig]->GetN(), eff_band[ig]->GetX()[ip       ], eff_band[ig]->GetY()[ip       ] );
      eff_band2[ig]->SetPoint( eff_band2[ig]->GetN(), eff_band[ig]->GetX()[ip+npoint], eff_band[ig]->GetY()[ip+npoint] );
    }

    leg->AddEntry( eff[ig], Form("l = %s", fl_name[ig]), "PL" );
  }

  //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  TCanvas* can = new TCanvas("can","can", 1000, 800 );

  can->Divide(2,2);
  can->Draw();

  can->cd(1);
  can->cd(1)->SetGridy(1);
  TH2D* waku_eff = new TH2D("eff", Form("efficiency ratio of %s to SM;%s %s;#varepsilon^{%s}/#varepsilon^{SM}",model,param,unit,model), 2, xmin, xmax, 2, ymin_eff, ymax_eff );
  waku_eff->Draw();  
  for( Int_t ig=0; ig<ng; ig++ ) eff_band [ig]->Draw("FCsame");
  for( Int_t ig=0; ig<ng; ig++ ) eff_band1[ig]->Draw( "Csame");
  for( Int_t ig=0; ig<ng; ig++ ) eff_band2[ig]->Draw( "Csame");
  for( Int_t ig=0; ig<ng; ig++ ) eff      [ig]->Draw( "Csame");
  leg->Draw();

  TH2D** waku_rdstr = new TH2D*[ng];
  for( Int_t ig=0; ig<ng; ig++ ){
    can->cd(ig+2);
    waku_rdstr[ig] = new TH2D( Form("rdstr_lep%d",fl_lep[ig]), Form("l = %s;%s %s;R(D*)",fl_name[ig],param,unit), 2, xmin, xmax, 2, ymin_rdstr, ymax_rdstr );
    waku_rdstr [ig]->Draw();  
    g_band_tot [ig]->Draw( "Fsame");
    g_band_stat[ig]->Draw( "Fsame");
    g_78p_band     ->Draw("FLsame");
    g_78p_band2    ->Draw("FLsame");
    g_78p          ->Draw(  "same");
    smline         ->Draw( "Lsame");
    expline    [ig]->Draw( "Lsame");
    g          [ig]->Draw( "Csame"); // PCsame
  }

  //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  // Calculation of Favored Region
  std::cout << model << " : " << param << std::endl;
  for( Int_t ig=0; ig<ng; ig++ ){
    std::cout << "[" << fl_name[ig] << "]" << std::endl;
    Int_t fl_allow  = 0;
    Int_t fl_th_exp = 0; // 1(th>exp)
    for( Int_t ip=0; ip<g_78p_band->GetN()/2; ip++ ){
      Double_t x = g_78p_band->GetX()[ip];
      Double_t y_th   = g_78p->Eval(x);
      Double_t yeh_th = g_78p_band->GetY()[ip] - y_th;
      Double_t yel_th = y_th - g_78p_band->GetY()[g_78p_band->GetN()-ip-1];
      if( x - g_78p_band->GetX()[ip] > 1.0e-5 ||
	  x - g_78p_band->GetX()[g_78p_band->GetN()-ip-1] >1.0e-5) std::cerr << "[ABORT] Wrong x values : "
										 << ip << " : "
										 << x  << " : "
										 << g_78p_band->GetX()[ip] << " : "
										 << g_78p_band->GetX()[g_78p_band->GetN()-ip-1] << " : "
										 << std::endl, abort();
      //std::cout << "x = " << x << " : y(th) = " << y_th << " + " << yeh_th << " - " << yel_th << std::endl;
      
      Int_t tmp_cnt = 0;
      while ( g[ig]->GetX()[tmp_cnt] <= x ) tmp_cnt++;
      Double_t x2   = g[ig]->GetX()[tmp_cnt  ];
      Double_t x1   = g[ig]->GetX()[tmp_cnt-1];
      Double_t y2   = g[ig]->GetY()[tmp_cnt  ];
      Double_t y1   = g[ig]->GetY()[tmp_cnt-1];
      Double_t yeh2 = g_band_tot[ig]->GetY()[tmp_cnt  ] - y2;
      Double_t yeh1 = g_band_tot[ig]->GetY()[tmp_cnt-1] - y1;
      Double_t yel2 = y2 - g_band_tot[ig]->GetY()[g_band_tot[ig]->GetN()-tmp_cnt-2];
      Double_t yel1 = y1 - g_band_tot[ig]->GetY()[g_band_tot[ig]->GetN()-tmp_cnt-1];
      Double_t y_exp   = y1 + (x-x1)*(y2-y1)/(x2-x1);
      Double_t yeh_exp = yeh1 + (x-x1)*(yeh2-yeh1)/(x2-x1);
      Double_t yel_exp = yel1 + (x-x1)*(yel2-yel1)/(x2-x1);
      //std::cout << "     cnt = " << tmp_cnt << " : "
      //<< "x = " << x1 << " ~ " << x2 << " : "
      //<< "y = " << y1 << " ~ " << y2 << " -> " << y_exp << " : "
      //<< "yeh = " << yeh1 << " ~ " << yeh2 << " -> " << yeh_exp << " : "
      //<< "yel = " << yel1 << " ~ " << yel2 << " -> " << yel_exp << " : "
      //<< std::endl;

      Double_t delta = y_th - y_exp;
      Double_t sigma = 0.0;
      if( y_th - y_exp > 0 ) sigma = sqrt( pow(yel_th,2) + pow(yeh_exp,2) );
      else                   sigma = sqrt( pow(yeh_th,2) + pow(yel_exp,2) );
      if( ip==0 && y_th - y_exp > 0 ) fl_th_exp = 1;

      if( fabs(delta) < sigma && fl_allow==0 ){
	std::cout << x << " < x" << std::endl;
	fl_allow = 1;
      }else if( fl_allow==1 && (
				( y_th - y_exp > 0 && fl_th_exp==0 ) ||
				( y_th - y_exp < 0 && fl_th_exp==1 )
				)
		){
	std::cout << "x == " << x << std::endl;
	if( y_th - y_exp > 0 ) fl_th_exp = 1;
	else                   fl_th_exp = 0;
      }else if( fabs(delta) > sigma && fl_allow==1 ){
	std::cout << "x < " << x << std::endl;
	fl_allow = 0;
      }      
    }
  }
  //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

  can->Print( Form("pic/npcurve_%s.eps",filename) );

  std::cout << "finish" << std::endl;
  if( !gROOT->IsBatch() ) app.Run();
  return 0;
}
