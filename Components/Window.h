#pragma once
#include"Entity.h"
#include"Item.h"

namespace window
{
	class Window:public component::Entity
	{
	public:
		Window(Vec2 pos,double w,double h);
		~Window() { component::Entity::~Entity(); };
		void update(double dt);
		void draw()const;
		ColorF color;

	private:
		Vec2 pos;
		RectF window;
	};

	class WindowItems :public component::Component
	{
	private:
		Array<item::Item> items;

		Vec2 item_pos;

		Vec2 box_pos;
		//縦並びかどうか
		bool virtical;

		item::Item* pre_item;

		//テキストボックスの長さ
		double w;
		double h;
	public:
		//virtical=trueの場合
		WindowItems(Vec2 base_pos,double size1,bool virtical = true);

		void addTextBox(String id, Font f, String text,double another_size,double interval = 0.0);

		void addItem(double interval=0.0);

		void move_item(double dt,Vec2 vel);

		void draw()const;
	};
}
