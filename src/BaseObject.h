#ifndef __BASEOBJECT__H
#define __BASEOBJECT__H

class BaseObject
{
public:
	BaseObject();
	~BaseObject();
private:
	int id_;
public:
	int id();
	void setId(int );
};
#endif//__BASEOBJECT__H
