///////////////////////////////////////////////////
////ARDUINO + TOUCHSCREEN SOUND CONTROLLER TEST////
///////////////////////////////////////////////////
/*By Maeve Mulholland Nov 2016
  for BSc Music Technology & Sonic Arts MTE3020*/

//libraries
#include <stdint.h>
#include <TouchScreen.h>
#include <TFTv2.h>
#include <SPI.h>

int SoundZoneW = 200; //sound zone width
int SoundZoneH = 64; //sound zone height
int color = YELLOW; //touch indicator colour
unsigned int colors[5] = {RED, GREEN, BLUE, GRAY1, GRAY2};

/*for best pressure precision, resistance between X+ and X- pins on shield must
  be known. this shield has 300 ohms across the X plate*/

TouchScreen ts = TouchScreen(XP, YP, XM, YM); //initialise TouchScreen port pins

void setup() {
  Tft.TFTinit(); //initialise TFT library
  Serial.begin(115200); //start Serial and set baud rate
  //draw title
  Tft.drawChar('M', 207, 60, 4, WHITE);
  Tft.drawChar('A', 207, 100, 4, WHITE);
  Tft.drawChar('E', 207, 140, 4, WHITE);
  Tft.drawChar('V', 207, 180, 4, WHITE);
  Tft.drawChar('E', 207, 220, 4, WHITE);
  //draw sound zones
  for (int i = 0; i < 5; i++)
  {
    Tft.fillRectangle(0, i * 64, SoundZoneW, SoundZoneH, colors[i]);
  }
}

void loop() {

  Point p = ts.getPoint(); //point object holds x, y, and z co-ordinates

  //map ADC value read into pixel co-ordinates
  p.x = map(p.x, TS_MINX, TS_MAXX, 0, 240);
  p.y = map(p.y, TS_MINY, TS_MAXY, 0, 320);

  //pressure of 0 means no pressing on screen
  if (p.z > __PRESURE) { //if touchscreen is pressed
    if (p.x < SoundZoneW + 2) //below title line
    { //send p.y value to serial port
      Serial.write(p.y);
      Serial.write(p.x);
    }
    }

  }
