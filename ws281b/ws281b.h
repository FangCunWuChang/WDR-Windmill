#ifndef _WS281b_H
#define _WS281b_H



#include "main.h"
//#include "delay.h"

/*
#define PIXEL_NUM_ARROW  419
#define PIXEL_NUM_SORROUNDING 419
#define GRB  24   //3*8
#define NUM_ARROW (24 * PIXEL_NUM_ARROW + 250)        // Reset 280us / 1.25us = 224
#define NUM_SORROUNDING (24 * PIXEL_NUM_SORROUNDING + 250)
#define WS1 		133//
#define WS0  	42//
*/

/*
typedef enum//箭头灯条
{
	 Arrow_Light_Bar_1 = DATA_A0_Pin ,
	 Arrow_Light_Bar_2 = DATA_B0_Pin ,
	 Arrow_Light_Bar_3 = DATA_C0_Pin ,
	 Arrow_Light_Bar_4 = DATA_D0_Pin ,
	 Arrow_Light_Bar_5 = DATA_E0_Pin ,
	 Arrow_Light_Bar_reserve = DATA_reserve_Pin, 

}Arrow_Light_Bar_e;

typedef enum//周围灯条
{
	 Surrounding_Light_Strip_1 = DATA_A1_Pin ,
	 Surrounding_Light_Strip_2 = DATA_B1_Pin ,
	 Surrounding_Light_Strip_3 = DATA_C1_Pin ,
	 Surrounding_Light_Strip_4 = DATA_D1_Pin ,
	 Surrounding_Light_Strip_5 = DATA_E1_Pin ,
	 Surrounding_Light_Strip_reserve = DATA_res1_Pin, 

}Surrounding_Light_Strip_e;
*/

/*
extern uint16_t send_Buf_Arrow[NUM_ARROW];
extern uint16_t send_Buf_Surrounding[NUM_SORROUNDING];
*/

/*
void WS_Load_Arrow(TIM_HandleTypeDef* htim, uint32_t Channel );
void WS_Load_Sorrounding(TIM_HandleTypeDef* htim, uint32_t Channel );
void WS_Load_ALL_Arrow(void);
void WS_Load_ALL_Sorrounding(void);
void WS_OpenAll(void);
void WS_CloseAll(void);
void WS_WriteAll_RGB(uint32_t color);
void WS_Write_RGB_Arrow(uint32_t color,TIM_HandleTypeDef* htim, uint32_t Channel);
void WS_Write_RGB_Sorrounding(uint32_t color,TIM_HandleTypeDef* htim, uint32_t Channel);
void WS_control_Arrows(uint32_t color,Arrow_Light_Bar_e Arrow_Light_Bar_n);
void WS_control_Surrounding(uint32_t color,Surrounding_Light_Strip_e Surrounding_Light_Strip_n);
*/

//void WS_WaterFall_Light(TIM_HandleTypeDef* htim, uint32_t Channel);
//void WS_WaterFall_ALL_Light(void);




/**
 * @name                Lite Version
 * @brief               The Lite Version of the code above this.
 * @authors             ZiYu Liu, Wu Chang
 *
 * @{
 */

#define PIXEL_NUM_LED       425
#define NUM_LED             (24 * PIXEL_NUM_LED + 250)        // Reset 280us / 1.25us = 224

#define WS1 		        133//
#define WS0  	            42//

extern uint16_t send_Buf_LED[NUM_LED];

void WS_Load_LED(TIM_HandleTypeDef* htim, uint32_t channel);
void WS_Write_RGB_LED(const uint8_t* buffer, int sizeLED, TIM_HandleTypeDef* htim, uint32_t channel);

/**
 * @}                   Lite Version
 */




/**
 * @name                ws281b2 Extension
 * @brief               The extension functions for ws281b2 lib.
 * @attention           The code in this file is not written by me except for this block.
 * @author              Wu Chang
 *
 * @{
 */

/**
 * @brief               Send buffered data through DMA.
 *
 * @param buffer        The data buffer.
 * @param sizeLED       The size of the LED buffer.
 * @param htim          The TIM handle.
 * @param Channel       The TIM channel.
 */
void WS_write_RGB(const void* buffer, int sizeLED, TIM_HandleTypeDef* htim, uint32_t channel);

/**
 * @}                   ws281b2 Extension
 */

#endif
