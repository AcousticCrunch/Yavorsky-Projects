#include <iostream>
#include <initializer_list>
#include <vector>
#include "stack.h"

// Default Constructor
template<typename T, typename Container>
Stack<T, Container>::Stack() {
    stackSize = 0;
}

// Destructor
template<typename T, typename Container>
Stack<T, Container>::~Stack() {
    clear();
}

// Copy Constructor
template<typename T, typename Container>
Stack<T, Container>::Stack(const Stack<T> &s) {
    stackSize = 0;
    for (int i = 0; i < s.stackSize; i++)
        push(s.stack[i]);
    stackSize = stack.size();

}

// Move Constructor
template<typename T, typename Container>
Stack<T, Container>::Stack(Stack<T> &&s) {
    stack = s.stack;
    stackSize = s.stackSize;
    s.clear();
}

// Assignment Operator Overload
template<typename T, typename Container>
const Stack<T> &Stack<T, Container>::operator=(const Stack<T> &s) {
    if (this != &s)
    {
        Stack stackCopy = s;
        std::swap(*this, stackCopy);
    }
    return *this;
}

// Assignment Move Operator Overload
template<typename T, typename Container>
Stack<T> &Stack<T, Container>::operator=(Stack<T> &&s) {
    std::swap(stack, s.stack);
    std::swap(stackSize, s.stackSize);
    return *this;
}

// Empty Function (Returns true if stack is empty, false otherwise)
template<typename T, typename Container>
bool Stack<T, Container>::empty() const {
    if (stackSize <= 0)
        return true;
    return false;
}

// Clear Function (Uses STL vector function to clear stack)
template<typename T, typename Container>
void Stack<T, Container>::clear() {
    stack.clear();
    stackSize = 0;
}

// Push Function (Copy Version)
template<typename T, typename Container>
void Stack<T, Container>::push(const T &x) {
    stackSize++;
    stack.push_back(x);
}

// Push Function (Move Version)
template<typename T, typename Container>
void Stack<T, Container>::push(T &&x) {
    stackSize++;
    stack.push_back(std::move(x));
}

// Pop Function (Removes top element)
template<typename T, typename Container>
void Stack<T, Container>::pop() {
    stackSize--;
    stack.pop_back();
}

// Top Function (Returns top element)
template<typename T, typename Container>
T &Stack<T, Container>::top() {
    return stack.back();
}

// Top Function (Const Version)
template<typename T, typename Container>
const T &Stack<T, Container>::top() const {
    const std::vector<T>& constStack = stack;
    return constStack.back;
}

// Size Function (Returns size of stack)
template<typename T, typename Container>
int Stack<T, Container>::size() const {
    return stackSize;
}

// Print Function
template<typename T, typename Container>
void Stack<T, Container>::print(std::ostream &os, char ofc) const {

    for (int i = 0; i < stackSize; i++)
        os << stack[i] << ofc;
}

// << Operator Overload
template<typename T>
std::ostream& operator<< (std::ostream& os, const Stack<T>& a)
{
    a.print(os, ' ');
    return os;
}

// == Operator Overload
template<typename T>
bool operator== (const Stack<T>& s1, const Stack <T>& s2)
{
    Stack<T> stackCopy1 = s1;
    Stack<T> stackCopy2 = s2;

    if (stackCopy1.size() < stackCopy2.size() || stackCopy1.size() > stackCopy2.size())
        return false;

    for (int i = 0; i < stackCopy1.size(); i++)
    {
        if (stackCopy1.top() != stackCopy2.top())
            return false;
        stackCopy1.pop();
        stackCopy2.pop();
    }

    return true;
}

// != Operator Overload
template<typename T>
bool operator!= (const Stack<T>& s1, const Stack <T>& s2)
{
    return !(s1.stack == s2.stack);
}

// <= Operator Overload
template<typename T>
bool operator<= (const Stack<T>& a, const Stack <T>& b)
{
    Stack<T> stackCopy1 = a;
    Stack<T> stackCopy2 = b;

    if (stackCopy1.size() > stackCopy2.size())
        return false;

    else
    {
        for (int i = 0; i < stackCopy1.size(); i++)
        {
            if (stackCopy1.top() > stackCopy2.top())
                return false;
            stackCopy1.pop();
            stackCopy2.pop();
        }
    }
    return true;
}