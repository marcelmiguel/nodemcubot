// Control of external IO
#include "peripherals.h"

bool oldSWManual;
bool oldSWSim;

void initGPIO() {
    pinMode(RELAY1IO, OUTPUT);
    pinMode(RELAY2IO, OUTPUT);
    
    pinMode(SWITCH1IO, INPUT);
    pinMode(SWITCH2IO, INPUT);

    oldSWManual = getSwitch(SW_MANUAL);
    oldSWSim = getSwitch(SW_SIM);
}

bool relayAction(String relayID, String action) {
    int relay;
    int lineLevel;
    
    //Serial.println(relayID + " " + action);

    if (relayID == "1") {
        relay = RELAY1IO;
    } else if (relayID == "2") {
        relay = RELAY2IO;
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

    Serial.printf("Relay: %i %i\n", relay, lineLevel);

    digitalWrite(relay, lineLevel);
    return true;
}

// Specific logic
bool getSwitch(String switchID) {
    if (switchID == SW_MANUAL) {
        //Serial.printf("SW Manual: %i\n", digitalRead(SWITCH1IO));
        return digitalRead(SWITCH1IO)==HIGH;
    } else if (switchID == SW_SIM) {
        //Serial.printf("SW Sim: %i\n", digitalRead(SWITCH2IO));
        return digitalRead(SWITCH2IO)==HIGH;
    } else {
        return false;
    }
}

void handleIO() {
    bool newSWManual = getSwitch(SW_MANUAL);
    bool newSWSim = getSwitch(SW_SIM);
    
    if ((oldSWManual!=newSWManual) || (oldSWSim!=newSWSim)) { // Detected change
        if (oldSWManual!=newSWManual) {
            Serial.printf("SW Manual: new %i - old %i\n", newSWManual, oldSWManual);
        }
        if  (oldSWSim!=newSWSim) {
            Serial.printf("SW Sim: new %i - old %i\n", newSWSim, oldSWSim);
        }

        if ( newSWManual && !oldSWManual) { // Moved switch to Manual/Remote, so force relay
            motionRemote();
        } if ( newSWSim && !oldSWSim) { // Moved switch to Sim, so force relay
            motionOn();
        } else if ( !newSWManual && !newSWSim ) { // Moved to stop
            motionOff();
        }    
    }
    oldSWManual = newSWManual; 
    oldSWSim = newSWSim;
}

void motionOn() {
    relayAction("1", "off");
    relayAction("2", "on");
}

void motionOff() {
    relayAction("1", "off");
    relayAction("2", "off");
}

void motionRemote() {
    relayAction("1", "on");
    relayAction("2", "off");
}