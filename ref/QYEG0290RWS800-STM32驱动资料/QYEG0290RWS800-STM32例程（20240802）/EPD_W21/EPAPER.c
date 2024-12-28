#include "epaper.h"

extern unsigned char Epaper_border;
void driver_delay_xms(unsigned long xms)	
{	
    unsigned long i = 0 , j=0;

    for(j=0;j<xms;j++)
	{
        for(i=0; i<256*40; i++);
    }
}



void Epaper_Spi_WriteByte(unsigned char TxData)
{				   			 
	unsigned char TempData;
	unsigned char scnt;
	TempData=TxData;

  EPD_W21_CLK_0;  
	for(scnt=0;scnt<8;scnt++)
	{ 
		if(TempData&0x80)
		  EPD_W21_MOSI_1 ;
		else
		  EPD_W21_MOSI_0 ;
		EPD_W21_CLK_1;  
	  EPD_W21_CLK_0;  
		TempData=TempData<<1;
  }
}



void Epaper_READBUSY(void)
{ 
  while(1)
  {	 //=1 BUSY
     if(isEPD_W21_BUSY==0) break;;
  }  
}



void Epaper_Write_Command(unsigned char cmd)
{
	EPD_W21_CS_1;
	EPD_W21_CS_0;
	EPD_W21_DC_0;  // D/C#   0:command  1:data

	Epaper_Spi_WriteByte(cmd);
	EPD_W21_CS_1;
}



void Epaper_Write_Data(unsigned char data)
{
	EPD_W21_CS_1;
	EPD_W21_CS_0;
	EPD_W21_DC_1;  // D/C#   0:command  1:data

	Epaper_Spi_WriteByte(data);
	EPD_W21_CS_1;
}



/////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////

void EPD_HW_Init(unsigned char direction) //Electronic paper initialization
{
	int XStart,XEnd,YStart_L,YStart_H,YEnd_L,YEnd_H;	
	int data_entry_mode;		
	
	XStart=0x00;
	XEnd=(EPD_HEIGHT/8-1);
	
	if (direction==Hor)
			{
				data_entry_mode=0x01;		//Y decrement, X increment				
				YStart_L=(EPD_WIDTH-1)%256;
				YStart_H=(EPD_WIDTH-1)/256;
				YEnd_L=0x00;
				YEnd_H=0x00;
			}			
	
	if (direction==Ver)
			{
				data_entry_mode=0x03;		//Y increment, X increment
				YStart_L=0x00;
				YStart_H=0x00;
				YEnd_L=(EPD_WIDTH-1)%256;
				YEnd_H=(EPD_WIDTH-1)/256;
			}
			
	EPD_W21_Init();							//hard reset 

	Epaper_READBUSY();
	Epaper_Write_Command(0x12); // soft reset
	Epaper_READBUSY();

	Epaper_Write_Command(0x01); //Driver output control      
	Epaper_Write_Data((EPD_WIDTH-1)%256);
	Epaper_Write_Data((EPD_WIDTH-1)/256);
	Epaper_Write_Data(0x00);
	
	Epaper_Write_Command(0x11); //data entry mode       
	Epaper_Write_Data(data_entry_mode);		

	Epaper_Write_Command(0x3C); //BorderWavefrom
	Epaper_Write_Data(0x05);	
	
	Epaper_Write_Command(0x21); //Display update control(Available Source from S8 to S167)      
	Epaper_Write_Data(0x00);	
	Epaper_Write_Data(0x80);		

	Epaper_Write_Command(0x44); //set Ram-X address start/end position   
	Epaper_Write_Data(XStart);		
	Epaper_Write_Data(XEnd);    

	Epaper_Write_Command(0x45); //set Ram-Y address start/end position          
	Epaper_Write_Data(YStart_L);   	
	Epaper_Write_Data(YStart_H);		
	Epaper_Write_Data(YEnd_L);		
	Epaper_Write_Data(YEnd_H); 
	
  Epaper_Write_Command(0x18); //Temperature Sensor Selection
	Epaper_Write_Data(0x80);	  //Internal temperature sensor

	Epaper_Write_Command(0x4E);   // set RAM x address count
	Epaper_Write_Data(XStart);
	Epaper_Write_Command(0x4F);   // set RAM y address count
	Epaper_Write_Data(YStart_L);
	Epaper_Write_Data(YStart_H);
	Epaper_READBUSY();
}


void EPD_W21_Init(void)
{
	EPD_W21_RST_0;     
	driver_delay_xms(100); 
	EPD_W21_RST_1; 							//hard reset  
	driver_delay_xms(100); 
}




//////////////////////////////All screen update////////////////////////////////////////////
void EPD_ALL_image(const unsigned char *datas_BW,const unsigned char *datas_RW)
{
   int i;
    Epaper_Write_Command(0x24);   //write RAM for black(0)/white (1)
   for(i=0;i<ALLSCREEN_GRAGHBYTES;i++)
   {               
     Epaper_Write_Data(*datas_BW);
			datas_BW++;
   }
	 
    Epaper_Write_Command(0x26);   //write RAM for white(0)/red (1)
   for(i=0;i<ALLSCREEN_GRAGHBYTES;i++)
   {               
     Epaper_Write_Data(*datas_RW);
			datas_RW++;
   }	 
	 
   EPD_Update_And_DeepSleep();	 
}




void EPD_SetRAMValue_BaseMap(const unsigned char *datas_BW,const unsigned char *datas_RED)
{
   int i;
	const unsigned char  *datas_flag;   
	datas_flag=datas_BW;	
	
    Epaper_Write_Command(0x24);   //write RAM for black(0)/white (1)
   for(i=0;i<ALLSCREEN_GRAGHBYTES;i++)
   {               
     Epaper_Write_Data(*datas_BW);
			datas_BW++;
   }
	 
    Epaper_Write_Command(0x26);   //write RAM for white(0)/red (1)
   for(i=0;i<ALLSCREEN_GRAGHBYTES;i++)
   {               
     Epaper_Write_Data(*datas_RED);
			datas_RED++;
   }	 
	 
   EPD_Update_BaseMap();	 

	 	datas_BW=datas_flag;
    Epaper_Write_Command(0x26);   //write RAM for black(0)/white (1)
   for(i=0;i<ALLSCREEN_GRAGHBYTES;i++)
   {               
     Epaper_Write_Data(*datas_BW);
			datas_BW++;
   }
}	




void EPD_Update_BaseMap(void)
{   
  Epaper_Write_Command(0x1A); 
  Epaper_Write_Data(0x19);   	
  Epaper_Write_Command(0x22); 
  Epaper_Write_Data(0xD7);   
  Epaper_Write_Command(0x20); 
  Epaper_READBUSY();  	
}


/////////////////////////////////////////////////////////////////////////////////////////
void EPD_Update_And_DeepSleep(void)
{   
  Epaper_Write_Command(0x1A); 
  Epaper_Write_Data(0x19);   	
  Epaper_Write_Command(0x22); 
  Epaper_Write_Data(0xD7);   
  Epaper_Write_Command(0x20); 
  Epaper_READBUSY();  	
	
  Epaper_Write_Command(0x10); //enter deep sleep
  Epaper_Write_Data(0x01); 
  driver_delay_xms(100);	
}



void EPD_Part_Update_And_DeepSleep(void)
{
	Epaper_Write_Command(0x22); 
	Epaper_Write_Data(0xFF);   
	Epaper_Write_Command(0x20); 
	Epaper_READBUSY(); 	
	
	Epaper_Write_Command(0x10); //enter deep sleep
	Epaper_Write_Data(0x01); 
	driver_delay_xms(10);	
}



/////////////////////////////////Single display////////////////////////////////////////////////
void EPD_WhiteScreen_Red(void)

{
   int i;
    Epaper_Write_Command(0x24);   //write RAM for black(0)/white (1)
	for(i=0;i<ALLSCREEN_GRAGHBYTES;i++)
  {
			Epaper_Write_Data(0xff);
  }
	
    Epaper_Write_Command(0x26);   //write RAM for red(1)/white (0)
	for(i=0;i<ALLSCREEN_GRAGHBYTES;i++)
  {
			Epaper_Write_Data(0xff);
  }
	
	EPD_Update_And_DeepSleep();
}



void EPD_WhiteScreen_Black(void)

{
   int i;
    Epaper_Write_Command(0x24);   //write RAM for black(0)/white (1)
	for(i=0;i<ALLSCREEN_GRAGHBYTES;i++)
  {
			Epaper_Write_Data(0x00);
  }
	
    Epaper_Write_Command(0x26);   //write RAM for red(1)/white (0)
	for(i=0;i<ALLSCREEN_GRAGHBYTES;i++)
  {
			Epaper_Write_Data(0x00);
  }
	
		EPD_Update_And_DeepSleep();
}




void EPD_WhiteScreen_White(void)

{
   int i;
    Epaper_Write_Command(0x24);   //write RAM for black(0)/white (1)
	for(i=0;i<ALLSCREEN_GRAGHBYTES;i++)
  {
			Epaper_Write_Data(0xff);
  }
	
    Epaper_Write_Command(0x26);   //write RAM for red(1)/white (0)
	for(i=0;i<ALLSCREEN_GRAGHBYTES;i++)
  {
			Epaper_Write_Data(0x00);
  }
	
	   EPD_Update_And_DeepSleep();
	
}




///////////////////////////Part update//////////////////////////////////////////////
//v和PART_Height 必须是8的整数倍。
void EPD_multiple_Part(int h_start,int v_start,const unsigned char * digit_1,const unsigned char * digit_2,const unsigned char * digit_3,const unsigned char * digit_4)
{

	int i;  
	int vstart,vend,hstart_1,hstart_H1,hstart_L1,hend_1,hend_H1,hend_L1;
	int hstart_2,hstart_H2,hstart_L2,hend_2,hend_H2,hend_L2;
	int hstart_3,hstart_H3,hstart_L3,hend_3,hend_H3,hend_L3;
	int hstart_4,hstart_H4,hstart_L4,hend_4,hend_H4,hend_L4;	

//第一位数字显示区域和内存区域设置	
	vstart=v_start/8;						//转换成字节
	vend=vstart+H_digit/8-1; 

	hstart_1=295-h_start;
		hstart_H1=hstart_1/256;
		hstart_L1=hstart_1%256;

	hend_1=hstart_1-W_digit+1;
		hend_H1=hend_1/256;
		hend_L1=hend_1%256;		
	
//第二位数字显示区域和内存区域设置	
	hstart_2=hend_1-1;
		hstart_H2=hstart_2/256;
		hstart_L2=hstart_2%256;

	hend_2=hstart_2-W_digit+1;
		hend_H2=hend_2/256;
		hend_L2=hend_2%256;	
		
//第三位数字显示区域和内存区域设置	
	hstart_3=hend_2-W_dot-1;
		hstart_H3=hstart_3/256;
		hstart_L3=hstart_3%256;

	hend_3=hstart_3-W_digit+1;
		hend_H2=hend_3/256;
		hend_L2=hend_3%256;	
		
//第四位数字显示区域和内存区域设置	
	hstart_4=hend_3-1;
		hstart_H4=hstart_4/256;
		hstart_L4=hstart_4%256;

	hend_4=hstart_4-W_digit+1;
		hend_H4=hend_4/256;
		hend_L4=hend_4%256;	

//第一位数字
	Epaper_Write_Command(0x44);       // set RAM x address start/end
	Epaper_Write_Data(vstart);    		// RAM x address start;
	Epaper_Write_Data(vend);    			// RAM x address end
	Epaper_Write_Command(0x45);       // set RAM y address start/end
	Epaper_Write_Data(hstart_L1);    	// RAM y address start Low
	Epaper_Write_Data(hstart_H1);    	// RAM y address start High
	Epaper_Write_Data(hend_L1);    		// RAM y address end Low
	Epaper_Write_Data(hend_H1);    		// RAM y address end High


	Epaper_Write_Command(0x4E);   		// set RAM x address count
	Epaper_Write_Data(vstart); 
	Epaper_Write_Command(0x4F);   		// set RAM y address count
	Epaper_Write_Data(hstart_L1);
	Epaper_Write_Data(hstart_H1);
	Epaper_READBUSY();	
	
	 Epaper_Write_Command(0x24);   //Write Black and White image to RAM
	
		for(i=0;i<W_digit*H_digit/8;i++)
			{                         
				Epaper_Write_Data(*digit_1);
				digit_1++;
			}
			
//第二位数字
	Epaper_Write_Command(0x44);       // set RAM x address start/end
	Epaper_Write_Data(vstart);    		// RAM x address start;
	Epaper_Write_Data(vend);    			// RAM x address end
	Epaper_Write_Command(0x45);       // set RAM y address start/end
	Epaper_Write_Data(hstart_L2);    	// RAM y address start Low
	Epaper_Write_Data(hstart_H2);    	// RAM y address start High
	Epaper_Write_Data(hend_L2);    		// RAM y address end Low
	Epaper_Write_Data(hend_H2);    		// RAM y address end High


	Epaper_Write_Command(0x4E);   		// set RAM x address count
	Epaper_Write_Data(vstart); 
	Epaper_Write_Command(0x4F);   		// set RAM y address count
	Epaper_Write_Data(hstart_L2);
	Epaper_Write_Data(hstart_H2);
	Epaper_READBUSY();	
	
	 Epaper_Write_Command(0x24);   //Write Black and White image to RAM
	
		for(i=0;i<W_digit*H_digit/8;i++)
			{                         
				Epaper_Write_Data(*digit_2);
				digit_2++;
			}

//第三位数字
	Epaper_Write_Command(0x44);       // set RAM x address start/end
	Epaper_Write_Data(vstart);    		// RAM x address start;
	Epaper_Write_Data(vend);    			// RAM x address end
	Epaper_Write_Command(0x45);       // set RAM y address start/end
	Epaper_Write_Data(hstart_L3);    	// RAM y address start Low
	Epaper_Write_Data(hstart_H3);    	// RAM y address start High
	Epaper_Write_Data(hend_L3);    		// RAM y address end Low
	Epaper_Write_Data(hend_H3);    		// RAM y address end High


	Epaper_Write_Command(0x4E);   		// set RAM x address count
	Epaper_Write_Data(vstart); 
	Epaper_Write_Command(0x4F);   		// set RAM y address count
	Epaper_Write_Data(hstart_L3);
	Epaper_Write_Data(hstart_H3);
	Epaper_READBUSY();	
	
	 Epaper_Write_Command(0x24);   //Write Black and White image to RAM
	
		for(i=0;i<W_digit*H_digit/8;i++)
			{                         
				Epaper_Write_Data(*digit_3);
				digit_3++;
			}

//第四位数字
	Epaper_Write_Command(0x44);       // set RAM x address start/end
	Epaper_Write_Data(vstart);    		// RAM x address start;
	Epaper_Write_Data(vend);    			// RAM x address end
	Epaper_Write_Command(0x45);       // set RAM y address start/end
	Epaper_Write_Data(hstart_L4);    	// RAM y address start Low
	Epaper_Write_Data(hstart_H4);    	// RAM y address start High
	Epaper_Write_Data(hend_L4);    		// RAM y address end Low
	Epaper_Write_Data(hend_H4);    		// RAM y address end High


	Epaper_Write_Command(0x4E);   		// set RAM x address count
	Epaper_Write_Data(vstart); 
	Epaper_Write_Command(0x4F);   		// set RAM y address count
	Epaper_Write_Data(hstart_L4);
	Epaper_Write_Data(hstart_H4);
	Epaper_READBUSY();	
	
	 Epaper_Write_Command(0x24);   //Write Black and White image to RAM
	
		for(i=0;i<W_digit*H_digit/8;i++)
			{                         
				Epaper_Write_Data(*digit_4);
				digit_4++;
			}			
}	


//////////////////////////////////////////////////////////////////////////////////////
