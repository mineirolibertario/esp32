/*

works with esp32-c6 devkit, mini
zigbee zstack 3.0

*/

#include "Zigbee.h"

SET_LOOP_TASK_STACK_SIZE( 32 * 1024 );

#define LED_PIN 8 
#define ZIGBEE_ENDPOINT 10

ZigbeeLight zbLight = ZigbeeLight(ZIGBEE_ENDPOINT);

void onLightChange(bool state) {
    if (state) {
        rgbLedWrite(LED_PIN, 0, 64, 0); 
    } else {
        rgbLedWrite(LED_PIN, 0, 0, 0); 
    }
}

void setup() {
    Serial.begin(115200);
    delay( 5 * 1000 ); // USB CDC issue

    Serial.println("\n=========================================");
    Serial.println("   ESP32-C6 ZIGBEE LED ONBOARD START     ");
    Serial.println("=========================================");

    rgbLedWrite(LED_PIN, 0, 0, 0);
    zbLight.onLightChange(onLightChange);

    // 1. Defina o estado inicial desejado antes de inicializar a biblioteca
    // Valores aceitos para StartUpOnOff:
    // 0x00 = Off (Sempre desliga ao ligar a energia)
    // 0x01 = On  (Sempre liga ao ligar a energia)
    // 0x02 = Toggle (Inverte o estado anterior)
    // 0xFF = Previous / Restaure (Mantém o último estado gravado na Flash)

    zbLight.setPowerOnState(0xFF); // Exemplo: restaura o estado anterior ao reiniciar
    zbLight.onLightChange(onLightChange);
    Zigbee.addEndpoint(&zbLight);
    Zigbee.addEndpoint(&zbLight);

    zbLight.setManufacturerAndModel("CustomESP32", "ESP32C6-DevKit");
    Serial.println("Zigbee...");

    if (!Zigbee.begin()) {
        Serial.println("fail !!!");
        while (1) { delay(1000); }
    }

    Serial.println("ok");
}

void loop() {
    delay(1000);
}


