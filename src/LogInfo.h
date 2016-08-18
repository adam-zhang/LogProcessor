#ifndef __LOGINFO__H
#define __LOGINFO__H

#include "DateTime.h"

class LogInfo
{
public:
	LogInfo();
	~LogInfo();
private:
	DateTime dateTime_;
	int property1_;
	unsigned int ip_;
	QString stringIP_;
	QString respond_;
	int property2_;
	QString method_;
	QString url_;
	QString client_;

public:
	void setStringIP(const QString& value)
	{ stringIP_ = value; }
	const QString& stringIP()const
	{ return stringIP_; }

	const DateTime& dateTime()const
	{ return dateTime_; }
	void setDateTime(const DateTime& dateTime)
	{ dateTime_ = dateTime; }
	const int& property1()const
	{ return property1_;}
	void setProperty1(const int& value)
	{ property1_ = value;}
	const unsigned int& ip()const
	{ return ip_; }
	void setIp(const unsigned int& ip)
	{ ip_ = ip; }
	const QString& respond()const
	{ return respond_; }
	void setRespond(const QString& respond)
	{ respond_ = respond;}
	int property2()const
	{ return property2_; }
	void setProperty2(int property)
	{ property2_ = property; }
	void setMethod(const QString& method)
	{ method_ = method;}
	const QString& method()const
	{ return method_; }
	const QString& url()const
	{ return url_;}
	void setUrl(const QString& url)
	{ url_ = url; }
	int loginTimeStamp()
	{ return dateTime_.dateTime().toTime_t(); }




};
#endif//__LOGINFO__H

