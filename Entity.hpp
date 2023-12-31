﻿#pragma once
#include<Siv3D.hpp>

namespace component
{
	class Entity;

	//コンポーネントの基底クラス
	class Component
	{
	public:
		Component() {}
		virtual ~Component() {}
		Entity* Parent;
		virtual void start() {}
		virtual void update(double dt) {}
		virtual void draw()const {}
	};

	//コンポーネントを適用した基底クラス
	//HashTableを使っているので計算量は基本O(1)？
	//同一の型のコンポーネントを追加することは可能　その場合idを指定しないとGetComponentはできない（バグ防止）
	//型が重複してるならGetComponentArrを使うことを推奨
	class Entity
	{
	protected:
		HashTable<size_t, HashTable<String, Component*>> components;
		HashTable<size_t, size_t>ids;
	public:
		Entity()
		{
		};

		virtual ~Entity()
		{
			components.clear();
		};

		//コンポーネントの削除 コンポーネントの型が重複している場合下のif文でid指定で消す
		template<class T>
		void remove(String id=U"")
		{
			if (components[typeid(T).hash_code()].size() <= 1)
			{
				components.erase(typeid(T).hash_code());
				if (ids.contains(typeid(T).hash_code()))ids[typeid(T).hash_code()] -= 1;
				return;
			}
			if (components[typeid(T).hash_code()].contains(id))
			{
				components[typeid(T).hash_code()].erase(id);
				if (ids.contains(typeid(T).hash_code()))ids[typeid(T).hash_code()] -= 1;
			}
		}

		//コンポーネントの追加　idがかぶったら上書き
		template<class T>
		T* AddComponent(const String& id, T* component = new T())
		{
			component->Parent = this;
			component->start();
			components[typeid(T).hash_code()][id] = component;
			return component;
		}
		//コンポーネントの追加　hash_codeなので異なるクラスならidはたぶんかぶらない
		template<class T>
		T* AddComponent(T* component = new T())
		{
			component->Parent = this;
			component->start();

			if (not ids.contains(typeid(T).hash_code()))
			{
				ids[typeid(T).hash_code()] = 0;
			}
			else
			{
				ids[typeid(T).hash_code()] += 1;
			}

			components[typeid(T).hash_code()][Format(ids[typeid(T).hash_code()])] = component;
			return component;
		}

		//コンポーネントの取得　型の重複はなし
		template<class T>
		T* GetComponent()
		{
			if (not components.contains(typeid(T).hash_code()))
			{
				return nullptr;
			}
			//型の重複がある場合エラー
			if (components[typeid(T).hash_code()].size() > 1)
			{
				throw Error{ U"コンポーネントが重複する場合idを指定してください\n重複:" + Format(typeid(T).hash_code()) };

				return nullptr;
			}
			return (T*)components[typeid(T).hash_code()].begin()->second;
		}

		//コンポーネントの取得 id指定。使いどころは複数のコンポーネントが同一の型で重複しているときとか。
		template<class T>
		T* GetComponent(const String& id)
		{
			if (not components.contains(typeid(T).hash_code()))
			{
				return nullptr;
			}

			if (not components[typeid(T).hash_code()].contains(id))
			{
				return nullptr;
			}

			return (T*)components[typeid(T).hash_code()][id];
		}

		template<class T>
		Array<T*>* GetComponentArr()
		{
			Array<T*>* arr = nullptr;

			if (not components.contains(typeid(T).hash_code()))
				return nullptr;

			for (auto& h : components[typeid(T).hash_code()])
			{
				if (arr == nullptr) arr = new Array<T*>();
				*arr << (T*)(h.second);
			}
			return arr;
		}

		//コンポーネントをHashTableで取得。使いどころは複数のコンポーネントが同一の型で重複しているときとか。
		template<class T>
		HashTable<String, T*>* GetComponentHashTable()
		{
			HashTable<String, T*>* ht = nullptr;
			if (not components.contains(typeid(T).hash_code()))
				return nullptr;

			for (const auto& h : components[typeid(T).hash_code()])
			{
				if (ht == nullptr) ht = new HashTable<String, T*>();
				ht->emplace(h.first, (T*)h.second);
			}
			return ht;
		}

		//コンポーネントをアップデート　派生クラスでも呼び出して
		virtual void update_components(double dt)
		{
			for (auto& com_ls : components)
				for (auto& com : com_ls.second)
					com.second->update(dt);
		};

		//コンポーネントをdraw　派生クラスでも呼び出して
		virtual void draw_components() const
		{
			for (const auto& com_ls : components)
				for (const auto& com : com_ls.second)
					com.second->draw();
		};
	};

}
