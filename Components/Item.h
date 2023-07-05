#pragma once
#include"Entity.h"

namespace item {
	//最低限の実装をし、あとはコンポーネントで追加
	class Item :public component::Entity
	{
	public:
		Vec2 pos;

		Item();
		~Item()
		{
			//親クラスのデストラクタは必ず呼び出す。
			component::Entity::~Entity();
		}

		void move(Vec2 p);

		void update(double dt)
		{
			//親クラスのupdateを必ず呼び出す。
			component::Entity::update(dt);
		}
		void draw() const
		{
			component::Entity::draw();
		}
	};

	//コンポーネント
	class TextBox:public component::Component
	{
	private:
		RectF window;
		String text;
		Array<std::pair<Vec2,MultiPolygon>> polygons;
		RectF area;
		Vec2 pos;
		Font font;
	public:
		ColorF color=Palette::Black;
		TextBox(const String& text, const Font& font,const RectF& area,const Vec2& pos);
		~TextBox() {};
		void set_pos(Vec2 p);
		void moveBy(Vec2 p);
		void update(double dt);
		void draw() const;
	};
}
