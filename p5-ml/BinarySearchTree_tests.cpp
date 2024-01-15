#include "BinarySearchTree.hpp"
#include "unit_test_framework.hpp"




TEST(test_single_element_tree) {
    BinarySearchTree<int> tree;
    tree.insert(10);
    ASSERT_FALSE(tree.empty());
    ASSERT_EQUAL(tree.size(), 1);
    ASSERT_EQUAL(tree.height(), 1);
    ASSERT_TRUE(tree.check_sorting_invariant());
}

TEST(test_check_invar_basic) {
    BinarySearchTree<char> tree;
    tree.insert('b');
    tree.insert('a');
    tree.insert('c');
    ASSERT_TRUE(tree.check_sorting_invariant());
    char &begin = *tree.begin();
    begin = 'd';
    ASSERT_FALSE(tree.check_sorting_invariant());
    begin = 'a';
    ASSERT_TRUE(tree.check_sorting_invariant());
}

TEST(test_insert_and_find) {
    BinarySearchTree<int> tree;
    ASSERT_TRUE(tree.find(5) == tree.end());
    tree.insert(5);
    ASSERT_TRUE(tree.find(5) != tree.end());
    tree.insert(3);
    tree.insert(7);

    ASSERT_EQUAL(tree.size(), 3);
    ASSERT_TRUE(tree.find(5) != tree.end());
    ASSERT_TRUE(tree.find(3) != tree.end());
    ASSERT_TRUE(tree.find(7) != tree.end());
    ASSERT_TRUE(tree.find(4) == tree.end());
}


TEST(test_tree_height_multiple_elements) {
    BinarySearchTree<int> tree;
    ASSERT_EQUAL(tree.height(), 0);

    tree.insert(5);
    ASSERT_EQUAL(tree.height(), 1);
    tree.insert(3);
    tree.insert(7);
    tree.insert(1);
    tree.insert(4);

    ASSERT_EQUAL(tree.height(), 3);
}


TEST(test_inorder_traversal) {
    BinarySearchTree<int> tree;
    std::stringstream ss;
    tree.traverse_inorder(ss);
    ASSERT_EQUAL(ss.str(), "");
    tree.insert(5);
    std::stringstream ss1;
    tree.traverse_inorder(ss1);
    ASSERT_EQUAL(ss1.str(), "5 ");
    tree.insert(3);
    std::stringstream ss3;
    tree.traverse_inorder(ss3);
    ASSERT_EQUAL(ss3.str(), "3 5 ");
    tree.insert(7);

    std::stringstream ss2;
    tree.traverse_inorder(ss2);
    ASSERT_EQUAL(ss2.str(), "3 5 7 ");
}


TEST(test_preorder_traversal) {
    BinarySearchTree<int> tree;
    std::stringstream ss;
    tree.traverse_preorder(ss);
    ASSERT_EQUAL(ss.str(), "");
    tree.insert(5);
    std::stringstream ss1;
    tree.traverse_preorder(ss1);
    ASSERT_EQUAL(ss1.str(), "5 ");
    tree.insert(3);
    std::stringstream ss3;
    tree.traverse_preorder(ss3);
    ASSERT_EQUAL(ss3.str(), "5 3 ");
    tree.insert(7);

    std::stringstream ss2;
    tree.traverse_preorder(ss2);
    ASSERT_EQUAL(ss2.str(), "5 3 7 ");
}


TEST(test_sorting_invariant) {
    BinarySearchTree<int> tree;
    ASSERT_TRUE(tree.check_sorting_invariant());
    tree.insert(5);
    ASSERT_TRUE(tree.check_sorting_invariant());
    tree.insert(3);
    tree.insert(7);
    ASSERT_TRUE(tree.check_sorting_invariant());
    tree.insert(2);
    tree.insert(4);
    std::stringstream ss;
    tree.traverse_inorder(ss);

    ASSERT_EQUAL(ss.str(), "2 3 4 5 7 ");
    ASSERT_TRUE(tree.check_sorting_invariant());
}


TEST(test_copy_constructor) {
    BinarySearchTree<int> tree;
    BinarySearchTree<int> empty(tree);
    ASSERT_EQUAL(empty.size(), tree.size());
    ASSERT_EQUAL(empty.height(), tree.height());
    ASSERT_EQUAL(empty.size(), 0);
    tree.insert(5);
    tree.insert(3);
    tree.insert(7);

    BinarySearchTree<int> tree_copy(tree);
    ASSERT_EQUAL(tree_copy.size(), tree.size());
    ASSERT_EQUAL(tree_copy.height(), tree.height());
}


TEST(test_assignment_operator) {
    BinarySearchTree<int> tree;
    tree.insert(5);
    tree.insert(3);
    tree.insert(7);

    BinarySearchTree<int> tree_assigned;
    tree_assigned = tree;
    ASSERT_EQUAL(tree_assigned.size(), tree.size());
    ASSERT_EQUAL(tree_assigned.height(), tree.height());
}



TEST(test_empty_tree) {
    BinarySearchTree<int> tree;
    ASSERT_TRUE(tree.empty());
    ASSERT_EQUAL(tree.size(), 0);
    ASSERT_EQUAL(tree.height(), 0);
}


TEST(test_insert_and_size) {
    BinarySearchTree<int> tree;
    tree.insert(5);
    ASSERT_TRUE(*tree.find(5) == 5);
    tree.insert(3);
    tree.insert(7);

    ASSERT_FALSE(tree.empty());
    ASSERT_EQUAL(tree.size(), 3);
}


TEST(test_tree_height) {
    BinarySearchTree<int> tree;
    ASSERT_EQUAL(tree.height(), 0);
    tree.insert(5);
    tree.insert(3);
    ASSERT_EQUAL(tree.height(), 2);
    tree.insert(7);
    ASSERT_EQUAL(tree.height(), 2);
    tree.insert(8);
    ASSERT_EQUAL(tree.height(), 3);
    tree.insert(6);
    ASSERT_EQUAL(tree.height(), 3);
}



TEST(test_find) {
    BinarySearchTree<int> tree;
    ASSERT_TRUE(tree.find(4)== tree.end());
    ASSERT_TRUE(tree.find(5)== tree.end());
    tree.insert(5);
    tree.insert(3);
    tree.insert(7);

    

    ASSERT_TRUE(tree.find(7) != tree.end());
    ASSERT_EQUAL(*tree.find(7), 7);

    
    ASSERT_TRUE(tree.find(4)== tree.end());
}

TEST(test_find_edge_cases) {
    BinarySearchTree<int> tree;
    tree.insert(5);
    tree.insert(3);
    tree.insert(7);

    ASSERT_TRUE(tree.find(0) == tree.end()); 
    ASSERT_TRUE(tree.find(10) == tree.end()); 
    BinarySearchTree<int> empty_tree;
    ASSERT_TRUE(empty_tree.find(5) == empty_tree.end()); 
}

TEST(test_preorder_empty) {
    BinarySearchTree<int> tree;
    std::ostringstream expected;
    std::ostringstream actual;
    tree.traverse_preorder(actual);
    ASSERT_EQUAL(expected.str(), actual.str());
}

TEST(test_complex_tree_structure) {
    BinarySearchTree<int> tree;
    tree.insert(8);
    tree.insert(3);
    tree.insert(10);
    tree.insert(1);
    tree.insert(6);
    tree.insert(4);
    tree.insert(7);
    tree.insert(14);
    tree.insert(13);

    ASSERT_EQUAL(tree.size(), 9);
    ASSERT_TRUE(tree.check_sorting_invariant());

    std::stringstream ss_inorder;
    tree.traverse_inorder(ss_inorder);
    ASSERT_EQUAL(ss_inorder.str(), "1 3 4 6 7 8 10 13 14 ");

    std::stringstream ss_preorder;
    tree.traverse_preorder(ss_preorder);
    ASSERT_EQUAL(ss_preorder.str(), "8 3 1 6 4 7 10 14 13 "); 
}

TEST(test_min_element) {
    BinarySearchTree<int> tree;
    ASSERT_TRUE(tree.min_element() == tree.end());
    tree.insert(5);
    ASSERT_TRUE(*tree.min_element() == 5);
    tree.insert(3);
    tree.insert(7);
    ASSERT_TRUE(*tree.min_element() == 3);
}

TEST(test_max_element) {
    BinarySearchTree<int> tree;
    ASSERT_TRUE(tree.max_element() == tree.end());
    tree.insert(5);
    ASSERT_TRUE(*tree.max_element() == 5);
    tree.insert(3);
    tree.insert(7);
    ASSERT_TRUE(*tree.max_element() == 7);
        BinarySearchTree<int> tree1;
    tree1.insert(1);
    tree1.insert(2);
    tree1.insert(3);
    ASSERT_EQUAL(*tree1.max_element(), 3);
    BinarySearchTree<int> tree2;
    tree2.insert(22);
    ASSERT_EQUAL(*tree2.max_element(), 22);
    tree2 = tree1;
    ASSERT_EQUAL(*tree2.max_element(), 3);
    tree1.insert(4);
    tree1.insert(5);
    ASSERT_EQUAL(*tree1.max_element(), 5);
    ASSERT_EQUAL(*tree2.max_element(), 3);
}

TEST(test_BST_copy_ctor_basic) {
    BinarySearchTree<int> tree1;
    tree1.insert(1);
    tree1.insert(2);
    tree1.insert(3);
    ASSERT_EQUAL(*tree1.max_element(), 3);

    BinarySearchTree<int> tree2(tree1);
    ASSERT_EQUAL(*tree2.max_element(), 3);

    tree1.insert(4);
    tree1.insert(5);
    ASSERT_EQUAL(*tree1.max_element(), 5);
    ASSERT_EQUAL(*tree2.max_element(), 3);
}



TEST(test_min_greater_than) {
    BinarySearchTree<int> tree;
    ASSERT_TRUE(tree.min_greater_than(4) == tree.end());
    tree.insert(5);
    tree.insert(3);
    tree.insert(7);
    ASSERT_TRUE(*tree.min_greater_than(4) == 5);
    ASSERT_TRUE(*tree.min_greater_than(6) == 7);
    ASSERT_TRUE(tree.min_greater_than(8) == tree.end());
}

TEST(test_tree_size) {
    BinarySearchTree<int> tree;
    ASSERT_EQUAL(tree.height(), 0);
    ASSERT_EQUAL(tree.size(), 0);
    tree.insert(5);
    ASSERT_EQUAL(tree.size(), 1);
    tree.insert(3);
    ASSERT_EQUAL(tree.size(), 2);
    tree.insert(7);
    ASSERT_EQUAL(tree.size(), 3);
    tree.insert(8);
    ASSERT_EQUAL(tree.size(), 4);
    tree.insert(6);
    ASSERT_EQUAL(tree.size(), 5);
}

TEST(test_iterator_begin) {
    BinarySearchTree<int> tree;
    BinarySearchTree<int>::Iterator begin = tree.begin();
    ASSERT_TRUE(begin == tree.end());

    ASSERT_TRUE(tree.begin() == tree.end());
    tree.insert(5);
    ASSERT_TRUE(*tree.begin() == 5);
    tree.insert(3);
    ASSERT_TRUE(*tree.begin() == 3);
    tree.insert(6);
    tree.insert(4);
    tree.insert(7);
    tree.insert(14);
    tree.insert(13);
    ASSERT_TRUE(*tree.begin() == 3);
}

TEST(test_prefix_plus) {
    BinarySearchTree<int> tree;
    tree.insert(5);
    tree.insert(3);
    tree.insert(7);
    ASSERT_TRUE(*tree.begin() == 3);
    ASSERT_TRUE(*++tree.begin() == 5);
    tree.insert(9);
    tree.insert(6);
    ASSERT_TRUE(*++++tree.begin() == 6);
    ASSERT_TRUE(*++++++tree.begin() == 7);
    ASSERT_TRUE(*++++++++tree.begin() == 9);
}

TEST(test_iterator_increment_end) {
    BinarySearchTree<int> tree;
    tree.insert(5);
    auto it = tree.begin();
    ++it;
    ASSERT_TRUE(it == tree.end());
}

TEST(test_copy_independence) {
    BinarySearchTree<int> tree;
    tree.insert(2);
    tree.insert(3);
    BinarySearchTree<int> tree_copy(tree);
    tree_copy.insert(4);
    ASSERT_TRUE(tree.find(4) == tree.end()); 
    ASSERT_TRUE(tree_copy.find(4) != tree_copy.end()); 
    tree.insert(10000);
    ASSERT_EQUAL(*tree.find(10000), 10000);
    ASSERT_FALSE(*tree.find(10000) == 1000);
}

TEST(test_large_tree) {
    BinarySearchTree<int> tree;
    for (int i = 0; i < 1000; ++i) {
        tree.insert(i);
    }
    ASSERT_EQUAL(tree.size(), 1000);
    ASSERT_TRUE(tree.check_sorting_invariant());
}

TEST(test_traversal_consistency) {
    BinarySearchTree<int> tree;
    tree.insert(5);
    tree.insert(3);
    tree.insert(7);
    std::stringstream ss1;
    tree.traverse_inorder(ss1);
    ASSERT_EQUAL(ss1.str(), "3 5 7 ");
    tree.insert(6);
    std::stringstream ss2;
    tree.traverse_inorder(ss2);
    ASSERT_EQUAL(ss2.str(), "3 5 6 7 ");
}

TEST(test_iter_end_basic) {
    BinarySearchTree<double> tree;
    ASSERT_TRUE(tree.end() == BinarySearchTree<double>::Iterator());
    tree.insert(5.6);
    ASSERT_TRUE(tree.end() == BinarySearchTree<double>::Iterator());
}


TEST_MAIN()
