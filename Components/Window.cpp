#include "stdafx.h"
#include "Window.h"


window::Window::Window(Vec2 pos, double w, double h)
	:pos(pos), window(RectF{ pos,w,h })
{
	using namespace window;
	WindowItems* item_setter = AddComponent<WindowItems>(new WindowItems(Vec2(pos.x+50,pos.y+50),70));
	item_setter->addTextBox(U"left", Font{ 15 },U"学費を上げる",100, 4);
	item_setter->addTextBox(U"center", Font{ 15 }, U"学費を上げることで得られる資金が多くなる",300, 4);
	item_setter->addTextBox(U"right", Font{ 10 }, U"消費:\n名声 0",60, 4);
	item_setter->addItem(2);
	item_setter->addTextBox(U"left", Font{ 15 }, U"学費を上げる", 100, 4);
	item_setter->addTextBox(U"center", Font{ 15 }, U"学費を上げることで得られる資金が多くなる", 300, 4);
	item_setter->addTextBox(U"right", Font{ 10 }, U"消費:\n名声 0", 60, 4);
	item_setter->addItem(2);
}

void window::Window::update(double dt)
{
	component::Entity::update(dt);
	if (KeyW.pressed())
	{
		WindowItems* item_setter = GetComponent<WindowItems>();
		item_setter->move_item(dt, Vec2{ 0,-400 });
	}
	if (KeyS.pressed())
	{
		WindowItems* item_setter = GetComponent<WindowItems>();
		item_setter->move_item(dt, Vec2{ 0,400 });
	}
}

void window::Window::draw() const
{
	window.draw(color);
	component::Entity::draw();
}

using namespace window;

WindowItems::WindowItems(Vec2 base_pos, double size1, bool virtical)
	:item_pos(base_pos), box_pos(base_pos), virtical(virtical)
{
	virtical ? h = size1 : w = size1;
	pre_item = new item::Item();
}

void WindowItems::addTextBox(String id, Font f, String text, double another_size,double interval)
{
	virtical ? w = another_size:h=another_size;
	
	pre_item->AddComponent<item::TextBox>(id, new item::TextBox(text, f, RectF{0,0,w,h}, box_pos));
	(not virtical) ? box_pos.y += h + interval : box_pos.x += w + interval;
}

void WindowItems::addItem(double interval)
{
	items << *pre_item;
	delete pre_item;
	pre_item = new item::Item();
	virtical ? item_pos.y = box_pos.y + h +interval : item_pos.x = box_pos.x+ w + interval;
	box_pos = item_pos;
}

void WindowItems::move_item(double dt,Vec2 vel)
{
	for (auto& itm : items)
	{
		itm.move(dt * vel);
	}
}

void WindowItems::draw()const
{
	for (const auto& itm : items)
	{
		itm.draw();
	}
}
