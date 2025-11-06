// объявление функций и классов для вычисления арифметических выражений

#include "stack.h"
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <set>

using namespace std;

struct Lexem
{
    int type;
    // 0 = number, 1 = operand, 2 = function, 3 = variable
    string name;

    bool operator==(const Lexem &a)
    {
        return type == a.type && name == a.name;
    }
};

class Arithmetic
{
private:
    string infix;
    vector<Lexem> postfix;
    vector<Lexem> lexems;
    map<string, int> priority;
    map<string, double> variables;
    double res;

public:
    Arithmetic();
    Arithmetic(string a);
    bool operator==(const Arithmetic &a)
    {
        if (infix == a.infix && res == a.res)
        {
            return true;
        }
        return false;
    };
    void ParsLexems(string s);
    void toPostfix(vector<Lexem> s);
    void check(vector<Lexem> s);
    void readVariables(const vector<Lexem> &postfix);
    void Res(vector<Lexem> postfix, map<string, double> variables = {});
    string GetInfix();
    vector<Lexem> GetPostfix();
    double GetRes();
    vector<Lexem> GetLexems();
};