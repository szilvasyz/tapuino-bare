#include "config.h"
#ifdef LCD_USE_ST7920_LCD_MODULE

#include "lcd_interface.h"

#include <util/delay.h>
#include <avr/pgmspace.h>

#include "i2c_master.h"
//#include "ST7920_font8x8.h"
//#include "myfont_8x8.h"
//#include "orig8x8-h-iso8859-1.h"
#include "orig8x8-h-iso8859-2.h"

// commands
#define LCD_CLEARDISPLAY 0x01
#define LCD_RETURNHOME 0x02
#define LCD_DISPLAYCONTROL 0x08
#define LCD_FUNCTIONSET 0x20
#define LCD_SETDDRAMADDR 0x80

// flags for display on/off control
#define LCD_DISPLAYON 0x04
#define LCD_CURSORON 0x02
#define LCD_CURSOROFF 0x00
#define LCD_BLINKON 0x01
#define LCD_BLINKOFF 0x00

// flags for backlight control
#define LCD_BACKLIGHT     _BV(LCD_BIT_BACKLIGHT)
#define LCD_NOBACKLIGHT   0x00

// flags for function set
#define LCD_4BITMODE 0x00
#define LCD_2LINE 0x08
#define LCD_5x8DOTS 0x00

#define LCD_EXTFUN 0x04
#define LCD_EXT_GRON 0x02

void lcd_init(uint8_t lcd_addr);
void lcd_write(uint8_t value);
void lcd_charWrite(uint8_t col, uint8_t row, uint8_t chr);

void command(uint8_t value);
void lcd_begin(uint8_t lcd_addr, uint8_t cols, uint8_t lines, uint8_t dotsize);
void lcd_clear();
void lcd_home();
void lcd_setCursor(uint8_t col, uint8_t row);
void lcd_noCursor();
void lcd_cursor();
void lcd_noBacklight(void);
void lcd_backlight(void);
void lcd_print(char* msg);
void send(uint8_t v, uint8_t mode);
void send16(uint16_t v, uint8_t mode);



uint8_t dm[MAX_LCD_LINE_LEN][LCD_NUM_LINES];


uint8_t _addr;
uint8_t _displayfunction;
uint8_t _displayextfunc;
uint8_t _displaycontrol;
uint8_t _cols;
uint8_t _rows;
uint8_t _backlightval;

uint8_t _curcol;
uint8_t _currow;


void lcd_write(uint8_t value) {
  lcd_charWrite(_curcol, _currow, value);
  if (++_curcol >= _cols) {
    _curcol = 0;
    if (++_currow >= _rows) {
      _curcol = _cols - 1; 
      _currow = _rows - 1; 
    }
  }
}

void lcd_print(char* msg) {
  uint8_t v;
  while((v = *msg++)) {
    lcd_write(v);
  }
}


// mid level commands, for sending data/cmds 

void command(uint8_t value) {
  i2c_start((_addr << 1) | I2C_WRITE);
  send(value, 0);
  i2c_stop();
//  _delay_us(50);
}

void lcd_init(uint8_t lcd_addr) {
  lcd_begin(lcd_addr, MAX_LCD_LINE_LEN, LCD_NUM_LINES, LCD_5x8DOTS);
}

void lcd_begin(uint8_t lcd_addr, uint8_t cols, uint8_t lines, uint8_t dotsize) {
  
  uint8_t t;
  
  _addr = lcd_addr;
  _cols = cols;
  _rows = lines;
  _backlightval = LCD_NOBACKLIGHT;
  i2c_init();

  _displayfunction = LCD_4BITMODE | LCD_2LINE | LCD_5x8DOTS;
  _displayextfunc = LCD_4BITMODE | LCD_EXTFUN; 

  _delay_ms(50); 

  lcd_noBacklight();  // reset expander and turn backlight off (Bit 8 = 0)
  _delay_ms(1000);
  
   // we start in 8bit mode, try to set 4 bit mode
  t = _BV(LCD_BIT_DATA0) | _BV(LCD_BIT_DATA1);
  i2c_start((_addr << 1) | I2C_WRITE);

  i2c_write(t); i2c_write(t | _BV(LCD_BIT_EN)); i2c_write(t);    
  _delay_us(4500); // wait min 4.1ms
   
   // second try
  i2c_write(t); i2c_write(t | _BV(LCD_BIT_EN)); i2c_write(t);    
  _delay_us(4500); // wait min 4.1ms
   
   // third go!
  i2c_write(t); i2c_write(t | _BV(LCD_BIT_EN)); i2c_write(t);    
  _delay_us(150);
   
   // finally, set to 4-bit interface
  t &= ~_BV(LCD_BIT_DATA0); 
  i2c_write(t); i2c_write(t | _BV(LCD_BIT_EN)); i2c_write(t);    

  i2c_stop();   

  // set # lines, font size, etc.
  command(LCD_FUNCTIONSET | _displayfunction);  
  
  // turn the display on with no cursor or blinking default
  _displaycontrol = LCD_DISPLAYON | LCD_CURSOROFF | LCD_BLINKOFF;
  command(LCD_DISPLAYCONTROL | _displaycontrol); 

  // clear it off
  lcd_clear();
  lcd_home();
}

// high level commands, for the user!
void lcd_clear() {
  uint8_t r, c, v;

  _curcol = 0;
  _currow = 0;
  
  command(LCD_CLEARDISPLAY);// clear display, set cursor position to zero
  _delay_us(2000);  // this command takes a long time!

  command(LCD_FUNCTIONSET | _displayextfunc | LCD_EXT_GRON);

  for (r = 0; r < _rows; r++) 
    for (c = 0; c < _cols; c++) 
      dm[c][r] = ' ';

  i2c_start((_addr << 1) | I2C_WRITE);

  for (r = 0; r < 32; r++) {

    send(LCD_SETDDRAMADDR | r, 0);
    send(LCD_SETDDRAMADDR | 0, 0);
    v = _backlightval | _BV(LCD_BIT_RS); 
    i2c_write(v);

    for (c = 0; c < 64; c++) {
      i2c_write(v | _BV(LCD_BIT_EN));
      i2c_write(v);
    }
  }
  i2c_stop();

}

void lcd_home() {

  _curcol = 0;
  _currow = 0;
  
  command(LCD_RETURNHOME);  // set cursor position to zero
  _delay_us(2000);  // this command takes a long time!
}


void lcd_setCursor(uint8_t col, uint8_t row) {
  int row_offsets[] = { 0x80, 0x88, 0x90, 0x98 };

  if ( row >= _rows ) {
    row = _rows - 1;    // we count rows starting w/0
  }
  if ( col >= _cols ) {
    col = _cols - 1;    // we count cols starting w/0
  }
  
  _curcol = col;
  _currow = row;

  command(LCD_FUNCTIONSET | _displayfunction);  
  command(LCD_SETDDRAMADDR | (col + row_offsets[row]));
}


// Turns the underline cursor on/off
void lcd_noCursor() {
  _displaycontrol &= ~LCD_CURSORON;
  command(LCD_DISPLAYCONTROL | _displaycontrol);
}

void lcd_cursor() {
  _displaycontrol |= LCD_CURSORON;
  command(LCD_DISPLAYCONTROL | _displaycontrol);
}





void lcd_charWrite(uint8_t col, uint8_t row, uint8_t chr) {
  uint8_t r, c, i;
  uint8_t rota;
  uint16_t mask;
  uint16_t temp;
  int p0, p1;

  dm[col][row] = chr;
  
  i2c_start((_addr << 1) | I2C_WRITE); 
  send(LCD_FUNCTIONSET | _displayextfunc | LCD_EXT_GRON, 0);
     
//  p0 = &console_font[ (dm[col & 0xFE][row]) - 32  ][0];
//  p1 = &console_font[ (dm[col | 0x01][row]) - 32  ][0];
#ifdef LCD_BIG_FONTS
  r = (row & 0b1) << 4;
  c = (col >> 1) | ((row & 0b10) << 2);
#else
  r = (row & 0b11) << 3;
  c = (col >> 1) | ((row & 0b100) << 1);
#endif  
  p0 = &console_font[  LCD_FONT_HEIGHT * LCD_CHAR_TO_POS(dm[col & 0xFE][row])  ];
  p1 = &console_font[  LCD_FONT_HEIGHT * LCD_CHAR_TO_POS(dm[col | 0x01][row])  ];

  for (i = 0; i < LCD_FONT_HEIGHT; i++) {
//  for (i = 0; i < LCD_FONT_HEIGHT; i+=2) {
    temp = (pgm_read_byte(p0++) << 8) | pgm_read_byte(p1++);
//    temp |= (pgm_read_byte(p0++) << 8) | pgm_read_byte(p1++);
    send(LCD_SETDDRAMADDR | r++, 0);
    send(LCD_SETDDRAMADDR | c, 0);
    send16(temp, 1);
#ifdef LCD_BIG_FONTS
    send(LCD_SETDDRAMADDR | r++, 0);
    send(LCD_SETDDRAMADDR | c, 0);
    send16(temp, 1);
#endif
  }
  i2c_stop();
}










// Turn the (optional) backlight off/on
void lcd_noBacklight(void) {
  _backlightval = LCD_NOBACKLIGHT;
  i2c_start((_addr << 1) | I2C_WRITE);
  i2c_write(_backlightval);
  i2c_stop();
}

void lcd_backlight(void) {
  _backlightval = LCD_BACKLIGHT;
  i2c_start((_addr << 1) | I2C_WRITE);
  i2c_write(_backlightval);
  i2c_stop();
}



// low level data pushing commands

// write data 16-bit without i2c_start
void send16(uint16_t v, uint8_t mode) {
  uint8_t r, i;
  uint16_t res;

  r =   _backlightval | (mode ? _BV(LCD_BIT_RS) : 0);  

  for (i = 0; i < 4; i++) {
    res = r;
    res |= v & 0x8000 ? _BV(LCD_BIT_DATA3) : 0;
    res |= v & 0x4000 ? _BV(LCD_BIT_DATA2) : 0;
    res |= v & 0x2000 ? _BV(LCD_BIT_DATA1) : 0;
    res |= v & 0x1000 ? _BV(LCD_BIT_DATA0) : 0;
    v <<= 4;

    i2c_write(res | _BV(LCD_BIT_EN));
    i2c_write(res);

  }
}



// write either command or data without i2c_start
void send(uint8_t v, uint8_t mode) {
  uint8_t r, i;
  uint8_t res;

  r = _backlightval | (mode ? _BV(LCD_BIT_RS) : 0);  
  
  for (i = 0; i < 2; i++) {
    res = r;
    res |= v & 0x80 ? _BV(LCD_BIT_DATA3) : 0;
    res |= v & 0x40 ? _BV(LCD_BIT_DATA2) : 0;
    res |= v & 0x20 ? _BV(LCD_BIT_DATA1) : 0;
    res |= v & 0x10 ? _BV(LCD_BIT_DATA0) : 0;
    v <<= 4;

    i2c_write(res | _BV(LCD_BIT_EN));
    i2c_write(res);

  }
}


#endif
