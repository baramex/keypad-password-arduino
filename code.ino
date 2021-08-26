/*
##########    keypad password   ##########
#          Developed by Baramex          #
### github: https://github.com/baramex ###

Licence: lgpl-3.0
*/

#include <Keypad.h>

String passwordcreat = "";
int tentative = 0;

//--edit this-- pins of items
int buzzer = 9;
int bleu = 11;
int rouge = 12;

//--edit this-- if you have differente version of keypad
const byte ROWS = 4;
const byte COLS = 3;
//--edit this-- if you have differente version of keypad
char hexaKeys[ROWS][COLS] = {
  {'1', '2', '3'},
  {'4', '5', '6'},
  {'7', '8', '9'},
  {'*', '0', '#'}
};

//--edit this-- pins keypad
byte rowPins[ROWS] = {2, 3, 4, 5};
byte colPins[COLS] = {6, 7, 8};

//--edit this--
String password = "0123456789";

Keypad kp = Keypad(makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS);

//--edit this-- it will be called when the password is correct
function callback() {

}

void setup() {
  pinMode(buzzer, OUTPUT);
  pinMode(bleu, OUTPUT);
  pinMode(rouge, OUTPUT);
  digitalWrite(bleu, 1);
}

void loop() {
  char k = kp.getKey();

  if (k) {
    digitalWrite(bleu, 0);
    tone(buzzer, 850, 100);
    delay(50);
    digitalWrite(bleu, 1);
    passwordcreat = passwordcreat + k;
    if (passwordcreat.length() == password.length()) {
      if (password == passwordcreat) {
        digitalWrite(bleu, 0);
        tone(buzzer, 523, 50);
        delay(50);
        tone(buzzer, 783, 50);
        delay(50);
        digitalWrite(bleu, 1);
        tone(buzzer, 1046, 50);
        delay(50);
        digitalWrite(bleu, 0);
        tone(buzzer, 1568, 50);
        delay(50);
        tone(buzzer, 2093, 70);
        delay(250);
        digitalWrite(bleu, 1);
        callback();
        tentative = 0;
      }
      else
      {
        if (tentative >= 3) {
          tentative = 0;
          digitalWrite(rouge, 1);
          digitalWrite(bleu, 0);
          for (int a = 0; a < 20; a++) {
            for (int x = 0; x < 180; x++) {
              int sinVal = (sin(x * (3.1412 / 180)));
              int toneVal = 2000 + (int(sinVal * 1000));
              tone(buzzer, toneVal);
              delay(2);
            }
          }
          tone(buzzer, 3500, 1800);
          digitalWrite(bleu, 1);
          digitalWrite(rouge, 0);
        }
        else {
          digitalWrite(rouge, 1);
          digitalWrite(bleu, 0);
          tone(buzzer, 370, 50);
          delay(100);
          tone(buzzer, 370, 300);
          delay(100);
          digitalWrite(rouge, 0);
          digitalWrite(bleu, 1);
          tentative++;
        }
      }
      passwordcreat = "";
    }
  }
}
