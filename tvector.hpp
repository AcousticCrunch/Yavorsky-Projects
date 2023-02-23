#include "tvector.h"

using namespace std;

// *************************************
// ***********TVector Class************
// *************************************

// Default Constructor
template<typename T>
TVector<T>::TVector()
{
    capacity = SPARECAPACITY;
    size = 0;
    array = new T[capacity];
}

// Two Param Constructor
// Creates vector of N of amount of X values
template<typename T>
TVector<T>::TVector(T val, int num)
{
    capacity = num;
    size = num;
    array = new T[capacity];
    for (int i = 0; i < size; i++)
        array[i] = val;
}

// Destructor
template<typename T>
TVector<T>::~TVector()
{
    if (array != nullptr);
        delete [] array;
}

// Copy Constructor
template<typename T>
TVector<T>::TVector(const TVector<T> &v)
{
    size = v.size;
    capacity = v.capacity;
    array = new T[capacity];

    for (int i = 0; i < size; i++)
        array[i] = v.array[i];

}


// Copy Assignment Operator
template<typename T>
TVector<T> &TVector<T>::operator=(const TVector<T> &v)
{
    if (this != &v)
    {
        delete [] array;

        capacity = v.capacity;
        size = v.size;
        array = new T[capacity];

        for (int i = 0; i < size; i++)
            array[i] = v.array[i];
    }

    return *this;
}

// Move Constructor
template<typename T>
TVector<T>::TVector(TVector<T> &&v)
{
    capacity = v.capacity;
    size = v.size;
    array = v.array;

    v.array = nullptr;
    v.capacity = 0;
    v.size = 0;

}

// Move Assignment Constructor
template<typename T>
TVector<T> &TVector<T>::operator=(TVector<T> &&v)
{
    std::swap(capacity, v.capacity);
    std::swap(size, v.size);
    std::swap(array, v.array);

    return *this;
}

// IsEmpty Function
// Checks to see if vector is empty
template<typename T>
bool TVector<T>::IsEmpty() const
{
    if (size == 0)
        return true;
    return false;
}

// Clear Function
// Clears current vector of data
template<typename T>
void TVector<T>::Clear()
{
    delete [] array;

    size = 0;
    array = new T[capacity];
}

// GetSize Function
// Returns size of vector
template<typename T>
int TVector<T>::GetSize() const
{
    return size;
}

// InsertBack Function
// Inserts elements in the back of vector
template<typename T>
void TVector<T>::InsertBack(const T &d)
{
    // Increases capacity if needed
    if (capacity == size)
        SetCapacity(size * 2);

    array[size] = d;
    size++;
}

// RemoveBack Function
// Removes element at the back of the vector
template<typename T>
void TVector<T>::RemoveBack()
{
    if (!IsEmpty())
    {
        size--;
        array[size] = 0;
    }
}

// GetFirst Function
// Returns array element at the beginning of the vector
template<typename T>
T &TVector<T>::GetFirst() const
{
    // Returns dummy object if vector is empty
    if (IsEmpty())
        return dummy;
    return array[0];
}

// GetLast Function
// Returns array element at the end of the vector
template<typename T>
T &TVector<T>::GetLast() const
{
    // Returns dummy object if vector is empty
    if (IsEmpty())
        return dummy;
    return array[size - 1];
}

// GetIterator Function
// Returns default iterator placed at the beginning of the vector
template<typename T>
TVectorIterator<T> TVector<T>::GetIterator() const
{
    TVectorIterator<T> itr;

    // Return default iterator with no data if vector is empty
    if (IsEmpty())
        return itr;

    itr.ptr = &array[0];
    itr.vsize = size;
    return itr;
}

// GetIteratorEnd
// Returns an iterator places at the last element in the vector
template<typename T>
TVectorIterator<T> TVector<T>::GetIteratorEnd() const
{
    TVectorIterator<T> itr;

    // Return default iterator with no data if vector is empty
    if (IsEmpty())
        return itr;


    itr.index = size - 1;
    itr.ptr = &array[itr.index];
    itr.vsize = size;
    return itr;
}

// SetCapacity Function
// Sets a new capacity for the vector, specified by param
template<typename T>
void TVector<T>::SetCapacity(unsigned int c)
{
    capacity = c;

    // Creates new template array
    T *temp = new T[capacity];

    // Copies all elements over to new array
    for (int i = 0; i < capacity && i < size; i++)
        temp[i] = array[i];

    // Deletes old array
    delete [] array;

    // Assigns old pointer to new array
    array = temp;
}

// Insert Function
// Inserts element at specified position, given by the position of an iterator, and returns iterator
// at that data element
template<typename T>
TVectorIterator<T> TVector<T>::Insert(TVectorIterator<T> pos, const T &d)
{
    // Return vector with only the specified element in it if given vector is empty
    if (IsEmpty())
    {
        array[0] = d;
        pos.index = 0;
        pos.vsize = 1;
        size = 1;
        pos.ptr = &array[0];
        return pos;
    }

    // Check to see if iterator is pointing to correct element
    bool found;
    for (int i = 0; i < size; i++)
    {
        if (&array[i] == pos.ptr)
        {
            found = true;
            break;
        }
        found = false;
    }

    // If iterator is invalid, insert element at the back and return iterator at the back
    if (pos.ptr == nullptr || !found)
    {
        InsertBack(d);
        pos.index = size - 1;
        pos.vsize = size;
        pos.ptr = &array[pos.index];
        return pos;
    }

    else
    {
        // If array is too small, grow it
        if (size == capacity)
            SetCapacity(2 * size);

        size++;
        pos.vsize++;

        // Shift all elements ahead of iterator up a spot
        for (int i = size; i > pos.index; i--)
            array[i] = array[i-1];

        // Empty spot is assigned new element
        array[pos.index] = d;
        pos.ptr = &array[pos.index];

        // Return iterator at new element
        return pos;
    }
}

// Remove Function
// Removes element at specified iterator
template<typename T>
TVectorIterator<T> TVector<T>::Remove(TVectorIterator<T> pos)
{
    bool found;

    // Check to see if iterator is valid
    for (int i = 0; i < size; i++)
    {
        if (&array[i] == pos.ptr)
        {
            found = true;
            break;
        }
        found = false;
    }

    // If iterator is invalid or the vector is empty, return default iterator
    if (pos.ptr == nullptr || !found || IsEmpty())
    {
        TVectorIterator<T> itr;
        return itr;
    }

    else
    {
        array[pos.index] = 0;
        size--;
        pos.vsize--;

        // Shift all elements from iterator down a spot
        for (int i = pos.index; i < size; i++)
            array[i] = array[i + 1];

        // Return iterator at same position now holding
        // the element that was ahead of specified element
        return pos;
    }
}

// Two Param Remove Function
// Removes elements of vector in specified range,
// not including element of pos2 but including element of pos1
template<typename T>
TVectorIterator<T> TVector<T>::Remove(TVectorIterator<T> pos1, TVectorIterator<T> pos2)
{
    bool found;

    // Check to see if iterator is valid
    for (int i = 0; i < size; i++)
    {
        if (&array[i] == pos1.ptr)
        {
            found = true;
            break;
        }
        found = false;
    }

    // If iterator is invalid or vector is empty, return default iterator
    if (pos1.ptr == nullptr || !found || IsEmpty())
    {
        TVectorIterator<T> itr;
        return itr;
    }

    // Check second iterator for validity
    for (int i = 0; i < size; i++)
    {
        if (&array[i] == pos2.ptr)
        {
            found = true;
            break;
        }
        found = false;
    }

    // If second iterator is invalid or empty, return default iterator
    if (pos2.ptr == nullptr || !found || IsEmpty())
    {
        TVectorIterator<T> itr;
        return itr;
    }

    // If first iterator is farther than the second iterator, return first iterator unchanged
    else if (pos1.index >= pos2.index)
        return pos1;

    else
    {
        int offset = pos2.index;

        // Every element after first iterator becomes the one ahead of it by offset of range
        for (int i = pos1.index; offset < size; i++)
        {
            array[i] = array[offset];
            offset++;
        }

        // Size is adjusted based on range
        size -= (pos2.index - pos1.index);
        pos1.vsize == size;
        pos2.vsize == size;

        // Assigned new pointers to iterators
        pos1.ptr = &array[pos1.index];
        pos2.ptr = &array[pos2.index];

        // Return second iterator
        return pos2;

    }
}

// Print Function
// Prints vector with specified delimiter separating each element
template<typename T>
void TVector<T>::Print(std::ostream &os, char delim) const
{

    // Create new iterator to loop with
    TVectorIterator<T> itr = GetIterator();

    // Loop through vector with iterator, printing each element
    os << itr.GetData();
    while (itr.HasNext())
    {
        itr = itr.Next();
        os  << delim << itr.GetData();
    }
}

// +Operator Overload
// Overloads the + operator to concatenate two vectors, with t1 going before t2
template<typename T>
TVector<T> operator+(const TVector<T>& t1, const TVector<T>& t2)
{
    // Create new vector
    TVector<T>t3;

    // Grow new vector to accompany the two vectors
    t3.SetCapacity(t1.GetSize() + t2.GetSize() + 10);

    // Create two iterators to loop with
    TVectorIterator<T> itr1 = t1.GetIterator();
    TVectorIterator<T> itr2 = t2.GetIterator();

    // Insert the first vector into the new vector, using the first iterator
    t3.Insert(itr1, itr1.GetData());
    while (itr1.HasNext())
    {
        itr1.Next();
        t3.Insert(itr1, itr1.GetData());
    }

    // Insert the second vector after the previous vector, using the second iterator
    t3.Insert(itr2, itr2.GetData());
    while (itr2.HasNext())
    {
        itr2.Next();
        t3.Insert(itr2, itr2.GetData());
    }

    // Return new vector
    return t3;
}

// *************************************
// ***********Iterator Class************
// *************************************

// Default Constructor
template<typename T>
TVectorIterator<T>::TVectorIterator()
{
    index = 0;
    ptr = nullptr;
    vsize= 0;
}

// HasNext Function
// Checks to see if iterator has another element after current one, returning false if not
// and true if so
template<typename T>
bool TVectorIterator<T>::HasNext() const
{
    // If iterator is invalid, return false
    if (ptr == nullptr)
        return false;

    else if (index >= (vsize - 1))
        return false;

    return true;
}

// HasNext Function
// Checks to see if iterator has another element before current one, returning false if not
// and true if so
template<typename T>
bool TVectorIterator<T>::HasPrevious() const
{
    // If iterator is invalid, return false
    if (ptr == nullptr)
        return false;

    else if (index <= 0)
        return false;

    return true;
}

// Next Function
// Moves iterator up one spot in vector
template<typename T>
TVectorIterator<T> TVectorIterator<T>::Next()
{

    // Create new iterator
    TVectorIterator<T> itr;

    // Checks to see if current iterator is valid
    if (ptr != nullptr)
    {
        // If iterator is at the last element, don't change the iterator
        if (index == (vsize - 1))
        {
            itr.index = index;
            itr.ptr = ptr;
            itr.vsize = vsize;
            return itr;
        }

        // Increment pointer and index of copy iterator
        index++;
        ptr++;

        // Make sure to copy over all data from current iterator
        itr.index = index;
        itr.ptr = ptr;
        itr.vsize = vsize;

        // Return copy of iterator, shifted up one spot
        return itr;
    }

    // Returns default iterator if current one is invalid
    else
        return itr;
    
}

// Previous Function
// Moves iterator back one spot in vector
template<typename T>
TVectorIterator<T> TVectorIterator<T>::Previous()
{

    // Create new iterator
    TVectorIterator<T> itr;

    // Checks to see if current iterator is valid
    if (ptr != nullptr)
    {
        // If iterator is at the first element, don't change the iterator
        if (index == 0)
        {
            itr.index = index;
            itr.ptr = ptr;
            itr.vsize = vsize;
            return itr;
        }

        // Decrement pointer and index of copy iterator
        index--;
        ptr--;

        // Make sure to copy over all data from current iterator
        itr.index = index;
        itr.ptr = ptr;
        itr.vsize = vsize;

        // Return copy of iterator, shifted down one spot
        return itr;
    }

    // Returns default iterator if current one is invalid
    else
        return itr;

}

// GetData Function
// Return element at current iterator
template<typename T>
T &TVectorIterator<T>::GetData() const
{
    // Return dummy object if current iterator is invalid
    if (ptr == nullptr)
    {
        TVector<T> v;
        return v.dummy;
    }

    // Return de-referenced pointer if valid
    else
        return *ptr;
}


