#ifndef __LOGGER__H
#define __LOGGER__H

#include <QFile>
#include <QTextStream>
#include <QString>

class Logger
{
public:
	Logger();
	~Logger();
private:
	QFile file_;
private:
	QTextStream getStream();
public:
	Logger& append(const QString& text);
};

inline Logger& operator<<(Logger& logger, QString& text)
{
	logger.append(text);
	return logger;
}

inline Logger& operator<<(Logger& logger, const char* text)
{
	logger.append(text);
	return logger;
}

inline Logger& logger()
{
	static Logger log;
	return log;
}
#endif//__LOGGER__H
