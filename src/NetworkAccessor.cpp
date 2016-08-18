#include "NetworkAccessor.h"
#include "Logger.h"
#include "ConnectiveLog.h"
#include "Database.h"
#include "LoginData.h"
#include "LoginLog.h"
#include "JsonParser.h"
#include <QDebug>
#include <QDateTime>
#include <QEventLoop>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QNetworkAccessManager>
#include <QUrl>
#include <QByteArray>
#include <QCryptographicHash>
#include <memory>

using namespace std;

NetworkAccessor::NetworkAccessor()
{
}

NetworkAccessor::~NetworkAccessor()
{
}


void NetworkAccessor::getData(const QDateTime& begin, const QDateTime& end)
{

	shared_ptr<LoginLog> log = getLoginLog(begin, end);
	Database database;
	database.saveLoginData(log->data());
	shared_ptr<ConnectiveLog> connectiveLog = getConnectiveLog(begin, end);
	database.saveConnectiveData(connectiveLog->data());
}

const QString NetworkAccessor::url()const
{
	return "http://www.ay321.com/api/logs/getlogs.php";
}

QByteArray NetworkAccessor::connectionPostData(int page, 
		const QDateTime& begin,
		const QDateTime& end,
		const QString& type)
{
	QString s = QString("sdate=%1&edate=%2&page=%3&type=%4&sign=%5")
		.arg(begin.toString(format()))
		.arg(end.toString(format()))
		.arg(page)
		.arg(type)
		.arg(hash(page, begin, end, type).constData());
	return s.toAscii();
}

shared_ptr<ConnectiveLog> NetworkAccessor::getConnectiveLog(const QDateTime& begin, const QDateTime& end)
{
	QString type = "connection";
	QByteArray data = connectionPostData(1, begin, end, type);
	QString text = post(url(), data);
	shared_ptr<ConnectiveLog> log = JsonParser::parseConnectiveLog(text);
	int total = log->result().totalPage();
	for(int i = 1; i < total; ++i)
	{
		vector<shared_ptr<ConnectiveData>> data = getConnectiveData(i + 1, begin, end, type);
		vector<shared_ptr<ConnectiveData>> vec = log->data();
		copy(data.begin(), data.end(), back_inserter(vec));
		log->setData(vec);
	}
	qDebug() << QString("connective data:%1").arg(log->data().size());
	return log;
}

vector<shared_ptr<ConnectiveData>> NetworkAccessor::getConnectiveData(int page,
		const QDateTime& begin,
		const QDateTime& end,
		const QString& type)
{
	QByteArray data = connectionPostData(page, begin, end, type);
	QString text = post(url(), data);
	auto log = JsonParser::parseConnectiveLog(text);
	return log->data();
}

shared_ptr<LoginLog> NetworkAccessor::getLoginLog(const QDateTime& begin, const QDateTime& end)
{
	QString type = "login";
	QByteArray data = loginPostData(1, begin, end, type );
	QString text = post(url(), data);
	shared_ptr<LoginLog> log = JsonParser::parseLoginLog(text);
	logger().append( QString("login post data:%1").arg(data.constData()));
	int total = log->result().totalPage();
	for(int i = 1; i < total; ++i)
	{
		vector<shared_ptr<LoginData>> data = getLoginData(i + 1, begin, end, type);
		vector<shared_ptr<LoginData>> vec = log->data();
		copy(data.begin(), data.end(), back_inserter(vec));
		log->setData(vec);
	}
	qDebug() << log->data().size();
	return log;
}


vector<shared_ptr<LoginData>> NetworkAccessor::getLoginData(int page, 
		const QDateTime& begin,
		const QDateTime& end,
		const QString& type)
{
	QString text = post(url(), loginPostData(page, begin, end, type));
	auto log = JsonParser::parseLoginLog(text);
	return log->data();
}

QByteArray NetworkAccessor::loginPostData(int page, 
		const QDateTime& begin,
	        const QDateTime& end,
		const QString& type	)
{
	QString s = QString("sdate=%1&edate=%2&page=%3&type=%4&sign=%5")
		.arg(begin.toString(format()))
		.arg(end.toString(format()))
		.arg(page)
		.arg(type)
		.arg(hash(page, begin, end, type).constData());
	//qDebug() << "logindata:" << s;
	return s.toAscii();
}

QByteArray NetworkAccessor::hash(int page, const QDateTime& begin, const QDateTime& end, const QString& type)
{
	QString s = QString("%1%2%3%4%5")
		.arg(page)
		.arg(begin.toString(format()))
		.arg(end.toString(format()))
		.arg(type)
		.arg("79392jjnfaoe89lf23f");
	//qDebug() << "md5:" << s;
	return QCryptographicHash::hash(s.toAscii(), QCryptographicHash::Md5).toHex();
}

const QString NetworkAccessor::format()const
{
	return "yyyy/MM/dd hh:mm:ss";
}

QString NetworkAccessor::targetUrl(int number)
{
	QString url;
	return QString("%1%2").arg(url).arg(number);
}

//int NetworkAccessor::pageNumber()
//{
//	QString url;
//	QByteArray data;
//	QByteArray result = post(url, data);	
//	return parsePageNumber(QString(result.constData()));
//}


QByteArray NetworkAccessor::post(const QString& url, const QByteArray& data)
{
	QNetworkAccessManager manager;
	QNetworkRequest request;
	request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencode");
	request.setUrl(QUrl(url));
	QNetworkReply* reply = manager.post(request, data);
	QEventLoop loop; 
	QObject::connect(&manager, SIGNAL(finished(QNetworkReply*)), &loop, SLOT(quit()));
	loop.exec();
	QByteArray response = reply->readAll();
	return response;
}

//int NetworkAccessor::parsePageNumber(const QString& data)
//{
//	return 0;
//}
