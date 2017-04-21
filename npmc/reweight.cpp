#include "draws_.h"
#include "draws_np_.h"

const Bool_t fl_message = !true;
//const Char_t* selection   = "(dec_d<2) && (dec_tau==1||dec_tau==2)";       // D tau(lep) nu
//const Char_t* weight_file = "table/dtaunu_dpi_lep_12_all/est_weight.root"; // D tau(lep) nu
const Char_t* selection   = "(dec_d==4||dec_d==5) && (dec_tau==1||dec_tau==2)"; // D*(Dpi) tau(lep) nu
//const Char_t* weight_file = "table/dstrtaunu_dpi_lep_12_all/est_weight.root";   // D*(Dpi) tau(lep) nu
const Char_t* weight_file = "pic/est_weight.root";   // D*(Dpi) tau(lep) nu
//const Char_t* selection   = "(dec_d==3||dec_d==6) && (dec_tau==1||dec_tau==2)";  // D*(Dgamma) tau(lep) nu
//const Char_t* weight_file = "table/dstrtaunu_dgamma_lep_12_all/est_weight.root"; // D*(Dgamma) tau(lep) nu
//const Char_t* selection   = "(dec_d==4||dec_d==5) && (dec_tau==3)";            // D*(Dpi) tau(pi) nu
//const Char_t* weight_file = "table/dstrtaunu_dpi_pi_8_all/est_weight.root";   // D*(Dpi) tau(pi) nu
//const Char_t* selection   = "(dec_d==3||dec_d==6) && (dec_tau==3)";             // D*(Dgamma) tau(pi) nu
//const Char_t* weight_file = "table/dstrtaunu_dgamma_pi_8_all/est_weight.root"; // D*(Dgamma) tau(pi) nu
//const Char_t* selection   = "(dec_d==4||dec_d==5) && (dec_tau==4)";            // D*(Dpi) tau(rho) nu
//const Char_t* weight_file = "table/dstrtaunu_dpi_rho_12_all/est_weight.root";  // D*(Dpi) tau(rho) nu
//const Char_t* selection   = "(dec_d==3||dec_d==6) && (dec_tau==4)";              // D*(Dgamma) tau(rho) nu
//const Char_t* weight_file = "table/dstrtaunu_dgamma_rho_12_all/est_weight.root"; // D*(Dgamma) tau(rho) nu

const Int_t nbin2[nvar] = {nbin[0], nbin[1], nbin[2], nbin[3]};
//const Int_t nbin2[nvar] = {20, 20, 20, 20};

const Int_t    nvar_fit = 4;        //mmiss, cos, evis, nb
const Int_t    nbin_fit    [nvar] = {   30,   30,    30, 30 };
const Double_t xmin_fit    [nvar] = { -2.0, -1.6,   4.0, -1.0 };
const Double_t xmax_fit    [nvar] = { 27.0,  1.6,  11.0,  1.0 };
const Char_t*  brname_fit  [nvar] = { "mmiss2", "cosdl1","evis2", "q2"}; // fourth component name is dummy
const Char_t*  axisname_fit[nvar] = { "M_{miss}^{2} [GeV^{2}]", "atan(cos#theta_{B-D*l})", "E_{vis} [GeV]", "NB" };

// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
TChain** c     = new TChain*[nfile];
TTree**  c_cut = new TTree* [nfile];
const Char_t* indir = "/home/belle/syutaro/dstrtaunu/modules/np_dstrtaunu_gen/hbk/";
const Char_t* treename = "h37";
// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  Expert* nb = new Expert( "/gpfs/home/belle/syutaro/dstrtaunu/ana/NB/info/nb_mode0_test13_nor.nb" );
  Float_t nnInput[3];

// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Int_t main( Int_t argc, Char_t** argv ){
  gROOT->SetBatch(true); // tmpppppp
  TApplication app( "app", &argc, argv );
  TStyle* sty = Style(10);
  sty->SetOptStat(0);
  sty->SetMarkerStyle(1);
  std::cout << "[selection] " << selection << std::endl;

  // ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

  for( Int_t ifile=0; ifile<nfile; ifile++ ){
    c    [ifile] = new TChain(treename);
    std::cout << param_name    << " = "
	      << std::setw( 7) << Form( "%.2f ",param[ifile] )
	      << param_unit    << " : ";
    std::cout << std::setw( 5) << std::right << c[ifile]->Add( Form("%s/%s_double/*set*.root",indir, tagdir[ifile]) ) << " files : ";
    std::cout << std::setw(10) << std::right << c[ifile]->GetEntries()                                                << " events -> ";
    c_cut[ifile] = c[ifile]->CopyTree( selection );
    std::cout << c_cut[ifile]->GetEntries() << " entries" << std::endl;
  }

  // +++++++++++++++++++++++++
  Int_t ntotbin = 1;
  for( Int_t ivar=0; ivar<nvar; ivar++ ) ntotbin *= nbin[ivar];
  Int_t** nevt_sysE    [nfile][nvar];
  Int_t** nevt_fit_sysE[nfile][nvar];

  for( Int_t ifile=0; ifile<nfile; ifile++ ){

    for( Int_t ivar=0; ivar<nvar; ivar++ ){
      nevt_sysE[ifile][ivar] = new Int_t*[nbin2[ivar]];
      for( Int_t ibin=0; ibin<nbin2[ivar]; ibin++ ){
	nevt_sysE[ifile][ivar][ibin] = new Int_t[ntotbin];
      }
    }

    for( Int_t ivar=0; ivar<nvar_fit; ivar++ ){
      nevt_fit_sysE[ifile][ivar] = new Int_t*[nbin_fit[ivar]];
      for( Int_t ibin=0; ibin<nbin_fit[ivar]; ibin++ ){
	nevt_fit_sysE[ifile][ivar][ibin] = new Int_t[ntotbin];
      }
    }
  }

  // +++++++++++++++++++++++++
  TFile* file = new TFile( weight_file );
  if( file->IsZombie() ) std::cerr << "[ABORT] can not find file : " << weight_file << std::endl, abort();
  TGraphErrors** graph = new TGraphErrors*[nfile];
  for( Int_t ifile=0; ifile<nfile; ifile++ ){
    graph[ifile] = (TGraphErrors*)file->Get( Form("np_%s",tagdir[ifile]) );
    if( graph[ifile]==NULL ) std::cerr << "[ABORT] can not find TGraphErrors : " << tagdir[ifile] << std::endl, abort();
  }
  
  // ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  THStack*** mh       = new THStack**[nfile]; // [nfile][nvar]
  TH1D***    hist_org = new TH1D**   [nfile]; // [nfile][nvar]
  TH1D***    hist_w   = new TH1D**   [nfile]; // [nfile][nvar]
  for( Int_t ifile=0; ifile<nfile; ifile++ ){
    mh      [ifile] = new THStack*[nvar];
    hist_org[ifile] = new TH1D*   [nvar];
    hist_w  [ifile] = new TH1D*   [nvar];
    for( Int_t ivar=0; ivar<nvar; ivar++ ){
      mh      [ifile][ivar] = new THStack( Form("mh_%s_%s",   tagdir[ifile],brname[ivar]), Form("mh_%s_%s;%s",tagdir[ifile],brname[ivar],axisname[ivar]) );
      hist_org[ifile][ivar] = new TH1D   ( Form("h_%s_%s_org",tagdir[ifile],brname[ivar]), Form("h_%s_%s_org",tagdir[ifile],brname[ivar]), nbin2[ivar], xmin[ivar], xmax[ivar] );
      hist_w  [ifile][ivar] = new TH1D   ( Form("h_%s_%s_w",  tagdir[ifile],brname[ivar]), Form("h_%s_%s_w",  tagdir[ifile],brname[ivar]), nbin2[ivar], xmin[ivar], xmax[ivar] );
      if( ifile==0 ){
	hist_org[ifile][ivar]->SetLineColor  (1);
	hist_org[ifile][ivar]->SetMarkerColor(1);
	//hist_org[ifile][ivar]->SetLineWidth  (2);
      }else{
	hist_org[ifile][ivar]->SetLineColor  (2);
	hist_org[ifile][ivar]->SetMarkerColor(2);
      }
      hist_w  [ifile][ivar]->SetLineColor  (3);
      hist_w  [ifile][ivar]->SetMarkerColor(3);
      hist_org[ifile][ivar]->SetMinimum(0.0);
      hist_w  [ifile][ivar]->SetMinimum(0.0);
      hist_org[ifile][ivar]->Sumw2();
      hist_w  [ifile][ivar]->Sumw2();
    }
  }

  THStack*** mh_fit       = new THStack**[nfile]; // [nfile][nvar_fit]
  TH1D***    hist_fit_org = new TH1D**   [nfile]; // [nfile][nvar_fit]
  TH1D***    hist_fit_w   = new TH1D**   [nfile]; // [nfile][nvar_fit]
  for( Int_t ifile=0; ifile<nfile; ifile++ ){
    mh_fit      [ifile] = new THStack*[nvar_fit];
    hist_fit_org[ifile] = new TH1D*   [nvar_fit];
    hist_fit_w  [ifile] = new TH1D*   [nvar_fit];
    for( Int_t ivar=0; ivar<nvar_fit; ivar++ ){
      mh_fit      [ifile][ivar] = new THStack( Form("mhf_%s_%s",   tagdir[ifile],brname_fit[ivar]), Form("mhf_%s_%s;%s",tagdir[ifile],brname_fit[ivar],  axisname_fit[ivar]) );
      hist_fit_org[ifile][ivar] = new TH1D   ( Form("hf_%s_%s_org",tagdir[ifile],brname_fit[ivar]), Form("hf_%s_%s_org",tagdir[ifile],brname_fit[ivar]), nbin_fit[ivar], xmin_fit[ivar], xmax_fit[ivar] );
      hist_fit_w  [ifile][ivar] = new TH1D   ( Form("hf_%s_%s_w",  tagdir[ifile],brname_fit[ivar]), Form("hf_%s_%s_w",  tagdir[ifile],brname_fit[ivar]), nbin_fit[ivar], xmin_fit[ivar], xmax_fit[ivar] );
      if( ifile==0 ){
	hist_fit_org[ifile][ivar]->SetLineColor  (1);
	hist_fit_org[ifile][ivar]->SetMarkerColor(1);
	//hist_fit_org[ifile][ivar]->SetLineWidth  (2);
      }else{
	hist_fit_org[ifile][ivar]->SetLineColor  (2);
	hist_fit_org[ifile][ivar]->SetMarkerColor(2);
      }
      hist_fit_w  [ifile][ivar]->SetLineColor  (3);
      hist_fit_w  [ifile][ivar]->SetMarkerColor(3);
      hist_fit_org[ifile][ivar]->SetMinimum(0.0);
      hist_fit_w  [ifile][ivar]->SetMinimum(0.0);
      hist_fit_org[ifile][ivar]->Sumw2();
      hist_fit_w  [ifile][ivar]->Sumw2();
    }
  }

  // +++++++++++++++++++++++++
  //// for weighted distribtuion
  for( Int_t ievt=0; ievt<c_cut[0]->GetEntries(); ievt++ ){
    c_cut[0]->GetEntry(ievt);
    Double_t val[nvar];
    for( Int_t ivar=0; ivar<nvar; ivar++ ) val[ivar] = c_cut[0]->GetLeaf(brname[ivar])->GetValue(); // reproduce NP distribution by re-weighted SM distribution
    Int_t gindex = getGIndex( val, fl_message );

    Double_t val_fit[nvar_fit];
    for( Int_t ivar=0; ivar<nvar_fit; ivar++ ){
      val_fit[ivar] = c_cut[0]->GetLeaf(brname_fit[ivar])->GetValue();
      if     ( ivar==0 ) val_fit[ivar] = pow(val_fit[ivar],3)/fabs(val_fit[ivar]);
      else if( ivar==1 ) val_fit[ivar] = atan( val_fit[ivar] );
      else if( ivar==3 ){
	nnInput[0] = val_fit[0];
	nnInput[1] = c_cut[0]->GetLeaf(brname_fit[1])->GetValue();
	nnInput[2] = c_cut[0]->GetLeaf(brname_fit[2])->GetValue();
	val_fit[ivar] = nb->nb_expert(nnInput);
      }
    }
    for( Int_t ifile=0; ifile<nfile; ifile++ ){
      Double_t weight  = graph[ifile]->GetY()[gindex];
      Double_t weightE = graph[ifile]->GetErrorY(gindex);
      for( Int_t ivar=0; ivar<nvar; ivar++ ){
	hist_w[ifile][ivar]->Fill( val[ivar], weight );
	Int_t bin = hist_w[ifile][ivar]->FindBin( val[ivar] );
	if( bin!=0 && bin!=nbin2[ivar]+1 ) nevt_sysE[ifile][ivar][bin-1][gindex]++;
      }
      for( Int_t ivar=0; ivar<nvar_fit; ivar++ ){
	hist_fit_w[ifile][ivar]->Fill( val_fit[ivar], weight );
	Int_t bin = hist_fit_w[ifile][ivar]->FindBin( val_fit[ivar] );
	if( bin!=0 && bin!=nbin_fit[ivar]+1 ) nevt_fit_sysE[ifile][ivar][bin-1][gindex]++;
      }
    }
  }

  // +++++++++++++++++++++++++
  // for original distribtuion
  for( Int_t ifile=0; ifile<nfile; ifile++ ){
    for( Int_t ivar=0; ivar<nvar; ivar++ ) c_cut[ifile]->Project( Form("h_%s_%s_org",tagdir[ifile],brname[ivar]), brname[ivar] );
  }

  // +++++++++++++++++++++++++
  //// for original distribtuion of fit variables
  for( Int_t ifile=0; ifile<nfile; ifile++ ){
    for( Int_t ievt=0; ievt<c_cut[ifile]->GetEntries(); ievt++ ){
      c_cut[ifile]->GetEntry(ievt);
      Double_t val_fit[nvar_fit];
      for( Int_t ivar=0; ivar<nvar_fit; ivar++ ){
	val_fit[ivar] = c_cut[ifile]->GetLeaf(brname_fit[ivar])->GetValue();
	if     ( ivar==0 ) val_fit[ivar] = pow(val_fit[ivar],3)/fabs(val_fit[ivar]);
	else if( ivar==1 ) val_fit[ivar] = atan( val_fit[ivar] );
	else if( ivar==3 ){
	  nnInput[0] = val_fit[0];
	  nnInput[1] = c_cut[ifile]->GetLeaf(brname_fit[1])->GetValue();
	  nnInput[2] = c_cut[ifile]->GetLeaf(brname_fit[2])->GetValue();
	  val_fit[ivar] = nb->nb_expert(nnInput);
	}
      }
      for( Int_t ivar=0; ivar<nvar_fit; ivar++ ) hist_fit_org[ifile][ivar]->Fill( val_fit[ivar] );
    }
  }

  // ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  // add systematic error
  for( Int_t ifile=0; ifile<nfile; ifile++ ){

    for( Int_t ivar=0; ivar<nvar; ivar++ ){
      for( Int_t ibin=0; ibin<nbin2[ivar]; ibin++ ){
	Double_t err_stat = hist_w[ifile][ivar]->GetBinError(ibin+1);
	Double_t err_syst = 0.0;
	for( Int_t i=0; i<ntotbin; i++ ) err_syst += pow( nevt_sysE[ifile][ivar][ibin][i] * graph[ifile]->GetErrorY(i), 2 );
	err_syst = sqrt( err_syst );
	hist_w[ifile][ivar]->SetBinError( ibin, sqrt(pow(err_stat,2)+pow(err_syst,2)) );
	//std::cout << "contents = " << hist_w[ifile][ivar]->GetBinContent(ibin+1) << std::endl
	//<< "err_stat = " << err_stat << std::endl
	//<< "err_syst = " << err_syst << std::endl << std::endl;
      }
    }

    for( Int_t ivar=0; ivar<nvar_fit; ivar++ ){
      for( Int_t ibin=0; ibin<nbin_fit[ivar]; ibin++ ){
	Double_t err_stat = hist_fit_w[ifile][ivar]->GetBinError(ibin+1);
	Double_t err_syst = 0.0;
	for( Int_t i=0; i<ntotbin; i++ ) err_syst += pow( nevt_fit_sysE[ifile][ivar][ibin][i] * graph[ifile]->GetErrorY(i), 2 );
	err_syst = sqrt( err_syst );
	hist_fit_w[ifile][ivar]->SetBinError( ibin, sqrt(pow(err_stat,2)+pow(err_syst,2)) );
      }
    }

  }


  // ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  TLegend* leg = new TLegend( 0.55,0.78,0.99,0.97 );
  leg->AddEntry( hist_org[0][0], "original(SM)", "PL" );
  leg->AddEntry( hist_org[1][0], "original",     "PL" );
  leg->AddEntry( hist_w  [1][0], "weight",       "PL" );

  TCanvas** can = new TCanvas*[nfile];
  for( Int_t ifile=0; ifile<nfile; ifile++ ){
    can[ifile] = Canvas( Form("can_%s",tagdir[ifile]), Form("can_%s", tagdir[ifile] ), nvar+nvar_fit );
    can[ifile]->Draw();
    for( Int_t ivar=0; ivar<nvar; ivar++ ){
      can[ifile]->cd(ivar+1);
      if( ivar==0 ){
	hist_org[ifile][ivar]->Print();
	hist_w  [ifile][ivar]->Print();
      }
      hist_org[    0][ivar]->Scale( 1.0/hist_org[    0][ivar]->Integral() );
      hist_org[ifile][ivar]->Scale( 1.0/hist_org[ifile][ivar]->Integral() );
      hist_w  [ifile][ivar]->Scale( 1.0/hist_w  [ifile][ivar]->Integral() );
      mh[ifile][ivar]->Add( hist_org[    0][ivar] );
      mh[ifile][ivar]->Add( hist_org[ifile][ivar] );
      mh[ifile][ivar]->Add( hist_w  [ifile][ivar] );
      mh[ifile][ivar]->Draw("nostack");
    }

    for( Int_t ivar=0; ivar<nvar_fit; ivar++ ){
      can[ifile]->cd(ivar+nvar+1);
      if( ivar==0 ){
	hist_fit_org[ifile][ivar]->Print();
	hist_fit_w  [ifile][ivar]->Print();
      }
      hist_fit_org[    0][ivar]->Scale( 1.0/hist_fit_org[    0][ivar]->Integral() );
      hist_fit_org[ifile][ivar]->Scale( 1.0/hist_fit_org[ifile][ivar]->Integral() );
      hist_fit_w  [ifile][ivar]->Scale( 1.0/hist_fit_w  [ifile][ivar]->Integral() );
      mh_fit[ifile][ivar]->Add( hist_fit_org[    0][ivar] );
      mh_fit[ifile][ivar]->Add( hist_fit_org[ifile][ivar] );
      mh_fit[ifile][ivar]->Add( hist_fit_w  [ifile][ivar] );
      mh_fit[ifile][ivar]->Draw("nostack");
    }
    
    can[ifile]->cd(1);
    leg->Draw();
  }


  for( Int_t ifile=0; ifile<nfile; ifile++ ){
    can[ifile]->Update();
    can[ifile]->Print( Form("pic/reweight_%d.eps",ifile) );
    can[ifile]->Print( Form("pic/reweight_%d.ps",ifile) );
  }
  system("psmerge -oreweight.ps pic/reweight_*.ps && ps2pdf reweight.ps pic/reweight.pdf && rm -f reweight.ps && rm -f pic/reweight_*.ps");  

  // ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  std::cout << "finish" << std::endl;
  if( !gROOT->IsBatch() ) app.Run();

  return 0;
}
