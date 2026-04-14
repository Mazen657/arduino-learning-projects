#include <LiquidCrystal.h>
#include <Keypad.h>
#include <string.h>

// LCD
LiquidCrystal lcd(13, 12, 11, 10, 9, 8);

// Keypad setup
const byte ROWS = 4;
const byte COLS = 4;

char hexaKeys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};

byte rowPins[ROWS] = {7, 6, 5, 4}; 
byte colPins[COLS] = {3, 2, 1, 0}; 

Keypad customKeypad = Keypad(makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS);

// Password system
String password = "1234";
String input = "";

int attempts = 3;

byte heart[8] = {
  B00000,
  B01010,
  B11111,
  B11111,
  B01110,
  B00100,
  B00000,
  B00000
};

void showHome() {
  lcd.createChar(0, heart);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Enter Password:");
  lcd.setCursor(0, 1);
}

void setup() {
  lcd.begin(16, 2);
  delay(200);
  showHome();
}

void loop() {
  char key = customKeypad.getKey();

  if (key) {

    // Clear input
    if (key == '*') {
      input = "";
      lcd.clear();
      lcd.print("Enter Password:");
      lcd.setCursor(0, 1);
    }

    // Submit password
    else if (key == '#') {
      lcd.clear();

      if (input == password) {
  		lcd.clear();
  		lcd.setCursor(0, 0);
 		lcd.print("Hello World!");

 		lcd.setCursor(0, 1);
 		for (int i = 0; i < 4; i++) {
  			lcd.write(byte(0));
		}

 		delay(3000);

  		input = "";
 		attempts = 3;

		lcd.clear();
  		lcd.print("Enter Password:");
  		lcd.setCursor(0, 1);
		}
      else {
        attempts--;
        lcd.print("Wrong Password");
        delay(1500);

        lcd.clear();

        if (attempts == 0) {
          lcd.print("SYSTEM LOCKED");
          while (true); // stop system
        }
        else {
          lcd.print("Attempts Left:");
          lcd.print(attempts);
          delay(1500);

          input = "";
          lcd.clear();
          lcd.print("Enter Password:");
          lcd.setCursor(0, 1);
        }
      }
    }

    // Add digit
    else {
      input += key;
      lcd.print("*"); // hide password
    }
  }
}