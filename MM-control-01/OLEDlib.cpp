#include "OLEDlib.h"
#include <Wire.h>
#include <avr/pgmspace.h>


// 8x8 Font ASCII 32 - 127 Implemented
// Users can modify this to support more characters(glyphs)
// BasicFont is placed in code memory.

// This font be freely used without any restriction(It is placed in public domain)
const byte BasicFont[][8] PROGMEM = {
	{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},
	{0x00,0x00,0x5F,0x00,0x00,0x00,0x00,0x00},
	{0x00,0x00,0x07,0x00,0x07,0x00,0x00,0x00},
	{0x00,0x14,0x7F,0x14,0x7F,0x14,0x00,0x00},
	{0x00,0x24,0x2A,0x7F,0x2A,0x12,0x00,0x00},
	{0x00,0x23,0x13,0x08,0x64,0x62,0x00,0x00},
	{0x00,0x36,0x49,0x55,0x22,0x50,0x00,0x00},
	{0x00,0x00,0x05,0x03,0x00,0x00,0x00,0x00},
	{0x00,0x1C,0x22,0x41,0x00,0x00,0x00,0x00},
	{0x00,0x41,0x22,0x1C,0x00,0x00,0x00,0x00},
	{0x00,0x08,0x2A,0x1C,0x2A,0x08,0x00,0x00},
	{0x00,0x08,0x08,0x3E,0x08,0x08,0x00,0x00},
	{0x00,0xA0,0x60,0x00,0x00,0x00,0x00,0x00},
	{0x00,0x08,0x08,0x08,0x08,0x08,0x00,0x00},
	{0x00,0x60,0x60,0x00,0x00,0x00,0x00,0x00},
	{0x00,0x20,0x10,0x08,0x04,0x02,0x00,0x00},
	{0x00,0x3E,0x51,0x49,0x45,0x3E,0x00,0x00},
	{0x00,0x00,0x42,0x7F,0x40,0x00,0x00,0x00},
	{0x00,0x62,0x51,0x49,0x49,0x46,0x00,0x00},
	{0x00,0x22,0x41,0x49,0x49,0x36,0x00,0x00},
	{0x00,0x18,0x14,0x12,0x7F,0x10,0x00,0x00},
	{0x00,0x27,0x45,0x45,0x45,0x39,0x00,0x00},
	{0x00,0x3C,0x4A,0x49,0x49,0x30,0x00,0x00},
	{0x00,0x01,0x71,0x09,0x05,0x03,0x00,0x00},
	{0x00,0x36,0x49,0x49,0x49,0x36,0x00,0x00},
	{0x00,0x06,0x49,0x49,0x29,0x1E,0x00,0x00},
	{0x00,0x00,0x36,0x36,0x00,0x00,0x00,0x00},
	{0x00,0x00,0xAC,0x6C,0x00,0x00,0x00,0x00},
	{0x00,0x08,0x14,0x22,0x41,0x00,0x00,0x00},
	{0x00,0x14,0x14,0x14,0x14,0x14,0x00,0x00},
	{0x00,0x41,0x22,0x14,0x08,0x00,0x00,0x00},
	{0x00,0x02,0x01,0x51,0x09,0x06,0x00,0x00},
	{0x00,0x32,0x49,0x79,0x41,0x3E,0x00,0x00},
	{0x00,0x7E,0x09,0x09,0x09,0x7E,0x00,0x00},
	{0x00,0x7F,0x49,0x49,0x49,0x36,0x00,0x00},
	{0x00,0x3E,0x41,0x41,0x41,0x22,0x00,0x00},
	{0x00,0x7F,0x41,0x41,0x22,0x1C,0x00,0x00},
	{0x00,0x7F,0x49,0x49,0x49,0x41,0x00,0x00},
	{0x00,0x7F,0x09,0x09,0x09,0x01,0x00,0x00},
	{0x00,0x3E,0x41,0x41,0x51,0x72,0x00,0x00},
	{0x00,0x7F,0x08,0x08,0x08,0x7F,0x00,0x00},
	{0x00,0x41,0x7F,0x41,0x00,0x00,0x00,0x00},
	{0x00,0x20,0x40,0x41,0x3F,0x01,0x00,0x00},
	{0x00,0x7F,0x08,0x14,0x22,0x41,0x00,0x00},
	{0x00,0x7F,0x40,0x40,0x40,0x40,0x00,0x00},
	{0x00,0x7F,0x02,0x0C,0x02,0x7F,0x00,0x00},
	{0x00,0x7F,0x04,0x08,0x10,0x7F,0x00,0x00},
	{0x00,0x3E,0x41,0x41,0x41,0x3E,0x00,0x00},
	{0x00,0x7F,0x09,0x09,0x09,0x06,0x00,0x00},
	{0x00,0x3E,0x41,0x51,0x21,0x5E,0x00,0x00},
	{0x00,0x7F,0x09,0x19,0x29,0x46,0x00,0x00},
	{0x00,0x26,0x49,0x49,0x49,0x32,0x00,0x00},
	{0x00,0x01,0x01,0x7F,0x01,0x01,0x00,0x00},
	{0x00,0x3F,0x40,0x40,0x40,0x3F,0x00,0x00},
	{0x00,0x1F,0x20,0x40,0x20,0x1F,0x00,0x00},
	{0x00,0x3F,0x40,0x38,0x40,0x3F,0x00,0x00},
	{0x00,0x63,0x14,0x08,0x14,0x63,0x00,0x00},
	{0x00,0x03,0x04,0x78,0x04,0x03,0x00,0x00},
	{0x00,0x61,0x51,0x49,0x45,0x43,0x00,0x00},
	{0x00,0x7F,0x41,0x41,0x00,0x00,0x00,0x00},
	{0x00,0x02,0x04,0x08,0x10,0x20,0x00,0x00},
	{0x00,0x41,0x41,0x7F,0x00,0x00,0x00,0x00},
	{0x00,0x04,0x02,0x01,0x02,0x04,0x00,0x00},
	{0x00,0x80,0x80,0x80,0x80,0x80,0x00,0x00},
	{0x00,0x01,0x02,0x04,0x00,0x00,0x00,0x00},
	{0x00,0x20,0x54,0x54,0x54,0x78,0x00,0x00},
	{0x00,0x7F,0x48,0x44,0x44,0x38,0x00,0x00},
	{0x00,0x38,0x44,0x44,0x28,0x00,0x00,0x00},
	{0x00,0x38,0x44,0x44,0x48,0x7F,0x00,0x00},
	{0x00,0x38,0x54,0x54,0x54,0x18,0x00,0x00},
	{0x00,0x08,0x7E,0x09,0x02,0x00,0x00,0x00},
	{0x00,0x18,0xA4,0xA4,0xA4,0x7C,0x00,0x00},
	{0x00,0x7F,0x08,0x04,0x04,0x78,0x00,0x00},
	{0x00,0x00,0x7D,0x00,0x00,0x00,0x00,0x00},
	{0x00,0x80,0x84,0x7D,0x00,0x00,0x00,0x00},
	{0x00,0x7F,0x10,0x28,0x44,0x00,0x00,0x00},
	{0x00,0x41,0x7F,0x40,0x00,0x00,0x00,0x00},
	{0x00,0x7C,0x04,0x18,0x04,0x78,0x00,0x00},
	{0x00,0x7C,0x08,0x04,0x7C,0x00,0x00,0x00},
	{0x00,0x38,0x44,0x44,0x38,0x00,0x00,0x00},
	{0x00,0xFC,0x24,0x24,0x18,0x00,0x00,0x00},
	{0x00,0x18,0x24,0x24,0xFC,0x00,0x00,0x00},
	{0x00,0x00,0x7C,0x08,0x04,0x00,0x00,0x00},
	{0x00,0x48,0x54,0x54,0x24,0x00,0x00,0x00},
	{0x00,0x04,0x7F,0x44,0x00,0x00,0x00,0x00},
	{0x00,0x3C,0x40,0x40,0x7C,0x00,0x00,0x00},
	{0x00,0x1C,0x20,0x40,0x20,0x1C,0x00,0x00},
	{0x00,0x3C,0x40,0x30,0x40,0x3C,0x00,0x00},
	{0x00,0x44,0x28,0x10,0x28,0x44,0x00,0x00},
	{0x00,0x1C,0xA0,0xA0,0x7C,0x00,0x00,0x00},
	{0x00,0x44,0x64,0x54,0x4C,0x44,0x00,0x00},
	{0x00,0x08,0x36,0x41,0x00,0x00,0x00,0x00},
	{0x00,0x00,0x7F,0x00,0x00,0x00,0x00,0x00},
	{0x00,0x41,0x36,0x08,0x00,0x00,0x00,0x00},
	{0x00,0x02,0x01,0x01,0x02,0x01,0x00,0x00},
	{0x00,0x02,0x05,0x05,0x02,0x00,0x00,0x00} 
};

// ====================== LOW LEVEL =========================

size_t OLEDlib::write(uint8_t c) {
  if (c == '\n') {
    //skip
  } else if (c == '\r') {
    // skip em
  } else {
    printChar(c);
  }
  return 1;
}

void OLEDlib::sendCommand(byte command){
	Wire.beginTransmission(oled_address); // begin transmitting
	Wire.write(OLEDlib_COMMAND_MODE);//data mode
	Wire.write(command);
	Wire.endTransmission();    // stop transmitting
}


void OLEDlib::sendData(byte data){
	
	Wire.beginTransmission(oled_address); // begin transmitting
	Wire.write(OLEDlib_DATA_MODE);//data mode
	Wire.write(data);
	Wire.endTransmission();    // stop transmitting

}

void OLEDlib::printChar(char c, byte x, byte y){

	if ( x < 128 )
		setCursorXY(x, y);

	//Ignore unused ASCII characters. Modified the range to support multilingual characters.
    if(c < 32 || c > 127)
		c='*'; //star - indicate characters that can't be displayed

	
    for(byte i=0; i<8; i++) {
	
       //read bytes from code memory
       sendData(pgm_read_byte(&BasicFont[c-32][i])); //font array starts at 0, ASCII starts at 32. Hence the translation
	 
    }
}

void OLEDlib::drawBitmap(const byte *bitmaparray, byte x, byte y, byte width, byte height){

// max width = 16
// max height = 8

	setCursorXY( x, y );
	
	byte column = 0; 
	for(int i=0; i<(width*height)/8; i++) {  

		sendData(pgm_read_byte(&bitmaparray[i]));
		
		if(++column == width) {
			column = 0;
			setCursorXY( x, ++y );
		} 
	}

}

void OLEDlib::printString(const char *String, byte x, byte y, byte numChar){

	if ( x < 128 )
		setCursorXY(x, y);

	
	byte count=0;
    while(String[count] && count<numChar){
		printChar(String[count++]);  
	}

}


byte OLEDlib::printNumber(long long_num, byte x, byte y){

	if ( x < 128 )
		setCursorXY(x, y);


	byte char_buffer[10] = "";
	byte i = 0;
	byte f = 0; // number of characters

	if (long_num < 0) {
	
		f++;
		printChar('-');
		long_num = -long_num;
	
	} 
	else if (long_num == 0) {
	
		f++;
		printChar('0');
		return f;
	
	} 

	while (long_num > 0) {
	
		char_buffer[i++] = long_num % 10;
		long_num /= 10;
	
	}

	f += i;
	for(; i > 0; i--) {

		printChar('0'+ char_buffer[i - 1]);

	}
	
	return f;

}

byte OLEDlib::printNumber(float float_num, byte prec, byte x, byte y){

	if ( x < 128 )
		setCursorXY(x, y);

// prec - 6 maximum

	byte num_int = 0;
	byte num_frac = 0;
	byte num_extra = 0;
	
	long d = float_num; // get the integer part
	float f = float_num - d; // get the fractional part
	
	
	if (d == 0 && f < 0.0){
	
		printChar('-');
		num_extra++;
		printChar('0');
		num_extra++;
		f *= -1;
		
	}
	else if (d < 0 && f < 0.0){
	
		num_int = printNumber(d); // count how many digits in integer part
		f *= -1;
		
	}
	else{
	
		num_int = printNumber(d); // count how many digits in integer part
	
	}
	
	// only when fractional part > 0, we show decimal point
	if (f > 0.0){
	
		printChar('.');
		num_extra++;
	
		long f_shift = 1;
		
		if (num_int + prec > 8) 
			prec = 8 - num_int;
		
		for (byte j=0; j<prec; j++){
			f_shift *= 10;
		}

		num_frac = printNumber((long)(f*f_shift)); // count how many digits in fractional part
	}
	
	return num_int + num_frac + num_extra;
}

// =================== High Level ===========================

void OLEDlib::init(int address, int width, int height){
    _width = width;
    _height = height;
    oled_address = address;
    Wire.begin();
    sendCommand(OLEDlib_CMD_DISPLAY_OFF);                    // 0xAE
    sendCommand(SSD1306_SETDISPLAYCLOCKDIV);            // 0xD5
    sendCommand(OLEDlib_COMMAND_MODE);                                  // the suggested ratio 0x80
    sendCommand(SSD1306_SETMULTIPLEX);                  // 0xA8
    if(height == 64)
    {
      sendCommand(0x3F);
    }
    else if (height == 32)
    {
      sendCommand(0x1F);
    }
    sendCommand(SSD1306_SETDISPLAYOFFSET);              // 0xD3
    sendCommand(0x0);                                   // no offset
    //sendCommand(SSD1306_SETSTARTLINE | 0x0);            // line #0
    sendCommand(SSD1306_CHARGEPUMP);                    // 0x8D
    sendCommand(0x14);
    sendCommand(SSD1306_MEMORYMODE);                    // 0x20
    sendCommand(0x00);                                  // 0x0 act like ks0108
    sendCommand(SSD1306_SEGREMAP | 0x1);
    sendCommand(SSD1306_COMSCANDEC);
    sendCommand(SSD1306_SETCOMPINS);                    // 0xDA
    if(height == 64)
    {
      sendCommand(0x12);
    }
    else if (height == 32)
    {
      sendCommand(0x02);
    }
    sendCommand(OLEDlib_CMD_SET_BRIGHTNESS);                   // 0x81
    sendCommand(0xCF);
    sendCommand(SSD1306_SETPRECHARGE);                  // 0xd9
    sendCommand(0xF1);
    sendCommand(SSD1306_SETVCOMDETECT);                 // 0xDB
    sendCommand(0x40);
    sendCommand(SSD1306_DISPLAYALLON_RESUME);           // 0xA4
    sendCommand(OLEDlib_CMD_NORMAL_DISPLAY);                 // 0xA6
    sendCommand(OLEDlib_CMD_DISPLAY_ON);
    clearDisplay();
	setCursorXY(0,0);
}

void OLEDlib::setCursorXY(float X, float Y){
	// Y - 1 unit = 1 page (8 pixel rows)
	// X - 1 unit = 8 pixel columns

  sendCommand(0x00 + ((byte)(8*X) & 0x0F)); 		//set column lower address
  sendCommand(0x10 + (((byte)(8*X)>>4)&0x0F)); 	//set column higher address
	sendCommand(0xB0 + (byte)Y); 					//set page address
	
}

void OLEDlib::clearDisplay()	{


	for(byte page=0; page<8; page++) {	
	
		setCursorXY(0, page);     
		for(byte column=0; column<128; column++){  //clear all columns
			sendData(0);    
		}

	}
	
	setCursorXY(0,0);  
	
}

/*
void OLEDlib::clearPage(byte page)	{
	// clear page and set cursor at beginning of that page

	setCursorXY(0, page);    
	for(byte column=0; column<128; column++){  //clear all columns
		sendData(0x00);    
	}
	
}
*/


void OLEDlib::setInverseDisplay(){

	sendCommand(OLEDlib_CMD_INVERSE_DISPLAY);
	
}

void OLEDlib::setNormalDisplay(){

	sendCommand(OLEDlib_CMD_NORMAL_DISPLAY);
	
}

void OLEDlib::setPowerOff(){

	sendCommand(OLEDlib_CMD_DISPLAY_OFF);
	
}

void OLEDlib::setPowerOn(){

	sendCommand(OLEDlib_CMD_DISPLAY_ON);
	
}

void OLEDlib::setBrightness(byte Brightness){

	sendCommand(OLEDlib_CMD_SET_BRIGHTNESS);
	sendCommand(Brightness);
   
}

void OLEDlib::setPageMode(){
	addressingMode = PAGE_ADDRESSING;
	sendCommand(0x20); 				//set addressing mode
	sendCommand(PAGE_ADDRESSING); 	//set page addressing mode
}

void OLEDlib::setHorizontalMode(){
	addressingMode = HORIZONTAL_ADDRESSING;
	sendCommand(0x20); 				//set addressing mode
	sendCommand(HORIZONTAL_ADDRESSING); 	//set page addressing mode
}


// startscrollright
// Activate a right handed scroll for rows start through stop
// Hint, the display is 16 rows tall. To scroll the whole display, run:
// scrollRight(0x00, 0x0F)  - start - stop
void OLEDlib::scrollRight(byte start, byte end, byte speed){

    sendCommand(OLEDlib_RIGHT_SCROLL);  //Horizontal Scroll Setup
    sendCommand(0x00);	// dummy byte 
    sendCommand(start);	// start page address
    sendCommand(speed);	// set time interval between each scroll
    sendCommand(end);	// end page address
	
    sendCommand(0x01);  
    sendCommand(0xFF);
	
    sendCommand(0x2f);  //active scrolling
	
}


// startscrollleft
// Activate a right handed scroll for rows start through stop
// Hint, the display is 16 rows tall. To scroll the whole display, run:
// display.scrollright(0x00, 0x0F)   - start - stop
void OLEDlib::scrollLeft(byte start, byte end, byte speed){

    sendCommand(OLEDlib_LEFT_SCROLL);  //Horizontal Scroll Setup
    sendCommand(0x00);	// dummy byte
    sendCommand(start);	// start page address
    sendCommand(speed);	// set time interval between each scroll
    sendCommand(end);	// end page address
	
    sendCommand(0x01);  
    sendCommand(0xFF);  
	
    sendCommand(0x2f);  //active scrolling
	
}

// startscrolldiagright
// Activate a diagonal scroll for rows start through stop
// Hint, the display is 16 rows tall. To scroll the whole display, run:
// display.scrollright(0x00, 0x0F) 
void OLEDlib::scrollDiagRight(){

        sendCommand(OLEDlib_SET_VERTICAL_SCROLL_AREA);        
        sendCommand(0X00);
        sendCommand(OLEDlib_Max_Y);
        sendCommand(OLEDlib_VERTICAL_RIGHT_SCROLL); //Vertical and Horizontal Scroll Setup
        sendCommand(0X00); 	//dummy byte
        sendCommand(0x00);	 //define page0 as startpage address
        sendCommand(0X00);	//set time interval between each scroll ste as 6 frames
        sendCommand(0x07);	//define page7 as endpage address
        sendCommand(0X01);	//set vertical scrolling offset as 1 row
        sendCommand(OLEDlib_CMD_ACTIVATE_SCROLL); //active scrolling
	
}

void OLEDlib::scrollDiagLeft(){

        sendCommand(OLEDlib_SET_VERTICAL_SCROLL_AREA);        
        sendCommand(0X00);
        sendCommand(OLEDlib_Max_Y);
        sendCommand(OLEDlib_VERTICAL_LEFT_SCROLL); //Vertical and Horizontal Scroll Setup
        sendCommand(0X00); //dummy byte
        sendCommand(0x00);	 //define page0 as startpage address
        sendCommand(0X00);	//set time interval between each scroll ste as 6 frames
        sendCommand(0x07);	//define page7 as endpage address
        sendCommand(0X01);	//set vertical scrolling offset as 1 row
        sendCommand(OLEDlib_CMD_ACTIVATE_SCROLL); //active scrolling
	
}


void OLEDlib::setActivateScroll(byte direction, byte startPage, byte endPage, byte scrollSpeed){


/*
This function is still not complete, we need more testing also.
Use the following defines for 'direction' :

 Scroll_Left			
 Scroll_Right			

For Scroll_vericle, still need to debug more... 

Use the following defines for 'scrollSpeed' :

 Scroll_2Frames		
 Scroll_3Frames
 Scroll_4Frames
 Scroll_5Frames	
 Scroll_25Frames
 Scroll_64Frames
 Scroll_128Frames
 Scroll_256Frames

*/


	if(direction == Scroll_Right) {
	
		//Scroll Right
		sendCommand(0x26);
		
	}
	else {
	
		//Scroll Left  
		sendCommand(0x27);

	}
	/*
	else if (direction == Scroll_Up ){
	
		//Scroll Up  
		sendCommand(0x29);
	
	}
	else{
	
		//Scroll Down  
		sendCommand(0x2A);
	
	}
	*/
	sendCommand(0x00);//dummy byte
	sendCommand(startPage);
	sendCommand(scrollSpeed);	
	sendCommand(endPage);		// for verticle scrolling, use 0x29 as command, endPage should = start page = 0
	
	/*
	if(direction == Scroll_Up) {
	
		sendCommand(0x01);

	}
	*/

	sendCommand(OLEDlib_CMD_ACTIVATE_SCROLL);

}

void OLEDlib::setDeactivateScroll(){

	sendCommand(OLEDlib_CMD_DEACTIVATE_SCROLL);

}




OLEDlib display;  // Preinstantiate Objects

