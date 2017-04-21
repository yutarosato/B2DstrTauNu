#include "draws_.h"
#include "draws_roofit_.h"

const Char_t*  treename   = "h15";
const Char_t*  nbbrname   = "nb_mode0_test13_nor";
const Char_t*  infilename = "/home/belle/syutaro/dstrtaunu/ana/NB/hbk/hbk_bcs_vtx_mode0_test13_nor/gMC_*s0[0-5]*.root";
const Double_t nstream    = 6;
const Int_t    nbin_nb    = 25;
//const Int_t    iteration  = 1000;
const Int_t    iteration  = 10;
const Bool_t   roosumw2   = !true; // fixed

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
const Int_t   npdf                = 4;
const Char_t* pdf_name     [npdf] = { "other",                           "sig",                           "nor",    "Dstst"};
const Char_t* pdf_selection[npdf] = {     "0", "self==1||(self==0&&gm_semi>0)", "self==2||(self==0&&gm_semi<0)", "self==-5"};
Bool_t        pdf_use      [npdf] = {   !true,                           !true,                           !true,     !true };
Bool_t        pdf_fix      [npdf] = {   !true,                           !true,                           !true,     !true };
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Int_t main( Int_t argc, Char_t** argv ){

  TApplication app( "app", &argc, argv );
  TStyle* sty = Style(10);
  sty->SetTitleOffset(1.0,"z");
  gROOT->SetBatch(!true); // tmpppppp
  //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  if( app.Argc()!=3+npdf ){
    std::cerr << "Wrong input : " << app.Argc() << std::endl
	      << " Usage : "      << app.Argv(0) 
	      << " (char*)outfilename "
	      << " (double)nexp "
	      << " (int)fl_pdf[npdf] " << std::endl
	      << " fl_pdf : 2(fixed pdf), 1(float pdf) 0(not used) " << std::endl
	      << " npdf=" << npdf << " : ";
    for( Int_t ipdf=0; ipdf<npdf; ipdf++ ) std::cout << pdf_name[ipdf] << ", ";
    std::cout << std::endl, abort();
  }
  
  Char_t outfilename[128];
  strcpy( outfilename, app.Argv(1) );
  Double_t nexp = atof( app.Argv(2) );

  Int_t pdf_fl[npdf] = {0};
  for( Int_t ipdf=0; ipdf<npdf; ipdf++ ){
    pdf_fl[ipdf] = atoi(app.Argv(ipdf+3));
    if( pdf_fl[ipdf]>0 ) pdf_use[ipdf] = true;
    if( pdf_fl[ipdf]>1 ) pdf_fix[ipdf] = true;
  }

  //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  unsigned int seed = time(NULL);
  seed += (Int_t)(10000.0*nexp);
  RooRandom::randomGenerator()->SetSeed( seed );
  //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  // <TChain>
  TChain* chain = new TChain( treename );  
  std::cout << chain->Add( infilename  ) << " files"   << std::endl;
  std::cout << chain->GetEntries()       << " entries" << std::endl;
  //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  // <OBSERVABLES>
  RooRealVar* nb     = new RooRealVar( "nb",   "NB",            -1.0, 1.0 ); // x 
  RooRealVar* eecl   = new RooRealVar( "eecl", "E_{ECL} [GeV]",  0.0, 1.2 ); // y
  RooRealVar* z      = new RooRealVar( "z",    "z",              0.0, 100 ); // z
  RooArgSet*  varset = new RooArgSet ( *nb, *eecl );
  nb  ->setRange( "signal_box_nb",   0.8, 1.0 );
  eecl->setRange( "signal_box_eecl", 0.0, 0.5 );
  //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  // <PDF COMPONENT>
  TH2D** h = new TH2D*[npdf];

  for( Int_t ipdf=0; ipdf<npdf; ipdf++ ){
    h[ipdf] = new TH2D( Form("h_%s",pdf_name[ipdf]),  Form("h_%s",pdf_name[ipdf]),  nbin_nb, -1.0, 1.0, 24, 0.0, 1.2 );
    if( ipdf==0 ) chain->Project( Form("h_%s",pdf_name[ipdf]),  Form("eecl:%s",nbbrname), makeCut_remain(pdf_selection,npdf).c_str() );
    else          chain->Project( Form("h_%s",pdf_name[ipdf]),  Form("eecl:%s",nbbrname), pdf_selection[ipdf]                        );
    h[ipdf]->Print();
  }

  Double_t init_tot   =  0;
  Double_t init[npdf] = {0};
  std::cout << std::setw(10) << std::right << "<name>"  << " : "
	    << std::setw(10) << std::right << "<nevt>"  << " -> "
	    << std::setw(10) << std::right << "(scale)"
	    << std::setw( 7) << std::right << "<use>"
	    << std::setw( 7) << std::right << "<fix>"
	    << std::endl;
  for( Int_t ipdf=0; ipdf<npdf; ipdf++ ){
    init[ipdf] = h[ipdf]->Integral();
    std::cout << std::setw(10) << std::right << pdf_name[ipdf] << " : "
	      << std::setw(10) << std::right << init[ipdf];
    init[ipdf] /= nstream;
    std::cout << " -> "
	      << std::setw(10) << std::right << init   [ipdf]
	      << std::setw( 7) << std::right << pdf_use[ipdf]
	      << std::setw( 7) << std::right << pdf_fix[ipdf]
	      << std::endl;
    if( pdf_use[ipdf] ) init_tot += init[ipdf];
  }
  std::cout << "ntot = " << init_tot << std::endl;

  RooDataHist** hist = new RooDataHist*[npdf];
  RooHistPdf**  pdf  = new RooHistPdf* [npdf];
  for( Int_t ipdf=0; ipdf<npdf; ipdf++ ){
    hist[ipdf] = new RooDataHist( Form("hist_%s",pdf_name[ipdf]), Form("hist_%s",pdf_name[ipdf]), *varset,     h[ipdf] );
    pdf [ipdf] = new RooHistPdf ( Form( "pdf_%s",pdf_name[ipdf]), Form( "pdf_%s",pdf_name[ipdf]), *varset, *hist[ipdf] );
    hist[ipdf]->Print();
  }

  //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  // <TOTAL PDF>
  RooRealVar** yield = new RooRealVar*[npdf];
  for( Int_t ipdf=0; ipdf<npdf; ipdf++ ){
    yield[ipdf] = new RooRealVar( Form("n%s",pdf_name[ipdf]), Form("N_{%s}",pdf_name[ipdf]), nexp*init[ipdf],  0, 1.2*nexp*init_tot );
    if( pdf_fix[ipdf] ) yield[ipdf]->setConstant(true);
  }

  RooArgList* pdflist   = new RooArgList();
  RooArgList* yieldlist = new RooArgList();
  for( Int_t ipdf=0; ipdf<npdf; ipdf++ ){
    if( pdf_use[ipdf] ){
      pdflist  ->add( *pdf  [ipdf] );
      yieldlist->add( *yield[ipdf] );
    }
  }
  RooAddPdf* pdf_tot = new RooAddPdf( "pdf_tot", "pdf_tot", *pdflist, *yieldlist );

  //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  // <CANVAS>
  TCanvas* can = Canvas( "can","can", 4, 3 );
  can->Draw();

  //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  can->cd(1);
  RooPlot* frame_nb = nb->frame();
  frame_nb->SetTitle("NB with signal E_{ECL} region");
  hist[1]->plotOn( frame_nb, Binning(nbin_nb), MarkerColor(kRed),   LineColor(kRed),   LineWidth(1), CutRange("signal_box_eecl") ); // sig
  hist[2]->plotOn( frame_nb, Binning(nbin_nb), MarkerColor(kBlue),  LineColor(kBlue),  LineWidth(1), CutRange("signal_box_eecl") ); // nor
  hist[3]->plotOn( frame_nb, Binning(nbin_nb), MarkerColor(kBlack), LineColor(kBlack), LineWidth(1), CutRange("signal_box_eecl") ); // D**
  frame_nb->Draw();

  //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  can->cd(2);
  RooPlot* frame_eecl = eecl->frame();
  frame_eecl->SetTitle("E_{ECL} with signal NB region");
  hist[1]->plotOn( frame_eecl, Binning(24), MarkerColor(kRed),   LineColor(kRed),   LineWidth(1), CutRange("signal_box_nb") ); // sig
  hist[2]->plotOn( frame_eecl, Binning(24), MarkerColor(kBlue),  LineColor(kBlue),  LineWidth(1), CutRange("signal_box_nb") ); // nor
  hist[3]->plotOn( frame_eecl, Binning(24), MarkerColor(kBlack), LineColor(kBlack), LineWidth(1), CutRange("signal_box_nb") ); // D**
  frame_eecl->Draw();

  //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  //can->cd(3); hist[1]->createHistogram( pdf_name[1], *nb, Binning(nbin_nb), YVar(*eecl,Binning(24)) )->Draw("SURF3");
  //can->cd(4); hist[2]->createHistogram( pdf_name[2], *nb, Binning(nbin_nb), YVar(*eecl,Binning(24)) )->Draw("SURF3");
  can->cd(3); hist[1]->createHistogram( pdf_name[1], *nb, Binning(nbin_nb), YVar(*eecl,Binning(24)) )->Draw("COLZ");
  can->cd(4); hist[2]->createHistogram( pdf_name[2], *nb, Binning(nbin_nb), YVar(*eecl,Binning(24)) )->Draw("COLZ");
  //can->cd(3); hist[0]->createHistogram( pdf_name[0], *nb, Binning(nbin_nb), YVar(*eecl,Binning(24)) )->Draw("COLZ");
  //can->cd(4); hist[3]->createHistogram( pdf_name[3], *nb, Binning(nbin_nb), YVar(*eecl,Binning(24)) )->Draw("COLZ");

  //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  // <TOY MC>
  std::cout << "*************************** TOY MC samples are generated : " << (Int_t)(nexp*init_tot) << " events "
	    << "***************************" << std::endl;
  for( Int_t ipdf=0; ipdf<npdf; ipdf++ ) yield[ipdf]->setVal( nexp*init[ipdf] );
  RooDataSet* toy_mcdata = pdf_tot->generate( *varset, (Int_t)(nexp*init_tot), AutoBinned(true) ); // Extended(true)
  toy_mcdata->Print();

  //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  // <FIT>
  std::cout << "*************************** Fit is started "
	    << "***************************" << std::endl;
  RooFitResult* fit_result = pdf_tot->fitTo( *toy_mcdata, Extended(true), Save(true), SumW2Error(roosumw2) );
  fit_result->Print();
  /*  
  can->cd(5);
  RooPlot* frame_fit_nb = nb->frame();
  frame_fit_nb->SetTitle("NB");
  toy_mcdata->plotOn( frame_fit_nb, Binning(nbin_nb),       MarkerColor(1), LineColor(1), LineWidth(1) ); // toy-data
  pdf_tot   ->plotOn( frame_fit_nb, Components(*pdflist), LineStyle(1), LineColor(2), LineWidth(1) ); // total
  for( Int_t ipdf=0; ipdf<npdf; ipdf++ ){
    if( pdf_use[ipdf] && !pdf_fix[ipdf] ) pdf_tot->plotOn( frame_fit_nb, Components(*pdf[ipdf]), LineStyle(2), LineColor(ipdf+3), LineWidth(1) );
  }
  frame_fit_nb->Draw();

  can->cd(6);
  can->cd(6)->SetLogy();
  RooPlot* frame_fit_nb_enh = nb->frame();
  frame_fit_nb_enh->SetTitle("NB with signal E_{ECL} region");
  toy_mcdata->plotOn( frame_fit_nb_enh, Binning(nbin_nb),       MarkerColor(1), LineColor(1), LineWidth(1),        CutRange("signal_box_eecl") ); // toy-data
  pdf_tot   ->plotOn( frame_fit_nb_enh, Components(*pdflist), LineStyle(2), LineColor(1), LineWidth(1), ProjectionRange("signal_box_eecl") ); // total
  for( Int_t ipdf=0; ipdf<npdf; ipdf++ ){
    if( pdf_use[ipdf] && !pdf_fix[ipdf] ) pdf_tot->plotOn( frame_fit_nb_enh, Components(*pdf[ipdf]), LineStyle(2), LineColor(ipdf+3), LineWidth(1), ProjectionRange("signal_box_eecl") ); // default
  }
  frame_fit_nb_enh->Draw();

  can->cd(7);
  RooPlot* frame_fit_eecl = eecl->frame();
  frame_fit_eecl->SetTitle("E_{ECL}");
  toy_mcdata->plotOn ( frame_fit_eecl, Binning(24),        MarkerColor(1), LineColor(1), LineWidth(1) ); // toy-data
  pdf_tot   ->plotOn ( frame_fit_eecl, Components(*pdflist), LineStyle(1), LineColor(2), LineWidth(1) ); // total
  for( Int_t ipdf=0; ipdf<npdf; ipdf++ ){
    if( pdf_use[ipdf] && !pdf_fix[ipdf] ) pdf_tot->plotOn( frame_fit_eecl, Components(*pdf[ipdf]), LineStyle(2), LineColor(ipdf+3), LineWidth(1) );
  }
  pdf_tot   ->paramOn( frame_fit_eecl, Format("NELU", AutoPrecision(2)), Layout(0.40, 0.99, 0.99), ShowConstants(true) );
  frame_fit_eecl->Draw();

  can->cd(8);
  RooPlot* frame_fit_eecl_enh = eecl->frame();
  frame_fit_eecl_enh->SetTitle("E_{ECL} signal NB region");
  toy_mcdata->plotOn( frame_fit_eecl_enh, Binning(24),        MarkerColor(1), LineColor(1), LineWidth(1),        CutRange("signal_box_nb") ); // toy-data
  pdf_tot   ->plotOn( frame_fit_eecl_enh, Components(*pdflist), LineStyle(2), LineColor(1), LineWidth(1), ProjectionRange("signal_box_nb") ); // total
  for( Int_t ipdf=0; ipdf<npdf; ipdf++ ){
    if( pdf_use[ipdf] && !pdf_fix[ipdf] ) pdf_tot->plotOn( frame_fit_eecl_enh, Components(*pdf[ipdf] ), LineStyle(2), LineColor(ipdf+3), LineWidth(1), ProjectionRange("signal_box_nb") ); // sig // default
  }
  frame_fit_eecl_enh->Draw();
  */
  //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  // Iterative TOY MC
  std::cout << "*************************** Iterative TOY MC is started : " << iteration << " iterations "
	    << "***************************" << std::endl;
  for( Int_t ipdf=0; ipdf<npdf; ipdf++ ) yield[ipdf]->setVal( nexp*init[ipdf] );

  RooMCStudy* mcstudy = new RooMCStudy( *pdf_tot, *varset, Binned(true), Silence(true), Extended(true), FitOptions(Save(true),PrintEvalErrors(0),SumW2Error(roosumw2)) );
  //RooMCStudy* mcstudy = new RooMCStudy( *pdf_tot, *varset, Binned(true), Silence(true), Extended(true), FitOptions(Save(true),PrintEvalErrors(0),SumW2Error(roosumw2)),Minos(true) );
  mcstudy->generateAndFit( iteration );
  for( Int_t i=0; i<iteration; i++ ) mcstudy->fitResult(i)->Print();

  RooPlot* frame_toy_mean = mcstudy->plotParam( *yield[1], Bins(40) );
  RooPlot* frame_toy_err  = mcstudy->plotError( *yield[1], Bins(40) );
  RooPlot* frame_toy_pull = mcstudy->plotPull ( *yield[1], Bins(40), FitGauss(true) );
  RooPlot* frame_toy_nll  = mcstudy->plotNLL( Bins(40) );

  can->cd( 9); frame_toy_mean->Draw();
  can->cd(10); frame_toy_err ->Draw();
  can->cd(11); frame_toy_pull->Draw();
  can->cd(12); frame_toy_nll ->Draw();

  //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  std::stringstream sTmp;
  for( Int_t ipdf=0; ipdf<npdf; ipdf++ ) sTmp << pdf_fl[ipdf];

  can->Update();
  can->Print( Form("pic/2d_%s_sumw%d_%.2f_%s.eps",outfilename,(Int_t)roosumw2,nexp,sTmp.str().c_str()) );

  //+++++++++++++++++++++++++++++++++++++++++++++++++
  ///*
  TCanvas* can2 = Canvas( "can2","can2", 2, 1, 800, 800 );
  can2->Draw();
  can2->cd(1)->SetLogy();
  RooPlot* frame2_fit_nb_enh = nb->frame();
  frame2_fit_nb_enh->SetTitle("NB with signal E_{ECL} region");
  toy_mcdata->plotOn( frame2_fit_nb_enh, Binning(nbin_nb),        MarkerColor(1), LineColor(1), LineWidth(2),        CutRange("signal_box_eecl") ); // toy-data
  pdf_tot   ->plotOn( frame2_fit_nb_enh, Components(*pdflist), LineStyle(1), LineColor(2), LineWidth(2), ProjectionRange("signal_box_eecl") ); // total

  pdf_tot->plotOn( frame2_fit_nb_enh, Components(*pdf[1]), LineStyle(1), LineColor(1), LineWidth(1), ProjectionRange("signal_box_eecl") ); // sig
  pdf_tot->plotOn( frame2_fit_nb_enh, Components(*pdf[0]), LineStyle(1), LineColor(4), LineWidth(1), ProjectionRange("signal_box_eecl") ); // other
  pdf_tot->plotOn( frame2_fit_nb_enh, Components(*pdf[2]), LineStyle(1), LineColor(3), LineWidth(1), ProjectionRange("signal_box_eecl") ); // nor
  pdf_tot->plotOn( frame2_fit_nb_enh, Components(*pdf[3]), LineStyle(1), LineColor(5), LineWidth(1), ProjectionRange("signal_box_eecl") ); // D**
  toy_mcdata->plotOn( frame2_fit_nb_enh, Binning(nbin_nb),        MarkerColor(1), LineColor(1), LineWidth(1),        CutRange("signal_box_eecl") ); // toy-data

  frame2_fit_nb_enh->Draw();

  can2->cd(2);
  RooPlot* frame2_fit_eecl_enh = eecl->frame();
  frame2_fit_eecl_enh->SetTitle("E_{ECL} signal NB region");
  toy_mcdata->plotOn( frame2_fit_eecl_enh, Binning(24),        MarkerColor(1), LineColor(1), LineWidth(2),        CutRange("signal_box_nb") ); // toy-data
  pdf_tot   ->plotOn( frame2_fit_eecl_enh, Components(*pdflist), LineStyle(1), LineColor(2), LineWidth(2), ProjectionRange("signal_box_nb") ); // total

  pdf_tot->plotOn( frame2_fit_eecl_enh, Components(*pdf[1] ), LineStyle(1), LineColor(1), LineWidth(1), ProjectionRange("signal_box_nb") ); // sig
  pdf_tot->plotOn( frame2_fit_eecl_enh, Components(*pdf[0] ), LineStyle(1), LineColor(4), LineWidth(1), ProjectionRange("signal_box_nb") ); // other
  pdf_tot->plotOn( frame2_fit_eecl_enh, Components(*pdf[2] ), LineStyle(1), LineColor(3), LineWidth(1), ProjectionRange("signal_box_nb") ); // nor
  pdf_tot->plotOn( frame2_fit_eecl_enh, Components(*pdf[3] ), LineStyle(1), LineColor(5), LineWidth(1), ProjectionRange("signal_box_nb") ); // D**
  toy_mcdata->plotOn( frame2_fit_eecl_enh, Binning(24),        MarkerColor(1), LineColor(1), LineWidth(1),        CutRange("signal_box_nb") ); // toy-data
  frame2_fit_eecl_enh->Draw();
  //*/
  //+++++++++++++++++++++++++++++++++++++++++++++++++
  std::cout << "finish" << std::endl;
  if( !gROOT->IsBatch() ) app.Run();

  return 0;

}
