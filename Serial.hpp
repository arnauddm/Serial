#ifndef SERIAL_HPP
#define SERIAL_HPP

#include <QSerialPortInfo>
#include <QSerialPort>
#include <QObject>

class Serial 
{
public:
	// Public Types
	enum class BaudRate 
	{
		Baud1200 = 1200,
		Baud2400 = 2400,
		Baud4800 = 4800,
		Baud9600 = 9600,
		Baud19200 = 19200,
		Baud38400 = 38400,
		Baud57600 = 57600,
		Baud115200 = 115200,
		UnknownBaudRate = -1
	};

	enum class DataBits
	{
		Data5 = 5,
		Data6 = 6,
		Data7 = 7,
		Data8 = 8,
		UnknownDataBits = -1
	};

	enum class Parity
	{
		NoParity = 0,
		EvenParity = 2,
		OddParity = 3,
		SpaceParity = 4,
		MarkParity = 5,
		UnknownParity = -1
	};

	enum class StopBits
	{
		OneStop = 1,
		OneAndHalfStop = 3,
		TwoStop = 2,
		UnknownStopBits = -1
	};

	enum class FlowControl
	{
		NoFlowControl = 0,
		HardwareControl = 1,
		SoftwareControl = 2,
		UnknownFlowControl = -1
	};

	enum class Direction
	{
		In = 1,
		Out = 2,
		Inout = In | Out
	};

	enum class SerialError
	{
		NoError = 0,
		DeviceNotFoundError = 1,
		PermissionError = 2,
		OpenError = 3,
		ParityError = 4,
		FarmingError = 5,
		BreakConditionError = 6,
		WriteError = 7,
		ReadError = 8,
		ResourceError = 9,
		UnsupportedOperationError = 10,
		UnknowError = 11,
		TimeoutError = 12,
		NotOpenError = 13,
		BaudRateError = 14,
		DataBitsError = 15,
		StopBitsError = 16,
		FlowControlError = 17,
		DirectionError = 18
	};

    Serial();
	Serial(	const QString &sPortName,
			BaudRate BaudRate,
			DataBits DataBits,
			FlowControl FlowControl,
			Parity Parity,
			StopBits StopBits,
			Direction Direction);
    ~Serial();

	SerialError init(	const QString& sPortName,
				BaudRate BaudRate,
				DataBits DataBits,
				FlowControl FlowControl,
				Parity Parity,
				StopBits StopBits,
				Direction Direction);
    SerialError init(void);

   	SerialError setPortName(const QString &sPortName);
	QString portName(void);

	SerialError setBaudRate(BaudRate BaudRate);
	BaudRate baudRate(void);

	SerialError setDataBits(DataBits DataBits);
	DataBits dataBits(void);

	SerialError setParity(Parity Parity);
	Parity parity(void);

	SerialError setStopBits(StopBits StopBits);
	StopBits stopBits(void);

	SerialError setFlowControl(FlowControl FlowControl);
	FlowControl flowControl(void);

	SerialError setDirection(Direction Direction);
	Direction direction(void);

	bool sendCommand(const QString &command);

private:
	QString 		_sPortName;
	BaudRate 		_BaudRate;
	DataBits		_DataBits;
	Parity			_Parity;
	StopBits		_StopBits;
	FlowControl		_FlowControl;
	Direction		_Direction;
	QSerialPort		*_pSerialPort;
};

#endif // SERIAL_HPP
