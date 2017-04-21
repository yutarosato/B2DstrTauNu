// ///////////////////////////////////////////////////////////
// Weigthts for B -> D(*) l nu and Bs -> Ds(*) l nu decays
// to correct the Belle generic MC (latest version).
// Using HFAG 2013 form factors and the HQET2 EvtGen model.
// Detailed documentation: BN 1335
//
// Author: Christian Oswald, Uni Bonn, 2013-2014.
// Version: 1.0
// ////////////////////////////////////////////////////////////


#include "const.h"

#ifndef SEMILEPWEIGHTS2D_H
#define SEMILEPWEIGHTS2D_H
class SemiLepWeights2D {
    private:
    TH2F*** hEntries;
    float lookup(int lclass, int iBinQ2, int iBinLepMom, int iType);
    float lookup(int lclass, float q2_t, float lep_ps_t, int iType);
    std::map<int,int> lclass2index;
    std::map<int,int> index2lclass;
    int nVarBins;
    int nlclass; // number of implemented lclass (4)
    const float* fTables[4]; // pointer to lclass tables (is set in the constructer)
    int nColumns[4]; // number of columns for each lclass table
    int nBinsLepMom[4]; // number p_l bins for each lclass table
    int nBinsQ2[4]; // number of q2 bins for each lclass table
    float fQ2Min[4]; // minimum q2 value for each lclass table
    float fQ2Max[4]; // maximum q2 value for each lclass table
    int iPosWeight[4]; // column where the weight is stored in each lclass table
    int iPosErrStat[4]; // column where the statistic uncertainty is stored in each lclass table
    int iPosErrSyst[4]; // column where the systematic uncertainty is stored in each lclass table
    void init(int nVarBins, const char* strVarName);
    public:
    SemiLepWeights2D();
    SemiLepWeights2D(int nVarBins, const char* strVarName);
    ~SemiLepWeights2D();
    static const float fLepMomMin;
    static const float fLepMomMax;
    static const float f2DWeightsCoarse1[];
    static const float f2DWeightsCoarse2[];
    static const float f2DWeightsFine1[];
    static const float f2DWeightsFine2[];
    static const float f2DWeightsCoarse7[];
    static const float f2DWeightsCoarse9[];
    float weight(int lclass, float q2_t, float lep_ps_t, int iVarBin=0);
    float errStat(int lclass, int iBinQ2, int iBinLepMom);
    float errSyst(int lclass, int iBinQ2, int iBinLepMom);
    float errStat(int lclass, float q2_t, float lep_ps_t); // added @20141113
    float errSyst(int lclass, float q2_t, float lep_ps_t); // added @20141113
    float calcBinError(int iVarBin);
    float calcBinError(int iVarBin, bool isSyst);
    void reset();
};

#endif //SEMILEPWEIGHTS2D_H
