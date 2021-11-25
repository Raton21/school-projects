/*
 * Blinking LED with millis 
 * Written by raton for school assignment 25.Nov.2021
Button is connected to pin 2. It starts blinking sequence. 

Sending number trough serial changes number of blinks

*/

#define startButton 2
#define LEDdelay 500  /blinking delay
short blinkCounter = 0; //LED blink counter
short inputCounter = 2; //counter for button press, blinks 2x by default
unsigned long previousMillis = 0; //for millis timing
bool LEDState; //stores state of led (changed in blinking function)


void setup()
{
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(startButton, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(startButton), button_ISR, FALLING); //calls button_ISR function when count button is pressed
 Serial.begin(9600);
}

void blinking() //takes care of blinking 
{
  if( (millis()- previousMillis) >= LEDdelay){   
    LEDState = !LEDState;// changes the state of LED
    previousMillis=millis();// remember current millis() time
    blinkCounter --;
  }
 digitalWrite(LED_BUILTIN,LEDState);
}

void button_ISR(){ //ISR function.. gets caled whenever count button is pressed
blinkCounter = inputCounter*2;
}

void loop() 
{

  
  if (blinkCounter){ //calls blinking function, if there are numbers left in counter
    blinking();
  }
  //************* serial reading *******
if (Serial.available() > 0) {
  char  incomingByte = Serial.read();
     inputCounter = incomingByte - '0';
    
    
    Serial.print("received: ");
    Serial.println(inputCounter);
  }
}
