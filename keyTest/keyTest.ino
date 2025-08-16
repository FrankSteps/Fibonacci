/*
  Programa apenas para testar a funcionalidade das teclas do Strawberry
  Criado por: Francisco Passos
  Criado em:  16/08/25
*/

const byte ROWS = 5;
const byte COLS = 7;

byte colPins[COLS] = {23, 22, 24, 28, 27, 26, 25};
byte rowPins[ROWS] = {30, 33, 32, 34, 35};

// Armazena o estado anterior das teclas
bool keyState[ROWS][COLS];

void setup() {
  Serial.begin(9600);

  for (byte row = 0; row < ROWS; row++) pinMode(rowPins[row], INPUT_PULLUP);
  for (byte col = 0; col < COLS; col++) {
    pinMode(colPins[col], OUTPUT);
    digitalWrite(colPins[col], HIGH);
  }

  // Inicializa o estado como solto
  for (byte row = 0; row < ROWS; row++)
    for (byte col = 0; col < COLS; col++)
      keyState[row][col] = false;

  Serial.println("Teste de teclado iniciado...");
}

void loop() {
  for (byte col = 0; col < COLS; col++) {
    digitalWrite(colPins[col], LOW);  // ativa coluna
    delay(1); // curto delay para estabilizar

    for (byte row = 0; row < ROWS; row++) {
      bool pressed = (digitalRead(rowPins[row]) == LOW);

      // Se o estado mudou, imprime apenas a mudança
      if (pressed != keyState[row][col]) {
        keyState[row][col] = pressed;
        Serial.print("Coluna ");
        Serial.print(col);
        Serial.print(" Linha ");
        Serial.print(row);
        Serial.print(" ");
        Serial.println(pressed ? "PRESIONADA" : "LIBERADA");
      }
    }

    digitalWrite(colPins[col], HIGH); // desativa coluna
  }
}
