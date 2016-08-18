#ifndef __LOGINLOG__H
#define __LOGINLOG__H

#include "Result.h"
#include "LoginData.h"
#include <memory>

class LoginLog
{
public:
	LoginLog();
	~LoginLog();
private:
	Result result_;
	std::vector<std::shared_ptr<LoginData>> data_;
public:
	void setResult(const Result& value)
	{ result_ = value;}
	const Result& result()const
	{ return result_; }
	void setData(const std::vector<std::shared_ptr<LoginData>>& data)
	{ data_ = data;}
	const std::vector<std::shared_ptr<LoginData>>& data()const
	{ return data_;}

};
#endif//__LOGINLOG__H
