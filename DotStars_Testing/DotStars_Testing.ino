//DotStars LED power testing used for skripsie project MNS6 at the University of Stellenbosch
//Author: SP Botes 25985116
//Only run/uncomment one of the functions at a time, either staticTest() or dynamicTest() 
//otherwise the dynamicTest() will override the staticTest() LED values

//Required libraries to control the DotStars LEDs using an SPI interface
#include <Adafruit_DotStar.h>
#include <SPI.h> 

#define NUMPIXELS 72 // Number of LEDs in strip
Adafruit_DotStar strip(NUMPIXELS, DOTSTAR_RBG); 

void staticTest(int firstLEDs, unsigned long firstLEDsColorHex, int secondLEDS, unsigned long secondLEDsColorHex);
void dynamicTest();

void setup() {
  Serial.begin(115200); //Initialise serial port for debug messages

  strip.begin(); // Initialize pins for output
  strip.show();  // Turn all LEDs off ASAP

  staticTest(36, 0x0F0F0F, 36, 0x0F0F0F); //Example first 36 LEDs 50% white, second 36 LEDs 50% white
}


void loop() {

  //dynamicTest(); //only uncomment if staticTest() is commented out as well
  
}

void staticTest(int firstLEDs, unsigned long firstLEDsColorHex, int secondLEDS, unsigned long secondLEDsColorHex){
  //Set first number of LEDs to color [first LED index number = 0]
  for (int i = 0; i < firstLEDs; i++){
    strip.setPixelColor(i, firstLEDsColorHex); //sets the LED at index "i" to the desired color

    //used to confirm succesful code execution using the serial monitor
    Serial.print(i);
    Serial.print(": ");
    Serial.println(firstLEDsColorHex, HEX); 
  }

  //Set the second number of LEDs to another color
  for (int i = firstLEDs; i < (firstLEDs + secondLEDS); i++){
    strip.setPixelColor(i, secondLEDsColorHex); //sets the LED at index "i" to the desired color

    //used to confirm succesful code execution using the serial monitor
    Serial.print(i);
    Serial.print(": ");
    Serial.println(secondLEDsColorHex, HEX);
  }
  
}

void dynamicTest(){
  // strip.setPixelColor(head, color); // 'On' pixel at head
  // strip.setPixelColor(tail, 0);     // 'Off' pixel at tail
  // strip.show();                     // Refresh strip
  // delay(20);                        // Pause 20 milliseconds (~50 FPS)

  // if(++head >= NUMPIXELS) {         // Increment head index.  Off end of strip?
  //   head = 0;                       //  Yes, reset head index to start
  //   if((color >>= 8) == 0)          //  Next color (R->G->B) ... past blue now?
  //     color = 0xFF0000;             //   Yes, reset to red
  // }
  // if(++tail >= NUMPIXELS) tail = 0; // Increment, reset tail index
}
