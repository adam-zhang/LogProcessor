#ifndef __CONNECTIVEDATA__H
#define __CONNECTIVEDATA__H

#include <QString>
#include <QDateTime>

class ConnectiveData
{
public:
	ConnectiveData();
	~ConnectiveData();
private:
	int id_;
	QString userName_;
	unsigned int nasipAddress_;
	unsigned int callingStationId_;
	unsigned int framedIpAddress_;
	QDateTime startTime_;
	QDateTime endTime_;
	int sessionTime_;
	int inputoctets_;
	int outputoctets_;
	QString client_;
	QString mac_;
public:
	void setClient(const QString& value)
	{ client_ = value; }
	const QString client()const
	{ return client_; }
	const int& outputOctets()const
	{ return outputoctets_; }

	void setOutputOctets(const int& value)
	{ outputoctets_ = value; }

	void setInputOctets(const int& value)
	{ inputoctets_ = value; }

	const int& inputOctets()const
	{ return inputoctets_; }
	void setSessionTime(const int& value)
	{ sessionTime_ = value; }
	const int& sessionTime()const
	{ return sessionTime_; }
	void setId(int id)
	{ id_ = id; }
	int id()const
	{ return id_;}
	void setUserName(const QString& value)
	{ userName_ = value;}
	const QString& userName()const
	{ return userName_;}
	void setNasipAddress(const unsigned int& value)
	{ nasipAddress_ = value; }
	const unsigned int& nasipAddress()const
	{ return nasipAddress_;}
	void setCallingStationId(const unsigned int& value)
	{ callingStationId_ = value;}
	const unsigned int& callingStationId()const
	{ return callingStationId_; }
	void setFramedIpAddress(const unsigned int& value)
	{ framedIpAddress_ = value; }
	const unsigned int& framedIpAddress()const
	{ return framedIpAddress_; }
	void setStartTime(const QDateTime& value)
	{ startTime_ = value; }
	const QDateTime& startTime()const
	{ return startTime_; }
	void setStopTime(const QDateTime& value)
	{ endTime_ = value;}
	const QDateTime& stopTime()const
	{ return endTime_; }

	const QString& mac()const
	{ return mac_; }

	void setMac(const QString& value)
	{ mac_ = value; }
	
	int startTimeStamp()
	{ return startTime_.toTime_t(); }

	int stopTimeStamp()
	{ return endTime_.toTime_t(); }

};
#endif//__CONNECTIVE__H
