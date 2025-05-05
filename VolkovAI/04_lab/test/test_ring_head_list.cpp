#include <gtest.h>
#include "ring_head_list.h"

TEST(RingHeadListTest, DefaultConstructor) {
    RingHeadList<int> list;
    EXPECT_EQ(list.size(), 0);
    EXPECT_TRUE(list.isEmpty());
}

TEST(RingHeadListTest, SingleElementConstructor) {
    RingHeadList<int> list(42);
    EXPECT_EQ(list.size(), 1);
    EXPECT_FALSE(list.isEmpty());
}

TEST(RingHeadListTest, CopyConstructor) {
    RingHeadList<int> list1;
    list1.push_back(1);
    list1.push_back(2);

    RingHeadList<int> list2(list1);
    EXPECT_EQ(list2.size(), 2);
    EXPECT_EQ(list1, list2);
}

TEST(RingHeadListTest, AssignmentOperator) {
    RingHeadList<int> list1;
    list1.push_back(1);
    list1.push_back(2);

    RingHeadList<int> list2;
    list2 = list1;
    EXPECT_EQ(list2.size(), 2);
    EXPECT_EQ(list1, list2);
}

TEST(RingHeadListTest, InsertOperations) {
    RingHeadList<int> list;
    list.push_back(1);
    list.push_back(3);

    // Find node with value 1
    list.reset();
    while (!list.isEnded() && list.current() != 1) {
        list.next();
    }
    if (!list.isEnded()) {
        TNode<int>* node = new TNode<int>(2);
        list.insert_after(node, list.current());
    }
    EXPECT_EQ(list.size(), 3);

    // Find node with value 3
    list.reset();
    while (!list.isEnded() && list.current() != 3) {
        list.next();
    }
    if (!list.isEnded()) {
        TNode<int>* node = new TNode<int>(2);
        list.insert_before(node, list.current());
    }
    EXPECT_EQ(list.size(), 4);
}

TEST(RingHeadListTest, Remove) {
    RingHeadList<int> list;
    list.push_back(1);
    list.push_back(2);
    list.push_back(3);

    list.remove(2);
    EXPECT_EQ(list.size(), 2);
}

TEST(RingHeadListTest, Clear) {
    RingHeadList<int> list;
    list.push_back(1);
    list.push_back(2);
    list.push_back(3);

    list.clear();
    EXPECT_EQ(list.size(), 0);
    EXPECT_TRUE(list.isEmpty());
}

TEST(RingHeadListTest, Size) {
    RingHeadList<int> list;
    EXPECT_EQ(list.size(), 0);

    list.push_back(1);
    list.push_back(2);
    EXPECT_EQ(list.size(), 2);
}

TEST(RingHeadListTest, EqualityOperators) {
    RingHeadList<int> list1;
    list1.push_back(1);
    list1.push_back(2);

    RingHeadList<int> list2;
    list2.push_back(1);
    list2.push_back(2);

    RingHeadList<int> list3;
    list3.push_back(3);
    list3.push_back(4);

    EXPECT_TRUE(list1 == list2);
    EXPECT_TRUE(list1 != list3);
}

TEST(RingHeadListTest, PushNullptrException) {
    RingHeadList<int> list;
    EXPECT_ANY_THROW(list.push_front(nullptr));
    EXPECT_ANY_THROW(list.push_back(nullptr));
}
