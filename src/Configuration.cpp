#include "Configuration.h"
#include <QFile>
#include <QTextStream>
#include <QStringList>
#include <QDebug>
#include <QCoreApplication>

Configuration::Configuration()
	: fileName_("/LogProcessor.config")
{
	fileName_ = QCoreApplication::applicationDirPath() + fileName_;
}

Configuration::~Configuration()
{
}

QDate Configuration::beginningDate()
{
	return queryDate("beginningDate=");
}

QDate Configuration::endingDate()
{
	return queryDate("endingDate=");
}

QString Configuration::filePath()
{
	return queryFile("filePath=");
}

QString Configuration::userName()
{
	return queryFile("userName=");
}

QTime Configuration::programmingEnd()
{
	return queryTime("programmingEnd=");
}

QTime Configuration::programmingStart()
{
	return queryTime("programmingStart=");
}
QString Configuration::password()
{
	return queryFile("password=");
}

QString Configuration::hostName()
{
	return queryFile("hostName=");
}

QString Configuration::databaseName()
{
	return queryFile("databaseName=");
}


const QString& Configuration::fileName()const
{
	return fileName_;
}

QTime Configuration::beginningTime()
{
	return queryTime("beginningTime=");
}

QTime Configuration::endingTime()
{
	return queryTime("endingTime=");
}

const QTime Configuration::queryTime(const QString& key)const
{
	QString result = queryFile(key);
	QStringList list = result.split(":");
	int hour = list[0].toInt();
	int minute = list[1].toInt();
	int second = list[2].toInt();
	return QTime(hour, minute, second);
}

bool Configuration::enableDate()
{
	QString result = queryFile("enableDate=");
	return result == "1";
}

const QDate Configuration::queryDate(const QString& key)const
{
	QString result = queryFile(key);
	//QStringList list = result.split("-");
	return QDate::fromString(result ,"yyyy-MM-dd");
}

const QString Configuration::queryFile(const QString& key)const
{
	QString line;
	QFile file(fileName_);
	if (!file.open(QFile::ReadOnly))
		return QString();
	QTextStream stream(&file);
	do
	{
		line = stream.readLine();
		if (!line.startsWith(key))
			continue;
		QStringList list = line.split("=");
		return list[1];
			
	}while(!line.isNull());
	return QString();
}

QDateTime Configuration::queryBeginningDateTime()
{
	QDate date = QDate::currentDate();
	if (enableDate())
		date = beginningDate();
	return QDateTime(date, beginningTime());
}

QDateTime Configuration::queryEndingDateTime()
{
	QDate date = QDate::currentDate();
	if (enableDate())
		date = endingDate();
	return QDateTime(date, endingTime());
}



const QTime Configuration::queryBeginningTime()
{
	return queryTime("beginningTime=");
}

const QTime Configuration::queryEndingTime()
{
	return queryTime("endingTime=");
}

QDateTime Configuration::beginningDateTime()
{
	QDate date = QDate::currentDate().addDays(-1);
	if (enableDate())
		date = beginningDate();
	return QDateTime(date, beginningTime());
}

QDateTime Configuration::endingDateTime()
{
	QDate date = QDate::currentDate();
	if (enableDate())
		date = endingDate();
	return QDateTime(date, endingTime());
}
