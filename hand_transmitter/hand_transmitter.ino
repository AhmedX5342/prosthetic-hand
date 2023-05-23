#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

RF24 radio(7, 8); // CE, CSN

const byte address[6] = "00001";

// flex_state>780
int thumb = A0;
int index = A1;
int middle = A2;
int ring = A3;
int little = A4;

void setup() {
  radio.begin();
  radio.openWritingPipe(address);
  radio.setPALevel(RF24_PA_MIN);
  radio.stopListening();
  Serial.begin(9600);
}

void loop() {
  int thumb_state = analogRead(thumb);
  int index_state = analogRead(index);
  int middle_state = analogRead(middle);
  int ring_state = analogRead(ring);
  int little_state = analogRead(little);

  int flex_data[] = {thumb_state,index_state,middle_state,ring_state,little_state};
  //=============================================
//  //thumb
  Serial.print("thumb: ");
  Serial.print(flex_data[0]);
  Serial.println("");
//  //index
//  Serial.print("index: ");
//  Serial.print(index_state);
//  Serial.println("");
//  //middle
//  Serial.print("middle: ");
//  Serial.print(middle_state);
//  Serial.println("");
//  //ring
//  Serial.print("ring: ");
//  Serial.print(ring_state);
//  Serial.println("");
//  //little
//  Serial.print("little: ");
//  Serial.print(little_state);
//  Serial.println("");
  //=============================================
  radio.write(&flex_data, sizeof(flex_data));
  delay(150);
}
