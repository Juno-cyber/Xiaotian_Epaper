#include "stm32f10x.h"
#include "epaper.h" 
#include "picture.h"
ErrorStatus HSEStartUpStatus;

/* Private function prototypes -----------------------------------------------*/
void RCC_Configuration(void);
void NVIC_Configuration(void);
void GPIO_Configuration(void);

/************************************************
************************************************/


						

/////////////////////main//////////////////////////////////////
int main(void)
{

	#ifdef DEBUG
	  debug();
	#endif
	RCC_Configuration();
	//GPIO setting
	GPIO_Configuration();
	 
	  //全屏刷新（横屏显示，FPC朝左）
	  //Full screen refresh
	
		EPD_HW_Init(Hor); //Electronic paper initialization
		EPD_ALL_image(gImage1_BW,gImage1_RED);	//Refresh the picture in full screen
    driver_delay_xms(2000);		
	
		EPD_HW_Init(Hor); 													//Electronic paper initialization（横屏初始化）
	 	EPD_ALL_image(gImage2_BW,gImage2_RED); 	//Refresh the picture in full screen
    driver_delay_xms(2000);		
	
		EPD_HW_Init(Hor); 											//Electronic paper initialization
	 	EPD_SetRAMValue_BaseMap(basemap_BW,basemap_RED); 	//刷新局刷背景，注意此处函数不一样
    driver_delay_xms(1500);			

//////////////////////Partial refresh digital presentation///////////////////
///////////////////////////////////////////局刷
//0613

//注意：单个图片刷新的时候，数据发送完直接执行 EPD_Part_Update();
//      多个图标一起刷新的时候，所有数据全都发送完毕，一次性执行 EPD_Part_Update();
//      y和显示高度必须是8的整数倍。
		
		EPD_HW_Init(Hor); 													//Electronic paper initialization（初始化）
		EPD_multiple_Part(x_digit_1,y_digit,Num[0],Num[6],Num[1],Num[3]); 					
		EPD_Part_Update_And_DeepSleep();
    driver_delay_xms(1500);		


///////////////////////////////////////////
//2748

//采用局刷方式连续刷新多个显示界面的时候，从休眠状态唤醒只需要硬件复位就可以，不要重新初始化。

		EPD_W21_Init();						//hard reset
		EPD_multiple_Part(x_digit_1,y_digit,Num[2],Num[7],Num[4],Num[8]); 		
		EPD_Part_Update_And_DeepSleep();
    driver_delay_xms(1500);		
		
		
//////////////////////////////////////////
//1905

		EPD_W21_Init();						//hard reset
		EPD_multiple_Part(x_digit_1,y_digit,Num[1],Num[9],Num[0],Num[5]); 	
		EPD_Part_Update_And_DeepSleep();
    driver_delay_xms(1500);		


	  //全刷（竖屏）刷新整张图片
		EPD_HW_Init(Ver);  													//Electronic paper initialization（竖屏初始化）	
	 	EPD_ALL_image(gImage3_BW,gImage3_RED); 	//Refresh the picture in full screen
    driver_delay_xms(2000);	


////////////////////////////////////////////////////////////////////////	
		//Clear screen
	
		EPD_HW_Init(Ver); //Electronic paper initialization			
		EPD_WhiteScreen_White();  //Show all white
    driver_delay_xms(1000);			

		EPD_HW_Init(Ver); //Electronic paper initialization			
		EPD_WhiteScreen_White();  //Show all white
}
///////////////////////////////////////////////////////////





/*******************************************************************************
* Function Name  : RCC_Configuration
* Description    : Configures the different system clocks.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void RCC_Configuration(void)
{
 
  // Reset RCC clock configuration
  RCC_DeInit();
 
  // Enable external crystal
  RCC_HSEConfig(RCC_HSE_ON);
  
  // Waiting for the external crystal to stabilize
  HSEStartUpStatus = RCC_WaitForHSEStartUp();
  if(HSEStartUpStatus == SUCCESS)
  {
    // Set the phase-locked loop frequency PLLCLK = 8MHz * 9 = 72 MHz
    RCC_PLLConfig(RCC_PLLSource_HSE_Div1, RCC_PLLMul_9);
  }
  else {
    // Enable internal crystal
    RCC_HSICmd(ENABLE);
    // Waiting for the internal crystal to stabilize
    while(RCC_GetFlagStatus(RCC_FLAG_HSIRDY) == RESET);

    // Set the phase-locked loop frequency PLLCLK = 8MHz/2 * 16 = 64 MHz 
    RCC_PLLConfig(RCC_PLLSource_HSI_Div2,RCC_PLLMul_16);
  }

    // Enable flash prefetch cache
  FLASH_PrefetchBufferCmd(FLASH_PrefetchBuffer_Enable);

  //Set the code delay, FLASH_Latency_2 is two delay cycles
  FLASH_SetLatency(FLASH_Latency_2);
	
  //Set the system total clock
  RCC_HCLKConfig(RCC_SYSCLK_Div1); 

  //Set the high speed device total clock, RCC_HCLK_Div1 is the system clock divided by 1
  RCC_PCLK2Config(RCC_HCLK_Div1); 

  //Set the low speed device total clock, RCC_HCLK_Div2 is the system clock divided by 2
  RCC_PCLK1Config(RCC_HCLK_Div2);
  
  //Enable phase-locked loop multiplier
  RCC_PLLCmd(ENABLE);
  
  // Waiting for the frequency of the phase-locked loop to multiply after frequency stabilization
  while(RCC_GetFlagStatus(RCC_FLAG_PLLRDY) == RESET);
  
  // Select the phase-locked loop clock as the system clock
  RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);
  
  // Waiting for setup to complete
  while(RCC_GetSYSCLKSource() != 0x08);
    
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA |
            RCC_APB2Periph_USART1|RCC_APB2Periph_AFIO,
            ENABLE);

}

/*******************************************************************************
* Function Name  :  GPIO_Configuration
* Description    : Configures the different system clocks.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void GPIO_Configuration(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure;
 	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD|RCC_APB2Periph_GPIOE, ENABLE);//使能PD、E端口时钟
	  				     	
	
	 //CS-->PD8   SCK-->PD9  SDO--->PD10 
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8|GPIO_Pin_9|GPIO_Pin_10;		//Port configuration
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 			
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;		 		
	GPIO_Init(GPIOD, &GPIO_InitStructure);	  	
	
	
	
	 // D/C--->PE15	   RES-->PE14
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_14|GPIO_Pin_15;		//Port configuration
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 			
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;		 		
	GPIO_Init(GPIOE, &GPIO_InitStructure);	  				     		
	
	// BUSY--->PE13
	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_13;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING; //Floating input
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
  GPIO_Init(GPIOE, &GPIO_InitStructure);    //Initialize GPIO
	
	 //LED
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;		//Port configuration
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 			
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;		 		
	GPIO_Init(GPIOE, &GPIO_InitStructure);
}

/*******************************************************************************
* Function Name  : NVIC_Configuration
* Description    : Configures Vector Table base location.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void NVIC_Configuration(void)
{ 
  //NVIC_InitTypeDef NVIC_InitStructure;
  ;
}


#ifdef  DEBUG
/*******************************************************************************
* Function Name  : assert_failed
* Description    : Reports the name of the source file and the source line number
*                  where the assert_param error has occurred.
* Input          : - file: pointer to the source file name
*                  - line: assert_param error line source number
* Output         : None
* Return         : None
*******************************************************************************/
void assert_failed(u8* file, u32 line)
{ 
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

  /* Infinite loop */
  while (1)
  {
  }
}
#endif






