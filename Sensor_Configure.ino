#include <SoftwareSerial.h>
int hum,val1,val2,vl3;
const byte nitro[] = {0x01,0x03, 0x00, 0x1e, 0x00, 0x01, 0xe4, 0x0c};
const byte phos[] = {0x01,0x03, 0x00, 0x1f, 0x00, 0x01, 0xb5, 0xcc};
const byte pota[] = {0x01,0x03, 0x00, 0x20, 0x00, 0x01, 0x85, 0xc0};
const int moistureThreshold = 500;
const int pumpRelayPin = 5;
const int pumpRelayPin1 = 6;
const int nutrientThreshold= 200;
byte NitrogenValues[8];
byte PhosphorousValues[8];
byte PotassiumValues[8];
SoftwareSerial bluetooth(0, 1);
SoftwareSerial mod(2, 3);
//SoftwareSerial bt(0, 1); 
void setup() {
  //pinMode(3, OUTPUT);
  // put your setup code here, to run once:
  Serial.begin(9600);
//   bt.begin(9600);
  pinMode(pumpRelayPin, OUTPUT);
    pinMode(pumpRelayPin1, OUTPUT);
   bluetooth.begin(9600);
  mod.begin(4800);
  delay(500);

 // digitalWrite(pumpRelayPin, HIGH);
 // digitalWrite(pumpRelayPin1, HIGH);

}

void loop() {
  // put your main code here, to run repeatedly:
   hum = analogRead(A0);
   int thresh[4];
   byte val1, val2, val3;
  val1 = nitrogen();
  delay(1500);
  val2 = phosphorous();
  delay(1500);
  val3 = potassium();
  delay(1500);
//int hum_thr,nit_thr;
 //if (bluetooth.available()) {
 //   String receivedText = bluetooth.readStringUntil('\n');
 //   Serial.println( receivedText);

    // if (receivedText.length() > 0) {
    //   // Process received text
    //  Serial.println( receivedText);

      // Parse received values
      ////int values[4];
    //  char *token = strtok((char *)receivedText.c_str(), ",");
      //int i = 0;

//       while (token != NULL && i < 4) {
//         values[i++] = atoi(token);
//         token = strtok(NULL, ",");
//       }
// //int j=0;
//       // Print parsed values
//       //Serial.println("Parsed values:");
//       for (int j = 0; j < 4; j++) {
//         //Serial.print("Value ");
//        // Serial.print(j + 1);
//        // Serial.print(": ");
//        Serial.println(values[j]);
//        thresh[j]=values[j];

//       // Clear the received text (optional)
//       receivedText = "";
//     }
 // }
  // Your other code here
 //




//  Serial.print("Soil Moisture Level: ");
//  Serial.println(temp);
   Serial.print((int)hum);
  if ((int)hum > moistureThreshold) {
    // If below threshold, turn on the pump and nutrient relays
    digitalWrite(pumpRelayPin, LOW);
    //delay(2000);
   // digitalWrite(pumpRelayPin, HIGH);
    //delay(3000);
   }
//   // else if((int)hum < thresh[0]){
//   // digitalWrite(pumpRelayPin, HIGH);
//   // }
  else {
    // If above threshold, turn off the pump and nutrient relays
    digitalWrite(pumpRelayPin, HIGH);
  }
   Serial.print(";");
// // //  
 if ((int)val1 < nutrientThreshold) {
    // If below threshold, turn on the pump and nutrient relays
    digitalWrite(pumpRelayPin1, LOW);
    //  delay(2000);
    // digitalWrite(pumpRelayPin1, HIGH);
    // delay(3000);
  }
  else {
    // If above threshold, turn off the pump and nutrient relays
    digitalWrite(pumpRelayPin1, HIGH);
  }


  // if ((int)hum > 0) {
  //   // If below threshold, turn on the pump and nutrient relays
  //   digitalWrite(pumpRelayPin, LOW);
  // }
  // if ((int)val1 < nutrientThreshold) {
  //   // If below threshold, turn on the pump and nutrient relays
  //   digitalWrite(pumpRelayPin1, LOW);

  //  }
  // delay(4000);
  // digitalWrite(pumpRelayPin, HIGH);
  // delay(100);
  // digitalWrite(pumpRelayPin1, HIGH);
  // delay(4000);

  // digitalWrite(pumpRelayPin, LOW);
  // delay(100);
  // digitalWrite(pumpRelayPin1, LOW);
  // delay(4000);

  //  digitalWrite(pumpRelayPin, HIGH);
  // delay(100);
  // digitalWrite(pumpRelayPin1, HIGH);
  // delay(4000);

//  // Serial.print("Nitrogen: ");
  Serial.print((int)val1);
  Serial.print(";");

// //Serial.print("Phosphorous: ");
  Serial.print((int)val2);
 Serial.print(";");

//   //Serial.print("Potassium: ");
  Serial.print((int)val3);
  Serial.print(";");
  
   delay(3000);
}
 


byte nitrogen() {
  mod.write(nitro, 8);
  delay(100);
  //if(mod.write(nitro,sizeof(nitro))==8){
  for (byte i = 0; i < 7; i++) {
    NitrogenValues[i] = mod.read();
//    Serial.print(NitrogenValues[i], HEX);
  }
//  Serial.println();
  
  return NitrogenValues[4];
}

byte phosphorous() {
  mod.write(phos, 8);
  delay(100);
 // if(mod.write(phos,sizeof(phos))==8){
  for (byte i = 0; i < 7; i++) {
    PhosphorousValues[i] = mod.read();
//    Serial.print(PhosphorousValues[i], HEX);
  }
//  Serial.println();

  return PhosphorousValues[4];
}

byte potassium() {
  mod.write(pota, 8);
  delay(100);
  //if(mod.write(pota,sizeof(pota))==8){
  for (byte i = 0; i < 7; i++) {
    PotassiumValues[i] = mod.read();
//    Serial.print(PotassiumValues[i], HEX);
  }
//  Serial.println();
  
  return PotassiumValues[4];
}