#include "draws_.h"
#include "draws_roofit_.h"

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
const Char_t*  brname         = "eecl";
//const Int_t    nhist          = 2;
const Int_t    nhist          = 4;
const Char_t*  selection      = "(dst1self!=1||dst2self!=1)";
//const Double_t nb_th[nhist+1] = {-1.0, 0.0, 1.0};
const Double_t nb_th[nhist+1] = {-1.0, -0.9, -0.8, -0.7, -0.6};
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
const Char_t*  infile_gmc   = "/home/belle/syutaro/dstrtaunu/modules/dstrtaunu/hbk/merge_cut_nb_bcs_vtx/gMC_mixed_*s0[0-5]*.root";
const Int_t    nstream      = 6;
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
const Int_t    xbin =  24;
const Double_t xmin = 0.0;
const Double_t xmax = 1.2;
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
Int_t main( Int_t argc, Char_t** argv ){

  TApplication app( "app", &argc, argv );
  TStyle* sty = Style();
  sty->SetOptStat(0);
  //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  TChain* c = new TChain("h15");
  std::cout << "[infile gMC] " << infile_gmc << " : ";
  std::cout << c->Add(infile_gmc)            << " files, ";
  std::cout << c->GetEntries()               << " entries, ";
  std::cout << nstream                       << " streams" << std::endl;

  //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  TCanvas* can = Canvas( "can","can", 2, 2 );
  can->Draw();

  //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  TLegend* leg  = new TLegend( 0.55,0.65,0.99,0.94 );
  THStack* mh   = new THStack( "mh", Form("%s;E_{ECL} [GeV]",selection) );
  TH1D**   hist = new TH1D*[nhist];
  TF1**    func = new TF1* [nhist]; 
  for( Int_t ihist=0; ihist<nhist; ihist++ ){
    hist[ihist] = new TH1D( Form("h%d",ihist), Form("h%d",ihist), xbin, xmin, xmax );
    c->Project( Form("h%d",ihist), brname, Form("((%s)&&%.2f<nb_mode0_test13_nor&&nb_mode0_test13_nor<%.2f)",selection,nb_th[ihist], nb_th[ihist+1]) );
    hist[ihist]->Sumw2();
    hist[ihist]->Scale(1.0/nstream);
    mh->Add( hist[ihist] );
    std::cout << std::setw(3) << std::right << ihist          << " : "
	      << std::setw(7) << std::right << nb_th[ihist]   << " < NB < "
	      << std::setw(7) << std::right << nb_th[ihist+1] << " : "
	      << std::setw(8) << std::right << hist [ihist]->Integral()  << std::endl;
    func[ihist] = new TF1( Form("f%d",ihist), "[0]*x*x+1.0", xmin, xmax );
    func[ihist]->SetParameter( 0, 0.0 );
  }

  //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  can->cd(1);
  for( Int_t ihist=0; ihist<nhist; ihist++ ){
    hist[ihist]->SetMarkerColor(ihist+1);
    hist[ihist]->SetLineColor  (ihist+1);
  }
  mh->DrawClone("nostack histE");
  for( Int_t ihist=0; ihist<nhist; ihist++ ) leg->AddEntry( hist[ihist], Form("%.2f < NB < %.2f", nb_th[ihist], nb_th[ihist+1]), "PL" );
  leg->Draw();

  //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  can->cd(2);
  for( Int_t ihist=0; ihist<nhist; ihist++ ) hist[ihist]->Scale( 1.0/hist[ihist]->Integral() );
  mh->DrawClone("nostack histE");

  //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

  can->Print("pic/ck_correlation.eps");
  std::cout << "finish" << std::endl;
  app.Run();
  return 0;
}
