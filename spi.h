#ifndef _SPIFUNCS_H__
#define _SPIFUNCS_H__

//SPI configuration (Platform dependent)

#if defined(__AVR_ATmega324A__) || defined(__AVR_ATmega324P__) || defined(__AVR_ATmega324PA__)
// renaming SPI registers and bits for unifying
#define SPCR SPCR0
#define SPR0 SPR00
#define SPR1 SPR10
#define CPHA CPHA0
#define CPOL CPOL0
#define MSTR MSTR0
#define DORD DORD0
#define SPE  SPE0
#define SPIE SPIE0

#define SPSR  SPSR0
#define SPI2X SPI2X0
#define WCOL  WCOL0
#define SPIF  SPIF0

#define SPDR SPDR0
#endif


#if defined(__AVR_ATmega328__) || defined(__AVR_ATmega328P__)
#warning "Using ATmega328 SPI pins"

#define SPI_DDR   DDRB
#define SPI_PORT  PORTB
#define SPI_SS    2
#define SPI_MOSI  3
#define SPI_MISO  4
#define SPI_SCK   5

#elif defined(__AVR_ATmega32__)  || \
      defined(__AVR_ATmega324A__) || defined(__AVR_ATmega324P__) || defined(__AVR_ATmega324PA__) || \
      defined(__AVR_ATmega644__) || defined(__AVR_ATmega644P__) || \
      defined(__AVR_ATmega1284__) || defined(__AVR_ATmega1284P__)
#warning "Using ATmega32/324/644/1284 SPI pins"

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
