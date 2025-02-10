#include <SPI.h>
#include "mcp_can.h"
#define CAN_CS_PIN 10
MCP_CAN CAN(CAN_CS_PIN);


bool belt;
bool park;

bool trunk;
bool rear_left_door;
bool rear_right_door;
bool front_left_door;
bool front_right_door;

long unsigned int rxId;
unsigned char len = 0;
unsigned char rxBuf[8];


static void snd_canbox_msg(uint8_t type, uint8_t* msg, uint8_t size) {
  uint8_t buf[4 + size];  
  buf[0] = 0x2e;          
  buf[1] = type;         
  buf[2] = size;         
  memcpy(buf + 3, msg, size); 
  buf[3 + size] = canbox_checksum(buf + 1, size + 2);  
  Serial.write(buf, sizeof(buf));
 }

static uint8_t canbox_checksum(uint8_t* buf, uint8_t len) {
  uint8_t sum = 0;
  for (uint8_t i = 0; i < len; i++)
    sum += buf[i];
  sum = sum ^ 0xff;
  return sum;
}

//// BUTTONS /////

 void canbox_up(void) {
  uint8_t buf[] = { 0x03, 0x01 };
  snd_canbox_msg(0x20, buf, sizeof(buf));

  buf[1] = 0x00;
  snd_canbox_msg(0x20, buf, sizeof(buf));
}
void canbox_down(void) {
  uint8_t buf[] = { 0x04, 0x01 };
  snd_canbox_msg(0x20, buf, sizeof(buf));

  buf[1] = 0x00;
  snd_canbox_msg(0x20, buf, sizeof(buf));
}


void vup(void) {
  uint8_t buf[] = { 0x01, 0x01 };
  snd_canbox_msg(0x20, buf, sizeof(buf));

  buf[1] = 0x00;
  snd_canbox_msg(0x20, buf, sizeof(buf));
}
void vd(void) {
  uint8_t buf[] = { 0x02, 0x01 };
  snd_canbox_msg(0x20, buf, sizeof(buf));

  buf[1] = 0x00;
  snd_canbox_msg(0x20, buf, sizeof(buf));
}

////BUTTONS END/////

void canbox_door_process(void)  //raise_vw_
{
  static uint8_t last_state = 0xFF; 
  uint8_t state = 0;
  
    if (belt)
 	state |= 0x80;
    if (park)
 	state |= 0x20;
  
  if (trunk)
     state |= 0x08;
  if (rear_right_door)
     state |= 0x20;
  if (rear_left_door)
      state |= 0x10;
  if (front_right_door)
   state |= 0x80; ///MQB
  if (front_left_door)
    state |= 0x40;

        if (state != last_state) { snd_canbox_msg(0x24, &state, 1); last_state = state; }
  }



void setup() {

 SPI.begin();
 Serial.begin(38400, SERIAL_8N1); 
 if (CAN.begin(MCP_ANY, CAN_500KBPS, MCP_8MHZ) == CAN_OK) {
    //Serial.println("CAN module initialized!");  
    } else {
    //Serial.println("CAN module initialization failed");
    while (1);
  }
  CAN.setMode(MCP_LISTENONLY);

            }
    
    
    
void loop() {
if (CAN_MSGAVAIL == CAN.checkReceive()) {
    CAN.readMsgBuf(&rxId, &len, rxBuf);  
    
    if (rxId == 0x000) /////change 0x000 to CAN ID
    
  //// MQB Platform style /////
    
     { rear_left_door = (rxBuf[0] & 0xFF) ? 1 : 0;
      rear_right_door = (rxBuf[0] & 0xFF) ? 1 : 0;
      front_left_door = (rxBuf[0] & 0xFF) ? 1 : 0;
      front_right_door = (rxBuf[0] & 0xFF) ? 1 : 0;
      trunk = (rxBuf[0] & 0xFF) ? 1 : 0;
      canbox_door_process(); }

    //////change rxBuf[0] to your CAN Frame byte position and 0xFF for correct values in your case///////

        }

    }