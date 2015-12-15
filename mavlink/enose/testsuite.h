/** @file
 *	@brief MAVLink comm protocol testsuite generated from enose.xml
 *	@see http://qgroundcontrol.org/mavlink/
 */
#ifndef ENOSE_TESTSUITE_H
#define ENOSE_TESTSUITE_H

#ifdef __cplusplus
extern "C" {
#endif

#ifndef MAVLINK_TEST_ALL
#define MAVLINK_TEST_ALL
static void mavlink_test_common(uint8_t, uint8_t, mavlink_message_t *last_msg);
static void mavlink_test_enose(uint8_t, uint8_t, mavlink_message_t *last_msg);

static void mavlink_test_all(uint8_t system_id, uint8_t component_id, mavlink_message_t *last_msg)
{
	mavlink_test_common(system_id, component_id, last_msg);
	mavlink_test_enose(system_id, component_id, last_msg);
}
#endif

#include "../common/testsuite.h"


static void mavlink_test_gas_sensor_measurement(uint8_t system_id, uint8_t component_id, mavlink_message_t *last_msg)
{
	mavlink_message_t msg;
        uint8_t buffer[MAVLINK_MAX_PACKET_LEN];
        uint16_t i;
	mavlink_gas_sensor_measurement_t packet_in = {
		17.0,45.0,73.0,101.0,53,120,187
    };
	mavlink_gas_sensor_measurement_t packet1, packet2;
        memset(&packet1, 0, sizeof(packet1));
        	packet1.raw_value = packet_in.raw_value;
        	packet1.raw_value_max = packet_in.raw_value_max;
        	packet1.raw_value_min = packet_in.raw_value_min;
        	packet1.zero_value_min = packet_in.zero_value_min;
        	packet1.technology = packet_in.technology;
        	packet1.manufacturer = packet_in.manufacturer;
        	packet1.mpn = packet_in.mpn;
        
        

        memset(&packet2, 0, sizeof(packet2));
	mavlink_msg_gas_sensor_measurement_encode(system_id, component_id, &msg, &packet1);
	mavlink_msg_gas_sensor_measurement_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
	mavlink_msg_gas_sensor_measurement_pack(system_id, component_id, &msg , packet1.technology , packet1.manufacturer , packet1.mpn , packet1.raw_value , packet1.raw_value_max , packet1.raw_value_min , packet1.zero_value_min );
	mavlink_msg_gas_sensor_measurement_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
	mavlink_msg_gas_sensor_measurement_pack_chan(system_id, component_id, MAVLINK_COMM_0, &msg , packet1.technology , packet1.manufacturer , packet1.mpn , packet1.raw_value , packet1.raw_value_max , packet1.raw_value_min , packet1.zero_value_min );
	mavlink_msg_gas_sensor_measurement_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
        mavlink_msg_to_send_buffer(buffer, &msg);
        for (i=0; i<mavlink_msg_get_send_buffer_length(&msg); i++) {
        	comm_send_ch(MAVLINK_COMM_0, buffer[i]);
        }
	mavlink_msg_gas_sensor_measurement_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);
        
        memset(&packet2, 0, sizeof(packet2));
	mavlink_msg_gas_sensor_measurement_send(MAVLINK_COMM_1 , packet1.technology , packet1.manufacturer , packet1.mpn , packet1.raw_value , packet1.raw_value_max , packet1.raw_value_min , packet1.zero_value_min );
	mavlink_msg_gas_sensor_measurement_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);
}

static void mavlink_test_enose(uint8_t system_id, uint8_t component_id, mavlink_message_t *last_msg)
{
	mavlink_test_gas_sensor_measurement(system_id, component_id, last_msg);
}

#ifdef __cplusplus
}
#endif // __cplusplus
#endif // ENOSE_TESTSUITE_H
