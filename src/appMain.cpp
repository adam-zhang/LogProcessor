#include <iostream>
#include <QCoreApplication>
#include "Daemon.h"
#include "Processor.h"
#include "Reporter.h"
#include "NetworkAccessor.h"
#include "Configuration.h"
#include "Logger.h"
#include <unistd.h>
#include <QDebug>

void run()
{	
	logger().append("begin to run.");
	Configuration config;
	NetworkAccessor accessor;
	accessor.getData(config.beginningDateTime(), config.endingDateTime());
	Processor p;
	p.start(config.beginningDateTime(), config.endingDateTime());
	logger().append("end to run");
}


int main(int argc, char** argv)
{
	QCoreApplication a(argc, argv);
	//Daemon::create();
	//while(true)
	//{
	//      	Configuration config;
	//	//qDebug() << config.programmingStart() << " " << config.programmingEnd();
	//	if (QTime::currentTime() > config.programmingStart() && QTime::currentTime() < config.programmingEnd())
	      		run();
	//      	else
	//      		sleep(60);
	//}
	return 0;
}
