#ifndef BENGALA_H
#define BENGALA_H

#include <Arduino.h>

// Definição dos Pinos
constexpr uint8_t PIN_TRIG = 9;
constexpr uint8_t PIN_ECHO = 10;
constexpr uint8_t PIN_BUZZER = 8;

// Protótipos das Funções
void setupBengala();
int lerDistanciaCM();
void atualizarAlertaSonoro(int distancia);

#endif