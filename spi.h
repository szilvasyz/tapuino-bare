#ifndef _SPIFUNCS_H__
#define _SPIFUNCS_H__

//SPI configuration (Platform dependent)

#if defined(__AVR_ATmega328__) || defined(__AVR_ATmega328P__)
#warning "Using ATmega328 SPI pins"

#define SPI_DDR   DDRB
#define SPI_PORT  PORTB
#define SPI_SS    2
#define SPI_MOSI  3
#define SPI_MISO  4
#define SPI_SCK   5

#elif defined(__AVR_ATmega644__) || defined(__AVR_ATmega644P__) || defined(__AVR_ATmega1284__) || defined(__AVR_ATmega1284P__)
#warning "Using ATmega644/1284 SPI pins"

#define SPI_DDR   DDRB
#define SPI_PORT  PORTB
#define SPI_SS    4
#define SPI_MOSI  5
#define SPI_MISO  6
#define SPI_SCK   7

#else
#error "Unknown chip!"
#endif


// SPI Controls
#define SPI_SELECT()    SPI_PORT &= ~_BV(SPI_SS)   // SPI CS = L
#define SPI_DESELECT()  SPI_PORT |=  _BV(SPI_SS)   
#define SPI_IS_SEL()    !(SPI_PORT & _BV(SPI_SS))  



void SPI_Init();
void SPI_Speed_Slow();
void SPI_Speed_Fast();
void SPI_Send( BYTE data );
BYTE SPI_Recv( void );

#endif
