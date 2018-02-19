#include "Serial.hpp"
#include "SerialTest.hpp"
#include <QSerialPort>

#include <QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	SerialTest serie;
	return a.exec();
}
