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


//função para aviso sonoro
int buzzer = 49;
void sound(int delayTime, int quant){
  for(int i = 0; i < quant; i++){
      digitalWrite(buzzer, true);
      delay(delayTime);
      digitalWrite(buzzer, false);
      delay(delayTime);
  }
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

//função para digitar o resultado na tela
void result(int valor1, int valor2, char simbol){

}

void setup() {
  TV.begin(NTSC, 128, 96);    // inicia TV (PAL, 128x96)
  TV.select_font(font8x8);
  TV.clear_screen();
  pinMode(buzzer, OUTPUT);
  sound(200, 3);

  //inicializando
  typeText("---------------", 20);
  typeText("Strawberry v1.0", 50);
  typeText("---------------", 20);
  typeText("CPU    : ATmega", 30);
  typeText("Board  : Arduin", 30);
  typeText("Softw. : C/C++", 30);
  typeText("R. date: 06/25", 30);
  typeText("You    : $user", 30);
  typeText("---------------", 20);
  typeText("> Francisco P.", 50);
  typeText("> <- for exit", 50);
}

void loop() {
  // mantém a tela
}



