#include "Card.hpp"
#include "unit_test_framework.hpp"
#include <iostream>

using namespace std;

TEST(test_card_default) {
    Card c;
    ASSERT_EQUAL(TWO, c.get_rank());
    ASSERT_EQUAL(SPADES, c.get_suit());
}
TEST(test_card_ctor) {
    Card c(ACE, HEARTS);
    ASSERT_EQUAL(ACE, c.get_rank());
    ASSERT_EQUAL(HEARTS, c.get_suit());
}

TEST(test_card_get_rank) {
    Card c(ACE, HEARTS);
    ASSERT_EQUAL(ACE, c.get_rank());
}
TEST(test_card_get_suit) {
    Card c(ACE, HEARTS);
    ASSERT_EQUAL(HEARTS, c.get_suit());
}
TEST(test_card_get_suit_trump) {
    Card c(JACK, HEARTS);
    ASSERT_EQUAL(DIAMONDS, c.get_suit(DIAMONDS));
}
TEST(test_card_is_face_or_ace) {
    Card c(ACE, HEARTS);
    ASSERT_TRUE(c.is_face_or_ace());
     Card d(NINE, HEARTS);
    ASSERT_FALSE(d.is_face_or_ace());
}
TEST(test_card_is_right_bower) {
    Card c(JACK, DIAMONDS);
    ASSERT_TRUE(c.is_right_bower(DIAMONDS));
    Card d (NINE, DIAMONDS);
    ASSERT_FALSE(d.is_right_bower(DIAMONDS));
}
TEST(test_card_is_left_bower) {
    Card c (JACK, HEARTS);
    ASSERT_TRUE(c.is_left_bower(DIAMONDS));
    Card d(JACK, DIAMONDS);
    ASSERT_FALSE(d.is_left_bower(DIAMONDS));
}
TEST(test_card_is_trump) {
    Card c(JACK, HEARTS);
    Card d(NINE, DIAMONDS);
    ASSERT_TRUE(c.is_trump(DIAMONDS));
    ASSERT_TRUE(d.is_trump(DIAMONDS));
    Card e(TEN, CLUBS);
    ASSERT_FALSE(e.is_trump(DIAMONDS));
}
TEST(test_card_os) {
    Card c(JACK, HEARTS);
    ostringstream os;
    os << c;
    ASSERT_EQUAL(os.str(), "Jack of Hearts")
}
TEST(test_card_is) {
    istringstream iss("Three of Spades");
    Card c;
    iss >> c;
    ASSERT_EQUAL(c, Card(THREE, SPADES));
}

TEST(test_card_less) {
    Card a(JACK, HEARTS);
    Card b(JACK, DIAMONDS);
    ASSERT_TRUE(a < b);
}
TEST(test_card_less_equal) {
    Card a(JACK, HEARTS);
    Card b(JACK, DIAMONDS);
    ASSERT_TRUE(a <= b);
    Card c(JACK, HEARTS);
    Card d(JACK, HEARTS);
    ASSERT_TRUE(c <= d);
}
TEST(test_card_greater) {
    Card a(JACK, HEARTS);
    Card b(JACK, DIAMONDS);
    ASSERT_TRUE(b > a);
}
TEST(test_card_greater_equal) {
    Card a(JACK, HEARTS);
    Card b(JACK, DIAMONDS);
    ASSERT_TRUE(b>=a);
    Card c(JACK, HEARTS);
    Card d(JACK, HEARTS);
    ASSERT_TRUE(c >= d);
}
TEST(test_card_equal) {
    Card c(JACK, HEARTS);
    Card d(JACK, HEARTS);
    ASSERT_TRUE(c == d);
}
TEST(test_card_not_equal) {
    Card a(JACK, HEARTS);
    Card b(JACK, DIAMONDS);
    ASSERT_TRUE(b!=a);
}
TEST(test_card_suit_next) {
    ASSERT_EQUAL(Suit_next(DIAMONDS), HEARTS);
    ASSERT_EQUAL(Suit_next(HEARTS), DIAMONDS);
    ASSERT_EQUAL(Suit_next(SPADES), CLUBS);
    ASSERT_EQUAL(Suit_next(CLUBS), SPADES);
}
TEST(test_card_card_less) {
    Card a(JACK, HEARTS);
    Card b(JACK, DIAMONDS);
    ASSERT_TRUE(Card_less(a, b, DIAMONDS));
    ASSERT_TRUE(Card_less(a, b, SPADES));
    Card c(NINE, SPADES);
    Card d(ACE, DIAMONDS);
    ASSERT_FALSE(Card_less(c, d, SPADES));
}
TEST(test_card_card_less_led) {
    Card a(ACE, HEARTS);
    Card b(NINE, DIAMONDS);
    Card led(TEN, DIAMONDS);
    ASSERT_TRUE(Card_less(a, b, led, SPADES));
    ASSERT_FALSE(Card_less(a, b, led, HEARTS));

}


// Add more test cases here

TEST_MAIN()
