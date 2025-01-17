#ifndef _CPU_TIMER_H
#define _CPU_TIMER_H

//-------------------------------------------CPU_TIMER

#define tbr_g1_TEST 0 
#define tbr_g1_BTN 1 
#define tbr_g1_READ_KEY 2 
#define tbr_g1_MOTOR_LINEAR_CONTOROL 3 
#define tbr_g1_TIME_SAVE 4 
#define tbr_g1_LOCAL 5 
#define tbr_g1_SEC 6 
#define tbr_g1_TIMER_BLANK_CMD 7

//-------------------------------------------SEC
#define tbrc_s1_DISPLAY_SHOW_MODE 1 
#define tbrc_s1_DISPLAY_BRT 2 

//-------------------------------------------CPU_TIMER_CONFIG

#define def_num_tbrc_s1 10
#define def_num_tbr_g1 10
#define def_num_tb_g2 10

//-------------------------------------------

	void ini_cpu_timer();
	void timer_second_manager();
	void timer_basic_manager();

	struct cpu_timer_basic_10bit_auto_reset	 
	{
		volatile unsigned char F_end : 1;
		volatile unsigned char EN : 1;
		volatile unsigned int I_time : 10;
		volatile unsigned int C_set_time : 10;		
	};
	
	struct  cpu_timer_basic_10bit
	{
		volatile unsigned char F_end :1;
		volatile unsigned char EN :1;
		volatile unsigned int I_time :10;		
	};
	
	struct  cpu_timer_8bit_reset_contorol_Seconds
	{
		volatile unsigned char AUTO : 1;
		volatile unsigned char F_end : 1;
		volatile unsigned char EN : 1;
		volatile unsigned int I_time : 10;
		volatile unsigned int C_set_time : 10;		
	};
	
#endif
