#ifndef PI0_EFF_H
#define PI0_EFF_H

#include <stdio.h>

class pi0_eff 
{

public:
  pi0_eff();
  virtual ~pi0_eff(){};

  void   add(double p);
  double total_effFactor(); //total eff correction after all events
  double total_errFactor(); //total uncertainty after all events
  int    get_totalNum   (); // return the total number of events up to this point
                            // (total number being used in weighing the eff. and errors)

private:
  static const double table_err[12];
  static const double table_eff[12];

  int bin_count[12];// counts events in momentum/cosTheta bins
  int global_count; // keeps track of total num of events (sum of all bin_count[12])

};

#endif
