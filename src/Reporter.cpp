#include "Reporter.h"
#include <QDateTime>
#include <QFile>
#include <QTextStream>
#include <QDebug>

Reporter::Reporter()
{
}

Reporter::~Reporter()
{
	setLine(QString("%1\n").arg(line()));
	writeTo(fileName());
}

void Reporter::writeTo(const QString& fileName)
{
	QFile file(fileName);
	file.open(QFile::WriteOnly|QFile::Append);
	QTextStream stream(&file);
	stream << line();
}

const QString Reporter::fileName()const
{
	return "report.txt";
}

Reporter& Reporter::append(int value)
{
	setLine(QString("%1%2").arg(line()).arg(value));
	return *this;
}

Reporter& Reporter::append(const QString& value)
{
	setLine(QString("%1%2").arg(line()).arg(value));
	return *this;
}

void Reporter::setLine(const QString& value)
{
	line_ = value;
}

QString& Reporter::line()
{
	return line_;
}

void Reporter::initialize()
{
	setLine(QDateTime::currentDateTime().toString());
	qDebug() << line();
}

Reporter report()
{
	Reporter r;
	return r;
}
