#include "ws281b.h"

/*
uint16_t send_Buf_Arrow[NUM_ARROW];
uint16_t send_Buf_Surrounding[NUM_SORROUNDING];
*/

extern TIM_HandleTypeDef htim1;

extern TIM_HandleTypeDef htim2;

extern TIM_HandleTypeDef htim3;

/*
// 启动DMA载入数据
void WS_Load_Arrow(TIM_HandleTypeDef* htim, uint32_t Channel )
{
	HAL_TIM_PWM_Start_DMA(htim, Channel, (uint32_t *)send_Buf_Arrow, NUM_ARROW);
	HAL_Delay(10);
	
}

void WS_Load_Sorrounding(TIM_HandleTypeDef* htim, uint32_t Channel )
{
	HAL_TIM_PWM_Start_DMA(htim, Channel, (uint32_t *)send_Buf_Surrounding, NUM_SORROUNDING);
	HAL_Delay(10);
}
void WS_Load_ALL_Arrow(void)
{
	WS_Load_Arrow(&htim1,TIM_CHANNEL_1);
	WS_Load_Arrow(&htim1,TIM_CHANNEL_2);
	WS_Load_Arrow(&htim1,TIM_CHANNEL_3);
	WS_Load_Arrow(&htim1,TIM_CHANNEL_4);

	WS_Load_Arrow(&htim2,TIM_CHANNEL_1);
	WS_Load_Arrow(&htim2,TIM_CHANNEL_2);//保留端口

}

void WS_Load_ALL_Sorrounding(void)
{

	WS_Load_Sorrounding(&htim2,TIM_CHANNEL_3);
	WS_Load_Sorrounding(&htim2,TIM_CHANNEL_4);
	
	WS_Load_Sorrounding(&htim3,TIM_CHANNEL_1);
	WS_Load_Sorrounding(&htim3,TIM_CHANNEL_2);
	WS_Load_Sorrounding(&htim3,TIM_CHANNEL_3);
	WS_Load_Sorrounding(&htim3,TIM_CHANNEL_4);//保留端口

}
// 关闭所有LED灯
void WS_CloseAll(void)
{
	uint16_t i;

	for (i = 0; i < PIXEL_NUM_ARROW * 24; i++)
		send_Buf_Arrow[i] = WS0; // 写入逻辑0的占空比

	for (i = PIXEL_NUM_ARROW * 24; i < NUM_ARROW; i++)
		send_Buf_Arrow[i] = 0; // 占空比比为0，全为低电平

	for (i = 0; i < PIXEL_NUM_SORROUNDING * 24; i++)
		send_Buf_Surrounding[i] = WS0; // 写入逻辑0的占空比

	for (i = PIXEL_NUM_SORROUNDING * 24; i < NUM_SORROUNDING; i++)
		send_Buf_Surrounding[i] = 0; // 占空比比为0，全为低电平
	
	WS_Load_ALL_Arrow();
	WS_Load_ALL_Sorrounding();
	
}

// 开启所有LED灯(白色)
void WS_OpenAll(void)
{
	uint16_t i;

	for (i = 0; i < PIXEL_NUM_ARROW * 24; i++)
		send_Buf_Arrow[i] = WS1; // 写入逻辑0的占空比

	for (i = PIXEL_NUM_ARROW * 24; i < NUM_ARROW; i++)
		send_Buf_Arrow[i] = 0; // 占空比比为0，全为低电平

	for (i = 0; i < PIXEL_NUM_SORROUNDING * 24; i++)
		send_Buf_Surrounding[i] = WS1; // 写入逻辑0的占空比

	for (i = PIXEL_NUM_SORROUNDING * 24; i < NUM_SORROUNDING; i++)
		send_Buf_Surrounding[i] = 0; // 占空比比为0，全为低电平
	
	WS_Load_ALL_Arrow();
	WS_Load_ALL_Sorrounding();
	
}
*/
/**
 * @brief 全部led灯设置成一样的亮度，其中RGB分别设置
 * WS2812的写入顺序是GRB，高位在前面
*/
/*
void WS_WriteAll_RGB(uint32_t color)
{
	uint16_t i, j;
	uint8_t n_R =(uint8_t)(color >>16); 
	uint8_t n_G =(uint8_t)(color >>8); 
	uint8_t n_B =(uint8_t)color ; 
	uint8_t dat[24];

	// 将RGB数据进行转换
	for (i = 0; i < 8; i++)
	{
		dat[i] = ((n_G & 0x80) ? WS1 : WS0);
		n_G <<= 1;
	}
	for (i = 0; i < 8; i++)
	{
		dat[i + 8] = ((n_R & 0x80) ? WS1 : WS0);
		n_R <<= 1;
	}
	for (i = 0; i < 8; i++)
	{
		dat[i + 16] = ((n_B & 0x80) ? WS1 : WS0);
		n_B <<= 1;
	}

	for (i = 0; i < PIXEL_NUM_ARROW; i++)
	{
		for (j = 0; j < 24; j++)
		{
			send_Buf_Arrow[i * 24 + j] = dat[j];
		}
	}

	for (i = PIXEL_NUM_ARROW * 24; i < NUM_ARROW; i++)
	{
		send_Buf_Arrow[i] = 0; // 占空比为0，全为低电平
	}

	for (i = 0; i < PIXEL_NUM_SORROUNDING; i++)
	{
		for (j = 0; j < 24; j++)
		{
			send_Buf_Surrounding[i * 24 + j] = dat[j];
		}
	}

	for (i = PIXEL_NUM_SORROUNDING * 24; i < NUM_SORROUNDING; i++)
	{
		send_Buf_Surrounding[i] = 0; // 占空比为0，全为低电平
	}
	
	
	WS_Load_ALL_Sorrounding();
	WS_Load_ALL_Arrow();
}
*/
/**
 * @brief 指定led灯设置成一样的亮度，其中RGB分别设置
 * WS2812的写入顺序是GRB，高位在前面
*/
/*
void WS_Write_RGB_Arrow(uint32_t color,TIM_HandleTypeDef* htim, uint32_t Channel)
{
	uint16_t i, j;
	uint8_t n_R =(uint8_t)(color >>16); 
	uint8_t n_G =(uint8_t)(color >>8); 
	uint8_t n_B =(uint8_t)color ;
	uint8_t dat[24];

	// 将RGB数据进行转换
	for (i = 0; i < 8; i++)
	{
		dat[i] = ((n_G & 0x80) ? WS1 : WS0);
		n_G <<= 1;
	}
	for (i = 0; i < 8; i++)
	{
		dat[i + 8] = ((n_R & 0x80) ? WS1 : WS0);
		n_R <<= 1;
	}
	for (i = 0; i < 8; i++)
	{
		dat[i + 16] = ((n_B & 0x80) ? WS1 : WS0);
		n_B <<= 1;
	}

	for (i = 0; i < PIXEL_NUM_ARROW; i++)
	{
		for (j = 0; j < 24; j++)
		{
			send_Buf_Arrow[i * 24 + j] = dat[j];
		}
	}

	for (i = PIXEL_NUM_ARROW * 24; i < NUM_ARROW; i++)
	{
		send_Buf_Arrow[i] = 0; // 占空比为0，全为低电平
	}

	WS_Load_Arrow(htim,Channel);
}

void WS_Write_RGB_Sorrounding(uint32_t color,TIM_HandleTypeDef* htim, uint32_t Channel)
{
	uint16_t i, j;
	uint8_t n_R =(uint8_t)(color >>16); 
	uint8_t n_G =(uint8_t)(color >>8); 
	uint8_t n_B =(uint8_t) color ;
	uint8_t dat[24];

	// 将RGB数据进行转换
	for (i = 0; i < 8; i++)
	{
		dat[i] = ((n_G & 0x80) ? WS1 : WS0);
		n_G <<= 1;
	}
	for (i = 0; i < 8; i++)
	{
		dat[i + 8] = ((n_R & 0x80) ? WS1 : WS0);
		n_R <<= 1;
	}
	for (i = 0; i < 8; i++)
	{
		dat[i + 16] = ((n_B & 0x80) ? WS1 : WS0);
		n_B <<= 1;
	}

	for (i = 0; i < PIXEL_NUM_SORROUNDING; i++)
	{
		for (j = 0; j < 24; j++)
		{
			send_Buf_Surrounding[i * 24 + j] = dat[j];
		}
	}

	for (i = PIXEL_NUM_SORROUNDING * 24; i < NUM_SORROUNDING; i++)
	{
		send_Buf_Surrounding[i] = 0; // 占空比为0，全为低电平
	}

	WS_Load_Sorrounding(htim,Channel);
}
*/
/*-----------------------------------------*/
//void WS_WaterFall_ALL_Light(void)//RM全部灯箭头流动模式
//{
//	uint16_t i,j;
//	for(i=0;i<4;i+=3)
//	{
//		send_Buf[i] =0x0F;
//		send_Buf[i+1]=0x00;
//		send_Buf[i+2]=0x00;
//	}
//	for (j = PIXEL_NUM * 24; j < NUM; j++)
//	{
//		send_Buf[j] = 0; // 占空比为0，全为低电平
//	}
//	WS_Load_ALL();
//	HAL_Delay(100);
//	for(i=0;i<4;i+=3)
//	{
//		send_Buf[i] =0x00;
//		send_Buf[i+1]=0x00;
//		send_Buf[i+2]=0xF0;
//	}
//	for (j = PIXEL_NUM * 24; j < NUM; j++)
//	{
//		send_Buf[j] = 0; // 占空比为0，全为低电平
//	}
//	WS_Load_ALL();

//}
///*-----------------------------------------*/

//void WS_WaterFall_Light(TIM_HandleTypeDef* htim, uint32_t Channel)//指定RM灯箭头流动模式
//{
//	uint16_t i,j;
//	for(i=0;i<4;i+=3)
//	{
//		send_Buf[i] =0x0F;
//		send_Buf[i+1]=0x00;
//		send_Buf[i+2]=0x00;
//	}
//	for (j = PIXEL_NUM * 24; j < NUM; j++)
//	{
//		send_Buf[j] = 0; // 占空比为0，全为低电平
//	}
//	WS_Load_ALL();
//	HAL_Delay(100);
//	for(i=0;i<4;i+=3)
//	{
//		send_Buf[i] =0x00;
//		send_Buf[i+1]=0x00;
//		send_Buf[i+2]=0xF0;
//	}
//	for (j = PIXEL_NUM * 24; j < NUM; j++)
//	{
//		send_Buf[j] = 0; // 占空比为0，全为低电平
//	}
//	WS_Load(htim,Channel);

//}
/*
void WS_control_Arrows(uint32_t color,Arrow_Light_Bar_e Arrow_Light_Bar_n)
{
	TIM_HandleTypeDef* htim;
	uint32_t Channel;
	
	switch(Arrow_Light_Bar_n)
	{
		case Arrow_Light_Bar_1 :
		{
			htim = &htim1;
			Channel = TIM_CHANNEL_1;
			break ;
		}
		case Arrow_Light_Bar_2 :
		{
			htim = &htim1;
			Channel = TIM_CHANNEL_2;
			break ;
		}
		case Arrow_Light_Bar_3 :
		{
			htim = &htim1;
			Channel = TIM_CHANNEL_3;
			break ;
		}
		case Arrow_Light_Bar_4 :
		{
			htim = &htim1;
			Channel = TIM_CHANNEL_4;
			break ;
		}
		case Arrow_Light_Bar_5 :
		{
			htim = &htim2;
			Channel = TIM_CHANNEL_1;
			break ;
		}
		case Arrow_Light_Bar_reserve :
		{
			htim = &htim2;
			Channel = TIM_CHANNEL_2;
			break ;		}
		default :
		{
			break ;
		}
	}
	WS_Write_RGB_Arrow(color,htim,Channel);
}


void WS_control_Surrounding(uint32_t color,Surrounding_Light_Strip_e Surrounding_Light_Strip_n)
{
	TIM_HandleTypeDef* htim;
	uint32_t Channel;
	
	switch(Surrounding_Light_Strip_n)
	{
		case Surrounding_Light_Strip_1 :
		{
			htim = &htim2;
			Channel = TIM_CHANNEL_3;
			break ;
		}
		case Surrounding_Light_Strip_2 :
		{
			htim = &htim2;
			Channel = TIM_CHANNEL_4;
			break ;
		}
		case Surrounding_Light_Strip_3 :
		{
			htim = &htim3;
			Channel = TIM_CHANNEL_1;
			break ;
		}
		case Surrounding_Light_Strip_4 :
		{
			htim = &htim3;
			Channel = TIM_CHANNEL_2;
			break ;
		}
		case Surrounding_Light_Strip_5 :
		{
			htim = &htim3;
			Channel = TIM_CHANNEL_3;
			break ;
		}
		case Surrounding_Light_Strip_reserve :
		{
			htim = &htim3;
			Channel = TIM_CHANNEL_4;
			break ;
		}
		default :
		{
			break ;
		}
	}
	WS_Write_RGB_Sorrounding(color,htim,Channel);
}
*/
//void WS_control_Arrows_WaterFall(Arrow_Light_Bar_e Arrow_Light_Bar_n)
//{
//	TIM_HandleTypeDef* htim;
//	uint32_t Channel;
//	
//	switch(Arrow_Light_Bar_n)
//	{
//		case Arrow_Light_Bar_1 :
//		{
//			htim = &htim1;
//			Channel = TIM_CHANNEL_1;
//			break ;
//		}
//		case Arrow_Light_Bar_2 :
//		{
//			htim = &htim1;
//			Channel = TIM_CHANNEL_2;
//			break ;
//		}
//		case Arrow_Light_Bar_3 :
//		{
//			htim = &htim1;
//			Channel = TIM_CHANNEL_3;
//			break ;
//		}
//		case Arrow_Light_Bar_4 :
//		{
//			htim = &htim1;
//			Channel = TIM_CHANNEL_4;
//			break ;
//		}
//		case Arrow_Light_Bar_5 :
//		{
//			htim = &htim2;
//			Channel = TIM_CHANNEL_1;
//			break ;
//		}
//		case Arrow_Light_Bar_reserve :
//		{
//			htim = &htim2;
//			Channel = TIM_CHANNEL_2;
//			break ;
//		}
//		default :
//		{
//			break ;
//		}
//	}
//		WS_WaterFall_Light(htim,Channel);

//}


void HAL_TIM_PWM_PulseFinishedCallback(TIM_HandleTypeDef *htim)
{

	
	HAL_TIM_PWM_Stop_DMA(&htim1, TIM_CHANNEL_1);
	HAL_TIM_PWM_Stop_DMA(&htim1, TIM_CHANNEL_2);
	HAL_TIM_PWM_Stop_DMA(&htim1, TIM_CHANNEL_3);
	HAL_TIM_PWM_Stop_DMA(&htim1, TIM_CHANNEL_4);
	
	HAL_TIM_PWM_Stop_DMA(&htim2, TIM_CHANNEL_1);
	HAL_TIM_PWM_Stop_DMA(&htim2, TIM_CHANNEL_2);
	HAL_TIM_PWM_Stop_DMA(&htim2, TIM_CHANNEL_3);
	HAL_TIM_PWM_Stop_DMA(&htim2, TIM_CHANNEL_4);
	
	HAL_TIM_PWM_Stop_DMA(&htim3, TIM_CHANNEL_1);
	HAL_TIM_PWM_Stop_DMA(&htim3, TIM_CHANNEL_2);
	HAL_TIM_PWM_Stop_DMA(&htim3, TIM_CHANNEL_3);
	HAL_TIM_PWM_Stop_DMA(&htim3, TIM_CHANNEL_4);
	
	
}

/**
 * @name                Lite Version
 * @brief               The Lite Version of the code above this.
 * @authors             ZiYu Liu, Wu Chang
 *
 * @{
 */

uint16_t send_Buf_LED[NUM_LED];

void WS_Load_LED(TIM_HandleTypeDef* htim, uint32_t channel) {
    HAL_TIM_PWM_Start_DMA(htim, channel, (uint32_t *)send_Buf_LED, NUM_LED);
    HAL_Delay(10);
}

void WS_Write_RGB_LED(const uint8_t* buffer, int sizeLED, TIM_HandleTypeDef* htim, uint32_t channel) {
    for (int index = 0; index < sizeLED; index++) {
        uint8_t n_G = buffer[index * 3 + 0];
        uint8_t n_R = buffer[index * 3 + 1];
        uint8_t n_B = buffer[index * 3 + 2];
        uint8_t dat[24] = { 0 };

        // 将RGB数据进行转换
        for (int i = 0; i < 8; i++) {
            dat[i] = ((n_G & 0x80) ? WS1 : WS0);
            n_G <<= 1;
        }
        for (int i = 0; i < 8; i++) {
            dat[i + 8] = ((n_R & 0x80) ? WS1 : WS0);
            n_R <<= 1;
        }
        for (int i = 0; i < 8; i++) {
            dat[i + 16] = ((n_B & 0x80) ? WS1 : WS0);
            n_B <<= 1;
        }

        for (int i = 0; i < 24; i++) {
            send_Buf_LED[index * 24 + i] = dat[i];
        }
    }

    for (int i = sizeLED * 24; i < NUM_LED; i++)
    {
        send_Buf_LED[i] = 0; // 占空比为0，全为低电平
    }

    WS_Load_LED(htim, channel);
}

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
void WS_write_RGB(const void* buffer, int sizeLED, TIM_HandleTypeDef* htim, uint32_t channel) {
    WS_Write_RGB_LED((const uint8_t*)buffer, sizeLED, htim, channel);
}

/**
 * @}                   ws281b2 Extension
 */
