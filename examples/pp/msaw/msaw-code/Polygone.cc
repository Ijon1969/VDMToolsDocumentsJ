//
// THIS FILE IS AUTOMATICALLY GENERATED!!
//
// Generated at Wed 05-Nov-97 by the VDM++toC++ Code Generator
// (v6.0e - Tue 04-Nov-97)
//
// Supported compilers:
// 	g++ version 2.7.2 on SunOS4, SunOS5, Linux, HP-UX10
// 	Dec cxx version 5.5 on Alpha OSF1
// 	VC++ version 5.0 on Windows95, Windows NT
//



#include "Polygone.h"

vdm_Polygone::vdm_Polygone() { RegisterAsDerived(vdm_GetId()); }

Bool vdm_Polygone::vdm_DansPolygone(const Tuple &var_1_1, const Set &var_2_2) {
  Set vdm_sommets;
  Int vdm_x;
  Int vdm_y;
  bool succ_3 = true;
  if (var_1_1.IsTuple()) {
    Sequence e_l_5;
    for (int i_6 = 1; i_6 <= ((Tuple) var_1_1).Length(); i_6++) 
      e_l_5.ImpAppend(((Tuple) var_1_1).GetField(i_6));
    if (succ_3 = 2 == (Int) e_l_5.Length()) {
      vdm_x = (Int) e_l_5.Hd();
      vdm_y = (Int) e_l_5[2];
    }
  }
  else 
    succ_3 = false;
  vdm_sommets = var_2_2;
  if (!succ_3) 
    RunTime("Pattern Match in Function Apply in function : DansPolygone failed");
  Generic varRes_4;
  RunTime("Can not evaluate an undefined expression");
  return varRes_4;
}
