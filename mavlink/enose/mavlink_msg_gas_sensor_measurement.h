// MESSAGE GAS_SENSOR_MEASUREMENT PACKING

#define MAVLINK_MSG_ID_GAS_SENSOR_MEASUREMENT 150

typedef struct __mavlink_gas_sensor_measurement_t
{
 float raw_value; /*< Raw measured value*/
 float raw_value_max; /*< Max raw measured value*/
 float raw_value_min; /*< Min raw measured value*/
 float zero_value_min; /*< Zero raw measured value*/
 uint8_t technology; /*< Sensor technology, such as MOX or Electrolytic. See enum GAS_SENSOR_TECHNOLOGY*/
 uint8_t manufacturer; /*< Manufacturer of the sensor. See enum GAS_SENSOR_MANUFACTURER*/
 uint8_t mpn; /*< Manufacturer part number*/
} mavlink_gas_sensor_measurement_t;

#define MAVLINK_MSG_ID_GAS_SENSOR_MEASUREMENT_LEN 19
#define MAVLINK_MSG_ID_150_LEN 19

#define MAVLINK_MSG_ID_GAS_SENSOR_MEASUREMENT_CRC 64
#define MAVLINK_MSG_ID_150_CRC 64



#define MAVLINK_MESSAGE_INFO_GAS_SENSOR_MEASUREMENT { \
	"GAS_SENSOR_MEASUREMENT", \
	7, \
	{  { "raw_value", NULL, MAVLINK_TYPE_FLOAT, 0, 0, offsetof(mavlink_gas_sensor_measurement_t, raw_value) }, \
         { "raw_value_max", NULL, MAVLINK_TYPE_FLOAT, 0, 4, offsetof(mavlink_gas_sensor_measurement_t, raw_value_max) }, \
         { "raw_value_min", NULL, MAVLINK_TYPE_FLOAT, 0, 8, offsetof(mavlink_gas_sensor_measurement_t, raw_value_min) }, \
         { "zero_value_min", NULL, MAVLINK_TYPE_FLOAT, 0, 12, offsetof(mavlink_gas_sensor_measurement_t, zero_value_min) }, \
         { "technology", NULL, MAVLINK_TYPE_UINT8_T, 0, 16, offsetof(mavlink_gas_sensor_measurement_t, technology) }, \
         { "manufacturer", NULL, MAVLINK_TYPE_UINT8_T, 0, 17, offsetof(mavlink_gas_sensor_measurement_t, manufacturer) }, \
         { "mpn", NULL, MAVLINK_TYPE_UINT8_T, 0, 18, offsetof(mavlink_gas_sensor_measurement_t, mpn) }, \
         } \
}


/**
 * @brief Pack a gas_sensor_measurement message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 *
 * @param technology Sensor technology, such as MOX or Electrolytic. See enum GAS_SENSOR_TECHNOLOGY
 * @param manufacturer Manufacturer of the sensor. See enum GAS_SENSOR_MANUFACTURER
 * @param mpn Manufacturer part number
 * @param raw_value Raw measured value
 * @param raw_value_max Max raw measured value
 * @param raw_value_min Min raw measured value
 * @param zero_value_min Zero raw measured value
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_gas_sensor_measurement_pack(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg,
						       uint8_t technology, uint8_t manufacturer, uint8_t mpn, float raw_value, float raw_value_max, float raw_value_min, float zero_value_min)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
	char buf[MAVLINK_MSG_ID_GAS_SENSOR_MEASUREMENT_LEN];
	_mav_put_float(buf, 0, raw_value);
	_mav_put_float(buf, 4, raw_value_max);
	_mav_put_float(buf, 8, raw_value_min);
	_mav_put_float(buf, 12, zero_value_min);
	_mav_put_uint8_t(buf, 16, technology);
	_mav_put_uint8_t(buf, 17, manufacturer);
	_mav_put_uint8_t(buf, 18, mpn);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_GAS_SENSOR_MEASUREMENT_LEN);
#else
	mavlink_gas_sensor_measurement_t packet;
	packet.raw_value = raw_value;
	packet.raw_value_max = raw_value_max;
	packet.raw_value_min = raw_value_min;
	packet.zero_value_min = zero_value_min;
	packet.technology = technology;
	packet.manufacturer = manufacturer;
	packet.mpn = mpn;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_GAS_SENSOR_MEASUREMENT_LEN);
#endif

	msg->msgid = MAVLINK_MSG_ID_GAS_SENSOR_MEASUREMENT;
#if MAVLINK_CRC_EXTRA
    return mavlink_finalize_message(msg, system_id, component_id, MAVLINK_MSG_ID_GAS_SENSOR_MEASUREMENT_LEN, MAVLINK_MSG_ID_GAS_SENSOR_MEASUREMENT_CRC);
#else
    return mavlink_finalize_message(msg, system_id, component_id, MAVLINK_MSG_ID_GAS_SENSOR_MEASUREMENT_LEN);
#endif
}

/**
 * @brief Pack a gas_sensor_measurement message on a channel
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param technology Sensor technology, such as MOX or Electrolytic. See enum GAS_SENSOR_TECHNOLOGY
 * @param manufacturer Manufacturer of the sensor. See enum GAS_SENSOR_MANUFACTURER
 * @param mpn Manufacturer part number
 * @param raw_value Raw measured value
 * @param raw_value_max Max raw measured value
 * @param raw_value_min Min raw measured value
 * @param zero_value_min Zero raw measured value
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_gas_sensor_measurement_pack_chan(uint8_t system_id, uint8_t component_id, uint8_t chan,
							   mavlink_message_t* msg,
						           uint8_t technology,uint8_t manufacturer,uint8_t mpn,float raw_value,float raw_value_max,float raw_value_min,float zero_value_min)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
	char buf[MAVLINK_MSG_ID_GAS_SENSOR_MEASUREMENT_LEN];
	_mav_put_float(buf, 0, raw_value);
	_mav_put_float(buf, 4, raw_value_max);
	_mav_put_float(buf, 8, raw_value_min);
	_mav_put_float(buf, 12, zero_value_min);
	_mav_put_uint8_t(buf, 16, technology);
	_mav_put_uint8_t(buf, 17, manufacturer);
	_mav_put_uint8_t(buf, 18, mpn);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_GAS_SENSOR_MEASUREMENT_LEN);
#else
	mavlink_gas_sensor_measurement_t packet;
	packet.raw_value = raw_value;
	packet.raw_value_max = raw_value_max;
	packet.raw_value_min = raw_value_min;
	packet.zero_value_min = zero_value_min;
	packet.technology = technology;
	packet.manufacturer = manufacturer;
	packet.mpn = mpn;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_GAS_SENSOR_MEASUREMENT_LEN);
#endif

	msg->msgid = MAVLINK_MSG_ID_GAS_SENSOR_MEASUREMENT;
#if MAVLINK_CRC_EXTRA
    return mavlink_finalize_message_chan(msg, system_id, component_id, chan, MAVLINK_MSG_ID_GAS_SENSOR_MEASUREMENT_LEN, MAVLINK_MSG_ID_GAS_SENSOR_MEASUREMENT_CRC);
#else
    return mavlink_finalize_message_chan(msg, system_id, component_id, chan, MAVLINK_MSG_ID_GAS_SENSOR_MEASUREMENT_LEN);
#endif
}

/**
 * @brief Encode a gas_sensor_measurement struct
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 * @param gas_sensor_measurement C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_gas_sensor_measurement_encode(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, const mavlink_gas_sensor_measurement_t* gas_sensor_measurement)
{
	return mavlink_msg_gas_sensor_measurement_pack(system_id, component_id, msg, gas_sensor_measurement->technology, gas_sensor_measurement->manufacturer, gas_sensor_measurement->mpn, gas_sensor_measurement->raw_value, gas_sensor_measurement->raw_value_max, gas_sensor_measurement->raw_value_min, gas_sensor_measurement->zero_value_min);
}

/**
 * @brief Encode a gas_sensor_measurement struct on a channel
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param gas_sensor_measurement C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_gas_sensor_measurement_encode_chan(uint8_t system_id, uint8_t component_id, uint8_t chan, mavlink_message_t* msg, const mavlink_gas_sensor_measurement_t* gas_sensor_measurement)
{
	return mavlink_msg_gas_sensor_measurement_pack_chan(system_id, component_id, chan, msg, gas_sensor_measurement->technology, gas_sensor_measurement->manufacturer, gas_sensor_measurement->mpn, gas_sensor_measurement->raw_value, gas_sensor_measurement->raw_value_max, gas_sensor_measurement->raw_value_min, gas_sensor_measurement->zero_value_min);
}

/**
 * @brief Send a gas_sensor_measurement message
 * @param chan MAVLink channel to send the message
 *
 * @param technology Sensor technology, such as MOX or Electrolytic. See enum GAS_SENSOR_TECHNOLOGY
 * @param manufacturer Manufacturer of the sensor. See enum GAS_SENSOR_MANUFACTURER
 * @param mpn Manufacturer part number
 * @param raw_value Raw measured value
 * @param raw_value_max Max raw measured value
 * @param raw_value_min Min raw measured value
 * @param zero_value_min Zero raw measured value
 */
#ifdef MAVLINK_USE_CONVENIENCE_FUNCTIONS

static inline void mavlink_msg_gas_sensor_measurement_send(mavlink_channel_t chan, uint8_t technology, uint8_t manufacturer, uint8_t mpn, float raw_value, float raw_value_max, float raw_value_min, float zero_value_min)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
	char buf[MAVLINK_MSG_ID_GAS_SENSOR_MEASUREMENT_LEN];
	_mav_put_float(buf, 0, raw_value);
	_mav_put_float(buf, 4, raw_value_max);
	_mav_put_float(buf, 8, raw_value_min);
	_mav_put_float(buf, 12, zero_value_min);
	_mav_put_uint8_t(buf, 16, technology);
	_mav_put_uint8_t(buf, 17, manufacturer);
	_mav_put_uint8_t(buf, 18, mpn);

#if MAVLINK_CRC_EXTRA
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_GAS_SENSOR_MEASUREMENT, buf, MAVLINK_MSG_ID_GAS_SENSOR_MEASUREMENT_LEN, MAVLINK_MSG_ID_GAS_SENSOR_MEASUREMENT_CRC);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_GAS_SENSOR_MEASUREMENT, buf, MAVLINK_MSG_ID_GAS_SENSOR_MEASUREMENT_LEN);
#endif
#else
	mavlink_gas_sensor_measurement_t packet;
	packet.raw_value = raw_value;
	packet.raw_value_max = raw_value_max;
	packet.raw_value_min = raw_value_min;
	packet.zero_value_min = zero_value_min;
	packet.technology = technology;
	packet.manufacturer = manufacturer;
	packet.mpn = mpn;

#if MAVLINK_CRC_EXTRA
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_GAS_SENSOR_MEASUREMENT, (const char *)&packet, MAVLINK_MSG_ID_GAS_SENSOR_MEASUREMENT_LEN, MAVLINK_MSG_ID_GAS_SENSOR_MEASUREMENT_CRC);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_GAS_SENSOR_MEASUREMENT, (const char *)&packet, MAVLINK_MSG_ID_GAS_SENSOR_MEASUREMENT_LEN);
#endif
#endif
}

#if MAVLINK_MSG_ID_GAS_SENSOR_MEASUREMENT_LEN <= MAVLINK_MAX_PAYLOAD_LEN
/*
  This varient of _send() can be used to save stack space by re-using
  memory from the receive buffer.  The caller provides a
  mavlink_message_t which is the size of a full mavlink message. This
  is usually the receive buffer for the channel, and allows a reply to an
  incoming message with minimum stack space usage.
 */
static inline void mavlink_msg_gas_sensor_measurement_send_buf(mavlink_message_t *msgbuf, mavlink_channel_t chan,  uint8_t technology, uint8_t manufacturer, uint8_t mpn, float raw_value, float raw_value_max, float raw_value_min, float zero_value_min)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
	char *buf = (char *)msgbuf;
	_mav_put_float(buf, 0, raw_value);
	_mav_put_float(buf, 4, raw_value_max);
	_mav_put_float(buf, 8, raw_value_min);
	_mav_put_float(buf, 12, zero_value_min);
	_mav_put_uint8_t(buf, 16, technology);
	_mav_put_uint8_t(buf, 17, manufacturer);
	_mav_put_uint8_t(buf, 18, mpn);

#if MAVLINK_CRC_EXTRA
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_GAS_SENSOR_MEASUREMENT, buf, MAVLINK_MSG_ID_GAS_SENSOR_MEASUREMENT_LEN, MAVLINK_MSG_ID_GAS_SENSOR_MEASUREMENT_CRC);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_GAS_SENSOR_MEASUREMENT, buf, MAVLINK_MSG_ID_GAS_SENSOR_MEASUREMENT_LEN);
#endif
#else
	mavlink_gas_sensor_measurement_t *packet = (mavlink_gas_sensor_measurement_t *)msgbuf;
	packet->raw_value = raw_value;
	packet->raw_value_max = raw_value_max;
	packet->raw_value_min = raw_value_min;
	packet->zero_value_min = zero_value_min;
	packet->technology = technology;
	packet->manufacturer = manufacturer;
	packet->mpn = mpn;

#if MAVLINK_CRC_EXTRA
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_GAS_SENSOR_MEASUREMENT, (const char *)packet, MAVLINK_MSG_ID_GAS_SENSOR_MEASUREMENT_LEN, MAVLINK_MSG_ID_GAS_SENSOR_MEASUREMENT_CRC);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_GAS_SENSOR_MEASUREMENT, (const char *)packet, MAVLINK_MSG_ID_GAS_SENSOR_MEASUREMENT_LEN);
#endif
#endif
}
#endif

#endif

// MESSAGE GAS_SENSOR_MEASUREMENT UNPACKING


/**
 * @brief Get field technology from gas_sensor_measurement message
 *
 * @return Sensor technology, such as MOX or Electrolytic. See enum GAS_SENSOR_TECHNOLOGY
 */
static inline uint8_t mavlink_msg_gas_sensor_measurement_get_technology(const mavlink_message_t* msg)
{
	return _MAV_RETURN_uint8_t(msg,  16);
}

/**
 * @brief Get field manufacturer from gas_sensor_measurement message
 *
 * @return Manufacturer of the sensor. See enum GAS_SENSOR_MANUFACTURER
 */
static inline uint8_t mavlink_msg_gas_sensor_measurement_get_manufacturer(const mavlink_message_t* msg)
{
	return _MAV_RETURN_uint8_t(msg,  17);
}

/**
 * @brief Get field mpn from gas_sensor_measurement message
 *
 * @return Manufacturer part number
 */
static inline uint8_t mavlink_msg_gas_sensor_measurement_get_mpn(const mavlink_message_t* msg)
{
	return _MAV_RETURN_uint8_t(msg,  18);
}

/**
 * @brief Get field raw_value from gas_sensor_measurement message
 *
 * @return Raw measured value
 */
static inline float mavlink_msg_gas_sensor_measurement_get_raw_value(const mavlink_message_t* msg)
{
	return _MAV_RETURN_float(msg,  0);
}

/**
 * @brief Get field raw_value_max from gas_sensor_measurement message
 *
 * @return Max raw measured value
 */
static inline float mavlink_msg_gas_sensor_measurement_get_raw_value_max(const mavlink_message_t* msg)
{
	return _MAV_RETURN_float(msg,  4);
}

/**
 * @brief Get field raw_value_min from gas_sensor_measurement message
 *
 * @return Min raw measured value
 */
static inline float mavlink_msg_gas_sensor_measurement_get_raw_value_min(const mavlink_message_t* msg)
{
	return _MAV_RETURN_float(msg,  8);
}

/**
 * @brief Get field zero_value_min from gas_sensor_measurement message
 *
 * @return Zero raw measured value
 */
static inline float mavlink_msg_gas_sensor_measurement_get_zero_value_min(const mavlink_message_t* msg)
{
	return _MAV_RETURN_float(msg,  12);
}

/**
 * @brief Decode a gas_sensor_measurement message into a struct
 *
 * @param msg The message to decode
 * @param gas_sensor_measurement C-struct to decode the message contents into
 */
static inline void mavlink_msg_gas_sensor_measurement_decode(const mavlink_message_t* msg, mavlink_gas_sensor_measurement_t* gas_sensor_measurement)
{
#if MAVLINK_NEED_BYTE_SWAP
	gas_sensor_measurement->raw_value = mavlink_msg_gas_sensor_measurement_get_raw_value(msg);
	gas_sensor_measurement->raw_value_max = mavlink_msg_gas_sensor_measurement_get_raw_value_max(msg);
	gas_sensor_measurement->raw_value_min = mavlink_msg_gas_sensor_measurement_get_raw_value_min(msg);
	gas_sensor_measurement->zero_value_min = mavlink_msg_gas_sensor_measurement_get_zero_value_min(msg);
	gas_sensor_measurement->technology = mavlink_msg_gas_sensor_measurement_get_technology(msg);
	gas_sensor_measurement->manufacturer = mavlink_msg_gas_sensor_measurement_get_manufacturer(msg);
	gas_sensor_measurement->mpn = mavlink_msg_gas_sensor_measurement_get_mpn(msg);
#else
	memcpy(gas_sensor_measurement, _MAV_PAYLOAD(msg), MAVLINK_MSG_ID_GAS_SENSOR_MEASUREMENT_LEN);
#endif
}
