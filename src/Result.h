#ifndef __RESULT__H
#define __RESULT__H

class Result
{
public:
	Result();
	~Result();
public:
	int ret()
	{ return ret_; }
	void setRet(int value)
	{ ret_ = value;}
	const int& recordCount()const
	{ return recordCount_;}
	void setRecordCount(int value)
	{ recordCount_ = value;}
	int page()
	{ return page_;}
	void setPage(int value)
	{ page_ = value; }
	const int& totalPage()const
	{ return totalPage_; }
	void setTotalPage(int totalPage)
	{ totalPage_ = totalPage;}
public:
	int ret_;
	int recordCount_;
	int page_;
	int totalPage_;
};
#endif//__RESULT__H
