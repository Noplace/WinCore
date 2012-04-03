/*****************************************************************************************************************
* Copyright (c) 2012 Khalid Ali Al-Kooheji                                                                       *
*                                                                                                                *
* Permission is hereby granted, free of charge, to any person obtaining a copy of this software and              *
* associated documentation files (the "Software"), to deal in the Software without restriction, including        *
* without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell        *
* copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the       *
* following conditions:                                                                                          *
*                                                                                                                *
* The above copyright notice and this permission notice shall be included in all copies or substantial           *
* portions of the Software.                                                                                      *
*                                                                                                                *
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT          *
* LIMITED TO THE WARRANTIES OF MERCHANTABILITY, * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.          *
* IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, * DAMAGES OR OTHER LIABILITY,      *
* WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE            *
* SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.                                                         *
*****************************************************************************************************************/
namespace core {
namespace delegation {
namespace PNAMESPACE {
namespace hidden {

/*********************************************************************
Class Name	: CallBase
Description	: abstract calling interface.
*********************************************************************/
template <templatePARAMS> 
class CallBase {
 public:
  virtual ReturnType operator ()(PARAMS) const = 0;
};

/*********************************************************************
Class Name	: CallStaticFunction
Description	: calling interface inheriting CallBase to allow 
              delegation of global/static functions.
*********************************************************************/
template <templatePARAMS> 
class CallStaticFunction: public CallBase<templatePARAMS>
{
 public:
  typedef ReturnType (*StaticFunctionPointer)(PARAMS);
  CallStaticFunction(StaticFunctionPointer p0): function_pointer(p0) {

  }

  virtual ReturnType operator()(PARAMSwithVARS) const {
      return function_pointer(VARS);
  }
 protected:
  StaticFunctionPointer	function_pointer;
 private:

};

/*********************************************************************
Class Name	: CallMemberFunction
Description	: calling interface inheriting CallBase to allow 
              delegation of class/struct functions.
*********************************************************************/
template <class ObjectType,templatePARAMS> 
class CallMemberFunction: public CallBase<templatePARAMS> {
 public:
  typedef ReturnType (ObjectType::*MemberFunctionPointer)(PARAMS);
  CallMemberFunction(ObjectType* p0,MemberFunctionPointer p1): object_pointer(p0),member_function_pointer(p1) {
            
  }
  virtual ReturnType operator()(PARAMSwithVARS) const {
      return (object_pointer->*member_function_pointer)(VARS);
  }
 protected:
  ObjectType*				object_pointer;
  MemberFunctionPointer	member_function_pointer;
 private:

};

}

/*********************************************************************
Struct Name	: pair
Description	: pair an object and a member function to allow
              assignment operator syntax for function delegation.
*********************************************************************/
template <class ObjectType,templatePARAMS> 
struct pair {
  pair(ObjectType* p0,ReturnType (ObjectType::*p1)(PARAMS)) : object_pointer(p0), member_function_pointer(p1) {
        
  }

  ObjectType*	object_pointer;
  ReturnType (ObjectType::*member_function_pointer)(PARAMS);
};

/*********************************************************************
Struct Name	: function
Description	: main class that allows delegation of member/non
              member functions.
Abbrev List : call : call
*********************************************************************/
template <templatePARAMS>
class Function {
 public:
  Function() : call(0)  {
          
  }

  ~Function()  {
      Clean();
  }
  
  template <class Func>
  Function& operator=(Func& function) {
      call = function.call;
      return *this;
  }

  Function& operator=(ReturnType (*p0)(PARAMS)) {
      Bind(p0);
      return *this;
  }

  template <class ObjectType>
  Function& operator=(const pair<ObjectType,templateICALLS>& p0) {
      Bind<ObjectType>(p0.object_pointer,p0.member_function_pointer);
      return *this;
  }

  void Bind(ReturnType (*p0)(PARAMS)) {
      Clean();
      call = new hidden::CallStaticFunction<templateICALLS>(p0);
  }

  template <class ObjectType>
  void Bind(ObjectType* p0,ReturnType (ObjectType::*p1)(PARAMS)) {
      Clean();
      call = new hidden::CallMemberFunction<ObjectType,templateICALLS>(p0,p1);
  }

  void UnBind() {
      Clean();
  }

  ReturnType operator()(PARAMSwithVARS) const {
      return (*call)(VARS);
  }

 protected:
 private:
  void Clean() {
      if (call != null) {
          delete call;
      }
  }
  hidden::CallBase<templateICALLS>* call;
};

/*********************************************************************
Struct Name	: FunctionList
Description	: same functionality as the function class, along with
              ability to maintain list of functions and be able to 
              call them all.
*********************************************************************/
template <templatePARAMS>
class FunctionList {
 public:
  FunctionList() {
      calls.clear();
  }

  ~FunctionList() {
      Clean();
  }

  FunctionList& operator=(void (*p0)(PARAMS)) {
      Clean();
      Bind(p0);
      return *this;
  }

  template <class ObjectType>
  FunctionList& operator=(const pair<ObjectType,templateICALLS>& p0) {
      Clean();
      Bind<ObjectType>(p0.object_pointer,p0.member_function_pointer);
      return *this;
  }


  FunctionList& operator+=(void (*p0)(PARAMS)) {
      Bind(p0);
      return *this;
  }

  template <class ObjectType>
  FunctionList& operator+=(const pair<ObjectType,templateICALLS>& p0) {
      Bind<ObjectType>(p0.object_pointer,p0.member_function_pointer);
      return *this;
  }

  FunctionList& operator-=(void (*p0)(PARAMS)) {
    if (calls[p0] != null) {
        delete calls[p0];
        calls[p0] = null;
        calls.erase(calls.find(p0));
    }
    return *this;
  }

  //check += , make it even
  template <class ObjectType>
  FunctionList& operator-=(const pair<ObjectType,templateICALLS>& p0) {
      union
      {
          void (ObjType::*mf)(PARAMS);
          void* mfptr;
      }x;

      x.mf = p0.mfp;
      void* mapptr = x.mfptr;
      if (calls[mapptr] != null)
      {
          delete calls[mapptr];
          calls[mapptr] = null;
          calls.erase(calls.find(mapptr));
      }
      return *this;
  }

  void Bind(void (*p0)(PARAMS)) {
      if (calls[p0] == null)
          calls[p0] = new hidden::CallStaticFunction<templateICALLS>(p0funcptr);
  }

  template <class ObjType>
  void Bind(ObjType* p0,void (ObjType::*p1)(PARAMS)) {
    //horrible cast, as they say..
    union {
        struct
        {
            ObjType* op;
            void (ObjType::*mf)(PARAMS);
        }y;
        void* mfptr;
    } x;

    x.y.op=p0;
    x.y.mf = p1;
    void* mapptr = x.mfptr;
    if (calls[mapptr] == null)
      calls[mapptr] = new hidden::CallMemberFunction<ObjType,templateICALLS>(p0,p1);
  }

  void operator()(PARAMSwithVARS) {
    std::map<void*, hidden::CallBase<templateICALLS>* >::iterator i;
    for (i = calls.begin(); i != calls.end(); ++i)   {
        (*i->second)(VARS);
    }
  }

 protected:
 private:
  void Clean() {
      std::map<void*, hidden::CallBase<templateICALLS>* >::iterator i;

      for (i = calls.begin(); i != calls.end(); ++i) {
          delete i->second;
      }

      calls.clear();

  }
  std::map<void*, hidden::CallBase<templateICALLS>* > calls;
};

}
}
}