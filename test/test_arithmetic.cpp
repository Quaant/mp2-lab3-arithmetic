// ����� ��� ���������� �������������� ���������

#include <gtest.h>
#include "arithmetic.h"

bool sravnenie(const vector<Lexem> &a, const vector<Lexem> &b)
{
    if (size(a) != size(b))
    {
        return false;
    }
    for (int i = 0; i < size(a); i++)
    {
        if (a[i].type != b[i].type || a[i].name != b[i].name)
        {
            return false;
        }
    }
    return true;
}

TEST(Arithmetic, simple_task)
{
    Arithmetic s1("2 + 3");
    Arithmetic s2("2 ^ 4");
    Arithmetic s3("2 / 2");
    Arithmetic s4("2 - 2");
    EXPECT_EQ(s1.GetRes(), 5.0);
    EXPECT_EQ(s2.GetRes(), 16.0);
    EXPECT_EQ(s3.GetRes(), 1.0);
    EXPECT_EQ(s4.GetRes(), 0);
}

TEST(Arithmetic, simple_task_with_funcion)
{
    Arithmetic s1("cos(0)");
    Arithmetic s2("sin(0)");
    Arithmetic s4("tg(0)");
    EXPECT_EQ(s1.GetRes(), 1.0);
    EXPECT_EQ(s2.GetRes(), 0);
    EXPECT_EQ(s4.GetRes(), 0);
}

TEST(Arithmetic, checking_check_function)
{
    EXPECT_ANY_THROW(Arithmetic s("123..123"));            // dve tochki
    EXPECT_ANY_THROW(Arithmetic s("123 + + 12"));          // dve operation
    EXPECT_ANY_THROW(Arithmetic s("(12 + 3 - (21 + 24)")); // poteryal skobku
}

TEST(Arithmetic, checking_ParsLexems)
{
    Arithmetic s("(1.234+a*3) / 10 + san(3)");
    vector<Lexem> tmp;
    Lexem a;
    a.type = 1;
    a.name = "(";
    tmp.push_back(a);
    a.type = 0;
    a.name = "1.234";
    tmp.push_back(a);
    a.type = 1;
    a.name = "+";
    tmp.push_back(a);
    a.type = 3;
    a.name = "a";
    tmp.push_back(a);
    a.type = 1;
    a.name = "*";
    tmp.push_back(a);
    a.type = 0;
    a.name = "3";
    tmp.push_back(a);
    a.type = 1;
    a.name = ")";
    tmp.push_back(a);
    a.type = 1;
    a.name = "/";
    tmp.push_back(a);
    a.type = 0;
    a.name = "10";
    tmp.push_back(a);
    a.type = 1;
    a.name = "+";
    tmp.push_back(a);
    a.type = 2;
    a.name = "sin";
    tmp.push_back(a);
    a.type = 1;
    a.name = "(";
    tmp.push_back(a);

    a.type = 0;
    a.name = "3";
    tmp.push_back(a);
    a.type = 1;
    a.name = ")";
    tmp.push_back(a);
    bool afk = sravnenie(tmp, s.GetLexems());
    EXPECT_EQ(afk, true);
}
TEST(Arithmetic, checking_toPostfix)
{
    Arithmetic s("(1.234+a*3) / 10 + san(3)");
    vector<Lexem> tmp;
    Lexem a;
    a.type = 0;
    a.name = "1.234";
    tmp.push_back(a);
    a.type = 3;
    a.name = "a";
    tmp.push_back(a);
    a.type = 0;
    a.name = "3";
    tmp.push_back(a);
    a.type = 1;
    a.name = "*";
    tmp.push_back(a);
    a.type = 1;
    a.name = "+";
    tmp.push_back(a);
    a.type = 0;
    a.name = "10";
    tmp.push_back(a);
    a.type = 1;
    a.name = "/";
    tmp.push_back(a);
    a.type = 0;
    a.name = "3";
    tmp.push_back(a);
    a.type = 2;
    a.name = "sin";
    tmp.push_back(a);
    a.type = 1;
    a.name = "+";
    tmp.push_back(a);
    bool afk = sravnenie(tmp, s.GetPostfix());
    EXPECT_EQ(afk, true);
}