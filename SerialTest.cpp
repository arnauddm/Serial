#include "SerialTest.hpp"

SerialTest::SerialTest(void)
{
	foreach (
                 const QSerialPortInfo &info, QSerialPortInfo::availablePorts()
                 ) {

			qDebug() << "Port name : " << info.portName();
			qDebug() << "Description " << info.description();
			qDebug() << "Manu " << info.manufacturer();
}
	qDebug() << "\n\n";
	PortSerie = new Serial;
	qDebug() << (int)PortSerie->setPortName("cu.usbmodem1411");
	qDebug() << (int)PortSerie->setBaudRate(Serial::BaudRate::Baud115200);
	qDebug() << (int)PortSerie->setDataBits(Serial::DataBits::Data8);
	qDebug() << (int)PortSerie->setFlowControl(Serial::FlowControl::NoFlowControl);
	qDebug() << (int)PortSerie->setStopBits(Serial::StopBits::OneStop);
	qDebug() << (int)PortSerie->setParity(Serial::Parity::NoParity);
	if(PortSerie->open(Serial::Mode::ReadWrite) != Serial::Error::NoError)
		qDebug() << "Open error";
	qDebug() << "Open ? " << PortSerie->isOpen();

	QObject::connect(	PortSerie,
						SIGNAL(ReceiveData(QString)),
						this,
						SLOT(AfficherDonnees(QString)));

//	for(int i = 0; i < 10; i++)
		qDebug() << (int)PortSerie->send("1");
}

void SerialTest::AfficherDonnees(QString sData)
{
	qDebug() << sData;
}
