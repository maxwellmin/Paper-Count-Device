#include "string.h"
#include "stdio.h"

#include "stm32f4xx.h"
#include "param.h"


#define PARAM_FLASH_SECTOR		FLASH_Sector_7
#define PARAM_FLASH_ADDR		0x08060000

uint32_t fdcBaseDataRsvd[100] = 
{	
	24933,25531,26142,26723,27227,27680,28040,28350,28623,28869,
	29104,29331,29537,29738,29919,30076,30206,30329,30442,30551,
	30645,30727,30806,30886,30964,31040,31104,31175,31243,31299,
	31356,31414,31461,31507,31545,31595,31635,31671,31707,31735,
	31768,31799,31820,31855,31885,31915,31937,31963,31991,32008,
};

Param param;

void Read_Param(void)
{
	uint32_t indexs;
	uint32_t i;
	uint32_t *pParam;

	pParam = (uint32_t *)&param;
	indexs = (sizeof(Param)>>2);

	for(i=0;i<indexs;i++)
	{
		*pParam = *((uint32_t *)(PARAM_FLASH_ADDR + (i<<2)));
		pParam++;
	
	}
	
	if(param.first_word != 0x5555AAAA)
	{
		param.first_word = 0x5555AAAA;
		
		memcpy(param.fdcBaseData[0],fdcBaseDataRsvd,sizeof(fdcBaseDataRsvd));
		
		Save_Param();
	}
}

/**
  * @brief  save param
  * @param  None
  * @retval 0;fail;1:ok
  */
uint32_t Save_Param(void)
{
	uint32_t ret = 1;
	uint32_t i = 0;
	uint32_t indexs = 0;
	uint32_t *pParam;

	FLASH_DataCacheCmd(DISABLE);
	FLASH_InstructionCacheCmd(DISABLE);

	/* Unlock the Flash *********************************************************/
	/* Enable the flash control register access */
	FLASH_Unlock();
	  
	/* Erase the user Flash area ************************************************/
	/* area defined by FLASH_USER_START_ADDR and FLASH_USER_END_ADDR */
	
	/* Clear pending flags (if any) */	
	FLASH_ClearFlag( FLASH_FLAG_EOP | FLASH_FLAG_OPERR | FLASH_FLAG_WRPERR | 
					FLASH_FLAG_PGAERR | FLASH_FLAG_PGPERR|FLASH_FLAG_PGSERR); 
	
	FLASH_EraseSector(PARAM_FLASH_SECTOR, VoltageRange_3);
	
	pParam = (uint32_t *)&param;
	indexs = (sizeof(Param)>>2);
	
	for(i=0;i<indexs;i++)
	{
		if (FLASH_ProgramWord((PARAM_FLASH_ADDR + (i<<2)), *pParam) != FLASH_COMPLETE)
		{
			ret = 0;
		}
		
		pParam++;
	}
	
	FLASH_ClearFlag( FLASH_FLAG_EOP | FLASH_FLAG_OPERR | FLASH_FLAG_WRPERR | 
					FLASH_FLAG_PGAERR | FLASH_FLAG_PGPERR|FLASH_FLAG_PGSERR); 
	FLASH_Lock();
	
	FLASH_DataCacheCmd(ENABLE);
	FLASH_InstructionCacheCmd(ENABLE);
	return ret;
}

