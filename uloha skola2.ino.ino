/*
 * Blinking LED with millis and interrupt
 * Written by raton for school assignment 12.Nov.2021

Buttons are connected to pins 3 and 4. Button on pin 3 adds 1 to variable, whenever it's pressed.
If you press second button, that value is transferred to different one and original variable is reset (so you can start adding up numbers again)
LED blinks 0.5s ON and 0.5s OFF. Number of blinks is determined by button presses. 
*/

//******** pin definition ******
#define countButton 3 
#define startButton 4
//****** blinking delay ******
#define LEDdelay 500
//******** global variables ******
short blinkCounter; //LED blink counter
short buttonPressCounter = 2; //counter for button press, blinks 2x by default
bool buttonState; //state of the button
bool prevButtonState; //previous state of button
bool LEDState; //stores state of led (changed in blinking function)
long previousMillis = 0; //for millis timing

//******* SETUP ******
void setup()
{
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(countButton, INPUT_PULLUP);
  pinMode(startButton, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(countButton), button_ISR, FALLING); //calls button_ISR function when count button is pressed

}
//******* FUNCTIONS ******
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
  buttonPressCounter ++ ;
}

void loop() 
{
 buttonState = !digitalRead(startButton); //reads start button 
  if ((buttonState == 1) && (prevButtonState == 0) && (blinkCounter ==0)){  //when button is pressed after not being pressed AND there isnt blinking in action 
    blinkCounter = buttonPressCounter*2; //stores value from button counter to blink counter *2 (one for every flip ON>OFF or OFF>ON) 
    buttonPressCounter = 0; //clears button counter
    prevButtonState = 1; //prevents holding start button
  }
  if ((buttonState == 0) && (prevButtonState == 1)){ // prevents holding start button
    prevButtonState = 0;
  }
  if (blinkCounter >0){ //calls blinking function, if there are numbers left in counter
    blinking();
  }

}