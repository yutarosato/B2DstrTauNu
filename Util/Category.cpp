#include "Category.h"

std::string makeCategory_recBBDD( Int_t fl_bb, Int_t fl_dd ){
  std::stringstream sTmp;
  sTmp << "rm_bb==" << fl_bb+3 << " && "
       << "rm_dd==" << fl_dd+1;
  return sTmp.str();
}
