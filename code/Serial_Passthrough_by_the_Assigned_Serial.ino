/*
  Sketch name: Serial passthrough by the assigned serial
  Suggested board: Arduino MEGA 2560 Rev3
  Purpose:
    1. Read and Send messages between two serial ports (Serial and AssignedSerial).
    2. The user can assign different serial ports to the "AssignedSerial."
       The name "AssignedSerial" can be specified by the user.
  Advantage:
    1. It's convenient to change the specific serial port easily, e.g., Serial1, Serial2, Serial3 (Serial#).
       We don't have to modify the Serial# in the entire program.
  Suggested system setup:
    1. A "TTL to USB device" is suggested to use for reading and sending messages through the "AssignedSerial."

  Date:   7 July 2021
  Author: Dr. Hsien-Ching Chung
  ORCID:  https://orcid.org/0000-0001-9364-8858
*/

#define AssignedSerial Serial1    // Assign Serial1 to the AssignedSerial
// #define AssignedSerial Serial2 // Assign Serial2 to the AssignedSerial
// #define AssignedSerial Serial3 // Assign Serial3 to the AssignedSerial

void setup() {
  Serial.begin(9600);
  AssignedSerial.begin(9600);
}

void loop() {
  if (Serial.available()) {               // If anything comes in Serial (USB)
    AssignedSerial.write(Serial.read());  // Read it and send it out through AssignedSerial
  }

  if (AssignedSerial.available()) {       // If anything comes in AssignedSerial
    Serial.write(AssignedSerial.read());  // Read it and send it out through Serial (USB)
  }
}
