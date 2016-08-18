#ifndef __REPORTER__H
#define __REPORTER__H

#include <QString>

class Reporter
{
public:
	Reporter();
	~Reporter();
public:
	Reporter& append(int value);
	Reporter& append(const QString& value);
private:
	void initialize();
	const QString fileName()const;
	QString& line();
	void setLine(const QString&);
	void writeTo(const QString&);
private:
	QString line_;

};

Reporter report();

//inline Reporter& operator<<(Reporter& r, int value)
//{
//	r.append(value);
//	return r;
//}
//
//inline Reporter& operator<<(Reporter& r, const QString& value)
//{
//	r.append(value);
//	return r;
//}
#endif//__REPORTER__H
