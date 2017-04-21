#include "draws_.h"
#include "draws_roofit_.h"

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
using namespace RooFit;
const Char_t* treename  = "h15";
const Bool_t  fl_line   = true;
const Char_t* wbr       = "w1_mc*w1_bf*w2_mc*w2_bf"; // (A+a) * (B+b) = AB + aB + Ab + ab
const Char_t* wbrEstat2 = "pow(w1_mc_estat*w2_mc,2) + pow(w1_mc*w2_mc_estat,2)";
const Char_t* wbrEsyst  = "w1_mc_esyst*w2_mc + w1_mc*w2_mc_esyst";
const Double_t nstream   = 6;
const Int_t   fl_dst    = 111; // 211 or 111

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
const Char_t* infile_dt = "~/dstrtaunu/modules/skim_dstrtaunu/hbk/hbk20/merge_loose_masscut/RD_*.root";
const Char_t* infile_mc = "~/dstrtaunu/modules/skim_dstrtaunu/hbk/hbk20/merge_loose_masscut/gMC_*.root";
//const Char_t* infile_dt = "~/dstrtaunu/modules/skim_dstrtaunu/hbk/hbk20/merge_loose_masscut_bcs_vtx/RD_*.root";
//const Char_t* infile_mc = "~/dstrtaunu/modules/skim_dstrtaunu/hbk/hbk20/merge_loose_masscut_bcs_vtx/gMC_*.root";
//const Char_t* selection = "eecl<1.2 && nb_mode0_test13_nor>0.8";
//const Char_t* selection = "eecl<1.2 && nb_mode0_test13_nor<0.0";
const Char_t* selection = "eecl<1.2";

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// correction factor
// D
Double_t R_ss_d[nd_dec] = {1.0, 1.0, 1.0, 1.0, 1.0,
			   1.0, 1.0, 1.0, 1.0, 1.0,
			   1.0, 1.0, 1.0, 1.0, 1.0};
Double_t R_sb_d[nd_dec] = {1.0, 1.0, 1.0, 1.0, 1.0,
			   1.0, 1.0, 1.0, 1.0, 1.0,
			   1.0, 1.0, 1.0, 1.0, 1.0};
Double_t R_bb_d[nd_dec] = {1.0, 1.0, 1.0, 1.0, 1.0,
			   1.0, 1.0, 1.0, 1.0, 1.0,
			   1.0, 1.0, 1.0, 1.0, 1.0};

Double_t R_ss_dE[nd_dec] = {0.0};
Double_t R_sb_dE[nd_dec] = {0.0};
Double_t R_bb_dE[nd_dec] = {0.0};
// D*
Double_t R_ss_dstr[nd_dec] = {1.0, 1.0, 1.0, 1.0, 1.0,
			      1.0, 1.0, 1.0, 1.0, 1.0,
			      1.0, 1.0, 1.0, 1.0, 1.0};
Double_t R_sb_dstr[nd_dec] = {1.0, 1.0, 1.0, 1.0, 1.0,
			      1.0, 1.0, 1.0, 1.0, 1.0,
			      1.0, 1.0, 1.0, 1.0, 1.0};
Double_t R_bb_dstr[nd_dec] = {1.0, 1.0, 1.0, 1.0, 1.0,
			      1.0, 1.0, 1.0, 1.0, 1.0,
			      1.0, 1.0, 1.0, 1.0, 1.0};

Double_t R_ss_dstrE[nd_dec] = {0.0};
Double_t R_sb_dstrE[nd_dec] = {0.0};
Double_t R_bb_dstrE[nd_dec] = {0.0};

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// nb
const Char_t*  nb_brname   = "nb_mode0_test13_nor";
const Char_t*  nb_axisname = "NB";
//const Int_t    nb_xbin     =   15;
const Int_t    nb_xbin     =   30;
const Double_t nb_xmin     = -1.0;
const Double_t nb_xmax     =  1.0;

// E_ECL
const Char_t*  eecl_brname   = "eecl";
const Char_t*  eecl_axisname = "E_{ECL} [GeV]";
const Int_t    eecl_xbin     =  24;
const Double_t eecl_xmin     = 0.0;
const Double_t eecl_xmax     = 1.2;

// p_D*
const Char_t*  dstp1_brname   = "dst1pcm";
const Char_t*  dstp2_brname   = "dst2pcm";
const Char_t*  dstp1_axisname = "P_{D1*} [GeV]";
const Char_t*  dstp2_axisname = "P_{D2*} [GeV]";
const Int_t    dstp_xbin     =  45;
const Double_t dstp_xmin     = 0.0;
const Double_t dstp_xmax     = 3.0;

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
void Read_Data( const Char_t* infile ){
  Char_t buf[2048];
  const Int_t ndata = 21;
  Double_t data[ndata] = {0};
  ifstream fin( infile );
  if( !fin ){
    std::cout << "[WARNING] can not find a file" << std::endl;
    return;
  }
  while( !fin.eof() ){
    fin.getline( buf,1024 );
    if     ( buf[0] == '#' ) continue; // comment line
    else if( buf[0] == '*' ) break;    // finish
    else{
      std::istringstream sTmp(buf);
      sTmp >> data[ 0] >> data[ 1] >> data[ 2] >> data[ 3] >> data[ 4]
	   >> data[ 5] >> data[ 6] >> data[ 7] >> data[ 8] >> data[ 9]
	   >> data[10] >> data[11] >> data[12] >> data[13] >> data[14]
	   >> data[15] >> data[16] >> data[17] >> data[18] >> data[19]
	   >> data[20];

      if( (Int_t)data[1]==411 ){
	for( Int_t i=0; i<nd_dec; i++ ){
	  if( d_dec_chg[i]==1 ){
	    R_ss_dstr [i] = data[12];
	    R_ss_dstrE[i] = data[13];
	    R_sb_dstr [i] = data[15];
	    R_sb_dstrE[i] = data[16];
	    R_bb_dstr [i] = data[18];
	    R_bb_dstrE[i] = data[19];
	  }
	}
      }else if( (Int_t)data[1]==421 ){
	for( Int_t i=0; i<nd_dec; i++ ){
	  if( d_dec_chg[i]==0 ){
	    R_ss_dstr [i] = data[12];
	    R_ss_dstrE[i] = data[13];
	    R_sb_dstr [i] = data[15];
	    R_sb_dstrE[i] = data[16];
	    R_bb_dstr [i] = data[18];
	    R_bb_dstrE[i] = data[19];
	  }
	}
      }else{
	R_ss_d [(Int_t)data[0]] = data[ 3];
	R_ss_dE[(Int_t)data[0]] = data[ 4];
	R_sb_d [(Int_t)data[0]] = data[ 6];
	R_sb_dE[(Int_t)data[0]] = data[ 7];
	R_bb_d [(Int_t)data[0]] = data[ 9];
	R_bb_dE[(Int_t)data[0]] = data[10];
	
	R_ss_dstr [(Int_t)data[0]] = data[12];
	R_ss_dstrE[(Int_t)data[0]] = data[13];
	R_sb_dstr [(Int_t)data[0]] = data[15];
	R_sb_dstrE[(Int_t)data[0]] = data[16];
	R_bb_dstr [(Int_t)data[0]] = data[18];
	R_bb_dstrE[(Int_t)data[0]] = data[19];
      }
    }
  }

  return;
}

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

  Read_Data( "calib.dat" );
  std::cout << std::setw(28) << std::right << " DECAY MODE "      << " : "
	    << std::setw(33) << std::left << " <TRUE,TRUE D> "    << " : "
	    << std::setw(33) << std::left << " <TRUE,FAKE D> "    << " : "
	    << std::setw(33) << std::left << " <FAKE,FAKE D> "    << " : "
	    << std::setw(33) << std::left << " <TRUE,TREU D*> "   << " : "
	    << std::setw(33) << std::left << " <TRUE,FAKE D*> "   << " : "
	    << std::setw(33) << std::left << " <FAKE,FAKE D*> "
	    << std::endl;
  for( Int_t idec=0; idec<nd_dec; idec++ ) std::cout << std::setw(20) << std::right << d_dec_name   [idec] << "("
						     << std::setw( 6) << std::right << d_dec        [idec] << ") : "
						     << std::setw(15) << std::right << R_ss_d       [idec] << " + "
						     << std::setw(15) << std::right << R_ss_dE      [idec] << " : "
						     << std::setw(15) << std::right << R_sb_d       [idec] << " + "
						     << std::setw(15) << std::right << R_sb_dE      [idec] << " : "
						     << std::setw(15) << std::right << R_bb_d       [idec] << " + "
						     << std::setw(15) << std::right << R_bb_dE      [idec] << " : "
						     << std::setw(15) << std::right << R_ss_dstr    [idec] << " + "
						     << std::setw(15) << std::right << R_ss_dstrE   [idec] << " : "
						     << std::setw(15) << std::right << R_sb_dstr    [idec] << " + "
						     << std::setw(15) << std::right << R_sb_dstrE   [idec] << " : "
						     << std::setw(15) << std::right << R_bb_dstr    [idec] << " + "
						     << std::setw(15) << std::right << R_bb_dstrE   [idec] << " : "
						     << std::endl;

  //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  std::stringstream sTmp;
  sTmp << " 1";
  //sTmp << " && (" << makeCut_dmass( 0.015, 0.015, 0.045, 0.030,
  //0.015, 0.015, 0.036, 0.024
  //).c_str()  << ")"; // dmass
  sTmp << " && (1.81 < d1_m && d1_m < 1.91 && 1.81 < d2_m && d2_m < 1.91)";
  sTmp << " && (" << makeCut_rem().c_str()    << ")"; // remaining track/pi0/Ks
  ///*
  sTmp << " && (" // deltam sideband
       << " ( abs(rm_dst1)==211 && (dm1<0.142 || dm1>0.149) ) || "
       << " ( abs(rm_dst2)==211 && (dm2<0.142 || dm2>0.149) ) || "
       << " ( abs(rm_dst1)==111 && (dm1<0.136 || dm1>0.146) ) || "
       << " ( abs(rm_dst2)==111 && (dm2<0.136 || dm2>0.146) ) "
       << ")";
  //*/
  sTmp << " && (abs(rm_dst2)==" << fl_dst << ") ";
  sTmp << " && " << selection;

  //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  std::cout << sTmp.str().c_str() << std::endl;
  // <Read Data file>
  TChain* c_dt = new TChain(treename);
  std::cout << "[DT] "
	    << c_dt->Add( infile_dt ) << " files : ";
  std::cout << c_dt->GetEntries() << " entries -> ";

  TTree* c_dt_cut = c_dt->CopyTree( Form("(%s)", sTmp.str().c_str()) );
  std::cout << c_dt_cut->GetEntries() << " entries" << std::endl;

  TChain* c_mc = new TChain(treename);
  std::cout << "[MC] "
	    << c_mc->Add( infile_mc ) << " files : ";
  std::cout << c_mc->GetEntries() << " entries -> ";
  TTree* c_mc_cut = c_mc->CopyTree( Form("(%s)", sTmp.str().c_str()) );
  std::cout << c_mc_cut->GetEntries() << " entries" << std::endl;


  //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  TH1D* nb_hist_mc    = new TH1D(    "nb_hist_mc",    "nb_hist_mc",   nb_xbin,   nb_xmin,   nb_xmax );    nb_hist_mc->Sumw2();
  TH1D* nb_hist_dt    = new TH1D(    "nb_hist_dt",    "nb_hist_dt",   nb_xbin,   nb_xmin,   nb_xmax );    nb_hist_dt->Sumw2();
  TH1D* eecl_hist_mc  = new TH1D(  "eecl_hist_mc",  "eecl_hist_mc", eecl_xbin, eecl_xmin, eecl_xmax );  eecl_hist_mc->Sumw2();
  TH1D* eecl_hist_dt  = new TH1D(  "eecl_hist_dt",  "eecl_hist_dt", eecl_xbin, eecl_xmin, eecl_xmax );  eecl_hist_dt->Sumw2();
  TH1D* dstp1_hist_mc = new TH1D( "dstp1_hist_mc", "dstp1_hist_mc", dstp_xbin, dstp_xmin, dstp_xmax ); dstp1_hist_mc->Sumw2();
  TH1D* dstp2_hist_mc = new TH1D( "dstp2_hist_mc", "dstp2_hist_mc", dstp_xbin, dstp_xmin, dstp_xmax ); dstp2_hist_mc->Sumw2();
  TH1D* dstp1_hist_dt = new TH1D( "dstp1_hist_dt", "dstp1_hist_dt", dstp_xbin, dstp_xmin, dstp_xmax ); dstp1_hist_dt->Sumw2();
  TH1D* dstp2_hist_dt = new TH1D( "dstp2_hist_dt", "dstp2_hist_dt", dstp_xbin, dstp_xmin, dstp_xmax ); dstp2_hist_dt->Sumw2();
  TH1D* dstpl_hist_mc = new TH1D( "dstpl_hist_mc", "dstpl_hist_mc", dstp_xbin, dstp_xmin, dstp_xmax ); dstpl_hist_mc->Sumw2();
  TH1D* dstph_hist_mc = new TH1D( "dstph_hist_mc", "dstph_hist_mc", dstp_xbin, dstp_xmin, dstp_xmax ); dstph_hist_mc->Sumw2();
  TH1D* dstpl_hist_dt = new TH1D( "dstpl_hist_dt", "dstpl_hist_dt", dstp_xbin, dstp_xmin, dstp_xmax ); dstpl_hist_dt->Sumw2();
  TH1D* dstph_hist_dt = new TH1D( "dstph_hist_dt", "dstph_hist_dt", dstp_xbin, dstp_xmin, dstp_xmax ); dstph_hist_dt->Sumw2();

  //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  for( Int_t ievt=0; ievt<c_mc_cut->GetEntries(); ievt++ ){
    c_mc_cut->GetEntry(ievt);
    Double_t weight = 1.0;
    weight *= c_mc_cut->GetLeaf("w1_mc")->GetValue(); // apply crrection for modeling of B1
    weight *= c_mc_cut->GetLeaf("w2_mc")->GetValue(); // apply crrection for modeling of B2
    weight *= c_mc_cut->GetLeaf("w1_bf")->GetValue(); // apply crrection for semileptonic branching fraction of B1
    weight *= c_mc_cut->GetLeaf("w2_bf")->GetValue(); // apply crrection for semileptonic branching fraction of B2
    if( c_mc_cut->GetLeaf("d1self")  ->GetValue()==1 ) weight *= R_ss_d   [dec_index((Int_t)(c_mc_cut->GetLeaf("rm_d1")->GetValue()))]; // apply correction factor for true D1
    else                                               weight *= R_bb_d   [dec_index((Int_t)(c_mc_cut->GetLeaf("rm_d1")->GetValue()))]; // apply correction factor for fake D1
    if( c_mc_cut->GetLeaf("d2self")  ->GetValue()==1 ) weight *= R_ss_d   [dec_index((Int_t)(c_mc_cut->GetLeaf("rm_d2")->GetValue()))]; // apply correction factor for true D2
    else                                               weight *= R_bb_d   [dec_index((Int_t)(c_mc_cut->GetLeaf("rm_d2")->GetValue()))]; // apply correction factor for fake D2
    if( c_mc_cut->GetLeaf("dst1self")->GetValue()==1 ) weight *= R_ss_dstr[dec_index((Int_t)(c_mc_cut->GetLeaf("rm_d1")->GetValue()))]; // apply correction factor for true D*1
    else                                               weight *= R_bb_dstr[dec_index((Int_t)(c_mc_cut->GetLeaf("rm_d1")->GetValue()))]; // apply correction factor for fake D*1
    if( c_mc_cut->GetLeaf("dst2self")->GetValue()==1 ) weight *= R_ss_dstr[dec_index((Int_t)(c_mc_cut->GetLeaf("rm_d2")->GetValue()))]; // apply correction factor for true D*2
    else                                               weight *= R_bb_dstr[dec_index((Int_t)(c_mc_cut->GetLeaf("rm_d2")->GetValue()))]; // apply correction factor for fake D*2
    
    weight /= (Double_t)nstream;

    nb_hist_mc   ->Fill( c_mc_cut->GetLeaf(   nb_brname)->GetValue(), weight );
    eecl_hist_mc ->Fill( c_mc_cut->GetLeaf( eecl_brname)->GetValue(), weight );
    dstp1_hist_mc->Fill( c_mc_cut->GetLeaf(dstp1_brname)->GetValue(), weight );
    dstp2_hist_mc->Fill( c_mc_cut->GetLeaf(dstp2_brname)->GetValue(), weight );

    if( c_mc_cut->GetLeaf("cosdl1")->GetValue() == c_mc_cut->GetLeaf("cosdll")->GetValue() ){
      dstpl_hist_mc->Fill( c_mc_cut->GetLeaf(dstp1_brname)->GetValue(), weight );
      dstph_hist_mc->Fill( c_mc_cut->GetLeaf(dstp2_brname)->GetValue(), weight );
    }else{
      dstph_hist_mc->Fill( c_mc_cut->GetLeaf(dstp1_brname)->GetValue(), weight );
      dstpl_hist_mc->Fill( c_mc_cut->GetLeaf(dstp2_brname)->GetValue(), weight );
    }
  }


  //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  for( Int_t ievt=0; ievt<c_dt_cut->GetEntries(); ievt++ ){
    c_dt_cut->GetEntry(ievt);
    nb_hist_dt   ->Fill( c_dt_cut->GetLeaf(  nb_brname )->GetValue() );
    eecl_hist_dt ->Fill( c_dt_cut->GetLeaf(eecl_brname )->GetValue() );
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
  nb_hist_dt->SetMarkerColor(1);
  nb_hist_dt->SetLineColor  (1);
  nb_hist_dt->SetMinimum(0.0);
  
  nb_hist_dt->Draw("P");
  nb_hist_mc->Draw("E2same");
  nb_hist_dt->Draw("Psame");

  can->cd(2);
  eecl_hist_mc->SetMarkerColor(13);
  eecl_hist_mc->SetFillColor  (13);
  eecl_hist_dt->SetMarkerColor(1);
  eecl_hist_dt->SetLineColor  (1);

  eecl_hist_dt->SetMinimum(0.0);
  eecl_hist_dt->Draw("P");
  eecl_hist_mc->Draw("E2same");
  eecl_hist_dt->Draw("Psame");

  can->cd(4);
  c_mc_cut->Draw("self");

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
  //c_mc_cut->Draw("dm2:dm1","abs(rm_dst2)==211","COLZ");

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
  //c_mc_cut->Draw("dm2:dm1","abs(rm_dst2)==211&&self==2","COLZ");
  //c_mc_cut->Draw("dm2:dm1","abs(rm_dst2)==111","COLZ");
  //c_dt_cut->Draw("dm2:dm1","0.05<eecl&&eecl<0.10","COLZ");
  
  //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  can->Update();
  can->Print( "pic/comparison_faked_dstr.eps" );
  std::cout << "finish" << std::endl;
  if( !gROOT->IsBatch() ) app.Run();
  return 0;
}

