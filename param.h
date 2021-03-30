#ifndef _MID_PARAM_TY_H
#define _MID_PARAM_TY_H


typedef struct _Param
{
	uint32_t first_word;
	uint32_t fdcBaseData[2][100];
}Param;

extern Param param;

void Read_Param(void);
uint32_t Save_Param(void);
#endif

