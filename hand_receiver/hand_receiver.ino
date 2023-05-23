#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

#include <Servo.h>

Servo servo_thumb;
Servo servo_index;
Servo servo_middle;
Servo servo_ring;
Servo servo_little;

RF24 radio(7, 8); // CE, CSN

const byte address[6] = "00001";

int flex_data[] = {0,0,0,0,0};

int little_state = 0;
int ring_state = 0;
int middle_state = 0;
int index_state = 0;
int thumb_state = 0;

int little_pos = 1;
int ring_pos = 1;
int middle_pos = 1;
int index_pos = 1;
int thumb_pos = 1;

void setup() {
  Serial.begin(9600);
  radio.begin();
  radio.openReadingPipe(0, address);
  radio.setPALevel(RF24_PA_MIN);
  radio.startListening();
  servo_little.attach(14);
  servo_ring.attach(15);
  servo_middle.attach(16);
  servo_index.attach(17);
  servo_thumb.attach(18);
}

void loop() {
  
  if (radio.available()) {
    radio.read(&flex_data, sizeof(flex_data));
    thumb_state = flex_data[0];
    index_state = flex_data[1];
    middle_state = flex_data[2];
    ring_state = flex_data[3];
    little_state = flex_data[4];
    Serial.println(thumb_state);
    Serial.println(thumb_pos);
    //---------------------------------closing fingers
    if(little_state>780 && little_pos==1){
      servo_little.write(0);
      little_pos=2;
      }
    if(ring_state>780 && ring_pos==1){
      servo_ring.write(0);
      ring_pos=2;
      }
    if(middle_state>780 && middle_pos==1){
      servo_middle.write(0);
      middle_pos=2;
      }
    if(index_state>780 && index_pos==1){
      servo_index.write(0);
      index_pos=2;
      }
    if(thumb_state>780 && thumb_pos==1){
      servo_thumb.write(0);
      Serial.println("closing");
      thumb_pos=2;
      }
    //---------------------------------opening fingers
     if(little_state<780 && little_pos==2){
      servo_little.write(180);
      little_pos=1;
      }
    if(ring_state<780 && ring_pos==2){
      servo_ring.write(180);
      ring_pos=1;
      }
    if(middle_state<780 && middle_pos==2){
      servo_middle.write(180);
      middle_pos=1;
      }
    if(index_state<780 && index_pos==2){
      servo_index.write(180);
      index_pos=1;
      }
    if(thumb_state<780 && thumb_pos==2){
      servo_thumb.write(180);
      thumb_pos=1;
      }
    //---------------------------------in progress
    delay(300);
    servo_little.write(90);
    servo_ring.write(90);
    servo_middle.write(90);
    servo_index.write(90);
    servo_thumb.write(90);
  }
}
