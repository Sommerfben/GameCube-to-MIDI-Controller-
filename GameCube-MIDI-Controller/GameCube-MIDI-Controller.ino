/*

Demonstrates simple RX and TX operation.
Any of the Basic_RX examples can be used as a receiver.
Please read through 'NRFLite.h' for a description of all the methods available in the library.

Radio    Arduino
CE    -> 9
CSN   -> 10 (Hardware SPI SS)
MOSI  -> 11 (Hardware SPI MOSI)
MISO  -> 12 (Hardware SPI MISO)
SCK   -> 13 (Hardware SPI SCK)
IRQ   -> No connection
VCC   -> No more than 3.6 volts
GND   -> GND

*/

#include <SPI.h>
#include "Nintendo.h"
#include "MIDIUSB.h"
#include "PitchToNote.h"

#define NUM_BUTTONS  12

// Define a Gamecube Controller
CGamecubeController GamecubeController(2);

// Generally, you should use "unsigned long" for variables that hold time
// The value will quickly become too large for an int to store
unsigned long previousMillis = 0;        // will store last time controller report was printed

// constants won't change:
const long interval = 1000;           // interval at which to print controller report (milliseconds)

const uint8_t button1 = 2;

const uint8_t button2 = 3;

const uint8_t button3 = 4;

const uint8_t button4 = 9;

const uint8_t button5 = 6;

const uint8_t button6 = 7;

const uint8_t button7 = 8;

const uint8_t button8 = 9;

const uint8_t button9 = 10;

const uint8_t button10 = 11;

const uint8_t button11 = 12;

const uint8_t button12 = 13;

const int intensityPot = 0;  //A0 input

const uint8_t buttons[NUM_BUTTONS] = {button1, button2, button3, button4, button5, button6, button7,button8,button9,button10,button11,button12};

const byte notePitches[NUM_BUTTONS] = {C3, D3, E3,F3, G3, A3, B3,C4,D4,E4,F4,G4};

uint8_t notesTime[NUM_BUTTONS];

uint32_t pressedButtons = 0x000;

uint32_t previousButtons = 0x000;

uint8_t intensity;
uint8_t val_right;
uint8_t val_left;
uint8_t val_x;
uint8_t val_y;
uint8_t val_cx;
uint8_t val_cy;


void setup()
{
    Serial.begin(115200);
}

void loop()
{
    // Try to read the controller data
  if (GamecubeController.read())
  {
    // Print Controller information
    auto status = GamecubeController.getStatus();
    auto report = GamecubeController.getReport();
    unsigned long currentMillis = millis();

    readButtons(report);

    readIntensity(report);

    playNotes();

  if (currentMillis - previousMillis >= interval) {
    // save the last time you blinked the LED
    previousMillis = currentMillis;
    print_gc_report(report, status);
  }
    
  }
  else
  {
    // Add debounce if reading failed
    Serial.println(F("Error reading Gamecube controller."));
    delay(1000);
  }
  delay(20);
}


void print_gc_report(Gamecube_Report_t &gc_report, Gamecube_Status_t &gc_status)
{
  // Print device information
  Serial.print(F("Device: "));
  switch (gc_status.device) {
    case NINTENDO_DEVICE_GC_NONE:
      Serial.println(F("No Gamecube Controller found!"));
      break;
    case NINTENDO_DEVICE_GC_WIRED:
      Serial.println(F("Original Nintendo Gamecube Controller"));
      break;

    default:
      Serial.print(F("Unknown "));
      Serial.println(gc_status.device, HEX);
      break;
  }

  // Print rumble state
  Serial.print(F("Rumble "));
  if (gc_status.rumble)
    Serial.println(F("on"));
  else
    Serial.println(F("off"));

  // Prints the raw data from the controller
  Serial.println();
  Serial.println(F("Printing Gamecube controller report:"));
  Serial.print(F("Start:\t"));
  Serial.println(gc_report.start);

  Serial.print(F("Y:\t"));
  Serial.println(gc_report.y);

  Serial.print(F("X:\t"));
  Serial.println(gc_report.x);

  Serial.print(F("B:\t"));
  Serial.println(gc_report.b);

  Serial.print(F("A:\t"));
  Serial.println(gc_report.a);

  Serial.print(F("L:\t"));
  Serial.println(gc_report.l);
  Serial.print(F("R:\t"));
  Serial.println(gc_report.r);
  Serial.print(F("Z:\t"));
  Serial.println(gc_report.z);

  Serial.print(F("Dup:\t"));
  Serial.println(gc_report.dup);
  Serial.print(F("Ddown:\t"));
  Serial.println(gc_report.ddown);
  Serial.print(F("Dright:\t"));
  Serial.println(gc_report.dright);
  Serial.print(F("Dleft:\t"));
  Serial.println(gc_report.dleft);

  Serial.print(F("xAxis:\t"));
  Serial.println(gc_report.xAxis, DEC);
  Serial.print(F("yAxis:\t"));
  Serial.println(gc_report.yAxis, DEC);

  Serial.print(F("cxAxis:\t"));
  Serial.println(gc_report.cxAxis, DEC);
  Serial.print(F("cyAxis:\t"));
  Serial.println(gc_report.cyAxis, DEC);

  Serial.print(F("L:\t"));
  Serial.println(gc_report.left, DEC);
  Serial.print(F("R:\t"));
  Serial.println(gc_report.right, DEC);
  Serial.println();

}


void readButtons(Gamecube_Report_t &gc_report)
{
    if (gc_report.a == 1)
    {
      bitWrite(pressedButtons, 0, 1);
    }
    else{
      bitWrite(pressedButtons, 0, 0);
  }
      if (gc_report.b == 1)
    {
      bitWrite(pressedButtons, 1, 1);
    }
    else{
      bitWrite(pressedButtons, 1, 0);
    }
    if (gc_report.x == 1)
    {
      bitWrite(pressedButtons, 2, 1);
    }
    else{
      bitWrite(pressedButtons, 2, 0);
  }
      if (gc_report.y == 1)
    {
      bitWrite(pressedButtons, 3, 1);
    }
    else{
      bitWrite(pressedButtons, 3, 0);
    }
       if (gc_report.start == 1)
    {
      bitWrite(pressedButtons, 4, 1);
    }
    else{
      bitWrite(pressedButtons, 4, 0);
    }
    if (gc_report.dup == 1)
    {
      bitWrite(pressedButtons, 5, 1);
    }
    else{
      bitWrite(pressedButtons, 5, 0);
    }
    if (gc_report.ddown == 1)
    {
      bitWrite(pressedButtons, 6, 1);
    }
    else{
      bitWrite(pressedButtons, 6, 0);
  }
      if (gc_report.dleft == 1)
    {
      bitWrite(pressedButtons, 7, 1);
    }
    else{
      bitWrite(pressedButtons, 7, 0);
    }
    if (gc_report.dright == 1)
    {
      bitWrite(pressedButtons, 8, 1);
    }
    else{
      bitWrite(pressedButtons, 8, 0);
    }
    if (gc_report.z == 1)
    {
      bitWrite(pressedButtons, 9, 1);
    }
    else{
      bitWrite(pressedButtons, 9, 0);
    }
    if (gc_report.l == 1)
    {
      bitWrite(pressedButtons, 10, 1);
    }
    else{
      bitWrite(pressedButtons, 10, 0);
    }
    if (gc_report.r == 1)
    {
      bitWrite(pressedButtons, 11, 1);
    }
    else{
      bitWrite(pressedButtons, 11, 0);
    }



    
}


void readIntensity(Gamecube_Report_t &gc_report)
{
  uint8_t temp;
  temp = map(gc_report.xAxis, 0, 256, 0, 127);
  if(temp != val_x){
     val_x = temp;
     updateControlSurfaces(); 
  }

  temp = map(gc_report.yAxis, 0, 256, 0, 127);
    if(temp != val_y){
     val_y = temp;
     updateControlSurfaces(); 
  }

  temp = map(gc_report.cxAxis, 0, 256, 0, 127);
  if(temp != val_cx){
   val_cx = temp;
   updateControlSurfaces(); 
  }

  temp = map(gc_report.cyAxis, 0, 256, 0, 127);
  if(temp != val_cy){
   val_cy = temp;
   updateControlSurfaces(); 
  }

  temp = map(gc_report.right, 0, 256, 0, 127);
  if(temp != val_right){
   val_right = temp;
   updateControlSurfaces(); 
  }

  temp = map(gc_report.left, 0, 256, 0, 127);
  if(temp != val_left){
   val_left = temp;
   updateControlSurfaces(); 
  }

  intensity = 126 - val_right;
  
}

void updateControlSurfaces(){
  controlChange(0, 0, val_x);
  controlChange(0, 1, val_y);
  controlChange(0, 2, val_cx);
  controlChange(0, 3, val_cy);
  controlChange(0, 4, val_right);
  controlChange(0, 5, val_left);
}

void playNotes()
{

  for (int i = 0; i < NUM_BUTTONS; i++)

  {

    if (bitRead(pressedButtons, i) != bitRead(previousButtons, i))

    {

      if (bitRead(pressedButtons, i))

      {

        bitWrite(previousButtons, i , 1);

        noteOn(0, notePitches[i], intensity);

        MidiUSB.flush();

      }

      else

      {

        bitWrite(previousButtons, i , 0);

        noteOff(0, notePitches[i], 0);

        MidiUSB.flush();

      }

    }

  }
}



// First parameter is the event type (0x0B = control change).
// Second parameter is the event type, combined with the channel.
// Third parameter is the control number number (0-119).
// Fourth parameter is the control value (0-127).

void controlChange(byte channel, byte control, byte value) {

  midiEventPacket_t event = {0x0B, 0xB0 | channel, control, value};

  MidiUSB.sendMIDI(event);
}


// First parameter is the event type (0x09 = note on, 0x08 = note off).
// Second parameter is note-on/note-off, combined with the channel.
// Channel can be anything between 0-15. Typically reported to the user as 1-16.
// Third parameter is the note number (48 = middle C).
// Fourth parameter is the velocity (64 = normal, 127 = fastest).

void noteOn(byte channel, byte pitch, byte velocity) {

  midiEventPacket_t noteOn = {0x09, 0x90 | channel, pitch, velocity};

  MidiUSB.sendMIDI(noteOn);
}

void noteOff(byte channel, byte pitch, byte velocity) {

  midiEventPacket_t noteOff = {0x08, 0x80 | channel, pitch, velocity};

  MidiUSB.sendMIDI(noteOff);
}
