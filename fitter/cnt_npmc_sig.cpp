#include "draws_.h"
#include "draws_fit_.h"

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
const Char_t* selection = "self==1 && eecl < 1.2";
const Int_t    nfile          = 11;
const Double_t tanb_mh[nfile] = {  0.0,   0.1,   0.2,   0.3,   0.4,   0.5,   0.6,   0.7,   0.8,   0.9,   1.0  };
const Char_t*  tagdir [nfile] = { "0p0", "0p1", "0p2", "0p3", "0p4", "0p5", "0p6", "0p7", "0p8", "0p9", "1p0" };
const Char_t*  infile_sigmc   = "/home/belle/syutaro/dstrtaunu/modules/dstrtaunu/hbk/0p0_weight_nb_cut/*.root";
const Char_t*  weight_table   = "../npmc/table/dstrtaunu_lep_20_all/est_weight.root";
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
Int_t main( Int_t argc, Char_t** argv ){
  //gROOT->SetBatch(true); // tmpppppp
  TApplication app( "app", &argc, argv );
  TStyle* sty = Style(1);
  sty->SetTitleOffset(1.0,"z");
  //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  Read_Data( calib_file, true );

  //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  TChain* c = new TChain(treename);
  std::cout << "[selection] " << selection    << std::endl;
  std::cout << "[ infile  ] " << infile_sigmc << std::endl;
  std::cout << c->Add(infile_sigmc)  << " files, ";
  std::cout << c->GetEntries()                             << " entries -> ";
  TTree* c_cut = c->CopyTree( selection );
  std::cout << c_cut->GetEntries() << " entries" << std::endl;

  //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  TFile* npweight_file = new TFile( weight_table );
  if( npweight_file->IsZombie() ) std::cerr << "[ABORT] can not find weight-file for " << weight_table << std::endl, abort();
  TGraphErrors** npweight_table = new TGraphErrors*[nfile];
  for( Int_t ifile=0; ifile<nfile; ifile++ ){
    npweight_table[ifile] = (TGraphErrors*)npweight_file->Get( Form( "np_%s",tagdir[ifile]) );
    if( npweight_table==NULL ) std::cerr << "[ABORT] can not find weight-table for " << tagdir[ifile] << std::endl, abort();
  }


  Double_t** nweight = new Double_t*[nfile];
  for( Int_t ifile=0; ifile<nfile; ifile++ ){
    nweight[ifile] = new Double_t[npweight_table[ifile]->GetN()];
    for( Int_t i=0; i<npweight_table[ifile]->GetN(); i++ ){
      nweight[ifile][i] = 0;
    }
  }
  
  //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  Double_t nsig [nfile] = {0.0};
  //Double_t nsigE[nfile] = {0.0}; ////////////
  for( Int_t ievt=0; ievt<c_cut->GetEntries(); ievt++ ){
    c_cut->GetEntry(ievt);
    Double_t weight = cal_weight( c_cut, ievt, 1.0 );
    Double_t val[np::nvar];
    for( Int_t ivar=0; ivar<np::nvar; ivar++ ) val[ivar] = c_cut->GetLeaf(np::brname[ivar])->GetValue(); // reproduce NP distribution by re-weighted SM distribution
    Int_t gindex = getGIndex( val );
    for( Int_t ifile=0; ifile<nfile; ifile++ ){
      Double_t npweight  = npweight_table[ifile]->GetY()[gindex];
      Double_t npweightE = npweight_table[ifile]->GetErrorY(gindex);
      nsig[ifile] += (weight*npweight);
      nweight[ifile][gindex] += weight;
      //nsigE[ifile] += pow(npweightE,2); //////
    }
  }

  for( Int_t ifile=0; ifile<nfile; ifile++ ) std::cout << ifile << ": nsig = " << nsig[ifile] << std::endl;

  //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

  TGraphErrors* eff = new TGraphErrors();
  eff->SetName("eff");
  eff->SetTitle("eff");
  eff->GetXaxis()->SetTitle("tan#beta/m_{H^{+}} [GeV^{-1}]");
  eff->GetYaxis()->SetTitle("#epsilon/#epsilon^{SM}");
  eff->SetMinimum(0.80);
  eff->SetMaximum(1.20);
  for( Int_t ifile=0; ifile<nfile; ifile++ ){
    Double_t ratio  = nsig[ifile]/nsig[0];
    //Double_t ratioE = ratio * sqrt(  1.0/nsig[ifile] + 1.0/nsig[0] );
    //Double_t ratioE = sqrt( nsigE[ifile] )/nsig[0];
    Double_t ratioE = 0;
    for( Int_t i=0; i<npweight_table[ifile]->GetN(); i++ ){
      //ratioE += pow(npweight_table[ifile]->GetY()[i]*sqrt(nweight[ifile][i]),2) + pow(npweight_table[ifile]->GetErrorY(i)*nweight[ifile][i],2);
      ratioE += pow(npweight_table[ifile]->GetErrorY(i)*nweight[ifile][i],2);
    }
    ratioE = sqrt(ratioE)/nsig[0];

    std::cout << ifile << ": ratioE = " << ratioE << std::endl;
    
    eff->SetPoint     ( eff->GetN(),   tanb_mh[ifile], ratio  );
    eff->SetPointError( eff->GetN()-1,            0.0, ratioE );
  }
  eff->Sort();
  eff->Print();

  //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  TCanvas* can = Canvas( "can","can" );
  can->Draw();
  eff->Draw("APL");
  can->Update();
  can->Print("pic/cnt_npmc_sig.eps");
  //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  std::cout << "finish" << std::endl;
  if( !gROOT->IsBatch() ) app.Run();

  return 0;

}
