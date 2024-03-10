#include <Arduino.h>

int TRIG_PIN = 9;               // Pino do trigger do sensor ultrassônico
int ECHO_PIN = 10;              // Pino do echo do sensor ultrassônico
int LATCH_PIN = 11;            // Pino do registrador de deslocamento
int CLOCK_PIN = 12;             // Pino do relógio do registrador da saída
int DATA_PIN = 13;              // Pino de dados do registrador de deslocamento
int DISTANCE_THRESHOLD = 20   // Distância de proximidade desejada em centímetros

byte leds = 0;

void setup() {
  Serial.begin(9600);
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  pinMode(LATCH_PIN, OUTPUT);
  pinMode(CLOCK_PIN, OUTPUT);
  pinMode(DATA_PIN, OUTPUT);
}

void loop() {
  long duration, distance;
  
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);
  
  duration = pulseIn(ECHO_PIN, HIGH);
  
  distance = duration * 0.034 / 2;
  
  Serial.print("Distance: ");
  Serial.println(distance);
  
  if (distance < DISTANCE_THRESHOLD) {
    leds = B10111111;  // Define a configuração dos LEDs
    tone(9, 1000);     // Emite um som de 1000 Hz
  } else {
    leds = B11111111;  // Todos os LEDs desligados
    noTone(9);         // Para de emitir som
  }
  
  digitalWrite(LATCH_PIN, LOW);  // Ativa o registrador de deslocamento
  shiftOut(DATA_PIN, CLOCK_PIN, LSBFIRST, leds); // Envia os dados para o registrador de deslocamento
  digitalWrite(LATCH_PIN, HIGH); // Desativa o registrador de deslocamento
  
  delay(100); // Espera um curto período antes de realizar a próxima medição
}
