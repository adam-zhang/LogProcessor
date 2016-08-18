#ifndef __MACHTCHEDDATA__H
#define __MACHTCHEDDATA__H

#include <QDateTime>
#include <QString>

class MatchedData
{
public:
	MatchedData();
	~MatchedData();
public:
	QString userName_;
	unsigned int serverIP_;
	unsigned int userIP_;
	unsigned int privateID_;
	QDateTime loginTime_;
	QString method_;
	QString url_;
	QString mac_;
public:
	void setUrl(const QString& url)
	{ url_ = url;}
	const QString& url()const
	{ return url_; }
	void setUserName(const QString& userName)
	{ userName_ = userName;}
	const QString& userName()const
	{ return userName_; }

	void setServerIP(const unsigned int& serverIP)
	{ serverIP_ = serverIP; }
	const unsigned int& serverIP()const
	{ return serverIP_; }

	void setUserIP(const unsigned int& userIP)
	{ userIP_ = userIP; }
	const unsigned int& userIP()const
	{ return userIP_; }

	void setPrivateIP(const int& value)
	{ privateID_ = value; }
	const unsigned int& privateIP()const
	{ return privateID_; }

	void setLoginTime(const QDateTime& value)
	{ loginTime_ = value; }
	const QDateTime& loginTime()const
	{ return loginTime_; }

	void setMethod(const QString& method)
	{ method_ = method; }

	const QString& method() const
	{ return method_; }
	
	const QString& mac()const
	{ return mac_; }

	void setMac(const QString& value)
	{ mac_ = value; }
	
	int loginTimeStamp()
	{ return loginTime_.toTime_t(); }

};
#endif//__MACHTCHEDDATA__H
