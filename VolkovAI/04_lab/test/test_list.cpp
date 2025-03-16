#include <gtest.h>
#include "list.h"

TEST(TListTest, TestIsEmpty) {
    TList<int> list;
    EXPECT_TRUE(list.isEmpty());

    TNode<int>* node = new TNode<int>(10);
    list.push_front(node);
    EXPECT_FALSE(list.isEmpty());
}

TEST(TListTest, TestPushFront) {
    TList<int> list;

    TNode<int>* node1 = new TNode<int>(10);
    list.push_front(node1);
    EXPECT_EQ(list.first_value(), 10);

    TNode<int>* node2 = new TNode<int>(20);
    list.push_front(node2);
    EXPECT_EQ(list.first_value(), 20); 
}

TEST(TListTest, TestPushBack) {
    TList<int> list;

    TNode<int>* node1 = new TNode<int>(10);
    list.push_back(node1);
    EXPECT_EQ(list.first_value(), 10);

    TNode<int>* node2 = new TNode<int>(20);
    list.push_back(node2);
    EXPECT_EQ(list.size(), 2);
}

TEST(TListTest, TestSearch) {
    TList<int> list;

    TNode<int>* node1 = new TNode<int>(10);
    list.push_back(node1);
    TNode<int>* node2 = new TNode<int>(20);
    list.push_back(node2);

    TNode<int>* foundNode = list.search(20);
    EXPECT_EQ(foundNode->value, 20); 

    EXPECT_THROW(list.search(30), const char*);
}

TEST(TListTest, TestInsertBefore) {
    TList<int> list;

    TNode<int>* node1 = new TNode<int>(10);
    list.push_back(node1);
    TNode<int>* node2 = new TNode<int>(20);
    list.push_back(node2);

    TNode<int>* newNode = new TNode<int>(15);
    list.insert_before(newNode, 20);
    EXPECT_EQ(list.size(), 3);
    EXPECT_EQ(list.first_value(), 10);
}

TEST(TListTest, TestInsertAfter) {
    TList<int> list;

    TNode<int>* node1 = new TNode<int>(10);
    list.push_back(node1);
    TNode<int>* node2 = new TNode<int>(20);
    list.push_back(node2);

    TNode<int>* newNode = new TNode<int>(25);
    list.insert_after(newNode, 20);
    EXPECT_EQ(list.size(), 3);
}

TEST(TListTest, TestRemove) {
    TList<int> list;

    TNode<int>* node1 = new TNode<int>(10);
    list.push_back(node1);
    TNode<int>* node2 = new TNode<int>(20);
    list.push_back(node2);

    list.remove(10);
    EXPECT_EQ(list.size(), 1);
    EXPECT_THROW(list.search(10), const char*);
}

TEST(TListTest, TestSize) {
    TList<int> list;

    TNode<int>* node1 = new TNode<int>(10);
    list.push_back(node1);
    EXPECT_EQ(list.size(), 1);

    TNode<int>* node2 = new TNode<int>(20);
    list.push_back(node2);
    EXPECT_EQ(list.size(), 2);
}

TEST(TListTest, TestCopyConstructor) {
    TList<int> list1;
    TNode<int>* node1 = new TNode<int>(10);
    list1.push_back(node1);
    TNode<int>* node2 = new TNode<int>(20);
    list1.push_back(node2);

    TList<int> list2 = list1; 
    EXPECT_EQ(list1.size(), list2.size()); 
    EXPECT_EQ(list1.first_value(), list2.first_value());
}

TEST(TListTest, TestAssignmentOperator) {
    TList<int> list1;
    TNode<int>* node1 = new TNode<int>(10);
    list1.push_back(node1);
    TNode<int>* node2 = new TNode<int>(20);
    list1.push_back(node2);

    TList<int> list2;
    list2 = list1; 
    EXPECT_EQ(list1.size(), list2.size()); 
    EXPECT_EQ(list1.first_value(), list2.first_value()); 
}

TEST(TListTest, TestEqualityOperator) {
    TList<int> list1;
    TNode<int>* node1 = new TNode<int>(10);
    list1.push_back(node1);
    TNode<int>* node2 = new TNode<int>(20);
    list1.push_back(node2);

    TList<int> list2;
    TNode<int>* node3 = new TNode<int>(10);
    list2.push_back(node3);
    TNode<int>* node4 = new TNode<int>(20);
    list2.push_back(node4);

    EXPECT_TRUE(list1 == list2); 

    TList<int> list3;
    TNode<int>* node5 = new TNode<int>(30);
    list3.push_back(node5);

    EXPECT_FALSE(list1 == list3); 
}
