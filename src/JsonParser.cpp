#include "JsonParser.h"
#include "LoginLog.h"
#include "ConnectiveLog.h"
#include "json.h"
#include <QDebug>

using namespace std;

shared_ptr<LoginLog> JsonParser::parseLoginLog(const QString& text)
{
	shared_ptr<LoginLog> log(new LoginLog);
	Q_ASSERT(log);
	bool ok = false;
	QtJson::JsonObject obj = QtJson::parse(text, ok).toMap();
	if (!ok)
		return shared_ptr<LoginLog>();
	log->setResult(parseResult(obj));
	log->setData(parseLoginData(obj["data"].toList()));
	return log;
}

Result JsonParser::parseResult(const QVariant& v)
{
	QMap<QString, QVariant> map = v.toMap();
	Result result;
	result.setRet(map["ret"].toString().toInt());
	result.setRecordCount(map["recordcount"].toString().toInt());
	result.setPage(map["page"].toString().toInt());
	result.setTotalPage(map["totalpage"].toString().toInt());
	return result;
}

vector<shared_ptr<LoginData>> JsonParser::parseLoginData(const QList<QVariant>& list)
{
	vector<shared_ptr<LoginData>> vec;
	for(auto i = list.begin(); i != list.end(); ++i)
		vec.push_back(parseLoginData(*i));
	return vec;
}

shared_ptr<LoginData> JsonParser::parseLoginData(const QVariant& v)
{
	QMap<QString, QVariant> map = v.toMap();
	shared_ptr<LoginData> data(new LoginData);
	Q_ASSERT(data);
	data->setId(map["id"].toString().toInt());
	data->setUserName(map["username"].toString());
	data->setLoginTime(QDateTime::fromString(map["logintime"].toString(), "yyyy-MM-dd hh:mm:ss"));
	data->setLoginIp(map["loginip"].toString().toInt());
	data->setMac(map["mac"].toString());
	if (data->mac().isNull())
		data->setMac("");
	data->setLoginWay(map["loginway"].toString().toInt());
	data->setDayTimes(map["daytimes"].toString().toInt());
	qDebug() << "json client: " << map["client"];
	data->setClient(map["client"].toString());
	return data;
}

shared_ptr<ConnectiveLog> JsonParser::parseConnectiveLog(const QString& text)
{
	qDebug() << text;
	shared_ptr<ConnectiveLog> log(new ConnectiveLog);
	auto ok = false;
	auto obj = QtJson::parse(text, ok).toMap();
	if (!ok)
		return shared_ptr<ConnectiveLog>();
	log->setResult(parseResult(obj));
	log->setData(parseConnectiveData(obj["data"].toList()));
	return log;
}

vector<shared_ptr<ConnectiveData>> JsonParser::parseConnectiveData(const QList<QVariant>& list)
{
	vector<shared_ptr<ConnectiveData>> vec;
	for_each(list.begin(), list.end(), [&vec](const QVariant& v)
	{
		vec.push_back(parseConnectiveData(v));
	});
	return vec;
}

shared_ptr<ConnectiveData> JsonParser::parseConnectiveData(const QVariant& v)
{
	auto data(make_shared<ConnectiveData>());
	Q_ASSERT(data);
	auto map = v.toMap();
	data->setId(map["radacctid"].toString().toInt());
	data->setUserName(map["username"].toString());
	data->setNasipAddress(map["nasipaddress"].toString().toUInt());
	data->setCallingStationId(map["callingstationid"].toString().toUInt());
	qDebug() << map["framedipaddress"].toString();
	data->setFramedIpAddress(map["framedipaddress"].toString().toUInt());
	qDebug() << data->framedIpAddress();
	data->setStartTime(QDateTime::fromString(map["acctstarttime"].toString(), "yyyy-MM-dd hh:mm:ss"));
	if (map["acctstoptime"].isNull() || map["acctstoptime"] == "0000-00-00 00:00:00")// == QVariant(NULL))
		data->setStopTime(QDateTime(QDate(1970, 1, 1), QTime( 0, 0, 0)));
	else
		data->setStopTime(QDateTime::fromString(map["acctstoptime"].toString(), "yyyy-MM-dd hh:mm:ss"));
	data->setInputOctets(map["acctinputoctets"].toString().toInt());
	data->setOutputOctets(map["acctoutputoctets"].toString().toInt());
	data->setSessionTime(map["acctsessiontime"].toString().toInt());
	data->setClient(map["client"].toString());
	data->setMac(map["mac"].toString());
	qDebug() <<"mac:" << map["mac"].isNull();
	if (data->mac().isNull())
		data->setMac("");
	return data;

}
