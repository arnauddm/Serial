#ifndef __SERIAL_TEST_HPP
#define __SERIAL_TEST_HPP

#include "Serial.hpp"
#include <QObject>
#include <QDebug>

class SerialTest : public QObject
{
	Q_OBJECT
public:
	SerialTest(void);
	Serial *PortSerie;

public slots:
	void AfficherDonnees(QString sData);

};

#endif
