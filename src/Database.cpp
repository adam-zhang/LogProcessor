#include "Database.h"
#include "MatchedData.h"
#include "ConnectiveData.h"
#include "LoginData.h"
#include "Configuration.h"
#include <QSqlQuery>
#include <QDebug>
#include <QSqlError>

using namespace std;

Database::Database()
{
}

Database::~Database()
{
}

bool Database::connect()
{
	//qDebug() << "connect entering";
	Configuration config;
	QSqlDatabase db;
        if (QSqlDatabase::contains("qt_sql_default_connection"))
	{
		db = QSqlDatabase::database("qt_sql_default_connection");
	}
	else
	{
		db = QSqlDatabase::addDatabase("QMYSQL");
	
		db.setHostName(config.hostName());
		db.setUserName(config.userName());
		db.setPassword(config.password());
		db.setDatabaseName(config.databaseName());
	}
	db_ = db;
	bool ok = db_.open();
	return ok;

}

vector<QString> Database::getTableNames()
{
	vector<QString> vec = {"ay_loginlogs", "ay_radacct"};
	return vec;
}

bool Database::createTable(const QSqlDatabase& db, const QString& tableName)
{
	QSqlDatabase database = db;
	QString sql = QString("CREATE TABLE if not exists `%1` (" //ay_loginlogs` ("
  			"`id` bigint(21) NOT NULL,"
  			"`username` char(15) NOT NULL,"
			 "`logintime` datetime NOT NULL,"
			 "`loginip` bigint(21) NOT NULL,"
			 "`mac` varchar(64) NOT NULL,"
			 "`loginway` tinyint(4) NOT NULL,"
			 "`daytimes` int(8) NOT NULL"
			") DEFAULT CHARSET=utf8;").arg(tableName);
	//qDebug() << "create table:" << sql;
	QSqlQuery query(sql, database);
	bool ok = query.exec();
	if (!ok)
	{
		qDebug() << "ok:" << ok;
		qDebug() << "databaseText:" << db.lastError().databaseText();
		qDebug() << "isValid:" << db.lastError().isValid();
		qDebug() << "driverText:" << db.lastError().driverText();
		qDebug() << "number:" << db.lastError().number() << "\n" 
			<< "text:" << db.lastError().text() << "\n" 
			<< "type:" << db.lastError().type();
	}
	return ok;
}

bool Database::saveLoginData(const vector<shared_ptr<LoginData>>& data)
{
	for(size_t i = 0 ; i < data.size(); ++i)
		saveLoginData(data[i]);
	return true;
}

bool Database::saveConnectiveData(const vector<shared_ptr<ConnectiveData>>& data)
{
	for(auto i = data.begin(); i != data.end(); ++i)
		if (!saveConnectiveData(*i))
			db_.lastError();	
	return true;
}

bool Database::saveConnectiveData(const shared_ptr<ConnectiveData>& data)
{
	if (!connect())
		return false;
	QSqlQuery query;
	query.prepare("insert into ay_radacct(radacctid, mac, username, nasipaddress,callingstationid, framedipaddress,"
			"acctstarttime, acctstoptime, acctsessionTime, acctinputoctets, acctoutputoctets, client, acctstarttime_stamp, acctstoptime_stamp)"
			"values(:radacctid, :mac, :username, :nasipaddress, :callingstationid, :framedipaddress,"
			":acctstarttime, :acctstoptime, :sessionTime, :inputoctets,:outputoctets,:client, :starttime_stamp, :stoptime_stamp)");
	query.bindValue(":radacctid", data->id());
	query.bindValue(":username", data->userName());
	query.bindValue(":nasipaddress", data->nasipAddress());
	query.bindValue(":callingstationid", data->callingStationId());
	query.bindValue(":framedipaddress", data->framedIpAddress());
	query.bindValue(":acctstarttime", data->startTime());
	query.bindValue(":acctstoptime", data->stopTime());
	query.bindValue(":sessionTime", data->sessionTime());
	query.bindValue(":inputoctets", data->inputOctets());
	query.bindValue(":outputoctets", data->outputOctets());
	query.bindValue(":client", data->client());
	query.bindValue(":mac", data->mac());
	query.bindValue(":starttime_stamp", data->startTimeStamp());
	query.bindValue(":stoptime_stamp", data->stopTimeStamp());
	bool ok = query.exec();
	if (!ok)
	{
		qDebug() << data->id();
		qDebug() << data->userName();
		qDebug() << data->nasipAddress();
		qDebug() << data->callingStationId();
		qDebug() << data->framedIpAddress();
		qDebug() << data->startTime();
		qDebug() << data->stopTime();
		qDebug() << db_.lastError();
	}
	return ok;
}

bool Database::saveLoginData(const shared_ptr<LoginData>& data)
{
	if (!connect())
		return false;
	QSqlQuery query;
	query.prepare("insert into ay_loginlogs(id, client, username, logintime, loginip, mac, loginway, daytimes, logintime_stamp)"
			"values(:id, :client, :username, :logintime, :loginip, :mac, :loginway, :daytimes, :logintime_stamp)");
	query.bindValue(":id", data->id());
	query.bindValue(":username", data->userName());
	query.bindValue(":logintime", data->loginTime());
	query.bindValue(":loginip",data->loginIp());
	query.bindValue(":mac", data->mac()); 
	query.bindValue(":loginway", data->loginWay());
	query.bindValue(":daytimes", data->dayTimes());
	query.bindValue(":client" , data->client());
	query.bindValue(":logintime_stamp", data->loginTimeStamp());
	//qDebug() << "client:" << data->client();
	bool ok = query.exec();
	if (!ok)
	{
		qDebug() << "save data failed";
	}
	return true;
}

const QString Database::tableName(const QString& ip, const QDateTime& begin)
{
	QString tableName = QString("%1_%2_%3")
		.arg("ay_accesslog")
		.arg(ip)
		.arg(begin.toString("yyyyMMdd"));
	return tableName;
}

bool Database::createTable(const QString& ip, const QDateTime& begin)
{
	//QString sql = QString("create table %1 (select * from ay_accesslog_tpl);").arg(tableName(begin));
	QString sql = QString("CREATE TABLE if not exists `%1` ("
	  "`id` bigint(21) NOT NULL AUTO_INCREMENT,"
	  "`username` char(15) NOT NULL,"
	  "`serverip` bigint(16) NOT NULL,"
	  "`userip` bigint(16) NOT NULL,"
	  "`privateip` bigint(16) NOT NULL,"
	  "`logintime` datetime NOT NULL,"
	  "`method` char(10) NOT NULL,"
	  "`logintime_stamp` int not null, "
	  "`url` varchar(20000) NOT NULL, "
	  "PRIMARY KEY (`id`),"
	  "UNIQUE KEY `id_UNIQUE` (`id`)"
	") ENGINE=MyISAM DEFAULT CHARSET=utf8;").arg(tableName(ip, begin));
	qDebug() << sql;
	if (!connect())
		return false;
	QSqlQuery query;
	query.prepare(sql);
	bool ok = query.exec();
	if (!ok)
		qDebug() << db_.lastError();
	return ok;
	//return false;
}

bool Database::saveMatchedData(const shared_ptr<MatchedData>& data, const QString& ip, const QDateTime& begin)
{
	QString sql = QString("insert into %1 (username,  serverip, userip, privateip, logintime, method, url, logintime_stamp)"
		"values(:username,  :serverip, :userip, :privateip, :logintime, :method, :url, :logintime_stamp);")
		.arg(tableName(ip ,begin));
	//qDebug() << sql;
	if (!connect())
		return false;
	QSqlQuery query;
	query.prepare(sql);
	query.bindValue(":userip", data->userIP());
	query.bindValue(":username", data->userName());
	query.bindValue(":serverip", data->serverIP());
	query.bindValue(":privateip", data->privateIP());
	
	query.bindValue(":logintime", data->loginTime().toString("yyyy-MM-dd hh:mm:ss"));
	query.bindValue(":method", data->method());
	query.bindValue(":url", data->url());
	query.bindValue(":logintime_stamp", data->loginTimeStamp());
	bool ok = query.exec();
	if (!ok)
	{
		qDebug() << "userIP" << data->userIP();
		qDebug() << "userName" << data->userName();
		qDebug() << "serverIP:" << data->serverIP();
		qDebug() << "privateIP:" << data->privateIP();
		qDebug() << data->loginTime().toString();
		qDebug() << "method:" << data->method();
		qDebug() << "url:" << data->url();
		qDebug() << db_.lastError();
	}
	return ok;
	//return false;
}

vector<shared_ptr<ConnectiveData>> Database::getConnectiveData(unsigned int serverIp, const QDateTime& begin, const QDateTime& end)
{
	qDebug() << "serverIP:" << serverIp;
	if (!connect())
		return vector<shared_ptr<ConnectiveData>>();
	QString sql = "select * from ay_radacct where nasipaddress=:nasipaddress"
			  " and acctstarttime>=:starttime and acctstarttime <= :endtime;";
	QSqlQuery query;
	query.prepare(sql);
	query.bindValue(":nasipaddress", serverIp);
	query.bindValue(":starttime", begin.toString("yyyy-MM-dd hh:mm:ss"));
	query.bindValue(":endtime", end.toString("yyyy-MM-dd hh:mm:ss"));
	if (!query.exec())
	{
		qDebug() << db_.lastError();
		return vector<shared_ptr<ConnectiveData>>();
	}
	vector<shared_ptr<ConnectiveData>> vec;
	enum 
	{
		id,
		username,
		nasipaddress,
		callingstationid,
		framedipaddress,
		acctstarttime,
		acctstoptime,
	};
	while(query.next())
	{
		shared_ptr<ConnectiveData> data(new ConnectiveData);
		data->setId(query.value(id).toInt());
		data->setUserName(query.value(username).toString());
		data->setNasipAddress(query.value(nasipaddress).toInt());
		data->setCallingStationId(query.value(callingstationid).toInt());
		data->setFramedIpAddress(query.value(framedipaddress).toInt());
		data->setStartTime(query.value(acctstarttime).toDateTime());
		data->setStopTime(query.value(acctstoptime).toDateTime());
		vec.push_back(data);
	}

	return vec;
}
