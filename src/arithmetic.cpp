// реализация функций и классов для вычисления арифметических выражений
// #include "arithmetic.h"
// #include <vector>
// #include <iostream>
// #include <algorithm>

// using namespace std;
// int levenshtein_distance(const std::string &s1, const std::string &s2)
// {
//     int m = s1.size();
//     int n = s2.size();

//     vector<vector<int>> d(m + 1, vector<int>(n + 1));

//     for (int i = 0; i <= m; i++)
//         d[i][0] = i;
//     for (int j = 0; j <= n; j++)
//         d[0][j] = j;

//     for (int i = 1; i <= m; i++)
//     {
//         for (int j = 1; j <= n; j++)
//         {
//             if (s1[i - 1] == s2[j - 1])
//             {
//                 d[i][j] = d[i - 1][j - 1];
//             }
//             else
//             {
//                 d[i][j] = 1 + min({d[i - 1][j], d[i][j - 1], d[i - 1][j - 1]});
//             }
//         }
//     }
//     return d[m][n];
// }

// void Arithmetic::ParsLexems(string s)
// {
//     // (1.234+a*3) / 0 + b;
//     string a = "";
//     bool flag_func = false;
//     bool flag = false;
//     for (int i = 0; i < s.size(); i++)
//     {
//         if (flag == true)
//         {
//             if (s[i] != '1' && s[i] != '2' && s[i] != '5' && s[i] != '6' && s[i] != '7' && s[i] != '8' && s[i] != '9' && s[i] != '0' && s[i] != '3' && s[i] != '4')
//             {
//                 lexems.push_back(a);
//                 a = "";
//                 flag = false;
//             }
//         }

//         else
//         {
//             if (flag_func)
//             {
//                 if (s[i] == '(' || s[i] == ')' || s[i] == '*' || s[i] == '+' || s[i] == '-' || s[i] == '/' || s[i] == '^' || s[i] == '0' || s[i] == '1' || s[i] == '2' || s[i] == '3' || s[i] == '4' || s[i] == '5' || s[i] == '6' || s[i] == '7' || s[i] == '8' || s[i] == '9')
//                 {
//                     flag_func = false;
//                     if (levenshtein_distance(a, "sin") <= 1)
//                     {
//                         lexems.push_back("sin");
//                         a = "";
//                     }
//                     else if (levenshtein_distance(a, "cos") <= 1)
//                     {
//                         lexems.push_back("cos");
//                         a = "";
//                     }
//                     else if (levenshtein_distance(a, "ln") <= 1)
//                     {
//                         lexems.push_back("ln");
//                         a = "";
//                     }
//                     else if (levenshtein_distance(a, "tg") <= 1)
//                     {
//                         lexems.push_back("tg");
//                         a = "";
//                     }
//                     else if (levenshtein_distance(a, "ctg") <= 1)
//                     {
//                         lexems.push_back("ctg");
//                         a = "";
//                     }
//                     else if (levenshtein_distance(a, "arcsin") <= 1)
//                     {
//                         lexems.push_back("arcsin");
//                         a = "";
//                     }
//                     else if (levenshtein_distance(a, "arccos") <= 1)
//                     {
//                         lexems.push_back("arccos");
//                         a = "";
//                     }
//                     else
//                     {
//                         string b;
//                         cout << "vvedite znachenie peremennoy: ";
//                         cin >> b;
//                         lexems.push_back(b);
//                         a = "";
//                     }
//                 }
//             }
//             else
//             {
//                 if (s[i] == '(' || s[i] == ')' || s[i] == '*' || s[i] == '+' || s[i] == '-' || s[i] == '/' || s[i] == '^')
//                 {
//                     lexems.push_back(string(1, s[i]));
//                 }
//                 else if (s[i] == '.')
//                 {
//                     flag = true;
//                 }
//                 else if (s[i] != '1' && s[i] != '2' && s[i] != '5' && s[i] != '6' && s[i] != '7' && s[i] != '8' && s[i] != '9' && s[i] != '0' && s[i] != '3' && s[i] != '4')
//                 {
//                     flag_func = true;
//                 }
//             }
//         }

//         a += string(1, s[i]);
//     }
// }
