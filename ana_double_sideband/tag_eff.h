#ifndef TAG_EFF_H
#define TAG_EFF_H

#include "draws_.h"

TGraphErrors* makeGraph( const Char_t* infile, const Int_t x, const Int_t y, const Int_t yE, const Bool_t fl_message=false ){

  ifstream fin( infile );
  if( !fin ){
    std::cout << "can not find a file : " << infile << std::endl;
    abort();
  }


  if( x>=y || y>=yE ) std::cerr << "[ABORT] Wrong selection : " << x << ", " << y << ", " << yE << std::endl, abort();
  std::stringstream sTmp;
  Bool_t fl_x = false;
  Bool_t fl_y = false;

  for( Int_t i=0; i<yE+1; i++ ){
    if( !fl_x ){ // x search
      if( i==x ){
	sTmp << "%lg ";
	fl_x = true;
	continue;
      }else{
	sTmp << "%*lg ";
      }
    }else if( !fl_y ){ // y search
      if( i==y ){
	sTmp << "%lg ";
	fl_y = true;
	continue;
      }else{
	sTmp << "%*lg ";
      }
    }else{ // yE search
      if( i==yE ){
	sTmp << "%lg ";
	break;
      }else{
	sTmp << "%*lg ";
      }
    }
  }

  std::cout << std::setw(30) << std::right << infile << " : "<< sTmp.str().c_str() << std::endl;
  TGraphErrors* g = new TGraphErrors( infile, sTmp.str().c_str() );
  g->Sort();
  if( fl_message==true ) g->Print("all");
  return g;
}

TGraphErrors* makeGraph_conv( const Char_t* infile, const Int_t x, const Int_t y, const Int_t yE, const Bool_t fl_message=false ){
  TGraphErrors* g = makeGraph( infile, x, y, yE, false );
  for( Int_t ip=0; ip<g->GetN(); ip++ ) g->SetPoint( ip, (Double_t)dec_index((Int_t)g->GetX()[ip]), g->GetY()[ip] );
  if( fl_message ) g->Print();
  return g;
}


TGraphErrors* makeGraph_manip( TGraphErrors* g1, TGraphErrors* g2, const Int_t fl, const Bool_t fl_message=false ){ // 0(ave), 1(prod), 2(diff)
  if( g1->GetN() != g2->GetN() ) std::cerr << "[ABORT] Different # of point" << std::endl, abort();
  TGraphErrors* g = new TGraphErrors();
  for( Int_t ip=0; ip<g1->GetN(); ip++ ){
    if( g1->GetX()[ip] != g2->GetX()[ip] ) std::cerr << "[ABORT] Different x value" << std::endl, abort();
    Double_t tmp1  = g1->GetY() [ip];
    Double_t tmp1E = g1->GetEY()[ip];
    Double_t tmp2  = g2->GetY() [ip];
    Double_t tmp2E = g2->GetEY()[ip];
    Double_t tmp, tmp_E;
    if( fl==0 ){
      tmp   = (tmp1/pow(tmp1E,2)+tmp2/pow(tmp2E,2))/(1/pow(tmp1E,2) + 1/pow(tmp2E,2));
      tmp_E = sqrt( 1/(1/pow(tmp1E,2) + 1/pow(tmp2E,2)) );
    }else if( fl==1 ){
      tmp   = tmp1*tmp2;
      tmp_E = tmp*sqrt( pow(tmp1E/tmp1,2) +  pow(tmp2E/tmp2,2) );
    }else if( fl==2 ){
      tmp   = tmp1-tmp2;
      tmp_E = sqrt( pow(tmp1E,2) +  pow(tmp2E,2) );
    }

    if( fl_message ){
      std::cout << "["
		<< std::setw( 3) << std::right << ip             << ", "
		<< std::setw( 5) << std::right << d_dec[(Int_t)g1->GetX()[ip]] << ", "
		<< std::setw(15) << std::right << d_dec_name[(Int_t)g1->GetX()[ip]] << " ] : ";
      std::cout << "[" << std::setw(10) << std::right << tmp1 << " +- " << std::setw(10) << std::right << tmp1E << "]";
      std::cout << "[" << std::setw(10) << std::right << tmp2 << " +- " << std::setw(10) << std::right << tmp2E << "] ->";
      std::cout << "[" << std::setw(10) << std::right << tmp  << " +- " << std::setw(10) << std::right << tmp_E << "]" << std::endl;
    }
    g->SetPoint     ( g->GetN(),   g1->GetX()[ip], tmp   );
    g->SetPointError( g->GetN()-1,              0, tmp_E );
  }
  return g;
}

TGraphErrors* makeGraph_ave ( TGraphErrors* g1, TGraphErrors* g2 ){ return makeGraph_manip( g1, g2, 0 ); }
TGraphErrors* makeGraph_prod( TGraphErrors* g1, TGraphErrors* g2 ){ return makeGraph_manip( g1, g2, 1 ); }
TGraphErrors* makeGraph_diff( TGraphErrors* g1, TGraphErrors* g2 ){ return makeGraph_manip( g1, g2, 2 ); }

void Deco_Fill( TGraphErrors* g, const Int_t col=13 ){
  g->SetLineWidth  ( 10);
  g->SetMarkerStyle(  1);
  g->SetMarkerColor(col);
  g->SetLineColor  (col);

}

void Deco_Mark( TGraphErrors* g, const Int_t col=1 ){
  g->SetLineWidth  (  2);
  g->SetMarkerStyle( 24);
  g->SetMarkerColor(col);
  g->SetLineColor  (col);
  
}

#endif
