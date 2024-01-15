#include "Pack.hpp"
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


  // EFFECTS: Initializes the Pack to be in the following standard order:
  //          the cards of the lowest suit arranged from lowest rank to
  //          highest rank, followed by the cards of the next lowest suit
  //          in order from lowest to highest rank, and so on.
  // NOTE: The standard order is the same as that in pack.in.
  // NOTE: Do NOT use pack.in in your implementation of this function
  Pack::Pack() : next(0) {
        int index = 0;
        for (int s = SPADES; s<= DIAMONDS; ++s) {
            for (int i = NINE; i <= ACE; ++i) {
                cards[index++] = Card(static_cast<Rank>(i), static_cast<Suit>(s));
            }
        }

  }



  // REQUIRES: pack_input contains a representation of a Pack in the
  //           format required by the project specification
  // MODIFIES: pack_input
  // EFFECTS: Initializes Pack by reading from pack_input.
  Pack::Pack(std::istream& pack_input) : next(0) {
        std::string ra;
        std::string of;
        std::string su;
        for (int i =0; i< PACK_SIZE; ++i) {
            pack_input >>ra >> of >> su;
            cards[i] = Card(string_to_rank(ra), string_to_suit(su));
        }
  }

  // REQUIRES: cards remain in the Pack
  // EFFECTS: Returns the next card in the pack and increments the next index
  Card Pack::deal_one() {
    assert(next < PACK_SIZE);
    return cards[next++];
  }

  // EFFECTS: Resets next index to first card in the Pack
  void Pack::reset() {
    next = 0;
  }

  // EFFECTS: Shuffles the Pack and resets the next index. This
  //          performs an in shuffle seven times. See
  //          https://en.wikipedia.org/wiki/In_shuffle.
  void Pack::shuffle() {
    for(int i =0; i <7; ++i) {
        std::array<Card, PACK_SIZE> arr;
        for (int j=0; j< PACK_SIZE/2; ++j ) {
            arr[2 * j] = cards[j+PACK_SIZE/2] ;
            arr[2*j +1] = cards[j];
        }

        cards = arr;
    }

    next = 0;
  }

  // EFFECTS: returns true if there are no more cards left in the pack
  bool Pack::empty() const {
    return next >= PACK_SIZE;
  }




