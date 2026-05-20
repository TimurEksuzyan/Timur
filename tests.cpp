#include <gtest/gtest.h>
#include "Stack.h"

TEST(StackTest, DefaultConstructor)
{
    Stack st;
    EXPECT_EQ(st.get_size(), 0);
    EXPECT_TRUE(st.is_empty());
    EXPECT_EQ(st.to_string(), "Empty");
}

TEST(StackTest, InitializerList)
{
    Stack st = {10, 20, 30};
    EXPECT_EQ(st.get_size(), 3);
    EXPECT_EQ(st.peek(), 30); // Верхний элемент списка инициализации
}

TEST(StackTest, CopyLogic)
{
    Stack st1 = {1, 2, 3};
    Stack st2 = st1;
    EXPECT_EQ(st2.to_string(), st1.to_string());

    st2.pop();
    EXPECT_NE(st2.get_size(), st1.get_size()); // Проверка изоляции памяти
}

TEST(StackTest, AssignmentOperator)
{
    Stack st1 = {7, 8, 9};
    Stack st2;
    st2 = st1;
    EXPECT_EQ(st2.to_string(), "7 8 9");
}

TEST(StackTest, PushElements)
{
    Stack st;
    st.push(100);
    EXPECT_EQ(st.to_string(), "100");
    EXPECT_EQ(st.peek(), 100);

    st.push(200);
    EXPECT_EQ(st.to_string(), "100 200");
    EXPECT_EQ(st.peek(), 200);
}

TEST(StackTest, PopElements)
{
    Stack st = {10, 20, 30};
    st.pop();
    EXPECT_EQ(st.to_string(), "10 20");
    EXPECT_EQ(st.peek(), 20);
    EXPECT_EQ(st.get_size(), 2);
}

TEST(StackTest, EmptyStackExceptions)
{
    Stack st;
    EXPECT_THROW(st.peek(), std::out_of_range);
    EXPECT_THROW(st.pop(), std::out_of_range);
}