#include <iostream>
#include <initializer_list>
#include "List.h"

// const_iterator Default Constructor
template<typename T>
List<T>::const_iterator::const_iterator(): current{nullptr} {};

// const_iterator Multiply Operator Overload
template<typename T>
const T& List<T>::const_iterator::operator*() const
{return retrieve();}

// const_iterator Increment Pre-Fix Operator Overload
template<typename T>
typename List<T>::const_iterator& List<T>::const_iterator::operator++(){
    current = current->next;
    return *this;
}

// const_iterator Increment Post-Fix Operator Overload
template<typename T>
typename List<T>::const_iterator List<T>::const_iterator::operator++(int){
    const_iterator old = *this;
    ++(*this);
    return old;
}

// const_iterator Decrement Pre-Fix Operator Overload
template<typename T>
typename List<T>::const_iterator& List<T>::const_iterator::operator--(){
    current = current->prev;
    return *this;
}

// const_iterator Decrement Post-Fix Operator Overload
template<typename T>
typename List<T>::const_iterator List<T>::const_iterator::operator--(int){
    const_iterator old = *this;
    --(*this);
    return old;
}

// const_iterator Comparison Operators
template<typename T>
bool List<T>::const_iterator::operator==(const const_iterator &rhs) const{
    if (current == rhs.current)
        return true;
    return false;
}

template<typename T>
bool List<T>::const_iterator:: operator!=(const const_iterator &rhs) const{
    if (current != rhs.current)
        return true;
    return false;
}

// const_iterator Retrieve Data Function
template<typename T>
T& List<T>::const_iterator::retrieve() const{
    return current->data;
}

// const_iterator One Parameter Constructor
template<typename T>
List<T>::const_iterator::const_iterator(Node *p):current{p}{}

/*-----------------------------------------------------*/

// iterator Default Constructor
template<typename T>
List<T>::iterator::iterator() {}

// iterator Pointer De-Reference Operator Overload
template<typename T>
T& List<T>::iterator::operator*(){
    return const_iterator::retrieve();
}

// Constant iterator Pointer De-Reference Operator Overload
template<typename T>
const T& List<T>::iterator::operator*() const
{return const_iterator::operator*();}

// iterator Increment Pre-Fix Operator Overload
template<typename T>
typename List<T>::iterator& List<T>::iterator::operator++(){
    this->current = this->current->next;
    return *this;
}

// iterator Increment Post-Fix Operator Overload
template<typename T>
typename List<T>::iterator List<T>::iterator::operator++(int){
    iterator old = *this;
    ++(*this);
    return old;
}

// iterator Decrement Pre-Fix Operator Overload
template<typename T>
typename List<T>::iterator& List<T>::iterator::operator--(){
    this->current = this->current->prev;
    return *this;
}

// iterator Decrement Post-Fix Operator Overload
template<typename T>
typename List<T>::iterator List<T>::iterator::operator--(int){
    iterator old = *this;
    --(*this);
    return old;
}

// iterator One Parameter Constructor
template<typename T>
List<T>::iterator::iterator(Node *p): const_iterator{p} {}

/*------------------------------------------------------*/

// List Default Constructor
template<typename T>
List<T>::List()
{init();}

// List Copy Constructor
template<typename T>
List<T>::List(const List &rhs){
    init();
    for (int i = 0; i < rhs.theSize; i++)
        push_back(rhs);
}

// List Move Constructor
template<typename T>
List<T>::List(List && rhs){
    head = rhs.head;
    tail = rhs.tail;
    theSize = rhs.theSize;

    rhs.theSize = 0;
    rhs.head = nullptr;
    rhs.tail = nullptr;
}

// List "# of Specified Value" Constructor
template<typename T>
List<T>::List(int num, const T& val){
    init();
    for (int i = 0; i < num; i++)
        push_back(val);
}

// List "From input List's x to y" Constructor
template<typename T>
List<T>::List(const_iterator start, const_iterator end){
    init();
    while (start != end)
    {
        push_back(start.current->data);
        start++;
    }
}

// List Initializer List Constructor
template<typename T>
List<T>::List (std::initializer_list<T> iList){
    init();
    auto itr = iList.begin();
    for (auto i: iList)
        push_back(*itr++);
}

// List Destructor
template<typename T>
List<T>::~List(){
    clear();
    delete head;
    delete tail;
}

// List Copy Assignment Operator
template<typename T>
const List<T>& List<T>::operator=(const List &rhs){
    List listCopy = rhs;
    std::swap(*this, listCopy);
    return *this;
}

// List Move Assignment Operator
template<typename T>
List<T>& List<T>::operator=(List && rhs){
    std::swap(head, rhs.head);
    std::swap(tail, rhs.tail);
    std::swap(theSize, rhs.theSize);
    return *this;
}

// List Initializer List Assignment Operator
template<typename T>
List<T>& List<T>::operator= (std::initializer_list<T> iList){
    init();
    auto itr = iList.begin();
    for (auto i: iList)
        push_back(*itr++);
    return *this;
}

// List Size Function (Returns size of list)
template<typename T>
int List<T>::size() const
{return theSize;}

// List Empty Function (Checks if list is empty)
template<typename T>
bool List<T>::empty() const{
    if (size() == 0)
        return true;
    return false;
}

// List Clear Function
template<typename T>
void List<T>::clear(){
    while (!empty())
        pop_front();
}

// List Reverse Function (Reverses order of list)
template<typename T>
void List<T>::reverse(){
    iterator itrFront = begin();
    iterator itrBack = --end();

    for (int i = 0; i < theSize/2; i++)
    {
        std::swap(itrFront.current->data, itrBack.current->data);
        itrFront++; itrBack--;
    }
}

// List Front Function (Returns the data at the beginning of list)
template<typename T>
T& List<T>::front(){
    return *begin();
}

// List Const Front Function
template<typename T>
const T& List<T>::front() const{
    return *begin();
}

// List Back Function (Return the data at the end of list)
template<typename T>
T& List<T>::back(){
    return *--end();
}

// List Const Back Function
template<typename T>
const T& List<T>::back() const{
    return *--end();
}

// List Push_Front Function (Inserts node at front of list)
template<typename T>
void List<T>::push_front(const T & val){
    insert(--begin(), val);
}

// List Move Semantics Push_Front Function
template<typename T>
void List<T>::push_front(T && val){
    insert(--begin(), std::move(val));
}

// List Push_Back Function (Inserts node at back of list)
template<typename T>
void List<T>::push_back(const T & val){
    insert(--end(), val);
}

// List Move Semantics Push_Back Function
template<typename T>
void List<T>::push_back(T && val){
    insert(--end(), std::move(val));
}

// List Pop_Front Function (Removes node at the front of list)
template<typename T>
void List<T>::pop_front(){
    erase(begin());
}

// List Pop_Back Function (Removes node at the back of list)
template<typename T>
void List<T>::pop_back(){
    erase(--end());
}

// List Remove Function (Removes all nodes with specified data)
template<typename T>
void List<T>::remove(const T &val){
    iterator itr = begin();
    while (itr != tail)
    {
        if(itr.current->data == val)
        {
            iterator oldItr = itr;
            itr++;
            erase(oldItr);
        }
        else itr++;
    }
}

// List Remove_if Function (Removes all nodes that meet specified function criteria)
template<typename T>
template<typename PREDICATE>
void List<T>::remove_if(PREDICATE pred) {
    iterator itr = begin();
    while(itr != tail)
    {
        if (pred(itr.current->data) == true)
        {
            iterator oldItr = itr;
            itr++;
            erase(oldItr);
        }
        else itr++;
    }
}

// List Print Function
template<typename T>
void List<T>::print(std::ostream& os, char ofc) const{
    auto itr = begin();
    while(itr != tail)
        os << *itr++ << ofc;
}

// List Begin Function (Returns iterator at front of list)
template<typename T>
typename List<T>::iterator List<T>::begin(){
    return iterator(head->next);
}

// List Const Begin Function (Returns const_iterator at front of list)
template<typename T>
typename List<T>::const_iterator List<T>::begin() const{
    return const_iterator(head->next);
}

// List End Function (Returns iterator at end of list)
template<typename T>
typename List<T>::iterator List<T>::end(){
    return iterator(tail);
}

// List Const End Function (Returns const_iterator at end of list)
template<typename T>
typename List<T>::const_iterator List<T>::end() const{
    return const_iterator(tail);
}

// List Insert Function (Inserts node ahead of iterator, returns iterator at new node)
template<typename T>
typename List<T>::iterator List<T>::insert(iterator itr, const T& val){
    Node *p = itr.current;
    theSize++;
    p->next = p->next->prev = new Node{val, p, p->next};
    return iterator(p->next);
}

// List Move Semantics Insert Function
template<typename T>
typename List<T>::iterator List<T>::insert(iterator itr, T && val){
    Node *p = itr.current;
    theSize++;
    p->next = p->next->prev = new Node{std::move(val), p, p->next};
    return iterator(p->next);
}

// List Erase Function (Erase node at iterator, return iterator at the following node)
template<typename T>
typename List<T>::iterator List<T>::erase(iterator itr){
    Node *p = itr.current;
    iterator returnValue(p->next);
    p->prev->next = p->next;
    p->next->prev = p->prev;
    delete p;
    theSize--;
    return returnValue;
}

// List "From x to non-inclusive y" Erase Function (Erases nodes from [x - y), returns iterator at y)
template<typename T>
typename List<T>::iterator List<T>::erase(iterator start, iterator end){
    while (start != end)
        start = erase(start);
    return end;
} // erase [start, end)

// List Init Function (Used by class to initialize list)
template<typename T>
void List<T>::init(){
    theSize = 0;
    head = new Node;
    tail = new Node;
    head->next = tail;
    tail->prev = head;
}

//------------------------------------------------------------

// Overloaded Comparison Operators
template <typename T>
bool operator==(const List<T> & lhs, const List<T> &rhs){

    if (lhs.size() == rhs.size())
    {
        auto itr = lhs.begin();
        auto itr2 = rhs.begin();
        for (int i = 0; i < lhs.size(); i++)
        {
            if (*itr != *itr2)
                return false;
        }
        return true;
    }
    return false;
}
template <typename T>
bool operator!=(const List<T> & lhs, const List<T> &rhs){
    return !(lhs == rhs);
}

// Overloaded Output Operator
template <typename T>
std::ostream & operator<<(std::ostream &os, const List<T> &l){
    l.print(os, ' ');
    return os;
}
