#ifndef SERIAL_HPP
#define SERIAL_HPP

#include <QSerialPortInfo>
#include <QSerialPort>
#include <QObject>
#include <QIODevice>
#include <QObject>
#include <QVector>
#include <QString>

class Serial : public QObject
{
	Q_OBJECT
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

	enum class Error
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
		ModeError = 18
	};

	enum class Mode
	{
		NotOpen = 0x0000,
		ReadOnly = 0x0001,
		WriteOnly = 0x0002,
		ReadWrite = ReadOnly | WriteOnly,
		Append = 0x0004,
		Truncate = 0x0008,
		Text = 0x0010,
		Unbuffered = 0x0020
	};

	enum class State
	{
		Open = 0,
		Close = 1
	};

	Serial();
	Serial(	const QString &sPortName,
			BaudRate BaudRate,
			DataBits DataBits,
			FlowControl FlowControl,
			Parity Parity,
			StopBits StopBits);
	~Serial();

	Error init(	const QString& sPortName,
				BaudRate BaudRate,
				DataBits DataBits,
				FlowControl FlowControl,
				Parity Parity,
				StopBits StopBits);
	Error init(void);

   	void setPortName(const QString &sPortName);
	QString portName(void);

	Error setBaudRate(BaudRate BaudRate);
	BaudRate baudRate(void);

	Error setDataBits(DataBits DataBits);
	DataBits dataBits(void);

	Error setParity(Parity Parity);
	Parity parity(void);

	Error setStopBits(StopBits StopBits);
	StopBits stopBits(void);

	Error setFlowControl(FlowControl FlowControl);
	FlowControl flowControl(void);

	Error open(Mode Mode);
	void close(void);
	State isOpen(void);

	Error send(const QString& Command);

	void EnableTrace(void);
	void DisableTrace(void);
	bool ResetTrace(void);

private:
	QString 			_sPortName;
	BaudRate 			_BaudRate;
	DataBits			_DataBits;
	Parity				_Parity;
	StopBits			_StopBits;
	FlowControl			_FlowControl;
	QSerialPort			*_pSerialPort;
	Mode				_Mode;
	bool				_EnableTrace;
	QVector<QString> 	*_pTrace;

signals:
	void ReceiveData(QString);

private slots:
	void DataReceived(void);
};

#endif // SERIAL_HPP
