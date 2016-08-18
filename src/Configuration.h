#ifndef __CONFIGURATION__H
#define __CONFIGURATION__H

#include <QString>
#include <QTextStream>
#include <QTime>

class Configuration
{
public:
	Configuration();
	~Configuration();
private:
	QString fileName_;

public:
	QString filePath();
	QTime beginningTime();
	QTime endingTime();
	QDate beginningDate();
	QDate endingDate();
	QString userName();
	QString password();
	QString hostName();
	QString databaseName();
	QDateTime beginningDateTime();
	QDateTime endingDateTime();
	QDateTime queryBeginningDateTime();
	QDateTime queryEndingDateTime();
	QTime programmingStart();
	QTime programmingEnd();
private:
	bool enableDate();
	const QString& fileName()const;
	const QString queryFile(const QString& )const;
	const QTime queryTime(const QString&)const;
	const QDate queryDate(const QString&)const;
	const QTime queryBeginningTime();
	const QTime queryEndingTime();
};

#endif//__CONFIGURATION__H
