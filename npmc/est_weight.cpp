#include "draws_.h"
#include "draws_np_.h"

const Bool_t fl_message = true;
//const Char_t* selection = "(dec_d<2) && (dec_tau==1||dec_tau==2)";                      // D          tau(lep) nu : "should change L.100 in draws_np_.h"
const Char_t* selection = "(dec_d==2||dec_d==4||dec_d==5) && (dec_tau==1||dec_tau==2)"; // D*(Dpi)    tau(lep) nu
//const Char_t* selection = "(dec_d==3||dec_d==6) && (dec_tau==1||dec_tau==2)";           // D*(Dgamma) tau(lep) nu
//const Char_t* selection = "(dec_d==2||dec_d==4||dec_d==5) && (dec_tau==3)"; // D*(Dpi)    tau(pi ) nu
//const Char_t* selection = "(dec_d==3||dec_d==6) && (dec_tau==3)";           // D*(Dgamma) tau(pi ) nu
//const Char_t* selection = "(dec_d==2||dec_d==4||dec_d==5) && (dec_tau==4)"; // D*(Dpi)    tau(rho) nu
//const Char_t* selection = "(dec_d==3||dec_d==6) && (dec_tau==4)";           // D*(Dgamma) tau(rho) nu

// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
TChain** c     = new TChain*[nfile];
TTree**  c_cut = new TTree* [nfile];
const Char_t* indir = "/home/belle/syutaro/dstrtaunu/modules/np_dstrtaunu_gen/hbk/";
const Char_t* treename = "h37";
// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Int_t main( Int_t argc, Char_t** argv ){
  gROOT->SetBatch(true); // tmpppppp
  TApplication app( "app", &argc, argv );
  TStyle* sty = Style(10);
  sty->SetPadGridY(1);
  sty->SetOptStat(0);

  if( !(app.Argc()==4) )
    std::cerr << "Wrong input" << std::endl
	      << "Usage : " << app.Argv(0)
	      << " (int)fl_index (int)bin_start (int)nbin" << std::endl, abort();
  Int_t  fl_index = atoi(app.Argv(1));
  Int_t  fl_sbin  = atoi(app.Argv(2));
  Int_t  fl_nbin  = atoi(app.Argv(3));
  

  std::cout << "[selection] " << selection << std::endl;
  std::cout << "[bin] " << fl_index
	    << " : "    << fl_sbin
	    << " -> "   << fl_sbin + fl_nbin << std::endl;

  // ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  for( Int_t ifile=0; ifile<nfile; ifile++ ){
    c[ifile] = new TChain(treename);
    std::cout << param_name    << " = "
	      << std::setw( 7) << Form( "%.2f ",param[ifile] )
	      << param_unit    << " : ";
    std::cout << std::setw( 5) << std::right << c[ifile]->Add( Form("%s/%s/*set*.root",indir, tagdir[ifile]) ) << " files : ";
    std::cout << std::setw(10) << std::right << c[ifile]->GetEntries()                                         << " events -> ";
    c_cut[ifile] = c[ifile]->CopyTree( selection );
    std::cout << c_cut[ifile]->GetEntries() << " entries" << std::endl;
  }

  // +++++++++++++++++++++++++
  Int_t ntotbin = 1;
  for( Int_t ivar=0; ivar<nvar; ivar++ ) ntotbin *= nbin[ivar];
  Double_t* nevt   [nfile];
  Double_t* weight [nfile];
  Double_t* weightE[nfile];
  for( Int_t ifile=0; ifile<nfile; ifile++ ){
    nevt   [ifile] = new Double_t[ntotbin];
    weight [ifile] = new Double_t[ntotbin];
    weightE[ifile] = new Double_t[ntotbin];
  }

  // ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  std::stringstream sTmp;
  for( Int_t ifile=0; ifile<nfile; ifile++ ){
    //for( Int_t ibin=0; ibin<ntotbin; ibin++ ){
    if( fl_message ) std::cout << "************ ifile == " << ifile << " : " << tagdir[ifile] << " ***************" << std::endl;
    for( Int_t ibin=fl_sbin; ibin<fl_sbin+fl_nbin; ibin++ ){
      if( ibin >= ntotbin ) break;
      nevt[ifile][ibin] = c_cut[ifile]->GetEntries( Form("%s", makeCut_np(ibin,fl_message).c_str()) );
      if( fl_message ) std::cout << std::setw(7) << std::right << nevt[ifile][ibin] << std::endl;
    }
  }

  // ++++++++++++++++++++++++++++++++++++++++++++
  for( Int_t ifile=0; ifile<nfile; ifile++ ){
    //for( Int_t ibin=0; ibin<ntotbin; ibin++ ){
    for( Int_t ibin=fl_sbin; ibin<fl_sbin+fl_nbin; ibin++ ){
      if( ibin >= ntotbin ) break;
      if( ifile==0 ){
	weight [ifile][ibin] = 1.0;
	weightE[ifile][ibin] = 0.0;
      }else{
	weight [ifile][ibin] = (  nevt[0][ibin]==0                          ? 1.0 : nevt[ifile][ibin]/nevt[0][ibin]                                         );
	weightE[ifile][ibin] = ( (nevt[0][ibin]==0 || nevt[ifile][ibin]==0) ? 1.0 : weight[ifile][ibin] * sqrt( 1.0/nevt[0][ibin] + 1.0/nevt[ifile][ibin] ) );
	if( nevt[0][ibin]==0 && nevt[ifile][ibin]!=0 ) std::cout << "[WARNING] bin = "
								 << ibin              << ", "
								 << tagdir[ifile]     << ", "
								 << nevt[ifile][ibin] << " / "
								 << nevt[    0][ibin] << std::endl;
      }
      if( fl_message ) std::cout << ibin << " : " << weight[ifile][ibin] << " +- " << weightE[ifile][ibin] << std::endl;
    }
  }

  TLegend*       leg   = new TLegend( 0.55,0.75,0.99,0.94 );
  TGraphErrors** graph = new TGraphErrors*[nfile];
  TMultiGraph*   mg    = new TMultiGraph();
  mg->SetTitle( Form("%s;Index;Weight factor (NP/SM)",selection) );
  mg->SetMinimum(0.0);
  for( Int_t ifile=0; ifile<nfile; ifile++ ){
    graph[ifile] = new TGraphErrors();
    graph[ifile]->SetMarkerColor(ifile+1);
    graph[ifile]->SetLineColor  (ifile+1);
    graph[ifile]->SetName( Form("np_%s",tagdir[ifile]) );
    //for( Int_t ibin=0; ibin<ntotbin; ibin++ ){
    for( Int_t ibin=fl_sbin; ibin<fl_sbin+fl_nbin; ibin++ ){
      if( ibin >= ntotbin ) break;
      graph[ifile]->SetPoint     ( graph[ifile]->GetN(),   ibin, weight [ifile][ibin] );
      graph[ifile]->SetPointError( graph[ifile]->GetN()-1,  0.0, weightE[ifile][ibin] );
    }
    leg->AddEntry( graph[ifile], Form("%s = %.2f %s", param_name,param[ifile],param_unit), "PL" );
    graph[ifile]->Sort();
    mg->Add( graph[ifile] );
  }
  
  TCanvas* can = Canvas( "can", "can" );
  can->Draw();
  mg->Draw("AP");
  leg->Draw();

  can->Update();
  //can->Print   ( Form("pic/est_weight_%d.eps", fl_index) );
  TFile outfile( Form("pic/est_weight_%d.root",fl_index), "RECREATE" );
  can->Write();
  for( Int_t ifile=0; ifile<nfile; ifile++ ) graph[ifile]->Write();
  outfile.Close();
  
  // ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  std::cout << "finish" << std::endl;
  if( !gROOT->IsBatch() ) app.Run();

  return 0;
}
