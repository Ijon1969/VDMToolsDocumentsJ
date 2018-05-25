/***
*  * �T�v
*  *    ���̃t�@�C����VDM Toolbox��CORBA API��p���� 
*  *    �N���C�A���g����������������@�̗��ł���B
*  *                                                                       
*  *    ���̃t�@�C���� windows NT/95���MS VC++ 6.0�@����� 
*  *    Unix��� gcc 2.95.2 �ŃR���p�C���\�ł���B
*  *                                                                       
*  *    98/NT���nmake���g�p����ꍇ�� makefile��Makefile.nm ��p��      
*  *    Linux��ŃR���p�C������ꍇ��Makefile ��p����
*  * ID
*  *    $Id: client_example.cc,v 1.27 2006/02/07 05:14:11 vdmtools Exp $
*  * AUTHOR
*  *    Ole Storm + $Author: vdmtools $
*  * COPYRIGHT
*  *    (C) 2005 CSK
***/

#include <iostream>
using namespace std;

#include <string>
// CORBA ������ ����� omniORB4�̂��߂̑��̂���
#include "corba_client.h"

#ifdef _MSC_VER
#include <direct.h> // getcwd�̂���
#else
#include <unistd.h> // getcwd�̂���
#endif // _MSC_VER

char ABS_FILENAME[200];
VDM::ClientID client_id;

#define ADD_PATH(p,s) strcat(strcpy(ABS_FILENAME, p), s)
#define SORT_NUM 20

void EchoPrimes(int, ToolboxAPI::VDMInterpreter_var, 
                ToolboxAPI::VDMApplication_var);
void EchoPrimes2(int, ToolboxAPI::VDMInterpreter_var, 
                 ToolboxAPI::VDMApplication_var);
void ListModules(ToolboxAPI::VDMApplication_var app);

int main(int argc, char *argv[])
{
  const char * source_path = getenv("VDM_SOURCE_LOCATION");
  string sdir;
  if( source_path == NULL )
  {
    char buf[1024];
    if( getcwd( buf, sizeof( buf ) ) != NULL )
    {
#ifdef _MSC_VER
      // Unix��ł�
      // �p�X���̃o�b�N�X���b�V���̓t�H���[�h�X���b�V���ɕϊ�����B
     for (char* s = buf; s = strchr(s, '\\'); s++) {
        *s = '/';
      }
#endif
      sdir = buf;
      for( int i = 0; i < 2; i++ )
      {
        unsigned int index = sdir.find_last_of( '/' );
        if( index == string::npos ) break;
        sdir = sdir.substr( 0, index );
      }
      sdir += "/";
    }
    source_path = sdir.c_str();

    cerr << "Environment variable VDM_SOURCE_LOCATION not set" << endl;
    cerr << "Default location: " << source_path << endl;
  }
  
  //  VDM Toolbox�ɑ΂����n���h��:
  ToolboxAPI::VDMApplication_var app;

  // ORB�̏������B���ꂪ�ǂ̂悤�ɍs���邩�ɂ��Ă̏ڍׂ�
  // corba_client.{h,cc}��omniORB3 ���[�U�[�}�j���A�����Q�l�ɁB
  init_corba(argc, argv);

  // �Ō�ɃX�^�[�g����VDMToolbox�ɑ΂���n���h�������o���B
  // �n���h����VDM Toolbox�ɂ�萶�����ꂽ
  // CORBA�I�u�W�F�N�g�̕�����\����ʂ��Ċl������B
  // ������̓t�@�C�����̕t����object.string�Ƃ��ď����o����
  // VDM_OBJECT_LOCATION�ɂ���`���ꂽ�f�B���N�g���ɒu�����B
  // ���ꂪ�ݒ肳��Ȃ��ꍇ�Aget_app �͎����I�Ƀz�[���iUnix�j�܂��� 
  // �v���t�@�C���f�B���N�g���iWindows NT/95�j�Ƀt�@�C����T���ɍs���B

#ifdef VDMPP
  GetAppReturnCode rt = get_app(app, NULL, ToolboxAPI::PP_TOOLBOX);
#else
  GetAppReturnCode rt = get_app(app, NULL, ToolboxAPI::SL_TOOLBOX);
#endif //VDMPP
  switch(rt){
  case VDM_OBJECT_LOCATION_NOT_SET:
    cerr << "Environment variable VDM_OBJECT_LOCATION not set" << endl;
    exit(0);
  case OBJECT_STRING_NON_EXISTING:
      cerr << "The file " + GetIORFileName() + " could not be located. \
               Make sure the Toolbox is running" << endl;
    exit(0);
  case CORBA_ERROR:
    cerr << "Unable to setup the CORBA environment" << endl;
    exit(0);
  case CORBA_SUCCESS:
  default:
    break;
  }

  try{
    // Toolbox�ɃN���C�A���g��o�^:
   client_id = app->Register();

    // ���v���W�F�N�g���\�z���邽�߂ɁA
    // VDMProject�C���^�[�t�F�C�X�ɑ΂���n���h�����ŏ��Ɋl��:
    ToolboxAPI::VDMProject_var prj = app->GetProject();

    prj->New();  // �V�K�v���W�F�N�g

    // �K�v�ȃt�@�C�����܂߂邽�߂ɁA�v���W�F�N�g���\�z����B
    // �t�@�C����VDM Toolbox���X�^�[�g���������ꏊ��
    // �z�u����Ȃ���΂Ȃ�Ȃ��B����ȊO�̏ꍇ�́A
    // �t�@�C���ɑ΂����΃p�X��p����ׂ��ł���
    if(app->Tool() == ToolboxAPI::SL_TOOLBOX)
      {
        prj->AddFile(ADD_PATH(source_path,"examples/sort/sort.vdm"));
      }
    else{
      prj->AddFile(ADD_PATH(source_path,"examples/sort/implsort.vpp")); 
      prj->AddFile(ADD_PATH(source_path,"examples/sort/sorter.vpp"));
      prj->AddFile(ADD_PATH(source_path,"examples/sort/explsort.vpp"));
      prj->AddFile(ADD_PATH(source_path,"examples/sort/mergesort.vpp"));
      prj->AddFile(ADD_PATH(source_path,"examples/sort/sortmachine.vpp"));
    }
    // �t�@�C�����\�����:
    ToolboxAPI::VDMParser_var parser = app->GetParser();
    ToolboxAPI::FileList_var fl;
    prj->GetFiles(fl);

    // �Q�̈�������@�Ńt�@�C�����\����͂���B
    // ���̕��@�ł̓t�@�C���ꗗ���P�P������
    // �e�t�@�C�����ʂɍ\����͂���
    // �i�������ASL_TOOLBOX�ɑ΂��Ă͍\�z�t�@�C�����B�P�ł��邪�A
    // �����ł͂���ŏ\���ł��낤)
    cout << "Parsing files individually" << endl;
    for(unsigned int i=0; i<fl->length(); i++){
      cout << (char *)fl[i] << "...Parsing...";
      if(parser->Parse(fl[i]))
        cout << "done." << endl;
      else
        cout << "error." << endl;
    }
    
    // �����Ă��̌シ�ׂẴt�@�C������x�ɍ\�����:
    cout << "\nParsing entire list...";
    parser->ParseList(fl);
    cout << "done." << endl;
    
    // �\����͒��ɃG���[���N�����ꍇ�ɂ�
    // �����Œ���:
    ToolboxAPI::VDMErrors_var errhandler = app->GetErrorHandler();  
    // �G���[�n���h���[
    ToolboxAPI::ErrorList_var errs;

    // �G���[������o��
    int nerr = errhandler->GetErrors(errs); 
    if(nerr){
      // �G���[�̈��:
      cout << nerr << " errors:" << endl;
      for(int ierr=0; ierr<nerr; ierr++)
        cout << (char *) errs[ierr].fname << ", " 
             << errs[ierr].line << endl 
             << (char *) errs[ierr].msg << endl;

    }
    // ���l�Ɍx����₢���킹�邱�Ƃ��ł���B

    // ���ׂẴ��W���[���̖��̂Ə�Ԃ��ꗗ:
    ListModules(app);

    // ���ׂẴ��W���[���̌^�`�F�b�N:
    ToolboxAPI::VDMTypeChecker_var tchk = app->GetTypeChecker();
    ToolboxAPI::ModuleList_var modules;
    prj->GetModules(modules);
    cout << "Type checking all modules...";
    if(tchk->TypeCheckList(modules))
      cout << "done." << endl;
    else
      cout << "errors." << endl;

    // ���ׂẴ��W���[���̍ŐV��Ԃ̈ꗗ:
    ListModules(app);


    // �Ō�ɃC���^�[�v���^�[�̎g�p�@�������B 

    cout << endl << "Interpreter tests:" << endl << endl;
    ToolboxAPI::VDMInterpreter_var interp = app->GetInterpreter();


    // �f���v�Z������֐��̌Ăяo��:
    EchoPrimes(20, interp, app);

    // ��Q�̕��@�Ƃ��Ė⍇����p������@������:
    // �\�[�g�����ׂ������̗���\�z����B���̂��߂�
    // VDM�l�����o�����߂�VDMFactory�ɑ΂���n���h�������߂�:
    VDM::VDMFactory_var fact = app->GetVDMFactory();

    app->PushTag(client_id); 
    // ����ȍ~�͐������ꂽ�I�u�W�F�N�g���ׂĂɃ^�O�t������

    VDM::VDMSequence_var list = fact->MkSequence(client_id);
    VDM::VDMNumeric_var elem;
    for(int j=0; j<SORT_NUM; j++){
      elem = fact->MkNumeric(client_id, j);
      list->ImpPrepend(elem);
    }
    cout << "The sequence to be sorted: " << list->ToAscii() << endl;

    // �Ăяo���̂��߂̈����̈ꗗ�̍\�z�B�����
    // �E���тɑS�������܂߂�VDM::Sequence�̍\�z�ł���:
    VDM::VDMSequence_var arg_l = fact->MkSequence(client_id);
    arg_l->ImpAppend(list);

    // ���[�U�[�C���^�[�t�F�C�X�ŃC���^�[�v���^�[��p���錋�ʂ�
    // �\�����邽�߁AVerbose ��true�ɐݒ�:
    interp->Verbose(true);
    interp->Debug(true);
    
    // �n�߂ɃC���^�[�v���^�[������������
    interp->Initialize();

    VDM::VDMGeneric_var g;
    if(app->Tool() == ToolboxAPI::SL_TOOLBOX){
      g = interp->Apply(client_id, "MergeSort", arg_l);
    }
    else{ // PP_TOOLBOX
      // �ŏ��́A���S�ƂȂ�\�[�g�I�u�W�F�N�̐���:
      interp->EvalCmd("create o := new SortMachine()");
      
      // ���́A���̃I�u�W�F�N�g��� GoSorting ���\�b�h���Ăяo��:
      g = interp->Apply(client_id, "o.GoSorting", arg_l);
    }

    cout << "The sorted sequence: " << g->ToAscii() << endl;

    // �Ō�ɁA�Ԃ��ꂽ���ʂ��ė񒆂̑S�v�f��
    // ���v���v�Z���邽�߂̌J��Ԃ�:

    VDM::VDMSequence_var s = VDM::VDMSequence::_narrow(g);
    int sum=0;
    for(int k=1; k<=s->Length(); k++){
      VDM::VDMNumeric_var n = VDM::VDMNumeric::_narrow(s->Index(k));
      sum += (Int(GetCPPValue(n))).GetValue();
    }
    cout << "The sum of all the elements: " << sum << endl;

    EchoPrimes2(50, interp, app);

    app->DestroyTag(client_id);

    // �N���C�A���g�̓o�^������:
    app->Unregister(client_id);
  }
  catch(ToolboxAPI::APIError &ex){
    cerr << "Caught API error " << (char *)ex.msg << endl;
  }
  catch(CORBA::COMM_FAILURE &ex) {
    cerr << "Caught system exception COMM_FAILURE, \
             unable to contact server" 
         << endl;
  }
  catch(omniORB::fatalException& ex) {
    cerr << "Caught omniORB3 fatalException" << endl;
  }

  return 0;  
}


void EchoPrimes(int n, ToolboxAPI::VDMInterpreter_var interp, 
                ToolboxAPI::VDMApplication_var app)
  // ���ȉ��̑f���̗�𐶐����A
  // �����stdout�ɂ��̂܂ܑ���Ԃ��B
{
  app->PushTag(client_id);

  interp->Initialize ();

  // ���� VDM::Generic �̓C���^�[�v���^�[����̌��ʂ̕ێ���
  // �p������B
  VDM::VDMGeneric_var g;
  
  // 20�ȉ��̑f�����v�Z���邽�߂�EvalExpression��p����
  char expr[200];
  sprintf(expr, "[e|e in set {1,...,%d} \
                  & exists1 x in set {2,...,e} & e mod x = 0 ]", n);
  g = interp->EvalExpression(client_id, expr);
  if(g->IsSequence()){
    cout << "All primes below " << n << ":" << endl << g->ToAscii() << endl;
  }
  VDM::VDMSequence_var s = VDM::VDMSequence::_narrow(g);
  int sum=0;
  for(int k=1; k<=s->Length(); k++){
    VDM::VDMNumeric_var n = VDM::VDMNumeric::_narrow(s->Index(k));
    sum += (Int(GetCPPValue(n))).GetValue();
  }
  cout << "The sum of all the primes: " << sum << endl;
  app->DestroyTag(client_id); // �d�グ...
}

void EchoPrimes2(int n, ToolboxAPI::VDMInterpreter_var interp, 
                 ToolboxAPI::VDMApplication_var app)
  // ���ȉ��̑f���̗�𐶐���
  // ���̗��stdout�ɂ��̂܂ܑ���Ԃ��B
  // �ǉ��Ƃ��āAVDM�l�S�̂�toolbox����N���C�A���g���ֈڍs��
  // �����metaiv.h�ɐ錾����Ă���"real"��C++�l�ɕϊ����邽�߂�
  // �ǂ�GetCPPValue���g�p�ł��邩�A�����̊֐��������Ă���
{
  // ���� VDM::VDMGeneric �̓C���^�[�v���^�[����̌��ʂ�ێ����邱�Ƃ� 
  // �p����B
  VDM::VDMGeneric_var g;
  
  // 20�ȉ��̑f�����v�Z����̂ɂ�EvalExpression��p����
  char expr[200];
  sprintf(expr, "[e|e in set {1,...,%d} & \
                  exists1 x in set {2,...,e} & e mod x = 0 ]", n);
  g = interp->EvalExpression(client_id, expr);

  // VDM::Generic g ��"real" metaiv-Sequence�l��
  // �ϊ�����:
  Sequence s(GetCPPValue(g));
  
  // �����Œl�S�̂��N���C�A���g���ֈڂ��ꂽ�̂ň��S�� g ��
  // �j�����邱�Ƃ��ł���:
  g->Destroy();

  cout << "All primes below " << n << ":" << endl
       << wstring2string(s.ascii()) << endl;
  int i, sum=0;
  Generic gg;
  for(i = s.First(gg); i; i = s.Next(gg)){
    sum += (int)Real(gg).GetValue();
  }
  cout << "The sum of all the primes: " << sum << endl;
}

        
void ListModules(ToolboxAPI::VDMApplication_var app)
  // ���̊֐��̓��W���[���Ƃ����̏�Ԃ��ꗗ�ɂ���B
{
 // �v���W�F�N�g�n���h��
  ToolboxAPI::VDMProject_var prj = app->GetProject();

  // ���W���[�����|�W�g��
  ToolboxAPI::VDMModuleRepos_var repos = app->GetModuleRepos();

  ToolboxAPI::ModuleList_var ml;
  prj->GetModules(ml);
  cout << "Modules:" << endl;
  for(unsigned int i=0; i<ml->length(); i++){
    // ���̍\���̓��W���[����Ԃ̕ێ��Ɏg�p�����:
    ToolboxAPI::ModuleStatus stat; 
    // i�Ԗڂ̃��W���[���̏�Ԃ𓾂�
    repos->Status(stat, ml[i]);  
    // ��Ԃ��������B 0 = none, 1 = OK
    cout << (int) stat.SyntaxChecked 
         << (int) stat.TypeChecked
         << (int) stat.CodeGenerated
         << (int) stat.PrettyPrinted
         << " " << (char *)ml[i] << endl;
  }
}


