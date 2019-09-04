///////////////////////////////////////////////////////////////////////////////
//
//	ComponentTypeIds.h
//	Global Enumeration for component type ids.	
//
//	Authors: Chris Peters,
//	Copyright 2010, Digipen Institute of Technology
//
///////////////////////////////////////////////////////////////////////////////


#pragma once

namespace Framework
{
	//A simple enumeration used to identify components quickly and efficiently.
	//There is alternative methods for generating ids automatically, 
	//(string hashing, static type ids).
	//But this is a clean, easy, understandable and stable way.
	enum ComponentTypeId
	{
		//Invalid component id
		CT_None = 0,
		//Basic Components
		CT_Transform,
		//Graphics
		CT_Camera,
		CT_Sprite,
		//Physics
		CT_Body,
		//Game Logic
		CT_Controller,
		CT_Bomb,
		//Max
		CT_MaxComponents
	};

}