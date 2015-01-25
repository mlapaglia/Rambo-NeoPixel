#include <Wire.h>
#include <Adafruit_NeoPixel.h>
 
#define PIN            7
#define NUMPIXELS      60
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);
 
struct toAux {
  int G;
  int M;
  float X;
  float Y;
  float Z;
  float E;
 
  uint8_t T; // temperature
  long S;
} myToAux;
 
int led = 13;
int currentLedLit = 0;
 
int currentLedBlue = 0;
int currentLedRed = 0;
int currentLedGreen = 0;
 
void setup()
{
  Wire.begin(4);                // join i2c bus with address #4
  Wire.onReceive(receiveEvent); // register event
  Serial.begin(9600);           // start serial for output
  pinMode(led, OUTPUT);
  pixels.begin();
}
 
void loop()
{
  delay(100);
}
 
unsigned char * bytes = (unsigned char *) &myToAux;
 
// function that executes whenever data is received from master
// this function is registered as an event, see setup()
void receiveEvent(int howMany)
{
  // if((howMany)!= sizeof(toAux)) return;
   
  digitalWrite(led, HIGH);
 
  int i = 0;
  while(Wire.available()) // loop through all but the last
  {
    bytes[i++] = Wire.read(); // receive byte as a character
  }
 
  if(myToAux.G != 0.00) {
    Serial.print("G: ");
    Serial.print(myToAux.G);
    Serial.print(" X: ");
    Serial.print(myToAux.X);
    Serial.print(" Y: ");
    Serial.print(myToAux.Y);
    Serial.print(" Z: ");
    Serial.print(myToAux.Z);
    Serial.print(" E: ");
    Serial.println(myToAux.E);
   
    if(myToAux.G == 1)
    {
      pixels.setPixelColor(currentLedLit, pixels.Color(currentLedRed,currentLedGreen,currentLedBlue));
     
      if(currentLedLit == NUMPIXELS)
      {
        currentLedLit = 0;
        for(int i = 0; i < NUMPIXELS; i++)
        {
          pixels.setPixelColor(i, pixels.Color(0,0,0));
        }        
      }
      else
      {
        currentLedLit++;
      }
     
     if(currentLedRed >= 255) {
       currentLedRed = 0;
       
     }
     
     if(currentLedGreen >= 255) {
       currentLedGreen = 0;
     
     }
     
     if(currentLedBlue >= 255) {
        currentLedBlue = 0;
     }
     
     currentLedRed += 5;
     currentLedGreen += 4;
     currentLedBlue += 3;
     
     pixels.show();
    }
  }
  else if(myToAux.M != 0.00) {
    Serial.print("M: ");
    Serial.print(myToAux.M);
    Serial.print(" T: ");
    Serial.print(myToAux.T);
    Serial.print(" S: ");
    Serial.println(myToAux.S);
  }
   
  digitalWrite(led, LOW);
}