#include "draws_.h"
#include "draws_roofit_.h"

const Char_t*  treename   = "h15";
const Char_t*  infilename = "/home/belle/syutaro/dstrtaunu/ana/NB/hbk/hbk_mode0_test13_nor/gMC_*s0[0-5]*.root";
const Double_t nstream    = 6;
const Int_t    iteration  = 1000;

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Int_t main( Int_t argc, Char_t** argv ){

  TApplication app( "app", &argc, argv );
  //gROOT->SetBatch(true); // tmpppppp

  //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  unsigned int seed = time(NULL);
  RooRandom::randomGenerator()->SetSeed( seed );
  //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  // <TChain>
  TChain* chain = new TChain( treename );  
  std::cout << chain->Add( infilename  ) << " files"   << std::endl;
  std::cout << chain->GetEntries()       << " entries" << std::endl;
  //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  // <OBSERVABLES>
  RooRealVar* eecl   = new RooRealVar( "eecl", "E_{ECL} [GeV]",  0.0, 1.2 ); // x
  RooArgSet*  varset = new RooArgSet ( *eecl );
  //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  // <PDF COMPONENT>
  const Int_t npdf = 2;
  TH1D** h = new TH1D*[npdf];
  h[0] = new TH1D( "h_sig",  "h_sig", 24, 0.0, 1.2 );
  h[1] = new TH1D( "h_bkg",  "h_bkg", 24, 0.0, 1.2 );
  chain->Project( "h_sig",  "eecl", "self==1&&nb_mode0_test13_nor>0.8");
  chain->Project( "h_bkg",  "eecl", "self!=1&&nb_mode0_test13_nor>0.8");
  h[0]->Print();
  h[1]->Print();

  Double_t init_tot   =  0;
  Double_t init[npdf] = {0};
  for( Int_t ipdf=0; ipdf<npdf; ipdf++ ){
    init[ipdf] = h[ipdf]->Integral()/nstream;
    init_tot += init[ipdf];
  }

  RooDataHist** hist = new RooDataHist*[npdf];
  RooHistPdf**  pdf  = new RooHistPdf* [npdf];
  hist[0] = new RooDataHist( "hist_sig", "hist_sig", *varset,     h[0] );
  hist[1] = new RooDataHist( "hist_bkg", "hist_bkg", *varset,     h[1] );
  pdf [0] = new RooHistPdf ( "pdf_sig",  "pdf_sig",  *varset, *hist[0] );
  pdf [1] = new RooHistPdf ( "pdf_bkg",  "pdf_bkg",  *varset, *hist[1] );
  hist[0]->Print();
  hist[1]->Print();

  //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  // <TOTAL PDF>
  RooRealVar** yield = new RooRealVar*[npdf];
  yield[0] = new RooRealVar( "n_sig", "N_{sig}", init[0],  0, 1.5*init_tot );
  yield[1] = new RooRealVar( "n_bkg", "N_{bkg}", init[1],  0, 1.5*init_tot );
  //yield[ipdf]->setConstant(true);

  RooArgList* pdflist   = new RooArgList();
  RooArgList* yieldlist = new RooArgList();
  for( Int_t ipdf=0; ipdf<npdf; ipdf++ ){
    pdflist  ->add( *pdf  [ipdf] );
    yieldlist->add( *yield[ipdf] );
  }
  RooAddPdf* pdf_tot = new RooAddPdf( "pdf_tot", "pdf_tot", *pdflist, *yieldlist );

  //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  // <CANVAS>
  TCanvas* can = new TCanvas( "can","can", 1200, 1000 );
  can->Divide(3,2);
  can->Draw();

  //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  can->cd(1);
  RooPlot* frame_eecl = eecl->frame();
  frame_eecl->SetTitle("E_{ECL}");
  hist[0]->plotOn( frame_eecl, Binning(24), MarkerColor(kRed),   LineColor(kRed),   LineWidth(1) ); // sig
  hist[1]->plotOn( frame_eecl, Binning(24), MarkerColor(kBlue),  LineColor(kBlue),  LineWidth(1) ); // bkg
  frame_eecl->Draw();

  //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  // <generate toy MC samples>
  std::cout << "*************************** TOY MC samples are generated : " << (Int_t)(init_tot) << " events "
	    << "***************************" << std::endl;
  for( Int_t ipdf=0; ipdf<npdf; ipdf++ ) yield[ipdf]->setVal( init[ipdf] );
  RooDataSet* toy_mcdata = pdf_tot->generate( *varset, (Int_t)(init_tot), AutoBinned(true) ); // if option "Extended(true)" is added, # of events will be fluctuated.
  toy_mcdata->Print();

  //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  // <Fitting toy MC samples>
  std::cout << "*************************** Fit is started "
	    << "***************************" << std::endl;
  RooFitResult* fit_result = pdf_tot->fitTo( *toy_mcdata, Extended(true), Save(true) );
  fit_result->Print();

  can->cd(2);
  RooPlot* frame_fit_eecl = eecl->frame();
  frame_fit_eecl->SetTitle("E_{ECL}");
  toy_mcdata->plotOn( frame_fit_eecl, Binning(24),        MarkerColor(1), LineColor(1), LineWidth(1) ); // toy-data
  pdf_tot   ->plotOn( frame_fit_eecl, Components(*pdflist), LineStyle(1), LineColor(2), LineWidth(1) ); // total-PDF
  for( Int_t ipdf=0; ipdf<npdf; ipdf++ ) pdf_tot->plotOn( frame_fit_eecl, Components(*pdf[ipdf] ), LineStyle(2), LineColor(ipdf+3), LineWidth(1) ); // each-PDF
  frame_fit_eecl->Draw();

  //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  // Iterative toy MC Fitting
  std::cout << "*************************** Iterative TOY MC is started : " << iteration << " iterations "
	    << "***************************" << std::endl;
  for( Int_t ipdf=0; ipdf<npdf; ipdf++ ) yield[ipdf]->setVal( init[ipdf] );

  RooMCStudy* mcstudy = new RooMCStudy( *pdf_tot, *varset, Binned(true), Silence(true), Extended(true), FitOptions(Save(true),PrintEvalErrors(0)) );
  mcstudy->generateAndFit( iteration );
  for( Int_t i=0; i<iteration; i++ ) mcstudy->fitResult(i)->Print();

  RooPlot* frame_toy_mean = mcstudy->plotParam( *yield[0], Bins(40) );
  RooPlot* frame_toy_err  = mcstudy->plotError( *yield[0], Bins(40) );
  RooPlot* frame_toy_pull = mcstudy->plotPull ( *yield[0], Bins(40), FitGauss(true) );
  RooPlot* frame_toy_nll  = mcstudy->plotNLL( Bins(40) );

  can->cd(3); frame_toy_mean->Draw();
  can->cd(4); frame_toy_err ->Draw();
  can->cd(5); frame_toy_pull->Draw();
  can->cd(6); frame_toy_nll ->Draw();

  //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

  can->Update();
  can->Print( Form("pic/1d_fit.eps") );
  std::cout << "finish" << std::endl;
  if( !gROOT->IsBatch() ) app.Run();

  return 0;

}
