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