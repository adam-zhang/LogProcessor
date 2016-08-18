#include "Processor.h"
#include "Logger.h"
#include "MatchedData.h"
#include "ServerData.h"
#include "Database.h"
#include "ConnectiveData.h"
#include "ConnectiveLog.h"
#include "Configuration.h"
#include "LogInfo.h"
#include "gzstream.h"
#include <iterator>
#include <QDebug>
#include <QDir>
#include <QProcess>
#include <memory>
#include <arpa/inet.h>

using namespace std;

Processor::Processor()
{
};

Processor::~Processor()
{
}

//void Processor::start()
//{
//
//	vector<shared_ptr<LogInfo>> list = logInfoList(serverIP);
//	for(size_t i = 0; i < list.size(); ++i)
//	{
//		for(size_t j = 0; j < connectiveLog->data().size(); ++j)
//		{
//			match(list[i], connectiveLog->data()[j]);
//		}
//	}
//}
//
void Processor::start(const QDateTime& begin, const QDateTime& )
{
	Configuration config;
	QDir root ( config.filePath());
	QFileInfoList list = root.entryInfoList();
	Database database;
	for(auto i = list.begin() ; i != list.end(); ++i)
	{
		if (i->fileName().startsWith("."))
			continue;
		QString ip = i ->fileName().replace(".", "_");
		database.createTable(ip, begin);
		shared_ptr<ServerData> data = getServerData(*i, begin);
		qDebug() << "data size:" << data->logInfoData().size();
		vector<shared_ptr<ConnectiveData>> connectiveData = database.getConnectiveData(data->serverIP(), config.queryBeginningDateTime(), config.queryEndingDateTime());
		qDebug() << "connective data size:" << connectiveData.size();
		match(data, connectiveData, ip, begin);

	}
}

void Processor::match(shared_ptr<ServerData>& data, 
		std::vector<shared_ptr<ConnectiveData>>& connectiveData,
		const QString& ip,
		const QDateTime& begin)
{
	vector<shared_ptr<LogInfo>> serverData = data->logInfoData();
	int sum = 0;
	for(auto i = serverData.begin(); i != serverData.end(); ++i)
	{
		//qDebug() << "number:" << data->serverIP() << " " << sum + 1;
		for(size_t j = 0;  j < connectiveData.size(); ++j)
		{
			if (match(*i, connectiveData[j], data->serverIP(), ip, begin))
			{
				++sum;
				break;
			}
			else if( j == connectiveData.size() - 1)
			{
				//qDebug() << (*i)->dateTime().dateTime();
				//qDebug() << (*i)->property1();
				//qDebug() << (*i)->ip();
				//qDebug() << (*i)->stringIP();
				//qDebug() << (*i)->respond();
				//qDebug() << (*i)->method();
				//qDebug() << (*i)->url();
			}
		}
	}
	logger().append(QString("ip %1 is written: %2/%3").arg(ip).arg(sum).arg(serverData.size())) ;
}

shared_ptr<ServerData> Processor::getServerData(const QFileInfo& fileInfo, const QDateTime& begin)
{
	shared_ptr<ServerData> data(new ServerData);
	data->setServerIP(iptoint(fileInfo.fileName()));
	data->setLogInfoData(getLogInfoData(fileInfo, begin));
	return data;
}

vector<shared_ptr<LogInfo>> Processor::getLogInfoData(const QFileInfo& fileInfo, const QDateTime& begin)
{
	Q_ASSERT(fileInfo.isDir());
	QDir dir(fileInfo.absoluteFilePath());
	QFileInfoList list = dir.entryInfoList();
	vector<shared_ptr<LogInfo>> vec;
	for(auto i = list.begin(); i != list.end(); ++i)
	{
		if (i->fileName().startsWith("."))
			continue;
		vector<shared_ptr<LogInfo>> data = getLogInfoList(*i, begin);
		copy(data.begin(), data.end(), back_inserter(vec));
	}
	qDebug() << vec.size();
	return vec;
}

inline vector<shared_ptr<LogInfo>> Processor::getLogInfoList(const QFileInfo& fileInfo, const QDateTime& begin)
{
	QString s = QString("%1.%2").arg(begin.toString("yyyyMMdd")).arg("gz");
	if (fileInfo.fileName().endsWith(s))
		return processFile(fileInfo);
	return vector<shared_ptr<LogInfo>>();
}




bool Processor::match(
		const shared_ptr<LogInfo>& logInfo, 
		const shared_ptr<ConnectiveData>& connectiveData,
	       	int serverIP,
		const QString& strServerIP,
	       	const QDateTime& begin)
{
	if (logInfo->ip() == connectiveData->framedIpAddress()
			&& logInfo->dateTime().dateTime() >= connectiveData->startTime()
			&& logInfo->dateTime().dateTime() <= connectiveData->stopTime())
	{
		shared_ptr<MatchedData> data(new MatchedData);
		data->setUserName(connectiveData->userName());
		data->setServerIP(serverIP);
		data->setUserIP(connectiveData->callingStationId());
		data->setPrivateIP(logInfo->ip());
		data->setLoginTime(logInfo->dateTime().dateTime());
		data->setMethod(logInfo->method());
		data->setUrl(logInfo->url());
		data->setMac(connectiveData->mac());
		Database database;
		database.saveMatchedData(data, strServerIP, begin);
		return true;
	}
	return false;
}


//std::vector<std::shared_ptr<LogInfo>> Processor::logInfoList(int& serverIP)
//{
//	
//	vector<shared_ptr<LogInfo>> vec;
//	Configuration config;
//	QDir dir(config.filePath());
//	QFileInfoList list = dir.entryInfoList();
//	for(auto i = list.begin(); i != list.end(); ++i)
//	{
//		if (i->fileName().startsWith("."))
//			continue;
//		if (!i->isDir())
//			continue;
//		QDir dir(i->fileName());
//		QFileInfoList dirs = dir.entryInfoList();
//		serverIP = iptoint(dir.fileName());
//		for(auto j = dirs.begin(); j != dirs.end(); ++j)
//		{
//			if (!(i->fileName().endsWith(".gz")))
//				continue;
//			vector<shared_ptr<LogInfo>> v = processFile(*i);
//			copy(v.begin(), v.end(), back_inserter(vec));
//		}
//	}
//	qDebug() << "logInfo:" << vec.size();
//	return vec;
//}

vector<shared_ptr<LogInfo>> Processor::processFile(const QFileInfo& fileInfo)
{
	qDebug() << fileInfo.fileName();
	vector<shared_ptr<LogInfo>> vec;
	igzstream stream; 
	stream.open(fileInfo.absoluteFilePath().toStdString().c_str());
	if (!stream.good())
		return vec;
	string line;
	while(getline(stream, line))
	{
		if (!line.empty())
		{
			shared_ptr<LogInfo> logInfo = parseLine(line.c_str());
			if (logInfo)
				if (logInfo->method() == "GET" || logInfo->method() == "POST")
					vec.push_back(logInfo);
		}
	}

	return vec;
}

shared_ptr<LogInfo> Processor::parseLine(const QString& line)
{
	QString newLine = line.simplified();
	QStringList filter = newLine.split("/");
	if (!filter[0][0].isNumber())
		return shared_ptr<LogInfo>();
	QStringList list = newLine.split(" ");
	if (list.size() < 8)
		return shared_ptr<LogInfo>();
	shared_ptr<LogInfo> info(new LogInfo);
	info->setDateTime(DateTime(list[0] + " " + list[1]));
	info->setProperty1(list[2].toInt());
	info->setIp(iptoint(list[3]));
	info->setStringIP(list[3]);
	info->setRespond(list[4]);
	info->setProperty2(list[5].toInt());
	info->setMethod(list[6]);
	QString url;
	for(int i = 7; i < list.size(); ++i)
		url += " " + list[i];
	info->setUrl(list[7]);
	return info;
}

int Processor::iptoint(const QString& ip)
{
	return ntohl(inet_addr(ip.toStdString().c_str()));
}


