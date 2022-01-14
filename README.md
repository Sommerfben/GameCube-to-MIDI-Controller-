# GameCube-to-MIDI-Controller-
Project to convert stock GameCube controller into a USB-MIDI controller with no hard mods. 

Full write up and tutorial available at https://www.instructables.com/Turn-a-GameCube-Controller-Into-a-USB-MIDI-Instrum/

Using a Pro Micro microcontroller, the code reads the serial data from the GameCube controller and converts it into USB MIDI messages. Theres a little external hardware required if you use a 5V variant of the Pro Micro to shift the logic levels down to the 3.3V that the controller requires. 

Requires two arduino libraries to build

  -MIDIUSB (validated up to v1.0.5) https://github.com/arduino-libraries/MIDIUSB
  
  -Nintendo (validated up to v1.4.0) https://www.arduino.cc/reference/en/libraries/nintendo/
  
  Maps the controls to the following diagram where the digital buttons act as a piano key and the analog controls act as MIDI control surfaces
  ![GC-Midi-map-diagram annotated](https://user-images.githubusercontent.com/32988623/149584996-543d8e43-b060-4464-8149-f8f04bf7f3ce.png)

## Wiring
  Simply connect the GameCube controller dataline to digital pin 2 on the Pro Micro. 
  ![GC Connecter color matched](https://user-images.githubusercontent.com/32988623/149585424-6f22aaac-7acc-4f09-a301-71f241d31069.png)
- White = 5V (Only used for the rumble motors so is optional)
- Red = Data (3.3V logic levels)
- Black = Ground
- Yellow = Ground
- Purple = Not connected
- Teal = 3.3V
- Purple = Cable Shielding/Not Connected
  
