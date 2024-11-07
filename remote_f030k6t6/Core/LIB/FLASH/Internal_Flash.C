#include "main.h"
#include "Internal_Flash.h"

#define FLASH_START_ADD  0x8007F00

void Write_Flash( uint16_t *buf , uint8_t num_save , uint8_t start_add )
{
	FLASH_EraseInitTypeDef Erase;
	uint32_t PageError=0;
	//HAL_StatusTypeDef status;

	Erase.TypeErase = FLASH_TYPEERASE_PAGES;
	Erase.PageAddress = FLASH_START_ADD;
	Erase.NbPages = 1;
	
	
	HAL_FLASH_Unlock();
	__HAL_FLASH_CLEAR_FLAG(FLASH_FLAG_EOP | FLASH_FLAG_BSY | FLASH_FLAG_WRPERR | FLASH_FLAG_PGERR);
	HAL_FLASHEx_Erase(&Erase,&PageError);

	for(uint8_t i=0;i<num_save; i++)
		 HAL_FLASH_Program(FLASH_TYPEPROGRAM_HALFWORD,FLASH_START_ADD+(start_add*2)+(i*2),buf[i]);

	HAL_FLASH_Lock();
}

uint16_t Read_Flash(uint32_t Address)
{
	uint32_t FlashAdd = FLASH_START_ADD + (Address * 2);
	
	return *(__IO uint16_t *) FlashAdd;
}
