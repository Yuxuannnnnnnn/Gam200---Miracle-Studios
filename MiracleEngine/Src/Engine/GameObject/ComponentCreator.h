#pragma once
#include "IComponent.h"

class ComponentCreator
{
public:
	ComponentCreator(ComponentId typeId)
		:TypeId(typeId)
	{
	}

	ComponentId TypeId;
	///Create the component
	virtual IComponent* Create() = 0;
};

///Templated helper class used to make concrete component creators.
template<typename type>
class ComponentCreatorType : public ComponentCreator
{
public:
	ComponentCreatorType(ComponentId typeId)
		:ComponentCreator(typeId)
	{
	}

	virtual IComponent* Create()
	{
		return new type();
	}
};

//Register component macro
#define RegisterComponent(type) MyFactory.AddComponentCreator( #type, new ComponentCreatorType<type##Component>( ComponentId::CT_##type ) );

