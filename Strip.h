#include <Adafruit_NeoPixel.h>

class Strip {
  public:
    const int ledPin = 5;
    const int numLeds = 57;

    Adafruit_NeoPixel strip = Adafruit_NeoPixel(numLeds, ledPin, NEO_GRB + NEO_KHZ800);

    void begin() {
      strip.begin();
    }

    void setBrightness(int brightness) {
      strip.setBrightness(brightness);
    }
    
    void setPixel(int Pixel, byte red, byte green, byte blue) {
      strip.setPixelColor(Pixel, strip.Color(red, green, blue));
      //checkForInput();
    }
    
    void clearStrip() {
      setAll(0, 0, 0);
    }
    
    void setAll(byte red, byte green, byte blue) {
      for(int i = 0; i < numLeds; i++ ) {
        setPixel(i, red, green, blue);
      }
      strip.show();
    }

    void solidColor(char color) {

      if (color == 'r') {
          setAll(255, 0, 0);
        } else if (color == 'g') {
          setAll(0, 255, 0);
        } else if (color == 'b') {
          setAll(0, 0, 255);
        }
        delay(5000);
        strip.clear();
        strip.show();
    }
    
    void rainbow(int wait) {
      uint16_t i, j;
      int startTime = millis();
      int endTime;
    
      while (true) {
        for(j=0; j<256; j++) {
          for(i=0; i<strip.numPixels(); i++) {
            strip.setPixelColor(i, Wheel((i*1+j) & 255));
          }
          endTime = millis();
          if (endTime - startTime > wait) {
            Serial.print(sprintf("endTime: %d\nstartTime: %d\ndifference: %d", endTime, startTime, endTime-startTime));
            return;
          }
          
          strip.show();
          delay(10);
        }
      }
    }
    
    
    // Input a value 0 to 255 to get a color value.
    // The colours are a transition r - g - b - back to r.
    uint32_t Wheel(byte WheelPos) {
      if(WheelPos < 85) {
        return strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
      } 
      else if(WheelPos < 170) {
        WheelPos -= 85;
        return strip.Color(255 - WheelPos * 3, 0, WheelPos * 3);
      } 
      else {
        WheelPos -= 170;
        return strip.Color(0, WheelPos * 3, 255 - WheelPos * 3);
      }
    }
};
