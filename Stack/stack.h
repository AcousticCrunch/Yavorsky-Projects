#ifndef ASSIGNMENT3_STACK_H
#define ASSIGNMENT3_STACK_H

#include <iostream>
#include <initializer_list>
#include <vector>


namespace cop4530 {

    //template Stack class (Utilizes STL vector to hold stack data)
    template <typename T, typename Container = std::vector<T> >
    class Stack{

    public:
        // constructors and destructor
        Stack();
        ~Stack();
        Stack (const Stack<T>&);
        Stack(Stack<T> &&);

        // assignment operators
        const Stack<T>& operator=(const Stack <T>&);
        Stack<T> & operator=(Stack<T> &&);

        // member functions
        bool empty() const;
        void clear();           // clears stack
        void push(const T& x);  // copy push (adds element to stack)
        void push(T && x);      // move push
        void pop();             // pop (removes top element)
        T& top();               // returns top element
        const T& top() const;   // returns top element (as const ref)
        int size() const;       // returns size of stack

        //print function
        void print(std::ostream& os, char ofc = ' ') const;


    private:
        Container stack;
        int stackSize;
    };

    // operator overloads
    template<typename T>
    std::ostream& operator<< (std::ostream& os, const Stack<T>& a);

    template<typename T>
    bool operator== (const Stack<T>&, const Stack <T>&);

    template<typename T>
    bool operator!= (const Stack<T>&, const Stack <T>&);

    template<typename T>
    bool operator<= (const Stack<T>& a, const Stack <T>& b);


#include "stack.hpp"

} // end of namespace 4530

#endif //ASSIGNMENT3_STACK_H
