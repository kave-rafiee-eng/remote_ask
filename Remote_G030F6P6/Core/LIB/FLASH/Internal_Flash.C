#include "main.h"
#include "Internal_Flash.h"

//#define FLASH_START_ADD  0x8007F00
#define FLASH_START_ADD  0x0800F800

void Write_Flash( uint16_t *buf , uint8_t num_save , uint8_t start_add )
{
	
	
	
	
	FLASH_EraseInitTypeDef Erase;
	uint32_t PageError=0;

	Erase.TypeErase = FLASH_TYPEERASE_PAGES;
	Erase.Page = 31;
	Erase.NbPages = 1;
	Erase.Banks = 0;
	//Erase.Banks = 1;
	
	
	HAL_FLASH_Unlock();
	
	__disable_irq();
	__HAL_FLASH_CLEAR_FLAG(FLASH_FLAG_EOP | FLASH_FLAG_BSY | FLASH_FLAG_WRPERR );
	HAL_FLASHEx_Erase(&Erase,&PageError);

	for(uint64_t i=0;i<num_save; i++)
		 HAL_FLASH_Program(FLASH_TYPEPROGRAM_DOUBLEWORD,FLASH_START_ADD+(i*8),buf[i]);
		 
	__enable_irq();
	
	HAL_FLASH_Lock();
	
	

}

uint16_t Read_Flash(uint32_t Address)
{
	uint32_t FlashAdd = FLASH_START_ADD + (Address * 8);
	
	return *(__IO uint16_t *) FlashAdd;
}



