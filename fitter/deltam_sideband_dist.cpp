#include "draws_.h"
#include "draws_fit_.h"
#include "draws_roofit_.h"

const Int_t nhist   = 2; // 0(D0-D0), 1(D0-D+)
TH1D** nb_hist_mc   = new TH1D*[nhist];
TH1D** nb_hist_dt   = new TH1D*[nhist];
TH1D** eecl_hist_mc = new TH1D*[nhist];
TH1D** eecl_hist_dt = new TH1D*[nhist];
TH1D** self_hist_mc = new TH1D*[nhist];

void inputEvent_mc( TTree* tree, Double_t used_nstream ){
  for( Int_t ievt=0; ievt<tree->GetEntries(); ievt++ ){
    tree->GetEntry(ievt);
    Int_t tmp_d1_lun = abs((Int_t)tree->GetLeaf("rm_d1lun")->GetValue());
    Int_t tmp_d2_lun = abs((Int_t)tree->GetLeaf("rm_d2lun")->GetValue());
    Int_t index = 0;
    if( tmp_d1_lun==411 || tmp_d2_lun==411 ) index = 1; // D0-D+
    else                                     index = 0; // D0-D0
    Double_t weight = cal_weight( tree, ievt, used_nstream );
      nb_hist_mc  [index]->Fill( tree->GetLeaf("nb_mode0_test13_nor")->GetValue(), weight );
      //eecl_hist_mc[index]->Fill( tree->GetLeaf("eecl"               )->GetValue(), weight );
      eecl_hist_mc[index]->Fill( tree->GetLeaf("eecl_exp"             )->GetValue(), weight ); // tmppppppp
      self_hist_mc[index]->Fill( tree->GetLeaf("self"               )->GetValue(), weight );
  }
  return;
}

void inputEvent_dt( TTree* tree ){
  for( Int_t ievt=0; ievt<tree->GetEntries(); ievt++ ){
    tree->GetEntry(ievt);
    Int_t tmp_d1_lun = abs((Int_t)tree->GetLeaf("rm_d1lun")->GetValue());
    Int_t tmp_d2_lun = abs((Int_t)tree->GetLeaf("rm_d2lun")->GetValue());

    Int_t index = 0;
    if( tmp_d1_lun==411 || tmp_d2_lun==411 ) index = 1; // D0-D+
    else                                     index = 0; // D0-D0

      nb_hist_dt[index]->Fill( tree->GetLeaf("nb_mode0_test13_nor")->GetValue() );
      //eecl_hist_dt[index]->Fill( tree->GetLeaf("eecl"               )->GetValue() );
    eecl_hist_dt[index]->Fill( tree->GetLeaf("eecl_exp"           )->GetValue() ); // tmppppppp
  }
  return;
}

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
const Char_t*  infile_dt       = "/home/belle/syutaro/dstrtaunu/modules/dstrtaunu/hbk/merge_noremcut_nomddmcut/RD_*.root";
const Char_t*  infile_gmc      = "/home/belle/syutaro/dstrtaunu/modules/dstrtaunu/hbk/merge_noremcut_nomddmcut/gMC_*s0[0-9]*.root";
const Char_t*  infile_dststmc  = "/home/belle/syutaro/dstrtaunu/modules/dstrtaunu/hbk/DssMC_weight_nb_noremcut_nomddmcut/DssMC_*.root";
const Char_t*  infile_npmc     = "/home/belle/syutaro/dstrtaunu/modules/dstrtaunu/hbk/%s_weight_nb_noremcut_nomddmcut/npMC_*.root";

const Double_t nstream_gmc     = 10;
const Bool_t   fl_use_dststmc  = true;
const Double_t nstream_dststmc = 2.7118;
const Bool_t   fl_use_npmc     = true;
const Double_t nstream_npmc    = 10;


//const Char_t* selection = "eecl<1.2 && nb_mode0_test13_nor>0.8";
//const Char_t* selection = "eecl<1.2 && nb_mode0_test13_nor<0.0";
const Char_t* selection = "eecl_exp<1.2 && remtrk==0 && rempi0_1==1 && remks==0";
//const Char_t* selection = "eecl_exp<1.2 && remtrk==0 && rempi0_1==1 && remks==0 && nb_mode0_test13_nor>0.8";
//const Char_t* selection = "eecl<1.2 && remtrk==0 && rempi0_1==0 && remks==0";

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
Int_t main( Int_t argc, Char_t** argv ){
  gROOT->SetBatch(!true); // tmpppppp
  TApplication app( "app", &argc, argv );
  TStyle* sty = Style(10);
  sty->SetTitleOffset(1.0,"y");
  sty->SetOptStat(0);
  sty->SetLabelSize(0.030,"xyz");
  sty->SetTitleSize(0.045,"xyz");
  sty->SetOptFit(11);
  sty->SetStatW(0.16);
  sty->SetMarkerSize(0.4);
  //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  Read_Data( "calib.dat", true );

  //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  std::stringstream sTmp;
  sTmp << " 1";
  /*
  sTmp << " && (" << makeCut_dmass( 0.015, 0.015, 0.045, 0.030,
				    0.015, 0.015, 0.036, 0.024
				    ).c_str()  << ")"; // dmass
  */
  sTmp << " && (1.81 < d1_m && d1_m < 1.91 && 1.81 < d2_m && d2_m < 1.91)";
  sTmp << " && (" // deltam sideband
       << " ( abs(rm_dst1)==211 && (dm1<0.142 || dm1>0.149) ) || "
       << " ( abs(rm_dst2)==211 && (dm2<0.142 || dm2>0.149) ) || "
       << " ( abs(rm_dst1)==111 && (dm1<0.136 || dm1>0.146) ) || "
       << " ( abs(rm_dst2)==111 && (dm2<0.136 || dm2>0.146) ) "
       << ")";
  sTmp << " && " << selection;

  //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  std::cout << sTmp.str().c_str() << std::endl;
  // <Read Data file>
  TChain* c_dt = new TChain(treename);
  std::cout << "[infile Data] "      << infile_dt << " : ";
  std::cout << c_dt->Add(infile_dt)  << " files, ";
  std::cout << c_dt->GetEntries()    << " entries -> ";
  TTree* c_dt_cut;
  c_dt_cut = c_dt->CopyTree( sTmp.str().c_str() );
  std::cout << c_dt_cut->GetEntries() << " entries" << std::endl;

  TChain* c_gmc = new TChain(treename);
  std::cout << "[infile_gmc] " << infile_gmc << std::endl;
  std::cout << c_gmc->Add(infile_gmc)  << " files, ";
  std::cout << nstream_gmc             << " streams, ";
  std::cout << c_gmc->GetEntries()     << " entries -> ";

  TTree* c_gmc_cut = c_gmc->CopyTree( Form("(%s)&&(%s)&&(%s)", sTmp.str().c_str(), makeCut_dststmc(fl_use_dststmc).c_str(), makeCut_npmc(fl_use_npmc).c_str()) );
  std::cout << c_gmc_cut->GetEntries() << " entries"
	    << std::endl;
      
  TChain* c_dststmc = new TChain(treename);
  std::cout << "[infile_dststmc] " << infile_dststmc << std::endl;
  std::cout << c_dststmc->Add(infile_dststmc) << " files, ";
  std::cout << nstream_dststmc                << " streams, ";
  std::cout << c_dststmc->GetEntries()        << " entries -> ";
  
  TTree* c_dststmc_cut = c_dststmc->CopyTree( Form("(%s)&&(%s)&&(%s)", sTmp.str().c_str(), makeCut_dststmc(fl_use_dststmc).c_str(), makeCut_npmc(fl_use_npmc).c_str()) );
  std::cout << c_dststmc_cut->GetEntries() << " entries"
	    << std::endl;
  
  TChain* c_npmc = new TChain(treename);
  std::cout << "[infile_npmc] " << Form(infile_npmc,"0p0") << std::endl;
  std::cout << c_npmc->Add(Form(infile_npmc,"0p0"))        << " files, ";
  std::cout << nstream_npmc                                << " streams, ";
  std::cout << c_npmc->GetEntries()                        << " entries -> ";

  TTree* c_npmc_cut = c_npmc->CopyTree( Form("(%s)&&(%s)&&(%s)", sTmp.str().c_str(), makeCut_dststmc(fl_use_dststmc).c_str(), makeCut_npmc(fl_use_npmc).c_str()) );
  std::cout << c_npmc_cut->GetEntries() << " entries"
	    << std::endl;

  //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

  for( Int_t ihist=0; ihist<nhist; ihist++ ){
    nb_hist_mc  [ihist] = new TH1D( Form(  "nb_hist_mc_%d",ihist),  Form(  "nb_hist_mc_%d",ihist),   nb_xbin,   nb_xmin,   nb_xmax );    nb_hist_mc[ihist]->Sumw2();
    nb_hist_dt  [ihist] = new TH1D( Form(  "nb_hist_dt_%d",ihist),  Form(  "nb_hist_dt_%d",ihist),   nb_xbin,   nb_xmin,   nb_xmax );    nb_hist_dt[ihist]->Sumw2();
    eecl_hist_mc[ihist] = new TH1D( Form("eecl_hist_mc_%d",ihist),  Form("eecl_hist_mc_%d",ihist), eecl_xbin, eecl_xmin, eecl_xmax );  eecl_hist_mc[ihist]->Sumw2();
    eecl_hist_dt[ihist] = new TH1D( Form("eecl_hist_dt_%d",ihist),  Form("eecl_hist_dt_%d",ihist), eecl_xbin, eecl_xmin, eecl_xmax );  eecl_hist_dt[ihist]->Sumw2();
    self_hist_mc[ihist] = new TH1D( Form("self_hist_mc_%d",ihist),  selection, 44, -8, 3 );
    nb_hist_mc[ihist]->SetXTitle("NB");
    nb_hist_dt[ihist]->SetXTitle("NB");
    eecl_hist_mc[ihist]->SetXTitle("E_{ECL} [GeV]");
    eecl_hist_dt[ihist]->SetXTitle("E_{ECL} [GeV]");
    self_hist_mc[ihist]->SetXTitle("Event Category");
  }

  //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  inputEvent_mc(     c_gmc_cut, nstream_gmc     );
  inputEvent_mc( c_dststmc_cut, nstream_dststmc );
  inputEvent_mc(    c_npmc_cut, nstream_npmc    );
  inputEvent_dt(      c_dt_cut                  );

  //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  for( Int_t ihist=0; ihist<nhist; ihist++ ){
    nb_hist_mc  [ihist]->Print();
    nb_hist_dt  [ihist]->Print();
    eecl_hist_mc[ihist]->Print();
    eecl_hist_dt[ihist]->Print();
  }

  for( Int_t ihist=0; ihist<nhist; ihist++ ){
    std::cout << eecl_hist_dt[ihist]->Integral()/eecl_hist_mc[ihist]->Integral() << std::endl;
    nb_hist_mc  [ihist]->Scale(   nb_hist_dt[ihist]->Integral()/  nb_hist_mc[ihist]->Integral() );
    eecl_hist_mc[ihist]->Scale( eecl_hist_dt[ihist]->Integral()/eecl_hist_mc[ihist]->Integral() );
  }
  
  for( Int_t ihist=0; ihist<nhist; ihist++ ){
    nb_hist_mc  [ihist]->Print();
    nb_hist_dt  [ihist]->Print();
    eecl_hist_mc[ihist]->Print();
    eecl_hist_dt[ihist]->Print();
  }
  
  //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  TCanvas* can = Canvas( "can", "can", 3, 2 );
  for( Int_t ihist=0; ihist<nhist; ihist++ ){
    
  can->cd(3*ihist+1);
  nb_hist_mc[ihist]->SetMarkerColor(13);
  nb_hist_mc[ihist]->SetLineColor  (13);
  nb_hist_mc[ihist]->SetFillColor  (13);
  nb_hist_dt[ihist]->SetMarkerColor(1);
  nb_hist_dt[ihist]->SetLineColor  (1);
  nb_hist_dt[ihist]->SetMinimum(0.0);
  
  nb_hist_dt[ihist]->Draw("P");
  nb_hist_mc[ihist]->Draw("E2same");
  nb_hist_dt[ihist]->Draw("Psame");

  can->cd(3*ihist+2);
  eecl_hist_mc[ihist]->SetMarkerColor(13);
  eecl_hist_mc[ihist]->SetLineColor  (13);
  eecl_hist_mc[ihist]->SetFillColor  (13);
  eecl_hist_dt[ihist]->SetMarkerColor(1);
  eecl_hist_dt[ihist]->SetLineColor  (1);

  eecl_hist_dt[ihist]->SetMinimum(0.0);
  eecl_hist_dt[ihist]->Draw("P");
  eecl_hist_mc[ihist]->Draw("E2same");
  eecl_hist_dt[ihist]->Draw("Psame");

  can->cd(3*ihist+3);
  self_hist_mc[ihist]->Draw();
  }
  TLegend* leg = new TLegend( 0.40,0.45,0.60,0.65 );
  leg->AddEntry( nb_hist_mc[0], "MC",   "F" );
  leg->AddEntry( nb_hist_dt[0], "Data", "PL" );
  can->cd(1);
  leg->Draw();

  //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  can->Update();
  can->Print( "pic/deltam_sideband_dist.eps" );
  std::cout << "finish" << std::endl;
  if( !gROOT->IsBatch() ) app.Run();
  return 0;
}

