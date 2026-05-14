#include <Arduino.h>
#include <bluefruit.h>

BLEUart bleuart;

void setup() {
    Serial.begin(115200);
    Bluefruit.begin();
    Bluefruit.setName("nRF54L BLEUART");
    bleuart.begin();

    Bluefruit.Advertising.addFlags(BLE_GAP_ADV_FLAGS_LE_ONLY_GENERAL_DISC_MODE);
    Bluefruit.Advertising.addTxPower();
    Bluefruit.Advertising.addService(bleuart);
    Bluefruit.Advertising.addName();
    Bluefruit.Advertising.restartOnDisconnect(true);
    Bluefruit.Advertising.setInterval(32, 244);
    Bluefruit.Advertising.setFastTimeout(30);
    Bluefruit.Advertising.start(0);
}

void loop() {
    while (bleuart.available()) {
        uint8_t ch = (uint8_t)bleuart.read();
        Serial.write(ch);
    }

    while (Serial.available()) {
        uint8_t ch = (uint8_t)Serial.read();
        bleuart.write(ch);
    }
}
