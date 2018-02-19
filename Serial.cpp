#include "Serial.hpp"

Serial::Serial()
{
	_pSerialPort = new QSerialPort;

	_BaudRate = Serial::BaudRate::UnknownBaudRate;
	_DataBits = Serial::DataBits::UnknownDataBits;
	_Parity = Serial::Parity::UnknownParity;
	_StopBits = Serial::StopBits::UnknownStopBits;
	_FlowControl = Serial::FlowControl::UnknownFlowControl;

	QObject::connect(_pSerialPort, SIGNAL(readyRead()), this, SLOT(DataReceived()));
}

Serial::Serial(	const QString &sPortName,
				Serial::BaudRate BaudRate,
				Serial::DataBits DataBits,
				Serial::FlowControl FlowControl,
				Serial::Parity Parity,
				Serial::StopBits StopBits)

{
	_pSerialPort = new QSerialPort;

	_sPortName = sPortName;
	_BaudRate = BaudRate;
	_DataBits = DataBits;
	_Parity = Parity;
	_StopBits = StopBits;
	_FlowControl = FlowControl;

	QObject::connect(_pSerialPort, SIGNAL(readyRead()), this, SLOT(DataReceive()));
}

Serial::~Serial(void)
{
	QObject::disconnect(_pSerialPort, SIGNAL(readyRead()), this, SLOT(DataReceive()));
	if(_pSerialPort)
	{
		delete _pSerialPort;
		_pSerialPort = NULL;
	}
    delete this;
}

Serial::Error Serial::init(	const QString &sPortName,
					Serial::BaudRate BaudRate,
					Serial::DataBits DataBits,
					Serial::FlowControl FlowControl,
					Serial::Parity Parity,
					Serial::StopBits StopBits)
{
	_sPortName = sPortName;
	_BaudRate = BaudRate;
	_DataBits = DataBits;
	_FlowControl = FlowControl;
	_Parity = Parity;
	_StopBits = StopBits;

	return init();
}

Serial::Error Serial::init(void)
{
	Serial::Error Error;

	setPortName(_sPortName);

	Error = setBaudRate(_BaudRate);
	if(Error != Serial::Error::NoError)
		return Error;
	
	Error = setDataBits(_DataBits);
	if(Error != Serial::Error::NoError)
		return Error;
	
	Error = setFlowControl(_FlowControl);
	if(Error != Serial::Error::NoError)
		return Error;

	Error = setParity(_Parity);
	if(Error != Serial::Error::NoError)
		return Error;

	Error = setStopBits(_StopBits);
	if(Error != Serial::Error::NoError)
		return Error;

	return Serial::Error::NoError;
}

Serial::Error Serial::setPortName(QString sPortName)
{ 
#ifdef trace
	qDebug() << "setPortName()";
#endif
	_sPortName = sPortName;
	if(!_pSerialPort)
		return Serial::Error::DeviceNotFoundError;
	_pSerialPort->setPortName(_sPortName);

#ifdef trace
	qDebug() << "Port name : " << _sPortName;
#endif

	return Serial::Error::NoError;
}

QString Serial::portName(void)
{
	return _sPortName;
}

Serial::Error Serial::setBaudRate(Serial::BaudRate BaudRate)
{
#ifdef trace
	qDebug() << "setBaudRate()";
	qDebug() << "BaudRate : " << (int)BaudRate;
#endif
	switch(BaudRate)
	{
		case Serial::BaudRate::Baud1200:
		case Serial::BaudRate::Baud2400:
		case Serial::BaudRate::Baud4800:
		case Serial::BaudRate::Baud9600:
		case Serial::BaudRate::Baud19200:
		case Serial::BaudRate::Baud38400:
		case Serial::BaudRate::Baud57600:
		case Serial::BaudRate::Baud115200:
		case Serial::BaudRate::UnknownBaudRate:
			_BaudRate = BaudRate;
			if(!_pSerialPort)
				return Serial::Error::DeviceNotFoundError;
			_pSerialPort->setBaudRate((QSerialPort::BaudRate)_BaudRate);
			return Serial::Error::NoError;
			break;
		default:
#ifdef trace
			qDebug() << "BaudRate error";
#endif
			return Serial::Error::BaudRateError;
			break;
	}
}

Serial::BaudRate Serial::baudRate(void)
{
	return _BaudRate;
}

Serial::Error Serial::setDataBits(Serial::DataBits DataBits)
{
#ifdef trace
	qDebug() << "setDataBits()";
	qDebug() << "DataBits : " << (int)DataBits;
#endif
	switch(DataBits)
	{
		case Serial::DataBits::Data5:
		case Serial::DataBits::Data6:
		case Serial::DataBits::Data7:
		case Serial::DataBits::Data8:
		case Serial::DataBits::UnknownDataBits:
			_DataBits = DataBits;
			if(!_pSerialPort)
				return Serial::Error::DeviceNotFoundError;
			_pSerialPort->setDataBits((QSerialPort::DataBits)_DataBits);
			return Serial::Error::NoError;
			break;
		default:
#ifdef trace
			qDebug() << "DataBits error";
#endif
			return Serial::Error::DataBitsError;
			break;
	}
}

Serial::DataBits Serial::dataBits(void)
{
	return _DataBits;
}

Serial::Error Serial::setParity(Serial::Parity Parity)
{
#ifdef trace
	qDebug() << "setParity()";
	qDebug() << "Parity : " << (int)Parity;
#endif
	switch(Parity)
	{
		case Serial::Parity::NoParity:
		case Serial::Parity::EvenParity:
		case Serial::Parity::OddParity:
		case Serial::Parity::SpaceParity:
		case Serial::Parity::MarkParity:
		case Serial::Parity::UnknownParity:
			_Parity = Parity;
			if(!_pSerialPort)
				return Serial::Error::DeviceNotFoundError;
			_pSerialPort->setParity((QSerialPort::Parity)_Parity);
			return Serial::Error::NoError;
			break;
		default:
#ifdef trace
			qDebug() << "Parity error";
#endif
			return Serial::Error::ParityError;
			break;
	}
}

Serial::Parity Serial::parity(void)
{
	return _Parity;
}

Serial::Error Serial::setStopBits(Serial::StopBits StopBits)
{
#ifdef trace
	qDebug() << "setStopBits()";
	qDebug() << "StopBits : " << (int)StopBits;
#endif
	switch(StopBits)
	{
		case Serial::StopBits::OneStop:
		case Serial::StopBits::OneAndHalfStop:
		case Serial::StopBits::TwoStop:
		case Serial::StopBits::UnknownStopBits:
			_StopBits = StopBits;
			if(!_pSerialPort)
				return Serial::Error::DeviceNotFoundError;
			_pSerialPort->setStopBits((QSerialPort::StopBits)_StopBits);
			return Serial::Error::NoError;
			break;
		default:
#ifdef trace
			qDebug() << "StopBits error";
#endif
			return Serial::Error::StopBitsError;
			break;
	}
}

Serial::StopBits Serial::stopBits(void)
{
	return _StopBits;
}

Serial::Error Serial::setFlowControl(Serial::FlowControl FlowControl)
{
#ifdef trace
	qDebug() << "setFlowControl()";
	qDebug() << "FlowControl : " << (int)FlowControl;
#endif
	switch(FlowControl)
	{
		case Serial::FlowControl::NoFlowControl:
		case Serial::FlowControl::HardwareControl:
		case Serial::FlowControl::SoftwareControl:
		case Serial::FlowControl::UnknownFlowControl:
			_FlowControl = FlowControl;
			if(!_pSerialPort)
				return Serial::Error::DeviceNotFoundError;
			_pSerialPort->setFlowControl((QSerialPort::FlowControl)_FlowControl);
			return Serial::Error::NoError;
			break;
		default:
#ifdef trace
			qDebug() << "FlowControl error";
#endif
			return Serial::Error::FlowControlError;
			break;
	}
}

Serial::FlowControl Serial::flowControl(void)
{
	return _FlowControl;
}

Serial::Error Serial::open(Serial::Mode Mode)
{
#ifdef trace
	qDebug() << "open() : " << _pSerialPort;
	qDebug() << "Mode : " << (int)Mode;
#endif
	bool resOpen;
	switch(Mode)
	{
		case Serial::Mode::NotOpen:
		case Serial::Mode::ReadOnly:
		case Serial::Mode::WriteOnly:
		case Serial::Mode::ReadWrite:
		case Serial::Mode::Append:
		case Serial::Mode::Truncate:
		case Serial::Mode::Text:
		case Serial::Mode::Unbuffered:
			_Mode = Mode;
			if(!_pSerialPort)
				return Serial::Error::DeviceNotFoundError;
			resOpen = _pSerialPort->open((QIODevice::OpenModeFlag)_Mode);
#ifdef trace
			qDebug() << "Open state : " << resOpen;
#endif
			if(resOpen)
				return Serial::Error::NoError;
			else
				return Serial::Error::OpenError;
			break;
		default:
#ifdef trace
		qDebug() << "open() error parameters";
#endif
			return Serial::Error::ModeError;
			break;
	}
}

void Serial::close(void)
{
	_pSerialPort->close();
}

bool Serial::isOpen(void)
{
	return _pSerialPort->isOpen();
}

void Serial::DataReceived(void)
{
	emit ReceiveData((QString)_pSerialPort->readAll());
}

void Serial::EnableTrace(void)
{
	_EnableTrace = true;
}

void Serial::DisableTrace(void)
{
	_EnableTrace = false;
}

bool Serial::ResetTrace(void)
{
	if(!_pTrace)
		return false;
	
	_pTrace->clear();
	return true;
}

Serial::Error Serial::send(const QString& Command)
{
	if(!_pSerialPort)
		return Serial::Error::DeviceNotFoundError;
	
	_pSerialPort->write(Command.toStdString().c_str());

	if(_EnableTrace)
	{
		if(!_pTrace)
			_pTrace = new QVector<QString>;

		_pTrace->push_back(Command);
	}

	return Serial::Error::NoError;
}
