#ifndef __INTERNAL_FLASH_H
#define __INTERNAL_FLASH_H

#include "main.h"

void Write_Flash( uint16_t *buf , uint8_t num_save , uint8_t start_add );
uint16_t Read_Flash(uint32_t Address);


#endif /* __INTERNAL_FLASH_H */
