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

#ifndef _CGBase_h
#define _CGBase_h

#include "cg.h"

class vdm_BulletinMeteo;
class vdm_Clock;
class vdm_Cone;
class vdm_Cylindre;
class vdm_Detecteur;
class vdm_HWPistesRadar;
class vdm_MSAWTypes;
class vdm_Main;
class vdm_Obstacle;
class vdm_ObstacleArtificiel;
class vdm_Parametres;
class vdm_PistesRadar;
class vdm_Polygone;
class vdm_ReliefParticulier;
class vdm_SegmentDePrediction;
class vdm_SpecView;
class vdm_TclTkView;
class vdm_Terrain;
class vdm_Vecteur3D;
class vdm_View;
class vdm_VisualDetecteur;
class vdm_VisualObstacleArtificiel;
class vdm_VisualPistesRadar;
class vdm_VisualSegmentDePrediction;
class vdm_VisualWorkSpace;
class vdm_VisualZoneAeroport;
class vdm_WorkSpace;
class vdm_ZoneAeroport;
class vdm_ZoneMilitaire;


class CGBase : public vdmBase {
private:

  virtual bool has_cg_base() const { return true; }
public:

  virtual vdm_BulletinMeteo * Get_vdm_BulletinMeteo() { return 0; }

  virtual vdm_Clock * Get_vdm_Clock() { return 0; }

  virtual vdm_Cone * Get_vdm_Cone() { return 0; }

  virtual vdm_Cylindre * Get_vdm_Cylindre() { return 0; }

  virtual vdm_Detecteur * Get_vdm_Detecteur() { return 0; }

  virtual vdm_HWPistesRadar * Get_vdm_HWPistesRadar() { return 0; }

  virtual vdm_MSAWTypes * Get_vdm_MSAWTypes() { return 0; }

  virtual vdm_Main * Get_vdm_Main() { return 0; }

  virtual vdm_Obstacle * Get_vdm_Obstacle() { return 0; }

  virtual vdm_ObstacleArtificiel * Get_vdm_ObstacleArtificiel() { return 0; }

  virtual vdm_Parametres * Get_vdm_Parametres() { return 0; }

  virtual vdm_PistesRadar * Get_vdm_PistesRadar() { return 0; }

  virtual vdm_Polygone * Get_vdm_Polygone() { return 0; }

  virtual vdm_ReliefParticulier * Get_vdm_ReliefParticulier() { return 0; }

  virtual vdm_SegmentDePrediction * Get_vdm_SegmentDePrediction() { return 0; }

  virtual vdm_SpecView * Get_vdm_SpecView() { return 0; }

  virtual vdm_TclTkView * Get_vdm_TclTkView() { return 0; }

  virtual vdm_Terrain * Get_vdm_Terrain() { return 0; }

  virtual vdm_Vecteur3D * Get_vdm_Vecteur3D() { return 0; }

  virtual vdm_View * Get_vdm_View() { return 0; }

  virtual vdm_VisualDetecteur * Get_vdm_VisualDetecteur() { return 0; }

  virtual vdm_VisualObstacleArtificiel * Get_vdm_VisualObstacleArtificiel() { return 0; }

  virtual vdm_VisualPistesRadar * Get_vdm_VisualPistesRadar() { return 0; }

  virtual vdm_VisualSegmentDePrediction * Get_vdm_VisualSegmentDePrediction() { return 0; }

  virtual vdm_VisualWorkSpace * Get_vdm_VisualWorkSpace() { return 0; }

  virtual vdm_VisualZoneAeroport * Get_vdm_VisualZoneAeroport() { return 0; }

  virtual vdm_WorkSpace * Get_vdm_WorkSpace() { return 0; }

  virtual vdm_ZoneAeroport * Get_vdm_ZoneAeroport() { return 0; }

  virtual vdm_ZoneMilitaire * Get_vdm_ZoneMilitaire() { return 0; }
};
vdm_BulletinMeteo * ObjGet_vdm_BulletinMeteo(const ObjectRef &obj);
vdm_Clock * ObjGet_vdm_Clock(const ObjectRef &obj);
vdm_Cone * ObjGet_vdm_Cone(const ObjectRef &obj);
vdm_Cylindre * ObjGet_vdm_Cylindre(const ObjectRef &obj);
vdm_Detecteur * ObjGet_vdm_Detecteur(const ObjectRef &obj);
vdm_HWPistesRadar * ObjGet_vdm_HWPistesRadar(const ObjectRef &obj);
vdm_MSAWTypes * ObjGet_vdm_MSAWTypes(const ObjectRef &obj);
vdm_Main * ObjGet_vdm_Main(const ObjectRef &obj);
vdm_Obstacle * ObjGet_vdm_Obstacle(const ObjectRef &obj);
vdm_ObstacleArtificiel * ObjGet_vdm_ObstacleArtificiel(const ObjectRef &obj);
vdm_Parametres * ObjGet_vdm_Parametres(const ObjectRef &obj);
vdm_PistesRadar * ObjGet_vdm_PistesRadar(const ObjectRef &obj);
vdm_Polygone * ObjGet_vdm_Polygone(const ObjectRef &obj);
vdm_ReliefParticulier * ObjGet_vdm_ReliefParticulier(const ObjectRef &obj);
vdm_SegmentDePrediction * ObjGet_vdm_SegmentDePrediction(const ObjectRef &obj);
vdm_SpecView * ObjGet_vdm_SpecView(const ObjectRef &obj);
vdm_TclTkView * ObjGet_vdm_TclTkView(const ObjectRef &obj);
vdm_Terrain * ObjGet_vdm_Terrain(const ObjectRef &obj);
vdm_Vecteur3D * ObjGet_vdm_Vecteur3D(const ObjectRef &obj);
vdm_View * ObjGet_vdm_View(const ObjectRef &obj);
vdm_VisualDetecteur * ObjGet_vdm_VisualDetecteur(const ObjectRef &obj);
vdm_VisualObstacleArtificiel * ObjGet_vdm_VisualObstacleArtificiel(const ObjectRef &obj);
vdm_VisualPistesRadar * ObjGet_vdm_VisualPistesRadar(const ObjectRef &obj);
vdm_VisualSegmentDePrediction * ObjGet_vdm_VisualSegmentDePrediction(const ObjectRef &obj);
vdm_VisualWorkSpace * ObjGet_vdm_VisualWorkSpace(const ObjectRef &obj);
vdm_VisualZoneAeroport * ObjGet_vdm_VisualZoneAeroport(const ObjectRef &obj);
vdm_WorkSpace * ObjGet_vdm_WorkSpace(const ObjectRef &obj);
vdm_ZoneAeroport * ObjGet_vdm_ZoneAeroport(const ObjectRef &obj);
vdm_ZoneMilitaire * ObjGet_vdm_ZoneMilitaire(const ObjectRef &obj);
enum  {
  VDM_BulletinMeteo,
  VDM_Clock,
  VDM_Cone,
  VDM_Cylindre,
  VDM_Detecteur,
  VDM_HWPistesRadar,
  VDM_MSAWTypes,
  VDM_Main,
  VDM_Obstacle,
  VDM_ObstacleArtificiel,
  VDM_Parametres,
  VDM_PistesRadar,
  VDM_Polygone,
  VDM_ReliefParticulier,
  VDM_SegmentDePrediction,
  VDM_SpecView,
  VDM_TclTkView,
  VDM_Terrain,
  VDM_Vecteur3D,
  VDM_View,
  VDM_VisualDetecteur,
  VDM_VisualObstacleArtificiel,
  VDM_VisualPistesRadar,
  VDM_VisualSegmentDePrediction,
  VDM_VisualWorkSpace,
  VDM_VisualZoneAeroport,
  VDM_WorkSpace,
  VDM_ZoneAeroport,
  VDM_ZoneMilitaire
};

#endif
