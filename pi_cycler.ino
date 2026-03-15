//Happy Pi Day 2026!
//Hope you enjoy 3.14159, This is Pi, followed by,
//26535 circumference over diameter :D

#include <LiquidCrystal_I2C.h>
#include <Wire.h>
#include <avr/pgmspace.h>

//Libraries and screen definition
LiquidCrystal_I2C lcd(0x27, 16, 2);

//Defintions :D
const int pi_button = 12;
const int pi_reset = 11;

//States :)
int press_count = 0;
bool update = false;
bool last_pi_state = HIGH;


//Array of strings :)
//An array of pi(e) :)
const char* pi_chunks[8] = {
  "1415926535897932",
  "3846264338327950",
  "2884197169399375",
  "1058209749445923",
  "0781640628620899",
  "8628034825342117",
  "0679............",
  "100 digits of Pi",
};


void setup() {
  lcd.init();
  lcd.backlight(); //Turns on the backlight :)

  //I'd still be defining those pins :D
  pinMode(pi_button, INPUT_PULLUP);
  pinMode(pi_reset, INPUT_PULLUP);

  //Essentially Greeting Screen
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print(F("Happy Pi Day '26"));
  lcd.setCursor(0,1);
  lcd.print(F("3..............."));
}

void loop() {
  //State system :D
  //So holding it doesn't do much :)
  bool pi_state = digitalRead(pi_button);

  // If the reset button is pressed, it will reset back to the start :)
  if(digitalRead(pi_reset) == LOW) {
    press_count = 0;
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print(F("Happy Pi Day '26"));
    bottom_clear();
    lcd.setCursor(0,1);
    lcd.print(F("3..............."));
    delay(314);
  }

  //If pressed once, a change system will now be activated :D
  if ((pi_state == LOW) && (last_pi_state == HIGH)) {
    update = true;
    //If over limited, will reset
    if (press_count >= 8){
      while (true) {
        lcd.setCursor(0,1);
        lcd.print(F("3..............."));
        delay(150); //Too lazy and too late at night, gonna use delay
      if(digitalRead(pi_button) == LOW) {
        press_count = 0;
        break;
       }
      }
    }

    delay(314);
  }

 last_pi_state = pi_state; //Makes the system possible for a flippy flip

 //Updating system
 if(update) {
  bottom_clear();
  lcd.setCursor(0,1);
  lcd.print(pi_chunks[press_count]); //If pressed, it will cycle through the double bytes of pi :)
  update = false; //Stops updating
  press_count++; //Adds one to the count
 }
}

//Custom function to clear the bottom row
void bottom_clear() {
  lcd.setCursor(0,1);
  lcd.print(F("                "));
}

//March 14th, 2026 (When I started writing)
//100 digits of Pi machine :D
//It's too late at night, Ima sleep now :D
