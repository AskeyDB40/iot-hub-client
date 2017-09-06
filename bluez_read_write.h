

#ifndef BLUE_READ_WRITE_H_
#define BLUE_READ_WRITE_H_

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "./wiring.h"
#include "./gattlib.h"

#define SENSOR_TAG_MAC              "B0:B4:48:BA:3C:02"

#define UUID_System_ID              "00002a23-0000-1000-8000-00805f9b34fb"
#define UUID_Model_Number           "00002a24-0000-1000-8000-00805f9b34fb"
#define UUID_Serial_Number          "00002a25-0000-1000-8000-00805f9b34fb"
#define UUID_Firmware_REV           "00002a26-0000-1000-8000-00805f9b34fb"
#define UUID_Hardware_REV           "00002a27-0000-1000-8000-00805f9b34fb"
#define UUID_Software_REV           "00002a28-0000-1000-8000-00805f9b34fb"
#define UUID_Manufacturer_Name      "00002a29-0000-1000-8000-00805f9b34fb"
#define UUID_CERT_Data_List         "00002a2a-0000-1000-8000-00805f9b34fb"

#define UUID_Temperature_DATA       "f000aa01-0451-4000-b000-000000000000"
#define UUID_Temperature_CONFIG     "f000aa02-0451-4000-b000-000000000000"
#define UUID_Temperature_PERIOD     "f000aa03-0451-4000-b000-000000000000"
#define UUID_Humidity_DATA          "f000aa21-0451-4000-b000-000000000000"
#define UUID_Humidity_CONFIG        "f000aa22-0451-4000-b000-000000000000"
#define UUID_Humidity_PERIOD        "f000aa23-0451-4000-b000-000000000000"
#define UUID_Barometer_DATA         "f000aa41-0451-4000-b000-000000000000"
#define UUID_Barometer_CONFIG       "f000aa42-0451-4000-b000-000000000000"
#define UUID_Barometer_PERIOD       "f000aa43-0451-4000-b000-000000000000"
#define UUID_Luxometer_DATA         "f000aa71-0451-4000-b000-000000000000"
#define UUID_Luxometer_CONFIG       "f000aa72-0451-4000-b000-000000000000"
#define UUID_Luxometer_PERIOD       "f000aa73-0451-4000-b000-000000000000"
#define UUID_Movement_DATA          "f000aa81-0451-4000-b000-000000000000"
#define UUID_Movement_CONFIG        "f000aa82-0451-4000-b000-000000000000"
#define UUID_Movement_PERIOD        "f000aa83-0451-4000-b000-000000000000"

#define READ_COMMAND          1
#define WRITE_COMMAND         2

#define DISABLE_SENSOR             "00"
#define ENABLE_SENSOR              "01"

int readSensorTagMessage(int messageId, char *payload);
int read_write_main(char *DevMAC, int op, char *uuid, char *data);

#endif  // BLUE_READ_WRITE_H_
