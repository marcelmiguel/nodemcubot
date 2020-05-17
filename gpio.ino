// Control of external IO
#include "peripherals.h"

void initGPIO() {
    pinMode(RELAY1IO, OUTPUT);
    pinMode(RELAY2IO, OUTPUT);
    
    pinMode(SWITCH1IO, INPUT);
    pinMode(SWITCH2IO, INPUT);
}

bool relayAction(String relayID, String action) {
    uint relay;
    uint lineLevel;
    
    if (relayID == "1") {
        relay == RELAY1IO;
    } else if (relayID == "2") {
        relay == RELAY2IO;
    } else {
        return false;
    }
    
    if (action == "on") {
        lineLevel = HIGH;
    } else if (action == "off") {
        lineLevel = LOW;
    } else {
        return false;
    }

    digitalWrite(relay, lineLevel);
    return true;
}

// Specific logic
bool getSwitch(String switchID) {
    if (switchID == SW_MANUAL) {
        return digitalRead(SWITCH1IO);
    } else if (switchID == SW_SIM) {
        return digitalRead(SWITCH2IO);
    } else {
        return false;
    }
    
}

void handleIO() {
    if (getSwitch(SW_MANUAL)) {
        relayAction("2", "off");
        relayAction("1", "on");
    } if (getSwitch(SW_SIM)) {
        relayAction("1", "off");
        relayAction("2", "on");
    } else { // Stop
        relayAction("1", "off");
        relayAction("2", "off");
    }
}