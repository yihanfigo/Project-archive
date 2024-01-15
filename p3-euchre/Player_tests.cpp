#include "Player.hpp"
#include "unit_test_framework.hpp"

#include <iostream>

using namespace std;

TEST(test_player_get_name) {
    Player * alice = Player_factory("Alice", "Simple");
    ASSERT_EQUAL("Alice", alice->get_name());

    delete alice;
}
TEST(test_player_add_card) {
  Player * bob = Player_factory("Bob", "Simple");
  bob->add_card(Card(NINE, SPADES));
  bob->add_card(Card(TEN, SPADES));
  bob->add_card(Card(QUEEN, SPADES));
  bob->add_card(Card(KING, SPADES));
  bob->add_card(Card(ACE, SPADES));

  ASSERT_EQUAL(bob->play_card(Card(NINE, DIAMONDS), HEARTS), Card(NINE, SPADES));
  ASSERT_EQUAL(bob->play_card(Card(NINE, DIAMONDS), HEARTS), Card(TEN, SPADES));
  ASSERT_EQUAL(bob->play_card(Card(NINE, DIAMONDS), HEARTS), Card(QUEEN, SPADES));
  ASSERT_EQUAL(bob->play_card(Card(NINE, DIAMONDS), HEARTS), Card(KING, SPADES));
  ASSERT_EQUAL(bob->play_card(Card(NINE, DIAMONDS), HEARTS), Card(ACE, SPADES));
  delete bob;
}

TEST(test_player_add_and_discard) {
  Player * bob = Player_factory("Bob", "Simple");
  bob->add_card(Card(JACK, SPADES));
  bob->add_card(Card(TEN, SPADES));
  bob->add_card(Card(QUEEN, SPADES));
  bob->add_card(Card(KING, SPADES));
  bob->add_card(Card(ACE, SPADES));
  bob->add_and_discard(Card(NINE, SPADES));
  ASSERT_EQUAL(bob->play_card(Card(NINE, DIAMONDS), HEARTS), Card(TEN, SPADES));
  ASSERT_EQUAL(bob->play_card(Card(NINE, DIAMONDS), HEARTS), Card(JACK, SPADES));
  ASSERT_EQUAL(bob->play_card(Card(NINE, DIAMONDS), HEARTS), Card(QUEEN, SPADES));
  ASSERT_EQUAL(bob->play_card(Card(NINE, DIAMONDS), HEARTS), Card(KING, SPADES));
  ASSERT_EQUAL(bob->play_card(Card(NINE, DIAMONDS), HEARTS), Card(ACE, SPADES));
  delete bob;
  Player * boba = Player_factory("Bob", "Simple");
  boba->add_card(Card(JACK, SPADES));
  boba->add_card(Card(NINE, DIAMONDS));
  boba->add_card(Card(TEN, SPADES));
  boba->add_card(Card(TEN, HEARTS));
  boba->add_card(Card(ACE, HEARTS));
  boba->add_and_discard(Card(NINE, SPADES));
  ASSERT_EQUAL(boba->play_card(Card(NINE, CLUBS), SPADES), Card(TEN, HEARTS));
  ASSERT_EQUAL(boba->play_card(Card(NINE, CLUBS), SPADES), Card(ACE, HEARTS));
  ASSERT_EQUAL(boba->play_card(Card(NINE, CLUBS), SPADES), Card(NINE, SPADES));
  ASSERT_EQUAL(boba->play_card(Card(NINE, CLUBS), SPADES), Card(TEN, SPADES));
  ASSERT_EQUAL(boba->play_card(Card(NINE, CLUBS), SPADES), Card(JACK, SPADES));
  delete boba;
}

TEST(test_player_make_trump) {
  Player * bob = Player_factory("Bob", "Simple");
  bob->add_card(Card(NINE, SPADES));
  bob->add_card(Card(TEN, SPADES));
  bob->add_card(Card(QUEEN, DIAMONDS));
  bob->add_card(Card(KING, DIAMONDS));
  bob->add_card(Card(ACE, SPADES));
  Suit up;
  ASSERT_TRUE(bob->make_trump(Card(NINE, DIAMONDS), false, 1, up));
  ASSERT_EQUAL(up, DIAMONDS);
  
  Player * dod = Player_factory("Bob", "Simple");
  dod->add_card(Card(NINE, SPADES));
  dod->add_card(Card(TEN, SPADES));
  dod->add_card(Card(TEN, HEARTS));
  dod->add_card(Card(KING, DIAMONDS));
  dod->add_card(Card(ACE, SPADES));
  Suit up2;
  ASSERT_FALSE(dod->make_trump(Card(NINE, DIAMONDS), false, 2, up2));
  ASSERT_TRUE(dod->make_trump(Card(NINE, DIAMONDS), true, 2, up2));
  ASSERT_EQUAL(up2, HEARTS);
  delete bob;
  delete dod;
}

TEST(test_player_lead_card) {
  // Bob's hand
  Player * bob = Player_factory("Bob", "Simple");
  bob->add_card(Card(NINE, SPADES));
  bob->add_card(Card(TEN, SPADES));
  bob->add_card(Card(QUEEN, SPADES));
  bob->add_card(Card(KING, SPADES));
  bob->add_card(Card(ACE, SPADES));

  // Bob adds a card to his hand and discards one card
  bob->add_and_discard(
    Card(NINE, HEARTS) // upcard
  );

  // Bob leads

  // Verify the card Bob selected to lead
  ASSERT_EQUAL(bob->lead_card(HEARTS), Card(ACE, SPADES)); //check led card


  Player * boba = Player_factory("Bob", "Simple");
  boba->add_card(Card(NINE, SPADES));
  boba->add_card(Card(TEN, SPADES));
  boba->add_card(Card(QUEEN, SPADES));
  boba->add_card(Card(KING, SPADES));
  boba->add_card(Card(ACE, SPADES));
  ASSERT_EQUAL(boba->lead_card(SPADES), Card(ACE, SPADES));
  delete bob;
  delete boba;


}

TEST(test_player_play_card) {
  // Bob's hand
  Player * bob = Player_factory("Bob", "Simple");
  bob->add_card(Card(NINE, SPADES));
  bob->add_card(Card(TEN, SPADES));
  bob->add_card(Card(QUEEN, SPADES));
  bob->add_card(Card(KING, SPADES));
  bob->add_card(Card(ACE, SPADES));

  // Bob plays a card
  Card nine_diamonds(NINE, DIAMONDS);
  Card card_played = bob->play_card(
    nine_diamonds,  // Nine of Diamonds is led
    HEARTS    // Trump suit
  ); 
  ASSERT_EQUAL(card_played, Card(NINE, SPADES));
  Card jack_spades(JACK, SPADES);
  card_played = bob->play_card(jack_spades, HEARTS);
  ASSERT_EQUAL(card_played, Card(ACE, SPADES));
  delete bob;
}


TEST_MAIN()
