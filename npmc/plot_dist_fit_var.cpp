#include "draws_.h"

//NeuroBayes
#include "NeuroBayesTeacher.hh"
#include "NeuroBayesExpert.hh"

// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
/*
const Int_t nfile = 5;
const Char_t* model      = "2HDMII";
const Char_t* param_name = "tan#beta/m_{H^{+}}";
const Char_t* param_unit = "[GeV^{-1}]";
const Double_t param  [nfile] = {  0.0,   0.3,   0.5,   0.7,  1.0  };
const Char_t*  tagdir [nfile] = { "0p0", "0p3", "0p5", "0p7","1p0" };
const Int_t    col    [nfile] = {    1,     3,     4,     2,    5  };
*/
/* R2 LQ
const Int_t nfile = 5;
const Char_t* model      = "R2LQ";
const Char_t* param_name = "C_{T}";
const Char_t* param_unit = "";
const Double_t param  [nfile] = {  -0.150,      0.000,      0.180,      0.340,     0.400     };
const Char_t*  tagdir [nfile] = { "R2_m0p150", "R2_0p000", "R2_0p180", "R2_0p340","R2_0p400" };
const Int_t    col    [nfile] = {       3,          1,          4,          2,         5     };
*/
///* S1 LQ
const Int_t nfile = 5;
const Char_t* model      = "S1LQ";
const Char_t* param_name = "C_{T}";
const Char_t* param_unit = "";
const Double_t param  [nfile] = {  -0.150,      0.000,      0.180,      0.260,     0.400     };
const Char_t*  tagdir [nfile] = { "S1_m0p150", "S1_0p000", "S1_0p180", "S1_0p260","S1_0p400" };
const Int_t    col    [nfile] = {       3,          1,          4,          2,         5     };
//*/

// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

TChain** c     = new TChain*[nfile];
TTree**  c_cut = new TTree* [nfile];
const Char_t* indir = "/home/belle/syutaro/dstrtaunu/modules/np_dstrtaunu_gen/hbk/";
const Char_t* treename = "h37";
//const Char_t* selection = "(dec_d==2||dec_d==4||dec_d==5) && (dec_tau==1||dec_tau==2)";
const Char_t* selection = "(dec_d==4) && (dec_tau==1||dec_tau==2)";

Expert* nb = new Expert( "/gpfs/home/belle/syutaro/dstrtaunu/ana/NB/info/nb_mode0_test13_nor.nb" );
Float_t nnInput[3];
// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
THStack* MakeHist( const Int_t xbin,   const Double_t xmin,  const Double_t xmax,
		   const Char_t* name, const Char_t* title,  const Char_t* axisname, const Char_t* brname,
		   const Char_t* selection ){
  THStack* mh = new THStack();
  mh->SetTitle( title );
  TH1D** hist = new TH1D*[nfile];
  for( Int_t ic=0; ic<nfile; ic++ ){
    hist[ic] = new TH1D( Form("%s_%.2f",name,param[ic]), title, xbin, xmin, xmax );
    c_cut[ic]->Project( Form("%s_%.2f",name,param[ic]), brname, selection );
    hist[ic]->SetLineColor( col[ic] );
    hist[ic]->Scale(1.0/hist[ic]->Integral());
    hist[ic]->SetMinimum(0.0);
    mh->Add( hist[ic] );
  }
  Bool_t tmp = gROOT->IsBatch();

  gROOT->SetBatch(true);
  mh->Draw("nostack");
  mh->GetXaxis()->SetTitle(axisname);
  gROOT->SetBatch(tmp);
  return mh;
}

// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
THStack* MakeHistNB( const Int_t xbin,   const Double_t xmin,  const Double_t xmax,
		     const Char_t* name, const Char_t* title,  const Char_t* axisname, const Char_t* brname,
		     const Char_t* selection ){
  THStack* mh = new THStack();
  mh->SetTitle( title );
  TH1D** hist = new TH1D*[nfile];
  for( Int_t ic=0; ic<nfile; ic++ ){
    hist[ic] = new TH1D( Form("%s_%.2f",name,param[ic]), title, xbin, xmin, xmax );

    for( Int_t ievt=0; ievt<c_cut[ic]->GetEntries(); ievt++ ){
      c_cut[ic]->GetEntry(ievt);
      Double_t mmiss  = c_cut[ic]->GetLeaf("mmiss2")->GetValue();
      Double_t evis   = c_cut[ic]->GetLeaf("evis2" )->GetValue();
      Double_t cosdll = c_cut[ic]->GetLeaf("cosdll")->GetValue();
      nnInput[0] = pow(mmiss,3)/fabs(mmiss);
      nnInput[1] = cosdll;
      nnInput[2] = evis;
      Double_t nbout = nb->nb_expert(nnInput);
      hist[ic]->Fill( nbout );
    }

    hist[ic]->SetLineColor( col[ic] );
    hist[ic]->Scale(1.0/hist[ic]->Integral());
    hist[ic]->SetMinimum(0.0);
    mh->Add( hist[ic] );
  }
  Bool_t tmp = gROOT->IsBatch();

  gROOT->SetBatch(true);
  mh->Draw("nostack");
  mh->GetXaxis()->SetTitle(axisname);
  gROOT->SetBatch(tmp);
  return mh;
}
// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Int_t main( Int_t argc, Char_t** argv ){
  //gROOT->SetBatch(true); // tmpppppp
  TApplication app( "app", &argc, argv );
  TStyle* sty = Style(10);
  sty->SetOptStat(0);
// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++  
  for( Int_t ic=0; ic<nfile; ic++ ){
    c[ic] = new TChain(treename);
    std::cout << param_name    << " = "
	      << std::setw( 7) << Form( "%.2f ",param[ic] )
	      << param_unit    << " : ";
    std::cout << std::setw( 5) << std::right << c[ic]->Add( Form("%s/%s_double/*.root",indir, tagdir[ic]) ) << " files : ";
    std::cout << std::setw(10) << std::right << c[ic]->GetEntries()                                         << " events -> ";
    c_cut[ic] = c[ic]->CopyTree( selection );
    std::cout << c_cut[ic]->GetEntries() << " entries" << std::endl;  
  }

  //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  THStack* hist_evis   = MakeHist  ( 100,  5.0, 11.0, "evis",   "E_{vis}",                  "E_{vis} [GeV]",            "evis2",                            "evis2>-1 && (dec_d==4||dec_d==5) && (dec_tau==1||dec_tau==2)" );
  THStack* hist_mmiss  = MakeHist  ( 100, -3.0, 25.0, "mmiss",  "M_{miss}^{2}",             "M_{miss}^{2} [GeV^{2}]",   "mmiss2*mmiss2*mmiss2/abs(mmiss2)", "evis2>-1 && (dec_d==4||dec_d==5) && (dec_tau==1||dec_tau==2)" );
  THStack* hist_cosdll = MakeHist  ( 100, -1.8,  1.8, "cosdll", "cos#theta_{B-D*l}^{low}",  "cos#theta_{B-D*l}^{low}",  "atan(cosdll)",                     "evis2>-1 && (dec_d==4||dec_d==5) && (dec_tau==1||dec_tau==2)" );
  THStack* hist_nb     = MakeHistNB(  30, -1.0,  1.0, "NB",     "NB",                       "NB",                       "nb_mode0_test13_nor",              "evis2>-1 && (dec_d==4||dec_d==5) && (dec_tau==1||dec_tau==2)" );

  //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  // <CANVAS>
  TCanvas* can1 = Canvas( "can1","can1", 2,2 );
  can1->Draw();

  TLegend* leg = new TLegend( 0.45,0.72,0.85,0.94 );
  for( Int_t ic=0; ic<nfile; ic++ ) leg->AddEntry( (hist_evis->GetHists())->At(ic), Form("%s = %.2f %s", param_name,param[ic],param_unit), "L" );

  can1->cd(1); hist_evis  ->Draw("nostack");
  can1->cd(2); hist_mmiss ->Draw("nostack");
  can1->cd(3); hist_cosdll->Draw("nostack");
  can1->cd(4); hist_nb    ->Draw("nostack");

  can1->cd(1); leg->Draw();

  can1->Print( Form("pic/plot_dist_fit_var_%s_1.eps",model) );
  
  std::cout << "finish" << std::endl;
  if( !gROOT->IsBatch() ) app.Run();

  return 0;
}
