/********************************************************************
 * Serial Reaction Timer
 * Written by: B. Huang, Nov. 17, 2014
 * 
 * Hardware connections:
 * LED: Pin 12
 * Button: Pin 7
 *
 * Upload this example, open up the serial monitor - set to 9600 bps. 
 * Push the button as soon as the light turn on.
 *******************************************************************/

int sound = false;     // enables the buzzer

/* Pin out definitions */
int ledPin = 12;       // connect LED between pin 12 and GND
int buttonPin = 7;     // connect push button between pin 7 and GND

int gameNum = 1;

unsigned long totalTime = 0;      // stores total time -- used for calculating average

unsigned long waitTime;  // Random "waiting" time before turning on the light
unsigned long zeroTime;  // Zero reference time
unsigned long reactTime; // Reaction Time

void setup()
{
  Serial.begin(9600);

  pinMode(ledPin, OUTPUT);
  pinMode(buttonPin, INPUT_PULLUP); // Sets the pull-up resistor for the button
  digitalWrite(ledPin, LOW); // sets pin LOW (GND)
  Serial.print("Iter");
  Serial.print("\t");
  Serial.print("React (ms)");
  Serial.println();
  Serial.print("==============");
  Serial.println();
}

void loop()
{
  randomSeed(analogRead(A5));    // Get noise to seed the random number generator
                                 // Use an un-used pin for the random noise.
  waitTime = random(2000, 3500); // randomTime from 2 to 3.5 seconds
  delay(waitTime);               // delay randomTime
  digitalWrite(ledPin, HIGH);    // turn on LED!

  zeroTime = millis();           // set zeroTime reference

  while(digitalRead(buttonPin) == HIGH)  // holding loop until button is pressed.
  {
  }

  reactTime = millis() - zeroTime; // calculation of reaction time
  totalTime = totalTime + reactTime;
  
  digitalWrite(ledPin, LOW);    // turn off LED!

// Display information to Serial Monitor //
 
  Serial.print(gameNum);
  Serial.print("\t");
  Serial.print(reactTime, 1);
  Serial.println();  

  fastBlink();  // feedback to show that you did something!

  gameNum++;

}

// Quickly blinks to button indicating the end of a game
void fastBlink()
{
  for(int x = 0 ; x < 7 ; x++)
  {
    digitalWrite(ledPin, HIGH);
    delay(60);
    digitalWrite(ledPin, LOW);
    delay(60);
  }
}
