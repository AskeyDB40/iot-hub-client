

#include "./bluez_read_write.h"

static uuid_t g_uuid;
long int value_data;
int random_index = 0;

int readSensorTagMessage(int messageId, char *payload)
{
	uint8_t buffer[100];
  uint16_t e, m;
	int i, ret, length;
	size_t len;
	gatt_connection_t* connection;
//  int ambient_temp_int;
  int32_t var1, var2, var3, T, ambient_temp_int;
  float temperature_1, temperature_2, temperature_3;
  float humidity, barometer, luxometer;
  
  len = sizeof(buffer);
  printf("readSensorTagMessage start()_12\n");

#if 1
// bluetooth connect
	connection = gattlib_connect(NULL, SENSOR_TAG_MAC, BDADDR_LE_PUBLIC, BT_SEC_LOW, 0, 0);
	if (connection == NULL) {
		fprintf(stderr, "Fail to connect to the bluetooth device.\n");
		return 1;
	}

// write temp config
	gattlib_string_to_uuid(UUID_Temperature_CONFIG, strlen(UUID_Temperature_CONFIG) + 1, &g_uuid);
	ret = gattlib_write_char_by_uuid(connection, &g_uuid, ENABLE_SENSOR, sizeof(ENABLE_SENSOR));
	assert(ret == 0);

// write humid config
	gattlib_string_to_uuid(UUID_Humidity_CONFIG, strlen(UUID_Humidity_CONFIG) + 1, &g_uuid);
	ret = gattlib_write_char_by_uuid(connection, &g_uuid, ENABLE_SENSOR, sizeof(ENABLE_SENSOR));
	assert(ret == 0);

// write baro config
	gattlib_string_to_uuid(UUID_Barometer_CONFIG, strlen(UUID_Barometer_CONFIG) + 1, &g_uuid);
	ret = gattlib_write_char_by_uuid(connection, &g_uuid, ENABLE_SENSOR, sizeof(ENABLE_SENSOR));
	assert(ret == 0);

// write luxo config
	gattlib_string_to_uuid(UUID_Luxometer_CONFIG, strlen(UUID_Luxometer_CONFIG) + 1, &g_uuid);
	ret = gattlib_write_char_by_uuid(connection, &g_uuid, ENABLE_SENSOR, sizeof(ENABLE_SENSOR));
	assert(ret == 0);
#if 0
// write move config
	gattlib_string_to_uuid(UUID_Movement_CONFIG, strlen(UUID_Movement_CONFIG) + 1, &g_uuid);
	ret = gattlib_write_char_by_uuid(connection, &g_uuid, ENABLE_SENSOR, sizeof(ENABLE_SENSOR));
	assert(ret == 0);
#endif
// delay for SensorTag response  
  delay(1000);
//  delay(700);

// read temp data
	gattlib_string_to_uuid(UUID_Temperature_DATA, strlen(UUID_Temperature_DATA) + 1, &g_uuid);
	ret = gattlib_read_char_by_uuid(connection, &g_uuid, buffer, &len);
	assert(ret == 0);
//  ambient_temp_int = ((buffer[3]<<8 + buffer[2]) >> 2) & 0x3FFF;  
  var1 = ((((int32_t)buffer[3]) << 8) + ((int32_t)buffer[2])) >> 2;
  var1 &= 0x3FFF;
  printf("var1 %x ", var1);
  temperature_1 = var1 * 0.03125;
  printf("%f \n", temperature_1);

  printf("Read temperature completed: ");
	for (i = 0; i < len; i++)
		printf("%02x ", buffer[i]);
	printf("\n");

// read humid data
	gattlib_string_to_uuid(UUID_Humidity_DATA, strlen(UUID_Humidity_DATA) + 1, &g_uuid);
	ret = gattlib_read_char_by_uuid(connection, &g_uuid, buffer, &len);
	assert(ret == 0);
	var1 = (((int32_t)buffer[3]) << 8) + ((int32_t)buffer[2]);
	var1 &= ~0x0003;
	var2 = (((int32_t)buffer[1]) << 8) + ((int32_t)buffer[0]);
	printf("var1 %x, var2 %x, ", var1, var2);
	humidity = ((double)var1/65536) * 100;
	temperature_2 = (((double)var2/65536) * 165) - 40;
	printf("%f %f \n", humidity, temperature_2);

	printf("Read humidity completed: ");
	for (i = 0; i < len; i++)
		printf("%02x ", buffer[i]);
	printf("\n");

// read baro data
	gattlib_string_to_uuid(UUID_Barometer_DATA, strlen(UUID_Barometer_DATA) + 1, &g_uuid);
	ret = gattlib_read_char_by_uuid(connection, &g_uuid, buffer, &len);
	assert(ret == 0);
	var1 = (((int32_t)buffer[5]) << 16) + (((int32_t)buffer[4]) << 8) + ((int32_t)buffer[3]);
	var2 = (((int32_t)buffer[2]) << 16) + (((int32_t)buffer[1]) << 8) + ((int32_t)buffer[0]);
	printf("var1 %x, var2 %x, ", var1, var2);
	barometer = (double)var1/100;
	temperature_3 = (double)var2/100;
	printf("%f %f \n", barometer, temperature_3);

	printf("Read barometer completed: ");
	for (i = 0; i < len; i++)
		printf("%02x ", buffer[i]);
	printf("\n");

// read luxo data
	gattlib_string_to_uuid(UUID_Luxometer_DATA, strlen(UUID_Luxometer_DATA) + 1, &g_uuid);
	ret = gattlib_read_char_by_uuid(connection, &g_uuid, buffer, &len);
	assert(ret == 0);
	var3 = (((int32_t)buffer[1]) << 8) + ((int32_t)buffer[0]); 
	m = var3 & 0x0FFF;
	e = (var3 & 0xF000) >> 12;
  printf("var3 %x, m %x, e %x, ", var3, m, e);
	/** e on 4 bits stored in a 16 bit unsigned => it can store 2 << (e - 1) with e < 16 */
	e = (e == 0) ? 1 : 2 << (e - 1);
	luxometer = m * (0.01 * e);
  printf("%f \n", luxometer);
  
	printf("Read luxometer completed: ");
	for (i = 0; i < len; i++)
		printf("%02x ", buffer[i]);
	printf("\n");
#if 0
// read move data
	gattlib_string_to_uuid(UUID_Movement_DATA, strlen(UUID_Movement_DATA) + 1, &g_uuid);
	ret = gattlib_read_char_by_uuid(connection, &g_uuid, buffer, &len);
	assert(ret == 0);
	printf("Read movement completed: ");
	for (i = 0; i < len; i++)
		printf("%02x ", buffer[i]);
	printf("\n");
#endif
#if 0
	gattlib_string_to_uuid(UUID_System_ID, strlen(UUID_System_ID) + 1, &g_uuid);
	ret = gattlib_read_char_by_uuid(connection, &g_uuid, buffer, &len);
	assert(ret == 0);
	printf("Read UUID completed: ");
	for (i = 0; i < len; i++)
		printf("%02x ", buffer[i]);
	printf("\n");
  
	gattlib_string_to_uuid(UUID_Model_Number, strlen(UUID_Model_Number) + 1, &g_uuid);
	ret = gattlib_read_char_by_uuid(connection, &g_uuid, buffer, &len);
	assert(ret == 0);
	printf("Read UUID completed: ");
	for (i = 0; i < len; i++)
		printf("%02x ", buffer[i]);
	printf("\n");
  
	gattlib_string_to_uuid(UUID_Serial_Number, strlen(UUID_Serial_Number) + 1, &g_uuid);
	ret = gattlib_read_char_by_uuid(connection, &g_uuid, buffer, &len);
	assert(ret == 0);
	printf("Read UUID completed: ");
	for (i = 0; i < len; i++)
		printf("%02x ", buffer[i]);
	printf("\n");
  
	gattlib_string_to_uuid(UUID_Firmware_REV, strlen(UUID_Firmware_REV) + 1, &g_uuid);
	ret = gattlib_read_char_by_uuid(connection, &g_uuid, buffer, &len);
	assert(ret == 0);
	printf("Read UUID completed: ");
	for (i = 0; i < len; i++)
		printf("%02x ", buffer[i]);
	printf("\n");
  
	gattlib_string_to_uuid(UUID_Hardware_REV, strlen(UUID_Hardware_REV) + 1, &g_uuid);
	ret = gattlib_read_char_by_uuid(connection, &g_uuid, buffer, &len);
	assert(ret == 0);
	printf("Read UUID completed: ");
	for (i = 0; i < len; i++)
		printf("%02x ", buffer[i]);
	printf("\n");
  
	gattlib_string_to_uuid(UUID_Software_REV, strlen(UUID_Software_REV) + 1, &g_uuid);
	ret = gattlib_read_char_by_uuid(connection, &g_uuid, buffer, &len);
	assert(ret == 0);
	printf("Read UUID completed: ");
	for (i = 0; i < len; i++)
		printf("%02x ", buffer[i]);
	printf("\n");
  
	gattlib_string_to_uuid(UUID_Manufacturer_Name, strlen(UUID_Manufacturer_Name) + 1, &g_uuid);
	ret = gattlib_read_char_by_uuid(connection, &g_uuid, buffer, &len);
	assert(ret == 0);
	printf("Read UUID completed: ");
	for (i = 0; i < len; i++)
		printf("%02x ", buffer[i]);
	printf("\n");
  
	gattlib_string_to_uuid(UUID_CERT_Data_List, strlen(UUID_CERT_Data_List) + 1, &g_uuid);
	ret = gattlib_read_char_by_uuid(connection, &g_uuid, buffer, &len);
	assert(ret == 0);
	printf("Read UUID completed: ");
	for (i = 0; i < len; i++)
		printf("%02x ", buffer[i]);
	printf("\n");
#endif

// bluetooth disconnect
	gattlib_disconnect(connection);

#endif


#if 1
    random_index ++;
    
//    float temperature_1 = 20 + random_index;
//    humidity = 60 + random_index;
    snprintf(payload,
             BUFFER_SIZE,
             "{ \"deviceId\": \"Raspberry Pi - C\", \"messageId\": %d, \"temperature\": %f, \"humidity\": %f, \"barometer\": %f, \"luxometer\": %f }",
             messageId,
             temperature_1,
             humidity,
             barometer,
             luxometer);
//    return 1;
#endif
  return 1;
}

