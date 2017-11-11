// Do NOT change. Changes will be lost next time file is generated
// derived from main92.cc example of PYTHIA 8.2

#define R__DICTIONARY_FILENAME dict4RootDct

/*******************************************************************/
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <assert.h>
#define G__DICTIONARY
#include "RConfig.h"
#include "TClass.h"
#include "TDictAttributeMap.h"
#include "TInterpreter.h"
#include "TROOT.h"
#include "TBuffer.h"
#include "TMemberInspector.h"
#include "TInterpreter.h"
#include "TVirtualMutex.h"
#include "TError.h"

#ifndef G__ROOT
#define G__ROOT
#endif

#include "RtypesImp.h"
#include "TIsAProxy.h"
#include "TFileMergeInfo.h"
#include <algorithm>
#include "TCollectionProxyInfo.h"
/*******************************************************************/

#include "TDataMember.h"

// Since CINT ignores the std namespace, we need to do so in this file.
namespace std {} using namespace std;

// Header files passed as explicit arguments
#include "dict4Root.h"

// Header files passed via #pragma extra_include

namespace Pythia8 {
   namespace ROOT {
      inline ::ROOT::TGenericClassInfo *GenerateInitInstance();
      static TClass *Pythia8_Dictionary();

      // Function generating the singleton type initializer
      inline ::ROOT::TGenericClassInfo *GenerateInitInstance()
      {
         static ::ROOT::TGenericClassInfo 
            instance("Pythia8", 0 /*version*/, "Pythia8/PythiaStdlib.h", 50,
                     ::ROOT::Internal::DefineBehavior((void*)0,(void*)0),
                     &Pythia8_Dictionary, 0);
         return &instance;
      }
      // Insure that the inline function is _not_ optimized away by the compiler
      ::ROOT::TGenericClassInfo *(*_R__UNIQUE_(InitFunctionKeeper))() = &GenerateInitInstance;  
      // Static variable to force the class initialization
      static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstance(); R__UseDummy(_R__UNIQUE_(Init));

      // Dictionary for non-ClassDef classes
      static TClass *Pythia8_Dictionary() {
         return GenerateInitInstance()->GetClass();
      }

   }
}

namespace ROOT {
   static TClass *Pythia8cLcLEvent_Dictionary();
   static void Pythia8cLcLEvent_TClassManip(TClass*);
   static void *new_Pythia8cLcLEvent(void *p = 0);
   static void *newArray_Pythia8cLcLEvent(Long_t size, void *p);
   static void delete_Pythia8cLcLEvent(void *p);
   static void deleteArray_Pythia8cLcLEvent(void *p);
   static void destruct_Pythia8cLcLEvent(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::Pythia8::Event*)
   {
      ::Pythia8::Event *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(::Pythia8::Event));
      static ::ROOT::TGenericClassInfo 
         instance("Pythia8::Event", "Pythia8/Event.h", 371,
                  typeid(::Pythia8::Event), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &Pythia8cLcLEvent_Dictionary, isa_proxy, 4,
                  sizeof(::Pythia8::Event) );
      instance.SetNew(&new_Pythia8cLcLEvent);
      instance.SetNewArray(&newArray_Pythia8cLcLEvent);
      instance.SetDelete(&delete_Pythia8cLcLEvent);
      instance.SetDeleteArray(&deleteArray_Pythia8cLcLEvent);
      instance.SetDestructor(&destruct_Pythia8cLcLEvent);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::Pythia8::Event*)
   {
      return GenerateInitInstanceLocal((::Pythia8::Event*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::Pythia8::Event*)0x0); R__UseDummy(_R__UNIQUE_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *Pythia8cLcLEvent_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const ::Pythia8::Event*)0x0)->GetClass();
      Pythia8cLcLEvent_TClassManip(theClass);
   return theClass;
   }

   static void Pythia8cLcLEvent_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   static TClass *Pythia8cLcLParticle_Dictionary();
   static void Pythia8cLcLParticle_TClassManip(TClass*);
   static void *new_Pythia8cLcLParticle(void *p = 0);
   static void *newArray_Pythia8cLcLParticle(Long_t size, void *p);
   static void delete_Pythia8cLcLParticle(void *p);
   static void deleteArray_Pythia8cLcLParticle(void *p);
   static void destruct_Pythia8cLcLParticle(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::Pythia8::Particle*)
   {
      ::Pythia8::Particle *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(::Pythia8::Particle));
      static ::ROOT::TGenericClassInfo 
         instance("Pythia8::Particle", "Pythia8/Event.h", 32,
                  typeid(::Pythia8::Particle), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &Pythia8cLcLParticle_Dictionary, isa_proxy, 4,
                  sizeof(::Pythia8::Particle) );
      instance.SetNew(&new_Pythia8cLcLParticle);
      instance.SetNewArray(&newArray_Pythia8cLcLParticle);
      instance.SetDelete(&delete_Pythia8cLcLParticle);
      instance.SetDeleteArray(&deleteArray_Pythia8cLcLParticle);
      instance.SetDestructor(&destruct_Pythia8cLcLParticle);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::Pythia8::Particle*)
   {
      return GenerateInitInstanceLocal((::Pythia8::Particle*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::Pythia8::Particle*)0x0); R__UseDummy(_R__UNIQUE_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *Pythia8cLcLParticle_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const ::Pythia8::Particle*)0x0)->GetClass();
      Pythia8cLcLParticle_TClassManip(theClass);
   return theClass;
   }

   static void Pythia8cLcLParticle_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   static TClass *Pythia8cLcLJunction_Dictionary();
   static void Pythia8cLcLJunction_TClassManip(TClass*);
   static void *new_Pythia8cLcLJunction(void *p = 0);
   static void *newArray_Pythia8cLcLJunction(Long_t size, void *p);
   static void delete_Pythia8cLcLJunction(void *p);
   static void deleteArray_Pythia8cLcLJunction(void *p);
   static void destruct_Pythia8cLcLJunction(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::Pythia8::Junction*)
   {
      ::Pythia8::Junction *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(::Pythia8::Junction));
      static ::ROOT::TGenericClassInfo 
         instance("Pythia8::Junction", "Pythia8/Event.h", 321,
                  typeid(::Pythia8::Junction), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &Pythia8cLcLJunction_Dictionary, isa_proxy, 4,
                  sizeof(::Pythia8::Junction) );
      instance.SetNew(&new_Pythia8cLcLJunction);
      instance.SetNewArray(&newArray_Pythia8cLcLJunction);
      instance.SetDelete(&delete_Pythia8cLcLJunction);
      instance.SetDeleteArray(&deleteArray_Pythia8cLcLJunction);
      instance.SetDestructor(&destruct_Pythia8cLcLJunction);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::Pythia8::Junction*)
   {
      return GenerateInitInstanceLocal((::Pythia8::Junction*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::Pythia8::Junction*)0x0); R__UseDummy(_R__UNIQUE_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *Pythia8cLcLJunction_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const ::Pythia8::Junction*)0x0)->GetClass();
      Pythia8cLcLJunction_TClassManip(theClass);
   return theClass;
   }

   static void Pythia8cLcLJunction_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   static TClass *Pythia8cLcLVec4_Dictionary();
   static void Pythia8cLcLVec4_TClassManip(TClass*);
   static void *new_Pythia8cLcLVec4(void *p = 0);
   static void *newArray_Pythia8cLcLVec4(Long_t size, void *p);
   static void delete_Pythia8cLcLVec4(void *p);
   static void deleteArray_Pythia8cLcLVec4(void *p);
   static void destruct_Pythia8cLcLVec4(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::Pythia8::Vec4*)
   {
      ::Pythia8::Vec4 *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(::Pythia8::Vec4));
      static ::ROOT::TGenericClassInfo 
         instance("Pythia8::Vec4", "Pythia8/Basics.h", 112,
                  typeid(::Pythia8::Vec4), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &Pythia8cLcLVec4_Dictionary, isa_proxy, 4,
                  sizeof(::Pythia8::Vec4) );
      instance.SetNew(&new_Pythia8cLcLVec4);
      instance.SetNewArray(&newArray_Pythia8cLcLVec4);
      instance.SetDelete(&delete_Pythia8cLcLVec4);
      instance.SetDeleteArray(&deleteArray_Pythia8cLcLVec4);
      instance.SetDestructor(&destruct_Pythia8cLcLVec4);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::Pythia8::Vec4*)
   {
      return GenerateInitInstanceLocal((::Pythia8::Vec4*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::Pythia8::Vec4*)0x0); R__UseDummy(_R__UNIQUE_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *Pythia8cLcLVec4_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const ::Pythia8::Vec4*)0x0)->GetClass();
      Pythia8cLcLVec4_TClassManip(theClass);
   return theClass;
   }

   static void Pythia8cLcLVec4_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   static TClass *Pythia8cLcLParticleData_Dictionary();
   static void Pythia8cLcLParticleData_TClassManip(TClass*);
   static void *new_Pythia8cLcLParticleData(void *p = 0);
   static void *newArray_Pythia8cLcLParticleData(Long_t size, void *p);
   static void delete_Pythia8cLcLParticleData(void *p);
   static void deleteArray_Pythia8cLcLParticleData(void *p);
   static void destruct_Pythia8cLcLParticleData(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::Pythia8::ParticleData*)
   {
      ::Pythia8::ParticleData *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(::Pythia8::ParticleData));
      static ::ROOT::TGenericClassInfo 
         instance("Pythia8::ParticleData", "Pythia8/ParticleData.h", 358,
                  typeid(::Pythia8::ParticleData), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &Pythia8cLcLParticleData_Dictionary, isa_proxy, 4,
                  sizeof(::Pythia8::ParticleData) );
      instance.SetNew(&new_Pythia8cLcLParticleData);
      instance.SetNewArray(&newArray_Pythia8cLcLParticleData);
      instance.SetDelete(&delete_Pythia8cLcLParticleData);
      instance.SetDeleteArray(&deleteArray_Pythia8cLcLParticleData);
      instance.SetDestructor(&destruct_Pythia8cLcLParticleData);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::Pythia8::ParticleData*)
   {
      return GenerateInitInstanceLocal((::Pythia8::ParticleData*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::Pythia8::ParticleData*)0x0); R__UseDummy(_R__UNIQUE_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *Pythia8cLcLParticleData_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const ::Pythia8::ParticleData*)0x0)->GetClass();
      Pythia8cLcLParticleData_TClassManip(theClass);
   return theClass;
   }

   static void Pythia8cLcLParticleData_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   static TClass *Pythia8cLcLParticleDataEntry_Dictionary();
   static void Pythia8cLcLParticleDataEntry_TClassManip(TClass*);
   static void *new_Pythia8cLcLParticleDataEntry(void *p = 0);
   static void *newArray_Pythia8cLcLParticleDataEntry(Long_t size, void *p);
   static void delete_Pythia8cLcLParticleDataEntry(void *p);
   static void deleteArray_Pythia8cLcLParticleDataEntry(void *p);
   static void destruct_Pythia8cLcLParticleDataEntry(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::Pythia8::ParticleDataEntry*)
   {
      ::Pythia8::ParticleDataEntry *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(::Pythia8::ParticleDataEntry));
      static ::ROOT::TGenericClassInfo 
         instance("Pythia8::ParticleDataEntry", "Pythia8/ParticleData.h", 116,
                  typeid(::Pythia8::ParticleDataEntry), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &Pythia8cLcLParticleDataEntry_Dictionary, isa_proxy, 4,
                  sizeof(::Pythia8::ParticleDataEntry) );
      instance.SetNew(&new_Pythia8cLcLParticleDataEntry);
      instance.SetNewArray(&newArray_Pythia8cLcLParticleDataEntry);
      instance.SetDelete(&delete_Pythia8cLcLParticleDataEntry);
      instance.SetDeleteArray(&deleteArray_Pythia8cLcLParticleDataEntry);
      instance.SetDestructor(&destruct_Pythia8cLcLParticleDataEntry);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::Pythia8::ParticleDataEntry*)
   {
      return GenerateInitInstanceLocal((::Pythia8::ParticleDataEntry*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::Pythia8::ParticleDataEntry*)0x0); R__UseDummy(_R__UNIQUE_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *Pythia8cLcLParticleDataEntry_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const ::Pythia8::ParticleDataEntry*)0x0)->GetClass();
      Pythia8cLcLParticleDataEntry_TClassManip(theClass);
   return theClass;
   }

   static void Pythia8cLcLParticleDataEntry_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   static TClass *Pythia8cLcLDecayChannel_Dictionary();
   static void Pythia8cLcLDecayChannel_TClassManip(TClass*);
   static void *new_Pythia8cLcLDecayChannel(void *p = 0);
   static void *newArray_Pythia8cLcLDecayChannel(Long_t size, void *p);
   static void delete_Pythia8cLcLDecayChannel(void *p);
   static void deleteArray_Pythia8cLcLDecayChannel(void *p);
   static void destruct_Pythia8cLcLDecayChannel(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::Pythia8::DecayChannel*)
   {
      ::Pythia8::DecayChannel *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(::Pythia8::DecayChannel));
      static ::ROOT::TGenericClassInfo 
         instance("Pythia8::DecayChannel", "Pythia8/ParticleData.h", 35,
                  typeid(::Pythia8::DecayChannel), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &Pythia8cLcLDecayChannel_Dictionary, isa_proxy, 4,
                  sizeof(::Pythia8::DecayChannel) );
      instance.SetNew(&new_Pythia8cLcLDecayChannel);
      instance.SetNewArray(&newArray_Pythia8cLcLDecayChannel);
      instance.SetDelete(&delete_Pythia8cLcLDecayChannel);
      instance.SetDeleteArray(&deleteArray_Pythia8cLcLDecayChannel);
      instance.SetDestructor(&destruct_Pythia8cLcLDecayChannel);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::Pythia8::DecayChannel*)
   {
      return GenerateInitInstanceLocal((::Pythia8::DecayChannel*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::Pythia8::DecayChannel*)0x0); R__UseDummy(_R__UNIQUE_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *Pythia8cLcLDecayChannel_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const ::Pythia8::DecayChannel*)0x0)->GetClass();
      Pythia8cLcLDecayChannel_TClassManip(theClass);
   return theClass;
   }

   static void Pythia8cLcLDecayChannel_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   static TClass *Pythia8cLcLPythia_Dictionary();
   static void Pythia8cLcLPythia_TClassManip(TClass*);
   static void *new_Pythia8cLcLPythia(void *p = 0);
   static void *newArray_Pythia8cLcLPythia(Long_t size, void *p);
   static void delete_Pythia8cLcLPythia(void *p);
   static void deleteArray_Pythia8cLcLPythia(void *p);
   static void destruct_Pythia8cLcLPythia(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::Pythia8::Pythia*)
   {
      ::Pythia8::Pythia *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(::Pythia8::Pythia));
      static ::ROOT::TGenericClassInfo 
         instance("Pythia8::Pythia", "Pythia8/Pythia.h", 53,
                  typeid(::Pythia8::Pythia), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &Pythia8cLcLPythia_Dictionary, isa_proxy, 4,
                  sizeof(::Pythia8::Pythia) );
      instance.SetNew(&new_Pythia8cLcLPythia);
      instance.SetNewArray(&newArray_Pythia8cLcLPythia);
      instance.SetDelete(&delete_Pythia8cLcLPythia);
      instance.SetDeleteArray(&deleteArray_Pythia8cLcLPythia);
      instance.SetDestructor(&destruct_Pythia8cLcLPythia);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::Pythia8::Pythia*)
   {
      return GenerateInitInstanceLocal((::Pythia8::Pythia*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::Pythia8::Pythia*)0x0); R__UseDummy(_R__UNIQUE_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *Pythia8cLcLPythia_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const ::Pythia8::Pythia*)0x0)->GetClass();
      Pythia8cLcLPythia_TClassManip(theClass);
   return theClass;
   }

   static void Pythia8cLcLPythia_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   static TClass *Pythia8cLcLCoupSM_Dictionary();
   static void Pythia8cLcLCoupSM_TClassManip(TClass*);
   static void *new_Pythia8cLcLCoupSM(void *p = 0);
   static void *newArray_Pythia8cLcLCoupSM(Long_t size, void *p);
   static void delete_Pythia8cLcLCoupSM(void *p);
   static void deleteArray_Pythia8cLcLCoupSM(void *p);
   static void destruct_Pythia8cLcLCoupSM(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::Pythia8::CoupSM*)
   {
      ::Pythia8::CoupSM *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(::Pythia8::CoupSM));
      static ::ROOT::TGenericClassInfo 
         instance("Pythia8::CoupSM", "Pythia8/StandardModel.h", 135,
                  typeid(::Pythia8::CoupSM), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &Pythia8cLcLCoupSM_Dictionary, isa_proxy, 4,
                  sizeof(::Pythia8::CoupSM) );
      instance.SetNew(&new_Pythia8cLcLCoupSM);
      instance.SetNewArray(&newArray_Pythia8cLcLCoupSM);
      instance.SetDelete(&delete_Pythia8cLcLCoupSM);
      instance.SetDeleteArray(&deleteArray_Pythia8cLcLCoupSM);
      instance.SetDestructor(&destruct_Pythia8cLcLCoupSM);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::Pythia8::CoupSM*)
   {
      return GenerateInitInstanceLocal((::Pythia8::CoupSM*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::Pythia8::CoupSM*)0x0); R__UseDummy(_R__UNIQUE_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *Pythia8cLcLCoupSM_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const ::Pythia8::CoupSM*)0x0)->GetClass();
      Pythia8cLcLCoupSM_TClassManip(theClass);
   return theClass;
   }

   static void Pythia8cLcLCoupSM_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   static TClass *Pythia8cLcLCouplings_Dictionary();
   static void Pythia8cLcLCouplings_TClassManip(TClass*);
   static void *new_Pythia8cLcLCouplings(void *p = 0);
   static void *newArray_Pythia8cLcLCouplings(Long_t size, void *p);
   static void delete_Pythia8cLcLCouplings(void *p);
   static void deleteArray_Pythia8cLcLCouplings(void *p);
   static void destruct_Pythia8cLcLCouplings(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::Pythia8::Couplings*)
   {
      ::Pythia8::Couplings *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(::Pythia8::Couplings));
      static ::ROOT::TGenericClassInfo 
         instance("Pythia8::Couplings", "Pythia8/StandardModel.h", 216,
                  typeid(::Pythia8::Couplings), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &Pythia8cLcLCouplings_Dictionary, isa_proxy, 4,
                  sizeof(::Pythia8::Couplings) );
      instance.SetNew(&new_Pythia8cLcLCouplings);
      instance.SetNewArray(&newArray_Pythia8cLcLCouplings);
      instance.SetDelete(&delete_Pythia8cLcLCouplings);
      instance.SetDeleteArray(&deleteArray_Pythia8cLcLCouplings);
      instance.SetDestructor(&destruct_Pythia8cLcLCouplings);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::Pythia8::Couplings*)
   {
      return GenerateInitInstanceLocal((::Pythia8::Couplings*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::Pythia8::Couplings*)0x0); R__UseDummy(_R__UNIQUE_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *Pythia8cLcLCouplings_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const ::Pythia8::Couplings*)0x0)->GetClass();
      Pythia8cLcLCouplings_TClassManip(theClass);
   return theClass;
   }

   static void Pythia8cLcLCouplings_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   static TClass *Pythia8cLcLInBeam_Dictionary();
   static void Pythia8cLcLInBeam_TClassManip(TClass*);
   static void *new_Pythia8cLcLInBeam(void *p = 0);
   static void *newArray_Pythia8cLcLInBeam(Long_t size, void *p);
   static void delete_Pythia8cLcLInBeam(void *p);
   static void deleteArray_Pythia8cLcLInBeam(void *p);
   static void destruct_Pythia8cLcLInBeam(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::Pythia8::InBeam*)
   {
      ::Pythia8::InBeam *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(::Pythia8::InBeam));
      static ::ROOT::TGenericClassInfo 
         instance("Pythia8::InBeam", "Pythia8/SigmaProcess.h", 49,
                  typeid(::Pythia8::InBeam), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &Pythia8cLcLInBeam_Dictionary, isa_proxy, 4,
                  sizeof(::Pythia8::InBeam) );
      instance.SetNew(&new_Pythia8cLcLInBeam);
      instance.SetNewArray(&newArray_Pythia8cLcLInBeam);
      instance.SetDelete(&delete_Pythia8cLcLInBeam);
      instance.SetDeleteArray(&deleteArray_Pythia8cLcLInBeam);
      instance.SetDestructor(&destruct_Pythia8cLcLInBeam);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::Pythia8::InBeam*)
   {
      return GenerateInitInstanceLocal((::Pythia8::InBeam*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::Pythia8::InBeam*)0x0); R__UseDummy(_R__UNIQUE_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *Pythia8cLcLInBeam_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const ::Pythia8::InBeam*)0x0)->GetClass();
      Pythia8cLcLInBeam_TClassManip(theClass);
   return theClass;
   }

   static void Pythia8cLcLInBeam_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   static TClass *Pythia8cLcLInPair_Dictionary();
   static void Pythia8cLcLInPair_TClassManip(TClass*);
   static void *new_Pythia8cLcLInPair(void *p = 0);
   static void *newArray_Pythia8cLcLInPair(Long_t size, void *p);
   static void delete_Pythia8cLcLInPair(void *p);
   static void deleteArray_Pythia8cLcLInPair(void *p);
   static void destruct_Pythia8cLcLInPair(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::Pythia8::InPair*)
   {
      ::Pythia8::InPair *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(::Pythia8::InPair));
      static ::ROOT::TGenericClassInfo 
         instance("Pythia8::InPair", "Pythia8/SigmaProcess.h", 66,
                  typeid(::Pythia8::InPair), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &Pythia8cLcLInPair_Dictionary, isa_proxy, 4,
                  sizeof(::Pythia8::InPair) );
      instance.SetNew(&new_Pythia8cLcLInPair);
      instance.SetNewArray(&newArray_Pythia8cLcLInPair);
      instance.SetDelete(&delete_Pythia8cLcLInPair);
      instance.SetDeleteArray(&deleteArray_Pythia8cLcLInPair);
      instance.SetDestructor(&destruct_Pythia8cLcLInPair);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::Pythia8::InPair*)
   {
      return GenerateInitInstanceLocal((::Pythia8::InPair*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::Pythia8::InPair*)0x0); R__UseDummy(_R__UNIQUE_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *Pythia8cLcLInPair_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const ::Pythia8::InPair*)0x0)->GetClass();
      Pythia8cLcLInPair_TClassManip(theClass);
   return theClass;
   }

   static void Pythia8cLcLInPair_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   static TClass *Pythia8cLcLAlphaStrong_Dictionary();
   static void Pythia8cLcLAlphaStrong_TClassManip(TClass*);
   static void *new_Pythia8cLcLAlphaStrong(void *p = 0);
   static void *newArray_Pythia8cLcLAlphaStrong(Long_t size, void *p);
   static void delete_Pythia8cLcLAlphaStrong(void *p);
   static void deleteArray_Pythia8cLcLAlphaStrong(void *p);
   static void destruct_Pythia8cLcLAlphaStrong(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::Pythia8::AlphaStrong*)
   {
      ::Pythia8::AlphaStrong *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(::Pythia8::AlphaStrong));
      static ::ROOT::TGenericClassInfo 
         instance("Pythia8::AlphaStrong", "Pythia8/StandardModel.h", 23,
                  typeid(::Pythia8::AlphaStrong), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &Pythia8cLcLAlphaStrong_Dictionary, isa_proxy, 4,
                  sizeof(::Pythia8::AlphaStrong) );
      instance.SetNew(&new_Pythia8cLcLAlphaStrong);
      instance.SetNewArray(&newArray_Pythia8cLcLAlphaStrong);
      instance.SetDelete(&delete_Pythia8cLcLAlphaStrong);
      instance.SetDeleteArray(&deleteArray_Pythia8cLcLAlphaStrong);
      instance.SetDestructor(&destruct_Pythia8cLcLAlphaStrong);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::Pythia8::AlphaStrong*)
   {
      return GenerateInitInstanceLocal((::Pythia8::AlphaStrong*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::Pythia8::AlphaStrong*)0x0); R__UseDummy(_R__UNIQUE_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *Pythia8cLcLAlphaStrong_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const ::Pythia8::AlphaStrong*)0x0)->GetClass();
      Pythia8cLcLAlphaStrong_TClassManip(theClass);
   return theClass;
   }

   static void Pythia8cLcLAlphaStrong_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   static TClass *Pythia8cLcLAlphaEM_Dictionary();
   static void Pythia8cLcLAlphaEM_TClassManip(TClass*);
   static void *new_Pythia8cLcLAlphaEM(void *p = 0);
   static void *newArray_Pythia8cLcLAlphaEM(Long_t size, void *p);
   static void delete_Pythia8cLcLAlphaEM(void *p);
   static void deleteArray_Pythia8cLcLAlphaEM(void *p);
   static void destruct_Pythia8cLcLAlphaEM(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::Pythia8::AlphaEM*)
   {
      ::Pythia8::AlphaEM *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(::Pythia8::AlphaEM));
      static ::ROOT::TGenericClassInfo 
         instance("Pythia8::AlphaEM", "Pythia8/StandardModel.h", 106,
                  typeid(::Pythia8::AlphaEM), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &Pythia8cLcLAlphaEM_Dictionary, isa_proxy, 4,
                  sizeof(::Pythia8::AlphaEM) );
      instance.SetNew(&new_Pythia8cLcLAlphaEM);
      instance.SetNewArray(&newArray_Pythia8cLcLAlphaEM);
      instance.SetDelete(&delete_Pythia8cLcLAlphaEM);
      instance.SetDeleteArray(&deleteArray_Pythia8cLcLAlphaEM);
      instance.SetDestructor(&destruct_Pythia8cLcLAlphaEM);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::Pythia8::AlphaEM*)
   {
      return GenerateInitInstanceLocal((::Pythia8::AlphaEM*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::Pythia8::AlphaEM*)0x0); R__UseDummy(_R__UNIQUE_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *Pythia8cLcLAlphaEM_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const ::Pythia8::AlphaEM*)0x0)->GetClass();
      Pythia8cLcLAlphaEM_TClassManip(theClass);
   return theClass;
   }

   static void Pythia8cLcLAlphaEM_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   static TClass *Pythia8cLcLInfo_Dictionary();
   static void Pythia8cLcLInfo_TClassManip(TClass*);
   static void *new_Pythia8cLcLInfo(void *p = 0);
   static void *newArray_Pythia8cLcLInfo(Long_t size, void *p);
   static void delete_Pythia8cLcLInfo(void *p);
   static void deleteArray_Pythia8cLcLInfo(void *p);
   static void destruct_Pythia8cLcLInfo(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::Pythia8::Info*)
   {
      ::Pythia8::Info *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(::Pythia8::Info));
      static ::ROOT::TGenericClassInfo 
         instance("Pythia8::Info", "Pythia8/Info.h", 27,
                  typeid(::Pythia8::Info), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &Pythia8cLcLInfo_Dictionary, isa_proxy, 4,
                  sizeof(::Pythia8::Info) );
      instance.SetNew(&new_Pythia8cLcLInfo);
      instance.SetNewArray(&newArray_Pythia8cLcLInfo);
      instance.SetDelete(&delete_Pythia8cLcLInfo);
      instance.SetDeleteArray(&deleteArray_Pythia8cLcLInfo);
      instance.SetDestructor(&destruct_Pythia8cLcLInfo);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::Pythia8::Info*)
   {
      return GenerateInitInstanceLocal((::Pythia8::Info*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::Pythia8::Info*)0x0); R__UseDummy(_R__UNIQUE_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *Pythia8cLcLInfo_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const ::Pythia8::Info*)0x0)->GetClass();
      Pythia8cLcLInfo_TClassManip(theClass);
   return theClass;
   }

   static void Pythia8cLcLInfo_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   static TClass *Pythia8cLcLRndm_Dictionary();
   static void Pythia8cLcLRndm_TClassManip(TClass*);
   static void *new_Pythia8cLcLRndm(void *p = 0);
   static void *newArray_Pythia8cLcLRndm(Long_t size, void *p);
   static void delete_Pythia8cLcLRndm(void *p);
   static void deleteArray_Pythia8cLcLRndm(void *p);
   static void destruct_Pythia8cLcLRndm(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::Pythia8::Rndm*)
   {
      ::Pythia8::Rndm *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(::Pythia8::Rndm));
      static ::ROOT::TGenericClassInfo 
         instance("Pythia8::Rndm", "Pythia8/Basics.h", 44,
                  typeid(::Pythia8::Rndm), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &Pythia8cLcLRndm_Dictionary, isa_proxy, 4,
                  sizeof(::Pythia8::Rndm) );
      instance.SetNew(&new_Pythia8cLcLRndm);
      instance.SetNewArray(&newArray_Pythia8cLcLRndm);
      instance.SetDelete(&delete_Pythia8cLcLRndm);
      instance.SetDeleteArray(&deleteArray_Pythia8cLcLRndm);
      instance.SetDestructor(&destruct_Pythia8cLcLRndm);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::Pythia8::Rndm*)
   {
      return GenerateInitInstanceLocal((::Pythia8::Rndm*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::Pythia8::Rndm*)0x0); R__UseDummy(_R__UNIQUE_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *Pythia8cLcLRndm_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const ::Pythia8::Rndm*)0x0)->GetClass();
      Pythia8cLcLRndm_TClassManip(theClass);
   return theClass;
   }

   static void Pythia8cLcLRndm_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   static TClass *Pythia8cLcLRndmEngine_Dictionary();
   static void Pythia8cLcLRndmEngine_TClassManip(TClass*);
   static void delete_Pythia8cLcLRndmEngine(void *p);
   static void deleteArray_Pythia8cLcLRndmEngine(void *p);
   static void destruct_Pythia8cLcLRndmEngine(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::Pythia8::RndmEngine*)
   {
      ::Pythia8::RndmEngine *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(::Pythia8::RndmEngine));
      static ::ROOT::TGenericClassInfo 
         instance("Pythia8::RndmEngine", "Pythia8/Basics.h", 25,
                  typeid(::Pythia8::RndmEngine), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &Pythia8cLcLRndmEngine_Dictionary, isa_proxy, 4,
                  sizeof(::Pythia8::RndmEngine) );
      instance.SetDelete(&delete_Pythia8cLcLRndmEngine);
      instance.SetDeleteArray(&deleteArray_Pythia8cLcLRndmEngine);
      instance.SetDestructor(&destruct_Pythia8cLcLRndmEngine);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::Pythia8::RndmEngine*)
   {
      return GenerateInitInstanceLocal((::Pythia8::RndmEngine*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::Pythia8::RndmEngine*)0x0); R__UseDummy(_R__UNIQUE_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *Pythia8cLcLRndmEngine_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const ::Pythia8::RndmEngine*)0x0)->GetClass();
      Pythia8cLcLRndmEngine_TClassManip(theClass);
   return theClass;
   }

   static void Pythia8cLcLRndmEngine_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   static TClass *Pythia8cLcLSettings_Dictionary();
   static void Pythia8cLcLSettings_TClassManip(TClass*);
   static void *new_Pythia8cLcLSettings(void *p = 0);
   static void *newArray_Pythia8cLcLSettings(Long_t size, void *p);
   static void delete_Pythia8cLcLSettings(void *p);
   static void deleteArray_Pythia8cLcLSettings(void *p);
   static void destruct_Pythia8cLcLSettings(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::Pythia8::Settings*)
   {
      ::Pythia8::Settings *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(::Pythia8::Settings));
      static ::ROOT::TGenericClassInfo 
         instance("Pythia8::Settings", "Pythia8/Settings.h", 195,
                  typeid(::Pythia8::Settings), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &Pythia8cLcLSettings_Dictionary, isa_proxy, 4,
                  sizeof(::Pythia8::Settings) );
      instance.SetNew(&new_Pythia8cLcLSettings);
      instance.SetNewArray(&newArray_Pythia8cLcLSettings);
      instance.SetDelete(&delete_Pythia8cLcLSettings);
      instance.SetDeleteArray(&deleteArray_Pythia8cLcLSettings);
      instance.SetDestructor(&destruct_Pythia8cLcLSettings);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::Pythia8::Settings*)
   {
      return GenerateInitInstanceLocal((::Pythia8::Settings*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::Pythia8::Settings*)0x0); R__UseDummy(_R__UNIQUE_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *Pythia8cLcLSettings_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const ::Pythia8::Settings*)0x0)->GetClass();
      Pythia8cLcLSettings_TClassManip(theClass);
   return theClass;
   }

   static void Pythia8cLcLSettings_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   static TClass *Pythia8cLcLResonanceTop_Dictionary();
   static void Pythia8cLcLResonanceTop_TClassManip(TClass*);
   static void delete_Pythia8cLcLResonanceTop(void *p);
   static void deleteArray_Pythia8cLcLResonanceTop(void *p);
   static void destruct_Pythia8cLcLResonanceTop(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::Pythia8::ResonanceTop*)
   {
      ::Pythia8::ResonanceTop *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(::Pythia8::ResonanceTop));
      static ::ROOT::TGenericClassInfo 
         instance("Pythia8::ResonanceTop", "Pythia8/ResonanceWidths.h", 212,
                  typeid(::Pythia8::ResonanceTop), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &Pythia8cLcLResonanceTop_Dictionary, isa_proxy, 4,
                  sizeof(::Pythia8::ResonanceTop) );
      instance.SetDelete(&delete_Pythia8cLcLResonanceTop);
      instance.SetDeleteArray(&deleteArray_Pythia8cLcLResonanceTop);
      instance.SetDestructor(&destruct_Pythia8cLcLResonanceTop);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::Pythia8::ResonanceTop*)
   {
      return GenerateInitInstanceLocal((::Pythia8::ResonanceTop*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::Pythia8::ResonanceTop*)0x0); R__UseDummy(_R__UNIQUE_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *Pythia8cLcLResonanceTop_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const ::Pythia8::ResonanceTop*)0x0)->GetClass();
      Pythia8cLcLResonanceTop_TClassManip(theClass);
   return theClass;
   }

   static void Pythia8cLcLResonanceTop_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   static TClass *Pythia8cLcLResonanceGeneric_Dictionary();
   static void Pythia8cLcLResonanceGeneric_TClassManip(TClass*);
   static void delete_Pythia8cLcLResonanceGeneric(void *p);
   static void deleteArray_Pythia8cLcLResonanceGeneric(void *p);
   static void destruct_Pythia8cLcLResonanceGeneric(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::Pythia8::ResonanceGeneric*)
   {
      ::Pythia8::ResonanceGeneric *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(::Pythia8::ResonanceGeneric));
      static ::ROOT::TGenericClassInfo 
         instance("Pythia8::ResonanceGeneric", "Pythia8/ResonanceWidths.h", 141,
                  typeid(::Pythia8::ResonanceGeneric), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &Pythia8cLcLResonanceGeneric_Dictionary, isa_proxy, 4,
                  sizeof(::Pythia8::ResonanceGeneric) );
      instance.SetDelete(&delete_Pythia8cLcLResonanceGeneric);
      instance.SetDeleteArray(&deleteArray_Pythia8cLcLResonanceGeneric);
      instance.SetDestructor(&destruct_Pythia8cLcLResonanceGeneric);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::Pythia8::ResonanceGeneric*)
   {
      return GenerateInitInstanceLocal((::Pythia8::ResonanceGeneric*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::Pythia8::ResonanceGeneric*)0x0); R__UseDummy(_R__UNIQUE_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *Pythia8cLcLResonanceGeneric_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const ::Pythia8::ResonanceGeneric*)0x0)->GetClass();
      Pythia8cLcLResonanceGeneric_TClassManip(theClass);
   return theClass;
   }

   static void Pythia8cLcLResonanceGeneric_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   static TClass *Pythia8cLcLResonanceGmZ_Dictionary();
   static void Pythia8cLcLResonanceGmZ_TClassManip(TClass*);
   static void delete_Pythia8cLcLResonanceGmZ(void *p);
   static void deleteArray_Pythia8cLcLResonanceGmZ(void *p);
   static void destruct_Pythia8cLcLResonanceGmZ(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::Pythia8::ResonanceGmZ*)
   {
      ::Pythia8::ResonanceGmZ *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(::Pythia8::ResonanceGmZ));
      static ::ROOT::TGenericClassInfo 
         instance("Pythia8::ResonanceGmZ", "Pythia8/ResonanceWidths.h", 157,
                  typeid(::Pythia8::ResonanceGmZ), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &Pythia8cLcLResonanceGmZ_Dictionary, isa_proxy, 4,
                  sizeof(::Pythia8::ResonanceGmZ) );
      instance.SetDelete(&delete_Pythia8cLcLResonanceGmZ);
      instance.SetDeleteArray(&deleteArray_Pythia8cLcLResonanceGmZ);
      instance.SetDestructor(&destruct_Pythia8cLcLResonanceGmZ);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::Pythia8::ResonanceGmZ*)
   {
      return GenerateInitInstanceLocal((::Pythia8::ResonanceGmZ*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::Pythia8::ResonanceGmZ*)0x0); R__UseDummy(_R__UNIQUE_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *Pythia8cLcLResonanceGmZ_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const ::Pythia8::ResonanceGmZ*)0x0)->GetClass();
      Pythia8cLcLResonanceGmZ_TClassManip(theClass);
   return theClass;
   }

   static void Pythia8cLcLResonanceGmZ_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   static TClass *Pythia8cLcLResonanceW_Dictionary();
   static void Pythia8cLcLResonanceW_TClassManip(TClass*);
   static void delete_Pythia8cLcLResonanceW(void *p);
   static void deleteArray_Pythia8cLcLResonanceW(void *p);
   static void destruct_Pythia8cLcLResonanceW(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::Pythia8::ResonanceW*)
   {
      ::Pythia8::ResonanceW *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(::Pythia8::ResonanceW));
      static ::ROOT::TGenericClassInfo 
         instance("Pythia8::ResonanceW", "Pythia8/ResonanceWidths.h", 185,
                  typeid(::Pythia8::ResonanceW), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &Pythia8cLcLResonanceW_Dictionary, isa_proxy, 4,
                  sizeof(::Pythia8::ResonanceW) );
      instance.SetDelete(&delete_Pythia8cLcLResonanceW);
      instance.SetDeleteArray(&deleteArray_Pythia8cLcLResonanceW);
      instance.SetDestructor(&destruct_Pythia8cLcLResonanceW);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::Pythia8::ResonanceW*)
   {
      return GenerateInitInstanceLocal((::Pythia8::ResonanceW*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::Pythia8::ResonanceW*)0x0); R__UseDummy(_R__UNIQUE_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *Pythia8cLcLResonanceW_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const ::Pythia8::ResonanceW*)0x0)->GetClass();
      Pythia8cLcLResonanceW_TClassManip(theClass);
   return theClass;
   }

   static void Pythia8cLcLResonanceW_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   static TClass *Pythia8cLcLResonanceFour_Dictionary();
   static void Pythia8cLcLResonanceFour_TClassManip(TClass*);
   static void delete_Pythia8cLcLResonanceFour(void *p);
   static void deleteArray_Pythia8cLcLResonanceFour(void *p);
   static void destruct_Pythia8cLcLResonanceFour(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::Pythia8::ResonanceFour*)
   {
      ::Pythia8::ResonanceFour *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(::Pythia8::ResonanceFour));
      static ::ROOT::TGenericClassInfo 
         instance("Pythia8::ResonanceFour", "Pythia8/ResonanceWidths.h", 239,
                  typeid(::Pythia8::ResonanceFour), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &Pythia8cLcLResonanceFour_Dictionary, isa_proxy, 4,
                  sizeof(::Pythia8::ResonanceFour) );
      instance.SetDelete(&delete_Pythia8cLcLResonanceFour);
      instance.SetDeleteArray(&deleteArray_Pythia8cLcLResonanceFour);
      instance.SetDestructor(&destruct_Pythia8cLcLResonanceFour);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::Pythia8::ResonanceFour*)
   {
      return GenerateInitInstanceLocal((::Pythia8::ResonanceFour*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::Pythia8::ResonanceFour*)0x0); R__UseDummy(_R__UNIQUE_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *Pythia8cLcLResonanceFour_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const ::Pythia8::ResonanceFour*)0x0)->GetClass();
      Pythia8cLcLResonanceFour_TClassManip(theClass);
   return theClass;
   }

   static void Pythia8cLcLResonanceFour_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   static TClass *Pythia8cLcLResonanceH_Dictionary();
   static void Pythia8cLcLResonanceH_TClassManip(TClass*);
   static void delete_Pythia8cLcLResonanceH(void *p);
   static void deleteArray_Pythia8cLcLResonanceH(void *p);
   static void destruct_Pythia8cLcLResonanceH(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::Pythia8::ResonanceH*)
   {
      ::Pythia8::ResonanceH *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(::Pythia8::ResonanceH));
      static ::ROOT::TGenericClassInfo 
         instance("Pythia8::ResonanceH", "Pythia8/ResonanceWidths.h", 267,
                  typeid(::Pythia8::ResonanceH), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &Pythia8cLcLResonanceH_Dictionary, isa_proxy, 4,
                  sizeof(::Pythia8::ResonanceH) );
      instance.SetDelete(&delete_Pythia8cLcLResonanceH);
      instance.SetDeleteArray(&deleteArray_Pythia8cLcLResonanceH);
      instance.SetDestructor(&destruct_Pythia8cLcLResonanceH);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::Pythia8::ResonanceH*)
   {
      return GenerateInitInstanceLocal((::Pythia8::ResonanceH*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::Pythia8::ResonanceH*)0x0); R__UseDummy(_R__UNIQUE_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *Pythia8cLcLResonanceH_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const ::Pythia8::ResonanceH*)0x0)->GetClass();
      Pythia8cLcLResonanceH_TClassManip(theClass);
   return theClass;
   }

   static void Pythia8cLcLResonanceH_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   static TClass *Pythia8cLcLResonanceHchg_Dictionary();
   static void Pythia8cLcLResonanceHchg_TClassManip(TClass*);
   static void delete_Pythia8cLcLResonanceHchg(void *p);
   static void deleteArray_Pythia8cLcLResonanceHchg(void *p);
   static void destruct_Pythia8cLcLResonanceHchg(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::Pythia8::ResonanceHchg*)
   {
      ::Pythia8::ResonanceHchg *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(::Pythia8::ResonanceHchg));
      static ::ROOT::TGenericClassInfo 
         instance("Pythia8::ResonanceHchg", "Pythia8/ResonanceWidths.h", 315,
                  typeid(::Pythia8::ResonanceHchg), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &Pythia8cLcLResonanceHchg_Dictionary, isa_proxy, 4,
                  sizeof(::Pythia8::ResonanceHchg) );
      instance.SetDelete(&delete_Pythia8cLcLResonanceHchg);
      instance.SetDeleteArray(&deleteArray_Pythia8cLcLResonanceHchg);
      instance.SetDestructor(&destruct_Pythia8cLcLResonanceHchg);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::Pythia8::ResonanceHchg*)
   {
      return GenerateInitInstanceLocal((::Pythia8::ResonanceHchg*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::Pythia8::ResonanceHchg*)0x0); R__UseDummy(_R__UNIQUE_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *Pythia8cLcLResonanceHchg_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const ::Pythia8::ResonanceHchg*)0x0)->GetClass();
      Pythia8cLcLResonanceHchg_TClassManip(theClass);
   return theClass;
   }

   static void Pythia8cLcLResonanceHchg_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   static TClass *Pythia8cLcLResonanceZprime_Dictionary();
   static void Pythia8cLcLResonanceZprime_TClassManip(TClass*);
   static void delete_Pythia8cLcLResonanceZprime(void *p);
   static void deleteArray_Pythia8cLcLResonanceZprime(void *p);
   static void destruct_Pythia8cLcLResonanceZprime(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::Pythia8::ResonanceZprime*)
   {
      ::Pythia8::ResonanceZprime *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(::Pythia8::ResonanceZprime));
      static ::ROOT::TGenericClassInfo 
         instance("Pythia8::ResonanceZprime", "Pythia8/ResonanceWidths.h", 343,
                  typeid(::Pythia8::ResonanceZprime), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &Pythia8cLcLResonanceZprime_Dictionary, isa_proxy, 4,
                  sizeof(::Pythia8::ResonanceZprime) );
      instance.SetDelete(&delete_Pythia8cLcLResonanceZprime);
      instance.SetDeleteArray(&deleteArray_Pythia8cLcLResonanceZprime);
      instance.SetDestructor(&destruct_Pythia8cLcLResonanceZprime);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::Pythia8::ResonanceZprime*)
   {
      return GenerateInitInstanceLocal((::Pythia8::ResonanceZprime*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::Pythia8::ResonanceZprime*)0x0); R__UseDummy(_R__UNIQUE_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *Pythia8cLcLResonanceZprime_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const ::Pythia8::ResonanceZprime*)0x0)->GetClass();
      Pythia8cLcLResonanceZprime_TClassManip(theClass);
   return theClass;
   }

   static void Pythia8cLcLResonanceZprime_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   static TClass *Pythia8cLcLResonanceWprime_Dictionary();
   static void Pythia8cLcLResonanceWprime_TClassManip(TClass*);
   static void delete_Pythia8cLcLResonanceWprime(void *p);
   static void deleteArray_Pythia8cLcLResonanceWprime(void *p);
   static void destruct_Pythia8cLcLResonanceWprime(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::Pythia8::ResonanceWprime*)
   {
      ::Pythia8::ResonanceWprime *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(::Pythia8::ResonanceWprime));
      static ::ROOT::TGenericClassInfo 
         instance("Pythia8::ResonanceWprime", "Pythia8/ResonanceWidths.h", 373,
                  typeid(::Pythia8::ResonanceWprime), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &Pythia8cLcLResonanceWprime_Dictionary, isa_proxy, 4,
                  sizeof(::Pythia8::ResonanceWprime) );
      instance.SetDelete(&delete_Pythia8cLcLResonanceWprime);
      instance.SetDeleteArray(&deleteArray_Pythia8cLcLResonanceWprime);
      instance.SetDestructor(&destruct_Pythia8cLcLResonanceWprime);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::Pythia8::ResonanceWprime*)
   {
      return GenerateInitInstanceLocal((::Pythia8::ResonanceWprime*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::Pythia8::ResonanceWprime*)0x0); R__UseDummy(_R__UNIQUE_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *Pythia8cLcLResonanceWprime_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const ::Pythia8::ResonanceWprime*)0x0)->GetClass();
      Pythia8cLcLResonanceWprime_TClassManip(theClass);
   return theClass;
   }

   static void Pythia8cLcLResonanceWprime_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   static TClass *Pythia8cLcLResonanceRhorizontal_Dictionary();
   static void Pythia8cLcLResonanceRhorizontal_TClassManip(TClass*);
   static void delete_Pythia8cLcLResonanceRhorizontal(void *p);
   static void deleteArray_Pythia8cLcLResonanceRhorizontal(void *p);
   static void destruct_Pythia8cLcLResonanceRhorizontal(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::Pythia8::ResonanceRhorizontal*)
   {
      ::Pythia8::ResonanceRhorizontal *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(::Pythia8::ResonanceRhorizontal));
      static ::ROOT::TGenericClassInfo 
         instance("Pythia8::ResonanceRhorizontal", "Pythia8/ResonanceWidths.h", 400,
                  typeid(::Pythia8::ResonanceRhorizontal), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &Pythia8cLcLResonanceRhorizontal_Dictionary, isa_proxy, 4,
                  sizeof(::Pythia8::ResonanceRhorizontal) );
      instance.SetDelete(&delete_Pythia8cLcLResonanceRhorizontal);
      instance.SetDeleteArray(&deleteArray_Pythia8cLcLResonanceRhorizontal);
      instance.SetDestructor(&destruct_Pythia8cLcLResonanceRhorizontal);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::Pythia8::ResonanceRhorizontal*)
   {
      return GenerateInitInstanceLocal((::Pythia8::ResonanceRhorizontal*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::Pythia8::ResonanceRhorizontal*)0x0); R__UseDummy(_R__UNIQUE_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *Pythia8cLcLResonanceRhorizontal_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const ::Pythia8::ResonanceRhorizontal*)0x0)->GetClass();
      Pythia8cLcLResonanceRhorizontal_TClassManip(theClass);
   return theClass;
   }

   static void Pythia8cLcLResonanceRhorizontal_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   static TClass *Pythia8cLcLResonanceExcited_Dictionary();
   static void Pythia8cLcLResonanceExcited_TClassManip(TClass*);
   static void delete_Pythia8cLcLResonanceExcited(void *p);
   static void deleteArray_Pythia8cLcLResonanceExcited(void *p);
   static void destruct_Pythia8cLcLResonanceExcited(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::Pythia8::ResonanceExcited*)
   {
      ::Pythia8::ResonanceExcited *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(::Pythia8::ResonanceExcited));
      static ::ROOT::TGenericClassInfo 
         instance("Pythia8::ResonanceExcited", "Pythia8/ResonanceWidths.h", 427,
                  typeid(::Pythia8::ResonanceExcited), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &Pythia8cLcLResonanceExcited_Dictionary, isa_proxy, 4,
                  sizeof(::Pythia8::ResonanceExcited) );
      instance.SetDelete(&delete_Pythia8cLcLResonanceExcited);
      instance.SetDeleteArray(&deleteArray_Pythia8cLcLResonanceExcited);
      instance.SetDestructor(&destruct_Pythia8cLcLResonanceExcited);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::Pythia8::ResonanceExcited*)
   {
      return GenerateInitInstanceLocal((::Pythia8::ResonanceExcited*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::Pythia8::ResonanceExcited*)0x0); R__UseDummy(_R__UNIQUE_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *Pythia8cLcLResonanceExcited_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const ::Pythia8::ResonanceExcited*)0x0)->GetClass();
      Pythia8cLcLResonanceExcited_TClassManip(theClass);
   return theClass;
   }

   static void Pythia8cLcLResonanceExcited_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   static TClass *Pythia8cLcLResonanceGraviton_Dictionary();
   static void Pythia8cLcLResonanceGraviton_TClassManip(TClass*);
   static void delete_Pythia8cLcLResonanceGraviton(void *p);
   static void deleteArray_Pythia8cLcLResonanceGraviton(void *p);
   static void destruct_Pythia8cLcLResonanceGraviton(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::Pythia8::ResonanceGraviton*)
   {
      ::Pythia8::ResonanceGraviton *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(::Pythia8::ResonanceGraviton));
      static ::ROOT::TGenericClassInfo 
         instance("Pythia8::ResonanceGraviton", "Pythia8/ResonanceWidths.h", 454,
                  typeid(::Pythia8::ResonanceGraviton), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &Pythia8cLcLResonanceGraviton_Dictionary, isa_proxy, 4,
                  sizeof(::Pythia8::ResonanceGraviton) );
      instance.SetDelete(&delete_Pythia8cLcLResonanceGraviton);
      instance.SetDeleteArray(&deleteArray_Pythia8cLcLResonanceGraviton);
      instance.SetDestructor(&destruct_Pythia8cLcLResonanceGraviton);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::Pythia8::ResonanceGraviton*)
   {
      return GenerateInitInstanceLocal((::Pythia8::ResonanceGraviton*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::Pythia8::ResonanceGraviton*)0x0); R__UseDummy(_R__UNIQUE_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *Pythia8cLcLResonanceGraviton_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const ::Pythia8::ResonanceGraviton*)0x0)->GetClass();
      Pythia8cLcLResonanceGraviton_TClassManip(theClass);
   return theClass;
   }

   static void Pythia8cLcLResonanceGraviton_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   static TClass *Pythia8cLcLResonanceLeptoquark_Dictionary();
   static void Pythia8cLcLResonanceLeptoquark_TClassManip(TClass*);
   static void delete_Pythia8cLcLResonanceLeptoquark(void *p);
   static void deleteArray_Pythia8cLcLResonanceLeptoquark(void *p);
   static void destruct_Pythia8cLcLResonanceLeptoquark(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::Pythia8::ResonanceLeptoquark*)
   {
      ::Pythia8::ResonanceLeptoquark *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(::Pythia8::ResonanceLeptoquark));
      static ::ROOT::TGenericClassInfo 
         instance("Pythia8::ResonanceLeptoquark", "Pythia8/ResonanceWidths.h", 520,
                  typeid(::Pythia8::ResonanceLeptoquark), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &Pythia8cLcLResonanceLeptoquark_Dictionary, isa_proxy, 4,
                  sizeof(::Pythia8::ResonanceLeptoquark) );
      instance.SetDelete(&delete_Pythia8cLcLResonanceLeptoquark);
      instance.SetDeleteArray(&deleteArray_Pythia8cLcLResonanceLeptoquark);
      instance.SetDestructor(&destruct_Pythia8cLcLResonanceLeptoquark);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::Pythia8::ResonanceLeptoquark*)
   {
      return GenerateInitInstanceLocal((::Pythia8::ResonanceLeptoquark*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::Pythia8::ResonanceLeptoquark*)0x0); R__UseDummy(_R__UNIQUE_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *Pythia8cLcLResonanceLeptoquark_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const ::Pythia8::ResonanceLeptoquark*)0x0)->GetClass();
      Pythia8cLcLResonanceLeptoquark_TClassManip(theClass);
   return theClass;
   }

   static void Pythia8cLcLResonanceLeptoquark_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   static TClass *Pythia8cLcLResonanceNuRight_Dictionary();
   static void Pythia8cLcLResonanceNuRight_TClassManip(TClass*);
   static void delete_Pythia8cLcLResonanceNuRight(void *p);
   static void deleteArray_Pythia8cLcLResonanceNuRight(void *p);
   static void destruct_Pythia8cLcLResonanceNuRight(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::Pythia8::ResonanceNuRight*)
   {
      ::Pythia8::ResonanceNuRight *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(::Pythia8::ResonanceNuRight));
      static ::ROOT::TGenericClassInfo 
         instance("Pythia8::ResonanceNuRight", "Pythia8/ResonanceWidths.h", 547,
                  typeid(::Pythia8::ResonanceNuRight), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &Pythia8cLcLResonanceNuRight_Dictionary, isa_proxy, 4,
                  sizeof(::Pythia8::ResonanceNuRight) );
      instance.SetDelete(&delete_Pythia8cLcLResonanceNuRight);
      instance.SetDeleteArray(&deleteArray_Pythia8cLcLResonanceNuRight);
      instance.SetDestructor(&destruct_Pythia8cLcLResonanceNuRight);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::Pythia8::ResonanceNuRight*)
   {
      return GenerateInitInstanceLocal((::Pythia8::ResonanceNuRight*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::Pythia8::ResonanceNuRight*)0x0); R__UseDummy(_R__UNIQUE_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *Pythia8cLcLResonanceNuRight_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const ::Pythia8::ResonanceNuRight*)0x0)->GetClass();
      Pythia8cLcLResonanceNuRight_TClassManip(theClass);
   return theClass;
   }

   static void Pythia8cLcLResonanceNuRight_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   static TClass *Pythia8cLcLResonanceZRight_Dictionary();
   static void Pythia8cLcLResonanceZRight_TClassManip(TClass*);
   static void delete_Pythia8cLcLResonanceZRight(void *p);
   static void deleteArray_Pythia8cLcLResonanceZRight(void *p);
   static void destruct_Pythia8cLcLResonanceZRight(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::Pythia8::ResonanceZRight*)
   {
      ::Pythia8::ResonanceZRight *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(::Pythia8::ResonanceZRight));
      static ::ROOT::TGenericClassInfo 
         instance("Pythia8::ResonanceZRight", "Pythia8/ResonanceWidths.h", 574,
                  typeid(::Pythia8::ResonanceZRight), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &Pythia8cLcLResonanceZRight_Dictionary, isa_proxy, 4,
                  sizeof(::Pythia8::ResonanceZRight) );
      instance.SetDelete(&delete_Pythia8cLcLResonanceZRight);
      instance.SetDeleteArray(&deleteArray_Pythia8cLcLResonanceZRight);
      instance.SetDestructor(&destruct_Pythia8cLcLResonanceZRight);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::Pythia8::ResonanceZRight*)
   {
      return GenerateInitInstanceLocal((::Pythia8::ResonanceZRight*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::Pythia8::ResonanceZRight*)0x0); R__UseDummy(_R__UNIQUE_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *Pythia8cLcLResonanceZRight_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const ::Pythia8::ResonanceZRight*)0x0)->GetClass();
      Pythia8cLcLResonanceZRight_TClassManip(theClass);
   return theClass;
   }

   static void Pythia8cLcLResonanceZRight_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   static TClass *Pythia8cLcLResonanceWRight_Dictionary();
   static void Pythia8cLcLResonanceWRight_TClassManip(TClass*);
   static void delete_Pythia8cLcLResonanceWRight(void *p);
   static void deleteArray_Pythia8cLcLResonanceWRight(void *p);
   static void destruct_Pythia8cLcLResonanceWRight(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::Pythia8::ResonanceWRight*)
   {
      ::Pythia8::ResonanceWRight *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(::Pythia8::ResonanceWRight));
      static ::ROOT::TGenericClassInfo 
         instance("Pythia8::ResonanceWRight", "Pythia8/ResonanceWidths.h", 601,
                  typeid(::Pythia8::ResonanceWRight), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &Pythia8cLcLResonanceWRight_Dictionary, isa_proxy, 4,
                  sizeof(::Pythia8::ResonanceWRight) );
      instance.SetDelete(&delete_Pythia8cLcLResonanceWRight);
      instance.SetDeleteArray(&deleteArray_Pythia8cLcLResonanceWRight);
      instance.SetDestructor(&destruct_Pythia8cLcLResonanceWRight);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::Pythia8::ResonanceWRight*)
   {
      return GenerateInitInstanceLocal((::Pythia8::ResonanceWRight*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::Pythia8::ResonanceWRight*)0x0); R__UseDummy(_R__UNIQUE_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *Pythia8cLcLResonanceWRight_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const ::Pythia8::ResonanceWRight*)0x0)->GetClass();
      Pythia8cLcLResonanceWRight_TClassManip(theClass);
   return theClass;
   }

   static void Pythia8cLcLResonanceWRight_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   static TClass *Pythia8cLcLResonanceHchgchgLeft_Dictionary();
   static void Pythia8cLcLResonanceHchgchgLeft_TClassManip(TClass*);
   static void delete_Pythia8cLcLResonanceHchgchgLeft(void *p);
   static void deleteArray_Pythia8cLcLResonanceHchgchgLeft(void *p);
   static void destruct_Pythia8cLcLResonanceHchgchgLeft(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::Pythia8::ResonanceHchgchgLeft*)
   {
      ::Pythia8::ResonanceHchgchgLeft *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(::Pythia8::ResonanceHchgchgLeft));
      static ::ROOT::TGenericClassInfo 
         instance("Pythia8::ResonanceHchgchgLeft", "Pythia8/ResonanceWidths.h", 628,
                  typeid(::Pythia8::ResonanceHchgchgLeft), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &Pythia8cLcLResonanceHchgchgLeft_Dictionary, isa_proxy, 4,
                  sizeof(::Pythia8::ResonanceHchgchgLeft) );
      instance.SetDelete(&delete_Pythia8cLcLResonanceHchgchgLeft);
      instance.SetDeleteArray(&deleteArray_Pythia8cLcLResonanceHchgchgLeft);
      instance.SetDestructor(&destruct_Pythia8cLcLResonanceHchgchgLeft);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::Pythia8::ResonanceHchgchgLeft*)
   {
      return GenerateInitInstanceLocal((::Pythia8::ResonanceHchgchgLeft*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::Pythia8::ResonanceHchgchgLeft*)0x0); R__UseDummy(_R__UNIQUE_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *Pythia8cLcLResonanceHchgchgLeft_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const ::Pythia8::ResonanceHchgchgLeft*)0x0)->GetClass();
      Pythia8cLcLResonanceHchgchgLeft_TClassManip(theClass);
   return theClass;
   }

   static void Pythia8cLcLResonanceHchgchgLeft_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   static TClass *Pythia8cLcLResonanceHchgchgRight_Dictionary();
   static void Pythia8cLcLResonanceHchgchgRight_TClassManip(TClass*);
   static void delete_Pythia8cLcLResonanceHchgchgRight(void *p);
   static void deleteArray_Pythia8cLcLResonanceHchgchgRight(void *p);
   static void destruct_Pythia8cLcLResonanceHchgchgRight(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::Pythia8::ResonanceHchgchgRight*)
   {
      ::Pythia8::ResonanceHchgchgRight *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(::Pythia8::ResonanceHchgchgRight));
      static ::ROOT::TGenericClassInfo 
         instance("Pythia8::ResonanceHchgchgRight", "Pythia8/ResonanceWidths.h", 655,
                  typeid(::Pythia8::ResonanceHchgchgRight), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &Pythia8cLcLResonanceHchgchgRight_Dictionary, isa_proxy, 4,
                  sizeof(::Pythia8::ResonanceHchgchgRight) );
      instance.SetDelete(&delete_Pythia8cLcLResonanceHchgchgRight);
      instance.SetDeleteArray(&deleteArray_Pythia8cLcLResonanceHchgchgRight);
      instance.SetDestructor(&destruct_Pythia8cLcLResonanceHchgchgRight);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::Pythia8::ResonanceHchgchgRight*)
   {
      return GenerateInitInstanceLocal((::Pythia8::ResonanceHchgchgRight*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::Pythia8::ResonanceHchgchgRight*)0x0); R__UseDummy(_R__UNIQUE_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *Pythia8cLcLResonanceHchgchgRight_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const ::Pythia8::ResonanceHchgchgRight*)0x0)->GetClass();
      Pythia8cLcLResonanceHchgchgRight_TClassManip(theClass);
   return theClass;
   }

   static void Pythia8cLcLResonanceHchgchgRight_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   static TClass *Pythia8cLcLSigmaProcess_Dictionary();
   static void Pythia8cLcLSigmaProcess_TClassManip(TClass*);
   static void delete_Pythia8cLcLSigmaProcess(void *p);
   static void deleteArray_Pythia8cLcLSigmaProcess(void *p);
   static void destruct_Pythia8cLcLSigmaProcess(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::Pythia8::SigmaProcess*)
   {
      ::Pythia8::SigmaProcess *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(::Pythia8::SigmaProcess));
      static ::ROOT::TGenericClassInfo 
         instance("Pythia8::SigmaProcess", "Pythia8/SigmaProcess.h", 84,
                  typeid(::Pythia8::SigmaProcess), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &Pythia8cLcLSigmaProcess_Dictionary, isa_proxy, 4,
                  sizeof(::Pythia8::SigmaProcess) );
      instance.SetDelete(&delete_Pythia8cLcLSigmaProcess);
      instance.SetDeleteArray(&deleteArray_Pythia8cLcLSigmaProcess);
      instance.SetDestructor(&destruct_Pythia8cLcLSigmaProcess);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::Pythia8::SigmaProcess*)
   {
      return GenerateInitInstanceLocal((::Pythia8::SigmaProcess*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::Pythia8::SigmaProcess*)0x0); R__UseDummy(_R__UNIQUE_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *Pythia8cLcLSigmaProcess_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const ::Pythia8::SigmaProcess*)0x0)->GetClass();
      Pythia8cLcLSigmaProcess_TClassManip(theClass);
   return theClass;
   }

   static void Pythia8cLcLSigmaProcess_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_Pythia8cLcLEvent(void *p) {
      return  p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) ::Pythia8::Event : new ::Pythia8::Event;
   }
   static void *newArray_Pythia8cLcLEvent(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) ::Pythia8::Event[nElements] : new ::Pythia8::Event[nElements];
   }
   // Wrapper around operator delete
   static void delete_Pythia8cLcLEvent(void *p) {
      delete ((::Pythia8::Event*)p);
   }
   static void deleteArray_Pythia8cLcLEvent(void *p) {
      delete [] ((::Pythia8::Event*)p);
   }
   static void destruct_Pythia8cLcLEvent(void *p) {
      typedef ::Pythia8::Event current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::Pythia8::Event

namespace ROOT {
   // Wrappers around operator new
   static void *new_Pythia8cLcLParticle(void *p) {
      return  p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) ::Pythia8::Particle : new ::Pythia8::Particle;
   }
   static void *newArray_Pythia8cLcLParticle(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) ::Pythia8::Particle[nElements] : new ::Pythia8::Particle[nElements];
   }
   // Wrapper around operator delete
   static void delete_Pythia8cLcLParticle(void *p) {
      delete ((::Pythia8::Particle*)p);
   }
   static void deleteArray_Pythia8cLcLParticle(void *p) {
      delete [] ((::Pythia8::Particle*)p);
   }
   static void destruct_Pythia8cLcLParticle(void *p) {
      typedef ::Pythia8::Particle current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::Pythia8::Particle

namespace ROOT {
   // Wrappers around operator new
   static void *new_Pythia8cLcLJunction(void *p) {
      return  p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) ::Pythia8::Junction : new ::Pythia8::Junction;
   }
   static void *newArray_Pythia8cLcLJunction(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) ::Pythia8::Junction[nElements] : new ::Pythia8::Junction[nElements];
   }
   // Wrapper around operator delete
   static void delete_Pythia8cLcLJunction(void *p) {
      delete ((::Pythia8::Junction*)p);
   }
   static void deleteArray_Pythia8cLcLJunction(void *p) {
      delete [] ((::Pythia8::Junction*)p);
   }
   static void destruct_Pythia8cLcLJunction(void *p) {
      typedef ::Pythia8::Junction current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::Pythia8::Junction

namespace ROOT {
   // Wrappers around operator new
   static void *new_Pythia8cLcLVec4(void *p) {
      return  p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) ::Pythia8::Vec4 : new ::Pythia8::Vec4;
   }
   static void *newArray_Pythia8cLcLVec4(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) ::Pythia8::Vec4[nElements] : new ::Pythia8::Vec4[nElements];
   }
   // Wrapper around operator delete
   static void delete_Pythia8cLcLVec4(void *p) {
      delete ((::Pythia8::Vec4*)p);
   }
   static void deleteArray_Pythia8cLcLVec4(void *p) {
      delete [] ((::Pythia8::Vec4*)p);
   }
   static void destruct_Pythia8cLcLVec4(void *p) {
      typedef ::Pythia8::Vec4 current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::Pythia8::Vec4

namespace ROOT {
   // Wrappers around operator new
   static void *new_Pythia8cLcLParticleData(void *p) {
      return  p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) ::Pythia8::ParticleData : new ::Pythia8::ParticleData;
   }
   static void *newArray_Pythia8cLcLParticleData(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) ::Pythia8::ParticleData[nElements] : new ::Pythia8::ParticleData[nElements];
   }
   // Wrapper around operator delete
   static void delete_Pythia8cLcLParticleData(void *p) {
      delete ((::Pythia8::ParticleData*)p);
   }
   static void deleteArray_Pythia8cLcLParticleData(void *p) {
      delete [] ((::Pythia8::ParticleData*)p);
   }
   static void destruct_Pythia8cLcLParticleData(void *p) {
      typedef ::Pythia8::ParticleData current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::Pythia8::ParticleData

namespace ROOT {
   // Wrappers around operator new
   static void *new_Pythia8cLcLParticleDataEntry(void *p) {
      return  p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) ::Pythia8::ParticleDataEntry : new ::Pythia8::ParticleDataEntry;
   }
   static void *newArray_Pythia8cLcLParticleDataEntry(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) ::Pythia8::ParticleDataEntry[nElements] : new ::Pythia8::ParticleDataEntry[nElements];
   }
   // Wrapper around operator delete
   static void delete_Pythia8cLcLParticleDataEntry(void *p) {
      delete ((::Pythia8::ParticleDataEntry*)p);
   }
   static void deleteArray_Pythia8cLcLParticleDataEntry(void *p) {
      delete [] ((::Pythia8::ParticleDataEntry*)p);
   }
   static void destruct_Pythia8cLcLParticleDataEntry(void *p) {
      typedef ::Pythia8::ParticleDataEntry current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::Pythia8::ParticleDataEntry

namespace ROOT {
   // Wrappers around operator new
   static void *new_Pythia8cLcLDecayChannel(void *p) {
      return  p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) ::Pythia8::DecayChannel : new ::Pythia8::DecayChannel;
   }
   static void *newArray_Pythia8cLcLDecayChannel(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) ::Pythia8::DecayChannel[nElements] : new ::Pythia8::DecayChannel[nElements];
   }
   // Wrapper around operator delete
   static void delete_Pythia8cLcLDecayChannel(void *p) {
      delete ((::Pythia8::DecayChannel*)p);
   }
   static void deleteArray_Pythia8cLcLDecayChannel(void *p) {
      delete [] ((::Pythia8::DecayChannel*)p);
   }
   static void destruct_Pythia8cLcLDecayChannel(void *p) {
      typedef ::Pythia8::DecayChannel current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::Pythia8::DecayChannel

namespace ROOT {
   // Wrappers around operator new
   static void *new_Pythia8cLcLPythia(void *p) {
      return  p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) ::Pythia8::Pythia : new ::Pythia8::Pythia;
   }
   static void *newArray_Pythia8cLcLPythia(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) ::Pythia8::Pythia[nElements] : new ::Pythia8::Pythia[nElements];
   }
   // Wrapper around operator delete
   static void delete_Pythia8cLcLPythia(void *p) {
      delete ((::Pythia8::Pythia*)p);
   }
   static void deleteArray_Pythia8cLcLPythia(void *p) {
      delete [] ((::Pythia8::Pythia*)p);
   }
   static void destruct_Pythia8cLcLPythia(void *p) {
      typedef ::Pythia8::Pythia current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::Pythia8::Pythia

namespace ROOT {
   // Wrappers around operator new
   static void *new_Pythia8cLcLCoupSM(void *p) {
      return  p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) ::Pythia8::CoupSM : new ::Pythia8::CoupSM;
   }
   static void *newArray_Pythia8cLcLCoupSM(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) ::Pythia8::CoupSM[nElements] : new ::Pythia8::CoupSM[nElements];
   }
   // Wrapper around operator delete
   static void delete_Pythia8cLcLCoupSM(void *p) {
      delete ((::Pythia8::CoupSM*)p);
   }
   static void deleteArray_Pythia8cLcLCoupSM(void *p) {
      delete [] ((::Pythia8::CoupSM*)p);
   }
   static void destruct_Pythia8cLcLCoupSM(void *p) {
      typedef ::Pythia8::CoupSM current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::Pythia8::CoupSM

namespace ROOT {
   // Wrappers around operator new
   static void *new_Pythia8cLcLCouplings(void *p) {
      return  p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) ::Pythia8::Couplings : new ::Pythia8::Couplings;
   }
   static void *newArray_Pythia8cLcLCouplings(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) ::Pythia8::Couplings[nElements] : new ::Pythia8::Couplings[nElements];
   }
   // Wrapper around operator delete
   static void delete_Pythia8cLcLCouplings(void *p) {
      delete ((::Pythia8::Couplings*)p);
   }
   static void deleteArray_Pythia8cLcLCouplings(void *p) {
      delete [] ((::Pythia8::Couplings*)p);
   }
   static void destruct_Pythia8cLcLCouplings(void *p) {
      typedef ::Pythia8::Couplings current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::Pythia8::Couplings

namespace ROOT {
   // Wrappers around operator new
   static void *new_Pythia8cLcLInBeam(void *p) {
      return  p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) ::Pythia8::InBeam : new ::Pythia8::InBeam;
   }
   static void *newArray_Pythia8cLcLInBeam(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) ::Pythia8::InBeam[nElements] : new ::Pythia8::InBeam[nElements];
   }
   // Wrapper around operator delete
   static void delete_Pythia8cLcLInBeam(void *p) {
      delete ((::Pythia8::InBeam*)p);
   }
   static void deleteArray_Pythia8cLcLInBeam(void *p) {
      delete [] ((::Pythia8::InBeam*)p);
   }
   static void destruct_Pythia8cLcLInBeam(void *p) {
      typedef ::Pythia8::InBeam current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::Pythia8::InBeam

namespace ROOT {
   // Wrappers around operator new
   static void *new_Pythia8cLcLInPair(void *p) {
      return  p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) ::Pythia8::InPair : new ::Pythia8::InPair;
   }
   static void *newArray_Pythia8cLcLInPair(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) ::Pythia8::InPair[nElements] : new ::Pythia8::InPair[nElements];
   }
   // Wrapper around operator delete
   static void delete_Pythia8cLcLInPair(void *p) {
      delete ((::Pythia8::InPair*)p);
   }
   static void deleteArray_Pythia8cLcLInPair(void *p) {
      delete [] ((::Pythia8::InPair*)p);
   }
   static void destruct_Pythia8cLcLInPair(void *p) {
      typedef ::Pythia8::InPair current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::Pythia8::InPair

namespace ROOT {
   // Wrappers around operator new
   static void *new_Pythia8cLcLAlphaStrong(void *p) {
      return  p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) ::Pythia8::AlphaStrong : new ::Pythia8::AlphaStrong;
   }
   static void *newArray_Pythia8cLcLAlphaStrong(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) ::Pythia8::AlphaStrong[nElements] : new ::Pythia8::AlphaStrong[nElements];
   }
   // Wrapper around operator delete
   static void delete_Pythia8cLcLAlphaStrong(void *p) {
      delete ((::Pythia8::AlphaStrong*)p);
   }
   static void deleteArray_Pythia8cLcLAlphaStrong(void *p) {
      delete [] ((::Pythia8::AlphaStrong*)p);
   }
   static void destruct_Pythia8cLcLAlphaStrong(void *p) {
      typedef ::Pythia8::AlphaStrong current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::Pythia8::AlphaStrong

namespace ROOT {
   // Wrappers around operator new
   static void *new_Pythia8cLcLAlphaEM(void *p) {
      return  p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) ::Pythia8::AlphaEM : new ::Pythia8::AlphaEM;
   }
   static void *newArray_Pythia8cLcLAlphaEM(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) ::Pythia8::AlphaEM[nElements] : new ::Pythia8::AlphaEM[nElements];
   }
   // Wrapper around operator delete
   static void delete_Pythia8cLcLAlphaEM(void *p) {
      delete ((::Pythia8::AlphaEM*)p);
   }
   static void deleteArray_Pythia8cLcLAlphaEM(void *p) {
      delete [] ((::Pythia8::AlphaEM*)p);
   }
   static void destruct_Pythia8cLcLAlphaEM(void *p) {
      typedef ::Pythia8::AlphaEM current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::Pythia8::AlphaEM

namespace ROOT {
   // Wrappers around operator new
   static void *new_Pythia8cLcLInfo(void *p) {
      return  p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) ::Pythia8::Info : new ::Pythia8::Info;
   }
   static void *newArray_Pythia8cLcLInfo(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) ::Pythia8::Info[nElements] : new ::Pythia8::Info[nElements];
   }
   // Wrapper around operator delete
   static void delete_Pythia8cLcLInfo(void *p) {
      delete ((::Pythia8::Info*)p);
   }
   static void deleteArray_Pythia8cLcLInfo(void *p) {
      delete [] ((::Pythia8::Info*)p);
   }
   static void destruct_Pythia8cLcLInfo(void *p) {
      typedef ::Pythia8::Info current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::Pythia8::Info

namespace ROOT {
   // Wrappers around operator new
   static void *new_Pythia8cLcLRndm(void *p) {
      return  p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) ::Pythia8::Rndm : new ::Pythia8::Rndm;
   }
   static void *newArray_Pythia8cLcLRndm(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) ::Pythia8::Rndm[nElements] : new ::Pythia8::Rndm[nElements];
   }
   // Wrapper around operator delete
   static void delete_Pythia8cLcLRndm(void *p) {
      delete ((::Pythia8::Rndm*)p);
   }
   static void deleteArray_Pythia8cLcLRndm(void *p) {
      delete [] ((::Pythia8::Rndm*)p);
   }
   static void destruct_Pythia8cLcLRndm(void *p) {
      typedef ::Pythia8::Rndm current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::Pythia8::Rndm

namespace ROOT {
   // Wrapper around operator delete
   static void delete_Pythia8cLcLRndmEngine(void *p) {
      delete ((::Pythia8::RndmEngine*)p);
   }
   static void deleteArray_Pythia8cLcLRndmEngine(void *p) {
      delete [] ((::Pythia8::RndmEngine*)p);
   }
   static void destruct_Pythia8cLcLRndmEngine(void *p) {
      typedef ::Pythia8::RndmEngine current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::Pythia8::RndmEngine

namespace ROOT {
   // Wrappers around operator new
   static void *new_Pythia8cLcLSettings(void *p) {
      return  p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) ::Pythia8::Settings : new ::Pythia8::Settings;
   }
   static void *newArray_Pythia8cLcLSettings(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) ::Pythia8::Settings[nElements] : new ::Pythia8::Settings[nElements];
   }
   // Wrapper around operator delete
   static void delete_Pythia8cLcLSettings(void *p) {
      delete ((::Pythia8::Settings*)p);
   }
   static void deleteArray_Pythia8cLcLSettings(void *p) {
      delete [] ((::Pythia8::Settings*)p);
   }
   static void destruct_Pythia8cLcLSettings(void *p) {
      typedef ::Pythia8::Settings current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::Pythia8::Settings

namespace ROOT {
   // Wrapper around operator delete
   static void delete_Pythia8cLcLResonanceTop(void *p) {
      delete ((::Pythia8::ResonanceTop*)p);
   }
   static void deleteArray_Pythia8cLcLResonanceTop(void *p) {
      delete [] ((::Pythia8::ResonanceTop*)p);
   }
   static void destruct_Pythia8cLcLResonanceTop(void *p) {
      typedef ::Pythia8::ResonanceTop current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::Pythia8::ResonanceTop

namespace ROOT {
   // Wrapper around operator delete
   static void delete_Pythia8cLcLResonanceGeneric(void *p) {
      delete ((::Pythia8::ResonanceGeneric*)p);
   }
   static void deleteArray_Pythia8cLcLResonanceGeneric(void *p) {
      delete [] ((::Pythia8::ResonanceGeneric*)p);
   }
   static void destruct_Pythia8cLcLResonanceGeneric(void *p) {
      typedef ::Pythia8::ResonanceGeneric current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::Pythia8::ResonanceGeneric

namespace ROOT {
   // Wrapper around operator delete
   static void delete_Pythia8cLcLResonanceGmZ(void *p) {
      delete ((::Pythia8::ResonanceGmZ*)p);
   }
   static void deleteArray_Pythia8cLcLResonanceGmZ(void *p) {
      delete [] ((::Pythia8::ResonanceGmZ*)p);
   }
   static void destruct_Pythia8cLcLResonanceGmZ(void *p) {
      typedef ::Pythia8::ResonanceGmZ current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::Pythia8::ResonanceGmZ

namespace ROOT {
   // Wrapper around operator delete
   static void delete_Pythia8cLcLResonanceW(void *p) {
      delete ((::Pythia8::ResonanceW*)p);
   }
   static void deleteArray_Pythia8cLcLResonanceW(void *p) {
      delete [] ((::Pythia8::ResonanceW*)p);
   }
   static void destruct_Pythia8cLcLResonanceW(void *p) {
      typedef ::Pythia8::ResonanceW current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::Pythia8::ResonanceW

namespace ROOT {
   // Wrapper around operator delete
   static void delete_Pythia8cLcLResonanceFour(void *p) {
      delete ((::Pythia8::ResonanceFour*)p);
   }
   static void deleteArray_Pythia8cLcLResonanceFour(void *p) {
      delete [] ((::Pythia8::ResonanceFour*)p);
   }
   static void destruct_Pythia8cLcLResonanceFour(void *p) {
      typedef ::Pythia8::ResonanceFour current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::Pythia8::ResonanceFour

namespace ROOT {
   // Wrapper around operator delete
   static void delete_Pythia8cLcLResonanceH(void *p) {
      delete ((::Pythia8::ResonanceH*)p);
   }
   static void deleteArray_Pythia8cLcLResonanceH(void *p) {
      delete [] ((::Pythia8::ResonanceH*)p);
   }
   static void destruct_Pythia8cLcLResonanceH(void *p) {
      typedef ::Pythia8::ResonanceH current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::Pythia8::ResonanceH

namespace ROOT {
   // Wrapper around operator delete
   static void delete_Pythia8cLcLResonanceHchg(void *p) {
      delete ((::Pythia8::ResonanceHchg*)p);
   }
   static void deleteArray_Pythia8cLcLResonanceHchg(void *p) {
      delete [] ((::Pythia8::ResonanceHchg*)p);
   }
   static void destruct_Pythia8cLcLResonanceHchg(void *p) {
      typedef ::Pythia8::ResonanceHchg current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::Pythia8::ResonanceHchg

namespace ROOT {
   // Wrapper around operator delete
   static void delete_Pythia8cLcLResonanceZprime(void *p) {
      delete ((::Pythia8::ResonanceZprime*)p);
   }
   static void deleteArray_Pythia8cLcLResonanceZprime(void *p) {
      delete [] ((::Pythia8::ResonanceZprime*)p);
   }
   static void destruct_Pythia8cLcLResonanceZprime(void *p) {
      typedef ::Pythia8::ResonanceZprime current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::Pythia8::ResonanceZprime

namespace ROOT {
   // Wrapper around operator delete
   static void delete_Pythia8cLcLResonanceWprime(void *p) {
      delete ((::Pythia8::ResonanceWprime*)p);
   }
   static void deleteArray_Pythia8cLcLResonanceWprime(void *p) {
      delete [] ((::Pythia8::ResonanceWprime*)p);
   }
   static void destruct_Pythia8cLcLResonanceWprime(void *p) {
      typedef ::Pythia8::ResonanceWprime current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::Pythia8::ResonanceWprime

namespace ROOT {
   // Wrapper around operator delete
   static void delete_Pythia8cLcLResonanceRhorizontal(void *p) {
      delete ((::Pythia8::ResonanceRhorizontal*)p);
   }
   static void deleteArray_Pythia8cLcLResonanceRhorizontal(void *p) {
      delete [] ((::Pythia8::ResonanceRhorizontal*)p);
   }
   static void destruct_Pythia8cLcLResonanceRhorizontal(void *p) {
      typedef ::Pythia8::ResonanceRhorizontal current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::Pythia8::ResonanceRhorizontal

namespace ROOT {
   // Wrapper around operator delete
   static void delete_Pythia8cLcLResonanceExcited(void *p) {
      delete ((::Pythia8::ResonanceExcited*)p);
   }
   static void deleteArray_Pythia8cLcLResonanceExcited(void *p) {
      delete [] ((::Pythia8::ResonanceExcited*)p);
   }
   static void destruct_Pythia8cLcLResonanceExcited(void *p) {
      typedef ::Pythia8::ResonanceExcited current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::Pythia8::ResonanceExcited

namespace ROOT {
   // Wrapper around operator delete
   static void delete_Pythia8cLcLResonanceGraviton(void *p) {
      delete ((::Pythia8::ResonanceGraviton*)p);
   }
   static void deleteArray_Pythia8cLcLResonanceGraviton(void *p) {
      delete [] ((::Pythia8::ResonanceGraviton*)p);
   }
   static void destruct_Pythia8cLcLResonanceGraviton(void *p) {
      typedef ::Pythia8::ResonanceGraviton current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::Pythia8::ResonanceGraviton

namespace ROOT {
   // Wrapper around operator delete
   static void delete_Pythia8cLcLResonanceLeptoquark(void *p) {
      delete ((::Pythia8::ResonanceLeptoquark*)p);
   }
   static void deleteArray_Pythia8cLcLResonanceLeptoquark(void *p) {
      delete [] ((::Pythia8::ResonanceLeptoquark*)p);
   }
   static void destruct_Pythia8cLcLResonanceLeptoquark(void *p) {
      typedef ::Pythia8::ResonanceLeptoquark current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::Pythia8::ResonanceLeptoquark

namespace ROOT {
   // Wrapper around operator delete
   static void delete_Pythia8cLcLResonanceNuRight(void *p) {
      delete ((::Pythia8::ResonanceNuRight*)p);
   }
   static void deleteArray_Pythia8cLcLResonanceNuRight(void *p) {
      delete [] ((::Pythia8::ResonanceNuRight*)p);
   }
   static void destruct_Pythia8cLcLResonanceNuRight(void *p) {
      typedef ::Pythia8::ResonanceNuRight current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::Pythia8::ResonanceNuRight

namespace ROOT {
   // Wrapper around operator delete
   static void delete_Pythia8cLcLResonanceZRight(void *p) {
      delete ((::Pythia8::ResonanceZRight*)p);
   }
   static void deleteArray_Pythia8cLcLResonanceZRight(void *p) {
      delete [] ((::Pythia8::ResonanceZRight*)p);
   }
   static void destruct_Pythia8cLcLResonanceZRight(void *p) {
      typedef ::Pythia8::ResonanceZRight current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::Pythia8::ResonanceZRight

namespace ROOT {
   // Wrapper around operator delete
   static void delete_Pythia8cLcLResonanceWRight(void *p) {
      delete ((::Pythia8::ResonanceWRight*)p);
   }
   static void deleteArray_Pythia8cLcLResonanceWRight(void *p) {
      delete [] ((::Pythia8::ResonanceWRight*)p);
   }
   static void destruct_Pythia8cLcLResonanceWRight(void *p) {
      typedef ::Pythia8::ResonanceWRight current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::Pythia8::ResonanceWRight

namespace ROOT {
   // Wrapper around operator delete
   static void delete_Pythia8cLcLResonanceHchgchgLeft(void *p) {
      delete ((::Pythia8::ResonanceHchgchgLeft*)p);
   }
   static void deleteArray_Pythia8cLcLResonanceHchgchgLeft(void *p) {
      delete [] ((::Pythia8::ResonanceHchgchgLeft*)p);
   }
   static void destruct_Pythia8cLcLResonanceHchgchgLeft(void *p) {
      typedef ::Pythia8::ResonanceHchgchgLeft current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::Pythia8::ResonanceHchgchgLeft

namespace ROOT {
   // Wrapper around operator delete
   static void delete_Pythia8cLcLResonanceHchgchgRight(void *p) {
      delete ((::Pythia8::ResonanceHchgchgRight*)p);
   }
   static void deleteArray_Pythia8cLcLResonanceHchgchgRight(void *p) {
      delete [] ((::Pythia8::ResonanceHchgchgRight*)p);
   }
   static void destruct_Pythia8cLcLResonanceHchgchgRight(void *p) {
      typedef ::Pythia8::ResonanceHchgchgRight current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::Pythia8::ResonanceHchgchgRight

namespace ROOT {
   // Wrapper around operator delete
   static void delete_Pythia8cLcLSigmaProcess(void *p) {
      delete ((::Pythia8::SigmaProcess*)p);
   }
   static void deleteArray_Pythia8cLcLSigmaProcess(void *p) {
      delete [] ((::Pythia8::SigmaProcess*)p);
   }
   static void destruct_Pythia8cLcLSigmaProcess(void *p) {
      typedef ::Pythia8::SigmaProcess current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::Pythia8::SigmaProcess

namespace ROOT {
   static TClass *vectorlEstringgR_Dictionary();
   static void vectorlEstringgR_TClassManip(TClass*);
   static void *new_vectorlEstringgR(void *p = 0);
   static void *newArray_vectorlEstringgR(Long_t size, void *p);
   static void delete_vectorlEstringgR(void *p);
   static void deleteArray_vectorlEstringgR(void *p);
   static void destruct_vectorlEstringgR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const vector<string>*)
   {
      vector<string> *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(vector<string>));
      static ::ROOT::TGenericClassInfo 
         instance("vector<string>", -2, "vector", 210,
                  typeid(vector<string>), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &vectorlEstringgR_Dictionary, isa_proxy, 0,
                  sizeof(vector<string>) );
      instance.SetNew(&new_vectorlEstringgR);
      instance.SetNewArray(&newArray_vectorlEstringgR);
      instance.SetDelete(&delete_vectorlEstringgR);
      instance.SetDeleteArray(&deleteArray_vectorlEstringgR);
      instance.SetDestructor(&destruct_vectorlEstringgR);
      instance.AdoptCollectionProxyInfo(TCollectionProxyInfo::Generate(TCollectionProxyInfo::Pushback< vector<string> >()));
      return &instance;
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const vector<string>*)0x0); R__UseDummy(_R__UNIQUE_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *vectorlEstringgR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const vector<string>*)0x0)->GetClass();
      vectorlEstringgR_TClassManip(theClass);
   return theClass;
   }

   static void vectorlEstringgR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_vectorlEstringgR(void *p) {
      return  p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<string> : new vector<string>;
   }
   static void *newArray_vectorlEstringgR(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<string>[nElements] : new vector<string>[nElements];
   }
   // Wrapper around operator delete
   static void delete_vectorlEstringgR(void *p) {
      delete ((vector<string>*)p);
   }
   static void deleteArray_vectorlEstringgR(void *p) {
      delete [] ((vector<string>*)p);
   }
   static void destruct_vectorlEstringgR(void *p) {
      typedef vector<string> current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class vector<string>

namespace ROOT {
   static TClass *vectorlEpairlEintcOintgRsPgR_Dictionary();
   static void vectorlEpairlEintcOintgRsPgR_TClassManip(TClass*);
   static void *new_vectorlEpairlEintcOintgRsPgR(void *p = 0);
   static void *newArray_vectorlEpairlEintcOintgRsPgR(Long_t size, void *p);
   static void delete_vectorlEpairlEintcOintgRsPgR(void *p);
   static void deleteArray_vectorlEpairlEintcOintgRsPgR(void *p);
   static void destruct_vectorlEpairlEintcOintgRsPgR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const vector<pair<int,int> >*)
   {
      vector<pair<int,int> > *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(vector<pair<int,int> >));
      static ::ROOT::TGenericClassInfo 
         instance("vector<pair<int,int> >", -2, "vector", 210,
                  typeid(vector<pair<int,int> >), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &vectorlEpairlEintcOintgRsPgR_Dictionary, isa_proxy, 0,
                  sizeof(vector<pair<int,int> >) );
      instance.SetNew(&new_vectorlEpairlEintcOintgRsPgR);
      instance.SetNewArray(&newArray_vectorlEpairlEintcOintgRsPgR);
      instance.SetDelete(&delete_vectorlEpairlEintcOintgRsPgR);
      instance.SetDeleteArray(&deleteArray_vectorlEpairlEintcOintgRsPgR);
      instance.SetDestructor(&destruct_vectorlEpairlEintcOintgRsPgR);
      instance.AdoptCollectionProxyInfo(TCollectionProxyInfo::Generate(TCollectionProxyInfo::Pushback< vector<pair<int,int> > >()));
      return &instance;
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const vector<pair<int,int> >*)0x0); R__UseDummy(_R__UNIQUE_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *vectorlEpairlEintcOintgRsPgR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const vector<pair<int,int> >*)0x0)->GetClass();
      vectorlEpairlEintcOintgRsPgR_TClassManip(theClass);
   return theClass;
   }

   static void vectorlEpairlEintcOintgRsPgR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_vectorlEpairlEintcOintgRsPgR(void *p) {
      return  p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<pair<int,int> > : new vector<pair<int,int> >;
   }
   static void *newArray_vectorlEpairlEintcOintgRsPgR(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<pair<int,int> >[nElements] : new vector<pair<int,int> >[nElements];
   }
   // Wrapper around operator delete
   static void delete_vectorlEpairlEintcOintgRsPgR(void *p) {
      delete ((vector<pair<int,int> >*)p);
   }
   static void deleteArray_vectorlEpairlEintcOintgRsPgR(void *p) {
      delete [] ((vector<pair<int,int> >*)p);
   }
   static void destruct_vectorlEpairlEintcOintgRsPgR(void *p) {
      typedef vector<pair<int,int> > current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class vector<pair<int,int> >

namespace ROOT {
   static TClass *vectorlEintgR_Dictionary();
   static void vectorlEintgR_TClassManip(TClass*);
   static void *new_vectorlEintgR(void *p = 0);
   static void *newArray_vectorlEintgR(Long_t size, void *p);
   static void delete_vectorlEintgR(void *p);
   static void deleteArray_vectorlEintgR(void *p);
   static void destruct_vectorlEintgR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const vector<int>*)
   {
      vector<int> *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(vector<int>));
      static ::ROOT::TGenericClassInfo 
         instance("vector<int>", -2, "vector", 210,
                  typeid(vector<int>), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &vectorlEintgR_Dictionary, isa_proxy, 0,
                  sizeof(vector<int>) );
      instance.SetNew(&new_vectorlEintgR);
      instance.SetNewArray(&newArray_vectorlEintgR);
      instance.SetDelete(&delete_vectorlEintgR);
      instance.SetDeleteArray(&deleteArray_vectorlEintgR);
      instance.SetDestructor(&destruct_vectorlEintgR);
      instance.AdoptCollectionProxyInfo(TCollectionProxyInfo::Generate(TCollectionProxyInfo::Pushback< vector<int> >()));
      return &instance;
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const vector<int>*)0x0); R__UseDummy(_R__UNIQUE_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *vectorlEintgR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const vector<int>*)0x0)->GetClass();
      vectorlEintgR_TClassManip(theClass);
   return theClass;
   }

   static void vectorlEintgR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_vectorlEintgR(void *p) {
      return  p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<int> : new vector<int>;
   }
   static void *newArray_vectorlEintgR(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<int>[nElements] : new vector<int>[nElements];
   }
   // Wrapper around operator delete
   static void delete_vectorlEintgR(void *p) {
      delete ((vector<int>*)p);
   }
   static void deleteArray_vectorlEintgR(void *p) {
      delete [] ((vector<int>*)p);
   }
   static void destruct_vectorlEintgR(void *p) {
      typedef vector<int> current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class vector<int>

namespace ROOT {
   static TClass *vectorlEdoublegR_Dictionary();
   static void vectorlEdoublegR_TClassManip(TClass*);
   static void *new_vectorlEdoublegR(void *p = 0);
   static void *newArray_vectorlEdoublegR(Long_t size, void *p);
   static void delete_vectorlEdoublegR(void *p);
   static void deleteArray_vectorlEdoublegR(void *p);
   static void destruct_vectorlEdoublegR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const vector<double>*)
   {
      vector<double> *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(vector<double>));
      static ::ROOT::TGenericClassInfo 
         instance("vector<double>", -2, "vector", 210,
                  typeid(vector<double>), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &vectorlEdoublegR_Dictionary, isa_proxy, 0,
                  sizeof(vector<double>) );
      instance.SetNew(&new_vectorlEdoublegR);
      instance.SetNewArray(&newArray_vectorlEdoublegR);
      instance.SetDelete(&delete_vectorlEdoublegR);
      instance.SetDeleteArray(&deleteArray_vectorlEdoublegR);
      instance.SetDestructor(&destruct_vectorlEdoublegR);
      instance.AdoptCollectionProxyInfo(TCollectionProxyInfo::Generate(TCollectionProxyInfo::Pushback< vector<double> >()));
      return &instance;
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const vector<double>*)0x0); R__UseDummy(_R__UNIQUE_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *vectorlEdoublegR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const vector<double>*)0x0)->GetClass();
      vectorlEdoublegR_TClassManip(theClass);
   return theClass;
   }

   static void vectorlEdoublegR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_vectorlEdoublegR(void *p) {
      return  p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<double> : new vector<double>;
   }
   static void *newArray_vectorlEdoublegR(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<double>[nElements] : new vector<double>[nElements];
   }
   // Wrapper around operator delete
   static void delete_vectorlEdoublegR(void *p) {
      delete ((vector<double>*)p);
   }
   static void deleteArray_vectorlEdoublegR(void *p) {
      delete [] ((vector<double>*)p);
   }
   static void destruct_vectorlEdoublegR(void *p) {
      typedef vector<double> current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class vector<double>

namespace ROOT {
   static TClass *vectorlEPythia8cLcLVec4gR_Dictionary();
   static void vectorlEPythia8cLcLVec4gR_TClassManip(TClass*);
   static void *new_vectorlEPythia8cLcLVec4gR(void *p = 0);
   static void *newArray_vectorlEPythia8cLcLVec4gR(Long_t size, void *p);
   static void delete_vectorlEPythia8cLcLVec4gR(void *p);
   static void deleteArray_vectorlEPythia8cLcLVec4gR(void *p);
   static void destruct_vectorlEPythia8cLcLVec4gR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const vector<Pythia8::Vec4>*)
   {
      vector<Pythia8::Vec4> *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(vector<Pythia8::Vec4>));
      static ::ROOT::TGenericClassInfo 
         instance("vector<Pythia8::Vec4>", -2, "vector", 210,
                  typeid(vector<Pythia8::Vec4>), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &vectorlEPythia8cLcLVec4gR_Dictionary, isa_proxy, 0,
                  sizeof(vector<Pythia8::Vec4>) );
      instance.SetNew(&new_vectorlEPythia8cLcLVec4gR);
      instance.SetNewArray(&newArray_vectorlEPythia8cLcLVec4gR);
      instance.SetDelete(&delete_vectorlEPythia8cLcLVec4gR);
      instance.SetDeleteArray(&deleteArray_vectorlEPythia8cLcLVec4gR);
      instance.SetDestructor(&destruct_vectorlEPythia8cLcLVec4gR);
      instance.AdoptCollectionProxyInfo(TCollectionProxyInfo::Generate(TCollectionProxyInfo::Pushback< vector<Pythia8::Vec4> >()));
      return &instance;
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const vector<Pythia8::Vec4>*)0x0); R__UseDummy(_R__UNIQUE_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *vectorlEPythia8cLcLVec4gR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const vector<Pythia8::Vec4>*)0x0)->GetClass();
      vectorlEPythia8cLcLVec4gR_TClassManip(theClass);
   return theClass;
   }

   static void vectorlEPythia8cLcLVec4gR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_vectorlEPythia8cLcLVec4gR(void *p) {
      return  p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<Pythia8::Vec4> : new vector<Pythia8::Vec4>;
   }
   static void *newArray_vectorlEPythia8cLcLVec4gR(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<Pythia8::Vec4>[nElements] : new vector<Pythia8::Vec4>[nElements];
   }
   // Wrapper around operator delete
   static void delete_vectorlEPythia8cLcLVec4gR(void *p) {
      delete ((vector<Pythia8::Vec4>*)p);
   }
   static void deleteArray_vectorlEPythia8cLcLVec4gR(void *p) {
      delete [] ((vector<Pythia8::Vec4>*)p);
   }
   static void destruct_vectorlEPythia8cLcLVec4gR(void *p) {
      typedef vector<Pythia8::Vec4> current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class vector<Pythia8::Vec4>

namespace ROOT {
   static TClass *vectorlEPythia8cLcLSigmaProcessmUgR_Dictionary();
   static void vectorlEPythia8cLcLSigmaProcessmUgR_TClassManip(TClass*);
   static void *new_vectorlEPythia8cLcLSigmaProcessmUgR(void *p = 0);
   static void *newArray_vectorlEPythia8cLcLSigmaProcessmUgR(Long_t size, void *p);
   static void delete_vectorlEPythia8cLcLSigmaProcessmUgR(void *p);
   static void deleteArray_vectorlEPythia8cLcLSigmaProcessmUgR(void *p);
   static void destruct_vectorlEPythia8cLcLSigmaProcessmUgR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const vector<Pythia8::SigmaProcess*>*)
   {
      vector<Pythia8::SigmaProcess*> *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(vector<Pythia8::SigmaProcess*>));
      static ::ROOT::TGenericClassInfo 
         instance("vector<Pythia8::SigmaProcess*>", -2, "vector", 210,
                  typeid(vector<Pythia8::SigmaProcess*>), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &vectorlEPythia8cLcLSigmaProcessmUgR_Dictionary, isa_proxy, 0,
                  sizeof(vector<Pythia8::SigmaProcess*>) );
      instance.SetNew(&new_vectorlEPythia8cLcLSigmaProcessmUgR);
      instance.SetNewArray(&newArray_vectorlEPythia8cLcLSigmaProcessmUgR);
      instance.SetDelete(&delete_vectorlEPythia8cLcLSigmaProcessmUgR);
      instance.SetDeleteArray(&deleteArray_vectorlEPythia8cLcLSigmaProcessmUgR);
      instance.SetDestructor(&destruct_vectorlEPythia8cLcLSigmaProcessmUgR);
      instance.AdoptCollectionProxyInfo(TCollectionProxyInfo::Generate(TCollectionProxyInfo::Pushback< vector<Pythia8::SigmaProcess*> >()));
      return &instance;
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const vector<Pythia8::SigmaProcess*>*)0x0); R__UseDummy(_R__UNIQUE_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *vectorlEPythia8cLcLSigmaProcessmUgR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const vector<Pythia8::SigmaProcess*>*)0x0)->GetClass();
      vectorlEPythia8cLcLSigmaProcessmUgR_TClassManip(theClass);
   return theClass;
   }

   static void vectorlEPythia8cLcLSigmaProcessmUgR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_vectorlEPythia8cLcLSigmaProcessmUgR(void *p) {
      return  p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<Pythia8::SigmaProcess*> : new vector<Pythia8::SigmaProcess*>;
   }
   static void *newArray_vectorlEPythia8cLcLSigmaProcessmUgR(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<Pythia8::SigmaProcess*>[nElements] : new vector<Pythia8::SigmaProcess*>[nElements];
   }
   // Wrapper around operator delete
   static void delete_vectorlEPythia8cLcLSigmaProcessmUgR(void *p) {
      delete ((vector<Pythia8::SigmaProcess*>*)p);
   }
   static void deleteArray_vectorlEPythia8cLcLSigmaProcessmUgR(void *p) {
      delete [] ((vector<Pythia8::SigmaProcess*>*)p);
   }
   static void destruct_vectorlEPythia8cLcLSigmaProcessmUgR(void *p) {
      typedef vector<Pythia8::SigmaProcess*> current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class vector<Pythia8::SigmaProcess*>

namespace ROOT {
   static TClass *vectorlEPythia8cLcLResonanceWidthsmUgR_Dictionary();
   static void vectorlEPythia8cLcLResonanceWidthsmUgR_TClassManip(TClass*);
   static void *new_vectorlEPythia8cLcLResonanceWidthsmUgR(void *p = 0);
   static void *newArray_vectorlEPythia8cLcLResonanceWidthsmUgR(Long_t size, void *p);
   static void delete_vectorlEPythia8cLcLResonanceWidthsmUgR(void *p);
   static void deleteArray_vectorlEPythia8cLcLResonanceWidthsmUgR(void *p);
   static void destruct_vectorlEPythia8cLcLResonanceWidthsmUgR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const vector<Pythia8::ResonanceWidths*>*)
   {
      vector<Pythia8::ResonanceWidths*> *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(vector<Pythia8::ResonanceWidths*>));
      static ::ROOT::TGenericClassInfo 
         instance("vector<Pythia8::ResonanceWidths*>", -2, "vector", 210,
                  typeid(vector<Pythia8::ResonanceWidths*>), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &vectorlEPythia8cLcLResonanceWidthsmUgR_Dictionary, isa_proxy, 0,
                  sizeof(vector<Pythia8::ResonanceWidths*>) );
      instance.SetNew(&new_vectorlEPythia8cLcLResonanceWidthsmUgR);
      instance.SetNewArray(&newArray_vectorlEPythia8cLcLResonanceWidthsmUgR);
      instance.SetDelete(&delete_vectorlEPythia8cLcLResonanceWidthsmUgR);
      instance.SetDeleteArray(&deleteArray_vectorlEPythia8cLcLResonanceWidthsmUgR);
      instance.SetDestructor(&destruct_vectorlEPythia8cLcLResonanceWidthsmUgR);
      instance.AdoptCollectionProxyInfo(TCollectionProxyInfo::Generate(TCollectionProxyInfo::Pushback< vector<Pythia8::ResonanceWidths*> >()));
      return &instance;
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const vector<Pythia8::ResonanceWidths*>*)0x0); R__UseDummy(_R__UNIQUE_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *vectorlEPythia8cLcLResonanceWidthsmUgR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const vector<Pythia8::ResonanceWidths*>*)0x0)->GetClass();
      vectorlEPythia8cLcLResonanceWidthsmUgR_TClassManip(theClass);
   return theClass;
   }

   static void vectorlEPythia8cLcLResonanceWidthsmUgR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_vectorlEPythia8cLcLResonanceWidthsmUgR(void *p) {
      return  p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<Pythia8::ResonanceWidths*> : new vector<Pythia8::ResonanceWidths*>;
   }
   static void *newArray_vectorlEPythia8cLcLResonanceWidthsmUgR(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<Pythia8::ResonanceWidths*>[nElements] : new vector<Pythia8::ResonanceWidths*>[nElements];
   }
   // Wrapper around operator delete
   static void delete_vectorlEPythia8cLcLResonanceWidthsmUgR(void *p) {
      delete ((vector<Pythia8::ResonanceWidths*>*)p);
   }
   static void deleteArray_vectorlEPythia8cLcLResonanceWidthsmUgR(void *p) {
      delete [] ((vector<Pythia8::ResonanceWidths*>*)p);
   }
   static void destruct_vectorlEPythia8cLcLResonanceWidthsmUgR(void *p) {
      typedef vector<Pythia8::ResonanceWidths*> current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class vector<Pythia8::ResonanceWidths*>

namespace ROOT {
   static TClass *vectorlEPythia8cLcLPhaseSpacemUgR_Dictionary();
   static void vectorlEPythia8cLcLPhaseSpacemUgR_TClassManip(TClass*);
   static void *new_vectorlEPythia8cLcLPhaseSpacemUgR(void *p = 0);
   static void *newArray_vectorlEPythia8cLcLPhaseSpacemUgR(Long_t size, void *p);
   static void delete_vectorlEPythia8cLcLPhaseSpacemUgR(void *p);
   static void deleteArray_vectorlEPythia8cLcLPhaseSpacemUgR(void *p);
   static void destruct_vectorlEPythia8cLcLPhaseSpacemUgR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const vector<Pythia8::PhaseSpace*>*)
   {
      vector<Pythia8::PhaseSpace*> *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(vector<Pythia8::PhaseSpace*>));
      static ::ROOT::TGenericClassInfo 
         instance("vector<Pythia8::PhaseSpace*>", -2, "vector", 210,
                  typeid(vector<Pythia8::PhaseSpace*>), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &vectorlEPythia8cLcLPhaseSpacemUgR_Dictionary, isa_proxy, 0,
                  sizeof(vector<Pythia8::PhaseSpace*>) );
      instance.SetNew(&new_vectorlEPythia8cLcLPhaseSpacemUgR);
      instance.SetNewArray(&newArray_vectorlEPythia8cLcLPhaseSpacemUgR);
      instance.SetDelete(&delete_vectorlEPythia8cLcLPhaseSpacemUgR);
      instance.SetDeleteArray(&deleteArray_vectorlEPythia8cLcLPhaseSpacemUgR);
      instance.SetDestructor(&destruct_vectorlEPythia8cLcLPhaseSpacemUgR);
      instance.AdoptCollectionProxyInfo(TCollectionProxyInfo::Generate(TCollectionProxyInfo::Pushback< vector<Pythia8::PhaseSpace*> >()));
      return &instance;
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const vector<Pythia8::PhaseSpace*>*)0x0); R__UseDummy(_R__UNIQUE_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *vectorlEPythia8cLcLPhaseSpacemUgR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const vector<Pythia8::PhaseSpace*>*)0x0)->GetClass();
      vectorlEPythia8cLcLPhaseSpacemUgR_TClassManip(theClass);
   return theClass;
   }

   static void vectorlEPythia8cLcLPhaseSpacemUgR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_vectorlEPythia8cLcLPhaseSpacemUgR(void *p) {
      return  p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<Pythia8::PhaseSpace*> : new vector<Pythia8::PhaseSpace*>;
   }
   static void *newArray_vectorlEPythia8cLcLPhaseSpacemUgR(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<Pythia8::PhaseSpace*>[nElements] : new vector<Pythia8::PhaseSpace*>[nElements];
   }
   // Wrapper around operator delete
   static void delete_vectorlEPythia8cLcLPhaseSpacemUgR(void *p) {
      delete ((vector<Pythia8::PhaseSpace*>*)p);
   }
   static void deleteArray_vectorlEPythia8cLcLPhaseSpacemUgR(void *p) {
      delete [] ((vector<Pythia8::PhaseSpace*>*)p);
   }
   static void destruct_vectorlEPythia8cLcLPhaseSpacemUgR(void *p) {
      typedef vector<Pythia8::PhaseSpace*> current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class vector<Pythia8::PhaseSpace*>

namespace ROOT {
   static TClass *vectorlEPythia8cLcLParticlegR_Dictionary();
   static void vectorlEPythia8cLcLParticlegR_TClassManip(TClass*);
   static void *new_vectorlEPythia8cLcLParticlegR(void *p = 0);
   static void *newArray_vectorlEPythia8cLcLParticlegR(Long_t size, void *p);
   static void delete_vectorlEPythia8cLcLParticlegR(void *p);
   static void deleteArray_vectorlEPythia8cLcLParticlegR(void *p);
   static void destruct_vectorlEPythia8cLcLParticlegR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const vector<Pythia8::Particle>*)
   {
      vector<Pythia8::Particle> *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(vector<Pythia8::Particle>));
      static ::ROOT::TGenericClassInfo 
         instance("vector<Pythia8::Particle>", -2, "vector", 210,
                  typeid(vector<Pythia8::Particle>), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &vectorlEPythia8cLcLParticlegR_Dictionary, isa_proxy, 0,
                  sizeof(vector<Pythia8::Particle>) );
      instance.SetNew(&new_vectorlEPythia8cLcLParticlegR);
      instance.SetNewArray(&newArray_vectorlEPythia8cLcLParticlegR);
      instance.SetDelete(&delete_vectorlEPythia8cLcLParticlegR);
      instance.SetDeleteArray(&deleteArray_vectorlEPythia8cLcLParticlegR);
      instance.SetDestructor(&destruct_vectorlEPythia8cLcLParticlegR);
      instance.AdoptCollectionProxyInfo(TCollectionProxyInfo::Generate(TCollectionProxyInfo::Pushback< vector<Pythia8::Particle> >()));
      return &instance;
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const vector<Pythia8::Particle>*)0x0); R__UseDummy(_R__UNIQUE_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *vectorlEPythia8cLcLParticlegR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const vector<Pythia8::Particle>*)0x0)->GetClass();
      vectorlEPythia8cLcLParticlegR_TClassManip(theClass);
   return theClass;
   }

   static void vectorlEPythia8cLcLParticlegR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_vectorlEPythia8cLcLParticlegR(void *p) {
      return  p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<Pythia8::Particle> : new vector<Pythia8::Particle>;
   }
   static void *newArray_vectorlEPythia8cLcLParticlegR(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<Pythia8::Particle>[nElements] : new vector<Pythia8::Particle>[nElements];
   }
   // Wrapper around operator delete
   static void delete_vectorlEPythia8cLcLParticlegR(void *p) {
      delete ((vector<Pythia8::Particle>*)p);
   }
   static void deleteArray_vectorlEPythia8cLcLParticlegR(void *p) {
      delete [] ((vector<Pythia8::Particle>*)p);
   }
   static void destruct_vectorlEPythia8cLcLParticlegR(void *p) {
      typedef vector<Pythia8::Particle> current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class vector<Pythia8::Particle>

namespace ROOT {
   static TClass *vectorlEPythia8cLcLLHAgeneratorgR_Dictionary();
   static void vectorlEPythia8cLcLLHAgeneratorgR_TClassManip(TClass*);
   static void *new_vectorlEPythia8cLcLLHAgeneratorgR(void *p = 0);
   static void *newArray_vectorlEPythia8cLcLLHAgeneratorgR(Long_t size, void *p);
   static void delete_vectorlEPythia8cLcLLHAgeneratorgR(void *p);
   static void deleteArray_vectorlEPythia8cLcLLHAgeneratorgR(void *p);
   static void destruct_vectorlEPythia8cLcLLHAgeneratorgR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const vector<Pythia8::LHAgenerator>*)
   {
      vector<Pythia8::LHAgenerator> *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(vector<Pythia8::LHAgenerator>));
      static ::ROOT::TGenericClassInfo 
         instance("vector<Pythia8::LHAgenerator>", -2, "vector", 210,
                  typeid(vector<Pythia8::LHAgenerator>), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &vectorlEPythia8cLcLLHAgeneratorgR_Dictionary, isa_proxy, 0,
                  sizeof(vector<Pythia8::LHAgenerator>) );
      instance.SetNew(&new_vectorlEPythia8cLcLLHAgeneratorgR);
      instance.SetNewArray(&newArray_vectorlEPythia8cLcLLHAgeneratorgR);
      instance.SetDelete(&delete_vectorlEPythia8cLcLLHAgeneratorgR);
      instance.SetDeleteArray(&deleteArray_vectorlEPythia8cLcLLHAgeneratorgR);
      instance.SetDestructor(&destruct_vectorlEPythia8cLcLLHAgeneratorgR);
      instance.AdoptCollectionProxyInfo(TCollectionProxyInfo::Generate(TCollectionProxyInfo::Pushback< vector<Pythia8::LHAgenerator> >()));
      return &instance;
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const vector<Pythia8::LHAgenerator>*)0x0); R__UseDummy(_R__UNIQUE_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *vectorlEPythia8cLcLLHAgeneratorgR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const vector<Pythia8::LHAgenerator>*)0x0)->GetClass();
      vectorlEPythia8cLcLLHAgeneratorgR_TClassManip(theClass);
   return theClass;
   }

   static void vectorlEPythia8cLcLLHAgeneratorgR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_vectorlEPythia8cLcLLHAgeneratorgR(void *p) {
      return  p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<Pythia8::LHAgenerator> : new vector<Pythia8::LHAgenerator>;
   }
   static void *newArray_vectorlEPythia8cLcLLHAgeneratorgR(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<Pythia8::LHAgenerator>[nElements] : new vector<Pythia8::LHAgenerator>[nElements];
   }
   // Wrapper around operator delete
   static void delete_vectorlEPythia8cLcLLHAgeneratorgR(void *p) {
      delete ((vector<Pythia8::LHAgenerator>*)p);
   }
   static void deleteArray_vectorlEPythia8cLcLLHAgeneratorgR(void *p) {
      delete [] ((vector<Pythia8::LHAgenerator>*)p);
   }
   static void destruct_vectorlEPythia8cLcLLHAgeneratorgR(void *p) {
      typedef vector<Pythia8::LHAgenerator> current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class vector<Pythia8::LHAgenerator>

namespace ROOT {
   static TClass *vectorlEPythia8cLcLJunctiongR_Dictionary();
   static void vectorlEPythia8cLcLJunctiongR_TClassManip(TClass*);
   static void *new_vectorlEPythia8cLcLJunctiongR(void *p = 0);
   static void *newArray_vectorlEPythia8cLcLJunctiongR(Long_t size, void *p);
   static void delete_vectorlEPythia8cLcLJunctiongR(void *p);
   static void deleteArray_vectorlEPythia8cLcLJunctiongR(void *p);
   static void destruct_vectorlEPythia8cLcLJunctiongR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const vector<Pythia8::Junction>*)
   {
      vector<Pythia8::Junction> *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(vector<Pythia8::Junction>));
      static ::ROOT::TGenericClassInfo 
         instance("vector<Pythia8::Junction>", -2, "vector", 210,
                  typeid(vector<Pythia8::Junction>), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &vectorlEPythia8cLcLJunctiongR_Dictionary, isa_proxy, 0,
                  sizeof(vector<Pythia8::Junction>) );
      instance.SetNew(&new_vectorlEPythia8cLcLJunctiongR);
      instance.SetNewArray(&newArray_vectorlEPythia8cLcLJunctiongR);
      instance.SetDelete(&delete_vectorlEPythia8cLcLJunctiongR);
      instance.SetDeleteArray(&deleteArray_vectorlEPythia8cLcLJunctiongR);
      instance.SetDestructor(&destruct_vectorlEPythia8cLcLJunctiongR);
      instance.AdoptCollectionProxyInfo(TCollectionProxyInfo::Generate(TCollectionProxyInfo::Pushback< vector<Pythia8::Junction> >()));
      return &instance;
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const vector<Pythia8::Junction>*)0x0); R__UseDummy(_R__UNIQUE_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *vectorlEPythia8cLcLJunctiongR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const vector<Pythia8::Junction>*)0x0)->GetClass();
      vectorlEPythia8cLcLJunctiongR_TClassManip(theClass);
   return theClass;
   }

   static void vectorlEPythia8cLcLJunctiongR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_vectorlEPythia8cLcLJunctiongR(void *p) {
      return  p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<Pythia8::Junction> : new vector<Pythia8::Junction>;
   }
   static void *newArray_vectorlEPythia8cLcLJunctiongR(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<Pythia8::Junction>[nElements] : new vector<Pythia8::Junction>[nElements];
   }
   // Wrapper around operator delete
   static void delete_vectorlEPythia8cLcLJunctiongR(void *p) {
      delete ((vector<Pythia8::Junction>*)p);
   }
   static void deleteArray_vectorlEPythia8cLcLJunctiongR(void *p) {
      delete [] ((vector<Pythia8::Junction>*)p);
   }
   static void destruct_vectorlEPythia8cLcLJunctiongR(void *p) {
      typedef vector<Pythia8::Junction> current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class vector<Pythia8::Junction>

namespace ROOT {
   static TClass *vectorlEPythia8cLcLInPairgR_Dictionary();
   static void vectorlEPythia8cLcLInPairgR_TClassManip(TClass*);
   static void *new_vectorlEPythia8cLcLInPairgR(void *p = 0);
   static void *newArray_vectorlEPythia8cLcLInPairgR(Long_t size, void *p);
   static void delete_vectorlEPythia8cLcLInPairgR(void *p);
   static void deleteArray_vectorlEPythia8cLcLInPairgR(void *p);
   static void destruct_vectorlEPythia8cLcLInPairgR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const vector<Pythia8::InPair>*)
   {
      vector<Pythia8::InPair> *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(vector<Pythia8::InPair>));
      static ::ROOT::TGenericClassInfo 
         instance("vector<Pythia8::InPair>", -2, "vector", 210,
                  typeid(vector<Pythia8::InPair>), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &vectorlEPythia8cLcLInPairgR_Dictionary, isa_proxy, 0,
                  sizeof(vector<Pythia8::InPair>) );
      instance.SetNew(&new_vectorlEPythia8cLcLInPairgR);
      instance.SetNewArray(&newArray_vectorlEPythia8cLcLInPairgR);
      instance.SetDelete(&delete_vectorlEPythia8cLcLInPairgR);
      instance.SetDeleteArray(&deleteArray_vectorlEPythia8cLcLInPairgR);
      instance.SetDestructor(&destruct_vectorlEPythia8cLcLInPairgR);
      instance.AdoptCollectionProxyInfo(TCollectionProxyInfo::Generate(TCollectionProxyInfo::Pushback< vector<Pythia8::InPair> >()));
      return &instance;
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const vector<Pythia8::InPair>*)0x0); R__UseDummy(_R__UNIQUE_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *vectorlEPythia8cLcLInPairgR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const vector<Pythia8::InPair>*)0x0)->GetClass();
      vectorlEPythia8cLcLInPairgR_TClassManip(theClass);
   return theClass;
   }

   static void vectorlEPythia8cLcLInPairgR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_vectorlEPythia8cLcLInPairgR(void *p) {
      return  p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<Pythia8::InPair> : new vector<Pythia8::InPair>;
   }
   static void *newArray_vectorlEPythia8cLcLInPairgR(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<Pythia8::InPair>[nElements] : new vector<Pythia8::InPair>[nElements];
   }
   // Wrapper around operator delete
   static void delete_vectorlEPythia8cLcLInPairgR(void *p) {
      delete ((vector<Pythia8::InPair>*)p);
   }
   static void deleteArray_vectorlEPythia8cLcLInPairgR(void *p) {
      delete [] ((vector<Pythia8::InPair>*)p);
   }
   static void destruct_vectorlEPythia8cLcLInPairgR(void *p) {
      typedef vector<Pythia8::InPair> current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class vector<Pythia8::InPair>

namespace ROOT {
   static TClass *vectorlEPythia8cLcLInBeamgR_Dictionary();
   static void vectorlEPythia8cLcLInBeamgR_TClassManip(TClass*);
   static void *new_vectorlEPythia8cLcLInBeamgR(void *p = 0);
   static void *newArray_vectorlEPythia8cLcLInBeamgR(Long_t size, void *p);
   static void delete_vectorlEPythia8cLcLInBeamgR(void *p);
   static void deleteArray_vectorlEPythia8cLcLInBeamgR(void *p);
   static void destruct_vectorlEPythia8cLcLInBeamgR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const vector<Pythia8::InBeam>*)
   {
      vector<Pythia8::InBeam> *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(vector<Pythia8::InBeam>));
      static ::ROOT::TGenericClassInfo 
         instance("vector<Pythia8::InBeam>", -2, "vector", 210,
                  typeid(vector<Pythia8::InBeam>), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &vectorlEPythia8cLcLInBeamgR_Dictionary, isa_proxy, 0,
                  sizeof(vector<Pythia8::InBeam>) );
      instance.SetNew(&new_vectorlEPythia8cLcLInBeamgR);
      instance.SetNewArray(&newArray_vectorlEPythia8cLcLInBeamgR);
      instance.SetDelete(&delete_vectorlEPythia8cLcLInBeamgR);
      instance.SetDeleteArray(&deleteArray_vectorlEPythia8cLcLInBeamgR);
      instance.SetDestructor(&destruct_vectorlEPythia8cLcLInBeamgR);
      instance.AdoptCollectionProxyInfo(TCollectionProxyInfo::Generate(TCollectionProxyInfo::Pushback< vector<Pythia8::InBeam> >()));
      return &instance;
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const vector<Pythia8::InBeam>*)0x0); R__UseDummy(_R__UNIQUE_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *vectorlEPythia8cLcLInBeamgR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const vector<Pythia8::InBeam>*)0x0)->GetClass();
      vectorlEPythia8cLcLInBeamgR_TClassManip(theClass);
   return theClass;
   }

   static void vectorlEPythia8cLcLInBeamgR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_vectorlEPythia8cLcLInBeamgR(void *p) {
      return  p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<Pythia8::InBeam> : new vector<Pythia8::InBeam>;
   }
   static void *newArray_vectorlEPythia8cLcLInBeamgR(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<Pythia8::InBeam>[nElements] : new vector<Pythia8::InBeam>[nElements];
   }
   // Wrapper around operator delete
   static void delete_vectorlEPythia8cLcLInBeamgR(void *p) {
      delete ((vector<Pythia8::InBeam>*)p);
   }
   static void deleteArray_vectorlEPythia8cLcLInBeamgR(void *p) {
      delete [] ((vector<Pythia8::InBeam>*)p);
   }
   static void destruct_vectorlEPythia8cLcLInBeamgR(void *p) {
      typedef vector<Pythia8::InBeam> current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class vector<Pythia8::InBeam>

namespace ROOT {
   static TClass *vectorlEPythia8cLcLDecayChannelgR_Dictionary();
   static void vectorlEPythia8cLcLDecayChannelgR_TClassManip(TClass*);
   static void *new_vectorlEPythia8cLcLDecayChannelgR(void *p = 0);
   static void *newArray_vectorlEPythia8cLcLDecayChannelgR(Long_t size, void *p);
   static void delete_vectorlEPythia8cLcLDecayChannelgR(void *p);
   static void deleteArray_vectorlEPythia8cLcLDecayChannelgR(void *p);
   static void destruct_vectorlEPythia8cLcLDecayChannelgR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const vector<Pythia8::DecayChannel>*)
   {
      vector<Pythia8::DecayChannel> *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(vector<Pythia8::DecayChannel>));
      static ::ROOT::TGenericClassInfo 
         instance("vector<Pythia8::DecayChannel>", -2, "vector", 210,
                  typeid(vector<Pythia8::DecayChannel>), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &vectorlEPythia8cLcLDecayChannelgR_Dictionary, isa_proxy, 0,
                  sizeof(vector<Pythia8::DecayChannel>) );
      instance.SetNew(&new_vectorlEPythia8cLcLDecayChannelgR);
      instance.SetNewArray(&newArray_vectorlEPythia8cLcLDecayChannelgR);
      instance.SetDelete(&delete_vectorlEPythia8cLcLDecayChannelgR);
      instance.SetDeleteArray(&deleteArray_vectorlEPythia8cLcLDecayChannelgR);
      instance.SetDestructor(&destruct_vectorlEPythia8cLcLDecayChannelgR);
      instance.AdoptCollectionProxyInfo(TCollectionProxyInfo::Generate(TCollectionProxyInfo::Pushback< vector<Pythia8::DecayChannel> >()));
      return &instance;
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const vector<Pythia8::DecayChannel>*)0x0); R__UseDummy(_R__UNIQUE_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *vectorlEPythia8cLcLDecayChannelgR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const vector<Pythia8::DecayChannel>*)0x0)->GetClass();
      vectorlEPythia8cLcLDecayChannelgR_TClassManip(theClass);
   return theClass;
   }

   static void vectorlEPythia8cLcLDecayChannelgR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_vectorlEPythia8cLcLDecayChannelgR(void *p) {
      return  p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<Pythia8::DecayChannel> : new vector<Pythia8::DecayChannel>;
   }
   static void *newArray_vectorlEPythia8cLcLDecayChannelgR(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<Pythia8::DecayChannel>[nElements] : new vector<Pythia8::DecayChannel>[nElements];
   }
   // Wrapper around operator delete
   static void delete_vectorlEPythia8cLcLDecayChannelgR(void *p) {
      delete ((vector<Pythia8::DecayChannel>*)p);
   }
   static void deleteArray_vectorlEPythia8cLcLDecayChannelgR(void *p) {
      delete [] ((vector<Pythia8::DecayChannel>*)p);
   }
   static void destruct_vectorlEPythia8cLcLDecayChannelgR(void *p) {
      typedef vector<Pythia8::DecayChannel> current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class vector<Pythia8::DecayChannel>

namespace ROOT {
   static TClass *maplEstringcOstringgR_Dictionary();
   static void maplEstringcOstringgR_TClassManip(TClass*);
   static void *new_maplEstringcOstringgR(void *p = 0);
   static void *newArray_maplEstringcOstringgR(Long_t size, void *p);
   static void delete_maplEstringcOstringgR(void *p);
   static void deleteArray_maplEstringcOstringgR(void *p);
   static void destruct_maplEstringcOstringgR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const map<string,string>*)
   {
      map<string,string> *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(map<string,string>));
      static ::ROOT::TGenericClassInfo 
         instance("map<string,string>", -2, "map", 96,
                  typeid(map<string,string>), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &maplEstringcOstringgR_Dictionary, isa_proxy, 0,
                  sizeof(map<string,string>) );
      instance.SetNew(&new_maplEstringcOstringgR);
      instance.SetNewArray(&newArray_maplEstringcOstringgR);
      instance.SetDelete(&delete_maplEstringcOstringgR);
      instance.SetDeleteArray(&deleteArray_maplEstringcOstringgR);
      instance.SetDestructor(&destruct_maplEstringcOstringgR);
      instance.AdoptCollectionProxyInfo(TCollectionProxyInfo::Generate(TCollectionProxyInfo::MapInsert< map<string,string> >()));
      return &instance;
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const map<string,string>*)0x0); R__UseDummy(_R__UNIQUE_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *maplEstringcOstringgR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const map<string,string>*)0x0)->GetClass();
      maplEstringcOstringgR_TClassManip(theClass);
   return theClass;
   }

   static void maplEstringcOstringgR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_maplEstringcOstringgR(void *p) {
      return  p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) map<string,string> : new map<string,string>;
   }
   static void *newArray_maplEstringcOstringgR(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) map<string,string>[nElements] : new map<string,string>[nElements];
   }
   // Wrapper around operator delete
   static void delete_maplEstringcOstringgR(void *p) {
      delete ((map<string,string>*)p);
   }
   static void deleteArray_maplEstringcOstringgR(void *p) {
      delete [] ((map<string,string>*)p);
   }
   static void destruct_maplEstringcOstringgR(void *p) {
      typedef map<string,string> current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class map<string,string>

namespace ROOT {
   static TClass *maplEstringcOpairlEvoidmUcOintgRsPgR_Dictionary();
   static void maplEstringcOpairlEvoidmUcOintgRsPgR_TClassManip(TClass*);
   static void *new_maplEstringcOpairlEvoidmUcOintgRsPgR(void *p = 0);
   static void *newArray_maplEstringcOpairlEvoidmUcOintgRsPgR(Long_t size, void *p);
   static void delete_maplEstringcOpairlEvoidmUcOintgRsPgR(void *p);
   static void deleteArray_maplEstringcOpairlEvoidmUcOintgRsPgR(void *p);
   static void destruct_maplEstringcOpairlEvoidmUcOintgRsPgR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const map<string,pair<void*,int> >*)
   {
      map<string,pair<void*,int> > *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(map<string,pair<void*,int> >));
      static ::ROOT::TGenericClassInfo 
         instance("map<string,pair<void*,int> >", -2, "map", 96,
                  typeid(map<string,pair<void*,int> >), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &maplEstringcOpairlEvoidmUcOintgRsPgR_Dictionary, isa_proxy, 0,
                  sizeof(map<string,pair<void*,int> >) );
      instance.SetNew(&new_maplEstringcOpairlEvoidmUcOintgRsPgR);
      instance.SetNewArray(&newArray_maplEstringcOpairlEvoidmUcOintgRsPgR);
      instance.SetDelete(&delete_maplEstringcOpairlEvoidmUcOintgRsPgR);
      instance.SetDeleteArray(&deleteArray_maplEstringcOpairlEvoidmUcOintgRsPgR);
      instance.SetDestructor(&destruct_maplEstringcOpairlEvoidmUcOintgRsPgR);
      instance.AdoptCollectionProxyInfo(TCollectionProxyInfo::Generate(TCollectionProxyInfo::MapInsert< map<string,pair<void*,int> > >()));
      return &instance;
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const map<string,pair<void*,int> >*)0x0); R__UseDummy(_R__UNIQUE_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *maplEstringcOpairlEvoidmUcOintgRsPgR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const map<string,pair<void*,int> >*)0x0)->GetClass();
      maplEstringcOpairlEvoidmUcOintgRsPgR_TClassManip(theClass);
   return theClass;
   }

   static void maplEstringcOpairlEvoidmUcOintgRsPgR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_maplEstringcOpairlEvoidmUcOintgRsPgR(void *p) {
      return  p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) map<string,pair<void*,int> > : new map<string,pair<void*,int> >;
   }
   static void *newArray_maplEstringcOpairlEvoidmUcOintgRsPgR(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) map<string,pair<void*,int> >[nElements] : new map<string,pair<void*,int> >[nElements];
   }
   // Wrapper around operator delete
   static void delete_maplEstringcOpairlEvoidmUcOintgRsPgR(void *p) {
      delete ((map<string,pair<void*,int> >*)p);
   }
   static void deleteArray_maplEstringcOpairlEvoidmUcOintgRsPgR(void *p) {
      delete [] ((map<string,pair<void*,int> >*)p);
   }
   static void destruct_maplEstringcOpairlEvoidmUcOintgRsPgR(void *p) {
      typedef map<string,pair<void*,int> > current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class map<string,pair<void*,int> >

namespace ROOT {
   static TClass *maplEstringcOintgR_Dictionary();
   static void maplEstringcOintgR_TClassManip(TClass*);
   static void *new_maplEstringcOintgR(void *p = 0);
   static void *newArray_maplEstringcOintgR(Long_t size, void *p);
   static void delete_maplEstringcOintgR(void *p);
   static void deleteArray_maplEstringcOintgR(void *p);
   static void destruct_maplEstringcOintgR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const map<string,int>*)
   {
      map<string,int> *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(map<string,int>));
      static ::ROOT::TGenericClassInfo 
         instance("map<string,int>", -2, "map", 96,
                  typeid(map<string,int>), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &maplEstringcOintgR_Dictionary, isa_proxy, 0,
                  sizeof(map<string,int>) );
      instance.SetNew(&new_maplEstringcOintgR);
      instance.SetNewArray(&newArray_maplEstringcOintgR);
      instance.SetDelete(&delete_maplEstringcOintgR);
      instance.SetDeleteArray(&deleteArray_maplEstringcOintgR);
      instance.SetDestructor(&destruct_maplEstringcOintgR);
      instance.AdoptCollectionProxyInfo(TCollectionProxyInfo::Generate(TCollectionProxyInfo::MapInsert< map<string,int> >()));
      return &instance;
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const map<string,int>*)0x0); R__UseDummy(_R__UNIQUE_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *maplEstringcOintgR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const map<string,int>*)0x0)->GetClass();
      maplEstringcOintgR_TClassManip(theClass);
   return theClass;
   }

   static void maplEstringcOintgR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_maplEstringcOintgR(void *p) {
      return  p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) map<string,int> : new map<string,int>;
   }
   static void *newArray_maplEstringcOintgR(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) map<string,int>[nElements] : new map<string,int>[nElements];
   }
   // Wrapper around operator delete
   static void delete_maplEstringcOintgR(void *p) {
      delete ((map<string,int>*)p);
   }
   static void deleteArray_maplEstringcOintgR(void *p) {
      delete [] ((map<string,int>*)p);
   }
   static void destruct_maplEstringcOintgR(void *p) {
      typedef map<string,int> current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class map<string,int>

namespace ROOT {
   static TClass *maplEstringcOdoublegR_Dictionary();
   static void maplEstringcOdoublegR_TClassManip(TClass*);
   static void *new_maplEstringcOdoublegR(void *p = 0);
   static void *newArray_maplEstringcOdoublegR(Long_t size, void *p);
   static void delete_maplEstringcOdoublegR(void *p);
   static void deleteArray_maplEstringcOdoublegR(void *p);
   static void destruct_maplEstringcOdoublegR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const map<string,double>*)
   {
      map<string,double> *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(map<string,double>));
      static ::ROOT::TGenericClassInfo 
         instance("map<string,double>", -2, "map", 96,
                  typeid(map<string,double>), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &maplEstringcOdoublegR_Dictionary, isa_proxy, 0,
                  sizeof(map<string,double>) );
      instance.SetNew(&new_maplEstringcOdoublegR);
      instance.SetNewArray(&newArray_maplEstringcOdoublegR);
      instance.SetDelete(&delete_maplEstringcOdoublegR);
      instance.SetDeleteArray(&deleteArray_maplEstringcOdoublegR);
      instance.SetDestructor(&destruct_maplEstringcOdoublegR);
      instance.AdoptCollectionProxyInfo(TCollectionProxyInfo::Generate(TCollectionProxyInfo::MapInsert< map<string,double> >()));
      return &instance;
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const map<string,double>*)0x0); R__UseDummy(_R__UNIQUE_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *maplEstringcOdoublegR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const map<string,double>*)0x0)->GetClass();
      maplEstringcOdoublegR_TClassManip(theClass);
   return theClass;
   }

   static void maplEstringcOdoublegR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_maplEstringcOdoublegR(void *p) {
      return  p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) map<string,double> : new map<string,double>;
   }
   static void *newArray_maplEstringcOdoublegR(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) map<string,double>[nElements] : new map<string,double>[nElements];
   }
   // Wrapper around operator delete
   static void delete_maplEstringcOdoublegR(void *p) {
      delete ((map<string,double>*)p);
   }
   static void deleteArray_maplEstringcOdoublegR(void *p) {
      delete [] ((map<string,double>*)p);
   }
   static void destruct_maplEstringcOdoublegR(void *p) {
      typedef map<string,double> current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class map<string,double>

namespace ROOT {
   static TClass *maplEstringcOPythia8cLcLWordgR_Dictionary();
   static void maplEstringcOPythia8cLcLWordgR_TClassManip(TClass*);
   static void *new_maplEstringcOPythia8cLcLWordgR(void *p = 0);
   static void *newArray_maplEstringcOPythia8cLcLWordgR(Long_t size, void *p);
   static void delete_maplEstringcOPythia8cLcLWordgR(void *p);
   static void deleteArray_maplEstringcOPythia8cLcLWordgR(void *p);
   static void destruct_maplEstringcOPythia8cLcLWordgR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const map<string,Pythia8::Word>*)
   {
      map<string,Pythia8::Word> *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(map<string,Pythia8::Word>));
      static ::ROOT::TGenericClassInfo 
         instance("map<string,Pythia8::Word>", -2, "map", 96,
                  typeid(map<string,Pythia8::Word>), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &maplEstringcOPythia8cLcLWordgR_Dictionary, isa_proxy, 0,
                  sizeof(map<string,Pythia8::Word>) );
      instance.SetNew(&new_maplEstringcOPythia8cLcLWordgR);
      instance.SetNewArray(&newArray_maplEstringcOPythia8cLcLWordgR);
      instance.SetDelete(&delete_maplEstringcOPythia8cLcLWordgR);
      instance.SetDeleteArray(&deleteArray_maplEstringcOPythia8cLcLWordgR);
      instance.SetDestructor(&destruct_maplEstringcOPythia8cLcLWordgR);
      instance.AdoptCollectionProxyInfo(TCollectionProxyInfo::Generate(TCollectionProxyInfo::MapInsert< map<string,Pythia8::Word> >()));
      return &instance;
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const map<string,Pythia8::Word>*)0x0); R__UseDummy(_R__UNIQUE_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *maplEstringcOPythia8cLcLWordgR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const map<string,Pythia8::Word>*)0x0)->GetClass();
      maplEstringcOPythia8cLcLWordgR_TClassManip(theClass);
   return theClass;
   }

   static void maplEstringcOPythia8cLcLWordgR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_maplEstringcOPythia8cLcLWordgR(void *p) {
      return  p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) map<string,Pythia8::Word> : new map<string,Pythia8::Word>;
   }
   static void *newArray_maplEstringcOPythia8cLcLWordgR(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) map<string,Pythia8::Word>[nElements] : new map<string,Pythia8::Word>[nElements];
   }
   // Wrapper around operator delete
   static void delete_maplEstringcOPythia8cLcLWordgR(void *p) {
      delete ((map<string,Pythia8::Word>*)p);
   }
   static void deleteArray_maplEstringcOPythia8cLcLWordgR(void *p) {
      delete [] ((map<string,Pythia8::Word>*)p);
   }
   static void destruct_maplEstringcOPythia8cLcLWordgR(void *p) {
      typedef map<string,Pythia8::Word> current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class map<string,Pythia8::Word>

namespace ROOT {
   static TClass *maplEstringcOPythia8cLcLWVecgR_Dictionary();
   static void maplEstringcOPythia8cLcLWVecgR_TClassManip(TClass*);
   static void *new_maplEstringcOPythia8cLcLWVecgR(void *p = 0);
   static void *newArray_maplEstringcOPythia8cLcLWVecgR(Long_t size, void *p);
   static void delete_maplEstringcOPythia8cLcLWVecgR(void *p);
   static void deleteArray_maplEstringcOPythia8cLcLWVecgR(void *p);
   static void destruct_maplEstringcOPythia8cLcLWVecgR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const map<string,Pythia8::WVec>*)
   {
      map<string,Pythia8::WVec> *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(map<string,Pythia8::WVec>));
      static ::ROOT::TGenericClassInfo 
         instance("map<string,Pythia8::WVec>", -2, "map", 96,
                  typeid(map<string,Pythia8::WVec>), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &maplEstringcOPythia8cLcLWVecgR_Dictionary, isa_proxy, 0,
                  sizeof(map<string,Pythia8::WVec>) );
      instance.SetNew(&new_maplEstringcOPythia8cLcLWVecgR);
      instance.SetNewArray(&newArray_maplEstringcOPythia8cLcLWVecgR);
      instance.SetDelete(&delete_maplEstringcOPythia8cLcLWVecgR);
      instance.SetDeleteArray(&deleteArray_maplEstringcOPythia8cLcLWVecgR);
      instance.SetDestructor(&destruct_maplEstringcOPythia8cLcLWVecgR);
      instance.AdoptCollectionProxyInfo(TCollectionProxyInfo::Generate(TCollectionProxyInfo::MapInsert< map<string,Pythia8::WVec> >()));
      return &instance;
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const map<string,Pythia8::WVec>*)0x0); R__UseDummy(_R__UNIQUE_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *maplEstringcOPythia8cLcLWVecgR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const map<string,Pythia8::WVec>*)0x0)->GetClass();
      maplEstringcOPythia8cLcLWVecgR_TClassManip(theClass);
   return theClass;
   }

   static void maplEstringcOPythia8cLcLWVecgR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_maplEstringcOPythia8cLcLWVecgR(void *p) {
      return  p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) map<string,Pythia8::WVec> : new map<string,Pythia8::WVec>;
   }
   static void *newArray_maplEstringcOPythia8cLcLWVecgR(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) map<string,Pythia8::WVec>[nElements] : new map<string,Pythia8::WVec>[nElements];
   }
   // Wrapper around operator delete
   static void delete_maplEstringcOPythia8cLcLWVecgR(void *p) {
      delete ((map<string,Pythia8::WVec>*)p);
   }
   static void deleteArray_maplEstringcOPythia8cLcLWVecgR(void *p) {
      delete [] ((map<string,Pythia8::WVec>*)p);
   }
   static void destruct_maplEstringcOPythia8cLcLWVecgR(void *p) {
      typedef map<string,Pythia8::WVec> current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class map<string,Pythia8::WVec>

namespace ROOT {
   static TClass *maplEstringcOPythia8cLcLParmgR_Dictionary();
   static void maplEstringcOPythia8cLcLParmgR_TClassManip(TClass*);
   static void *new_maplEstringcOPythia8cLcLParmgR(void *p = 0);
   static void *newArray_maplEstringcOPythia8cLcLParmgR(Long_t size, void *p);
   static void delete_maplEstringcOPythia8cLcLParmgR(void *p);
   static void deleteArray_maplEstringcOPythia8cLcLParmgR(void *p);
   static void destruct_maplEstringcOPythia8cLcLParmgR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const map<string,Pythia8::Parm>*)
   {
      map<string,Pythia8::Parm> *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(map<string,Pythia8::Parm>));
      static ::ROOT::TGenericClassInfo 
         instance("map<string,Pythia8::Parm>", -2, "map", 96,
                  typeid(map<string,Pythia8::Parm>), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &maplEstringcOPythia8cLcLParmgR_Dictionary, isa_proxy, 0,
                  sizeof(map<string,Pythia8::Parm>) );
      instance.SetNew(&new_maplEstringcOPythia8cLcLParmgR);
      instance.SetNewArray(&newArray_maplEstringcOPythia8cLcLParmgR);
      instance.SetDelete(&delete_maplEstringcOPythia8cLcLParmgR);
      instance.SetDeleteArray(&deleteArray_maplEstringcOPythia8cLcLParmgR);
      instance.SetDestructor(&destruct_maplEstringcOPythia8cLcLParmgR);
      instance.AdoptCollectionProxyInfo(TCollectionProxyInfo::Generate(TCollectionProxyInfo::MapInsert< map<string,Pythia8::Parm> >()));
      return &instance;
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const map<string,Pythia8::Parm>*)0x0); R__UseDummy(_R__UNIQUE_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *maplEstringcOPythia8cLcLParmgR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const map<string,Pythia8::Parm>*)0x0)->GetClass();
      maplEstringcOPythia8cLcLParmgR_TClassManip(theClass);
   return theClass;
   }

   static void maplEstringcOPythia8cLcLParmgR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_maplEstringcOPythia8cLcLParmgR(void *p) {
      return  p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) map<string,Pythia8::Parm> : new map<string,Pythia8::Parm>;
   }
   static void *newArray_maplEstringcOPythia8cLcLParmgR(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) map<string,Pythia8::Parm>[nElements] : new map<string,Pythia8::Parm>[nElements];
   }
   // Wrapper around operator delete
   static void delete_maplEstringcOPythia8cLcLParmgR(void *p) {
      delete ((map<string,Pythia8::Parm>*)p);
   }
   static void deleteArray_maplEstringcOPythia8cLcLParmgR(void *p) {
      delete [] ((map<string,Pythia8::Parm>*)p);
   }
   static void destruct_maplEstringcOPythia8cLcLParmgR(void *p) {
      typedef map<string,Pythia8::Parm> current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class map<string,Pythia8::Parm>

namespace ROOT {
   static TClass *maplEstringcOPythia8cLcLPVecgR_Dictionary();
   static void maplEstringcOPythia8cLcLPVecgR_TClassManip(TClass*);
   static void *new_maplEstringcOPythia8cLcLPVecgR(void *p = 0);
   static void *newArray_maplEstringcOPythia8cLcLPVecgR(Long_t size, void *p);
   static void delete_maplEstringcOPythia8cLcLPVecgR(void *p);
   static void deleteArray_maplEstringcOPythia8cLcLPVecgR(void *p);
   static void destruct_maplEstringcOPythia8cLcLPVecgR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const map<string,Pythia8::PVec>*)
   {
      map<string,Pythia8::PVec> *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(map<string,Pythia8::PVec>));
      static ::ROOT::TGenericClassInfo 
         instance("map<string,Pythia8::PVec>", -2, "map", 96,
                  typeid(map<string,Pythia8::PVec>), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &maplEstringcOPythia8cLcLPVecgR_Dictionary, isa_proxy, 0,
                  sizeof(map<string,Pythia8::PVec>) );
      instance.SetNew(&new_maplEstringcOPythia8cLcLPVecgR);
      instance.SetNewArray(&newArray_maplEstringcOPythia8cLcLPVecgR);
      instance.SetDelete(&delete_maplEstringcOPythia8cLcLPVecgR);
      instance.SetDeleteArray(&deleteArray_maplEstringcOPythia8cLcLPVecgR);
      instance.SetDestructor(&destruct_maplEstringcOPythia8cLcLPVecgR);
      instance.AdoptCollectionProxyInfo(TCollectionProxyInfo::Generate(TCollectionProxyInfo::MapInsert< map<string,Pythia8::PVec> >()));
      return &instance;
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const map<string,Pythia8::PVec>*)0x0); R__UseDummy(_R__UNIQUE_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *maplEstringcOPythia8cLcLPVecgR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const map<string,Pythia8::PVec>*)0x0)->GetClass();
      maplEstringcOPythia8cLcLPVecgR_TClassManip(theClass);
   return theClass;
   }

   static void maplEstringcOPythia8cLcLPVecgR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_maplEstringcOPythia8cLcLPVecgR(void *p) {
      return  p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) map<string,Pythia8::PVec> : new map<string,Pythia8::PVec>;
   }
   static void *newArray_maplEstringcOPythia8cLcLPVecgR(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) map<string,Pythia8::PVec>[nElements] : new map<string,Pythia8::PVec>[nElements];
   }
   // Wrapper around operator delete
   static void delete_maplEstringcOPythia8cLcLPVecgR(void *p) {
      delete ((map<string,Pythia8::PVec>*)p);
   }
   static void deleteArray_maplEstringcOPythia8cLcLPVecgR(void *p) {
      delete [] ((map<string,Pythia8::PVec>*)p);
   }
   static void destruct_maplEstringcOPythia8cLcLPVecgR(void *p) {
      typedef map<string,Pythia8::PVec> current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class map<string,Pythia8::PVec>

namespace ROOT {
   static TClass *maplEstringcOPythia8cLcLModegR_Dictionary();
   static void maplEstringcOPythia8cLcLModegR_TClassManip(TClass*);
   static void *new_maplEstringcOPythia8cLcLModegR(void *p = 0);
   static void *newArray_maplEstringcOPythia8cLcLModegR(Long_t size, void *p);
   static void delete_maplEstringcOPythia8cLcLModegR(void *p);
   static void deleteArray_maplEstringcOPythia8cLcLModegR(void *p);
   static void destruct_maplEstringcOPythia8cLcLModegR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const map<string,Pythia8::Mode>*)
   {
      map<string,Pythia8::Mode> *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(map<string,Pythia8::Mode>));
      static ::ROOT::TGenericClassInfo 
         instance("map<string,Pythia8::Mode>", -2, "map", 96,
                  typeid(map<string,Pythia8::Mode>), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &maplEstringcOPythia8cLcLModegR_Dictionary, isa_proxy, 0,
                  sizeof(map<string,Pythia8::Mode>) );
      instance.SetNew(&new_maplEstringcOPythia8cLcLModegR);
      instance.SetNewArray(&newArray_maplEstringcOPythia8cLcLModegR);
      instance.SetDelete(&delete_maplEstringcOPythia8cLcLModegR);
      instance.SetDeleteArray(&deleteArray_maplEstringcOPythia8cLcLModegR);
      instance.SetDestructor(&destruct_maplEstringcOPythia8cLcLModegR);
      instance.AdoptCollectionProxyInfo(TCollectionProxyInfo::Generate(TCollectionProxyInfo::MapInsert< map<string,Pythia8::Mode> >()));
      return &instance;
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const map<string,Pythia8::Mode>*)0x0); R__UseDummy(_R__UNIQUE_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *maplEstringcOPythia8cLcLModegR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const map<string,Pythia8::Mode>*)0x0)->GetClass();
      maplEstringcOPythia8cLcLModegR_TClassManip(theClass);
   return theClass;
   }

   static void maplEstringcOPythia8cLcLModegR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_maplEstringcOPythia8cLcLModegR(void *p) {
      return  p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) map<string,Pythia8::Mode> : new map<string,Pythia8::Mode>;
   }
   static void *newArray_maplEstringcOPythia8cLcLModegR(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) map<string,Pythia8::Mode>[nElements] : new map<string,Pythia8::Mode>[nElements];
   }
   // Wrapper around operator delete
   static void delete_maplEstringcOPythia8cLcLModegR(void *p) {
      delete ((map<string,Pythia8::Mode>*)p);
   }
   static void deleteArray_maplEstringcOPythia8cLcLModegR(void *p) {
      delete [] ((map<string,Pythia8::Mode>*)p);
   }
   static void destruct_maplEstringcOPythia8cLcLModegR(void *p) {
      typedef map<string,Pythia8::Mode> current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class map<string,Pythia8::Mode>

namespace ROOT {
   static TClass *maplEstringcOPythia8cLcLMVecgR_Dictionary();
   static void maplEstringcOPythia8cLcLMVecgR_TClassManip(TClass*);
   static void *new_maplEstringcOPythia8cLcLMVecgR(void *p = 0);
   static void *newArray_maplEstringcOPythia8cLcLMVecgR(Long_t size, void *p);
   static void delete_maplEstringcOPythia8cLcLMVecgR(void *p);
   static void deleteArray_maplEstringcOPythia8cLcLMVecgR(void *p);
   static void destruct_maplEstringcOPythia8cLcLMVecgR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const map<string,Pythia8::MVec>*)
   {
      map<string,Pythia8::MVec> *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(map<string,Pythia8::MVec>));
      static ::ROOT::TGenericClassInfo 
         instance("map<string,Pythia8::MVec>", -2, "map", 96,
                  typeid(map<string,Pythia8::MVec>), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &maplEstringcOPythia8cLcLMVecgR_Dictionary, isa_proxy, 0,
                  sizeof(map<string,Pythia8::MVec>) );
      instance.SetNew(&new_maplEstringcOPythia8cLcLMVecgR);
      instance.SetNewArray(&newArray_maplEstringcOPythia8cLcLMVecgR);
      instance.SetDelete(&delete_maplEstringcOPythia8cLcLMVecgR);
      instance.SetDeleteArray(&deleteArray_maplEstringcOPythia8cLcLMVecgR);
      instance.SetDestructor(&destruct_maplEstringcOPythia8cLcLMVecgR);
      instance.AdoptCollectionProxyInfo(TCollectionProxyInfo::Generate(TCollectionProxyInfo::MapInsert< map<string,Pythia8::MVec> >()));
      return &instance;
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const map<string,Pythia8::MVec>*)0x0); R__UseDummy(_R__UNIQUE_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *maplEstringcOPythia8cLcLMVecgR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const map<string,Pythia8::MVec>*)0x0)->GetClass();
      maplEstringcOPythia8cLcLMVecgR_TClassManip(theClass);
   return theClass;
   }

   static void maplEstringcOPythia8cLcLMVecgR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_maplEstringcOPythia8cLcLMVecgR(void *p) {
      return  p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) map<string,Pythia8::MVec> : new map<string,Pythia8::MVec>;
   }
   static void *newArray_maplEstringcOPythia8cLcLMVecgR(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) map<string,Pythia8::MVec>[nElements] : new map<string,Pythia8::MVec>[nElements];
   }
   // Wrapper around operator delete
   static void delete_maplEstringcOPythia8cLcLMVecgR(void *p) {
      delete ((map<string,Pythia8::MVec>*)p);
   }
   static void deleteArray_maplEstringcOPythia8cLcLMVecgR(void *p) {
      delete [] ((map<string,Pythia8::MVec>*)p);
   }
   static void destruct_maplEstringcOPythia8cLcLMVecgR(void *p) {
      typedef map<string,Pythia8::MVec> current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class map<string,Pythia8::MVec>

namespace ROOT {
   static TClass *maplEstringcOPythia8cLcLLHAweightgroupgR_Dictionary();
   static void maplEstringcOPythia8cLcLLHAweightgroupgR_TClassManip(TClass*);
   static void *new_maplEstringcOPythia8cLcLLHAweightgroupgR(void *p = 0);
   static void *newArray_maplEstringcOPythia8cLcLLHAweightgroupgR(Long_t size, void *p);
   static void delete_maplEstringcOPythia8cLcLLHAweightgroupgR(void *p);
   static void deleteArray_maplEstringcOPythia8cLcLLHAweightgroupgR(void *p);
   static void destruct_maplEstringcOPythia8cLcLLHAweightgroupgR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const map<string,Pythia8::LHAweightgroup>*)
   {
      map<string,Pythia8::LHAweightgroup> *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(map<string,Pythia8::LHAweightgroup>));
      static ::ROOT::TGenericClassInfo 
         instance("map<string,Pythia8::LHAweightgroup>", -2, "map", 96,
                  typeid(map<string,Pythia8::LHAweightgroup>), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &maplEstringcOPythia8cLcLLHAweightgroupgR_Dictionary, isa_proxy, 0,
                  sizeof(map<string,Pythia8::LHAweightgroup>) );
      instance.SetNew(&new_maplEstringcOPythia8cLcLLHAweightgroupgR);
      instance.SetNewArray(&newArray_maplEstringcOPythia8cLcLLHAweightgroupgR);
      instance.SetDelete(&delete_maplEstringcOPythia8cLcLLHAweightgroupgR);
      instance.SetDeleteArray(&deleteArray_maplEstringcOPythia8cLcLLHAweightgroupgR);
      instance.SetDestructor(&destruct_maplEstringcOPythia8cLcLLHAweightgroupgR);
      instance.AdoptCollectionProxyInfo(TCollectionProxyInfo::Generate(TCollectionProxyInfo::MapInsert< map<string,Pythia8::LHAweightgroup> >()));
      return &instance;
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const map<string,Pythia8::LHAweightgroup>*)0x0); R__UseDummy(_R__UNIQUE_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *maplEstringcOPythia8cLcLLHAweightgroupgR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const map<string,Pythia8::LHAweightgroup>*)0x0)->GetClass();
      maplEstringcOPythia8cLcLLHAweightgroupgR_TClassManip(theClass);
   return theClass;
   }

   static void maplEstringcOPythia8cLcLLHAweightgroupgR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_maplEstringcOPythia8cLcLLHAweightgroupgR(void *p) {
      return  p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) map<string,Pythia8::LHAweightgroup> : new map<string,Pythia8::LHAweightgroup>;
   }
   static void *newArray_maplEstringcOPythia8cLcLLHAweightgroupgR(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) map<string,Pythia8::LHAweightgroup>[nElements] : new map<string,Pythia8::LHAweightgroup>[nElements];
   }
   // Wrapper around operator delete
   static void delete_maplEstringcOPythia8cLcLLHAweightgroupgR(void *p) {
      delete ((map<string,Pythia8::LHAweightgroup>*)p);
   }
   static void deleteArray_maplEstringcOPythia8cLcLLHAweightgroupgR(void *p) {
      delete [] ((map<string,Pythia8::LHAweightgroup>*)p);
   }
   static void destruct_maplEstringcOPythia8cLcLLHAweightgroupgR(void *p) {
      typedef map<string,Pythia8::LHAweightgroup> current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class map<string,Pythia8::LHAweightgroup>

namespace ROOT {
   static TClass *maplEstringcOPythia8cLcLLHAweightgR_Dictionary();
   static void maplEstringcOPythia8cLcLLHAweightgR_TClassManip(TClass*);
   static void *new_maplEstringcOPythia8cLcLLHAweightgR(void *p = 0);
   static void *newArray_maplEstringcOPythia8cLcLLHAweightgR(Long_t size, void *p);
   static void delete_maplEstringcOPythia8cLcLLHAweightgR(void *p);
   static void deleteArray_maplEstringcOPythia8cLcLLHAweightgR(void *p);
   static void destruct_maplEstringcOPythia8cLcLLHAweightgR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const map<string,Pythia8::LHAweight>*)
   {
      map<string,Pythia8::LHAweight> *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(map<string,Pythia8::LHAweight>));
      static ::ROOT::TGenericClassInfo 
         instance("map<string,Pythia8::LHAweight>", -2, "map", 96,
                  typeid(map<string,Pythia8::LHAweight>), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &maplEstringcOPythia8cLcLLHAweightgR_Dictionary, isa_proxy, 0,
                  sizeof(map<string,Pythia8::LHAweight>) );
      instance.SetNew(&new_maplEstringcOPythia8cLcLLHAweightgR);
      instance.SetNewArray(&newArray_maplEstringcOPythia8cLcLLHAweightgR);
      instance.SetDelete(&delete_maplEstringcOPythia8cLcLLHAweightgR);
      instance.SetDeleteArray(&deleteArray_maplEstringcOPythia8cLcLLHAweightgR);
      instance.SetDestructor(&destruct_maplEstringcOPythia8cLcLLHAweightgR);
      instance.AdoptCollectionProxyInfo(TCollectionProxyInfo::Generate(TCollectionProxyInfo::MapInsert< map<string,Pythia8::LHAweight> >()));
      return &instance;
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const map<string,Pythia8::LHAweight>*)0x0); R__UseDummy(_R__UNIQUE_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *maplEstringcOPythia8cLcLLHAweightgR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const map<string,Pythia8::LHAweight>*)0x0)->GetClass();
      maplEstringcOPythia8cLcLLHAweightgR_TClassManip(theClass);
   return theClass;
   }

   static void maplEstringcOPythia8cLcLLHAweightgR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_maplEstringcOPythia8cLcLLHAweightgR(void *p) {
      return  p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) map<string,Pythia8::LHAweight> : new map<string,Pythia8::LHAweight>;
   }
   static void *newArray_maplEstringcOPythia8cLcLLHAweightgR(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) map<string,Pythia8::LHAweight>[nElements] : new map<string,Pythia8::LHAweight>[nElements];
   }
   // Wrapper around operator delete
   static void delete_maplEstringcOPythia8cLcLLHAweightgR(void *p) {
      delete ((map<string,Pythia8::LHAweight>*)p);
   }
   static void deleteArray_maplEstringcOPythia8cLcLLHAweightgR(void *p) {
      delete [] ((map<string,Pythia8::LHAweight>*)p);
   }
   static void destruct_maplEstringcOPythia8cLcLLHAweightgR(void *p) {
      typedef map<string,Pythia8::LHAweight> current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class map<string,Pythia8::LHAweight>

namespace ROOT {
   static TClass *maplEstringcOPythia8cLcLFlaggR_Dictionary();
   static void maplEstringcOPythia8cLcLFlaggR_TClassManip(TClass*);
   static void *new_maplEstringcOPythia8cLcLFlaggR(void *p = 0);
   static void *newArray_maplEstringcOPythia8cLcLFlaggR(Long_t size, void *p);
   static void delete_maplEstringcOPythia8cLcLFlaggR(void *p);
   static void deleteArray_maplEstringcOPythia8cLcLFlaggR(void *p);
   static void destruct_maplEstringcOPythia8cLcLFlaggR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const map<string,Pythia8::Flag>*)
   {
      map<string,Pythia8::Flag> *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(map<string,Pythia8::Flag>));
      static ::ROOT::TGenericClassInfo 
         instance("map<string,Pythia8::Flag>", -2, "map", 96,
                  typeid(map<string,Pythia8::Flag>), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &maplEstringcOPythia8cLcLFlaggR_Dictionary, isa_proxy, 0,
                  sizeof(map<string,Pythia8::Flag>) );
      instance.SetNew(&new_maplEstringcOPythia8cLcLFlaggR);
      instance.SetNewArray(&newArray_maplEstringcOPythia8cLcLFlaggR);
      instance.SetDelete(&delete_maplEstringcOPythia8cLcLFlaggR);
      instance.SetDeleteArray(&deleteArray_maplEstringcOPythia8cLcLFlaggR);
      instance.SetDestructor(&destruct_maplEstringcOPythia8cLcLFlaggR);
      instance.AdoptCollectionProxyInfo(TCollectionProxyInfo::Generate(TCollectionProxyInfo::MapInsert< map<string,Pythia8::Flag> >()));
      return &instance;
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const map<string,Pythia8::Flag>*)0x0); R__UseDummy(_R__UNIQUE_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *maplEstringcOPythia8cLcLFlaggR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const map<string,Pythia8::Flag>*)0x0)->GetClass();
      maplEstringcOPythia8cLcLFlaggR_TClassManip(theClass);
   return theClass;
   }

   static void maplEstringcOPythia8cLcLFlaggR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_maplEstringcOPythia8cLcLFlaggR(void *p) {
      return  p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) map<string,Pythia8::Flag> : new map<string,Pythia8::Flag>;
   }
   static void *newArray_maplEstringcOPythia8cLcLFlaggR(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) map<string,Pythia8::Flag>[nElements] : new map<string,Pythia8::Flag>[nElements];
   }
   // Wrapper around operator delete
   static void delete_maplEstringcOPythia8cLcLFlaggR(void *p) {
      delete ((map<string,Pythia8::Flag>*)p);
   }
   static void deleteArray_maplEstringcOPythia8cLcLFlaggR(void *p) {
      delete [] ((map<string,Pythia8::Flag>*)p);
   }
   static void destruct_maplEstringcOPythia8cLcLFlaggR(void *p) {
      typedef map<string,Pythia8::Flag> current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class map<string,Pythia8::Flag>

namespace ROOT {
   static TClass *maplEstringcOPythia8cLcLFVecgR_Dictionary();
   static void maplEstringcOPythia8cLcLFVecgR_TClassManip(TClass*);
   static void *new_maplEstringcOPythia8cLcLFVecgR(void *p = 0);
   static void *newArray_maplEstringcOPythia8cLcLFVecgR(Long_t size, void *p);
   static void delete_maplEstringcOPythia8cLcLFVecgR(void *p);
   static void deleteArray_maplEstringcOPythia8cLcLFVecgR(void *p);
   static void destruct_maplEstringcOPythia8cLcLFVecgR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const map<string,Pythia8::FVec>*)
   {
      map<string,Pythia8::FVec> *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(map<string,Pythia8::FVec>));
      static ::ROOT::TGenericClassInfo 
         instance("map<string,Pythia8::FVec>", -2, "map", 96,
                  typeid(map<string,Pythia8::FVec>), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &maplEstringcOPythia8cLcLFVecgR_Dictionary, isa_proxy, 0,
                  sizeof(map<string,Pythia8::FVec>) );
      instance.SetNew(&new_maplEstringcOPythia8cLcLFVecgR);
      instance.SetNewArray(&newArray_maplEstringcOPythia8cLcLFVecgR);
      instance.SetDelete(&delete_maplEstringcOPythia8cLcLFVecgR);
      instance.SetDeleteArray(&deleteArray_maplEstringcOPythia8cLcLFVecgR);
      instance.SetDestructor(&destruct_maplEstringcOPythia8cLcLFVecgR);
      instance.AdoptCollectionProxyInfo(TCollectionProxyInfo::Generate(TCollectionProxyInfo::MapInsert< map<string,Pythia8::FVec> >()));
      return &instance;
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const map<string,Pythia8::FVec>*)0x0); R__UseDummy(_R__UNIQUE_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *maplEstringcOPythia8cLcLFVecgR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const map<string,Pythia8::FVec>*)0x0)->GetClass();
      maplEstringcOPythia8cLcLFVecgR_TClassManip(theClass);
   return theClass;
   }

   static void maplEstringcOPythia8cLcLFVecgR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_maplEstringcOPythia8cLcLFVecgR(void *p) {
      return  p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) map<string,Pythia8::FVec> : new map<string,Pythia8::FVec>;
   }
   static void *newArray_maplEstringcOPythia8cLcLFVecgR(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) map<string,Pythia8::FVec>[nElements] : new map<string,Pythia8::FVec>[nElements];
   }
   // Wrapper around operator delete
   static void delete_maplEstringcOPythia8cLcLFVecgR(void *p) {
      delete ((map<string,Pythia8::FVec>*)p);
   }
   static void deleteArray_maplEstringcOPythia8cLcLFVecgR(void *p) {
      delete [] ((map<string,Pythia8::FVec>*)p);
   }
   static void destruct_maplEstringcOPythia8cLcLFVecgR(void *p) {
      typedef map<string,Pythia8::FVec> current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class map<string,Pythia8::FVec>

namespace ROOT {
   static TClass *maplEintcOstringgR_Dictionary();
   static void maplEintcOstringgR_TClassManip(TClass*);
   static void *new_maplEintcOstringgR(void *p = 0);
   static void *newArray_maplEintcOstringgR(Long_t size, void *p);
   static void delete_maplEintcOstringgR(void *p);
   static void deleteArray_maplEintcOstringgR(void *p);
   static void destruct_maplEintcOstringgR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const map<int,string>*)
   {
      map<int,string> *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(map<int,string>));
      static ::ROOT::TGenericClassInfo 
         instance("map<int,string>", -2, "map", 96,
                  typeid(map<int,string>), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &maplEintcOstringgR_Dictionary, isa_proxy, 0,
                  sizeof(map<int,string>) );
      instance.SetNew(&new_maplEintcOstringgR);
      instance.SetNewArray(&newArray_maplEintcOstringgR);
      instance.SetDelete(&delete_maplEintcOstringgR);
      instance.SetDeleteArray(&deleteArray_maplEintcOstringgR);
      instance.SetDestructor(&destruct_maplEintcOstringgR);
      instance.AdoptCollectionProxyInfo(TCollectionProxyInfo::Generate(TCollectionProxyInfo::MapInsert< map<int,string> >()));
      return &instance;
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const map<int,string>*)0x0); R__UseDummy(_R__UNIQUE_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *maplEintcOstringgR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const map<int,string>*)0x0)->GetClass();
      maplEintcOstringgR_TClassManip(theClass);
   return theClass;
   }

   static void maplEintcOstringgR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_maplEintcOstringgR(void *p) {
      return  p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) map<int,string> : new map<int,string>;
   }
   static void *newArray_maplEintcOstringgR(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) map<int,string>[nElements] : new map<int,string>[nElements];
   }
   // Wrapper around operator delete
   static void delete_maplEintcOstringgR(void *p) {
      delete ((map<int,string>*)p);
   }
   static void deleteArray_maplEintcOstringgR(void *p) {
      delete [] ((map<int,string>*)p);
   }
   static void destruct_maplEintcOstringgR(void *p) {
      typedef map<int,string> current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class map<int,string>

namespace ROOT {
   static TClass *maplEintcOlonggR_Dictionary();
   static void maplEintcOlonggR_TClassManip(TClass*);
   static void *new_maplEintcOlonggR(void *p = 0);
   static void *newArray_maplEintcOlonggR(Long_t size, void *p);
   static void delete_maplEintcOlonggR(void *p);
   static void deleteArray_maplEintcOlonggR(void *p);
   static void destruct_maplEintcOlonggR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const map<int,long>*)
   {
      map<int,long> *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(map<int,long>));
      static ::ROOT::TGenericClassInfo 
         instance("map<int,long>", -2, "map", 96,
                  typeid(map<int,long>), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &maplEintcOlonggR_Dictionary, isa_proxy, 0,
                  sizeof(map<int,long>) );
      instance.SetNew(&new_maplEintcOlonggR);
      instance.SetNewArray(&newArray_maplEintcOlonggR);
      instance.SetDelete(&delete_maplEintcOlonggR);
      instance.SetDeleteArray(&deleteArray_maplEintcOlonggR);
      instance.SetDestructor(&destruct_maplEintcOlonggR);
      instance.AdoptCollectionProxyInfo(TCollectionProxyInfo::Generate(TCollectionProxyInfo::MapInsert< map<int,long> >()));
      return &instance;
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const map<int,long>*)0x0); R__UseDummy(_R__UNIQUE_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *maplEintcOlonggR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const map<int,long>*)0x0)->GetClass();
      maplEintcOlonggR_TClassManip(theClass);
   return theClass;
   }

   static void maplEintcOlonggR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_maplEintcOlonggR(void *p) {
      return  p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) map<int,long> : new map<int,long>;
   }
   static void *newArray_maplEintcOlonggR(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) map<int,long>[nElements] : new map<int,long>[nElements];
   }
   // Wrapper around operator delete
   static void delete_maplEintcOlonggR(void *p) {
      delete ((map<int,long>*)p);
   }
   static void deleteArray_maplEintcOlonggR(void *p) {
      delete [] ((map<int,long>*)p);
   }
   static void destruct_maplEintcOlonggR(void *p) {
      typedef map<int,long> current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class map<int,long>

namespace ROOT {
   static TClass *maplEintcOdoublegR_Dictionary();
   static void maplEintcOdoublegR_TClassManip(TClass*);
   static void *new_maplEintcOdoublegR(void *p = 0);
   static void *newArray_maplEintcOdoublegR(Long_t size, void *p);
   static void delete_maplEintcOdoublegR(void *p);
   static void deleteArray_maplEintcOdoublegR(void *p);
   static void destruct_maplEintcOdoublegR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const map<int,double>*)
   {
      map<int,double> *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(map<int,double>));
      static ::ROOT::TGenericClassInfo 
         instance("map<int,double>", -2, "map", 96,
                  typeid(map<int,double>), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &maplEintcOdoublegR_Dictionary, isa_proxy, 0,
                  sizeof(map<int,double>) );
      instance.SetNew(&new_maplEintcOdoublegR);
      instance.SetNewArray(&newArray_maplEintcOdoublegR);
      instance.SetDelete(&delete_maplEintcOdoublegR);
      instance.SetDeleteArray(&deleteArray_maplEintcOdoublegR);
      instance.SetDestructor(&destruct_maplEintcOdoublegR);
      instance.AdoptCollectionProxyInfo(TCollectionProxyInfo::Generate(TCollectionProxyInfo::MapInsert< map<int,double> >()));
      return &instance;
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const map<int,double>*)0x0); R__UseDummy(_R__UNIQUE_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *maplEintcOdoublegR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const map<int,double>*)0x0)->GetClass();
      maplEintcOdoublegR_TClassManip(theClass);
   return theClass;
   }

   static void maplEintcOdoublegR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_maplEintcOdoublegR(void *p) {
      return  p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) map<int,double> : new map<int,double>;
   }
   static void *newArray_maplEintcOdoublegR(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) map<int,double>[nElements] : new map<int,double>[nElements];
   }
   // Wrapper around operator delete
   static void delete_maplEintcOdoublegR(void *p) {
      delete ((map<int,double>*)p);
   }
   static void deleteArray_maplEintcOdoublegR(void *p) {
      delete [] ((map<int,double>*)p);
   }
   static void destruct_maplEintcOdoublegR(void *p) {
      typedef map<int,double> current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class map<int,double>

namespace ROOT {
   static TClass *maplEintcOPythia8cLcLParticleDataEntrygR_Dictionary();
   static void maplEintcOPythia8cLcLParticleDataEntrygR_TClassManip(TClass*);
   static void *new_maplEintcOPythia8cLcLParticleDataEntrygR(void *p = 0);
   static void *newArray_maplEintcOPythia8cLcLParticleDataEntrygR(Long_t size, void *p);
   static void delete_maplEintcOPythia8cLcLParticleDataEntrygR(void *p);
   static void deleteArray_maplEintcOPythia8cLcLParticleDataEntrygR(void *p);
   static void destruct_maplEintcOPythia8cLcLParticleDataEntrygR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const map<int,Pythia8::ParticleDataEntry>*)
   {
      map<int,Pythia8::ParticleDataEntry> *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(map<int,Pythia8::ParticleDataEntry>));
      static ::ROOT::TGenericClassInfo 
         instance("map<int,Pythia8::ParticleDataEntry>", -2, "map", 96,
                  typeid(map<int,Pythia8::ParticleDataEntry>), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &maplEintcOPythia8cLcLParticleDataEntrygR_Dictionary, isa_proxy, 0,
                  sizeof(map<int,Pythia8::ParticleDataEntry>) );
      instance.SetNew(&new_maplEintcOPythia8cLcLParticleDataEntrygR);
      instance.SetNewArray(&newArray_maplEintcOPythia8cLcLParticleDataEntrygR);
      instance.SetDelete(&delete_maplEintcOPythia8cLcLParticleDataEntrygR);
      instance.SetDeleteArray(&deleteArray_maplEintcOPythia8cLcLParticleDataEntrygR);
      instance.SetDestructor(&destruct_maplEintcOPythia8cLcLParticleDataEntrygR);
      instance.AdoptCollectionProxyInfo(TCollectionProxyInfo::Generate(TCollectionProxyInfo::MapInsert< map<int,Pythia8::ParticleDataEntry> >()));
      return &instance;
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const map<int,Pythia8::ParticleDataEntry>*)0x0); R__UseDummy(_R__UNIQUE_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *maplEintcOPythia8cLcLParticleDataEntrygR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const map<int,Pythia8::ParticleDataEntry>*)0x0)->GetClass();
      maplEintcOPythia8cLcLParticleDataEntrygR_TClassManip(theClass);
   return theClass;
   }

   static void maplEintcOPythia8cLcLParticleDataEntrygR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_maplEintcOPythia8cLcLParticleDataEntrygR(void *p) {
      return  p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) map<int,Pythia8::ParticleDataEntry> : new map<int,Pythia8::ParticleDataEntry>;
   }
   static void *newArray_maplEintcOPythia8cLcLParticleDataEntrygR(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) map<int,Pythia8::ParticleDataEntry>[nElements] : new map<int,Pythia8::ParticleDataEntry>[nElements];
   }
   // Wrapper around operator delete
   static void delete_maplEintcOPythia8cLcLParticleDataEntrygR(void *p) {
      delete ((map<int,Pythia8::ParticleDataEntry>*)p);
   }
   static void deleteArray_maplEintcOPythia8cLcLParticleDataEntrygR(void *p) {
      delete [] ((map<int,Pythia8::ParticleDataEntry>*)p);
   }
   static void destruct_maplEintcOPythia8cLcLParticleDataEntrygR(void *p) {
      typedef map<int,Pythia8::ParticleDataEntry> current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class map<int,Pythia8::ParticleDataEntry>

namespace {
  void TriggerDictionaryInitialization_dict4RootDct_Impl() {
    static const char* headers[] = {
"dictionary/dict4Root.h",
0
    };
    static const char* includePaths[] = {
"../include",
"/usr/local/include/root",
0
    };
    static const char* fwdDeclCode = R"DICTFWDDCLS(
#line 1 "dict4RootDct dictionary forward declarations' payload"
#pragma clang diagnostic ignored "-Wkeyword-compat"
#pragma clang diagnostic ignored "-Wignored-attributes"
#pragma clang diagnostic ignored "-Wreturn-type-c-linkage"
extern int __Cling_Autoloading_Map;
namespace Pythia8{class __attribute__((annotate("$clingAutoload$dictionary/dict4Root.h")))  Event;}
namespace Pythia8{class __attribute__((annotate("$clingAutoload$dictionary/dict4Root.h")))  Particle;}
namespace Pythia8{class __attribute__((annotate("$clingAutoload$dictionary/dict4Root.h")))  Junction;}
namespace Pythia8{class __attribute__((annotate("$clingAutoload$dictionary/dict4Root.h")))  Vec4;}
namespace Pythia8{class __attribute__((annotate("$clingAutoload$dictionary/dict4Root.h")))  ParticleData;}
namespace Pythia8{class __attribute__((annotate("$clingAutoload$dictionary/dict4Root.h")))  ParticleDataEntry;}
namespace Pythia8{class __attribute__((annotate("$clingAutoload$dictionary/dict4Root.h")))  DecayChannel;}
namespace Pythia8{class __attribute__((annotate("$clingAutoload$dictionary/dict4Root.h")))  Pythia;}
namespace Pythia8{class __attribute__((annotate("$clingAutoload$dictionary/dict4Root.h")))  CoupSM;}
namespace Pythia8{class __attribute__((annotate("$clingAutoload$dictionary/dict4Root.h")))  Couplings;}
namespace Pythia8{class __attribute__((annotate("$clingAutoload$dictionary/dict4Root.h")))  InBeam;}
namespace Pythia8{class __attribute__((annotate("$clingAutoload$dictionary/dict4Root.h")))  InPair;}
namespace Pythia8{class __attribute__((annotate("$clingAutoload$dictionary/dict4Root.h")))  AlphaStrong;}
namespace Pythia8{class __attribute__((annotate("$clingAutoload$dictionary/dict4Root.h")))  AlphaEM;}
namespace Pythia8{class __attribute__((annotate("$clingAutoload$dictionary/dict4Root.h")))  Info;}
namespace Pythia8{class __attribute__((annotate("$clingAutoload$dictionary/dict4Root.h")))  Rndm;}
namespace Pythia8{class __attribute__((annotate("$clingAutoload$dictionary/dict4Root.h")))  RndmEngine;}
namespace Pythia8{class __attribute__((annotate("$clingAutoload$dictionary/dict4Root.h")))  Settings;}
namespace Pythia8{class __attribute__((annotate("$clingAutoload$dictionary/dict4Root.h")))  ResonanceTop;}
namespace Pythia8{class __attribute__((annotate("$clingAutoload$dictionary/dict4Root.h")))  ResonanceGeneric;}
namespace Pythia8{class __attribute__((annotate("$clingAutoload$dictionary/dict4Root.h")))  ResonanceGmZ;}
namespace Pythia8{class __attribute__((annotate("$clingAutoload$dictionary/dict4Root.h")))  ResonanceW;}
namespace Pythia8{class __attribute__((annotate("$clingAutoload$dictionary/dict4Root.h")))  ResonanceFour;}
namespace Pythia8{class __attribute__((annotate("$clingAutoload$dictionary/dict4Root.h")))  ResonanceH;}
namespace Pythia8{class __attribute__((annotate("$clingAutoload$dictionary/dict4Root.h")))  ResonanceHchg;}
namespace Pythia8{class __attribute__((annotate("$clingAutoload$dictionary/dict4Root.h")))  ResonanceZprime;}
namespace Pythia8{class __attribute__((annotate("$clingAutoload$dictionary/dict4Root.h")))  ResonanceWprime;}
namespace Pythia8{class __attribute__((annotate("$clingAutoload$dictionary/dict4Root.h")))  ResonanceRhorizontal;}
namespace Pythia8{class __attribute__((annotate("$clingAutoload$dictionary/dict4Root.h")))  ResonanceExcited;}
namespace Pythia8{class __attribute__((annotate("$clingAutoload$dictionary/dict4Root.h")))  ResonanceGraviton;}
namespace Pythia8{class __attribute__((annotate("$clingAutoload$dictionary/dict4Root.h")))  ResonanceLeptoquark;}
namespace Pythia8{class __attribute__((annotate("$clingAutoload$dictionary/dict4Root.h")))  ResonanceNuRight;}
namespace Pythia8{class __attribute__((annotate("$clingAutoload$dictionary/dict4Root.h")))  ResonanceZRight;}
namespace Pythia8{class __attribute__((annotate("$clingAutoload$dictionary/dict4Root.h")))  ResonanceWRight;}
namespace Pythia8{class __attribute__((annotate("$clingAutoload$dictionary/dict4Root.h")))  ResonanceHchgchgLeft;}
namespace Pythia8{class __attribute__((annotate("$clingAutoload$dictionary/dict4Root.h")))  ResonanceHchgchgRight;}
namespace Pythia8{class __attribute__((annotate("$clingAutoload$dictionary/dict4Root.h")))  SigmaProcess;}
)DICTFWDDCLS";
    static const char* payloadCode = R"DICTPAYLOAD(
#line 1 "dict4RootDct dictionary payload"

#ifndef G__VECTOR_HAS_CLASS_ITERATOR
  #define G__VECTOR_HAS_CLASS_ITERATOR 1
#endif

#define _BACKWARD_BACKWARD_WARNING_H
#include "dictionary/dict4Root.h"

#undef  _BACKWARD_BACKWARD_WARNING_H
)DICTPAYLOAD";
    static const char* classesHeaders[]={
"Pythia8::AlphaEM", payloadCode, "@",
"Pythia8::AlphaStrong", payloadCode, "@",
"Pythia8::CoupSM", payloadCode, "@",
"Pythia8::Couplings", payloadCode, "@",
"Pythia8::DecayChannel", payloadCode, "@",
"Pythia8::Event", payloadCode, "@",
"Pythia8::InBeam", payloadCode, "@",
"Pythia8::InPair", payloadCode, "@",
"Pythia8::Info", payloadCode, "@",
"Pythia8::Junction", payloadCode, "@",
"Pythia8::Particle", payloadCode, "@",
"Pythia8::ParticleData", payloadCode, "@",
"Pythia8::ParticleDataEntry", payloadCode, "@",
"Pythia8::Pythia", payloadCode, "@",
"Pythia8::ResonanceExcited", payloadCode, "@",
"Pythia8::ResonanceFour", payloadCode, "@",
"Pythia8::ResonanceGeneric", payloadCode, "@",
"Pythia8::ResonanceGmZ", payloadCode, "@",
"Pythia8::ResonanceGraviton", payloadCode, "@",
"Pythia8::ResonanceH", payloadCode, "@",
"Pythia8::ResonanceHchg", payloadCode, "@",
"Pythia8::ResonanceHchgchgLeft", payloadCode, "@",
"Pythia8::ResonanceHchgchgRight", payloadCode, "@",
"Pythia8::ResonanceLeptoquark", payloadCode, "@",
"Pythia8::ResonanceNuRight", payloadCode, "@",
"Pythia8::ResonanceRhorizontal", payloadCode, "@",
"Pythia8::ResonanceTop", payloadCode, "@",
"Pythia8::ResonanceW", payloadCode, "@",
"Pythia8::ResonanceWRight", payloadCode, "@",
"Pythia8::ResonanceWprime", payloadCode, "@",
"Pythia8::ResonanceZRight", payloadCode, "@",
"Pythia8::ResonanceZprime", payloadCode, "@",
"Pythia8::Rndm", payloadCode, "@",
"Pythia8::RndmEngine", payloadCode, "@",
"Pythia8::Settings", payloadCode, "@",
"Pythia8::SigmaProcess", payloadCode, "@",
"Pythia8::Vec4", payloadCode, "@",
nullptr};

    static bool isInitialized = false;
    if (!isInitialized) {
      TROOT::RegisterModule("dictionary/dict4RootDct",
        headers, includePaths, payloadCode, fwdDeclCode,
        TriggerDictionaryInitialization_dict4RootDct_Impl, {}, classesHeaders);
      isInitialized = true;
    }
  }
  static struct DictInit {
    DictInit() {
      TriggerDictionaryInitialization_dict4RootDct_Impl();
    }
  } __TheDictionaryInitializer;
}
void TriggerDictionaryInitialization_dict4RootDct() {
  TriggerDictionaryInitialization_dict4RootDct_Impl();
}
