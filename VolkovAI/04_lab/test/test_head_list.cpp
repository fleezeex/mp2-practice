#include <gtest.h>
#include "head_list.h"

TEST(HeadListTest, DefaultConstructor) {
    HeadList<int> list;
    EXPECT_EQ(list.size(), 0);
    EXPECT_TRUE(list.isEmpty());
}

TEST(HeadListTest, PushFront) {
    HeadList<int> list;
    list.push_front(new TNode<int>(10));
    EXPECT_EQ(list.size(), 1);
    EXPECT_FALSE(list.isEmpty());
}

TEST(HeadListTest, PushBack) {
    HeadList<int> list;
    list.push_back(new TNode<int>(20));
    EXPECT_EQ(list.size(), 1);
    EXPECT_FALSE(list.isEmpty());
}

TEST(HeadListTest, InsertAfter) {
    HeadList<int> list;
    list.push_back(new TNode<int>(10));
    list.insert_after(new TNode<int>(20), 10);
    EXPECT_EQ(list.size(), 2);
}

TEST(HeadListTest, InsertBefore) {
    HeadList<int> list;
    list.push_back(new TNode<int>(10));
    list.insert_before(new TNode<int>(5), 10);
    EXPECT_EQ(list.size(), 2);
}

TEST(HeadListTest, Remove) {
    HeadList<int> list;
    list.push_back(new TNode<int>(10));
    list.push_back(new TNode<int>(20));
    list.remove(10);
    EXPECT_EQ(list.size(), 1);
}

TEST(HeadListTest, Clear) {
    HeadList<int> list;
    list.push_back(new TNode<int>(10));
    list.push_back(new TNode<int>(20));
    list.clear();
    EXPECT_EQ(list.size(), 0);
    EXPECT_TRUE(list.isEmpty());
}

TEST(HeadListTest, AssignmentOperator) {
    HeadList<int> list1;
    list1.push_back(new TNode<int>(10));

    HeadList<int> list2;
    list2 = list1;
    EXPECT_EQ(list2.size(), 1);
}

TEST(HeadListTest, EqualityOperator) {
    HeadList<int> list1;
    list1.push_back(new TNode<int>(10));

    HeadList<int> list2;
    list2.push_back(new TNode<int>(10));

    EXPECT_TRUE(list1 == list2);
    EXPECT_FALSE(list1 != list2);
}

TEST(HeadListTest, InequalityOperator) {
    HeadList<int> list1;
    list1.push_back(new TNode<int>(10));

    HeadList<int> list2;
    list2.push_back(new TNode<int>(20));

    EXPECT_TRUE(list1 != list2);
    EXPECT_FALSE(list1 == list2);
}