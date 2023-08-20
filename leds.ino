#include <LiquidCrystal_I2C.h>

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
int led;

char* selectedFunction;
int selectedSpeed;
int selectedCycles;

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
  int led;
  int leds_size = 4;
  int leds[leds_size] = {LED1, LED2, LED3, LED4};

  int options_size = 3;
  char* options[options_size] = {"Functions", "Speed", "Cycles"};

  int functions_size = 3;
  char* functions[functions_size] = {"left", "right", "blink"};

  int speeds_size = 7;
  int speeds[speeds_size] = {1000, 800, 600, 400, 200, 100, 50};

  int cycles_size = 10;
  int cycles[cycles_size] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

  for ( char* option : options){
    bool hasChanged = false;
    int button1State = 0;
    int button2State = 0;
    int counter = 0;
    int lastButton1State = 0;
    int lastButton2State = 0;
    print(0, String(option));    
    // LEFT
    if (option == options[0]) {
      while (!hasChanged){
        button1State = digitalRead(BUTTON1);
        if (button1State != lastButton1State) {
          if (button1State == HIGH) {
            print(1, String(functions[counter]));
            counter++;
            selectedFunction = counter;
            if (counter == functions_size){
                counter = 0;
            }
          } 
          delay(50);
        }
        button2State = digitalRead(BUTTON2);
        if (button2State != lastButton2State) {
          if (button2State != HIGH) {
            hasChanged = true;
          } 
          delay(50);
          lastButton2State = button2State;
        }
        lastButton1State = button1State;
      }
    // RIGHT
    } else if (option == options[1]) {
      while (!hasChanged){
        button1State = digitalRead(BUTTON1);
        if (button1State != lastButton1State) {
          if (button1State == HIGH) {
            selectedSpeed = speeds[counter];
            print(1, String(selectedSpeed));
            counter++;
            if (counter == speeds_size){
                counter = 0;
            }
          } 
          delay(50);
        }
        button2State = digitalRead(BUTTON2);
        if (button2State != lastButton2State) {
          if (button2State != HIGH) {
            hasChanged = true;
          } 
          delay(50);
          lastButton2State = button2State;
        }
        lastButton1State = button1State;
      }    
    // BLINK
    } else if (option == options[2]) {
      while (!hasChanged){
        button1State = digitalRead(BUTTON1);
        if (button1State != lastButton1State) {
          if (button1State == HIGH) {
            selectedCycles = cycles[counter];
            print(1, String(selectedCycles));
            counter++;
            if (counter == cycles_size){
                counter = 0;
            }
          } 
          delay(50);
        }
        button2State = digitalRead(BUTTON2);
        if (button2State != lastButton2State) {
          if (button2State != HIGH) {
            hasChanged = true;
          } 
          delay(50);
          lastButton2State = button2State;
        }
        lastButton1State = button1State;
      }
    }
  }

  delay(dt);
  for (int cycle = 0; cycle < selectedCycles; cycle++){
    // LEFT
    if (selectedFunction == 1) {
      dt = selectedSpeed / leds_size;
      for (int i = 0; i < leds_size; i++){
        ligh_on(leds[i]);
        delay(dt);
      }
      ring();
      for (int i = 0; i < leds_size; i++){
        ligh_off(leds[i]);
        delay(dt);
      }
    // RIGHT
    } else if (selectedFunction == 2) {
      dt = selectedSpeed / leds_size;
      for (int i = leds_size; i > 0; i--){
        ligh_on(leds[i-1]);
        delay(dt);
      }
      ring();
      for (int i = leds_size; i > 0; i--){
        ligh_off(leds[i-1]);
        delay(dt);
      }
    // BLINK
    } else if (selectedFunction == 3) {
      dt = selectedSpeed;
      for (int i = leds_size; i > 0; i--){
        ligh_on(leds[i-1]);
      }
      ring();
      for (int i = leds_size; i > 0; i--){
        ligh_off(leds[i-1]);
      }
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

void ring(){
  tone(buzzer, 5000);
  delay(100);
  delay(dt);
  noTone(buzzer);
  delay(100);
}

void ligh_on(int led){
  digitalWrite(led, HIGH);
}
void ligh_off(int led){
  digitalWrite(led, LOW);
}

