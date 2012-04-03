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
#pragma once

#include "../types.h"

#define PARAM(n)			P##n##Type
#define VAR(n)				p##n
#define PARAMVAR(n)			PARAM(n) VAR(n)
#define RETTYPE				ReturnType 


#define PARAMS 
#define VARS 
#define PARAMSwithVARS 
#define templatePARAMS typename RETTYPE
#define templateICALLS RETTYPE
#define PNAMESPACE none
#include "delegation_template.h"
#undef PARAMS 
#undef VARS 
#undef PARAMSwithVARS 
#undef templatePARAMS
#undef templateICALLS
#undef PNAMESPACE



#define PARAMS PARAM(0)
#define VARS VAR(0)
#define PARAMSwithVARS PARAMVAR(0)
#define templatePARAMS typename RETTYPE,typename PARAM(0)
#define templateICALLS RETTYPE, PARAMS
#define PNAMESPACE one
#include "delegation_template.h"
#undef PARAMS 
#undef VARS 
#undef PARAMSwithVARS 
#undef templatePARAMS
#undef templateICALLS
#undef PNAMESPACE



#define PARAMS PARAM(0),PARAM(1)
#define VARS VAR(0),VAR(1)
#define PARAMSwithVARS PARAMVAR(0),PARAMVAR(1)
#define templatePARAMS typename RETTYPE,typename PARAM(0),typename PARAM(1)
#define templateICALLS RETTYPE, PARAMS
#define PNAMESPACE two
#include "delegation_template.h"
#undef PARAMS 
#undef VARS 
#undef PARAMSwithVARS 
#undef templatePARAMS
#undef templateICALLS
#undef PNAMESPACE




#define PARAMS PARAM(0),PARAM(1),PARAM(2)
#define VARS VAR(0),VAR(1),VAR(2)
#define PARAMSwithVARS PARAMVAR(0),PARAMVAR(1),PARAMVAR(2)
#define templatePARAMS typename RETTYPE,typename PARAM(0),typename PARAM(1),typename PARAM(2)
#define templateICALLS RETTYPE, PARAMS
#define PNAMESPACE three
#include "delegation_template.h"
#undef PARAMS 
#undef VARS 
#undef PARAMSwithVARS 
#undef templatePARAMS
#undef templateICALLS
#undef PNAMESPACE