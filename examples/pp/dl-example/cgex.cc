#include "metaiv.h"
#include "A.h"

int main() {
    
  ObjectRef obj(new vdm_A());
  wcout << (ObjGet_vdm_A(obj))->vdm_Test().ascii() << endl;
  return 0;
}
