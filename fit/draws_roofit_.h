#ifndef DRAWS_ROOFIT_H
#define DRAWS_ROOFIT_H

#include <RooFit.h>
#include <RooGlobalFunc.h>
#include <RooRealVar.h>
#include <RooCategory.h>
#include <RooDataSet.h>
#include <RooDataHist.h>
#include <RooArgSet.h>
#include <RooArgList.h>
#include <RooGaussian.h>
#include <RooArgusBG.h>
#include <RooChebychev.h>
#include <RooFormulaVar.h>
#include <RooAddPdf.h>
#include <RooProdPdf.h>
#include <RooHistPdf.h>
#include <RooSimultaneous.h>
#include <RooFitResult.h>
#include <RooPlot.h>
#include <RooBinning.h>
#include <RooAbsReal.h>
#include <RooGenericPdf.h>
#include <RooCFunction1Binding.h>
#include <RooCFunction2Binding.h>
#include <RooCFunction3Binding.h>
#include <RooCFunction4Binding.h>
#include <RooTFnPdfBinding.h>
#include <RooPolynomial.h>
#include <RooTFnBinding.h>
#include <RooMCStudy.h>
#include <RooRandom.h>
#include <RooKeysPdf.h>
#include <RooNDKeysPdf.h>
#include "RooFFTConvPdf.h"

using namespace RooFit;
/*
void smooth( TH2D* hist, Int_t n=3 ){
  Int_t xbin = hist->GetNbinsX(); // nb
  Int_t ybin = hist->GetNbinsY(); // eecl
  for( Int_t iybin=0; iybin<ybin; iybin++ ){
    TH1D* hist_proj = hist->ProjectionX( "_proj", iybin+1, iybin+1 );
    RooRealVar  nb      ( "nb",       "NB",       -1.0, 1.0 );
    RooDataHist datahist( "datahist", "datahist", nb, hist_proj );
    RooHistPdf  pdfhist ( "pdfhist",  "pdfhist",  nb, datahist  );
    RooDataSet* dataset = pdfhist.generate( nb, hist_proj->GetEntries() );

    RooKeysPdf kest( "kest", "kest", nb, *dataset, RooKeysPdf::MirrorBoth );
    TH1* smoothed_hist = kest.createHistogram( Form("sm_%d",iybin), nb, Binning(xbin) );
    smoothed_hist->Scale( hist_proj->Integral()/smoothed_hist->Integral() );
    for( Int_t ixbin=0; ixbin<xbin; ixbin++ ) hist->SetBinContent( ixbin+1, iybin+1, smoothed_hist->GetBinContent(ixbin+1) );

  }
  return;
}
*/
#endif
