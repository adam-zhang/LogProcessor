#ifndef __NETWORKACCESSOR__H
#define __NETWORKACCESSOR__H

#include <QString>
#include <memory>

class QDateTime;
class LoginLog;
class LoginData;
class ConnectiveLog;
class ConnectiveData;

class NetworkAccessor
{
public:
	NetworkAccessor();
	~NetworkAccessor();
public:
	void getData(const QDateTime&, const QDateTime&);
	std::shared_ptr<LoginLog> getLoginLog(const QDateTime&, const QDateTime&);
	std::shared_ptr<ConnectiveLog> getConnectiveLog(const QDateTime&, const QDateTime&);
private:
	const QString url()const;
	int pageNumber();
	QByteArray post(const QString& url, const QByteArray& data);
	QString targetUrl(int);
	QByteArray loginPostData(int, const QDateTime&, const QDateTime&, const QString&);
	QByteArray connectionPostData(int, const QDateTime&, const QDateTime&, const QString&);
	QByteArray hash(int, const QDateTime&, const QDateTime&, const QString&);
	const QString format() const;
	std::vector<std::shared_ptr<LoginData>> getLoginData(int, const QDateTime&, const QDateTime&, const QString&);
	std::vector<std::shared_ptr<ConnectiveData>> getConnectiveData(int, const QDateTime&, const QDateTime&, const QString&);
};
#endif//__NETWORKACCESSOR__H
