///////////////////////////////////////////////////////////////////////////////////////
//
//	ISingleton.h
//	
//	Authors: yinshuyu
//	Copyright 2019, Digipen Institute of Technology
//
///////////////////////////////////////////////////////////////////////////////////////
#ifndef _ICONTAIONER_H
#define _ICONTAIONER_H

class IContainer
{
public:
	IContainer() = default;
	virtual ~IContainer() {}

	virtual void AddObject(size_t uId) = 0;
	virtual void RemoveObject(size_t uId) = 0;
};

#endif
