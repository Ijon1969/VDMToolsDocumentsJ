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

#ifndef _VisualWorkSpace_h
#define _VisualWorkSpace_h

#include <math.h>
#include "metaiv.h"
#include "cg.h"
#include "cg_aux.h"
#include "CGBase.h"
#include "WorkSpace.h"



class vdm_VisualWorkSpace : public virtual vdm_WorkSpace {
protected:
  ObjectRef vdm_view;
public:

  virtual vdm_VisualWorkSpace * Get_vdm_VisualWorkSpace() { return this; }

  ObjectRef Self() { return ObjectRef(Get_vdm_VisualWorkSpace()); }

  int vdm_GetId() { return VDM_VisualWorkSpace; }
  virtual void vdm_Init(const Set &, const ObjectRef &, const ObjectRef &);
  virtual void vdm_TraiterPistesRadar();
   vdm_VisualWorkSpace();

  virtual ~vdm_VisualWorkSpace() {}
};

#endif

