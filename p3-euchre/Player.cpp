#include "Player.hpp"
#include <array>
#include <string>
#include <iostream>
#include <fstream> 
#include <cstdlib> 
#include <cassert> 
#include <cstring>
#include <string>
#include <array>
#include <vector>
#include <sstream>
#include <algorithm>

using namespace std;

class SimplePlayer : public Player {
private:
    std::string name;
    std::vector<Card> hand;

    // Helper function to count face or ace cards of a given suit
    int count_face_or_ace_of_suit(Suit s) const {
        int count = 0;
        for (const Card &c : hand) {
            if (c.get_suit(s) == s && c.is_face_or_ace()) {
                ++count;
            }
        }
        return count;
    }
public:
    explicit SimplePlayer(const std::string &n) : name(n) {}

    const std::string & get_name() const override {
        return name;
    }

    void add_card(const Card &c) override {
        hand.push_back(c);
    }

    bool make_trump(const Card &upcard, bool is_dealer,
     int round, Suit &order_up_suit) const override {
        if (round == 1) {
            if (count_face_or_ace_of_suit(upcard.get_suit()) >= 2) {
                order_up_suit = upcard.get_suit();
                return true;
            }
        } else if (round == 2) {
            Suit next_suit = Suit_next(upcard.get_suit());
            if (count_face_or_ace_of_suit(next_suit) >= 1 || is_dealer) {
                order_up_suit = next_suit;
                return true;
            }
        }
        return false;
    }

    void add_and_discard(const Card &upcard) override {
        add_card(upcard);
        int index = 0;
        Card discard = hand.at(0);
        for (int i = 0; i<hand.size();i++) {
            if (Card_less(hand.at(i), discard, upcard.get_suit())) {
                discard = hand.at(i);
                index = i;
            }
        }
        hand.erase(hand.begin()+index);
    }

    Card lead_card(Suit trump) override {
        int index = 0;
        bool have_non_trump = false;
        for (int j = 0; j < hand.size(); j++) {
            if (!hand.at(j).is_trump(trump)) {
                have_non_trump = true;
                index = j;
                break;
            }
        }
        Card card_to_lead;
        if (!have_non_trump) {
            Card it = hand.at(0);
            for (int i = 0; i < hand.size(); i++) {
                if (Card_less(it, hand.at(i), trump)) {
                    it = hand.at(i);
                    index = i;
                }
            }
            card_to_lead = it;
        } else {
            Card it;
            for (int i = 0; i < hand.size(); i++) {
                if (!hand.at(i).is_trump(trump)) {
                    it = hand.at(i);
                    index = i;
                }
            }
            for (int i = 0; i < hand.size(); i++) {
                if (Card_less(it, hand.at(i), trump) 
                && !hand.at(i).is_trump(trump)) {
                    it = hand.at(i);
                    index = i;
                }
            }
            card_to_lead = it;
        }
        hand.erase(hand.begin() + index);
        return card_to_lead;
    }

    Card play_card(const Card &led_card, Suit trump) override {
        bool hav = false;
        for (int i = 0; i< hand.size(); i++) {
            if (hand.at(i).get_suit(trump) == led_card.get_suit(trump)) {
                hav = true;
            }
        }
        int index = 0;
        Card it = hand.at(0);
        if (hav) {
            for (int j = 0; j<hand.size(); j++) {
                if (hand.at(j).get_suit(trump) == led_card.get_suit(trump)) {
                    it = hand.at(j);
                    index = j;
                    break;
                }
            }
            it = hand.at(index);
            for (int i = 0; i<hand.size();i++) {
                if (Card_less(it, hand.at(i), led_card, trump)
                &&hand.at(i).get_suit(trump) == led_card.get_suit(trump)) {
                        it = hand.at(i);
                        index = i;
              }
            }
        } else {
            for (int i = 0; i<hand.size();i++) {
            if (Card_less(hand.at(i), it, led_card, trump)) {
                it = hand.at(i);
                index = i;
            }
            }
        }
        Card card_to_play = it;
        hand.erase(hand.begin() + index);
        return card_to_play;
   }
};



class HumanPlayer : public Player {
private:
    std::string name;
    std::vector<Card> hand;

    void print_hand() const {
        for (size_t i = 0; i < hand.size(); ++i) {
            std::cout << "Human player " << name << "'s hand: "
                 << "[" << i << "] " << hand[i] << "\n";
        }
    }

public:
    explicit HumanPlayer(const std::string &n) : name(n) {}

    const std::string & get_name() const override {
        return name;
    }

    void add_card(const Card &c) override {
        hand.push_back(c);
        std::sort(hand.begin(), hand.end());
    }

    bool make_trump(const Card &upcard, bool is_dealer,
     int round, Suit &order_up_suit) const override {
        print_hand();
        std::cout << "Human player " << name 
        << ", please enter a suit, or \"pass\":" << std::endl;

        std::string decision;
        std::cin >> decision;

        if (decision != "pass") {
            order_up_suit = string_to_suit(decision);
            return true;
        }
        return false;
    }

    void add_and_discard(const Card &upcard) override {
        print_hand();
        std::cout << "Discard upcard: [-1]" << std::endl;
        std::cout << "Human player " << name 
        << ", please select a card to discard:" << std::endl;
        int index;
        std::cin >> index;

        if (index == -1) {
            std::sort(hand.begin(), hand.end());
        }
        else {
            hand.erase(hand.begin() + index);
            hand.push_back(upcard);
            std::sort(hand.begin(), hand.end());
        }
    }

    Card lead_card(Suit trump) override {
        print_hand();
        std::cout << "Human player " << name << ", please select a card:" << std::endl;

        int index;
        std::cin >> index;

        Card chosen_card = hand[index];
        hand.erase(hand.begin() + index);
        return chosen_card;
    }

    Card play_card(const Card &led_card, Suit trump) override {
        print_hand();
        std::cout << "Human player " << name << ", please select a card:" << std::endl;

        int index;
        std::cin >> index;

        Card chosen_card = hand[index];
        hand.erase(hand.begin() + index);
        return chosen_card;
    }
};




//EFFECTS: Returns a pointer to a player with the given name and strategy
//To create an object that won't go out of scope when the function returns,
//use "return new Simple(name)" or "return new Human(name)"
//Don't forget to call "delete" on each Player* after the game is over
Player * Player_factory(const std::string &name, const std::string &strategy) {
      // We need to check the value of strategy and return 
  // the corresponding player type.
    if (strategy == "Simple") {
        return new SimplePlayer(name);
    } else if (strategy == "Human") {
        return new HumanPlayer(name);
    }
  assert(false);
  return nullptr;
}

//EFFECTS: Prints player's name to os
std::ostream & operator<<(std::ostream &os, const Player &p) {
    os << p.get_name();
    return os;
}
