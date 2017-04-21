#include "Object.h"


// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++;
TH1D** makeHist( const Char_t* tag, const Int_t xbin, const Double_t xmin, const Double_t xmax, const Int_t n1 ){
  TH1D** hist = new TH1D*[n1];
  for( Int_t i1=0; i1<n1; i1++ ){
    hist[i1] = new TH1D( Form("%s_%d",tag,i1), Form("%s_%d",tag,i1), xbin, xmin, xmax );
  }
  return hist;
}

TH1D*** makeHist( const Char_t* tag, const Int_t xbin, const Double_t xmin, const Double_t xmax, const Int_t n1, const Int_t n2 ){
  TH1D*** hist = new TH1D**[n1];
  for( Int_t i1=0; i1<n1; i1++ ){
    hist[i1] = makeHist( Form("%s_%d",tag,i1), xbin, xmin, xmax, n2 );
  }
  return hist;
}

TH1D**** makeHist( const Char_t* tag, const Int_t xbin, const Double_t xmin, const Double_t xmax, const Int_t n1, const Int_t n2, const Int_t n3 ){
  TH1D**** hist = new TH1D***[n1];
  for( Int_t i1=0; i1<n1; i1++ ){
    hist[i1] = makeHist( Form("%s_%d",tag,i1), xbin, xmin, xmax, n2, n3 );
  }
  return hist;
}

TH1D***** makeHist( const Char_t* tag, const Int_t xbin, const Double_t xmin, const Double_t xmax, const Int_t n1, const Int_t n2, const Int_t n3, const Int_t n4 ){
  TH1D***** hist = new TH1D****[n1];
  for( Int_t i1=0; i1<n1; i1++ ){
    hist[i1] = makeHist( Form("%s_%d",tag,i1), xbin, xmin, xmax, n2, n3, n4 );
  }
  return hist;
}

TH1D****** makeHist( const Char_t* tag, const Int_t xbin, const Double_t xmin, const Double_t xmax, const Int_t n1, const Int_t n2, const Int_t n3, const Int_t n4, const Int_t n5 ){
  TH1D****** hist = new TH1D*****[n1];
  for( Int_t i1=0; i1<n1; i1++ ){
    hist[i1] = makeHist( Form("%s_%d",tag,i1), xbin, xmin, xmax, n2, n3, n4, n5 );
  }
  return hist;
}
// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++;

THStack** makeStack( const Char_t* tag, const Int_t n1 ){
  THStack** stack = new THStack*[n1];
  for( Int_t i1=0; i1<n1; i1++ ){
    stack[i1] = new THStack( Form("%s_%d",tag,i1), Form("%s_%d",tag,i1) );
  }
  return stack;
}

THStack*** makeStack( const Char_t* tag, const Int_t n1, const Int_t n2 ){
  THStack*** stack = new THStack**[n1];
  for( Int_t i1=0; i1<n1; i1++ ){
    stack[i1] = makeStack( Form("%s_%d",tag,i1), n2 );
  }
  return stack;
}

THStack**** makeStack( const Char_t* tag, const Int_t n1, const Int_t n2, const Int_t n3 ){
  THStack**** stack = new THStack***[n1];
  for( Int_t i1=0; i1<n1; i1++ ){
    stack[i1] = makeStack( Form("%s_%d",tag,i1), n2, n3 );
  }
  return stack;
}

THStack***** makeStack( const Char_t* tag, const Int_t n1, const Int_t n2, const Int_t n3, const Int_t n4 ){
  THStack***** stack = new THStack****[n1];
  for( Int_t i1=0; i1<n1; i1++ ){
    stack[i1] = makeStack( Form("%s_%d",tag,i1), n2, n3, n4 );
  }
  return stack;
}

THStack****** makeStack( const Char_t* tag, const Int_t n1, const Int_t n2, const Int_t n3, const Int_t n4, const Int_t n5 ){
  THStack****** stack = new THStack*****[n1];
  for( Int_t i1=0; i1<n1; i1++ ){
    stack[i1] = makeStack( Form("%s_%d",tag,i1), n2, n3, n4, n5 );
  }
  return stack;
}
// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++;
TH1D** makeHist( const Char_t* tag, const Int_t* xbin, const Double_t* xmin, const Double_t* xmax, const Int_t n1 ){
  TH1D** hist = new TH1D*[n1];
  for( Int_t i1=0; i1<n1; i1++ ){
    hist[i1] = new TH1D( Form("%s_%d",tag,i1), Form("%s_%d",tag,i1), xbin[i1], xmin[i1], xmax[i1] );
  }
  return hist;
}

TH1D*** makeHist( const Char_t* tag, const Int_t* xbin, const Double_t* xmin, const Double_t* xmax, const Int_t n1, const Int_t n2 ){
  TH1D*** hist = new TH1D**[n1];
  for( Int_t i1=0; i1<n1; i1++ ){
    hist[i1] = makeHist( Form("%s_%d",tag,i1), xbin, xmin, xmax, n2 );
  }
  return hist;
}

TH1D**** makeHist( const Char_t* tag, const Int_t* xbin, const Double_t* xmin, const Double_t* xmax, const Int_t n1, const Int_t n2, const Int_t n3 ){
  TH1D**** hist = new TH1D***[n1];
  for( Int_t i1=0; i1<n1; i1++ ){
    hist[i1] = makeHist( Form("%s_%d",tag,i1), xbin, xmin, xmax, n2, n3 );
  }
  return hist;
}

TH1D***** makeHist( const Char_t* tag, const Int_t* xbin, const Double_t* xmin, const Double_t* xmax, const Int_t n1, const Int_t n2, const Int_t n3, const Int_t n4 ){
  TH1D***** hist = new TH1D****[n1];
  for( Int_t i1=0; i1<n1; i1++ ){
    hist[i1] = makeHist( Form("%s_%d",tag,i1), xbin, xmin, xmax, n2, n3, n4 );
  }
  return hist;
}

TH1D****** makeHist( const Char_t* tag, const Int_t* xbin, const Double_t* xmin, const Double_t* xmax, const Int_t n1, const Int_t n2, const Int_t n3, const Int_t n4, const Int_t n5 ){
  TH1D****** hist = new TH1D*****[n1];
  for( Int_t i1=0; i1<n1; i1++ ){
    hist[i1] = makeHist( Form("%s_%d",tag,i1), xbin, xmin, xmax, n2, n3, n4, n5 );
  }
  return hist;
}

// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++;
TH2D** makeHist( const Char_t* tag, const Int_t xbin, const Double_t xmin, const Double_t xmax, const Int_t ybin, const Double_t ymin, const Double_t ymax, const Int_t n1 ){
  TH2D** hist = new TH2D*[n1];
  for( Int_t i1=0; i1<n1; i1++ ){
    hist[i1] = new TH2D( Form("%s_%d",tag,i1), Form("%s_%d",tag,i1), xbin, xmin, xmax, ybin, ymin, ymax );
  }
  return hist;
}

TH2D*** makeHist( const Char_t* tag, const Int_t xbin, const Double_t xmin, const Double_t xmax, const Int_t ybin, const Double_t ymin, const Double_t ymax, const Int_t n1, const Int_t n2 ){
  TH2D*** hist = new TH2D**[n1];
  for( Int_t i1=0; i1<n1; i1++ ){
    hist[i1] = makeHist( Form("%s_%d",tag,i1), xbin, xmin, xmax, ybin, ymin, ymax, n2 );
  }
  return hist;
}

TH2D**** makeHist( const Char_t* tag, const Int_t xbin, const Double_t xmin, const Double_t xmax, const Int_t ybin, const Double_t ymin, const Double_t ymax, const Int_t n1, const Int_t n2, const Int_t n3 ){
  TH2D**** hist = new TH2D***[n1];
  for( Int_t i1=0; i1<n1; i1++ ){
    hist[i1] = makeHist( Form("%s_%d",tag,i1), xbin, xmin, xmax, ybin, ymin, ymax, n2, n3 );
  }
  return hist;
}

TH2D***** makeHist( const Char_t* tag, const Int_t xbin, const Double_t xmin, const Double_t xmax, const Int_t ybin, const Double_t ymin, const Double_t ymax, const Int_t n1, const Int_t n2, const Int_t n3, const Int_t n4 ){
  TH2D***** hist = new TH2D****[n1];
  for( Int_t i1=0; i1<n1; i1++ ){
    hist[i1] = makeHist( Form("%s_%d",tag,i1), xbin, xmin, xmax, ybin, ymin, ymax, n2, n3, n4 );
  }
  return hist;
}

TH2D****** makeHist( const Char_t* tag, const Int_t xbin, const Double_t xmin, const Double_t xmax, const Int_t ybin, const Double_t ymin, const Double_t ymax, const Int_t n1, const Int_t n2, const Int_t n3, const Int_t n4, const Int_t n5 ){
  TH2D****** hist = new TH2D*****[n1];
  for( Int_t i1=0; i1<n1; i1++ ){
    hist[i1] = makeHist( Form("%s_%d",tag,i1), xbin, xmin, xmax, ybin, ymin, ymax, n2, n3, n4, n5 );
  }
  return hist;
}

// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++;

TH2D*** makeHist( const Char_t* tag, const Int_t* xbin, const Double_t* xmin, const Double_t* xmax, const Int_t* ybin, const Double_t* ymin, const Double_t* ymax, const Int_t n1, const Int_t n2 ){
  TH2D*** hist = new TH2D**[n1];
  for( Int_t i1=0; i1<n1; i1++ ){
    hist[i1] = new TH2D*[n2];
    for( Int_t i2=0; i2<n2; i2++ ){
      hist[i1][i2] = new TH2D( Form("%s_%d_%d",tag,i1,i2), Form("%s_%d_%d",tag,i1,i2), xbin[i1], xmin[i1], xmax[i1], ybin[i2], ymin[i2], ymax[i2] );
    }
  }
  return hist;
}

TH2D**** makeHist( const Char_t* tag, const Int_t* xbin, const Double_t* xmin, const Double_t* xmax, const Int_t* ybin, const Double_t* ymin, const Double_t* ymax, const Int_t n1, const Int_t n2, const Int_t n3 ){
  TH2D**** hist = new TH2D***[n1];
  for( Int_t i1=0; i1<n1; i1++ ){
    hist[i1] = makeHist( Form("%s_%d",tag,i1), xbin, xmin, xmax, ybin, ymin, ymax, n2, n3 );
  }
  return hist;
}

TH2D***** makeHist( const Char_t* tag, const Int_t* xbin, const Double_t* xmin, const Double_t* xmax, const Int_t* ybin, const Double_t* ymin, const Double_t* ymax, const Int_t n1, const Int_t n2, const Int_t n3, const Int_t n4 ){
  TH2D***** hist = new TH2D****[n1];
  for( Int_t i1=0; i1<n1; i1++ ){
    hist[i1] = makeHist( Form("%s_%d",tag,i1), xbin, xmin, xmax, ybin, ymin, ymax, n2, n3, n4 );
  }
  return hist;
}

TH2D****** makeHist( const Char_t* tag, const Int_t* xbin, const Double_t* xmin, const Double_t* xmax, const Int_t* ybin, const Double_t* ymin, const Double_t* ymax, const Int_t n1, const Int_t n2, const Int_t n3, const Int_t n4, const Int_t n5 ){
  TH2D****** hist = new TH2D*****[n1];
  for( Int_t i1=0; i1<n1; i1++ ){
    hist[i1] = makeHist( Form("%s_%d",tag,i1), xbin, xmin, xmax, ybin, ymin, ymax, n2, n3, n4, n5 );
  }
  return hist;
}

// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++;

TChain** makeChain( const Char_t* treename, const Int_t n1 ){
  TChain** chain = new TChain*[n1];
  for( Int_t i1=0; i1<n1; i1++ ) chain[i1] = new TChain(treename);
  return chain;
}

