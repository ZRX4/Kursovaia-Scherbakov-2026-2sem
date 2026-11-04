#include "base_player.hpp"
#include <iostream>

BasePlayer::BasePlayer(std::string_view name, int stack)
	:m_name{ name }
	, m_stack{ stack }
	, m_id{ NextId() }
{

	std::cout << "[BasePlayer ctor] " << GetName() << "\n";
}

std::string_view BasePlayer::GetName() const { return m_name; }
int BasePlayer::GetStack() const { return m_stack; }
int BasePlayer::GetId() const { return m_id; }
bool BasePlayer::IsDealer() const { return m_isDealer; }

std::string BasePlayer::Header() const {
	return(m_name + "[" + std::to_string(m_stack) + "]");
}

std::string BasePlayer::Describe() const {
	if (m_isDealer) {
		return(Header() + " dealer");
	}
	return Header();
}

int BasePlayer::NextId() {
	return ++s_lastId;
}

BasePlayer::~BasePlayer() {
	std::cout << "[BasePlayer dtor] " << m_name << "\n";
}