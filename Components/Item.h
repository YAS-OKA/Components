#pragma once
#include"Entity.h"

namespace item {
	//最低限の実装をし、あとはコンポーネントで追加
	class Item :public component::Entity
	{
	public:
		Item(){}
		~Item()
		{
			//親クラスのデストラクタは必ず呼び出す。
			component::Entity::~Entity();
		}

		void update(double dt)
		{
			//親クラスのupdateを必ず呼び出す。
			component::Entity::update(dt);
		}
		void draw()
		{
			component::Entity::draw();
		}
	};

	class Position : public component::Component
	{
	public:
		Vec2 pos;
		Position(Vec2 p) :pos(p) {}

		void draw()const
		{
			Print << pos;
		}
	};
}
