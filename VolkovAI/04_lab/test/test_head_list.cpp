#include <gtest.h>
#include "head_list.h"

TEST(HeadListTest, DefaultConstructor) {
    HeadList<int> list;
    EXPECT_EQ(list.size(), 0);
    EXPECT_TRUE(list.isEmpty());
    EXPECT_EQ(list.get_pHead()->pNext, nullptr);
}

TEST(HeadListTest, PushFront) {
    HeadList<int> list;
    TNode<int>* node = new TNode<int>(10);
    list.push_front(node);
    EXPECT_EQ(list.size(), 1);
    EXPECT_FALSE(list.isEmpty());
    EXPECT_EQ(list.get_pHead()->pNext, node);
    EXPECT_EQ(node->pNext, nullptr);
}

TEST(HeadListTest, PushBack) {
    HeadList<int> list;
    TNode<int>* node = new TNode<int>(20);
    list.push_back(node);
    EXPECT_EQ(list.size(), 1);
    EXPECT_FALSE(list.isEmpty());
    EXPECT_EQ(list.get_pHead()->pNext, node);
    EXPECT_EQ(node->pNext, nullptr);
}

TEST(HeadListTest, InsertAfter) {
    HeadList<int> list;
    TNode<int>* node1 = new TNode<int>(10);
    list.push_back(node1);
    TNode<int>* node2 = new TNode<int>(20);
    list.insert_after(node2, 10);
    EXPECT_EQ(list.size(), 2);
    EXPECT_EQ(node1->pNext->value, 20);
    EXPECT_EQ(node2->pNext, nullptr);
}


TEST(HeadListTest, InsertBefore) {
    HeadList<int> list;
    TNode<int>* node1 = new TNode<int>(10);
    list.push_back(node1);
    TNode<int>* node2 = new TNode<int>(5);
    list.insert_before(node2, 10);
    EXPECT_EQ(list.size(), 2);
    EXPECT_EQ(list.get_pHead()->pNext->value, 5);
    EXPECT_EQ(node2->pNext, node1);
}


TEST(HeadListTest, Remove) {
    HeadList<int> list;
    TNode<int>* node1 = new TNode<int>(10);
    TNode<int>* node2 = new TNode<int>(20);
    list.push_back(node1);
    list.push_back(node2);
    list.remove(10);
    EXPECT_EQ(list.size(), 1);
    EXPECT_EQ(list.get_pHead()->pNext->value, 20);
    EXPECT_EQ(node2->pNext, nullptr);
}

TEST(HeadListTest, Clear) {
    HeadList<int> list;
    TNode<int>* node1 = new TNode<int>(10);
    TNode<int>* node2 = new TNode<int>(20);
    list.push_back(node1);
    list.push_back(node2);
    list.clear();
    EXPECT_EQ(list.size(), 0);
    EXPECT_TRUE(list.isEmpty());
    EXPECT_EQ(list.get_pHead()->pNext, nullptr);
}

TEST(HeadListTest, AssignmentOperator) {
    HeadList<int> list1;
    TNode<int>* node1 = new TNode<int>(10);
    list1.push_back(node1);

    HeadList<int> list2;
    list2 = list1;
    EXPECT_EQ(list2.size(), 1);
    EXPECT_EQ(list2.get_pHead()->pNext->value, 10);
}

TEST(HeadListTest, EqualityOperator) {
    HeadList<int> list1;
    TNode<int>* node1 = new TNode<int>(10);
    list1.push_back(node1);

    HeadList<int> list2;
    TNode<int>* node2 = new TNode<int>(10);
    list2.push_back(node2);

    EXPECT_TRUE(list1 == list2);
    EXPECT_FALSE(list1 != list2);
}

TEST(HeadListTest, InequalityOperator) {
    HeadList<int> list1;
    TNode<int>* node1 = new TNode<int>(10);
    list1.push_back(node1);

    HeadList<int> list2;
    TNode<int>* node2 = new TNode<int>(20);
    list2.push_back(node2);

    EXPECT_TRUE(list1 != list2);
    EXPECT_FALSE(list1 == list2);
}

TEST(HeadListTest, Destructor) {
    HeadList<int>* list = new HeadList<int>();
    TNode<int>* node1 = new TNode<int>(10);
    TNode<int>* node2 = new TNode<int>(20);
    list->push_back(node1);
    list->push_back(node2);
    delete list;
}
