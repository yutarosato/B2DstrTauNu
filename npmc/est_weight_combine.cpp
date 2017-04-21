#include "draws_.h"
#include "draws_np_.h"

Int_t main( Int_t argc, Char_t** argv ){
  //gROOT->SetBatch(true); // tmpppppp
  TApplication app( "app", &argc, argv );
  TStyle* sty = Style(10);
  sty->SetPadGridY(1);
  sty->SetOptStat(0);
  sty->SetMarkerStyle(1);
  sty->SetPadTopMargin   (0.10);
  sty->SetPadRightMargin (0.07);


  if( !(app.Argc()==2) )
    std::cerr << "Wrong input" << std::endl
	      << "Usage : " << app.Argv(0)
	      << " (int)fl_nfile" << std::endl, abort();
  Int_t  fl_infile = atoi(app.Argv(1));
  
  std::cout << "[nfile] " << fl_infile << std::endl;
  // ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  TGraphErrors** graph = new TGraphErrors*[nfile];
  for( Int_t ifile=0; ifile<nfile; ifile++ ){
    graph[ifile] = new TGraphErrors();
    graph[ifile]->SetName( Form("np_%s",tagdir[ifile]) );
  }
  // ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
      
  for( Int_t i=0; i<fl_infile; i++ ){
    TFile* file = new TFile( Form("pic/est_weight_%d.root", i) );
    if( file->IsZombie() ) std::cerr << "[ABORT] can not find file : " << i << std::endl, abort();
    TGraphErrors** tmp_graph = new TGraphErrors*[nfile];
    for( Int_t ifile=0; ifile<nfile; ifile++ ){
      tmp_graph[ifile] = (TGraphErrors*)file->Get( Form("np_%s",tagdir[ifile]) );
      if( tmp_graph[ifile]==NULL ) std::cerr << "[ABORT] can not find TGraphErrors : " << tagdir[ifile] << std::endl, abort();

      for( Int_t ip=0; ip<tmp_graph[ifile]->GetN(); ip++ ){
	graph[ifile]->SetPoint     ( graph[ifile]->GetN()  , tmp_graph[ifile]->GetX()[ip], tmp_graph[ifile]->GetY()[ip]    );
	graph[ifile]->SetPointError( graph[ifile]->GetN()-1,                          0.0, tmp_graph[ifile]->GetErrorY(ip) );
      }
      delete tmp_graph[ifile];
    }
    delete tmp_graph;
    file->Close();
    delete file;

  }
  // +++++++++++++++++++++++++++++++++++++++++++
  TLegend*    leg = new TLegend( 0.55,0.70,0.80,0.88 );
  TMultiGraph* mg = new TMultiGraph();
  mg->SetTitle( ";Index;Weight factor (NP/SM)" );
  for( Int_t ifile=0; ifile<nfile; ifile++ ){
    std::cout << ifile << " : " << graph[ifile]->GetN() << std::endl;
    graph[ifile]->Sort();
    graph[ifile]->SetMarkerColor(ifile+1);
    graph[ifile]->SetLineColor  (ifile+1);
    mg->Add( graph[ifile] );
    leg->AddEntry( graph[ifile], Form("%s = %.2f %s", param_name,param[ifile],param_unit), "PL" );
  }

  // ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  TCanvas* can = Canvas( "can", "can", 1, 1, 1500, 700 );
  can->Draw();
  mg->Draw("AP");
  leg->Draw();

  can->Update();
  can->Print   ( "pic/est_weight.eps" );
  TFile outfile( "pic/est_weight.root", "RECREATE" );
  can->Write();
  for( Int_t ifile=0; ifile<nfile; ifile++ ) graph[ifile]->Write();
  outfile.Close();

  // ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  system("rm -f pic/est_weight_*.root");
  std::cout << "finish" << std::endl;
  if( !gROOT->IsBatch() ) app.Run();

  return 0;
}
