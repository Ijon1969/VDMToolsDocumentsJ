//
// THIS FILE IS AUTOMATICALLY GENERATED!!
//
// Generated at Thu 25-Sep-97 by the VDM++toC++ Code Generator
// (v6.0 - Thu 25-Sep-97)
//
// Supported compiler: g++ version 2.7.2
//



#include "Parallelogram.h"

vdm_Parallelogram::vdm_Parallelogram() { RegisterAsDerived(vdm_GetId()); }

Real vdm_Parallelogram::vdm_GetAngle() { return vdm_acos(vdm_inproduct(vdm_v1, vdm_v2) / vdm_length(vdm_v1) * vdm_length(vdm_v2)); }