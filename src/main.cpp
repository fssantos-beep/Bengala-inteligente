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