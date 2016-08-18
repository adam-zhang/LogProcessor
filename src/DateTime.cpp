#include "DateTime.h"
#include <QStringList>
#include <QDebug>
#include <utility>

using namespace std;

DateTime::DateTime()
{
}

DateTime::~DateTime()
{
}

DateTime::DateTime(const QString& s)
	: dateTime_(analyzeDateTime(s))
	, timeZone_(analyzeTimezone(s))
{
	//qDebug() << "s:" << s;
	//qDebug() << "DataTime:" << dateTime_.toString();
}

QDateTime DateTime::analyzeDateTime(const QString& s)
{
	//s = 
	QStringList list = s.split(" ");
	if (list[0].size() > 40)
		return QDateTime(QDate(1970, 1, 1), QTime(0, 0, 0 ));
	list = list[0].split("/");
	int day = list[0].toInt();
	QString m = list[1];
	int month = getMonthMap()[m];
	list = list[2].split(":");
	int year = list[0].toInt();
	int hour = list[1].toInt();
	int minute = list[2].toInt();
	int second = list[3].toInt();
	QDateTime dt(QDate(year, month, day), QTime(hour, minute, second));
	//qDebug() << dt.toString();
	return dt;
}

int DateTime::analyzeTimezone(const QString& s)
{
	QStringList list = s.split(".");
	return list[0].toInt();
}

std::map<QString, int> DateTime::monthMap_;

std::map<QString, int> DateTime::getMonthMap()
{
	if (monthMap_.size() == 0)
	{
		monthMap_.insert(make_pair("Jan", 1));
		monthMap_.insert(make_pair("Feb", 2));
		monthMap_.insert(make_pair("Mar", 3));
		monthMap_.insert(make_pair("Apr", 4));
		monthMap_.insert(make_pair("May", 5));
		monthMap_.insert(make_pair("Jun", 6));
		monthMap_.insert(make_pair("Jul", 7));
		monthMap_.insert(make_pair("Aug", 8));
		monthMap_.insert(make_pair("Sep", 9));
		monthMap_.insert(make_pair("Oct", 10));
		monthMap_.insert(make_pair("Nov", 11));
		monthMap_.insert(make_pair("Dec", 12));
	}
	return monthMap_;
}
