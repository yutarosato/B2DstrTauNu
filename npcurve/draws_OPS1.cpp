#include "draws_.h"
#include "draws_npcurve_.h"

const Int_t    smpoint    = 5;
const Char_t*  model      = "Operator";
const Char_t*  param      = "C_{S_{1}}";
const Char_t*  unit       = "";
const Char_t*  filename   = "OPS1";
const Double_t xmin       = -5.0;
const Double_t xmax       =  3.0;
const Double_t ymin_eff   = 0.85;
//const Double_t ymax_eff   = 1.10;
const Double_t ymax_eff   = 1.20; // for paper
//const Double_t ymin_rdstr = 0.22;
//const Double_t ymax_rdstr = 0.40;
const Double_t ymin_rdstr = 0.10;
const Double_t ymax_rdstr = 0.65;

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
  TLine* smline = new TLine( xmin, 0.252753, xmax, 0.252753 );
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
  
  //                                                                                                                            [  CS1 ]   [  CS2 ]  [  CV1 ]  [  CV2 ]  [  CT  ]
  TGraphErrors* g_op = makeRdstr_OP( rho_A1_2, a_3, R11, R21, mbPmc, mbMmc, rho_A1_2_E, a_3_E, R11_E, R21_E, mbPmc_E, mbMmc_E, 1.0, 0.0,  0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, xmin, xmax );
  g_op->SetLineColor(4);
  g_op->SetLineWidth(2);
  TGraph* g_op_band  = makeBand( g_op, 7 );
  TGraph* g_op_band2 = makeBand( g_op, 7 );
  g_op_band2->SetFillColor(1);
  g_op_band2->SetFillStyle(3005);
  
  for( Int_t ip=0; ip<g_op_band->GetN()/2; ip++ ) g_op->SetPointError( ip, 0.0, 0.0 );

  //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  const Int_t   npoint           = 10-1+1; // last component is dummy data for smooth curve
  Double_t      x       [npoint] = {    -5.0, -4.0, -3.0, -2.0, -1.0, 0.0, 1.0, /*1.05,*/ 2.0, 3.0, 4.0 };
  Double_t      nsig[ng][npoint] = { // OPS1
    {178.166, 179.741, 181.833, 183.892, 186.124, 186.799, 187.466, /*187.279, */186.79,  186.082, 186.082  },
    {111.938, 112.494, 113.478, 114.411, 115.634, 116.126, 116.898, /*116.777, */116.888, 116.811, 116.811  },
    { 66.2287, 67.2475, 68.355,  69.4809, 70.4896, 70.6731, 70.568, /* 70.5018,*/ 69.9017, 69.2709, 69.2709 }
  };
  Double_t      nsigE[ng][npoint] = { // OPS1
    { 0.929807, 0.863871, 0.78633,  0.713148, 0.570724, 0.0, 0.594976, /*0.601676,*/ 0.782868, 0.907602, 0.907602 },
    { 0.75185,  0.698404, 0.634262, 0.571168, 0.452446, 0.0, 0.474383, /*0.479983,*/ 0.626146, 0.725652, 0.725652 },
    { 0.547049, 0.508435, 0.464786, 0.427021, 0.347877, 0.0, 0.359106, /*0.362809,*/ 0.469919, 0.545133, 0.545133 },
  };

  TLegend* leg  = new TLegend( 0.60,0.60,0.85,0.85 );
  TGraphErrors** eff       = new TGraphErrors*[ng];
  TGraph**       eff_band  = new TGraph*      [ng];
  TGraph**       eff_band1 = new TGraph*      [ng];
  TGraph**       eff_band2 = new TGraph*      [ng];
  for( Int_t ig=0; ig<ng; ig++ ){
    eff[ig] = new TGraphErrors();
    eff[ig]->SetMarkerStyle();
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
    g_op_band      ->Draw("FLsame");
    g_op_band2     ->Draw("FLsame");
    g_op           ->Draw(  "same");
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
    for( Int_t ip=0; ip<g_op_band->GetN()/2; ip++ ){
      Double_t x = g_op_band->GetX()[ip];
      Double_t y_th   = g_op->Eval(x);
      Double_t yeh_th = g_op_band->GetY()[ip] - y_th;
      Double_t yel_th = y_th - g_op_band->GetY()[g_op_band->GetN()-ip-1];
      if( x - g_op_band->GetX()[ip] > 1.0e-5 ||
	  x - g_op_band->GetX()[g_op_band->GetN()-ip-1] >1.0e-5) std::cerr << "[ABORT] Wrong x values : "
										 << ip << " : "
										 << x  << " : "
										 << g_op_band->GetX()[ip] << " : "
										 << g_op_band->GetX()[g_op_band->GetN()-ip-1] << " : "
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

  
