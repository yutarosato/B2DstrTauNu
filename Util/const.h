#ifndef CONST_H
#define CONST_H

#include <fstream>
#include <iostream>
#include <sstream>
#include <iomanip>
#include <vector>
#include <math.h>
#include <stdlib.h>
#include <map>

#include <TROOT.h>
#include <TStyle.h>
#include <TSystem.h>
#include <TColor.h>
#include <TGaxis.h>
#include <TCanvas.h>
#include <TChain.h>
#include <TTree.h>
#include <TCut.h>
#include <TLeaf.h>
#include <THStack.h>
#include <TH2C.h>
#include <TH1D.h>
#include <TH2D.h>
#include <TH2F.h>
#include <TProfile.h>
#include <TF1.h>
#include <TFitResult.h>
#include <TFitResultPtr.h>
#include <TGraph.h>
#include <TGraphErrors.h>
#include <TGraphAsymmErrors.h>
#include <TApplication.h>
#include <TLegend.h>
#include <TPaveText.h>
#include <TString.h>
#include <TFile.h>
#include <TArrow.h>
#include <TMath.h>
#include <TRandom.h>
#include <TSpectrum.h>

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



namespace PDGmass{
  const double pip   =  0.13957018;
  const double pim   =  pip;
  const double pi0   =  0.1349766;
  const double ele   =  0.000510998910;
  const double pos   =  ele;
  const double mu    =  0.105658367;
  const double ks    =  0.497614;
  const double kstr0 =  0.89594;
  const double kstrp =  0.89166;
  const double kstrm =  kstrp;
  const double kp    =  0.493677;
  const double km    =  kp;
  const double jpsi  =  3.096916;
  const double psi2s =  3.68609;
  const double b0    =  5.27953;
  const double bp    =  5.27915;
  const double bm    =  bp;
  const double dstr0 =  2.00696;
  const double dstrp =  2.01025;
  const double dstrm =  dstrp;
  const double d0    =  1.86484;
  const double dp    =  1.86962;
  const double dm    =  dp;
}

#endif
