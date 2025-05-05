#include <gtest.h>
#include "list.h"

TEST(TListTest, TestIsEmpty) {
    TList<int> list;
    EXPECT_TRUE(list.isEmpty());

    list.push_front(new TNode<int>(10));
    EXPECT_FALSE(list.isEmpty());
}

TEST(TListTest, TestPushFront) {
    TList<int> list;

    list.push_front(new TNode<int>(10));
    list.reset();
    EXPECT_EQ(list.current(), 10);

    list.push_front(new TNode<int>(20));
    list.reset();
    EXPECT_EQ(list.current(), 20);
}

TEST(TListTest, TestPushBack) {
    TList<int> list;

    list.push_back(new TNode<int>(10));
    list.reset();
    EXPECT_EQ(list.current(), 10);

    list.push_back(new TNode<int>(20));
    EXPECT_EQ(list.size(), 2);
}

TEST(TListTest, TestSearch) {
    TList<int> list;

    list.push_back(new TNode<int>(10));
    list.push_back(new TNode<int>(20));

    TNode<int>* foundNode = list.search(20);
    EXPECT_NE(foundNode, nullptr);
    if (foundNode) {
        EXPECT_EQ(foundNode->value, 20);
    }

    EXPECT_EQ(list.search(30), nullptr);
}

TEST(TListTest, TestInsertBefore) {
    TList<int> list;

    list.push_back(new TNode<int>(10));
    list.push_back(new TNode<int>(20));

    list.insert_before(new TNode<int>(15), 20);
    EXPECT_EQ(list.size(), 3);
    list.reset();
    EXPECT_EQ(list.current(), 10);
    list.next();
    EXPECT_EQ(list.current(), 15);
}

TEST(TListTest, TestInsertAfter) {
    TList<int> list;

    list.push_back(new TNode<int>(10));
    list.push_back(new TNode<int>(20));

    list.insert_after(new TNode<int>(25), 20);
    EXPECT_EQ(list.size(), 3);
}

TEST(TListTest, TestRemove) {
    TList<int> list;

    list.push_back(new TNode<int>(10));
    list.push_back(new TNode<int>(20));

    list.remove(10);
    EXPECT_EQ(list.size(), 1);
    list.reset();
    EXPECT_EQ(list.current(), 20);
}

TEST(TListTest, TestSize) {
    TList<int> list;

    list.push_back(new TNode<int>(10));
    EXPECT_EQ(list.size(), 1);

    list.push_back(new TNode<int>(20));
    EXPECT_EQ(list.size(), 2);
}

TEST(TListTest, TestCopyConstructor) {
    TList<int> list1;
    list1.push_back(new TNode<int>(10));
    list1.push_back(new TNode<int>(20));

    TList<int> list2 = list1;
    EXPECT_EQ(list1.size(), list2.size());
    list2.reset();
    EXPECT_EQ(list2.current(), 10);
}

TEST(TListTest, TestAssignmentOperator) {
    TList<int> list1;
    list1.push_back(new TNode<int>(10));
    list1.push_back(new TNode<int>(20));

    TList<int> list2;
    list2 = list1;
    EXPECT_EQ(list1.size(), list2.size());
    list2.reset();
    EXPECT_EQ(list2.current(), 10);
}

TEST(TListTest, TestEqualityOperator) {
    TList<int> list1;
    list1.push_back(new TNode<int>(10));
    list1.push_back(new TNode<int>(20));

    TList<int> list2;
    list2.push_back(new TNode<int>(10));
    list2.push_back(new TNode<int>(20));

    EXPECT_TRUE(list1 == list2);

    TList<int> list3;
    list3.push_back(new TNode<int>(30));

    EXPECT_FALSE(list1 == list3);
}