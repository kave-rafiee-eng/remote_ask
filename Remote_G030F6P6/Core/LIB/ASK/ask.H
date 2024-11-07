#ifndef __ASK_H
#define __ASK_H

#include "main.h"

#define 	Min_Pulse_Len	200 	/* In us */
#define 	Max_Pulse_Len	15000	/* In us*/

#define IS_Valid_Pulse_Len(T1,T2)		((T1 > Min_Pulse_Len) && (T2 < Max_Pulse_Len))
#define IS_Sync_Start_Pulse(T1,T2)		(T2 > (T1*29))
#define Bit_IS_Zero(T1,T2)				(T2 > (T1*2))

void Get_Remote_Code(uint8_t *Code);
	uint8_t	IS_Recive_Valid_Remote(void);
		uint16_t Stop_Read_timer(void);
			uint16_t Read_timer(void);
				void Stop_Timer(void);
					void Start_Timer(void);

#endif /* __ASK_H */
