// объявление и реализация шаблонного стека
// стек поддерживает операции:
// - вставка элемента,
// - извлечение элемента,
// - просмотр верхнего элемента (без удаления)
// - проверка на пустоту,
// - получение количества элементов в стеке
// - очистка стека
// при вставке в полный стек должна перевыделяться память
#pragma once
#include <iostream>
#include <cmath>
#include <vector>

using namespace std;

template <class T>
class Stack
{
    vector<T> mem;

public:
    Stack() = default;
    void PushElem(const T &val)
    {
        mem.push_back(val);
    }

    T PopElem()
    {
        if (mem.empty())
        {
            throw runtime_error("stack is empty");
        }
        T a = mem.back();
        mem.pop_back();
        return a;
    }

    T LastElem() const
    {
        if (mem.empty())
        {
            throw runtime_error("Stack is empty");
        }
        return mem.back();
    }

    bool isEmpty() const
    {
        return mem.empty();
    }
    void DeleteStack()
    {
        mem.clear();
    }
    int Size()
    {
        return mem.size();
    }
};