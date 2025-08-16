/*
Criado por: Francisco Passos
Criado em:  12/08/2025
Modif. em:  12/08/2025

Descrição:

Este software é o sistema operacional do meu projeto chamado "Strawberry". 
Fibonacci é um pequeno computador que imita os computadores antigos como 
o Macintosh, fabricado pela Apple em 1984. 

O monitor desse computador é uma miniTV de 5.5 polegadas e o seu teclado
é uma calculadora antiga que também imita muito a estética da década de 80.

O projeto consiste em que o usuário use a calculadora normalmente, mas em 
que seu resultado é processado, interpretado e mostrado por intermédio de
um microcontrolador. Neste caso, o ATmega 2560 (presente no Arduino Mega).

Bibliotecas: TVout

---------------
strawberry v1.0
---------------
CPU   :  ATmega
softw :  C++
author:  Frank
date  :  06/25
you   :  $user
---------------
> Francisco P.
> <- for exit
*/
#include <TVout.h>
#include <fontALL.h>

TVout TV;

const int buzzer = 49;
const byte ROWS = 5;
const byte COLS = 7;

bool infoB = false; 

// posição do cursor na TV
byte cursorX = 0;
byte cursorY = 0;

//linha e coluna
byte colPins[COLS] = {23, 22, 24, 28, 27, 26, 25};
byte rowPins[ROWS] = {30, 33, 32, 34, 35};

// Matriz
String hexaKeys[ROWS][COLS] = {
  {"OFF", "EX", "+/-", " ", " ", " ", " "},
  {"%", "/", "9", "8", "7", "MU", "->"},
  {"-", "x", "6", "5", "4", "MR", "GT"},
  {"=", "+", "3", "2", "1", "M-", "CE"},
  {" ", "0", "$", ".", ".", "M+", "ON"}
};

String getKey() {
  String keysPressed = "";
  for (byte col = 0; col < COLS; col++) {
    digitalWrite(colPins[col], LOW);
    for (byte row = 0; row < ROWS; row++) {
      if (digitalRead(rowPins[row]) == LOW) {
        delay(50);
        if (digitalRead(rowPins[row]) == LOW) {
          while (digitalRead(rowPins[row]) == LOW);
          keysPressed += hexaKeys[row][col];
          for (byte c = 0; c < COLS; c++) {
            digitalWrite(colPins[c], HIGH);
          }
        }
      }
    }
    digitalWrite(colPins[col], HIGH);
  }
  return keysPressed;
}

//função para o efeito de digitar na tela
void typeText(const char *text, int delayTime = 50) {
  while (*text) {
    TV.print(*text);
    delay(delayTime);    
    text++;
  }
  TV.print("\n");        
}

void clearScreen() {
  //resetar a memória nessa função
  //"desligar" o computador - talvez usar um relé no hardware seja uma boa escolha
  TV.clear_screen();
  cursorX = 0;
  cursorY = 0;
}

void sound(int quant, int delayTemp){
  for(int i = 0; i < quant; i++){
    digitalWrite(buzzer, HIGH);
    delay(delayTemp);
    digitalWrite(buzzer, LOW);
    delay(delayTemp);
  }
}

void setup() {
  TV.begin(NTSC, 128, 96);   
  TV.select_font(font8x8);
  TV.clear_screen();
  Serial.begin(9600);

  //aviso
  pinMode(buzzer, OUTPUT); 
  sound(3, 200);

  for (byte row = 0; row < ROWS; row++) { 
    pinMode(rowPins[row], INPUT_PULLUP); 
  } 

  for (byte col = 0; col < COLS; col++) { 
    pinMode(colPins[col], OUTPUT); 
    digitalWrite(colPins[col], HIGH); 
  }
}

void loop() {
  String customKey = getKey();
  if (customKey != "") {
    Serial.print(customKey);

    // digitação normal
    if(customKey != "->") {
      TV.set_cursor(cursorX, cursorY);
      TV.print(customKey.c_str());

      cursorX += 9 * customKey.length();
      if(cursorX > 120){
        cursorX = 0;
        cursorY += 8;
        if(cursorY > 88){
          clearScreen();
        }
      }
    }

    // toggle da tela infoB
    if (customKey == "->") {
      if(infoB == false){
        clearScreen();
        infoB = true;
        typeText("---------------", 20);
        typeText("Strawberry v1.0", 50);
        typeText("---------------", 20);
        typeText("CPU    :ATmega", 30);
        typeText("Board  :Arduino", 30);
        typeText("Softw  :BerryOS", 30);
        typeText("R. date: 06/25", 30);
        typeText("You    : $user", 30);
        typeText("---------------", 20);
        typeText("> Francisco P.", 50);
        typeText("> '->' for exit", 50);  
      } else {
        clearScreen();
        infoB = false;
      }
    }

    // limpa tela com ON ou OFF
    if(customKey == "ON" || customKey == "OFF"){
      clearScreen();
      infoB = false;
    }
  }
}




