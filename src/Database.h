#ifndef __DATABASE__H
#define __DATABASE__H

#include <QSqlDatabase>
#include <vector>
#include <memory>

class LoginData;
class ConnectiveData;
class QDateTime;
class MatchedData;

class Database
{
public:
	Database();
	~Database();
private:
	//QSqlDatabase db_;
private:
	bool connect();
private:
	QSqlDatabase db_;
public:
	bool saveLoginData(const std::vector<std::shared_ptr<LoginData>>& data);
	bool saveConnectiveData(const std::vector<std::shared_ptr<ConnectiveData>>& data);
	std::vector<std::shared_ptr<ConnectiveData>> getConnectiveData(unsigned int ip, const QDateTime&, const QDateTime&);
	bool createTable(const QString&, const QDateTime& begin);
	bool saveMatchedData(const std::shared_ptr<MatchedData>& data, const QString&, const QDateTime&);
private:
	bool saveConnectiveData(const std::shared_ptr<ConnectiveData>&);
	bool saveLoginData(const std::shared_ptr<LoginData>& data);
	std::vector<QString> getTableNames();
	bool createTable(const QSqlDatabase& ,const QString&);
	const QString tableName(const QString& ,const QDateTime&);
};

#endif//__DATABASE__H
