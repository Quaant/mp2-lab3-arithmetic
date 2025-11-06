#include <iostream>
#include <string>
#include <map>
#include <set>
#include <vector>
#include <algorithm>
#include "stack.h"
using namespace std;

set<string> functions = {"sin", "cos", "tg", "ln", "arcsin", "arccos", "ctg"};

struct Lexem
{
    int type;
    // 0 = number, 1 = operand, 2 = function, 3 = variable
    string name;
};

ostream &operator<<(ostream &os, const Lexem &lexem)
{
    os << '(' << lexem.type << '.' << lexem.name << ')';
    return os;
}

ostream &operator<<(ostream &os, const vector<Lexem> &lexems)
{
    for (size_t i = 0; i < lexems.size(); ++i)
    {
        os << lexems[i];
        if (i != lexems.size() - 1)
        {
            os << " ";
        }
    }
    return os;
}

bool isOperator(string s)
{
    return s == "+" || s == "-" || s == "*" ||
           s == "/" || s == "^";
}

bool isFunction(string s)
{
    return functions.find(s) != functions.end();
}

bool isNumber(string s)
{
    if (s.empty())
        return false;

    if (isFunction(s) || isOperator(s) ||
        s == "(" || s == ")")
    {
        return false;
    }

    bool num = false;
    int dot = 0;

    for (char c : s)
    {
        if (isdigit(c))
        {
            num = true;
        }
        else if (c == '.')
        {
            dot++;
            if (dot > 1)
                return false;
        }
        else
        {
            return false;
        }
    }

    return num;
}

double calculateFunction(const string &func, double value)
{
    if (func == "sin")
        return sin(value);
    if (func == "cos")
        return cos(value);
    if (func == "tg")
        return tan(value);
    if (func == "ctg")
        return 1.0 / tan(value);
    if (func == "ln")
        return log(value);
    if (func == "arcsin")
        return asin(value);
    if (func == "arccos")
        return acos(value);
}

double Res(vector<Lexem> postfix, map<string, double> variables = {})
{
    Stack<double> stack;

    for (int i = 0; i < postfix.size(); i++)
    {
        string token = postfix[i].name;

        // Если это число
        if (isNumber(token))
        {
            stack.PushElem(stod(token));
        }
        // Если это переменная
        else if (variables.find(token) != variables.end())
        {
            stack.PushElem(variables[token]);
        }
        // Если это оператор
        else if (isOperator(token))
        {
            if (stack.Size() < 2)
            {
                throw runtime_error("Not enough operands for operator: " + token);
            }

            double right = stack.PopElem();
            double left = stack.PopElem();
            double result;

            if (token == "+")
            {
                result = left + right;
            }
            else if (token == "-")
            {
                result = left - right;
            }
            else if (token == "*")
            {
                result = left * right;
            }
            else if (token == "/")
            {
                if (right == 0)
                {
                    throw runtime_error("Division by zero");
                }
                result = left / right;
            }
            else if (token == "^")
            {
                result = pow(left, right);
            }
            else
            {
                throw runtime_error("Unknown operator: " + token);
            }

            stack.PushElem(result);
        }
        // Если это функция
        else if (isFunction(token))
        {
            if (stack.Size() < 1)
            {
                throw runtime_error("Not enough operands for function: " + token);
            }

            double arg = stack.PopElem();
            double result = calculateFunction(token, arg);
            stack.PushElem(result);
        }
        else
        {
            // Если это неизвестная переменная
            throw runtime_error("Unknown variable or invalid token: " + token);
        }
    }

    if (stack.Size() != 1)
    {
        throw runtime_error("Invalid expression - stack has " + to_string(stack.Size()) + " elements instead of 1");
    }

    return stack.PopElem();
}

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

vector<Lexem> ParsLexems(string s)
{
    vector<Lexem> lexems;
    string a = "";
    bool flag_number = false;
    bool flag_identifier = false;
    int dot_count = 0;

    vector<string> supported_functions = {"sin", "cos", "tg", "ctg", "ln", "arcsin", "arccos"};

    for (int i = 0; i < s.size(); i++)
    {
        if (flag_number && (!isdigit(s[i]) && s[i] != '.'))
        {
            if (dot_count > 1)
            {
                throw runtime_error("Number has more than one decimal point: " + a);
            }

            Lexem lexem;
            lexem.type = 0; // number
            lexem.name = a;
            lexems.push_back(lexem);
            a = "";
            flag_number = false;
            dot_count = 0;
        }

        if (flag_identifier &&
            (s[i] == '(' || s[i] == ')' || s[i] == '*' || s[i] == '+' ||
             s[i] == '-' || s[i] == '/' || s[i] == '^' || isdigit(s[i]) ||
             s[i] == ' ' || s[i] == '.'))
        {
            Lexem lexem;
            bool is_func = false;
            string closest_func = "";
            int min_distance = 1000000;

            for (const auto &func : supported_functions)
            {
                int distance = levenshtein_distance(a, func);
                if (distance <= 1 && distance < min_distance)
                {
                    is_func = true;
                    closest_func = func;
                    min_distance = distance;
                }
            }

            if (is_func)
            {
                lexem.type = 2; // function
                lexem.name = closest_func;
            }
            else
            {
                lexem.type = 3; // variable
                lexem.name = a;
            }
            lexems.push_back(lexem);
            a = "";
            flag_identifier = false;
        }

        if (s[i] == '(' || s[i] == ')' || s[i] == '*' || s[i] == '+' ||
            s[i] == '-' || s[i] == '/' || s[i] == '^')
        {
            Lexem lexem;
            lexem.type = 1; // operand
            lexem.name = string(1, s[i]);
            lexems.push_back(lexem);
        }
        else if (isdigit(s[i]) || s[i] == '.')
        {
            if (!flag_number)
            {
                flag_number = true;
                flag_identifier = false;
                a = "";
                dot_count = 0;
            }

            if (s[i] == '.')
            {
                dot_count++;
                if (dot_count > 1)
                {
                    throw runtime_error("Number cannot have more than one decimal point");
                }
            }

            a += s[i];
        }
        else if (isalpha(s[i]))
        {
            if (!flag_identifier && !flag_number)
            {
                flag_identifier = true;
                a = "";
            }
            a += s[i];
        }
        else if (s[i] != ' ')
        {
            if (flag_number || flag_identifier)
            {
                a += s[i];
            }
        }
    }

    if (!a.empty())
    {
        Lexem lexem;
        if (flag_number)
        {
            if (dot_count > 1)
            {
                throw runtime_error("Number has more than one decimal point: " + a);
            }
            lexem.type = 0; // number
            lexem.name = a;
        }
        else
        {
            bool is_func = false;
            string closest_func = "";
            int min_distance = 1000000;

            for (const auto &func : supported_functions)
            {
                int distance = levenshtein_distance(a, func);
                if (distance <= 1 && distance < min_distance)
                {
                    is_func = true;
                    closest_func = func;
                    min_distance = distance;
                }
            }

            if (is_func)
            {
                lexem.type = 2; // function
                lexem.name = closest_func;
            }
            else
            {
                lexem.type = 3; // variable
                lexem.name = a;
            }
        }
        lexems.push_back(lexem);
    }

    return lexems;
}

map<string, int> priority;

vector<Lexem> toPostfix(vector<Lexem> s)
{
    priority["+"] = 0;
    priority["-"] = 0;
    priority["*"] = 1;
    priority["/"] = 1;
    priority["^"] = 2;
    priority["sin"] = 3;
    priority["cos"] = 3;
    priority["arcsin"] = 3;
    priority["tg"] = 3;
    priority["arccos"] = 3;
    priority["ln"] = 3;
    priority["ctg"] = 3;

    vector<Lexem> postfix;
    Stack<Lexem> stack;

    for (int i = 0; i < s.size(); i++)
    {
        if (s[i].type == 0)
        {
            postfix.push_back(s[i]);
        }
        else if (s[i].type == 3)
        {
            postfix.push_back(s[i]);
        }
        else if (s[i].type == 2)
        {
            stack.PushElem(s[i]);
        }
        else if (s[i].name == "(")
        {
            stack.PushElem(s[i]);
        }
        else if (s[i].name == ")")
        {
            while (!stack.isEmpty() && stack.LastElem().name != "(")
            {
                postfix.push_back(stack.PopElem());
            }
            if (!stack.isEmpty())
            {
                stack.PopElem();
            }
            if (!stack.isEmpty() && stack.LastElem().type == 2)
            {
                postfix.push_back(stack.PopElem());
            }
        }
        else if (s[i].type == 1 && s[i].name != "(" && s[i].name != ")") // operand (only operators)
        {
            while (!stack.isEmpty() &&
                   stack.LastElem().name != "(" &&
                   priority[stack.LastElem().name] >= priority[s[i].name])
            {
                postfix.push_back(stack.LastElem());
                stack.PopElem();
            }
            stack.PushElem(s[i]);
        }
    }
    while (!stack.isEmpty())
    {
        postfix.push_back(stack.PopElem());
    }

    return postfix;
}

void check(vector<Lexem> s)
{
    bool flag = true;
    int open = 0;
    int close = 0;

    for (int i = 0; i < size(s) - 1; i++)
    {
        if (s[i].type == s[i + 1].type)
        {

            if (s[i].type == 0 || s[i].type == 2 || s[i].type == 3)
            {
                throw runtime_error("2 Lexem of same type stand together");
            }

            else
            {

                if (s[i].name == ")" || s[i + 1].name == "(")
                {
                    continue;
                }

                else
                {
                    throw runtime_error("2 Lexem of same type stand together");
                }
            }
        }
        if (s[i].name == "." && s[i + 1].name == ".")
        {
            throw runtime_error("2 '.' stand together");
        }
        if (s[i].type == 1 && s[i].name != "(" && s[i].name != ")")
        {
            if (!isOperator(s[i].name))
            {
                throw runtime_error("unknown operand");
            }
        }
    }
    int k = 0;
    for (int i = 0; i < size(s); i++)
    {
        if (s[i].name == "(")
        {
            k++; // open++;
        }
        else if (s[i].name == ")")
        {
            if (k <= 0)
                throw runtime_error("the number of open brackets is not equal to the number of closed ones"); // close++;
            else
                k--;
        }
    }
    if (k > 0)
    {
        throw runtime_error("the number of open brsckets is not equal to the number of closed ones");
    }
}
map<string, double> readVariables(const vector<Lexem> &postfix)
{
    map<string, double> variables;
    set<string> unique_vars; // уникальные элементы так как можем использовать одну переменную несколько раз
    for (const auto &token : postfix)
    {
        if (token.type != 0 && token.type != 1 && token.type != 2)
        {
            unique_vars.insert(token.name);
        }
    }
    for (const auto &var_name : unique_vars)
    {
        double value;
        cout << "Введите значение переменной '" << var_name << "': ";
        cin >> value;
        variables[var_name] = value;
    }

    return variables;
}
int main()
{
    //(1.234+a*3) / 10 + san(3)
    cout << "CIN: ";

    string str;
    getline(cin, str);

    vector<Lexem> lexems = ParsLexems(str);
    cout << "11111111" << endl;
    check(lexems);
    cout << "22222222" << endl;
    vector<Lexem> a = toPostfix(lexems);
    for (int i = 0; i < size(a); i++)
    {
        cout << a[i] << " ";
    }
    return 0;
}