#include "Print.h"

void Print( TH1D* hist, const Int_t xbin, const Double_t xmin, const Double_t xmax ){
  std::cout << std::setw(10) << std::right << hist->GetEntries()          << "( "
	    << std::setw(10) << std::right << hist->GetBinContent(0)      << " / "
	    << std::setw(10) << std::right << hist->Integral()            << " / "
	    << std::setw(10) << std::right << hist->GetBinContent(xbin+1) << " )";
  if( xmax - xmin ) std::cout << " -> " << std::setw(10) << std::right << hist->Integral(
											 hist->FindBin(xmin+0.00000000001),
											 hist->FindBin(xmax-0.00000000001)
											 );
  std::cout << " events : ";
  return;
}
