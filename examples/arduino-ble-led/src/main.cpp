#include <Arduino.h>
#include <bluefruit.h>

BLEService ledService = BLEService(0x1815);
BLECharacteristic ledChar = BLECharacteristic(0x2A56);

void ledWriteCallback(uint16_t conn_hdl, BLECharacteristic* chr,
                      uint8_t* data, uint16_t len);

void setupLedService() {
    ledService.begin();
    ledChar.setProperties(CHR_PROPS_WRITE);
    ledChar.setPermission(SECMODE_OPEN, SECMODE_OPEN);
    ledChar.setFixedLen(1);
    ledChar.setWriteCallback(ledWriteCallback);
    ledChar.begin();
}

void ledWriteCallback(uint16_t conn_hdl, BLECharacteristic* chr,
                      uint8_t* data, uint16_t len) {
    (void)conn_hdl;
    (void)chr;
    if (len >= 1) {
        digitalWrite(LED_BUILTIN, data[0] ? HIGH : LOW);
    }
}

void startAdv() {
    Bluefruit.Advertising.addFlags(BLE_GAP_ADV_FLAGS_LE_ONLY_GENERAL_DISC_MODE);
    Bluefruit.Advertising.addTxPower();
    Bluefruit.Advertising.addService(ledService);
    Bluefruit.Advertising.addName();
    Bluefruit.Advertising.restartOnDisconnect(true);
    Bluefruit.Advertising.setInterval(32, 244);
    Bluefruit.Advertising.setFastTimeout(30);
    Bluefruit.Advertising.start(0);
}

void setup() {
    pinMode(LED_BUILTIN, OUTPUT);
    Bluefruit.begin();
    Bluefruit.setName("nRF54L BLE LED");
    setupLedService();
    startAdv();
}

void loop() {
    delay(10000);
}
