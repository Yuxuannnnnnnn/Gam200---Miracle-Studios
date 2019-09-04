///////////////////////////////////////////////////////////////////////////////
///
///	\file Serialization.h
///	Defines ISerializer interface and basic stream opeartors.
///
///	Authors: Chris Peters
///	Copyright 2010, Digipen Institute of Technology
///
///////////////////////////////////////////////////////////////////////////////
#pragma once

namespace Framework
{
	///Base Serializer interface. Concrete serializers (Text, Xml, Binary) 
	///implement this interface. This separates the serialization process 
	///(what data needs to be read) from the serialization format (Text,Binary)
	///The serializers only need to implement the serialization of fundamental
	///type to be used by the engine.
	class ISerializer
	{
	public:
		///Open the serialization stream from a file.
		virtual bool Open(const std::string& file)=0;
		///Does the stream still have data?
		virtual bool IsGood()=0;
		virtual void ReadInt(int& i)=0;
		virtual void ReadFloat(float& f)=0;
		virtual void ReadString(std::string& str)=0;
	};

	//Serialization Operators 


	//Base case of serialization is that the object serializes itself.
	template<typename type>
	inline void StreamRead(ISerializer& stream,type& typeInstance)
	{
		typeInstance.Serialize(stream);
	}

	//Base non recursive stream operators of fundamental types.

	inline void StreamRead(ISerializer& stream,float& f)
	{
		stream.ReadFloat(f);
	}

	inline void StreamRead(ISerializer& stream,int& i)
	{
		stream.ReadInt(i);
	}

	inline void StreamRead(ISerializer& stream,std::string& str)
	{
		stream.ReadString(str);
	}


}
