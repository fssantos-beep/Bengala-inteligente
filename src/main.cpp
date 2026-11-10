/*
 * Bengala Inteligente - programa principal
 *
 * A cada ciclo do loop():
 *   1. mede a distância do obstáculo (já filtrada por média móvel);
 *   2. atualiza o alerta sonoro conforme a distância;
 *   3. imprime a distância no monitor serial (115200 baud) a cada 200 ms.
 *
 * As funções estão em Bengala.cpp e os pinos em Bengala.h.
 */
#include <Arduino.h>
#include "Bengala.h"

void setup() {
    Serial.begin(115200);
    setupBengala();
    Serial.println("--- Bengala Inteligente Inicializada ---");
}

void loop() {
    int distancia = lerDistanciaCM();

    // Atualiza o alerta continuamente
    atualizarAlertaSonoro(distancia);

    // Exibe no Serial a cada 200ms para depuração
    static unsigned long ultimoPrint = 0;
    if (millis() - ultimoPrint >= 200) {
        ultimoPrint = millis();
        Serial.print("Distancia: ");
        Serial.print(distancia);
        Serial.println(" cm");
    }
}