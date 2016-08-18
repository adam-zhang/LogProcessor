#ifndef __LOGINDATA__H
#define __LOGINDATA__H

#include <QString>
#include <QDateTime>

class LoginData
{
public:
	LoginData()
		: id_(0)
		  , loginWay_(0)
		  , dayTimes_(0)
	{}
	~LoginData() {}
private:
	int id_;
	QString userName_;
	QDateTime loginTime_;
	int loginIp_;
	QString mac_;
	int loginWay_;
	int dayTimes_;
	QString client_;
public:
	void setClient(const QString& value)
	{ client_ = value; }
	const QString& client()const
	{ return client_; }
	void setId(int value)
	{ id_ = value;}
	int id()
	{ return id_; }
	void setUserName(const QString& value)
	{ userName_ = value;}
	const QString& userName()const
	{ return userName_; }
	void setLoginTime(const QDateTime& value)
	{ loginTime_ = value;}
	const QDateTime& loginTime()const
	{ return loginTime_; }
	void setLoginIp(const int& ip)
	{ loginIp_ = ip;}
	const int& loginIp()const
	{ return loginIp_;}
	void setMac(const QString& value)
	{ mac_ = value; }
	const QString mac()const
	{ return mac_; }
	void setLoginWay(int value)
	{ loginWay_ = value;}
	int loginWay()const
	{ return loginWay_; }
	void setDayTimes(int value)
	{ dayTimes_ = value;}
	int dayTimes()const
	{ return dayTimes_; }
	int loginTimeStamp()
	{ return loginTime_.toTime_t();}
};
#endif//__LOGINDATA__H
