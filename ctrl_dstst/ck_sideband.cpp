#include "draws_.h"
#include "draws_fit_.h"

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

const Char_t*  infile_dt       = "/home/belle/syutaro/dstrtaunu/modules/dstrtaunu/hbk/merge_noremcut_nomddmcut/RD*.root";
const Bool_t   fl_use_dststmc  = true;
const Char_t*  infile_gmc      = "/home/belle/syutaro/dstrtaunu/modules/dstrtaunu/hbk/merge_noremcut_nomddmcut/gMC_*s0[0-9]*.root";
const Double_t nstream_gmc     = 10;
const Char_t*  infile_dststmc  = "/home/belle/syutaro/dstrtaunu/modules/dstrtaunu/hbk/DssMC_weight_nb_noremcut_nomddmcut/DssMC_*.root";
const Double_t nstream_dststmc = 2.7118;
const Bool_t   fl_use_npmc     = true;
const Char_t*  infile_npmc     = "/home/belle/syutaro/dstrtaunu/modules/dstrtaunu/hbk/0p0_weight_nb_noremcut_nomddmcut/npMC_*s0*.root";
const Double_t nstream_npmc    = 10;

const Char_t* selection    = "eecl_exp<1.2 && (rempi0_1==1 && remks==0 && remtrk==0)";
//const Char_t* selection_mc = "1";
const Char_t*  selection_mc = "(ctgrsyst!=7&&ctgrsyst!=8)"; // veto D(*)(2S) // tmppppppppppppppp
//const Char_t*  selection_mc = "(ctgrsyst!=5&&ctgrsyst!=7&&ctgrsyst!=8)"; // veto D1' and D(*)(2S) // tmppppppppppppp
//const Char_t*  selection_mc = "!(2<ctgrsyst && ctgrsyst<9)"; // veto all D** // tmpppppppppppppp


//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// p_D*
const Char_t*  dstp1_brname   = "dst1pcm";
const Char_t*  dstp2_brname   = "dst2pcm";
const Char_t*  dstp1_axisname = "P_{D1*} [GeV]";
const Char_t*  dstp2_axisname = "P_{D2*} [GeV]";
const Int_t    dstp_xbin     =  45;
const Double_t dstp_xmin     = 0.0;
const Double_t dstp_xmax     = 3.0;

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
  
  if( !(app.Argc()==2) )
    std::cerr << "Wrong input" << std::endl
	      << "Usage : " << app.Argv(0)
	      << " (int)fl_dec" << std::endl
	      << "     * fl_dec : 421(D0) or 411(D+)"
	      << "[e.g]" << std::endl
	      << "./ck_sideband 421" << std::endl
	      << "./ck_sideband 411" << std::endl, abort();
  Int_t fl_dec = atoi(app.Argv(1));
  //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  Read_Data( calib_file, true );

  //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  std::stringstream sTmp;
  sTmp << " 1";
  //sTmp << " && (" << makeCut_rem().c_str()    << ")"; // remaining track/pi0/Ks

  //sTmp << " && (" << makeCut_dmass( 0.015, 0.015, 0.045, 0.030,
  //0.015, 0.015, 0.036, 0.024
  //).c_str()  << ")"; // dmass
  sTmp << " && (1.81 < d1_m && d1_m < 1.91 && 1.81 < d2_m && d2_m < 1.91)";

  ///*
  sTmp << " && (" // deltam sideband
       << " ( abs(rm_dst1)==211 && (dm1<0.142 || dm1>0.149) ) || "
       << " ( abs(rm_dst2)==211 && (dm2<0.142 || dm2>0.149) ) || "
       << " ( abs(rm_dst1)==111 && (dm1<0.136 || dm1>0.146) ) || "
       << " ( abs(rm_dst2)==111 && (dm2<0.136 || dm2>0.146) ) "
       << ")";
  //*/
  /*
  sTmp << " && (" // deltam sideband
       << " ( abs(rm_dst1)==211 && (dm1<0.143 || dm1>0.148) ) || "
       << " ( abs(rm_dst2)==211 && (dm2<0.143 || dm2>0.148) ) || "
       << " ( abs(rm_dst1)==111 && (dm1<0.137 || dm1>0.145) ) || "
       << " ( abs(rm_dst2)==111 && (dm2<0.137 || dm2>0.145) ) "
       << ")";
  */
  sTmp << " && (abs(rm_d2lun)==" << fl_dec << ") ";
  sTmp << " && " << selection;

  //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  std::cout << "[Cut] " << sTmp.str().c_str() << std::endl;

  // <Read Data file>
  TChain* c_dt = new TChain(treename);
  std::cout << "[DT] "
	    << c_dt->Add( infile_dt ) << " files : ";
  std::cout << c_dt->GetEntries() << " entries -> ";

  TTree* c_dt_cut = c_dt->CopyTree( Form("(%s)", sTmp.str().c_str()) );
  std::cout << c_dt_cut->GetEntries() << " entries" << std::endl;

  sTmp << " && " << makeCut_dststmc( fl_use_dststmc ).c_str();
  sTmp << " && " << makeCut_npmc   ( fl_use_npmc    ).c_str();

  TChain* c_gmc = new TChain(treename);
  std::cout << "[gMC] "
	    << c_gmc->Add( infile_gmc ) << " files : ";
  std::cout << c_gmc->GetEntries() << " entries -> ";
  TTree* c_gmc_cut = c_gmc->CopyTree( Form("(%s)&&(%s)", sTmp.str().c_str(),selection_mc) );
  std::cout << c_gmc_cut->GetEntries() << " entries" << std::endl;


  TChain* c_dststmc = new TChain(treename);
  std::cout << "[D**MC] "
	    << c_dststmc->Add( infile_dststmc ) << " files : ";
  std::cout << c_dststmc->GetEntries() << " entries -> ";
  TTree* c_dststmc_cut = c_dststmc->CopyTree( Form("(%s)&&(%s)", sTmp.str().c_str(),selection_mc) );
  std::cout << c_dststmc_cut->GetEntries() << " entries" << std::endl;

  TChain* c_npmc = new TChain(treename);
  std::cout << "[NPMC] "
	    << c_npmc->Add( infile_npmc ) << " files : ";
  std::cout << c_npmc->GetEntries() << " entries -> ";
  TTree* c_npmc_cut = c_npmc->CopyTree( Form("(%s)&&(%s)", sTmp.str().c_str(),selection_mc) );
  std::cout << c_npmc_cut->GetEntries() << " entries" << std::endl;


  //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  TH1D* nb_hist_mc    = new TH1D(    "nb_hist_mc",    "nb_hist_mc",   nb_xbin,   nb_xmin,   nb_xmax );    nb_hist_mc->Sumw2(); nb_hist_mc  ->SetXTitle("NB");
  TH1D* nb_hist_dt    = new TH1D(    "nb_hist_dt",    "nb_hist_dt",   nb_xbin,   nb_xmin,   nb_xmax );    nb_hist_dt->Sumw2(); nb_hist_dt  ->SetXTitle("NB");
  TH1D* eecl_hist_mc  = new TH1D(  "eecl_hist_mc",  "eecl_hist_mc", eecl_xbin, eecl_xmin, eecl_xmax );  eecl_hist_mc->Sumw2(); eecl_hist_mc->SetXTitle("E'_{ECL} [GeV]");
  TH1D* eecl_hist_dt  = new TH1D(  "eecl_hist_dt",  "eecl_hist_dt", eecl_xbin, eecl_xmin, eecl_xmax );  eecl_hist_dt->Sumw2(); eecl_hist_dt->SetXTitle("E'_{ECL} [GeV]");
  TH1D* dstp1_hist_mc = new TH1D( "dstp1_hist_mc", "dstp1_hist_mc", dstp_xbin, dstp_xmin, dstp_xmax ); dstp1_hist_mc->Sumw2(); dstp1_hist_mc->SetXTitle("p_{D*}^{1st} [GeV]");
  TH1D* dstp2_hist_mc = new TH1D( "dstp2_hist_mc", "dstp2_hist_mc", dstp_xbin, dstp_xmin, dstp_xmax ); dstp2_hist_mc->Sumw2(); dstp2_hist_mc->SetXTitle("p_{D*}^{2nd} [GeV]");
  TH1D* dstp1_hist_dt = new TH1D( "dstp1_hist_dt", "dstp1_hist_dt", dstp_xbin, dstp_xmin, dstp_xmax ); dstp1_hist_dt->Sumw2(); dstp1_hist_dt->SetXTitle("p_{D*}^{1st} [GeV]");
  TH1D* dstp2_hist_dt = new TH1D( "dstp2_hist_dt", "dstp2_hist_dt", dstp_xbin, dstp_xmin, dstp_xmax ); dstp2_hist_dt->Sumw2(); dstp2_hist_dt->SetXTitle("p_{D*}^{2nd} [GeV]");
  TH1D* dstpl_hist_mc = new TH1D( "dstpl_hist_mc", "dstpl_hist_mc", dstp_xbin, dstp_xmin, dstp_xmax ); dstpl_hist_mc->Sumw2(); dstpl_hist_mc->SetXTitle("p_{D*}^{low} [GeV]");
  TH1D* dstph_hist_mc = new TH1D( "dstph_hist_mc", "dstph_hist_mc", dstp_xbin, dstp_xmin, dstp_xmax ); dstph_hist_mc->Sumw2(); dstph_hist_mc->SetXTitle("p_{D*}^{high} [GeV]");
  TH1D* dstpl_hist_dt = new TH1D( "dstpl_hist_dt", "dstpl_hist_dt", dstp_xbin, dstp_xmin, dstp_xmax ); dstpl_hist_dt->Sumw2(); dstpl_hist_dt->SetXTitle("p_{D*}^{low} [GeV]");
  TH1D* dstph_hist_dt = new TH1D( "dstph_hist_dt", "dstph_hist_dt", dstp_xbin, dstp_xmin, dstp_xmax ); dstph_hist_dt->Sumw2(); dstph_hist_dt->SetXTitle("p_{D*}^{high} [GeV]");
  TH1D* self_hist_mc  = new TH1D(  "self_hist_mc",  "self_hist_mc", 22, -8, 3 ); self_hist_mc->SetXTitle("ctgry");

  //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    for( Int_t ievt=0; ievt<c_gmc_cut->GetEntries(); ievt++ ){
      Double_t weight = cal_weight( c_gmc_cut, ievt, (Double_t)nstream_gmc );
      //if( c_gmc_cut->GetLeaf("self")->GetValue()==2 || (
      //c_gmc_cut->GetLeaf("gm_semi" )->GetValue() < 0 &&
      //c_gmc_cut->GetLeaf("dst1self")->GetValue()== 1 &&
      //c_gmc_cut->GetLeaf("dst2self")->GetValue()== 2
      //)
      //) weight *= 1.152; // ~279/242 // tmpppppp
	  
      nb_hist_mc   ->Fill( c_gmc_cut->GetLeaf( nb_brname)->GetValue(), weight );
      eecl_hist_mc ->Fill( c_gmc_cut->GetLeaf("eecl_exp")->GetValue(), weight );
      dstp1_hist_mc->Fill( c_gmc_cut->GetLeaf(dstp1_brname)->GetValue(), weight );
      dstp2_hist_mc->Fill( c_gmc_cut->GetLeaf(dstp2_brname)->GetValue(), weight );
      
      if( c_gmc_cut->GetLeaf("cosdl1")->GetValue() == c_gmc_cut->GetLeaf("cosdll")->GetValue() ){
	dstpl_hist_mc->Fill( c_gmc_cut->GetLeaf(dstp1_brname)->GetValue(), weight );
	dstph_hist_mc->Fill( c_gmc_cut->GetLeaf(dstp2_brname)->GetValue(), weight );
      }else{
	dstph_hist_mc->Fill( c_gmc_cut->GetLeaf(dstp1_brname)->GetValue(), weight );
	dstpl_hist_mc->Fill( c_gmc_cut->GetLeaf(dstp2_brname)->GetValue(), weight );
      }

      if( c_gmc_cut->GetLeaf("self")->GetValue()==-6 && (c_gmc_cut->GetLeaf("gm_ddst1")->GetValue()==3 || c_gmc_cut->GetLeaf("gm_ddst2")->GetValue()==3) ) self_hist_mc->Fill(-5, weight);
      else                                                                                                                                                 self_hist_mc->Fill( c_gmc_cut->GetLeaf("self")->GetValue(), weight );
    }
    
    for( Int_t ievt=0; ievt<c_dststmc_cut->GetEntries(); ievt++ ){
      Double_t weight = cal_weight( c_dststmc_cut, ievt, (Double_t)nstream_dststmc );
      //weight *= 0.392; // ~102/260 // tmppppppp
      nb_hist_mc   ->Fill( c_dststmc_cut->GetLeaf(   nb_brname)->GetValue(), weight );
      eecl_hist_mc ->Fill( c_dststmc_cut->GetLeaf("eecl_exp")->GetValue(), weight );
      dstp1_hist_mc->Fill( c_dststmc_cut->GetLeaf(dstp1_brname)->GetValue(), weight );
      dstp2_hist_mc->Fill( c_dststmc_cut->GetLeaf(dstp2_brname)->GetValue(), weight );
      
      if( c_dststmc_cut->GetLeaf("cosdl1")->GetValue() == c_dststmc_cut->GetLeaf("cosdll")->GetValue() ){
	dstpl_hist_mc->Fill( c_dststmc_cut->GetLeaf(dstp1_brname)->GetValue(), weight );
	dstph_hist_mc->Fill( c_dststmc_cut->GetLeaf(dstp2_brname)->GetValue(), weight );
      }else{
	dstph_hist_mc->Fill( c_dststmc_cut->GetLeaf(dstp1_brname)->GetValue(), weight );
	dstpl_hist_mc->Fill( c_dststmc_cut->GetLeaf(dstp2_brname)->GetValue(), weight );
      }
      if( c_dststmc_cut->GetLeaf("self")->GetValue()==-6 && (c_dststmc_cut->GetLeaf("gm_ddst1")->GetValue()==3 || c_dststmc_cut->GetLeaf("gm_ddst2")->GetValue()==3) ) self_hist_mc->Fill(-5, weight);
      else                                                                                                                                                             self_hist_mc->Fill( c_dststmc_cut->GetLeaf("self")->GetValue(), weight );
    }

    for( Int_t ievt=0; ievt<c_npmc_cut->GetEntries(); ievt++ ){
      Double_t weight = cal_weight( c_npmc_cut, ievt, (Double_t)nstream_npmc );
      nb_hist_mc   ->Fill( c_npmc_cut->GetLeaf(   nb_brname)->GetValue(), weight );
      eecl_hist_mc ->Fill( c_npmc_cut->GetLeaf("eecl_exp")->GetValue(), weight );
      dstp1_hist_mc->Fill( c_npmc_cut->GetLeaf(dstp1_brname)->GetValue(), weight );
      dstp2_hist_mc->Fill( c_npmc_cut->GetLeaf(dstp2_brname)->GetValue(), weight );
      
      if( c_npmc_cut->GetLeaf("cosdl1")->GetValue() == c_npmc_cut->GetLeaf("cosdll")->GetValue() ){
	dstpl_hist_mc->Fill( c_npmc_cut->GetLeaf(dstp1_brname)->GetValue(), weight );
	dstph_hist_mc->Fill( c_npmc_cut->GetLeaf(dstp2_brname)->GetValue(), weight );
      }else{
	dstph_hist_mc->Fill( c_npmc_cut->GetLeaf(dstp1_brname)->GetValue(), weight );
	dstpl_hist_mc->Fill( c_npmc_cut->GetLeaf(dstp2_brname)->GetValue(), weight );
      }
      self_hist_mc->Fill( c_npmc_cut->GetLeaf("self")->GetValue(), weight );
      if( c_npmc_cut->GetLeaf("self")->GetValue()==-6 && (c_npmc_cut->GetLeaf("gm_ddst1")->GetValue()==3 || c_npmc_cut->GetLeaf("gm_ddst2")->GetValue()==3) ) self_hist_mc->Fill(-5, weight);
      else                                                                                                                                                    self_hist_mc->Fill( c_npmc_cut->GetLeaf("self")->GetValue(), weight );
    }

  //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  for( Int_t ievt=0; ievt<c_dt_cut->GetEntries(); ievt++ ){
    c_dt_cut->GetEntry(ievt);
    nb_hist_dt   ->Fill( c_dt_cut->GetLeaf(  nb_brname )->GetValue() );
    eecl_hist_dt ->Fill( c_dt_cut->GetLeaf("eecl_exp"  )->GetValue() );
    dstp1_hist_dt->Fill( c_dt_cut->GetLeaf(dstp1_brname)->GetValue() );
    dstp2_hist_dt->Fill( c_dt_cut->GetLeaf(dstp2_brname)->GetValue() );
    if( c_dt_cut->GetLeaf("cosdl1")->GetValue() == c_dt_cut->GetLeaf("cosdll")->GetValue() ){
      dstpl_hist_dt->Fill( c_dt_cut->GetLeaf(dstp1_brname)->GetValue() );
      dstph_hist_dt->Fill( c_dt_cut->GetLeaf(dstp2_brname)->GetValue() );
    }else{
      dstph_hist_dt->Fill( c_dt_cut->GetLeaf(dstp1_brname)->GetValue() );
      dstpl_hist_dt->Fill( c_dt_cut->GetLeaf(dstp2_brname)->GetValue() );
    }
  }

  //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  nb_hist_mc   ->Print();
  nb_hist_dt   ->Print();
  eecl_hist_mc ->Print();
  eecl_hist_dt ->Print();
  dstp1_hist_mc->Print();
  dstp2_hist_mc->Print();
  dstp1_hist_dt->Print();
  dstp2_hist_dt->Print();
  dstpl_hist_mc->Print();
  dstph_hist_mc->Print();
  dstpl_hist_dt->Print();
  dstph_hist_dt->Print();

  std::cout << eecl_hist_dt->Integral()/eecl_hist_mc->Integral() << std::endl;

  nb_hist_mc   ->Scale(   nb_hist_dt ->Integral()/  nb_hist_mc ->Integral() );
  eecl_hist_mc ->Scale( eecl_hist_dt ->Integral()/eecl_hist_mc ->Integral() );
  dstp1_hist_mc->Scale( dstp1_hist_dt->Integral()/dstp1_hist_mc->Integral() );
  dstp2_hist_mc->Scale( dstp2_hist_dt->Integral()/dstp2_hist_mc->Integral() );
  dstpl_hist_mc->Scale( dstpl_hist_dt->Integral()/dstpl_hist_mc->Integral() );
  dstph_hist_mc->Scale( dstph_hist_dt->Integral()/dstph_hist_mc->Integral() );

  nb_hist_mc   ->Print();
  nb_hist_dt   ->Print();
  eecl_hist_mc ->Print();
  eecl_hist_dt ->Print();
  dstp1_hist_mc->Print();
  dstp2_hist_mc->Print();
  dstp1_hist_dt->Print();
  dstp2_hist_dt->Print();
  dstpl_hist_mc->Print();
  dstph_hist_mc->Print();
  dstpl_hist_dt->Print();
  dstph_hist_dt->Print();

  //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  TCanvas* can = Canvas( "can", "can", 3, 2 );
  can->cd(1);
  nb_hist_mc->SetMarkerColor(13);
  nb_hist_mc->SetFillColor  (13);
  nb_hist_mc->SetMinimum    (0.0);
  nb_hist_dt->SetMarkerColor(1);
  nb_hist_dt->SetLineColor  (1);
  nb_hist_dt->SetMinimum    (0.0);

  
  if( nb_hist_dt->GetMaximum() > nb_hist_mc->GetMaximum() ) nb_hist_dt->Draw("P");
  else                                                      nb_hist_mc->Draw("E2");
  nb_hist_mc->Draw("E2same");
  nb_hist_dt->Draw("Psame");

  can->cd(2);
  eecl_hist_mc->SetMarkerColor(13);
  eecl_hist_mc->SetFillColor  (13);
  eecl_hist_dt->SetMarkerColor(1);
  eecl_hist_dt->SetLineColor  (1);

  eecl_hist_dt->SetMinimum(0.0);
  eecl_hist_mc->SetMinimum(0.0);
  if( eecl_hist_dt->GetMaximum() > eecl_hist_mc->GetMaximum() ) eecl_hist_dt->Draw("P");
  else                                                          eecl_hist_mc->Draw("E2");
  eecl_hist_mc->Draw("E2same");
  eecl_hist_dt->Draw("Psame");
  
  TLegend* leg = new TLegend( 0.65,0.80,0.85,0.95 );  
  leg->AddEntry( eecl_hist_mc, "MC",   "F"   );
  leg->AddEntry( eecl_hist_dt, "Data", "PLF" );
  
  leg->Draw();

  can->cd(4);
  self_hist_mc->Draw();

  can->cd(5);
  dstp1_hist_mc->SetMarkerColor(13);
  dstp1_hist_mc->SetFillColor  (13);
  dstp1_hist_dt->SetMarkerColor(1);
  dstp1_hist_dt->SetLineColor  (1);

  dstp1_hist_dt->SetMinimum(0.0);
  dstp1_hist_dt->Draw("P");
  dstp1_hist_mc->Draw("E2same");
  dstp1_hist_dt->Draw("Psame");
  /*
  dstpl_hist_mc->SetMarkerColor(13);
  dstpl_hist_mc->SetFillColor  (13);
  dstpl_hist_dt->SetMarkerColor(1);
  dstpl_hist_dt->SetLineColor  (1);

  dstpl_hist_dt->SetMinimum(0.0);

  dstpl_hist_dt->Draw("P");
  dstpl_hist_mc->Draw("E2same");
  dstpl_hist_dt->Draw("Psame");
  */

  can->cd(6);
  dstp2_hist_mc->SetMarkerColor(13);
  dstp2_hist_mc->SetFillColor  (13);
  dstp2_hist_dt->SetMarkerColor(1);
  dstp2_hist_dt->SetLineColor  (1);

  dstp2_hist_dt->SetMinimum(0.0);
  dstp2_hist_dt->Draw("P");
  dstp2_hist_mc->Draw("E2same");
  dstp2_hist_dt->Draw("Psame");
  /*
  dstph_hist_mc->SetMarkerColor(13);
  dstph_hist_mc->SetFillColor  (13);
  dstph_hist_dt->SetMarkerColor(1);
  dstph_hist_dt->SetLineColor  (1);

  dstph_hist_dt->SetMinimum(0.0);
  dstph_hist_dt->Draw("P");
  dstph_hist_mc->Draw("E2same");
  dstph_hist_dt->Draw("Psame");
  */
  
  //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  can->Update();
  can->Print( Form("pic/ck_sideband_%d_comparison_faked_dstr.eps",fl_dec) );
  std::cout << "finish" << std::endl;
  if( !gROOT->IsBatch() ) app.Run();
  return 0;
}

//nb_hist_mc->SetBinContent( nb_xbin, 0.95*nb_hist_mc->GetBinContent(nb_xbin) );
//nb_hist_mc->SetBinContent( 2, 1.5*nb_hist_mc->GetBinContent(2) );
//nb_hist_mc->SetBinContent( nb_xbin-1, 0.90*nb_hist_mc->GetBinContent(nb_xbin-1) );
