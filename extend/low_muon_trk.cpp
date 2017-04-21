#include "draws_.h"

const Char_t* infile = "/home/belle/syutaro/dstrtaunu/modules/dstrtaunu/hbk/mixed/gMC_*s0[0-9]*.root";
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
const Int_t nhist = 2;
const Char_t* com_sel = "rm_l1==1 && l1p < 0.7";
const Char_t* selection[nhist] = { "abs(l1selfid)==13",
				   "abs(l1selfid)==211" };
const Char_t* ctgry_name[nhist] = { "#mu track", "#pi track" };

//++++++++++++++
const Int_t nvar  = 4;
const Char_t*  brname [nvar]   = {            "l1p", "mu1e9e25",  "mu1ecl",                "mu1ewid" };
const Char_t* axisname[nvar]   = { "Momentum [GeV]",   "E9/E25", "E [GeV]", "Shower Width (rms)[cm]" };
const Int_t    xbin[nvar]      = {  50,  50,  50,   50 };
const Double_t xmin[nvar]      = { 0.0, 0.0, 0.0,  0.0 };
const Double_t xmax[nvar]      = { 1.0, 1.0, 0.6, 10.0 };

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
Int_t main( Int_t argc, Char_t** argv ){
  //gROOT->SetBatch(true); // tmpppppp
  TApplication app( "app", &argc, argv );
  TStyle* sty = Style();
  sty->SetOptStat(0);
  sty->SetPadBottomMargin(0.16);

  //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  TChain* c = new TChain("h15");
  std::cout << "[infile] " << infile << " : ";
  std::cout << c->Add(infile)  << " files, ";
  std::cout << c->GetEntries() << " entries"
	    << std::endl;
  
  //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  Double_t ymax[nvar] = {0};
  TH1D*** hist = new TH1D**[nhist]; // [hist][var]
  for( Int_t ihist=0; ihist<nhist; ihist++ ){
    hist[ihist] = new TH1D*[nvar];
    for( Int_t ivar=0; ivar<nvar; ivar++ ){
      hist[ihist][ivar] = new TH1D( Form("h%d_%d",ihist,ivar), Form("%s (%s)",brname[ivar],com_sel), xbin[ivar], xmin[ivar], xmax[ivar] );
      c->Project( Form("h%d_%d",ihist,ivar), brname[ivar], Form("(%s)&&(%s)",com_sel,selection[ihist]) );
      hist[ihist][ivar]->SetXTitle( axisname[ivar] );
      hist[ihist][ivar]->SetLineColor(ihist+1);
      if( hist[ihist][ivar]->GetMaximum() > ymax[ivar] ) ymax[ivar] = hist[ihist][ivar]->GetMaximum();
    }
  }

  for( Int_t ihist=0; ihist<nhist; ihist++ ){
    for( Int_t ivar=0; ivar<nvar; ivar++ ){
      hist[ihist][ivar]->SetMaximum( ymax[ivar] );
    }
  }

  
  //++++++++++++++
  TCanvas* can = Canvas( "can","can", nvar );
  can->Draw();
  for( Int_t ivar=0; ivar<nvar; ivar++ ){
    can->cd(ivar+1);
    for( Int_t ihist=0; ihist<nhist; ihist++ ){
      hist[ihist][ivar]->DrawNormalized( ihist ? "same" : "" );
    }
  }
  TLegend* leg = new TLegend( 0.20,0.60,0.50,0.85 );
  for( Int_t ihist=0; ihist<nhist; ihist++ ) leg->AddEntry( hist[ihist][0], ctgry_name[ihist], "L" );
  can->cd(1);
  leg->Draw();

  //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  can->Print("pic/low_muon_trk.eps");
  std::cout << "finish" << std::endl;
  app.Run();
  return 0;
}
