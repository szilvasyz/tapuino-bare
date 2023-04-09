#include "config.h"
#ifdef LCD_USE_SH1106_OLED_MODULE

#include <string.h>
#include <avr/pgmspace.h>
#include <util/delay.h>
#include "i2c_master.h"
#include "orig8x8-iso8859-2.h"
//#include "orig8x8-iso8859-1.h"
//#include "font8x8.h"

#ifndef LCD_SH1106_COLOFFSET
#define LCD_SH1106_COLOFFSET 0
#endif

#define NUM_COLS  16
#define NUM_ROWS  4

#ifdef LCD_BIG_FONTS
#define BANKS_PER_ROW 2

#ifdef LCD_SH1106_128x32
#define NUM_ROWS  2
#endif

#else
#define BANKS_PER_ROW 1

#ifdef LCD_SH1106_128x64
#define NUM_ROWS  8
#endif

#endif

#define NUM_CHARS NUM_COLS * NUM_ROWS

static uint8_t _addr; // I2C address
static uint8_t _row, _col;
static uint8_t _buffer[NUM_CHARS];
static uint8_t _displayCursor;

void write_raw(uint8_t value, uint8_t cursor);
void sh1106_fillscreen(uint8_t fill);
void sh1106_send_command_start(void);
void sh1106_send_command(uint8_t command);
void sh1106_send_data_start(void);

#define SH1106_LOWCOLUMNADDR       0x00
#define SH1106_HIGHCOLUMNADDR      0x10
#define SH1106_SETPUMPVOLTAGE      0x30
#define SH1106_SETSTARTLINE        0x40
#define SH1106_SETCONTRAST         0x81
#define SH1106_SEGREMAP            0xA0
#define SH1106_DISPLAYALLON        0xA5
#define SH1106_DISPLAYALLON_RESUME 0xA4
#define SH1106_NORMALDISPLAY       0xA6
#define SH1106_REVERSEDISPLAY      0xA7
#define SH1106_SETMULTIPLEX        0xA8
#define SH1106_SETDCDCCONTROL      0xAD
#define SH1106_SETDCDCOFF          0x8A
#define SH1106_SETDCDCON           0x8B
#define SH1106_DISPLAYOFF          0xAE
#define SH1106_DISPLAYON           0xAF
#define SH1106_SETSTARTPAGE        0xB0
#define SH1106_COMSCANINC          0xC0
#define SH1106_COMSCANDEC          0xC8
#define SH1106_SETDISPLAYOFFSET    0xD3
#define SH1106_SETDISPLAYCLOCKDIV  0xD5
#define SH1106_SETPRECHARGE        0xD9
#define SH1106_SETCOMPINS          0xDA
#define SH1106_SETVCOMDESELECT     0xDB
#define SH1106_READMODIFYWRITE     0xE0
#define SH1106_RMWEND              0xEE
#define SH1106_NOP                 0xE3

#define SSD1306_CHARGEPUMP          0x8D
#define SSD1306_MEMORYMODE          0x20


// Init Sequence
const uint8_t sh1106_init_sequence [] PROGMEM = {
  SH1106_DISPLAYOFF,                   // 0xAE Display OFF (sleep mode)
  SH1106_SETDISPLAYCLOCKDIV,   0x80,   // 0xD5 Set display clock divide ratio/oscillator frequency

#if defined LCD_SH1106_128x64  
  SH1106_SETMULTIPLEX,         0x3F,   // 0xA8 Set multiplex ratio (1 to 64)
  SH1106_SETCOMPINS,           0x12,   // 0xDA Set com pins hardware configuration
#elif defined LCD_SH1106_128x32
  SH1106_SETMULTIPLEX,         0x1F,   // 0xA8 Set multiplex ratio (1 to 32)
  SH1106_SETCOMPINS,           0x02,   // 0xDA Set com pins hardware configuration
#endif

  SH1106_SETDISPLAYOFFSET,     0x00,   // 0xD3 Set display offset. 00 = no offset

#ifdef LCD_SH1106_SSD1306INIT
  SSD1306_CHARGEPUMP,          0x14,   // SSD1306_CHARGEPUMP, 0x8D Set DC-DC enable: internal VCC
  SSD1306_MEMORYMODE,          0x10,   // SSD1306_MEMORYMODE, 0x20 Set Memory Addressing Mode
#endif
  
  SH1106_SETSTARTLINE | 0x00,          // 0x40 Set start line address
                                        //      00=Horizontal Addressing Mode; 01=Vertical Addressing Mode;
                                        //      10=Page Addressing Mode (RESET); 11=Invalid
#ifndef LCD_SH1106_UPSIDEDOWN
  SH1106_SEGREMAP | 0x01,              // 0xA1 Set Segment Re-map. A0=address mapped; A1=address 127 mapped. 
  SH1106_COMSCANDEC,                   // 0xC8 Set COM Output Scan Direction - descending
#else
  SH1106_SEGREMAP | 0x00,              // 0xA0 Set Segment Re-map. A0=address mapped; A1=address 127 mapped. 
  SH1106_COMSCANINC,                   // 0xC0 Set COM Output Scan Direction - ascending
#endif

  SH1106_SETCONTRAST,          0x3F,   // 0x81 Set contrast control register
  SH1106_SETPRECHARGE,         0x22,   // 0xD9 Set pre-charge period
  SH1106_SETVCOMDESELECT,      0x35,   // 0xDB Set vcomh 0x20,0.77xVcc
  SH1106_DISPLAYALLON_RESUME,          // 0xA4 Output RAM to Display 0xA4=Output follows RAM content; 0xA5,Output ignores RAM content
  SH1106_NORMALDISPLAY,                // 0xA6 Set display mode. A6=Normal; A7=Inverse
  SH1106_SETSTARTPAGE | 0x00,          // Set Page Start Address for Page Addressing Mode, 0-7
  SH1106_LOWCOLUMNADDR,                // ---set low column address
  SH1106_HIGHCOLUMNADDR,               // ---set high column address
  SH1106_DISPLAYON                     // 0xAF Display ON in normal mode
};


void lcd_init(uint8_t lcd_addr)
{
  uint8_t i;
  _addr = lcd_addr;
  _displayCursor = 0;
  
  i2c_init();
  _delay_ms(100);

  for (i = 0; i < sizeof (sh1106_init_sequence); i++) {
    sh1106_send_command(pgm_read_byte(&sh1106_init_sequence[i]));
  }
  lcd_clear();
}

void lcd_clear() {
  sh1106_fillscreen(0);
  memset(_buffer, 32, NUM_CHARS);  
  _row = 0;
  _col = 0;
}

void lcd_cursor() {
  uint8_t curValue = _buffer[_row * NUM_COLS + _col];
  _displayCursor = 1;
  write_raw(curValue, 1);
}

void lcd_noCursor(){
  uint8_t curValue = _buffer[_row * NUM_COLS + _col];
  _displayCursor = 0;
  write_raw(curValue, 0);
}

void lcd_backlight() {
  
}

void lcd_noBacklight() {
  
}


void write_raw(uint8_t value, uint8_t cursor) {
  uint8_t i, j, v, w1, w2, col, row;
  uint8_t c = value < 32 ? 0 : value - 32;
  uint8_t b[8];
 
  col = (_col << 3) + LCD_SH1106_COLOFFSET; // convert to pixel: character column * 8
  row = BANKS_PER_ROW * _row;
  
  for (i = 0; i < 8; i++)
    b[i] = pgm_read_byte(&font8x8[c * 8 + i]) | (cursor ? 0x80: 0);

  sh1106_send_command_start();
  i2c_write(SH1106_SETSTARTPAGE + row);
  i2c_write((col & 0x0f) | SH1106_LOWCOLUMNADDR);
  i2c_write(((col & 0xf0) >> 4) | SH1106_HIGHCOLUMNADDR);
  sh1106_send_data_start();

  // write 1 column of the character per iteration
  for (i = 0; i < 8; i++)
  {
    v = b[i];
#ifdef LCD_BIG_FONTS
    w1 = 0;
    w2 = 0;
    for (j = 0; j < 4; j++) {
      w1 = ((w1 >> 2) & 0x3F ) | ((v & 0x01) ? 0xC0 : 00);
      w2 = ((w2 >> 2) & 0x3F ) | ((v & 0x10) ? 0xC0 : 00);
      v >>= 1;
    }
    v = w1;
    b[i] = w2;
#endif
    i2c_write(v);
  }

#ifdef LCD_BIG_FONTS
  sh1106_send_command_start();
  i2c_write(SH1106_SETSTARTPAGE + row + 1);
  i2c_write((col & 0x0f) | SH1106_LOWCOLUMNADDR);
  i2c_write(((col & 0xf0) >> 4) | SH1106_HIGHCOLUMNADDR);
  sh1106_send_data_start();

  for (i = 0; i < 8; i++)
    i2c_write(b[i]);
#endif

  i2c_stop();
}

void lcd_setCursor(uint8_t col, uint8_t row)
{
  if ((row < NUM_ROWS) && (col < NUM_COLS)) {
    if (_displayCursor) {
      uint8_t curValue = _buffer[_row * NUM_COLS + _col];
      write_raw(curValue, 0);
    }
    
    _col = col;
    _row = row;
    
    if (_displayCursor) {
      uint8_t curValue = _buffer[_row * NUM_COLS + _col];
      write_raw(curValue, 1);
    }
  } 
}

// ----------------------------------------------------------------------------

void lcd_write(uint8_t value) {
  write_raw(value, 0);
  
  _buffer[_row * NUM_COLS + _col] = value;
  _col++;
  if (_col >= NUM_COLS) {
    _col = 0;
    _row = (_row + 1) % NUM_ROWS;
  }
  if (_displayCursor) {
    uint8_t curValue = _buffer[_row * NUM_COLS + _col];
    write_raw(curValue, 1);
  }
}

void lcd_print(char *s) {
  while (*s) {
    lcd_write(*s++);
  }
}

// ----------------------------------------------------------------------------
void sh1106_fillscreen(uint8_t fill) {
  uint8_t m, n;
  for (m = 0; m < 8; m++)
  {
    sh1106_send_command_start();
    i2c_write(SH1106_SETSTARTPAGE + m);  // page0 - page7
    i2c_write(SH1106_LOWCOLUMNADDR | LCD_SH1106_COLOFFSET);      // low column start address    
    i2c_write(SH1106_HIGHCOLUMNADDR);      // high column start address
    sh1106_send_data_start();
    for (n = 0; n < 128; n++)
    {
      i2c_write(fill);
    }
    i2c_stop();
  }
}

void sh1106_send_command_start(void) {
  i2c_start(_addr << 1);
  i2c_write(0x00); // command
}

void sh1106_send_command(uint8_t command) {
  sh1106_send_command_start();
  i2c_write(command);
  i2c_stop();
}

void sh1106_send_data_start(void) {
  i2c_start(_addr << 1);
  i2c_write(0x40); // data
}

#endif
