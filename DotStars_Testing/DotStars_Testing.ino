//DotStars LED power testing used for skripsie project MNS6 at the University of Stellenbosch
//Author: SP Botes 25985116
//Only run/uncomment one of the functions at a time, either staticTest() or dynamicTest() 
//otherwise the dynamicTest() will override the staticTest() LED values

//Required libraries to control the DotStars LEDs using an SPI interface
#include <Adafruit_DotStar.h>
#include <SPI.h> 
#define NUMPIXELS 72 // Number of LEDs in strip
unsigned long color = 0x00000F; //Staring color of dynamic test [50% brightness Blue = 0x00000F]
unsigned long OGcolor = color; //Save starting color to reset dynamic test colours

Adafruit_DotStar strip(NUMPIXELS, DOTSTAR_RBG); 

void staticTest(int firstLEDs, unsigned long firstLEDsColorHex, int secondLEDS, unsigned long secondLEDsColorHex);
//startPosition, Length (must be nagative), 
void dynamicColorTest(int head, int tail, unsigned long color, int tDelay,  unsigned long OGcolor);


void setup() {
  Serial.begin(115200); //Initialise serial port for debug messages

  strip.begin(); // Initialize pins for output
  strip.show();  // Turn all LEDs off ASAP

  staticTest(36, 0x0F0F0F, 36, 0x0F0F0F); //Example first 36 LEDs 50% white, second 36 LEDs 50% white
}


void loop() {

  // Only uncomment one of the two dynamic tests, if staticTest() is commented out as well
  dynamicColorTest(0, -10, color, 20, OGcolor); //Example for 10 LED ling trail at an approximate 20 ms refresh rate starting at 50% brighteness Blue [0x00000F]
  
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

void dynamicColorTest(int head, int tail, unsigned long color, int tDelay, unsigned long startColor){
  strip.setPixelColor(head, color); // 'On' pixel at head
  strip.setPixelColor(tail, 0);     // 'Off' pixel at tail
  strip.show();                     // Refresh strip
  delay(tDelay);                    // Pause milliseconds

  if(++head >= NUMPIXELS) {         // Increment head index.  Off end of strip?
    head = 0;                       //  Yes, reset head index to start
    if((color >>= 8) == 0)          //  Next color (R->B->G) ... past green now?
      color = startColor;             //  Yes, reset to red
  }
  if(++tail >= NUMPIXELS) tail = 0; // Increment, reset tail index
  
}
