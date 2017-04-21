#ifndef Object_H
#define Object_H

#include "const.h"

// [ TH1D ]
TH1D**     makeHist( const Char_t* tag, const Int_t xbin, const Double_t xmin, const Double_t xmax, const Int_t n1 );
TH1D***    makeHist( const Char_t* tag, const Int_t xbin, const Double_t xmin, const Double_t xmax, const Int_t n1, const Int_t n2 );
TH1D****   makeHist( const Char_t* tag, const Int_t xbin, const Double_t xmin, const Double_t xmax, const Int_t n1, const Int_t n2, const Int_t n3 );
TH1D*****  makeHist( const Char_t* tag, const Int_t xbin, const Double_t xmin, const Double_t xmax, const Int_t n1, const Int_t n2, const Int_t n3, const Int_t n4 );
TH1D****** makeHist( const Char_t* tag, const Int_t xbin, const Double_t xmin, const Double_t xmax, const Int_t n1, const Int_t n2, const Int_t n3, const Int_t n4, const Int_t n5 );
// [ THStack ]
THStack**     makeStack( const Char_t* tag, const Int_t n1 );
THStack***    makeStack( const Char_t* tag, const Int_t n1, const Int_t n2 );
THStack****   makeStack( const Char_t* tag, const Int_t n1, const Int_t n2, const Int_t n3 );
THStack*****  makeStack( const Char_t* tag, const Int_t n1, const Int_t n2, const Int_t n3, const Int_t n4 );
THStack****** makeStack( const Char_t* tag, const Int_t n1, const Int_t n2, const Int_t n3, const Int_t n4, const Int_t n5 );
// [ TH1D ]
TH1D**     makeHist( const Char_t* tag, const Int_t* xbin, const Double_t* xmin, const Double_t* xmax, const Int_t n1 );
TH1D***    makeHist( const Char_t* tag, const Int_t* xbin, const Double_t* xmin, const Double_t* xmax, const Int_t n1, const Int_t n2 );
TH1D****   makeHist( const Char_t* tag, const Int_t* xbin, const Double_t* xmin, const Double_t* xmax, const Int_t n1, const Int_t n2, const Int_t n3 );
TH1D*****  makeHist( const Char_t* tag, const Int_t* xbin, const Double_t* xmin, const Double_t* xmax, const Int_t n1, const Int_t n2, const Int_t n3, const Int_t n4 );
TH1D****** makeHist( const Char_t* tag, const Int_t* xbin, const Double_t* xmin, const Double_t* xmax, const Int_t n1, const Int_t n2, const Int_t n3, const Int_t n4, const Int_t n5 );

// [ TH2D ]
TH2D**     makeHist( const Char_t* tag, const Int_t xbin, const Double_t xmin, const Double_t xmax, const Int_t ybin, const Double_t ymin, const Double_t ymax, const Int_t n1 );
TH2D***    makeHist( const Char_t* tag, const Int_t xbin, const Double_t xmin, const Double_t xmax, const Int_t ybin, const Double_t ymin, const Double_t ymax, const Int_t n1, const Int_t n2 );
TH2D****   makeHist( const Char_t* tag, const Int_t xbin, const Double_t xmin, const Double_t xmax, const Int_t ybin, const Double_t ymin, const Double_t ymax, const Int_t n1, const Int_t n2, const Int_t n3 );
TH2D*****  makeHist( const Char_t* tag, const Int_t xbin, const Double_t xmin, const Double_t xmax, const Int_t ybin, const Double_t ymin, const Double_t ymax, const Int_t n1, const Int_t n2, const Int_t n3, const Int_t n4 );
TH2D****** makeHist( const Char_t* tag, const Int_t xbin, const Double_t xmin, const Double_t xmax, const Int_t ybin, const Double_t ymin, const Double_t ymax, const Int_t n1, const Int_t n2, const Int_t n3, const Int_t n4, const Int_t n5 );

// [ TH2D ]
TH2D***    makeHist( const Char_t* tag, const Int_t* xbin, const Double_t* xmin, const Double_t* xmax, const Int_t* ybin, const Double_t* ymin, const Double_t* ymax, const Int_t n1, const Int_t n2 );
TH2D****   makeHist( const Char_t* tag, const Int_t* xbin, const Double_t* xmin, const Double_t* xmax, const Int_t* ybin, const Double_t* ymin, const Double_t* ymax, const Int_t n1, const Int_t n2, const Int_t n3 );
TH2D*****  makeHist( const Char_t* tag, const Int_t* xbin, const Double_t* xmin, const Double_t* xmax, const Int_t* ybin, const Double_t* ymin, const Double_t* ymax, const Int_t n1, const Int_t n2, const Int_t n3, const Int_t n4 );
TH2D****** makeHist( const Char_t* tag, const Int_t* xbin, const Double_t* xmin, const Double_t* xmax, const Int_t* ybin, const Double_t* ymin, const Double_t* ymax, const Int_t n1, const Int_t n2, const Int_t n3, const Int_t n4, const Int_t n5 );

// [ TChain ]
TChain** makeChain( const Char_t* treename, const Int_t n1 );

#endif
