#include <Wire.h>
#include <Bridge.h>
#include "Seeed_BME280.h"

//for reset Counter
int resetCounter = 0;

//for Bridge
char D13[2];
char valueStr[23];
int  valueInt=0;

const int UVpin  = A0;       //UV        A0
const int LUXpin = A1;       //照度      A1
const int pHpin  = A2;       //土壤酸鹼  A2
const int MoisturePin = A3;  //土壤濕度  A3
const int BugPin = 7;        //蟲罐      D7

BME280 bme280;   //BME 大氣壓   //D2(SDA), D3(SCL)
float Temperature=0.0;
uint32_t AtmosphericPressure=0, Humidity=0;

int BugCounter = 0;
int PreviousBugCounter = 9999;
long suspendTimestamp = millis();
void blink(){//Bugs
    if (millis()-suspendTimestamp > 180000){
        BugCounter += 1;
        suspendTimestamp = millis();
        Serial.println("xxxxxxxxxxxxxxxxx");
    }
}

void setup() {
    pinMode(UVpin,INPUT);        //UV     A0  
    pinMode(LUXpin,INPUT);       //Lux    A1  
    pinMode(pHpin,INPUT);        //pH     A2  
    pinMode(MoisturePin,INPUT);  //土壤濕度   A3
    pinMode(BugPin, INPUT_PULLUP);
    attachInterrupt(digitalPinToInterrupt(BugPin), blink, RISING);
    
    if(!bme280.init()) Serial.println("Sensor Error!");  //BME208 大氣壓 D2, D3
    
    Serial.begin(115200);
    Bridge.begin();   // D0 and D1 are used by the Bridge library.
 
    //IoTtalk successful registration notification
    pinMode(13,OUTPUT);    
}


void loop() {
    Bridge.get("Reg_done",  D13, 2);
    digitalWrite(13, atoi(D13));      

    const char *DFname[]={"UV1","UV2","pH1","Moisture1"};
    const int pinNum[]={UVpin, LUXpin, pHpin, MoisturePin};
    for(int i=0;i<=3;i++){
        valueInt = analogRead(pinNum[i]);     
        Serial.print(DFname[i]); Serial.print(": ");  Serial.println(valueInt);   
        itoa(valueInt, valueStr, 10); 
        Bridge.put(DFname[i], valueStr); 
    }

    
    Temperature = bme280.getTemperature();      //BME 大氣壓   D2, D3
    AtmosphericPressure = bme280.getPressure();
    Humidity = bme280.getHumidity();
    Serial.print("Temp: ");        Serial.print(Temperature);    Serial.println(" C");// unit: C
    Serial.print("Pressure: ");    Serial.print(AtmosphericPressure);    Serial.println(" Pa");     // unit: Pa
    Serial.print("Altitude: ");    Serial.print(bme280.calcAltitude(AtmosphericPressure));    Serial.println(" m");  // unit: meter
    Serial.print("Humidity: ");    Serial.print(Humidity);    Serial.println(" %"); // unit:%
    dtostrf(Temperature, 6, 2, valueStr);
    Bridge.put("Temperature", valueStr); 
    dtostrf(AtmosphericPressure, 8, 0, valueStr);
    Bridge.put("AtPressure", valueStr);     
    dtostrf(Humidity, 8, 0, valueStr);
    Bridge.put("Humidity", valueStr);        
    
    
    if (PreviousBugCounter != BugCounter){
        PreviousBugCounter = BugCounter;
        itoa(BugCounter, valueStr, 10);
        Bridge.put("Bugs", valueStr);
    }
    Serial.print("Bugs counter: ");    Serial.println(BugCounter);    

    Bridge.get("resetCounter",  valueStr, 5);
    if ( (strcmp(valueStr,"") != 0) and atoi(valueStr) != resetCounter){
        BugCounter = 0;
        Serial.println("Reset bug's counter.");
        resetCounter = atoi(valueStr);
    }

    Serial.println("    ");
    delay(10000);
}
