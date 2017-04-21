// ///////////////////////////////////////////////////////////
// Weigthts for B -> D** l nu decays
// to correct the Belle generic MC (latest version).
// Using the LLSW model [arXiv:9705467]
// Detailed documentation: BN 1335
//
// Author: Jan Hasenbusch, Christian Oswald, Uni Bonn, 2013-2014.
// Version: 1.0
// ////////////////////////////////////////////////////////////

#include "const.h"

#ifndef SEMILEPD2STARWEIGHTS2D_H
#define SEMILEPD2STARWEIGHTS2D_H
class SemiLepD2StarWeights2D {
    private:
    std::map<int,int> lclass2index;
    std::map<int,int> index2lclass;
    TH2F*** hEntries;
    float lookup(int idx, int iBinW, int iBinCosTh, int iType);
    float lookup(int idx, float w_t, float CosTh_t, int iType);
    int nVarBins;
    int nMesons; // number of implemented lclass (6)
    const float* fTables[4]; // pointer to lclass tables (is set in the constructer)
    int nColumns[4]; // number of columns for each lclass table
    int nBinsCosTh[4]; // number cos theta bins for each lclass table
    float fCosThMin[4];
    float fCosThMax[4];
    int nBinsW[4]; // number of w bins for each lclass table
    float fWMin[4]; // minimum w value for each lclass table
    float fWMax[4]; // maximum w value for each lclass table
    int iPosWeight[4]; // column where the weight is stored in each lclass table
    int iPosErrStat[4]; // column where the statistic uncertainty is stored in each lclass table
    int iPosErrSyst[4]; // column where the systematic uncertainty is stored in each lclass table
    int iPosShape[4][3]; // column where the max change in shape is stored (0: normal shape; 1,2: deviation)
    void init(int nVarBins, const char* strVarName);

    public:
    SemiLepD2StarWeights2D();
    SemiLepD2StarWeights2D(int nVarBins, const char* strVarName);
    ~SemiLepD2StarWeights2D();
    static const float fWeights0[];
    static const float fWeights1[];
    static const float fWeights2[];
    static const float fWeights3[];
    float weight(int lclass, float w_t, float CosTh_t, int iVarBin=0);
    float errStat(int lclass, int iBinW, int iBinCosTh);
    float errSyst(int lclass, int iBinW, int iBinCosTh);
    float errStat(int lclass, float w_t, float CosTh_t); // added @20141113
    float errSyst(int lclass, float w_t, float CosTh_t); // added @20141113
    float calcBinError(int iVarBin);
    float calcBinError(int iVarBin, bool isSyst);
    void reset();
    void setShape(int lclass, int iShape);
    void resetShapes( void );
};

#endif //SEMILEPD2STARWEIGHTS2D_H
