#include "Logger.h"
#include <QCoreApplication>
#include <QDateTime>

Logger::Logger()
	: file_(QCoreApplication::applicationDirPath() + "/Log")
{
	file_.open(QIODevice::WriteOnly|QIODevice::Text|QIODevice::Append);
}

Logger::~Logger() {}


Logger& Logger::append(const QString& text)
{
	QTextStream stream(&file_);
	stream << QString("%1 %2\n").arg(QDateTime::currentDateTime().toString()).arg(text);
	return *this;
}

