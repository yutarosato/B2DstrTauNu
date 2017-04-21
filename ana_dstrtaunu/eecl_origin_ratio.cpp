#include "draws_.h"

//const Char_t* infile     = "~/dstrtaunu/modules/dstrtaunu/hbk/store/hbk8_merge_cut/gMC_*.root";
const Char_t* infile = "~/dstrtaunu/ana/NB/hbk/hbk_mode0_test04_nor_setAA_HH/sigMC_*.root";
//const Char_t* infile     = "~/dstrtaunu/modules/dstrtaunu/hbk/store/hbk8/???_kpi_through_cut/sigMC_*.root";
const Char_t* tname      = "h15";
const Char_t* outname    = "eecl_origin";

const Int_t necl_ctgry = 29;
const Char_t* ecl_ctgry_name[necl_ctgry] = {
  "other", // 0
  "beam B.G.", // 1
  "#Lambda", // 2
  "K_{S}#rightarrow#pi^{+}#pi^{-}", // 3
  "K_{s}#rightarrow#pi^{0}#pi^{0}", // 4
  "K_{L}", // 5
  "neutron", // 6
  "neutral baryon", // 7
  "#gamma from #pi^{0} from D", // 8
  "#gamma from #pi^{0} from D*", // 9
  "#gamma from #pi^{0} from D**", // 10
  "#gamma from #pi^{0} from Ds(*)", // 11
  "#gamma from #pi^{0} from others", // 12
  "#gamma from #eta", // 13
  "#gamma from D*", // 14
  "#gamma from B (brems.)", // 15
  "#gamma from other", // 16
  "K track", // 17
  "K shower", // 18
  "#pi track", // 19
  "#pi shower", // 20
  "electron track", // 21
  "electron shower", // 22
  "muon track", // 23
  "muon shower", // 24
  "proton track", // 25
  "proton shower", // 26
  "charged baryon track", // 27
  "charged baryon shower", // 28
};

const Int_t nhist = 8;
const Char_t* ctgry_name[nhist] = {
  "sig",
  "sig_loweecl",
  "sig_higheecl_nbpeak",
  "sig_higheecl_nbnonpeak",
  "nor",
  "nor_loweecl",
  "nor_higheecl_nbpeak",
  "nor_higheecl_nbnonpeak",
};
const Char_t* ctgry_selection[nhist] = {
  "self==1",
  "self==1&&eecl<1.5",
  "self==1&&eecl>1.5&&abs(nb_mode0_test04_nor-0.6)<0.1",
  "self==1&&eecl>1.5&&abs(nb_mode0_test04_nor-0.6)>0.1",
  "self==2",
  "self==2&&eecl<1.5",
  "self==2&&eecl>1.5&&abs(nb_mode0_test04_nor-0.6)<0.1",
  "self==2&&eecl>1.5&&abs(nb_mode0_test04_nor-0.6)>0.1",
};


void makeEECLHist( TChain* fchain, TH1D** fhist, const Char_t* fname, const Char_t* fselection );
void plotEECLHist( TCanvas* fcan,  TH1D** fhist, const Char_t* fname );
// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Int_t main( Int_t argc, Char_t** argv ){
  TApplication app( "app", &argc, argv );
  TStyle* sty = Style(10);
  sty->SetPadBottomMargin(0.25);
  gROOT->SetBatch(true); // tmpppppp

  TChain* chain = new TChain(tname);
  std::cout << chain->Add(infile)  << " files, ";
  std::cout << chain->GetEntries() << " entries, "
	    << infile
	    << std::endl;


  TH1D*** hist = new TH1D**[nhist];
  for( Int_t ihist=0; ihist<nhist; ihist++ ){
    hist[ihist] = new TH1D*[4]; // 0(E_ECL distribution), 1(ratio of origin), 2(average energy/events), 3(average energy/hits)
    makeEECLHist( chain, hist[ihist], ctgry_name[ihist], ctgry_selection[ihist] );
  }

  TCanvas* can = Canvas( "can_eecl", "can_eecl", 2, 2 );
  can->Print("pic/eecl_origin.ps[");
  for( Int_t ihist=0; ihist<nhist; ihist++ ) plotEECLHist( can, hist[ihist], ctgry_name[ihist] );

  TLegend* leg = new TLegend( 0.75,0.75,0.99,0.99 );
  THStack* hs  = new THStack( "summary", "E_{ECL}" );
  
  for( Int_t ihist=0; ihist<nhist; ihist++ ){
    hist[ihist][0]->SetLineColor  (ihist+1);
    hist[ihist][0]->Scale( 1.0/hist[ihist][0]->GetEntries() );
    hs->Add( hist[ihist][0] );

    hist[ihist][2]->SetLineColor  (ihist+1);
    hist[ihist][2]->SetMarkerColor(ihist+1);
    leg->AddEntry( hist[ihist][2], ctgry_name[ihist], "PL" );

    hist[ihist][3]->SetLineColor  (ihist+1);
    hist[ihist][3]->SetMarkerColor(ihist+1);
  }

  can->cd(0);
  can->Clear();
  can->Divide(2,2);

  can->cd(1);
  hs->Draw("nostack");
  hs->GetXaxis()->SetTitle("E_{ECL} [GeV]"  );
  hs->GetYaxis()->SetTitle("Entries/(50MeV)");

  can->cd(3);
  for( Int_t ihist=0; ihist<nhist; ihist++ ) hist[ihist][2]->Draw( (ihist==0 ? "PL" : "PLsame") );
  leg->Draw();

  can->cd(4);
  for( Int_t ihist=0; ihist<nhist; ihist++ ) hist[ihist][3]->Draw( (ihist==0 ? "PL" : "PLsame") );

  can->Update();
  can->Print( "pic/eecl_origin.ps" );

  can->Print("pic/eecl_origin.ps]");
  system( "ps2pdf pic/eecl_origin.ps pic/eecl_origin.pdf" );
  std::cout << "finish" << std::endl;
  if( !gROOT->IsBatch() ) app.Run();

  return 0;
}

void makeEECLHist( TChain* fchain, TH1D** fhist, const Char_t* fname, const Char_t* fselection ){
  TTree* tree = fchain->CopyTree( fselection );
  Int_t nevt = tree->GetEntries();

  Double_t eecl_tot=0;
  Double_t eecl [necl_ctgry]={0};
  Int_t    neecl[necl_ctgry]={0};
  for( Int_t ievt=0; ievt<tree->GetEntries(); ievt++ ){ // entry loop
    tree->GetEntry(ievt);
    eecl_tot += tree->GetLeaf( "eecl" )->GetValue();
    for( Int_t iecl=0; iecl<necl_ctgry; iecl ++ ){
      eecl[iecl]  +=        tree->GetLeaf( Form("eecl_%d", iecl) )->GetValue();
      neecl[iecl] += (Int_t)tree->GetLeaf( Form("neecl_%d",iecl) )->GetValue();
    }
  }

  std::cout << "[selection] "
	    << std::setw(20) << std::right << fname << " ("
	    << std::setw(10) << std::right << nevt  << ") : "
	    << std::setw(10) << std::right << eecl_tot/tree->GetEntries() << " (eecl/events[average])" << std::endl;

  
  fhist[0] = new TH1D( Form("eecl_%s",    fname), Form("E_{ECL}(%s)",         fname), 24, 0.0, 1.2 );
  fhist[1] = new TH1D( Form("ratio_%s",   fname), Form("Ratio of E_{ECL}(%s)",fname), 30, 0,   30  );
  fhist[2] = new TH1D( Form("ave_evt_%s", fname), Form("E_{ECL}/events (%s)", fname), 30, 0,   30  );  
  fhist[3] = new TH1D( Form("ave_hit_%s", fname), Form("E_{ECL}/hits (%s)",   fname), 30, 0,   30  );  


  // hist[0]
  tree->Project( Form("eecl_%s",fname), "eecl" );
  fhist[0]->SetXTitle( "E_{ECL} [GeV]"   );
  fhist[0]->SetYTitle( "Entries/(50MeV)" );

  // hist[1]
  for( Int_t iecl=0; iecl<necl_ctgry; iecl ++ ){
    fhist[1]->SetBinContent( iecl+1, 100.0*eecl[iecl]/eecl_tot  );
    ((TAxis*)fhist[1]->GetXaxis())->SetBinLabel(  iecl+1, ecl_ctgry_name[iecl] );
  }
  fhist[1]->LabelsOption ("v");
  fhist[1]->SetLabelSize(0.04,"x");
  fhist[1]->SetYTitle("Ratio [%]");

  // hist[2]
  for( Int_t iecl=0; iecl<necl_ctgry; iecl ++ ){
    fhist[2]->SetBinContent( iecl+1, 1000*eecl[iecl]/nevt );
    ((TAxis*)fhist[2]->GetXaxis())->SetBinLabel(  iecl+1, ecl_ctgry_name[iecl] );
  }
  fhist[2]->LabelsOption ("v");
  fhist[2]->SetLabelSize(0.04,"x");
  fhist[2]->SetYTitle("E_{ECL} per events [MeV]");
  //fhist[2]->SetMaximum(350);

  // hist[3]
  for( Int_t iecl=0; iecl<necl_ctgry; iecl ++ ){
    fhist[3]->SetBinContent( iecl+1, neecl[iecl]==0 ? 0 : 1000*eecl[iecl]/neecl[iecl] );
    ((TAxis*)fhist[3]->GetXaxis())->SetBinLabel(  iecl+1, ecl_ctgry_name[iecl] );
  }
  fhist[3]->LabelsOption ("v");
  fhist[3]->SetLabelSize(0.04,"x");
  fhist[3]->SetYTitle("E_{ECL} per hits [MeV]");
  //fhist[3]->SetMaximum(1000);

  return;
}

void plotEECLHist( TCanvas* fcan, TH1D** fhist, const Char_t* fname ){
  fcan->cd(0);
  fcan->Clear();
  fcan->Divide(2,2);

  fcan->cd(1);
  fhist[0]->DrawCopy();

  fcan->cd(2);
  fcan->cd(2)->SetGridy(1);
  fhist[1]->SetFillColor(9);
  fhist[1]->DrawCopy();
  fhist[1]->SetFillColor(0);

  fcan->cd(3);
  fcan->cd(3)->SetGridy(1);
  fhist[2]->SetFillColor(9);
  fhist[2]->DrawCopy();
  fhist[2]->SetFillColor(0);

  fcan->cd(4);
  fcan->cd(4)->SetGridy(1);
  fhist[3]->SetFillColor(9);
  fhist[3]->DrawCopy();
  fhist[3]->SetFillColor(0);
   
  fcan->Update();
  fcan->Print( "pic/eecl_origin.ps" );
}
