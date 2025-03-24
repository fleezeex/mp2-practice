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

TEST(RingHeadListTest, InsertAfter) {
    RingHeadList<int> list;
    list.push_back(1);
    list.push_back(3);

    auto node = list.get_pHead()->pNext;
    list.insert_after(node, 2);

    EXPECT_EQ(list.size(), 3);
    EXPECT_EQ(list.get_pHead()->pNext->value, 1);
    EXPECT_EQ(list.get_pHead()->pNext->pNext->value, 2);
    EXPECT_EQ(list.get_pHead()->pNext->pNext->pNext->value, 3);
}

TEST(RingHeadListTest, InsertBefore) {
    RingHeadList<int> list;
    list.push_back(1);
    list.push_back(3);

    auto node = list.get_pHead()->pNext->pNext; 
    list.insert_before(node, 2);

    EXPECT_EQ(list.size(), 3);
    EXPECT_EQ(list.get_pHead()->pNext->value, 1);
    EXPECT_EQ(list.get_pHead()->pNext->pNext->value, 2);
    EXPECT_EQ(list.get_pHead()->pNext->pNext->pNext->value, 3);
}

TEST(RingHeadListTest, Remove) {
    RingHeadList<int> list;
    list.push_back(1);
    list.push_back(2);
    list.push_back(3);

    list.remove(2);
    EXPECT_EQ(list.size(), 2);
    EXPECT_EQ(list.get_pHead()->pNext->value, 1);
    EXPECT_EQ(list.get_pHead()->pNext->pNext->value, 3);
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

TEST(RingHeadListTest, EqualityOperator) {
    RingHeadList<int> list1;
    list1.push_back(1);
    list1.push_back(2);

    RingHeadList<int> list2;
    list2.push_back(1);
    list2.push_back(2);

    EXPECT_TRUE(list1 == list2);
}

TEST(RingHeadListTest, InequalityOperator) {
    RingHeadList<int> list1;
    list1.push_back(1);
    list1.push_back(2);

    RingHeadList<int> list2;
    list2.push_back(3);
    list2.push_back(4);

    EXPECT_TRUE(list1 != list2);
}

TEST(RingHeadListTest, RingStructure) {
    RingHeadList<int> list;
    list.push_back(1);
    list.push_back(2);
    list.push_back(3);

    auto lastNode = list.get_pHead()->pNext->pNext->pNext; 
    EXPECT_EQ(lastNode->pNext, list.get_pHead());
}

TEST(RingHeadListTest, PushNullptrException) {
    RingHeadList<int> list;
    EXPECT_ANY_THROW(list.push_front(nullptr));
    EXPECT_ANY_THROW(list.push_back(nullptr));
}

TEST(RingHeadListTest, InsertAfterNullptrException) {
    RingHeadList<int> list;
    EXPECT_ANY_THROW(list.insert_after(nullptr, 1));
}

TEST(RingHeadListTest, InsertBeforeNullptrException) {
    RingHeadList<int> list;
    EXPECT_ANY_THROW(list.insert_before(nullptr, 1));
}

TEST(RingHeadListTest, PushFrontBackEmptyList) {
    RingHeadList<int> list;
    list.push_front(1);
    EXPECT_EQ(list.size(), 1);


    list.push_back(2);
    EXPECT_EQ(list.size(), 2);
}

TEST(RingHeadListTest, RemoveFromEmptyList) {
    RingHeadList<int> list;
    list.remove(1);
    EXPECT_EQ(list.size(), 0);
}

TEST(RingHeadListTest, RemoveNonExistentElement) {
    RingHeadList<int> list;
    list.push_back(1);
    list.push_back(2);

    list.remove(3); 
    EXPECT_EQ(list.size(), 2);
}

TEST(RingHeadListTest, ClearEmptyList) {
    RingHeadList<int> list;
    list.clear();
    EXPECT_EQ(list.size(), 0);
}