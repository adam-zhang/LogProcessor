#ifndef __CONNECTIVELOG__H
#define __CONNECTIVELOG__H

#include "Result.h"
#include "ConnectiveData.h"
#include <memory>
#include <vector>

class ConnectiveLog
{
public:
	ConnectiveLog() {}
	~ConnectiveLog() {}
private:
	Result result_;
	std::vector<std::shared_ptr<ConnectiveData>> data_;
public:
	void setResult(const Result& value)
	{ result_ = value; }
	const Result& result()const
	{ return result_; }
	void setData(const std::vector<std::shared_ptr<ConnectiveData>>& value)
	{ data_ = value; }
	const std::vector<std::shared_ptr<ConnectiveData>>& data()const
	{ return data_; }

};
#endif//__CONNECTIVELOG__H
