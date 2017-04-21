#include "draws_.h"
#include "draws_npcurve_.h"

const Int_t    smpoint    = 1;
const Char_t*  model      = "type-II 2HDM";
const Char_t*  param      = "tan#beta/m_{H+}";
const Char_t*  unit       = "[GeV^{-1}]";
const Char_t*  filename   = "2hdmII";
const Double_t xmin       = 0.0;
const Double_t xmax       = 1.0;
const Double_t ymin_eff   = 0.85;
const Double_t ymax_eff   = 1.10;
//const Double_t ymax_eff   = 1.20; // for paper
const Double_t ymin_rdstr = 0.22;
const Double_t ymax_rdstr = 0.40;

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
  TGraphErrors** g           = new TGraphErrors*[ng]; // measured R(D*) value curve
  TGraph**       g_band_stat = new TGraph*      [ng]; // measured R(D*) error band (only stat)
  TGraph**       g_band_tot  = new TGraph*      [ng]; // measured R(D*) error band (stat + syst)
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
  TF1*    func_r_dsttaunu = new TF1( "func_r_dsttaunu",   makefunc_R_Dsttaunu, xmin, xmax, 0 ); // theoretical prediction curve
  func_r_dsttaunu->SetLineColor(4);
  TGraph* g_r_dsttaunu  = makeband_R_Dsttaunu( 0.0, 1.0 ); // theoretical predication error band (filled )
  TGraph* g_r_dsttaunu2 = makeband_R_Dsttaunu( 0.0, 1.0 ); // theoretical predication error band (hatched)
  g_r_dsttaunu2->SetFillColor(1);
  g_r_dsttaunu2->SetFillStyle(3005);


  //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  const Int_t   npoint           = 13; // first and last component is dummy data for smooth curve
  Double_t      x       [npoint] = {    -1.0, 0.0,     0.1,    0.2,     0.3,    0.4,     0.5,     0.6,    0.7,     0.8,     0.9,    1.0, 2.0 };
  Double_t      nsig[ng][npoint] = { // type-II 2HDM
    {186.799, 186.799, 187.679, 187.127, 186.859, 186.252, 184.823, 182.94,  180.915, 178.61,  177.536, 176.75,  176.75  },
    {116.126, 116.126, 116.537, 116.124, 115.991, 115.642, 114.725, 113.829, 113.005, 112.053, 111.737, 111.614, 111.614 },
    { 70.6731, 70.6731, 71.1428, 71.0028, 70.8679, 70.6101, 70.0985, 69.1102, 67.9108, 66.5577, 65.7992, 65.1362, 65.1362}
  };
  Double_t      nsigE[ng][npoint] = { // type-II 2HDM
    { 0.0, 0.0, 0.384254, 0.414727, 0.505816, 0.616514, 0.708494, 0.770601, 0.841783, 0.917139, 0.98169,  1.02396, 1.02396  },
    { 0.0, 0.0, 0.299784, 0.323185, 0.39603,  0.485562, 0.561487, 0.616189, 0.679072, 0.740569, 0.792296, 0.827657,0.827657 },
    { 0.0, 0.0, 0.240377, 0.259903, 0.31466,  0.379894, 0.432083, 0.462749, 0.497453, 0.541018, 0.579641, 0.60289, 0.60289  }
  };

  TLegend* leg  = new TLegend( 0.60,0.60,0.85,0.85 );
  TGraphErrors** eff       = new TGraphErrors*[ng]; // efficiency curve
  TGraph**       eff_band  = new TGraph*      [ng]; // efficiency error band (filled)
  TGraph**       eff_band1 = new TGraph*      [ng]; // efficiency error edge line (line)
  TGraph**       eff_band2 = new TGraph*      [ng]; // efficiency error edge line (line)
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
    g_r_dsttaunu   ->Draw("FLsame");
    g_r_dsttaunu2  ->Draw("FLsame");
    func_r_dsttaunu->Draw(  "same");
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
    for( Int_t ip=0; ip<g_r_dsttaunu->GetN()/2; ip++ ){
      Double_t x = g_r_dsttaunu->GetX()[ip];
      Double_t y_th   = func_r_dsttaunu->Eval(x);
      Double_t yeh_th = g_r_dsttaunu->GetY()[ip] - y_th;
      Double_t yel_th = y_th - g_r_dsttaunu->GetY()[g_r_dsttaunu->GetN()-ip-1];
      if( x - g_r_dsttaunu->GetX()[ip] > 1.0e-5 ||
	  x - g_r_dsttaunu->GetX()[g_r_dsttaunu->GetN()-ip-1] >1.0e-5) std::cerr << "[ABORT] Wrong x values : "
										 << ip << " : "
										 << x  << " : "
										 << g_r_dsttaunu->GetX()[ip] << " : "
										 << g_r_dsttaunu->GetX()[g_r_dsttaunu->GetN()-ip-1] << " : "
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

  
