//
// THIS FILE IS AUTOMATICALLY GENERATED!!
//
// Generated at Thu 25-Sep-97 by the VDM++toC++ Code Generator
// (v6.0 - Thu 25-Sep-97)
//
// Supported compiler: g++ version 2.7.2
//

#ifndef _Parallelogram_h
#define _Parallelogram_h

#include <math.h>
#include "metaiv.h"
#include "cg.h"
#include "cg_aux.h"
#include "CGBase.h"
#include "Quadrilateral.h"



class vdm_Parallelogram : public virtual vdm_Quadrilateral {
public:

  virtual vdm_Parallelogram * Get_vdm_Parallelogram() { return this; }

  ObjectRef Self() { return ObjectRef(Get_vdm_Parallelogram()); }

  int vdm_GetId() { return VDM_Parallelogram; }
  virtual Real vdm_GetAngle();
   vdm_Parallelogram();

  virtual ~vdm_Parallelogram() {}
};

#endif

