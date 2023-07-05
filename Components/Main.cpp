# include <Siv3D.hpp> // OpenSiv3D v0.6.10
#include"Item.h"
#include"Entity.h"
#include"Window.h"

void Main()
{

	Array<component::Entity*>entity_list;
	window::Window* w = new window::Window(Vec2{ 10,10 }, 600, 500);
	w->color = ColorF(Palette::White, 0.3);
	entity_list << w;

	while (System::Update())
	{
		//ClearPrint();

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
