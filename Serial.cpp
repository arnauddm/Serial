#include "Serial.hpp"

Serial::Serial()
{
	if(!_pSerialPort)
		_pSerialPort = new QSerialPort;

	_BaudRate = Serial::BaudRate::UnknownBaudRate;
	_DataBits = Serial::DataBits::UnknownDataBits;
	_Parity = Serial::Parity::UnknownParity;
	_StopBits = Serial::StopBits::UnknownStopBits;
	_FlowControl = Serial::FlowControl::UnknownFlowControl;
}

Serial::Serial(	const QString &sPortName,
				Serial::BaudRate BaudRate,
				Serial::DataBits DataBits,
				Serial::FlowControl FlowControl,
				Serial::Parity Parity,
				Serial::StopBits StopBits)

{
	if(!_pSerialPort)
		_pSerialPort = new QSerialPort;

	_sPortName = sPortName;
	_BaudRate = BaudRate;
	_DataBits = DataBits;
	_Parity = Parity;
	_StopBits = StopBits;
	_FlowControl = FlowControl;
}

Serial::~Serial(void)
{
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
}

void Serial::setPortName(const QString &sPortName)
{ 
	_sPortName = sPortName;
	if(!_pSerialPort)
		_pSerialPort = new QSerialPort;
	_pSerialPort->setPortName(_sPortName);
}

QString Serial::portName(void)
{
	return _sPortName;
}

Serial::Error Serial::setBaudRate(Serial::BaudRate BaudRate)
{
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
				_pSerialPort = new QSerialPort;
			_pSerialPort->setBaudRate((QSerialPort::BaudRate)_BaudRate);
			break;
		default:
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
	switch(DataBits)
	{
		case Serial::DataBits::Data5:
		case Serial::DataBits::Data6:
		case Serial::DataBits::Data7:
		case Serial::DataBits::Data8:
		case Serial::DataBits::UnknownDataBits:
			_DataBits = DataBits;
			if(!_pSerialPort)
				_pSerialPort = new QSerialPort;
			_pSerialPort->setDataBits((QSerialPort::DataBits)_DataBits);
			break;
		default:
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
				_pSerialPort = new QSerialPort;
			_pSerialPort->setParity((QSerialPort::Parity)_Parity);
			break;
		default:
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
	switch(StopBits)
	{
		case Serial::StopBits::OneStop:
		case Serial::StopBits::OneAndHalfStop:
		case Serial::StopBits::TwoStop:
		case Serial::StopBits::UnknownStopBits:
			_StopBits = StopBits;
			if(!_pSerialPort)
				_pSerialPort = new QSerialPort;
			_pSerialPort->setStopBits((QSerialPort::StopBits)_StopBits);
			break;
		default:
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
	switch(FlowControl)
	{
		case Serial::FlowControl::NoFlowControl:
		case Serial::FlowControl::HardwareControl:
		case Serial::FlowControl::SoftwareControl:
		case Serial::FlowControl::UnknownFlowControl:
			_FlowControl = FlowControl;
			if(!_pSerialPort)
				_pSerialPort = new QSerialPort;
			_pSerialPort->setFlowControl((QSerialPort::FlowControl)_FlowControl);
			break;
		default:
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
			if(_pSerialPort)
				_pSerialPort = new QSerialPort;
			if(_pSerialPort->open((QIODevice::OpenModeFlag)Mode))
				return Serial::Error::NoError;
			else
				return Serial::Error::OpenError;
			break;
		default:
			return Serial::Error::ModeError;
			break;
	}
}

void Serial::close(void)
{
	_pSerialPort->close();
}

Serial::State Serial::isOpen(void)
{
	return _Mode == Serial::Mode::NotOpen ? Serial::State::Close : Serial::State::Open;
}
