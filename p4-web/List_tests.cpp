#include "List.hpp"
#include "unit_test_framework.hpp"

using namespace std;

// Add your test cases here

TEST(test_stub) {
    // Add test code here
    ASSERT_TRUE(true);
}

TEST(test_default_ctor) {
    List<int> empty_list;
    ASSERT_TRUE(empty_list.empty());
}

//TEST(test_dtor)

TEST(test_ctor) {
    List<int> a;
    a.push_back(1);
    a.push_back(2);
    a.push_back(3);
    List<int> b(a);
    List<int>::Iterator ia;
    List<int>::Iterator ib;
    ASSERT_EQUAL(a.size(), b.size());
    ia = a.begin();
    ib = b.begin();
    while (ia != a.end() && ib != b.end()) {
        ASSERT_EQUAL(*ia, *ib);
        ++ia;
        ++ib;
    }
}

TEST(test_assign) {
    List<int> a;
    a.push_back(1);
    a.push_back(2);
    a.push_back(3);
    List<int> b;
    b = a;
    List<int>::Iterator ia;
    List<int>::Iterator ib;
    ASSERT_EQUAL(a.size(), b.size());
    ia = a.begin();
    ib = b.begin();
    while (ia != a.end() && ib != b.end()) {
        ASSERT_EQUAL(*ia, *ib);
        ++ia;
        ++ib;
    }
}

TEST(test_empty) {
    List<int> empty_list;
    empty_list.push_back(1);
    empty_list.clear();
    ASSERT_TRUE(empty_list.empty());
}

TEST(test_size) {
    List<int> a;
    ASSERT_EQUAL(a.size() , 0);
    a.push_back(1);
    ASSERT_EQUAL(a.size() , 1);
    a.push_back(2);
    ASSERT_EQUAL(a.size() , 2);
}

TEST(test_front) {
    List<int> a;
    a.push_back(1);
    a.push_back(2);
    a.push_back(3);
    ASSERT_EQUAL(a.front(), 1);
    a.clear();
    a.push_back(1);
    ASSERT_EQUAL(a.front(), 1);
}

TEST(test_back) {
    List<int> a;
    a.push_back(1);
    a.push_back(2);
    a.push_back(3);
    ASSERT_EQUAL(a.back(), 3);
    a.clear();
    a.push_back(1);
    ASSERT_EQUAL(a.back(), 1);
}

TEST(test_push_front) {
    List<int> a;
    a.push_front(1);
    ASSERT_EQUAL(a.front(), 1);
    a.push_front(2);
    ASSERT_EQUAL(a.front(), 2);
    ASSERT_EQUAL(a.back(), 1);
}

TEST(test_push_back) {
    List<int> a;
    a.push_back(1);
    ASSERT_EQUAL(a.back(), 1);
    a.push_back(2);
    ASSERT_EQUAL(a.back(), 2);
    ASSERT_EQUAL(a.front(), 1);
}

TEST(test_pop_front) {
    List<int> a;
    a.push_back(3);
    a.pop_front();
    ASSERT_TRUE(a.empty());
    a.push_back(1);
    a.push_back(2);
    a.push_back(3);
    a.pop_front();
    ASSERT_EQUAL(a.front(), 2);
}

TEST(test_pop_back) {
    List<int> a;
    a.push_back(3);
    a.pop_back();
    ASSERT_TRUE(a.empty());
    a.push_back(1);
    a.push_back(2);
    a.push_back(3);
    a.pop_back();
    ASSERT_EQUAL(a.back(), 2);
}

TEST(test_clear) {
    List<int> a;
    a.push_back(1);
    a.push_back(2);
    a.push_back(3);
    a.clear();
    ASSERT_TRUE(a.empty());
    ASSERT_EQUAL(a.size(), 0);
}

TEST(test_begin) {
    List<int> a;
    a.push_front(1);
    List<int>:: Iterator it;
    it = a.begin();
    ASSERT_TRUE(a.begin() != a.end());
    ASSERT_EQUAL(*it, 1);
    a.push_front(2);
    a.push_front(3);
    it = a.begin();
    ASSERT_TRUE(a.begin() != a.end());
    ASSERT_EQUAL(*it, 3);
    a.pop_back();
    a.pop_back();
    a.pop_back();
    ASSERT_TRUE(a.begin() == a.end());
}

TEST(test_end) {
    List<int> a;
    List<int>:: Iterator it;
    ASSERT_TRUE(it == a.end());
    a.push_back(1);
    ASSERT_TRUE(it == a.end());
    a.pop_back();
    ASSERT_TRUE(a.begin() == a.end());
}

TEST(test_erase) {
    List<int> a;
    a.push_back(1);
    a.push_back(2);
    a.push_back(3);
    List<int>:: Iterator it;
    it = a.begin();
    a.erase(it);
    ASSERT_EQUAL(a.front(), 2);
    it = a.begin();
    ++it;
    a.erase(it);
    ASSERT_EQUAL(a.back(), 2);
}

TEST(test_insert) {
    List<int> a;
    a.push_back(1);
    a.push_back(2);
    List<int>:: Iterator it;
    it = a.begin();
    a.insert(it, 5);
    ASSERT_EQUAL(a.front(), 5);
    it = a.end();
    a.insert(it, 6);
    ASSERT_EQUAL(a.back(), 6);
}

TEST(test_iterator_default_ctor) {
    List<int> a;
    a.push_back(1);
    a.push_back(2);
    a.push_back(3);
    List<int>:: Iterator it;
    ASSERT_TRUE(it == a.end());
}

TEST(test_Iterator_add) {
    List<int> a;
    a.push_back(1);
    a.push_back(2);
    a.push_back(3);
    List<int>:: Iterator it;
    it = a.begin();
    ++it;
    ASSERT_EQUAL(*it, 2);
    ++it;
    ASSERT_EQUAL(*it, 3);
    ++it;
    ASSERT_TRUE(it == a.end());
}

TEST(test_iterator_deference) {
    List<int> a;
    a.push_back(1);
    a.push_back(2);
    a.push_back(3);
    List<int>:: Iterator it;
    it = a.begin();
    ASSERT_EQUAL(*it, 1);
    ++it;
    ASSERT_EQUAL(*it, 2);
}

TEST(test_iterator_equal) {
    List<int> a;
    a.push_back(1);
    a.push_back(2);
    a.push_back(3);
    List<int>:: Iterator first;
    List<int>:: Iterator second;
    first = a.begin();
    second = a.begin();
    ASSERT_TRUE(first==second);
}

TEST(test_iterator_not_equal) {
    List<int> a;
    a.push_back(1);
    a.push_back(2);
    a.push_back(3);
    List<int>:: Iterator first;
    List<int>:: Iterator second;
    first = a.begin();
    second = a.begin();
    ++second;
    ASSERT_TRUE(first!=second);
}

TEST(test_copy_ctor_empty) {
    List<int> empty_list;
    List<int> copied_list(empty_list);
    ASSERT_TRUE(copied_list.empty());
}

TEST(test_assign_empty) {
    List<int> empty_list;
    List<int> another_list;
    another_list = empty_list;
    ASSERT_TRUE(another_list.empty());
}

TEST(test_self_assign) {
    List<int> a;
    a.push_back(1);
    a = a;
    ASSERT_EQUAL(a.size(), 1);
    ASSERT_EQUAL(a.front(), 1);
}

TEST(test_dtor) {
    List<int>* dynamic_list = new List<int>();
    dynamic_list->push_back(1);
    delete dynamic_list;
    ASSERT_TRUE(true);
}

TEST(test_push_pop_multiple) {
    List<int> a;
    a.push_front(1);
    a.push_back(2);
    a.pop_front();
    a.pop_back();
    ASSERT_TRUE(a.empty());
}

TEST(test_erase_insert_boundary) {
    List<int> a;
    a.push_back(1);
    a.push_back(2);
    a.push_back(3);
    a.insert(a.begin(), 0);
    ASSERT_EQUAL(a.front(), 0);
    List<int>:: Iterator it;
    it = a.begin();
    ++it;
    ++it;
    ++it;
    a.erase(it);
    ASSERT_EQUAL(a.back(), 2);
}



TEST(test_large_list_operations) {
    List<int> large_list;
    const int LARGE_SIZE = 1000000;

    for (int i = 0; i < LARGE_SIZE; ++i) {
        large_list.push_back(i);
    }

    ASSERT_EQUAL(large_list.size(), LARGE_SIZE);
}

TEST_MAIN()
