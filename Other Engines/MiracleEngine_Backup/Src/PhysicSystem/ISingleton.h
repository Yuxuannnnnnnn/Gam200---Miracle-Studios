///////////////////////////////////////////////////////////////////////////////////////
//
//	ISingleton.h
//	
//	Authors: yinshuyu
//	Copyright 2019, Digipen Institute of Technology
//
///////////////////////////////////////////////////////////////////////////////////////
#ifndef _ISINGLETON_H
#define _ISINGLETON_H

template<typename Tclass>
class ISingleton
{
	static Tclass* _instance;

public:
	inline explicit ISingleton()
	{
		_instance = static_cast<Tclass*>(this);
	}

	virtual ~ISingleton()
	{
		if (_instance)
		{
			delete _instance;
		}

		_instance = 0;
	}

	ISingleton(const ISingleton& rhs) = delete;
	ISingleton& operator= (const ISingleton& rhs) = delete;

	static Tclass& GetInstance()
	{
		if (!_instance)
		{
			_instance = new Tclass();
		}

		return *_instance;
	}

};

template<typename Tclass>
Tclass* ISingleton<Tclass>::_instance = 0;

#endif
