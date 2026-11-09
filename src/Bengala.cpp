#include "Bengala.h"

// Configuração do Filtro de Média Móvel (Tratamento de Incertezas exigido pelo trabalho)
const int NUM_LEITURAS = 5;
int leituras[NUM_LEITURAS];
int indiceLeitura = 0;
long somaLeituras = 0;

void setupBengala() {
    pinMode(PIN_TRIG, OUTPUT);
    pinMode(PIN_ECHO, INPUT);
    pinMode(PIN_BUZZER, OUTPUT);
    digitalWrite(PIN_TRIG, LOW);

    // Inicializa o array de leituras com zero
    for (int i = 0; i < NUM_LEITURAS; i++) {
        leituras[i] = 0;
    }
}

int lerDistanciaCM() {
    // Pulso ultrassônico
    digitalWrite(PIN_TRIG, HIGH);
    delayMicroseconds(10);
    digitalWrite(PIN_TRIG, LOW);

    // Medição da resposta do eco (com timeout de 30ms)
    long duracao = pulseIn(PIN_ECHO, HIGH, 30000); 
    int distanciaAtual = (duracao == 0) ? 999 : static_cast<int>(duracao * 0.034 / 2);

    // Aplicação do Filtro de Média Móvel para eliminar ruídos do sensor
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

    // Define os intervalos de bip com base na distância filtrada
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

    // Temporizador assíncrono seguro (sem travar com delay)
    if (tempoAtual - ultimaTrocaState >= static_cast<unsigned long>(intervalo)) {
        ultimaTrocaState = tempoAtual;
        buzzerLigado = !buzzerLigado;
        digitalWrite(PIN_BUZZER, buzzerLigado ? HIGH : LOW);
    }
}