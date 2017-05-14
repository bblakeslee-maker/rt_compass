/* 
 * STM32L476VGTx LCD display driver.
 * Author:  Bryan Blakeslee
 */

// Include files
#include "lcd.h"

void init_lcd_gpio(void){
  // Clock configuration
	RCC->AHB2ENR |= RCC_AHB2ENR_GPIOAEN;				// GPIOA clock enable
	RCC->AHB2ENR |= RCC_AHB2ENR_GPIOBEN;				// GPIOB clock enable
	RCC->AHB2ENR |= RCC_AHB2ENR_GPIOCEN;				// GPIOC clock enable
	RCC->AHB2ENR |= RCC_AHB2ENR_GPIODEN;				// GPIOD clock enable
    
  // Configure GPIOA pins as AF11
  GPIOA->MODER &= ~GPIO_MODER_MODER6_0;       // PA6 -- SEG3
  GPIOA->AFR[0] |= (AF11 << BSL(6));					// Format: AF11 << shift_macro
  GPIOA->MODER &= ~GPIO_MODER_MODER7_0;       // PA7 -- SEG4
  GPIOA->AFR[0] |= (AF11 << BSL(7));
	GPIOA->MODER &= ~GPIO_MODER_MODER8_0;				// PA8 -- COM0
	GPIOA->AFR[1] |= (AF11 << BSH(8));
	GPIOA->MODER &= ~GPIO_MODER_MODER9_0;		    // PA9 -- COM1
	GPIOA->AFR[1] |= (AF11 << BSH(9));
  GPIOA->MODER &= ~GPIO_MODER_MODER15_0;			// PA15 -- SEG17
	GPIOA->AFR[1] |= (AF11 << BSH(15));
	
	// Configure GPIOB pins as AF11
	GPIOB->MODER &= ~GPIO_MODER_MODER0_0;				// PB0 -- SEG5
	GPIOB->AFR[0] |= (AF11 << BSL(0));					// Format: AF11 << shift_macro
	GPIOB->MODER &= ~GPIO_MODER_MODER1_0;				// PB1 -- SEG6
	GPIOB->AFR[0] |= (AF11 << BSL(1));
	GPIOB->MODER &= ~GPIO_MODER_MODER3_0;				// PB3 -- SEG7
	GPIOB->AFR[0] |= (AF11 << BSL(3));
	GPIOB->MODER &= ~GPIO_MODER_MODER4_0;				// PB4 -- SEG8
	GPIOB->AFR[0] |= (AF11 << BSL(4));
	GPIOB->MODER &= ~GPIO_MODER_MODER5_0;				// PB5 -- SEG9
	GPIOB->AFR[0] |= (AF11 << BSL(5));
	GPIOB->MODER &= ~GPIO_MODER_MODER8_0;		    // PB8 -- SEG16
	GPIOB->AFR[1] |= (AF11 << BSH(8));
	GPIOB->MODER &= ~GPIO_MODER_MODER10_0;		  // PB10 -- SEG10
	GPIOB->AFR[1] |= (AF11 << BSH(10));
  GPIOB->MODER &= ~GPIO_MODER_MODER11_0;      // PB11 -- SEG11
  GPIOB->AFR[1] |= (AF11 << BSH(11));
  GPIOB->MODER &= ~GPIO_MODER_MODER12_0;      // PB12 -- SEG12
  GPIOB->AFR[1] |= (AF11 << BSH(12));
  GPIOB->MODER &= ~GPIO_MODER_MODER13_0;      // PB13 -- SEG13
  GPIOB->AFR[1] |= (AF11 << BSH(13));
  GPIOB->MODER &= ~GPIO_MODER_MODER14_0;      // PB14 -- SEG14
  GPIOB->AFR[1] |= (AF11 << BSH(14));
  GPIOB->MODER &= ~GPIO_MODER_MODER15_0;      // PB15 -- SEG15
	GPIOB->AFR[1] |= (AF11 << BSH(15));
    
	// Configure GPIOC pins as AF11
	GPIOC->MODER &= ~GPIO_MODER_MODER0_0;				// PC0 -- SEG18
	GPIOC->AFR[0] |= (AF11 << BSL(0));					// Format: AF11 << shift_macro
	GPIOC->MODER &= ~GPIO_MODER_MODER1_0;				// PC1 -- SEG19
	GPIOC->AFR[0] |= (AF11 << BSL(1));
	GPIOC->MODER &= ~GPIO_MODER_MODER2_0;				// PC2 -- SEG20
	GPIOC->AFR[0] |= (AF11 << BSL(2));
	GPIOC->MODER &= ~GPIO_MODER_MODER3_0;				// PC3 -- VLCD
	GPIOC->AFR[0] |= (AF11 << BSL(3));
	GPIOC->MODER &= ~GPIO_MODER_MODER4_0;				// PC4 -- SEG22
	GPIOC->AFR[0] |= (AF11 << BSL(4));
  GPIOC->MODER &= ~GPIO_MODER_MODER5_0;       // PC5 -- SEG23
  GPIOC->AFR[0] |= (AF11 << BSL(5));
	GPIOC->MODER &= ~GPIO_MODER_MODER6_0;				// PC6 -- SEG24
	GPIOC->AFR[0] |= (AF11 << BSL(6));
	GPIOC->MODER &= ~GPIO_MODER_MODER7_0;				// PC7 -- SEG25
	GPIOC->AFR[0] |= (AF11 << BSL(7));
	GPIOC->MODER &= ~GPIO_MODER_MODER8_0;				// PC8 -- SEG26
	GPIOC->AFR[1] |= (AF11 << BSH(8));
	GPIOC->MODER &= ~GPIO_MODER_MODER9_0;				// PC9 -- SEG27
	GPIOC->AFR[1] |= (AF11 << BSH(9));
	
	// Configure GPIOD pins as AF11
	GPIOD->MODER &= ~GPIO_MODER_MODER8_0;				// PD8 -- SEG28
	GPIOD->AFR[1] |= (AF11 << BSH(8));
	GPIOD->MODER &= ~GPIO_MODER_MODER9_0;				// PD9 -- SEG29
	GPIOD->AFR[1] |= (AF11 << BSH(9));
	GPIOD->MODER &= ~GPIO_MODER_MODER10_0;			// PD10 -- SEG30
	GPIOD->AFR[1] |= (AF11 << BSH(10));
	GPIOD->MODER &= ~GPIO_MODER_MODER11_0;			// PD11 -- SEG31
	GPIOD->AFR[1] |= (AF11 << BSH(11));
	GPIOD->MODER &= ~GPIO_MODER_MODER12_0;			// PD12 -- SEG32
	GPIOD->AFR[1] |= (AF11 << BSH(12));
	GPIOD->MODER &= ~GPIO_MODER_MODER13_0;			// PD13 -- SEG33
	GPIOD->AFR[1] |= (AF11 << BSH(13));
	GPIOD->MODER &= ~GPIO_MODER_MODER14_0;			// PD14 -- SEG34
	GPIOD->AFR[1] |= (AF11 << BSH(14));
	GPIOD->MODER &= ~GPIO_MODER_MODER15_0;			// PD15 -- SEG35
	GPIOD->AFR[1] |= (AF11 << BSH(15));
	
	USART_Write(USART2, (uint8_t*)"GPIO Done!\n\r", strlen("GPIO Done!\n\r"));
}

void init_lcd_clock(void){
  RCC->APB1ENR1 |= RCC_APB1ENR1_PWREN;                // Power interface clock enable
  PWR->CR1 |= PWR_CR1_DBP;                            // Disable write protection
    
  // Disable RTC register write protection
  RTC->WPR = 0xCA;
  RTC->WPR = 0x53;
    
    // LCD clock enable
	RCC->APB1ENR1 |= RCC_APB1ENR1_LCDEN;				
    
  // Enable SYSCFG
  RCC->APB2ENR |= RCC_APB2ENR_SYSCFGEN;
   
  // Enable LSI and wait for stabilization
  RCC->CSR |= RCC_CSR_LSION;
  while((RCC->CSR & RCC_CSR_LSIRDY) == 0);
    
  // Set LSI as LCD clock source
  RCC->BDCR &= ~RCC_BDCR_RTCSEL;                      // Flush LSI selection bits
  RCC->BDCR |= RCC_BDCR_RTCSEL_1;                     // Select LSI for RTC and LCD
  RCC->BDCR |= RCC_BDCR_RTCEN;                        // Enable RTC
	
	USART_Write(USART2, (uint8_t*)"Clocks Done!\n\r", strlen("Clocks Done!\n\r"));
}

void init_lcd_params(void){
  // Configure LCD controller frame rate, LCDCLK = 32kHz, f_frame = 30.12Hz
	LCD->FCR |= (0x4 << 22);							// Configure 16 bit prescaler (PS = 4)
	LCD->FCR |= (0x1 << 18);							// Configure clock divider (DIV = 1)
    
  // Configure bias
  LCD->CR |= LCD_CR_BIAS_1;                           // Set bias to 1/3
  LCD->CR |= LCD_CR_BUFEN;                            // Turn on output buffers
  
	// Configure duty to 1/2 
	LCD->CR |= LCD_CR_DUTY_0;
    
  // Configure contrast to maximum
  LCD->FCR |= LCD_FCR_CC;
    
  // Turn on internal LCD voltage
  LCD->CR &= ~LCD_CR_VSEL;
    
  // Spin wait for frame control synchronization
  USART_Write(USART2, (uint8_t*)"Waiting for frame sync!\n\r", strlen("Waiting for frame sync!\n\r"));
  while((LCD->SR & LCD_SR_FCRSR) == 0);
  USART_Write(USART2, (uint8_t*)"Frame sync done!\n\r", strlen("Frame sync done!\n\r"));
    
  // Enable LCD
  LCD->CR |= LCD_CR_LCDEN;
    
  // Spin wait until LCD enabled
  USART_Write(USART2, (uint8_t*)"Waiting for LCD ready!\n\r", strlen("Waiting for LCD ready!\n\r"));
  while((LCD->SR & LCD_SR_ENS) == 0);
  USART_Write(USART2, (uint8_t*)"LCD ready done!\n\r", strlen("LCD ready done!\n\r"));
    
  // Spin wait until boost converter ready
  USART_Write(USART2, (uint8_t*)"Waiting for voltage ready!\n\r", strlen("Waiting for voltage ready!\n\r"));
  while((LCD->SR & LCD_SR_RDY) == 0);
  USART_Write(USART2, (uint8_t*)"Voltage done!\n\r", strlen("Voltage done!\n\r"));
}

void init_lcd(void){
	UART2_Init();                                       // Enable UART for debugging
    
  USART_Write(USART2, (uint8_t*)"Start init!\n\r", strlen("Start init!\n\r"));
  
	// Subsystem initialization
  init_lcd_clock();
  init_lcd_gpio();
  init_lcd_params();

	USART_Write(USART2, (uint8_t*)"End init!\n\r", strlen("End init!\n\r"));
}

void clear_display(void){
	clear_slot(SLOT1);
	clear_slot(SLOT2);
	clear_slot(SLOT3);
	clear_slot(SLOT4);
	clear_slot(SLOT5);
	clear_slot(SLOT6);
}

void write_slot(display_slot slot, letter_map map){
	switch(slot){
		case SLOT1:
			// Pixel Map Formula:  ((map & pixel_bit_mask) << (LCD_RAM_bit_location - map_bit_location))
			LCD->RAM[0] |= ((map & MM) << (B23 - B0)) | ((map & MB) << (B22 - B6)) | ((map & ME) << (B4 - B3)) | ((map & MG) << (B3 - B1));
			LCD->RAM[2] |= ((map & MC) << (B23 - B5)) | ((map & MA) << (B22 - B7)) | ((map & MD) << (B4 - B4)) | ((map & MF) << (B3 - B2));
			break;
		case SLOT2:
			LCD->RAM[0] |= ((map & MM) << (B13 - B0)) | ((map & MB) << (B12 - B6)) | ((map & ME) << (B6 - B3)) | ((map & MG) << (B5 - B1));
			LCD->RAM[2] |= ((map & MC) << (B13 - B5)) | ((map & MA) << (B12 - B7)) | ((map & MD) << (B6 - B4)) | ((map & MF) << (B5 - B2));
			break;
		case SLOT3:
			LCD->RAM[0] |= ((map & MM) << (B29 - B0)) | ((map & MB) << (B28 - B6)) | ((map & ME) << (B15 - B3)) | ((map & MG) << (B14 - B1));
			LCD->RAM[2] |= ((map & MC) << (B29 - B5)) | ((map & MA) << (B28 - B7)) | ((map & MD) << (B15 - B4)) | ((map & MF) << (B14 - B2));
			break;
		case SLOT4:
			LCD->RAM[0] |= ((map & ME) << (B31 - B3)) | ((map & MG) << (B30 - B1));
			LCD->RAM[1] |= ((map & MM) << (B1  - B0)) | ((map & MB) >> (B6  - B0));
			LCD->RAM[2] |= ((map & MD) << (B31 - B4)) | ((map & MF) << (B30 - B2));
			// Pixel Map Formula:  ((map & pixel_bit_mask) << (map_bit_location - LCD_RAM_bit_location))
			LCD->RAM[3] |= ((map & MC) >> (B5  - B1)) | ((map & MA) >> (B7  - B0));
			break;
		case SLOT5:
			LCD->RAM[0] |= ((map & MM) << (B25 - B0)) | ((map & MB) << (B24 - B6));
			LCD->RAM[1] |= ((map & ME) << (B3  - B3)) | ((map & MG) << (B2  - B1));
			LCD->RAM[2] |= ((map & MC) << (B25 - B5)) | ((map & MA) << (B24 - B7));
			LCD->RAM[3] |= ((map & MD) >> (B4  - B3)) | ((map & MF) << (B2  - B2));
			break;
		case SLOT6:
			LCD->RAM[0] |= ((map & MG) << (B26 - B1)) | ((map & ME) << (B17 - B3)) | ((map & MB) << (B9 - B6)) | ((map & MM) << (B8 - B0));
			LCD->RAM[2] |= ((map & MF) << (B26 - B2)) | ((map & MD) << (B17 - B4)) | ((map & MA) << (B9 - B7)) | ((map & MC) << (B8 - B5));
			break;
		default:
			break;
	}
}

void clear_slot(display_slot slot){
	switch(slot){
		case SLOT1:
			// Pixel Map Formula:  ((map & pixel_bit_mask) << (LCD_RAM_bit_location - map_bit_location))
			LCD->RAM[0] &= ~((MM << (B23 - B0)) | (MB << (B22 - B6)) | (ME << (B4 - B3)) | (MG << (B3 - B1)));
			LCD->RAM[2] &= ~((MC << (B23 - B5)) | (MA << (B22 - B7)) | (MD << (B4 - B4)) | (MF << (B3 - B2)));
			break;
		case SLOT2:
			LCD->RAM[0] &= ~((MM << (B13 - B0)) | (MB << (B12 - B6)) | (ME << (B6 - B3)) | (MG << (B5 - B1)));
			LCD->RAM[2] &= ~((MC << (B13 - B5)) | (MA << (B12 - B7)) | (MD << (B6 - B4)) | (MF << (B5 - B2)));
			break;
		case SLOT3:
			LCD->RAM[0] &= ~((MM << (B29 - B0)) | (MB << (B28 - B6)) | (ME << (B15 - B3)) | (MG << (B14 - B1)));
			LCD->RAM[2] &= ~((MC << (B29 - B5)) | (MA << (B28 - B7)) | (MD << (B15 - B4)) | (MF << (B14 - B2)));
			break;
		case SLOT4:
			LCD->RAM[0] &= ~((ME << (B31 - B3)) | (MG << (B30 - B1)));
			LCD->RAM[1] &= ~((MM << (B1  - B0)) | (MB >> (B6  - B0)));
			LCD->RAM[2] &= ~((MD << (B31 - B4)) | (MF << (B30 - B2)));
			// Pixel Map Formula:  ((map & pixel_bit_mask) << (map_bit_location - LCD_RAM_bit_location))
			LCD->RAM[3] &= ~((MC >> (B5  - B1)) | (MA >> (B7  - B0)));
			break;
		case SLOT5:
			LCD->RAM[0] &= ~((MM << (B25 - B0)) | (MB << (B24 - B6)));
			LCD->RAM[1] &= ~((ME << (B3  - B3)) | (MG << (B2  - B1)));
			LCD->RAM[2] &= ~((MC << (B25 - B5)) | (MA << (B24 - B7)));
			LCD->RAM[3] &= ~((MD >> (B4  - B3)) | (MF << (B2  - B2)));
			break;
		case SLOT6:
			LCD->RAM[0] &= ~((MG << (B26 - B1)) | (ME << (B17 - B3)) | (MB << (B9 - B6)) | (MM << (B8 - B0)));
			LCD->RAM[2] &= ~((MF << (B26 - B2)) | (MD << (B17 - B4)) | (MA << (B9 - B7)) | (MC << (B8 - B5)));
			break;
		default:
			break;
	}
}

void screen_update(void){
	LCD->SR |= LCD_SR_UDR;
	while((LCD->SR & LCD_SR_UDD) == 0);
	LCD->CLR |= LCD_CLR_UDDC;
}

void dump_map(void){
	int ir, ib;
	char buf[40];
	
	for(ir = 0; ir < 16; ir++){
		for(ib = 0; ib < 32; ib++){
			LCD->RAM[ir] = 0;
			LCD->RAM[ir] |= (1 << ib);
			LCD->SR |= LCD_SR_UDR;
			while((LCD->SR & LCD_SR_UDD) == 0);
			LCD->CLR |= LCD_CLR_UDDC;
			sprintf(buf, "ir = %d, ib = %d\n\r", ir, ib);
			USART_Write(USART2, (uint8_t*)buf, strlen(buf));
			USART_Read(USART2);	
		}
		LCD->RAM[ir] = 0;
	}
}
