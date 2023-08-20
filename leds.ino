#include <LiquidCrystal_I2C.h>
#include <Wire.h>
#include <string.h> 

using namespace std;
LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);
const int BUTTON1 = 13;
const int BUTTON2 = 11;
const int buzzer = 12;
const int LED1=2;
const int LED2=3;
const int LED3=4;
const int LED4=5;
int dt = 500;

int button1State = 0;
int button1PushCounter = 0;
int lastButton1State = 0;

int button2State = 0;
int button2PushCounter = 0;
int lastButton2State = 0;

int buttonsState = 0;



void setup() {                
  pinMode(LED1, OUTPUT);  
  pinMode(LED2, OUTPUT);
  pinMode(LED3, OUTPUT);    
  pinMode(BUTTON1, INPUT_PULLUP);
  pinMode(BUTTON2, INPUT_PULLUP);
  pinMode(buzzer, OUTPUT);

  lcd.begin(16,2);
  lcd.backlight();
  lcd.setCursor(0,0);
  lcd.print("WELCOME");
}

void loop() {

char* selectedFunction = -1;
int selectedSpeed = -1;
int selectedCycles = -1;

int leds[4] = {LED1, LED2, LED3, LED4};

int options_size = 3;
char* options[options_size] = {"Functions", "Speed", "Cycles"};

int functions_size = 3;
char* functions[functions_size] = {"left", "right", "blink"};

int speeds_size = 5;
int speeds[speeds_size] = {1000, 800, 600, 400, 200};

int cycles_size = 5;
int cycles[cycles_size] = {1, 2, 3, 4, 5};

for ( char* option : options){

  int actual = -1;
  button1State = 0;
  button1PushCounter = 0;
  lastButton1State = 0;

  button2State = 0;
  lastButton2State = 0;

  print(0, String(option));
  
  if (option == options[0]) {
    while (selectedFunction == -1){
      button1State = digitalRead(BUTTON1);
      if (button1State != lastButton1State) {
        if (button1State == HIGH) {
          print(1, String(functions[button1PushCounter]));
          button1PushCounter++;
          actual = button1PushCounter;
          if (button1PushCounter == functions_size){
              button1PushCounter = 0;
              }
        } 
        delay(50);
      }

      button2State = digitalRead(BUTTON2);
      if (button2State != lastButton2State) {
        if (button2State != HIGH) {
          selectedFunction = actual;
        } 
        delay(50);
        lastButton2State = button2State;
      }
      lastButton1State = button1State;
    }

  
    } else if (option == options[1]) {
    while (selectedSpeed == -1){
      button1State = digitalRead(BUTTON1);
      if (button1State != lastButton1State) {
        if (button1State == HIGH) {
          print(1, String(speeds[button1PushCounter]));
          button1PushCounter++;
          actual = button1PushCounter;
          if (button1PushCounter == speeds_size){
              button1PushCounter = 0;
              }
        } 
        delay(50);
      }

      button2State = digitalRead(BUTTON2);
      if (button2State != lastButton2State) {
        if (button2State != HIGH) {
          selectedSpeed = speeds[actual];
        } 
        delay(50);
        lastButton2State = button2State;
      }
      lastButton1State = button1State;
    }

  } else if (option == options[2]) {
    while (selectedCycles == -1){
      button1State = digitalRead(BUTTON1);
      if (button1State != lastButton1State) {
        if (button1State == HIGH) {
          print(1, String(cycles[button1PushCounter]));
          button1PushCounter++;
          actual = button1PushCounter;
          if (button1PushCounter == cycles_size){
              button1PushCounter = 0;
              }
        } 
        delay(50);
      }

      button2State = digitalRead(BUTTON2);
      if (button2State != lastButton2State) {
        if (button2State != HIGH) {
          selectedCycles = actual;
        } 
        delay(50);
        lastButton2State = button2State;
      }
      lastButton1State = button1State;
    }
    }
  }

delay(500);

dt = selectedSpeed;
for (int cycle = 0; cycle < selectedCycles; cycle++){
  for (auto led : leds) {
      digitalWrite(led, HIGH);
      delay(dt);
      }
  tone(buzzer, 5000); // Send 1KHz sound signal...
  delay(100);        // ...for 1 sec
  delay(dt);
  noTone(buzzer);     // Stop sound...
  delay(100);        // ...for 1sec

  for (int led : leds) {
      digitalWrite(led, LOW);
      delay(dt);
  }
}



}


void print(int line, String text){
      lcd.setCursor(0,line);
      lcd.print("                ");
      lcd.setCursor(0,line);
      lcd.print(text);
}

