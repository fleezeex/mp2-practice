#include "list.h"
#include <gtest.h>

TEST(TNodeTest, DefaultConstructorCreatesValidNode) {
    ASSERT_NO_THROW(TNode<int> node);
}

TEST(TNodeTest, ConstructorWithValueInitializesCorrectly) {
    TNode<int> node(5);
    EXPECT_EQ(node.value, 5);
    EXPECT_EQ(node.pNext, nullptr);
}

TEST(TNodeTest, NodeAssignmentWorksCorrectly) {
    TNode<int> node1(3);
    TNode<int> node2(8);
    node1 = node2;
    EXPECT_EQ(node1.value, 8);
}

TEST(TListTest, EmptyListCreation) {
    ASSERT_NO_THROW(TList<int> lst);
}

TEST(TListTest, ListCopyConstructor) {
    TList<int> original;
    TNode<int>* node = new TNode<int>(2);
    original.push_front(node);

    TList<int> copy(original);
    EXPECT_TRUE(original == copy);
}

TEST(TListTest, CopiedListsIndependent) {
    TList<int> first;
    first.push_front(new TNode<int>(3));

    TList<int> second(first);
    second.push_front(new TNode<int>(7));

    EXPECT_FALSE(first == second);
}

TEST(TListTest, FindExistingElement) {
    TList<int> lst;
    lst.push_front(new TNode<int>(4));
    EXPECT_NE(lst.search(4), nullptr);
}

TEST(TListTest, NonExistingElementSearch) {
    TList<int> lst;
    lst.push_front(new TNode<int>(4));
    EXPECT_EQ(lst.search(8), nullptr);
}

TEST(TListTest, FrontInsertion) {
    TList<int> lst;
    ASSERT_NO_THROW(lst.push_front(new TNode<int>(6)));
}

TEST(TListTest, FrontInsertedElementFound) {
    TList<int> lst;
    lst.push_front(new TNode<int>(9));
    EXPECT_EQ(lst.search(9)->value, 9);
}

TEST(TListTest, BackInsertion) {
    TList<int> lst;
    ASSERT_NO_THROW(lst.push_back(new TNode<int>(11)));
}

TEST(TListTest, BackInsertedElementFound) {
    TList<int> lst;
    lst.push_back(new TNode<int>(13));
    EXPECT_EQ(lst.search(13)->value, 13);
}

TEST(TListTest, InsertBeforeExisting) {
    TList<int> lst;
    lst.push_back(new TNode<int>(15));
    ASSERT_NO_THROW(lst.insert_before(new TNode<int>(14), 15));
}

TEST(TListTest, InsertBeforeNonExisting) {
    TList<int> lst;
    lst.push_back(new TNode<int>(16));
    ASSERT_ANY_THROW(lst.insert_before(new TNode<int>(17), 99));
}

TEST(TListTest, InsertAfterExisting) {
    TList<int> lst;
    lst.push_back(new TNode<int>(18));
    ASSERT_NO_THROW(lst.insert_after(new TNode<int>(19), 18));
}

TEST(TListTest, ElementRemoval) {
    TList<int> lst;
    lst.push_back(new TNode<int>(20));
    ASSERT_NO_THROW(lst.remove(20));
}

TEST(TListTest, RemoveNonExisting) {
    TList<int> lst;
    lst.push_back(new TNode<int>(21));
    ASSERT_ANY_THROW(lst.remove(99));
}

TEST(TListTest, ListAssignment) {
    TList<int> first;
    first.push_back(new TNode<int>(22));

    TList<int> second;
    second = first;

    EXPECT_TRUE(first == second);
}

TEST(TListTest, EmptyListSize) {
    TList<int> lst;
    EXPECT_EQ(lst.size(), 0);
}

TEST(TListTest, NonEmptyListSize) {
    TList<int> lst;
    lst.push_back(new TNode<int>(23));
    lst.push_back(new TNode<int>(24));
    EXPECT_EQ(lst.size(), 2);
}

TEST(TListTest, ListIteration) {
    TList<int> lst;
    lst.push_back(new TNode<int>(25));
    lst.push_back(new TNode<int>(26));

    lst.reset();
    EXPECT_EQ(lst.current(), 25);
    lst.next();
    EXPECT_EQ(lst.current(), 26);
    lst.next();
    EXPECT_TRUE(lst.isEnded());
}