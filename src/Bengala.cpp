/*
 * Bengala Inteligente - leitura do sensor, filtro e alerta sonoro
 *
 * - lerDistanciaCM(): mede a distância com o HC-SR04 e aplica a média móvel.
 * - atualizarAlertaSonoro(): define o ritmo do buzzer conforme a distância.
 *
 * Os pinos estão definidos em Bengala.h.
 */
#include "Bengala.h"

// Filtro de média móvel (5 leituras) para suavizar o ruído do HC-SR04
const int NUM_LEITURAS = 5;
int leituras[NUM_LEITURAS];
int indiceLeitura = 0;
long somaLeituras = 0;

void setupBengala() {
    pinMode(PIN_TRIG, OUTPUT);
    pinMode(PIN_ECHO, INPUT);
    pinMode(PIN_BUZZER, OUTPUT);
    digitalWrite(PIN_TRIG, LOW);

    // Inicia a janela com zeros: nas primeiras leituras a média sai subestimada, até a janela encher
    for (int i = 0; i < NUM_LEITURAS; i++) {
        leituras[i] = 0;
    }
}

int lerDistanciaCM() {
    // Pulso ultrassônico
    digitalWrite(PIN_TRIG, HIGH);
    delayMicroseconds(10);
    digitalWrite(PIN_TRIG, LOW);

    // Mede o tempo do eco em µs; timeout de 30 ms (cerca de 5 m, acima do alcance do sensor)
    long duracao = pulseIn(PIN_ECHO, HIGH, 30000); 
    // Sem eco: 999 cm (sem obstáculo). Senão: distância = tempo × velocidade do som (0,034 cm/µs) ÷ 2, pois o som vai e volta
    int distanciaAtual = (duracao == 0) ? 999 : static_cast<int>(duracao * 0.034 / 2);

    // Remove da soma a leitura mais antiga, coloca a nova no lugar e avança o índice (buffer circular)
    somaLeituras = somaLeituras - leituras[indiceLeitura];
    leituras[indiceLeitura] = distanciaAtual;
    somaLeituras = somaLeituras + leituras[indiceLeitura];
    indiceLeitura = (indiceLeitura + 1) % NUM_LEITURAS;

    return static_cast<int>(somaLeituras / NUM_LEITURAS);
}

void atualizarAlertaSonoro(int distancia) {
    static unsigned long ultimaTrocaState = 0;
    static bool buzzerLigado = false;
    
    unsigned long tempoAtual = millis();
    unsigned long intervalo = 0; 

    // intervalo = tempo (ms) entre ligar e desligar o buzzer: quanto menor, mais rápido o bipe
    if (distancia > 0 && distancia <= 30) {
        intervalo = 80;   // Muito perto: bipes rápidos
    } else if (distancia > 30 && distancia <= 80) {
        intervalo = 250;  // Distância média
    } else if (distancia > 80 && distancia <= 150) {
        intervalo = 500;  // Distância longa
    } else {
        digitalWrite(PIN_BUZZER, LOW);
        buzzerLigado = false;
        return;
    }

    // Alterna o buzzer usando millis() (sem delay), para não travar a leitura do sensor
    if (tempoAtual - ultimaTrocaState >= static_cast<unsigned long>(intervalo)) {
        ultimaTrocaState = tempoAtual;
        buzzerLigado = !buzzerLigado;
        digitalWrite(PIN_BUZZER, buzzerLigado ? HIGH : LOW);
    }
}