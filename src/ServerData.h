#ifndef __SERVERDATA__H
#define __SERVERDATA__H

#include <vector>
#include <memory>

class LogInfo;

class ServerData
{
public:
	ServerData();
	~ServerData();
public:
	const int& serverIP()const
	{ return serverIP_; }
	void setServerIP(const int& value)
	{ serverIP_ = value; }
	const std::vector<std::shared_ptr<LogInfo>> logInfoData()const
	{ return logInfoData_; }
	void setLogInfoData(const std::vector<std::shared_ptr<LogInfo>>& value)
	{ logInfoData_= value; }
private:
	int serverIP_;
	std::vector<std::shared_ptr<LogInfo>> logInfoData_;
};
#endif//__SERVERDATA__H
