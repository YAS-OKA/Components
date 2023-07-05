#include "stdafx.h"
#include "Item.h"

using namespace item;

Item::Item()
{
}

void Item::move(Vec2 p)
{
	Array<TextBox*>* arr = GetComponentArr<TextBox>();
	if (arr == nullptr)return;

	for (auto& t : *arr)
	{
		t->moveBy(p);
	}
}

TextBox::TextBox(const String& text, const Font& font, const RectF& Area, const Vec2& pos)
	:font(font), text(text), area(Area), pos(pos)
{
	area = area.movedBy(pos);

	//箱の縦棒と文字の間の間隔
	double interval = 10;
	//文字の横間隔
	double moji_inte = 2;
	//文字の行間隔
	double gyou_inte = 3;
	//中央ぞろえ
	//polygon化したときに文章の横はばと縦はばを求める
	int32 max_width=0;
	int32 w = 0;
	int32 h = 0;
	for (const auto& t : text.split(U'\n'))
	{
		for (const auto& polyg : font.renderPolygons(t))
		{
			polygons << std::pair<Vec2, MultiPolygon>(Vec2{ w,h }, polyg.polygons);
			w += polyg.width+moji_inte;
			if (w > area.w - interval*2)
			{
				if (max_width < w - polyg.width-moji_inte)
				{
					max_width = w - polyg.width- moji_inte;
				}
				w = 0;
				h += font.fontSize()+gyou_inte;
			}
		}
		h += font.fontSize() + gyou_inte;
		w = 0;
	}
	//文字polygonを配置する
	double top = area.centerY() - h / 2-gyou_inte+font.fontSize()/2;
	double left = area.pos.x + interval;

	for (auto& polys : polygons)
	{
		for (auto& poly : polys.second)
		{
			poly.moveBy(Vec2{ polys.first.x + left,polys.first.y + top });
			//Print << Vec2{ w + left, h + top };
		}
	}
}



void TextBox::set_pos(Vec2 p)
{
	area = area.movedBy(p - pos);
	pos = p;
}

void TextBox::moveBy(Vec2 p)
{
	area = area.movedBy(p);
	pos += p;
}

void TextBox::update(double dt)
{
	
}

void TextBox::draw() const
{
	area.drawFrame();
	
	//font(text).draw(area, color);
	for (const auto& polys : polygons)
	{
		for (const auto& poly : polys.second)
		{
			poly.draw(color);
		}
	}
}
