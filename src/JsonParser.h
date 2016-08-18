#ifndef __JSONPARSER__H
#define __JSONPARSER__H

#include "Result.h"
#include <vector>
#include <memory>
#include <QList>

class LoginLog;
class ConnectiveLog;
class QString;
class QVariant;
class LoginData;
class ConnectiveData;

class JsonParser
{
private:
	JsonParser() {}
	~JsonParser() {}
public:
	static std::shared_ptr<LoginLog> parseLoginLog(const QString&);
	static std::shared_ptr<ConnectiveLog> parseConnectiveLog(const QString&);
private:
	static Result parseResult(const QVariant&);
	static std::vector<std::shared_ptr<LoginData>> parseLoginData(const QList<QVariant>&);
	static std::shared_ptr<LoginData> parseLoginData(const QVariant&);

	static std::vector<std::shared_ptr<ConnectiveData>> parseConnectiveData(const QList<QVariant>&);
	static std::shared_ptr<ConnectiveData> parseConnectiveData(const QVariant&);
};
#endif//__JSONPARSER__H
