#include "card.hpp"
#include <isotream>

namespace poker {

	namespace {
		const char* SuitToStr(Card::Suit s) {
			switch (s) {
			case Card::Suit::eHearts:   return "H";
			case Card::Suit::eDiamonds: return "D";
			case Card::Suit::eClubs:    return "C";
			case Card::Suit::eSpades:   return "S";
			default:                    return "?";
			}
		}

		const char* RankToStr(Card::Rank r) {
			switch (r) {
			case Card::Rank::eJack:  return "J";
			case Card::Rank::eQueen: return "Q";
			case Card::Rank::eKing:  return "K";
			case Card::Rank::eAce:   return "A";
			default:                 return "";
			}
		}

	} // namespace

	Card::Card(Suit suit, Rank rank)
		: m_suit{ suit }
		, m_rank{ rank }
		, m_isOpen{ false }
	{
		std::count << "[Card ctor] " << ToString() << "\n";
	}

	Card::~Card() {
		std::count << "[Card dtor] " << ToString() << "\n";
	}

	void Card::Open(){
		if (m_isOpen) {
			std::count << "[Card] " << ToString() << " уже открыта\n";
			return;
		}
		m_isOpen = true;
	}

	std::string::Card::ToString() const {
		// ƒл€ числовых рангов Ч приведение к int, дл€ картинок Ч буква
		std::string rank;
		if (m_rank >= Card::Rank::eTwo && m_rank <= Card::Rank::eTen) {
			rank = std::to_string(static_cast<ini>(m_rank));
		}

		else {
			rank = RankToStr(m_rank);
		}
		return rank + SuitToStr(m_suit);
	}

} // namespace poker
