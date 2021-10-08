#include <SoftwareSerial.h>

SoftwareSerial cubeSerial(10, 11);

class Cube {
  public:
    
    int start = 0xf2;
    static const int numLights = 64;
    int twitchLogo[numLights] = { 
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7f, 
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xc1, 
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xd5, 
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xd5, 
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xc1, 
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xe6, 
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x38, 
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10
    };

    void bounce(int endDelay) {
      int bounceHeights[] = {8, 7, 6, 5, 4, 3, 2, 1, 0, 1, 2, 3, 4, 5, 6, 7, 7, 6, 6, 5, 5, 4, 3, 2, 1, 0, 1, 2, 3, 3, 4, 4, 5, 5, 4, 4, 3, 2, 1, 0, 1, 1, 2, 2, 1, 1, 0, 0, 1, 1, 1, 0, 0, 1, 1, 0};
      int copy[numLights];
      int* currentFrame;
      
      int i;
      for ( i= 0; i < sizeof(bounceHeights)/sizeof(bounceHeights[0]); i++) {
      currentFrame = deepCopy(copy);
      shiftUp(currentFrame, bounceHeights[i]);
      writeAll(currentFrame);
      delay(10);
      }
      delay(endDelay);
    }

    void oneAtTime() {
      int copy[numLights];
      int* currentFrame = emptyCube(copy);

      int i, j, k;
      for (i = 0; i < 8; i++) {
      for (j = 0; j < 8; j++) {
        for (k = 0; k < 8; k++) {
        setPixel(currentFrame, i, j, k);
        writeAll(currentFrame);
        delay(1);
        }
      }
      }
    }

    void oneAtTimeRandom() {
      int copy[numLights];
      int* currentFrame = emptyCube(copy);
      int lightsSet = 0;
      int x, y, z;

      while (true) {
      x = random(8);
      y = random(8);
      z = random(8);

      if (isPixelSet(currentFrame, x, y, z)) {
        continue;
      }

      setPixel(currentFrame, x, y, z);
      writeAll(currentFrame);
      lightsSet++;

      if (lightsSet == 256) {
        break;
      }
      
      delay(10);
      }
    }

    void shiftBackTest() {
      int i; 

      int copy[numLights];
      int* currentFrame = deepCopy(copy);
      writeAll(currentFrame);
      delay(100);

      for (i = 0; i < 8; i++) {
      shiftBack(currentFrame, 1);
      writeAll(currentFrame);
      delay(100);
      }
      
      shiftBack(currentFrame, 2);
      writeAll(currentFrame);
      delay(100);
    }

    void clearCube() {
      int empty[numLights];
      int* cube = emptyCube(empty);
      writeAll(cube);
    }

    void shiftUp(int *values, int shift) {
      if (shift <= 0) {
      return;
      }
      
      int i;
      int shiftLightNum = shift * 8;

      for (i = 0; i < numLights - shiftLightNum; i++) {
      values[i] = values[i+shiftLightNum];
      }

      for (i = numLights-shiftLightNum; i < numLights; i++) {
      values[i] = 0;
      }
    }

    void shiftBack(int *values, int shift) {
      if (shift <= 0) {
      return;
      }
      
      int i, j;

      for (i = 0; i < numLights; i += 8) {
      for (j = i; j <= i + (8 - shift); j++) {
        values[j] = values[j + shift];
      }
      }

      for (i = 0; i < numLights; i += 8) {
      for (j = i + (8-shift); j <= i + 8; j++) {
        values[j] = 0;
      }
      }
    }

    void clearPixel(int* values, int x, int y, int z) {
      int pixelLocation = x + (y * 8);
      values[pixelLocation] &= ~(1UL << z);
    }

    void setPixel(int* values, int x, int y, int z) {
      int pixelLocation = x + (y * 8);
      values[pixelLocation] |= 1UL << z;
    }

    bool isPixelSet(int* values, int x, int y, int z) {
      int pixelLocation = x + (y * 8);
      return (values[pixelLocation] >> z) & 1U > 0;
    }

    void writeAll(int *values) {
      int i;
      cubeSerial.write(start);
      for (i = 0; i < numLights; i++) {
        cubeSerial.write(values[i]);
      }
    }

    int* deepCopy(int *copy) {
      int i;
      for (i = 0; i < numLights; i++) {
        copy[i] = twitchLogo[i];
      }
      return copy;
    }

    int* emptyCube(int* empty) {
      int i;
      for (i = 0; i < numLights; i++) {
      empty[i] = 0;
      }
      return empty;
    }
};
