#include "PrecompiledHeaders.h"
#include "ICollider2D.h"

Collider2D::Collider2D() :
	_type{ (unsigned)ColliderType::NONE_COLLIDER },
	_tag{ (unsigned)ColliderTag::NONE },
	_layer{ 0 },
	_trigger{ true },
	_attachedRigidboy{ false },
	_componentEnable{ true }
{}

std::string Collider2D::ComponentName() const
{
	return "ColliderComponent";
}


void Collider2D::Inspect()
{
	IComponent::Inspect();

	ImGui::Spacing();
	ImGui::Checkbox("Collider Tigger", &_trigger);

	ImGui::Spacing();
	{
		ImGui::Spacing();

		static auto& TagList = MyPhysicsSystem._collisionTable.GetTagList();
		std::vector<const char*> list;
		list.push_back("Choose a Collider Tag ");
		static const char* name = list[0];


		int i = 1;
		static int select = 0;
		for (auto TagPair = TagList.begin(); TagPair != TagList.end(); TagPair++, i++)
		{
			const char* ptr = TagPair->first.c_str();
			list.push_back(ptr);
			if (TagPair->second == (size_t)_tag)
				select = i;
		}

		if (ImGui::BeginCombo(" ", list[select], 0)) // The second parameter is the label previewed before opening the combo.
		{
			for (int n = 0; n < list.size(); n++)
			{
				bool is_selected = (name == list[n]);
				if (ImGui::Selectable(list[n], is_selected))
				{
					_tag = TagList[list[n]];
					select = n;
				}

			}
			ImGui::EndCombo();
		}
	}

}


void Collider2D::DeSerialiseComponent(rapidjson::Value& prototypeDoc, rapidjson::MemoryPoolAllocator<>& allocator)
{
	rapidjson::Value value;

	value.SetInt(_type);
	prototypeDoc.AddMember("ColliderTypeId", value, allocator);

	value.SetInt(_tag);
	prototypeDoc.AddMember("ColliderTag", value, allocator);

	value.SetBool(_trigger);
	prototypeDoc.AddMember("ColliderTrigger", value, allocator);
}