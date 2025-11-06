// ����� ��� �����

#include "stack.h"
#include <gtest.h>

TEST(Stack, can_make_stack)
{
    ASSERT_NO_THROW(Stack<int> a());
}
TEST(Stack, can_get_last_elem_and_pop_elem)
{
    Stack<int> a;
    EXPECT_NO_THROW(a.PushElem(1));
    EXPECT_EQ(a.LastElem(), 1);
    EXPECT_NO_THROW(a.PopElem());
    EXPECT_EQ(a.Size(), 0);
}

TEST(Stack, can_work_pop_elem_and_empty)
{
    Stack<int> a;
    EXPECT_NO_THROW(a.PushElem(1));
    EXPECT_EQ(a.PopElem(), 1);
    EXPECT_EQ(a.Size(), 0);
    EXPECT_EQ(a.isEmpty(), true); 
}
