#include "BaseObject.h"

BaseObject::BaseObject()
{
}

BaseObject::~BaseObject()
{
}

int BaseObject::id()
{
	return id_;
}

void BaseObject::setId(int value)
{
	id_ = value;
}
