#include "metaiv.h"
#include "A.h"

int main() {
    
  ObjectRef obj(new vdm_A());
  cout << (ObjGet_vdm_A(obj))->vdm_Test().ascii() << "\n";
  return 0;
}
