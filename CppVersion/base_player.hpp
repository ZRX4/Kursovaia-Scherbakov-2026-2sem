#pragma once
#include <string>
#include <string_view>
#include <memory>

class BasePlayer {

public:
	//конструктор и вирт. деструктор
	BasePlayer(std::string_view name, int stack);

	virtual ~BasePlayer();

	//геттеры
	std::string_view GetName() const;
	int GetStack() const;
	int GetId() const;
	bool IsDealer() const;

	//виртуальные методы
	virtual std::string Describe() const;
	virtual std::string DecideAction() const = 0;
	virtual std::unique_ptr<BasePlayer> Clone() const = 0;

	static int NextId();

private:

	inline static int s_lastId{ 0 };
	bool m_isDealer{ false } ;
	std::string m_name;
	int m_id{};
	int m_stack{};

//Защищенный метод для наследников
protected:
	std::string Header() const;

};


