# include <Siv3D.hpp> // OpenSiv3D v0.6.10
#include"Item.h"
#include"Entity.h"

void Main()
{
	component::Entity* entity = new item::Item();
	entity->AddComponent<item::Position>(new item::Position(Vec2{ 3,3 }));
	//entity->AddComponent<item::Position>(new item::Position(Vec2{ 3,3 }));
	item::Position* p = entity->GetComponent<item::Position>();

	p->pos.x = 0;
	Array<component::Entity*>entity_list;
	entity_list << entity;
	while (System::Update())
	{
		ClearPrint();

		double dt = Scene::DeltaTime();

		for (auto& obj : entity_list)
		{
			obj->update(dt);
		}

		for (const auto& obj : entity_list)
		{
			obj->draw();
		}
	}
}
