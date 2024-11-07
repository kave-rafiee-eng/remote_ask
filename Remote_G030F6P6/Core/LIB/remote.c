#include "main.h"
#include "remote.h"


extern struct cpu_timer_basic_10bit_auto_reset tbr_g1[def_num_tbr_g1];
extern uint8_t Code[4];

extern uint8_t remote_address[5][2];
extern uint16_t buf_temp[10];

extern uint8_t		Revice_Flag;

int btn_push_time=0;
char learn=0;
char blink=0;

int start_time=0;

void remote_manage(){
	
	if( learn == 0 ){
		
		normal_operation();
		
		tbr_g1[tbr_g1_BTN].EN=1; 
		tbr_g1[tbr_g1_BTN].C_set_time = 10;
		if( tbr_g1[tbr_g1_BTN].F_end ){ tbr_g1[tbr_g1_BTN].F_end=0;

			if( start_time<10000 )start_time++;
			
			if( BTN && btn_push_time<10000 )btn_push_time++;
			else btn_push_time=0;	
			
			if( start_time < 300 && btn_push_time > 50){
				clear_all_remote();
				start_time = 10000;
				btn_push_time = 0;
				
			}
			
			if( btn_push_time >= 100 ){
				learn=1;
			}
		}			
			
	}
	
	if( learn == 1 ){
	
			tbr_g1[tbr_g1_TEST].EN=1; 
			tbr_g1[tbr_g1_TEST].C_set_time = 100;
			if( tbr_g1[tbr_g1_TEST].F_end ){ tbr_g1[tbr_g1_TEST].F_end=0;
				blink = 1 - blink;
				led(blink);
			}

			if(IS_Recive_Valid_Remote()){
			
				Get_Remote_Code(Code);
				
				//led(1);
				//opto(1);
				buzzer(1);
				HAL_Delay(500);

				led(0);
				opto(0);
				buzzer(0);
				
				char remote_exist=0; // check exist remote
				for( int j=0; j<NUM_REMOTE; j++ ){
					if( remote_address[j][0] == Code[0] && remote_address[j][1] == Code[1] ){
						remote_exist=1;
					}
				}
				
				if( remote_exist == 0 ){
					
					for( int j=0; j<NUM_REMOTE; j++ ){ // check for free space
						if( remote_address[j][0] == 0 && remote_address[j][1] == 0 ){
							remote_address[j][0] = Code[0];
							remote_address[j][1] = Code[1];
							break;
						}
					}			
					
					for( int j=0; j<NUM_REMOTE; j++ ){ // temp for save
						buf_temp[j*2] = remote_address[j][0];
						buf_temp[j*2+1] = remote_address[j][1];
					}
					Write_Flash(buf_temp,NUM_REMOTE*2,0);				
				
				}
							
				HAL_Delay(2000);
				
				learn = 0;
				Revice_Flag=0;
			}
		
	}
	
}



void normal_operation(){
	
	if(IS_Recive_Valid_Remote()){
			
			Get_Remote_Code(Code);
	
			for( int j=0; j<NUM_REMOTE; j++ ){
					
				if( remote_address[j][0] == Code[0] && remote_address[j][1] == Code[1] ){
					led(1);
					opto(1);
					buzzer(1);
					HAL_Delay(500);

					led(0);
					opto(0);
					buzzer(0);
				}
			}		
				
			HAL_Delay(1000);
				
			learn = 0;
			Revice_Flag=0;
	}	
}

void clear_all_remote(){
	
		led(1);
		buzzer(1);
		HAL_Delay(3000);

		for( int j=0; j<NUM_REMOTE; j++ ){
			remote_address[j][0]=0;
			remote_address[j][1]=0;
		}
			
		for( int j=0; j<NUM_REMOTE*2; j++ ){
			buf_temp[j]=0;
		}
		Write_Flash(buf_temp,NUM_REMOTE*2,0);
		
		led(0);
		opto(0);
		buzzer(0);
	

}

/*

*/
		