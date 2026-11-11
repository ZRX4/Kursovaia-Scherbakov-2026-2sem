#include "base_player.hpp"
#include <iostream>

BasePlayer::BasePlayer(std::string_view name, int stack)
	:m_name{ name }
	, m_stack{ stack }
	, m_id{ NextId() }
	, m_nickname{ std::make_shared<std::string>(name)}
{

	std::cout << "[BasePlayer ctor] " << GetName() << "\n";
}

BasePlayer::BasePlayer(const BasePlayer& other)
	:m_name{ other.m_name }
	, m_stack{ other.m_stack }
	, m_id{ NextId() } // новый id тк новый игрок
	, m_nickname{ std::make_shared<std::string>(*other.m_nickname) }
	, m_isDealer{ other.m_isDealer }

{
	std::cout << "[BasePlayer copy ctor] " << m_name << "\n";
}


BasePlayer& BasePlayer::operator=(const BasePlayer& other) 
{
	if (this == &other) 
	{
		return *this;
	}

	m_name = other.m_name;
    m_stack = other.m_stack;
    m_isDealer = other.m_isDealer;

	m_nickname = std::make_shared<std::string>(*other.m_nickname);
	
	return *this;
}

std::string_view BasePlayer::GetName() const { return m_name; }
int BasePlayer::GetStack() const { return m_stack; }
int BasePlayer::GetId() const { return m_id; }
bool BasePlayer::IsDealer() const { return m_isDealer; }
std::shared_ptr<std::string>BasePlayer::GetNickname() const { return m_nickname; }

void BasePlayer::SitDown(BasePlayer& other) const
{

	std::cout << "  [this] " << GetName() << " садится за стол к " << other.GetName() << "\n";

}

std::string BasePlayer::Header() const
{
	return(m_name + "[" + std::to_string(m_stack) + "]");
}

std::string BasePlayer::Describe() const
{
	if (m_isDealer) {
		return(Header() + " dealer");
	}
	return Header();
}

int BasePlayer::NextId() 
{
	return ++s_lastId;
}

BasePlayer::~BasePlayer() 
{
	std::cout << "[BasePlayer dtor] " << m_name << "\n";
}