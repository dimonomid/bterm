%% machine NaviTech;
%% alphtype byte;

%%{

# Используемые действия

action STORE_PACKET_LENGTH {
	_packetLength=(ushort) (ToUShort() & 0x7FFF);
	
	Logger.Debug("Packet Length: {0}", _packetLength);
}

action CLEAR_LAST_INDEX {
	_lastIndex = 0;
}

action READ_IMEI {
	_imei[_lastIndex++] = fc;
}

action READ_BYTES {
	_numBuf[_lastIndex++] = fc;
}

action READ_HARDWARE_VERSION {
	_hardwareVersion = fc;

	Logger.Debug("Hardware Version: {0}", _hardwareVersion);
}

action READ_SOFTWARE_VERSION {
	_softwareVersion = fc;

	Logger.Debug("Software Version: {0}", _softwareVersion);
}

action STORE_DEVICE_ID {
	_deviceId = ToUShort();
	
	Logger.Debug("Device Id: {0}", _deviceId);
}

action STORE_PACKET_NO {
	_packetNo = ToUShort();
	
	Logger.Debug("Packet No: {0}", _packetNo);
}

action STORE_NEXT_PACKET {
	unchecked {
		_packetNo++;
	}

	Logger.Debug("Next packet No: {0}", _packetNo);
}

action STORE_DATE_TIME {
	int seconds = ToInt();
	_datetime = ToDateTime(seconds);

	Logger.Debug("Message DateTime: {0}", _datetime);
}

action DELTA_DATETIME {
	byte delta = fc;
	_datetime = _datetime.AddSeconds(delta);

	Logger.Debug("Next message DateTime: {0} [added {1} sec]", _datetime, delta);
}

action STORE_GPS_DATA {
	_numSattelites = (byte)(fc & 0x0F);
	_isGpsValid = (fc & 0xF0) == 0;

	Logger.Debug("SatNum: {0} | IsCoordValid: {1}", _numSattelites, _isGpsValid);
}

action STORE_LATITUDE {
	_latitude = ToInt()/1E6d;
}

action STORE_LONGITUDE {
	_longitude = ToInt()/1E6d;
}

action STORE_SPEED {
	_speed = ToUShort()/10f;
	Logger.Debug("Speed: {0}", _speed);
}

action STORE_AZIMUTH {
	_azimuth = ToUShort()/10f;
	Logger.Debug("Azimuth: {0}", _azimuth);
}

action STORE_HEIGHT {
	_height = ToShort();
	Logger.Debug("Height: {0}", _height);
}

action STORE_HDOP {
	_hdop = fc / 10f;
	Logger.Debug("HDOP: {0}", _hdop);
}

action STORE_STATE {
	_state = ToUShort();
	Logger.Debug("State: 0x{0:X}", _state);
}

action STORE_MAIN_VOLT {
	_mainVolt = ToUShort();
	Logger.Debug("Main power: {0}mV",_mainVolt);
}

action STORE_RESERVE_VOLT {
	_reserveVolt = ToUShort();
	Logger.Debug("Reserve power: {0}mV",_reserveVolt);
}

action STORE_TEMP {
	_temp = (sbyte) fc;
	Logger.Debug("Temperature: {0}", _temp);
}

action STORE_ACC {
	_acc = ToInt();
	Logger.Debug("Accelerometer: 0x{0:X}", _acc);
}

action STORE_OUTPUT_STATE {
	_outputState = ToUShort();
	Logger.Debug("Output state: {0:X}", _outputState);
}

action STORE_INPUT_STATE {
	_inputState = ToUShort();
	Logger.Debug("Input state: {0:X}", _inputState);
}

action STORE_ANALOG_INPUT_NO {
	_inputNo = (byte) (fc - FirstAnalogInputId);
}

action STORE_DIGITAL_INPUT_NO {
	_inputNo = (byte) (fc - FirstDigitalInputId);
}

action STORE_ANALOG_INPUT {
	_input = ToUShort();
	Logger.Debug("Analog Input #{0}: {1}mV", _inputNo, _input);
}

action STORE_DIGITAL_INPUT {
	_input = ToUShort();
	Logger.Debug("Digital Input #{0}: {1}", _inputNo, _input);
}

action STORE_REQ_NO {
	int reqNo=ToInt();
	Logger.Debug("ReqNo: {0}", reqNo);
}

action STORE_VAR_LENGTH {
	_varLength = fc;
	_curLength = 0;
	_varString = new byte[_varLength];
}

action STORE_VAR_STRING {
	_varString[_curLength++] = fc;

	if (_curLength >= _varLength)
	{
		var request = System.Text.Encoding.ASCII.GetString(_varString,0,_varString.Length);
		_varString = null;

		Logger.Debug("Request: {0}", request);

		fret;
	}
}

action STORE_CRC {
	_crc = ToUShort();
}

action CLEAR_PACKET_LENGTH {
	_currentPacketLength = 0;
}

action TEST_PACKET_LENGTH {
	if (_currentPacketLength >= _packetLength)
	{
		fret;
	}
}

action INC_CUR_PACKET_LENGTH
{
	_currentPacketLength++;
}

action GET_TAG {
	fhold; 
	fcall tag;
}

action CLEAR_CRC {
	_actualCrc = 0xFFFF;
}

action CALC_CRC {
	CalcCrc(fc);
}

action GET_PACKET {
	fhold;
	fcall packet;
}

action RETURN {
	fret;
}

# ----------------------------------------------------------

action PROCESS_IMEI {
	string imei = System.Text.Encoding.ASCII.GetString(_imei,0,_imei.Length);
	
	Logger.Debug("IMEI: {0}", imei);

	DoAuth(imei);
}

action PROCESS_COORD {
	Logger.Debug("Lat: {0} / Lon: {1}", _latitude, _longitude);

	ProcessCoord(_datetime, _isGpsValid, _numSattelites, _latitude, _longitude);
}

action PROCESS_SPEED_AZIMUTH {
	ProcessSpeedAzimuth(_datetime, _speed, _azimuth);
}

action PROCESS_HEIGHT {
	ProcessHeight(_datetime, _height);
}

action PROCESS_HDOP {
	ProcessHDOP(_datetime, _hdop);
}

action PROCESS_STATE {
	ProcessState(_datetime, _state);
}

action PROCESS_MAIN_VOLT {
	ProcessMainVolt(_datetime, _mainVolt);
}

action PROCESS_RESERVE_VOLT {
	ProcessReserveVolt(_datetime, _reserveVolt);
}

action PROCESS_TEMP {
	ProcessTemperature(_datetime, _temp);
}

action PROCESS_ACC {
	ProcessAccelerometer(_datetime, _acc);
}

action PROCESS_OUTPUT_STATE {
	ProcessOutputState(_datetime, _outputState);
}

action PROCESS_INPUT_STATE {
	ProcessInputState(_datetime, _inputState);
}

action PROCESS_ANALOG_INPUT {
	ProcessAnalogInput(_datetime, _inputNo, _input);
}

action PROCESS_DIGITAL_INPUT {
	ProcessDigitalInput(_datetime, _inputNo, _input);
}

action PROCESS_BEGIN_PACKET {
	ProcessBeginPacket();
}

action PROCESS_PACKET_END {
	bool isValid = _crc == _actualCrc;

	Logger.Debug("IsValid: {0} [Crc: {1:X} | Actual Crc: {2:X}]", isValid, _crc, _actualCrc);
	ProcessPacketEnd(isValid);
}

action PROCESS_DATA_ERROR {
	Logger.Debug("Error in received data: pos: {0} data: {1}", fpc, BitConverter.ToString(data));
	Logger.Debug("Unprocessed data: {0}", BitConverter.ToString(data, fpc));

	ProcessDataError();
	fbreak;
}

}%%

%%{

# Определения

# Сигнатура – фиксированная последовательность байтов – 01
signature = (0x01);

# Длина пакета в байтах – целое 2 байта (старший бит отбрасывается)
length = (any{2} >CLEAR_LAST_INDEX $READ_BYTES @STORE_PACKET_LENGTH);

# Теги

# 01 – Модель устройства – целое 1 байт
hardware_version = (0x01 any $READ_HARDWARE_VERSION);

# 02 – Версия прошивки – целое 1 байт
software_version = (0x02 any $READ_SOFTWARE_VERSION);

# 03 – IMEI – 15 байт
imei = (0x03 any{15} >CLEAR_LAST_INDEX $READ_IMEI @PROCESS_IMEI);

# 04 – Номер устройства – целое 2 байта
device_id = (0x04 any{2} >CLEAR_LAST_INDEX $READ_BYTES @STORE_DEVICE_ID);

# 10 – Номер пакета – целое 2 байта
packet_no = (0x10 any{2} >CLEAR_LAST_INDEX $READ_BYTES @STORE_PACKET_NO);

# 11 – Следующий пакет – без параметров
next_packet = (0x11 >STORE_NEXT_PACKET);

# 20 – Дата/время – целое 4 байта, в формате UTC (секунды с 01.01.1970 00:00:00)
datetime = (0x20 any{4} >CLEAR_LAST_INDEX $READ_BYTES @STORE_DATE_TIME);

# 21 – Изменение даты/времени – целое 1 байт
datetime_delta = (0x21 any $DELTA_DATETIME);

# 30 – Координаты в движении – запись
#	 кол-во спутников/признак валидности – целое 1 байт; кол-во спутников в младшей тетраде, валидность – в старшей
#	 широта – целое 4 байта (6 знаков после точки), градусы
#	 долгота – целое 4 байта (6 знаков после точки), градусы
coord = (0x30 any $STORE_GPS_DATA any{4} >CLEAR_LAST_INDEX $READ_BYTES @STORE_LATITUDE any{4} >CLEAR_LAST_INDEX $READ_BYTES @STORE_LONGITUDE @PROCESS_COORD);

# 33 – Скорость и направление движения – запись
#	 скорость – целое 2 байта (1 знак после точки), км/ч
#	 направление – целое 2 байта (1 знак после точки), градусы
speed_azimuth = (0x33 any{2} >CLEAR_LAST_INDEX $READ_BYTES @STORE_SPEED any{2} >CLEAR_LAST_INDEX $READ_BYTES @STORE_AZIMUTH @PROCESS_SPEED_AZIMUTH);

# 34 – Высота - целое 2 байта, м
height = (0x34 any{2} >CLEAR_LAST_INDEX $READ_BYTES @STORE_HEIGHT @PROCESS_HEIGHT);

# 35 – HDOP – целое 1 байт (1 знак после точки)
hdop = (0x35 any $STORE_HDOP @PROCESS_HDOP);

# 40 – Статус – целое 2 байта
state = (0x40 any{2} >CLEAR_LAST_INDEX $READ_BYTES @STORE_STATE @PROCESS_STATE);

# 41 – Напряжение питания – целое 2 байта (3 знака после точки)
mainVolt = (0x41 any{2} >CLEAR_LAST_INDEX $READ_BYTES @STORE_MAIN_VOLT @PROCESS_MAIN_VOLT);

# 42 – Напряжение на аккумуляторе – целое 2 байта (3 знака после точки)
reserveVolt = (0x42 any{2} >CLEAR_LAST_INDEX $READ_BYTES @STORE_RESERVE_VOLT @PROCESS_RESERVE_VOLT);

# 43 – Температура – целое 1 байт
temp = (0x43 any $STORE_TEMP @PROCESS_TEMP);

# 44 – Данные с акселерометра – запись, 10 бит по каждой оси – целое 4 байта
acc = (0x44 any{4} >CLEAR_LAST_INDEX $READ_BYTES @STORE_ACC @PROCESS_ACC);

# 45 – Состояние выходов - целое 2 байта
output_state = (0x45 any{2} >CLEAR_LAST_INDEX $READ_BYTES @STORE_OUTPUT_STATE @PROCESS_OUTPUT_STATE);

# 46 – Состояние входов - целое 2 байта
input_state = (0x46 any{2} >CLEAR_LAST_INDEX $READ_BYTES @STORE_INPUT_STATE @PROCESS_INPUT_STATE);

# 50..57 – аналоговые входы IN0..IN7
analog_input_tag = 0x50 .. 0x57;
analog_input = (analog_input_tag $STORE_ANALOG_INPUT_NO any{2} >CLEAR_LAST_INDEX $READ_BYTES @STORE_ANALOG_INPUT @PROCESS_ANALOG_INPUT);

# 58 .. 5F - цифровые входы IN0..IN7
digital_input_tag = 0x58 .. 0x5F;
digital_input = (digital_input_tag $STORE_DIGITAL_INPUT_NO any{2} >CLEAR_LAST_INDEX $READ_BYTES @STORE_DIGITAL_INPUT @PROCESS_DIGITAL_INPUT);

# E0 – Номер запроса – целое 4 байта
req_no = (0xE0 any{4} >CLEAR_LAST_INDEX $READ_BYTES @STORE_REQ_NO);

# E1 – Текст запроса/ответа – запись
#	 длина строки – 1 байт
#	 строка – последовательность символов; кол-во символов определяется полем длина строки

request = (0xE1 @{fcall read_var_string;});

# Последовательность элементов тег – 1 байт – значение (тип и длина однозначно зависят от тега)
tag := (hardware_version | software_version | imei | device_id | packet_no | next_packet 
	   | datetime | datetime_delta | coord | speed_azimuth | height | hdop | state
	   | mainVolt | reserveVolt | temp | acc | output_state | input_state
	   | analog_input | digital_input | req_no | request) $CALC_CRC $INC_CUR_PACKET_LENGTH $TEST_PACKET_LENGTH @RETURN $!PROCESS_DATA_ERROR @/PROCESS_DATA_ERROR;

# CRC – 2 байта
crc = (any{2} >CLEAR_LAST_INDEX >{fhold;} $READ_BYTES @STORE_CRC);

# Пакет – одна или несколько записей, передаваемых одновременно
packet := signature >CLEAR_CRC $CALC_CRC %PROCESS_BEGIN_PACKET length $CALC_CRC %CLEAR_PACKET_LENGTH (any* $TEST_PACKET_LENGTH $GET_TAG)* @/PROCESS_DATA_ERROR;

# Чтение строки переменной длины
read_var_string := any $STORE_VAR_LENGTH $CALC_CRC (any $INC_CUR_PACKET_LENGTH $CALC_CRC $STORE_VAR_STRING)* @/PROCESS_DATA_ERROR;

# Протокол
main := (signature $GET_PACKET crc @PROCESS_PACKET_END $!PROCESS_DATA_ERROR @/PROCESS_DATA_ERROR)*;

}%%

#region	Подключаемые пространства имен

using System;

#endregion

namespace Scs.NaviTech
{
	internal sealed partial class NaviTech
	{
		#region Внутренние переменные
		private static readonly DateTime BaseTimestamp = new DateTime(1970, 1, 1, 0, 0, 0, DateTimeKind.Utc);
		
		private const byte FirstAnalogInputId = 0x50;
		private const byte FirstDigitalInputId = 0x58;

		private int _lastIndex;
		private byte[] _numBuf = new byte[sizeof(long)];
		
		private byte _varLength;
		private byte _curLength;
		private byte[] _varString;

		private ushort _packetLength;
   		private ushort _currentPacketLength;

		private byte[] _imei = new byte[15];
		
		private byte _hardwareVersion;
		private byte _softwareVersion;

		private ushort _deviceId;
		private ushort _packetNo;
		
		private ushort _crc;
		private ushort _actualCrc;

		private DateTime _datetime;

		private bool _isGpsValid; 
		private byte _numSattelites;
		private double _latitude;
		private double _longitude;

		private float _speed;
		private float _azimuth;

		private short _height;
		private float _hdop;

		private ushort _state;
		
		private ushort _mainVolt;
		private ushort _reserveVolt;

		private sbyte _temp;
		private int _acc;

		private ushort _inputState;
		private ushort _outputState;

		private byte _inputNo;
		private ushort _input;

		#region	Переменные КА

		%% variable cs _cs;	
		private int _cs;

		%% variable stack _stack;
		private int[] _stack = new int[16];

		%% variable top _top;
		private int _top;

		%% write data noerror nofinal;


		#endregion

		#endregion

		#region	Частичные методы для обработки

		partial void DoAuth(string imei);
		partial void ProcessCoord(DateTime datetime, bool isGpsValid, byte numSattelites, double latitude, double longitude);
		partial void ProcessSpeedAzimuth(DateTime datetime, float speed, float azimuth);
		partial void ProcessHeight(DateTime datetime, short height);
		partial void ProcessHDOP(DateTime datetime, float hdop);
		partial void ProcessState(DateTime datetime, ushort state);
		partial void ProcessMainVolt(DateTime datetime, ushort mainVolt);
		partial void ProcessReserveVolt(DateTime datetime, ushort reserveVolt);
		partial void ProcessTemperature(DateTime datetime, sbyte temp);
		partial void ProcessAccelerometer(DateTime datetime, int acc);
		partial void ProcessOutputState(DateTime datetime, ushort outputState);
		partial void ProcessInputState(DateTime datetime, ushort inputState);
		partial void ProcessAnalogInput(DateTime datetime, byte inputNo, ushort value);
		partial void ProcessDigitalInput(DateTime datetime, byte inputNo, ushort value);
		
		partial void ProcessBeginPacket();
		partial void ProcessPacketEnd(bool isValid);
		partial void ProcessDataError();

		#endregion

		#region Вспомогательные методы для преобразования

		private ushort ToUShort()
		{
			return (ushort)(_numBuf[0] | (_numBuf[1] << 8));
		}

		private short ToShort()
		{
			return (short)(_numBuf[0] | (_numBuf[1] << 8));
		}

		private int ToInt()
		{
			return (_numBuf[0] | (_numBuf[1] << 8) | (_numBuf[2] << 16) | (_numBuf[3] << 24));
		}

		private DateTime ToDateTime(int seconds)
		{
			try 
			{
				return BaseTimestamp.AddSeconds(seconds);
			}
			catch(Exception ex)
			{
				Logger.Debug("Сбой при преобразовании времени: {0} [{1}]", seconds, ex.Message);

				return default(DateTime);
			}
		}

		#endregion

		#region InitParser - Инициализация парсера
		internal void InitParser()
		{
			%% write init;
		}
		#endregion

		#region	Parse - Обработка принятых данных
		internal void Parse(byte[] data, bool isEof)
		{
			int p = 0;
			int pe = data.Length;
			int eof = isEof ? pe : -1;
	
			%% write exec;
		}
		#endregion

		#region GetProcessingResult - Получение результата парсинга
		internal int GetProcessingResult()
		{
			if ( _cs == %%{ write error; }%% ) 
			{
				return -1; // Parsing error
			}

			if ( _cs >= %%{ write first_final; }%% ) 
			{
				return 1; // Ok
			}

			return 0;
		}
		#endregion

		#region CalcCrc - Расчет CRC16

        /// <summary>
        /// Таблица для расчета CRC
        /// </summary>
        private static readonly ushort[] CRCTable =
            {
                0x0000, 0xC0C1, 0xC181, 0x0140, 0xC301, 0x03C0, 0x0280, 0xC241,
                0xC601, 0x06C0, 0x0780, 0xC741, 0x0500, 0xC5C1, 0xC481, 0x0440,
                0xCC01, 0x0CC0, 0x0D80, 0xCD41, 0x0F00, 0xCFC1, 0xCE81, 0x0E40,
                0x0A00, 0xCAC1, 0xCB81, 0x0B40, 0xC901, 0x09C0, 0x0880, 0xC841,
                0xD801, 0x18C0, 0x1980, 0xD941, 0x1B00, 0xDBC1, 0xDA81, 0x1A40,
                0x1E00, 0xDEC1, 0xDF81, 0x1F40, 0xDD01, 0x1DC0, 0x1C80, 0xDC41,
                0x1400, 0xD4C1, 0xD581, 0x1540, 0xD701, 0x17C0, 0x1680, 0xD641,
                0xD201, 0x12C0, 0x1380, 0xD341, 0x1100, 0xD1C1, 0xD081, 0x1040,
                0xF001, 0x30C0, 0x3180, 0xF141, 0x3300, 0xF3C1, 0xF281, 0x3240,
                0x3600, 0xF6C1, 0xF781, 0x3740, 0xF501, 0x35C0, 0x3480, 0xF441,
                0x3C00, 0xFCC1, 0xFD81, 0x3D40, 0xFF01, 0x3FC0, 0x3E80, 0xFE41,
                0xFA01, 0x3AC0, 0x3B80, 0xFB41, 0x3900, 0xF9C1, 0xF881, 0x3840,
                0x2800, 0xE8C1, 0xE981, 0x2940, 0xEB01, 0x2BC0, 0x2A80, 0xEA41,
                0xEE01, 0x2EC0, 0x2F80, 0xEF41, 0x2D00, 0xEDC1, 0xEC81, 0x2C40,
                0xE401, 0x24C0, 0x2580, 0xE541, 0x2700, 0xE7C1, 0xE681, 0x2640,
                0x2200, 0xE2C1, 0xE381, 0x2340, 0xE101, 0x21C0, 0x2080, 0xE041,
                0xA001, 0x60C0, 0x6180, 0xA141, 0x6300, 0xA3C1, 0xA281, 0x6240,
                0x6600, 0xA6C1, 0xA781, 0x6740, 0xA501, 0x65C0, 0x6480, 0xA441,
                0x6C00, 0xACC1, 0xAD81, 0x6D40, 0xAF01, 0x6FC0, 0x6E80, 0xAE41,
                0xAA01, 0x6AC0, 0x6B80, 0xAB41, 0x6900, 0xA9C1, 0xA881, 0x6840,
                0x7800, 0xB8C1, 0xB981, 0x7940, 0xBB01, 0x7BC0, 0x7A80, 0xBA41,
                0xBE01, 0x7EC0, 0x7F80, 0xBF41, 0x7D00, 0xBDC1, 0xBC81, 0x7C40,
                0xB401, 0x74C0, 0x7580, 0xB541, 0x7700, 0xB7C1, 0xB681, 0x7640,
                0x7200, 0xB2C1, 0xB381, 0x7340, 0xB101, 0x71C0, 0x7080, 0xB041,
                0x5000, 0x90C1, 0x9181, 0x5140, 0x9301, 0x53C0, 0x5280, 0x9241,
                0x9601, 0x56C0, 0x5780, 0x9741, 0x5500, 0x95C1, 0x9481, 0x5440,
                0x9C01, 0x5CC0, 0x5D80, 0x9D41, 0x5F00, 0x9FC1, 0x9E81, 0x5E40,
                0x5A00, 0x9AC1, 0x9B81, 0x5B40, 0x9901, 0x59C0, 0x5880, 0x9841,
                0x8801, 0x48C0, 0x4980, 0x8941, 0x4B00, 0x8BC1, 0x8A81, 0x4A40,
                0x4E00, 0x8EC1, 0x8F81, 0x4F40, 0x8D01, 0x4DC0, 0x4C80, 0x8C41,
                0x4400, 0x84C1, 0x8581, 0x4540, 0x8701, 0x47C0, 0x4680, 0x8641,
                0x8201, 0x42C0, 0x4380, 0x8341, 0x4100, 0x81C1, 0x8081, 0x4040
            };


        /// <summary>
        /// Вспомогательный метод для выполнения расчета CRC16
        /// </summary>
        private void CalcCrc(byte value)
        {		
			unchecked {
				_actualCrc = (ushort)((_actualCrc >> 8) ^ CRCTable[(byte)(_actualCrc ^ value)]);
			}
        }

        #endregion

	}
}