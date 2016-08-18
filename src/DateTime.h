#ifndef __DATETIME__H
#define __DATETIME__H

#include <QString>
#include <QDateTime>
#include <map>


class DateTime
{
public:
	DateTime();
	explicit DateTime(const QString& );
	~DateTime();
private:
	QDateTime dateTime_;
	int timeZone_;
private:
	QDateTime analyzeDateTime(const QString&);
	int analyzeTimezone(const QString&);
public:
	const QDateTime dateTime()const
	{ return dateTime_; }

private:
	static std::map<QString, int> monthMap_;
private:
	static std::map<QString, int> getMonthMap();
};
#endif//__DATETIME__H
