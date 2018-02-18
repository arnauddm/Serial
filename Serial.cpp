#include "Serial.hpp"

Serial::Serial()
{
    // do nothing
    // just create object
	if(!_pSerialPort)
		_pSerialPort = new QSerialPort;

	_BaudRate = Serial::BaudRate::UnknownBaudRate;
	_DataBits = Serial::DataBits::UnknownDataBits;
	_Parity = Serial::Parity::UnknownParity;
	_StopBits = Serial::StopBits::UnknownStopBits;
	_FlowControl = Serial::FlowControl::UnknownFlowControl;
	_Direction = Serial::Direction::Inout;
}

Serial::Serial(	const QString &sPortName,
				Serial::BaudRate BaudRate,
				Serial::DataBits DataBits,
				Serial::FlowControl FlowControl,
				Serial::Parity Parity,
				Serial::StopBits StopBits,
				Serial::Direction Direction)

{
	if(!_pSerialPort)
		_pSerialPort = new QSerialPort;

	_sPortName = sPortName;
	_BaudRate = BaudRate;
	_DataBits = DataBits;
	_Parity = Parity;
	_StopBits = StopBits;
	_FlowControl = FlowControl;
	_Direction = Direction;
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

Serial::SerialError Serial::init(	const QString &sPortName,
					Serial::BaudRate BaudRate,
					Serial::DataBits DataBits,
					Serial::FlowControl FlowControl,
					Serial::Parity Parity,
					Serial::StopBits StopBits,
					Serial::Direction Direction)
{
	_sPortName = sPortName;
	_BaudRate = BaudRate;
	_DataBits = DataBits;
	_FlowControl = FlowControl;
	_Parity = Parity;
	_StopBits = StopBits;

	if(!_pSerialPort)
		_pSerialPort = new QSerialPort;

	Serial::SerialError Error;

	Error = setPortName(_sPortName);
	if(Error != Serial::SerialError::NoError)
		return Error;

	Error = setBaudRate(_BaudRate);
	if(Error != Serial::SerialError::NoError)
		return Error;
	
	Error = setDataBits(_DataBits);
	if(Error != Serial::SerialError::NoError)
		return Error;
	
	Error = setFlowControl(_FlowControl);
	if(Error != Serial::SerialError::NoError)
		return Error;

	Error = setParity(_Parity);
	if(Error != Serial::SerialError::NoError)
		return Error;

	Error = setStopBits(_StopBits);
	if(Error != Serial::SerialError::NoError)
		return Error;
}

Serial::SerialError Serial::init(void)
{
	Serial::SerialError Error;

	Error = setPortName(_sPortName);
	if(Error != Serial::SerialError::NoError)
		return Error;

	Error = setBaudRate(_BaudRate);
	if(Error != Serial::SerialError::NoError)
		return Error;
	
	Error = setDataBits(_DataBits);
	if(Error != Serial::SerialError::NoError)
		return Error;
	
	Error = setFlowControl(_FlowControl);
	if(Error != Serial::SerialError::NoError)
		return Error;

	Error = setParity(_Parity);
	if(Error != Serial::SerialError::NoError)
		return Error;

	Error = setStopBits(_StopBits);
	if(Error != Serial::SerialError::NoError)
		return Error;
}

bool Serial::sendCommand(const QString &command)
{

}

Serial::SerialError Serial::setPortName(const QString &sPortName)
{ 
	_sPortName = sPortName;
}

QString Serial::portName(void)
{
	return _sPortName;
}

Serial::SerialError Serial::setBaudRate(Serial::BaudRate BaudRate)
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
			_pSerialPort->setBaudRate((QSerialPort::BaudRate)_BaudRate, (QSerialPort::Direction)_Direction);
			break;
		default:
			return Serial::SerialError::BaudRateError;
			break;
	}
}

Serial::BaudRate Serial::baudRate(void)
{
	return _BaudRate;
}

Serial::SerialError Serial::setDataBits(Serial::DataBits DataBits)
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
			return Serial::SerialError::DataBitsError;
			break;
	}
}

Serial::DataBits Serial::dataBits(void)
{
	return _DataBits;
}

Serial::SerialError Serial::setParity(Serial::Parity Parity)
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
			return Serial::SerialError::ParityError;
			break;
	}
}

Serial::Parity Serial::parity(void)
{
	return _Parity;
}

Serial::SerialError Serial::setStopBits(Serial::StopBits StopBits)
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
			return Serial::SerialError::StopBitsError;
			break;
	}
}

Serial::StopBits Serial::stopBits(void)
{
	return _StopBits;
}

Serial::SerialError Serial::setFlowControl(Serial::FlowControl FlowControl)
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
			return Serial::SerialError::FlowControlError;
			break;
		}
}

Serial::FlowControl Serial::flowControl(void)
{
	return _FlowControl;
}

Serial::SerialError Serial::setDirection(Serial::Direction Direction)
{
	switch(Direction)
	{
		case Serial::Direction::In:
		case Serial::Direction::Out:
		case Serial::Direction::Inout:
			_Direction = Direction;
			if(!_pSerialPort)
				_pSerialPort->setBaudRate((QSerialPort::BaudRate)_BaudRate,(QSerialPort::Direction)_Direction);
			break;
		default:
			return Serial::SerialError::DirectionError;
			break;
	}
}

Serial::Direction Serial::direction(void)
{
	return _Direction;
}
