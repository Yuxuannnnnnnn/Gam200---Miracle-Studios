///////////////////////////////////////////////////////////////////////////////
///
///	\file TextSerialization.h
///	Text based concrete serializer class.
///
///	Authors: Chris Peters
///	Copyright 2010, Digipen Institute of Technology
///
///////////////////////////////////////////////////////////////////////////////

#pragma once
#include "Serialization.h"
#include <fstream>

namespace Framework
{
	///Serializer for a simple text file format.
	class TextSerializer : public ISerializer
	{
	public:
		std::ifstream stream;
		virtual bool Open(const std::string& file);
		virtual bool IsGood();
		virtual void ReadInt(int& i);
		virtual void ReadFloat(float& f);
		virtual void ReadString(std::string& str);
	};

}