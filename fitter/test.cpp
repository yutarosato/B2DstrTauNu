#include "draws_.h"
#include "draws_fit_.h"

const Int_t xmin = 15;
const Int_t xmax = 17;

TH2D* get2D_nosmooth( const Char_t* infile ){
  TFile* file = new TFile( infile );
  if( file->IsZombie () ) std::cerr << "[ABORT] can not find pdf-file :" << infile << std::endl, abort();
  TH2D* hist = (TH2D*)file->Get("nb_eecl_dstst_nosmooth");
  if( hist== NULL ) std::cerr << "[ABORT] can not find  2d  histogram for " << infile << std::endl, abort();
  //hist->Scale( 1.0/hist->Integral() );
  hist->Print();
  return hist;
}

TH2D* get2D( const Char_t* infile ){
  TFile* file = new TFile( infile );
  if( file->IsZombie () ) std::cerr << "[ABORT] can not find pdf-file :" << infile << std::endl, abort();
  TH2D* hist = (TH2D*)file->Get("nb_eecl_dstst");
  if( hist== NULL ) std::cerr << "[ABORT] can not find  2d  histogram for " << infile << std::endl, abort();
  //hist->Scale( 1.0/hist->Integral() );
  hist->Print();
  return hist;
}

TH1D** get1DX( TH2D* hist, const Int_t col ){

  TH1D** hist_proj = new TH1D*[hist->GetNbinsY()];
  for( Int_t i=0; i<hist->GetNbinsY(); i++ ){
    hist_proj[i] = hist->ProjectionX( Form("_projx%d",i+1), i+1, i+1 );
    hist_proj[i]->SetLineColor  (col);
    hist_proj[i]->SetMarkerColor(col);
  }
  return hist_proj;
}

TH1D** get1DY( TH2D* hist, const Int_t col ){
  TH1D** hist_proj = new TH1D*[hist->GetNbinsX()];
  for( Int_t i=0; i<hist->GetNbinsX(); i++ ){
    hist_proj[i] = hist->ProjectionY( Form("_projy%d",i+1), i+1, i+1 );
    hist_proj[i]->SetLineColor  (col);
    hist_proj[i]->SetMarkerColor(col);
  }
  return hist_proj;
}

Int_t main( Int_t argc, Char_t** argv ){
  TApplication app( "app", &argc, argv );
  TStyle* sty = Style(10);

  TH2D*  hist0_2d    = get2D_nosmooth( "pdf_eecl_24bin_nb_30bin_w_dststmc_1/makepdf_dstst.root" );
  TH1D** hist0_1dx   = get1DX        ( hist0_2d,   1 );
  TH1D** hist0_1dy   = get1DY        ( hist0_2d,   1 );
  TH2D*  hist1_2d    = get2D         ( "pdf_eecl_24bin_nb_30bin_w_dststmc_1/makepdf_dstst.root" );
  TH1D** hist1_1dx   = get1DX        ( hist1_2d,   2 );
  TH1D** hist1_1dy   = get1DY        ( hist1_2d,   2 );
  //TH2D*  hist1000_2d  = get2D         ( "pic/testpdf_1.root" );
  //TH1D** hist1000_1dx = get1DX        ( hist1000_2d, 3 );
  //TH1D** hist1000_1dy = get1DY        ( hist1000_2d, 3 );
  TH2D*  hist1000_2d  = get2D         ( "pdf_eecl_24bin_nb_30bin_w_dststmc_1000_test/makepdf_dstst.root" );
  TH1D** hist1000_1dx = get1DX        ( hist1000_2d, 3 );
  TH1D** hist1000_1dy = get1DY        ( hist1000_2d, 3 );

  TCanvas* canx = Canvas( "canx", "canx", 4, 3 ); canx->Draw();
  TCanvas* cany = Canvas( "cany", "cany", 4, 3 ); cany->Draw();

  for( Int_t i=0; i<12; i++ ){ // NB
    canx->cd(i+1);
    hist0_1dx  [i]->Draw();
    hist1_1dx  [i]->Draw("same");
    hist1000_1dx[i]->Draw("same");
  }

  Int_t cnt=1;
  for( Int_t i=24-12; i<24; i++ ){ // EECL
    cany->cd(cnt);
    hist0_1dy  [i]->Draw();
    hist1_1dy  [i]->Draw("same");
    hist1000_1dy[i]->Draw("same");
    cnt++;
  }

  TH2D* sub = new TH2D( *hist0_2d );
  TH2D* div = new TH2D( *hist0_2d );
  for( Int_t ix=0; ix<sub->GetNbinsX(); ix++ ){
    for( Int_t iy=0; iy<sub->GetNbinsY(); iy++ ){
      double dz = hist1000_2d->GetBinContent(ix+1,iy+1) - sub->GetBinContent(ix+1,iy+1);
      double de = sqrt(
		       pow(hist1000_2d->GetBinError(ix+1,iy+1),2) + 
		       pow(sub        ->GetBinError(ix+1,iy+1),2)
		       );
      div->SetBinContent( ix+1, iy+1, (de ? dz/de : 0) );
      sub->SetBinContent( ix+1, iy+1, dz    );
    }
  }

  TCanvas* can = Canvas( "can", "can", 2, 1 );
  can->Draw();
  can->cd(1); sub->Draw("COLZ");
  can->cd(2); div->Draw("COLZ");
  

  canx->Update();
  cany->Update();
  std::cout << "finish" << std::endl;
  app.Run();
  return 0;
}
