#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <algorithm>

using namespace std;

vector<string> lexems;

// double Res(vector<string> a)
// {
//     //[12.34, 10, +, 123, 12, 22, *, /]
//     Stack<double> stack;
//     for (int i = 0; i < size(a); i++)
//     {
//         if (a[i] == "+" || a[i] == "-" || a[i] == "*" || a[i] == "*")
//         {
//             double k = stack.PopElem();
//             double l = stack.PopElem();
//             if (a[i] == "+")
//             {
//                 stack.PushElem(k + l);
//             }
//             else if (a[i] == "-")
//             {
//                 stack.PushElem(k - l);
//             }
//             else if (a[i] == "*")
//             {
//                 stack.PushElem(k - l);
//             }
//             else
//             {
//                 if (l == 0)
//                 {
//                     throw "u can take div on zero!";
//                 }
//                 stack.PushElem(k / l);
//             }
//         }
//         else
//         {
//             stack.PushElem(stod(a[i]));
//         }
//     }

//     return stack.PopElem(); // tut neznay pochemu nemogu vizvat funciton LastElem, pishet chto tip vozvrashemiy ne sovpadaet s tipom func.
// }

// реализация функций и классов для вычисления арифметических выражений

int levenshtein_distance(const std::string &s1, const std::string &s2)
{
    int m = s1.size();
    int n = s2.size();

    vector<vector<int>> d(m + 1, vector<int>(n + 1));

    for (int i = 0; i <= m; i++)
        d[i][0] = i;
    for (int j = 0; j <= n; j++)
        d[0][j] = j;

    for (int i = 1; i <= m; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            if (s1[i - 1] == s2[j - 1])
            {
                d[i][j] = d[i - 1][j - 1];
            }
            else
            {
                d[i][j] = 1 + min({d[i - 1][j], d[i][j - 1], d[i - 1][j - 1]});
            }
        }
    }
    return d[m][n];
}

void ParsLexems(string s)
{
    string a = "";
    bool flag_func = false;
    bool flag_number = false;

    for (int i = 0; i < s.size(); i++)
    {
        if (flag_number)
        {
            if (!isdigit(s[i]) && s[i] != '.')
            {
                lexems.push_back(a);
                a = "";
                flag_number = false;
            }
        }

        if (flag_func)
        {
            if (s[i] == '(' || s[i] == ')' || s[i] == '*' || s[i] == '+' || s[i] == '-' || s[i] == '/' || s[i] == '^' || isdigit(s[i]) || s[i] == ' ')
            {
                flag_func = false;

                if (levenshtein_distance(a, "sin") <= 1)
                {
                    lexems.push_back("sin");
                }
                else if (levenshtein_distance(a, "cos") <= 1)
                {
                    lexems.push_back("cos");
                }
                else if (levenshtein_distance(a, "ln") <= 1)
                {
                    lexems.push_back("ln");
                }
                else if (levenshtein_distance(a, "tg") <= 1)
                {
                    lexems.push_back("tg");
                }
                else if (levenshtein_distance(a, "ctg") <= 1)
                {
                    lexems.push_back("ctg");
                }
                else if (levenshtein_distance(a, "arcsin") <= 1)
                {
                    lexems.push_back("arcsin");
                }
                else if (levenshtein_distance(a, "arccos") <= 1)
                {
                    lexems.push_back("arccos");
                }
                else
                {
                    string b;
                    cout << "vvedite znachenie peremennoy '" << a << "': ";
                    cin >> b;
                    lexems.push_back(b);
                }
                a = "";
            }
        }

        if (s[i] == '(' || s[i] == ')' || s[i] == '*' || s[i] == '+' || s[i] == '-' || s[i] == '/' || s[i] == '^')
        {
            lexems.push_back(string(1, s[i]));
        }
        else if (isdigit(s[i]) || s[i] == '.')
        {
            if (!flag_number)
            {
                flag_number = true;
            }
            a += s[i];
        }
        else if (isalpha(s[i]))
        {
            if (!flag_func)
            {
                flag_func = true;
            }
            a += s[i];
        }
        else if (s[i] != ' ')
        {
            a += s[i];
        }
    }

    if (!a.empty())
    {
        if (flag_number)
        {
            lexems.push_back(a);
        }
        else if (flag_func)
        {
            if (levenshtein_distance(a, "sin") <= 1)
                lexems.push_back("sin");
            else if (levenshtein_distance(a, "cos") <= 1)
                lexems.push_back("cos");
            else if (levenshtein_distance(a, "ln") <= 1)
                lexems.push_back("ln");
            else if (levenshtein_distance(a, "tg") <= 1)
                lexems.push_back("tg");
            else if (levenshtein_distance(a, "ctg") <= 1)
                lexems.push_back("ctg");
            else if (levenshtein_distance(a, "arcsin") <= 1)
                lexems.push_back("arcsin");
            else if (levenshtein_distance(a, "arccos") <= 1)
                lexems.push_back("arccos");
            else
            {
                string b;
                cout << "vvedite znachenie peremennoy '" << a << "': ";
                cin >> b;
                lexems.push_back(b);
            }
        }
    }
}

int main()
{
    //(1.234+a*3) / 0 + san(3)
    string str;
    getline(cin, str);
    ParsLexems(str);
    for (int i = 0; i < size(lexems); i++)
    {
        cout << lexems[i] << ", ";
    }
    return 0;
}
