#include "Residual.h"

TGraphErrors* Residual( TH1D* hist1, TH1D* hist2, const Char_t* axisname, const Char_t* memo, Double_t chi_range ){
  if( hist1->GetNbinsX()      != hist2->GetNbinsX()      ) std::cerr << "[ABORT] different #bin"      << std::endl, abort();
  if( hist1->GetBinLowEdge(1) != hist2->GetBinLowEdge(1) ) std::cerr << "[ABORT] different bin range" << std::endl, abort();
  if( hist1->GetBinWidth  (1) != hist2->GetBinWidth  (1) ) std::cerr << "[ABORT] different bin width" << std::endl, abort();

  TGraphErrors* graph = new TGraphErrors();
  const Int_t    xbin = hist1->GetNbinsX();
  const Double_t xmin = hist1->GetBinLowEdge(1);
  const Double_t xmax = hist1->GetBinLowEdge(xbin) + hist1->GetBinWidth(xbin);
  for( Int_t ibin=0; ibin<xbin; ibin++ ){
    Double_t  x   = hist1->GetBinCenter (ibin+1);
    Double_t dy   = hist1->GetBinContent(ibin+1) - hist2->GetBinContent(ibin+1); // hist1 - hist2
    Double_t dyE  = sqrt( pow(hist1->GetBinError(ibin+1),2) + pow(hist2->GetBinError(ibin+1),2) );
    Double_t chi = dy/dyE;

    graph->SetPoint     ( ibin, x, chi   );
    graph->SetPointError( ibin, 0, 1     );
  }
  graph->SetMarkerStyle(6);
  graph->SetMarkerColor(2);
  graph->SetLineColor  (2);
  graph->GetXaxis()->SetLimits( xmin, xmax );
  graph->SetMinimum(-chi_range);
  graph->SetMaximum( chi_range);
  graph->SetTitle( Form(";%s;#chi(%s)",axisname, memo) );
  graph->GetYaxis()->SetNdivisions(110);
  graph->GetXaxis()->SetNdivisions(510);

  return graph;
}


TGraphErrors* Residual( TH1D* hist, TF1* func, const Char_t* axisname, const Char_t* memo, Double_t chi_range ){
  TGraphErrors* graph = new TGraphErrors();
  const Int_t    xbin = hist->GetNbinsX();
  const Double_t xmin = hist->GetBinLowEdge(1);
  const Double_t xmax = hist->GetBinLowEdge(xbin) + hist->GetBinWidth(xbin);
  for( Int_t ibin=0; ibin<xbin; ibin++ ){
    Double_t  x   = hist->GetBinCenter (ibin+1);
    Double_t dy   = hist->GetBinContent(ibin+1) - func->Eval(x); // hist - func
    Double_t dyE  = hist->GetBinError(ibin+1);
    Double_t chi = dy/dyE;

    graph->SetPoint     ( ibin, x, chi   );
    graph->SetPointError( ibin, 0, 1     );
  }
  graph->SetMarkerStyle(6);
  graph->SetMarkerColor(2);
  graph->SetLineColor  (2);
  graph->GetXaxis()->SetLimits( xmin, xmax );
  graph->SetMinimum(-chi_range);
  graph->SetMaximum( chi_range);
  graph->SetTitle( Form(";%s;#chi(%s)",axisname,memo) );
  graph->GetYaxis()->SetNdivisions(110);
  graph->GetXaxis()->SetNdivisions(510);
  return graph;
}
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

TPad* makePadU( const Char_t* name, const Char_t* title, Double_t margin, Bool_t fl_gridy, Bool_t fl_gridx ){
  return makePad( 1, name, title, margin, fl_gridy, fl_gridx );
}

TPad* makePadD( const Char_t* name, const Char_t* title, Double_t margin, Bool_t fl_gridy, Bool_t fl_gridx ){
  return makePad( 0, name, title, margin, fl_gridy, fl_gridx );
}

TPad* makePad( Bool_t fl_ud, const Char_t* name, const Char_t* title, Double_t margin, Bool_t fl_gridy, Bool_t fl_gridx ){
  TPad* pad = new TPad( name, title, 0.0, 0.0, 1.0, 1.0 );
  if( fl_ud ) pad->SetBottomMargin( margin ); // for  upper pad
  else        pad->SetTopMargin   ( margin ); // for bottom pad
  pad->SetFillColor(0);
  pad->SetFillStyle(0);
  pad->SetGridx(fl_gridx);
  pad->SetGridy(fl_gridy);
  return pad;
}
