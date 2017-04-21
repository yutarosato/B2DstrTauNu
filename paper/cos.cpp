#include "draws_.h"

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
///*
const Char_t* infile = "/home/belle/syutaro/dstrtaunu/modules/dstrtaunu/hbk/0p0_weight_nb_nocoscut/*s??*.root";
//*/

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
Int_t main( Int_t argc, Char_t** argv ){
  TApplication app( "app", &argc, argv );
  TStyle* sty = Style();
  sty->SetOptStat(0);
  sty->SetPadTickX(1);
  sty->SetPadTickY(1);
  sty->SetTickLength( 0.02, "XY" );

  //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  TChain* c = new TChain("h15");
  std::cout << "[infile] " << infile << " : ";
  std::cout << c->Add(infile)        << " files, ";
  std::cout << c->GetEntries()       << " entries" << std::endl;

  //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  TLegend* leg  = new TLegend( 0.55,0.65,0.99,0.94 );
  THStack* mh_cos  = new THStack( "mh_cos",  ";cos#theta_{B-D*l}"       );
  THStack* mh_atan = new THStack( "mh_atan", ";atan(cos#theta_{B-D*l})" );
  const Int_t nhist = 2; // 0(D* l nu ), 1(D* tau nu)
  TH1D**   hist_cos  = new TH1D*[nhist];
  TH1D**   hist_atan = new TH1D*[nhist];

  for( Int_t ihist=0; ihist<nhist; ihist++ ){
    hist_cos [ihist] = new TH1D( Form("hcos_%d",  ihist), Form("hcos_%d",  ihist), 100, -20, 5 );
    hist_atan[ihist] = new TH1D( Form("hatan_%d", ihist), Form("hatan_%d", ihist), 50,  -TMath::Pi()/2.0, TMath::Pi()/2.0 );
    hist_cos [ihist]->Sumw2();
    hist_atan[ihist]->Sumw2();
  }
  //++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  for( Int_t ievt=0; ievt<c->GetEntries(); ievt++ ){
    c->GetEntry(ievt);
    if( c->GetLeaf("self")->GetValue()!=1 ) continue;

    Double_t cosdlh = c->GetLeaf("cosdlh")->GetValue();
    Double_t cosdll = c->GetLeaf("cosdll")->GetValue();
    if( c->GetLeaf("semi1")->GetValue()==3 ){
      if( c->GetLeaf("recgen")->GetValue()==1 ){
	cosdlh = c->GetLeaf("cosdl2")->GetValue();
	cosdll = c->GetLeaf("cosdl1")->GetValue();
      }else if( c->GetLeaf("recgen")->GetValue()==-1 ){
	cosdlh = c->GetLeaf("cosdl1")->GetValue();
	cosdll = c->GetLeaf("cosdl2")->GetValue();
      }
    }else if( c->GetLeaf("semi2")->GetValue()==3 ){
      if( c->GetLeaf("recgen")->GetValue()==1 ){
	cosdlh = c->GetLeaf("cosdl1")->GetValue();
	cosdll = c->GetLeaf("cosdl2")->GetValue();
      }else if( c->GetLeaf("recgen")->GetValue()==-1 ){
	cosdlh = c->GetLeaf("cosdl2")->GetValue();
	cosdll = c->GetLeaf("cosdl1")->GetValue();
      }else{
	std::cout << "war1 : " << c->GetLeaf("recgen")->GetValue() << std::endl;
      }
    }else{
      std::cout << "war2 : " << c->GetLeaf("semi1")->GetValue()
		<< " : "     << c->GetLeaf("semi2")->GetValue()
		<< std::endl;
    }
    
    hist_cos[0]->Fill( cosdlh );
    hist_cos[1]->Fill( cosdll );
    hist_atan[0]->Fill( atan(cosdlh) );
    hist_atan[1]->Fill( atan(cosdll) );
  }
  
  //++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  hist_cos [0]->SetMarkerStyle(4);
  hist_atan[0]->SetMarkerStyle(4);
  for( Int_t ihist=0; ihist<nhist; ihist++ ){
    hist_cos [ihist]->Scale( 1.0/hist_cos [ihist]->Integral() );
    hist_atan[ihist]->Scale( 1.0/hist_atan[ihist]->Integral() );
    hist_cos [ihist]->SetLineColor  (ihist+1);
    hist_cos [ihist]->SetMarkerColor(ihist+1);
    hist_atan[ihist]->SetLineColor  (ihist+1);
    hist_atan[ihist]->SetMarkerColor(ihist+1);
    mh_cos ->Add( hist_cos [ihist] );
    mh_atan->Add( hist_atan[ihist] );
  }

  //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  TCanvas* can = Canvas( "can","can", 2 );
  can->Draw();
  can->cd(1); mh_cos ->Draw("nostack"); // nostackhistE, nostackhist, nostack
  can->cd(2); mh_atan->Draw("nostack");

  can->Print("pic/cos.eps");
  std::cout << "finish" << std::endl;
  app.Run();
  return 0;
}
