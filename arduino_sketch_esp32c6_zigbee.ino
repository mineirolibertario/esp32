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


