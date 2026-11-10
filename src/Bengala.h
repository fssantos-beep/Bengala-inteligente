/*
 * Bengala Inteligente - definições de pinos e funções
 *
 * Ligações no Arduino Uno:
 *
 *   Sensor ultrassônico HC-SR04
 *     VCC  -> 5V
 *     GND  -> GND
 *     TRIG -> D9   (saída: dispara o pulso ultrassônico)
 *     ECHO -> D10  (entrada: recebe o eco)
 *
 *   Buzzer ativo 5 V
 *     (+)  -> D8   (saída: liga e desliga o som)
 *     (-)  -> GND
 */
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