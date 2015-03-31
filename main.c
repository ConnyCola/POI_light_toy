/ POI
#include <msp430.h> 
#include "drivers/spi.h"
#include "defines.h"
#include "font.c"

char msg[] = "Hello World!  ";
uint8_t len = 14;

void printChar(char c);

void send_Byte(char add, char data){
	SPI_OUT_PORT &= ~CS_PIN;
	spi_send(0x40);
	spi_send(add);
	spi_send(data);
	SPI_OUT_PORT |= CS_PIN;
}

void main(void){
    WDTCTL = WDTPW | WDTHOLD;	// Stop watchdog timer
    initSPI();

    send_Byte(0x01, 0x00);

    while(1){
    	int i=0;
    	for(i=0;i<len;i++)
    		printChar(msg[i]);
    }
}

void printChar(char c){
	int i=0;
    for(i=0;i<5;i++){
    	int line = font[(c*5)+i];
    	send_Byte(0x13, line);
    	__delay_cycles(500);
    }
}