#include <ArduinoQueue.h>
#include "Cube.h"
#include "Strip.h"
#include "Command.h"

// GENERAL CONSTANTS
const int SECOND = 1000;
ArduinoQueue<Command> COMMANDS(50);

// Define controllable devices
Cube cube;
Strip ledStrip;


// DEFAULT ARDUINO FUNCTIONS

void setup() {
  // Set up neopixel strip
  ledStrip.begin();
  ledStrip.setBrightness(255);

  // Set up cube
  pinMode(13, OUTPUT);
  digitalWrite(13, HIGH);

  // Set up Serial
  Serial.begin(9600);
  cubeSerial.begin(9600);
  while (!Serial && !cubeSerial) {};
  Serial.println("Ready!");
}

void loop() {
  cube.clearCube();
  ledStrip.clearStrip();
  
  checkForInput();
  
  if (!COMMANDS.isEmpty()) {
    performAction(COMMANDS.dequeue().value());
  }
}

// ====================================================================================================================

// HELPER FUNCTIONS

void performAction(char action) {
  
  Serial.println("Performing " + (String) action);
  switch(action) {
      case 'a':
        ledStrip.rainbow(10 * SECOND);
        break;
      case 'c':
        cube.bounce(5 * SECOND);
        break;
      default:
        ledStrip.solidColor(action);
    }
}

void checkForInput() {
  if (Serial.available() > 0) {
    Command command(char(Serial.read()));

    if (command.isValid())
      COMMANDS.enqueue(command.value());
  }
}
