#ifndef __PROCESSOR__H
#define __PROCESSOR__H

#include <vector>
#include <memory>

#include <QFileInfo>

class LogInfo;
class ConnectiveData;
class ServerData;

class Processor
{
public:
	Processor();
	~Processor();
public:
	void start(const QDateTime&, const QDateTime&);
private:
	void getLoginLog();
	std::vector<std::shared_ptr<LogInfo>> logInfoList(int& serverIP);
	std::vector<std::shared_ptr<LogInfo>> processFile(const QFileInfo&);
	std::shared_ptr<LogInfo> parseLine(const QString& line);
	int iptoint(const QString&);
	bool match(const std::shared_ptr<LogInfo>&,
		       	const std::shared_ptr<ConnectiveData>&,
		       	int, 
			const QString&, 
			const QDateTime&);
	std::shared_ptr<ServerData> getServerData(const QFileInfo& fileInfo, const QDateTime&);
	std::vector<std::shared_ptr<LogInfo>> getLoginData(const QFileInfo& fileInfo);
	std::vector<std::shared_ptr<LogInfo>> getLogInfoData(const QFileInfo&, const QDateTime&);
	std::vector<std::shared_ptr<LogInfo>> getLogInfoList(const QFileInfo&, const QDateTime&);
	void match(std::shared_ptr<ServerData>& serverData, std::vector<std::shared_ptr<ConnectiveData>>&, 
			const QString&,
			const QDateTime&);
};
#endif//__PROCESSOR__H
