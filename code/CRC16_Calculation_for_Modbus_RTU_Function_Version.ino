/*
  Sketch name: CRC16 calculation for Modbus-RTU function version
  Suggested board: Arduino UNO Rev3
  Purpose: 
    A simple example to calculate the CRC16 values for Modbus-RTU by using the library from Rob Tillaart.
    There are two routes to calculate the CRC16. 
    In the first route, all parameters are set at once.
    In the second route, the parameters are set one by one.
  Feature:
    This is a function version. It can be simply implemented in the user's project.
  Date:   6 July 2021
  Author: Dr. Hsien-Ching Chung
  ORCID:  https://orcid.org/0000-0001-9364-8858
*/

#include "CRC16.h" // CRC library from Rob Tillaart
#include "CRC.h"   // https://github.com/RobTillaart/CRC

// The data received from the Modbus-RTU device.
// This is an example data.
struct ByteArray { 
  byte Array[27] = {0x01,0x04,0x16,0x00,0x14,0x04,0xB0,0x02,0x00,0x00,
                    0x15,0x00,0x0C,0x00,0xFF,0x00,0x0E,0x00,0x27,0x00,
                    0x00,0x00,0x22,0x00,0x02,0x9A,0xC7}; 
} Data_Modbus;
// A structure type is a user-defined composite type. 
// It is composed of fields or members that can have different types. 
// It enables the programmer to create a variable that structures a selected set of data.

uint16_t  CRCx16;           // CRC16 value of Modbus-RTU
byte      HI_CRC16;         // High byte of CRCx16
byte      LO_CRC16;         // Low byte of CRCx16

// CRC16 variable name. Required for CRC_comparison_2()
// No need for CRC_comparison_1()
CRC16 crc; 

void setup()
{
  Serial.begin(115200);
  
  Serial.println("The first route");
  if ( CRC_comparison_1(Data_Modbus) ) {
    Serial.println("The CRC PASS. Do the main works.");
  } else {
    Serial.println("The CRC DOES NOT PASS. Resend and Reread the message.");
  }

  Serial.println("The second route");
  if ( CRC_comparison_2(Data_Modbus) ) {
    Serial.println("The CRC PASS. Do the main works.");
  } else {
    Serial.println("The CRC DOES NOT PASS. Resend and Reread the message.");
  }
}

void loop()
{
}

// The first route to calculate CRC16 for Modbus-RTU and return the condition of CRC_PASS.
bool CRC_comparison_1(struct ByteArray Data_Modbus) {
  bool CRC_PASS;
  int  DataSize = sizeof(Data_Modbus.Array);
  Serial.print("DataSize = ");
  Serial.println(DataSize);

  // Calculate CRC16. All parameters are set at once.
  // The parameters for calculting the CRC16/Modbus can be found in https://crccalc.com/ 
  // uint16_t = crc16(array, length, polynome = 0xA001, start = 0, end = 0, reverseIn = false, reverseOut = false)
  uint16_t CRCx16 = crc16(Data_Modbus.Array, DataSize-2, 0x8005, 0xFFFF, 0, true, true); 

  Serial.print("CRCx16: ");
  Serial.println(CRCx16, HEX);          // Show the CRC16 code on the serial monitor
  
  byte HI_CRC16 = highByte(CRCx16);     // Separate the CRC16 value into two bytes (highByte and lowByte)
  Serial.print("HI_CRC16: ");
  Serial.println(HI_CRC16, HEX);        // Show the high byte of the CRC16 code on the serial monitor
  byte LO_CRC16 = lowByte(CRCx16);
  Serial.print("LO_CRC16: ");
  Serial.println(LO_CRC16, HEX);        // Show the low byte of the CRC16 code on the serial monitor

  Serial.print("The received CRC16: "); // Show the received CRC16 code on the serial monitor
  Serial.print(Data_Modbus.Array[DataSize-1], HEX);
  Serial.println(Data_Modbus.Array[DataSize-2], HEX);

  // Compare the received data array and the HI/LO bytes of the CRC16 code
  if ( Data_Modbus.Array[DataSize-2] == LO_CRC16 && Data_Modbus.Array[DataSize-1] == HI_CRC16 ) {
    CRC_PASS = true;
    Serial.println(CRC_PASS);
    Serial.println("CRC success.");
    return CRC_PASS;
  } else {
    CRC_PASS = false;
    Serial.println(CRC_PASS);
    Serial.println("CRC failed. ");
    return CRC_PASS;
  }
}

// The second route to calculate CRC16 for Modbus-RTU and return the condition of CRC_PASS.
bool CRC_comparison_2(struct ByteArray Data_Modbus) {
  bool CRC_PASS;
  int  DataSize = sizeof(Data_Modbus.Array);
  Serial.print("DataSize = ");
  Serial.println(DataSize);
  
  crc.setPolynome(0x8005); // Set parameters one by one
  crc.setStartXOR(0xFFFF);
  crc.setReverseIn(true);
  crc.setReverseOut(true);
  
  for (int i = 0; i < 25; i++) // Calculate CRC16
  {
    crc.add(Data_Modbus.Array[i]);
  }
  CRCx16 = crc.getCRC(); // Get the calculated CRC16

  Serial.print("CRCx16: ");
  Serial.println(CRCx16, HEX);          // Show the CRC16 code on the serial monitor
  
  byte HI_CRC16 = highByte(CRCx16);     // Separate the CRC16 value into two bytes (highByte and lowByte)
  Serial.print("HI_CRC16: ");
  Serial.println(HI_CRC16, HEX);        // Show the high byte of the CRC16 code on the serial monitor
  byte LO_CRC16 = lowByte(CRCx16);
  Serial.print("LO_CRC16: ");
  Serial.println(LO_CRC16, HEX);        // Show the low byte of the CRC16 code on the serial monitor

  Serial.print("The received CRC16: "); // Show the received CRC16 code on the serial monitor
  Serial.print(Data_Modbus.Array[DataSize-1], HEX);
  Serial.println(Data_Modbus.Array[DataSize-2], HEX);

  // Compare the received data array and the HI/LO bytes of the CRC16 code
  if ( Data_Modbus.Array[DataSize-2] == LO_CRC16 && Data_Modbus.Array[DataSize-1] == HI_CRC16 ) {
    CRC_PASS = true;
    Serial.println(CRC_PASS);
    Serial.println("CRC success.");
    return CRC_PASS;
  } else {
    CRC_PASS = false;
    Serial.println(CRC_PASS);
    Serial.println("CRC failed. ");
    return CRC_PASS;
  }
}
