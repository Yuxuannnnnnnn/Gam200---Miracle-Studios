///////////////////////////////////////////////////////////////////////////////////////
//
//	IForce.h
//	
//	Authors: yinshuyu
//	Copyright 2019, Digipen Institute of Technology
//
///////////////////////////////////////////////////////////////////////////////////////
#ifndef _IFORCE_H
#define _IFORCE_H

class IForce
{
public:
	virtual ~IForce() {}
protected:
	
	void AddForce(size_t uId, Vector3 forceDir, float force);
	void AddForwardForce(size_t uId, float force);
	
};

#endif
