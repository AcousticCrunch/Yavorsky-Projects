#include <iostream>
#include "tvector.h"

using namespace std;

int main()
{
    cout << "****************************" << endl
         << "**** Vector Class Tests ****" << endl
         << "****************************" << endl;

    // Default Vector Constructor
    TVector<int> V1;
    TVector<char>V1Char;

    // Two Param Vector Constructor
    TVector<int> V2(2, 10);

    // Print Default Vectors
    cout << "V1 = "; V1.Print(cout, ','); cout << endl;
    cout << "V2 = "; V2.Print(cout, ','); cout << endl;
    cout << "V1Char = "; V1Char.Print(cout, ','); cout << endl << endl;

    // Insert back function
    for (int i = 0; i < 15; i++)
        V1.InsertBack(i);
    cout << "V1 after InsertBack (0 -> 14) = "; V1.Print(cout, ',');
    cout << endl;

    // Copy assignment operator
    TVector<int> V1Copy;
    V1Copy = V1;
    cout << "V1Copy (Copy Assignment Operator) = "; V1Copy.Print(cout, ',');
    cout << endl << endl;

    // Insert Back function, copy constructor and Remove Back function (char);
    for (int i = 0; i < 12; i++)
        V1Char.InsertBack('a' + i);
    cout << "V1Char after InsertBack (a -> k) = "; V1Char.Print(cout, ',');
    cout << endl;

    TVector<char> V1CharCopy = V1Char;
    cout << "V1CharCopy (Copy Constructor) = "; V1CharCopy.Print(cout, ',');
    cout << endl << endl;

    cout << "V1Char before RemoveBack (All Removed) = "; V1Char.Print(cout, ',');
    cout << endl;
    while (!V1Char.IsEmpty())
        V1Char.RemoveBack();
    cout << "V1Char after RemoveBack (All Removed) = "; V1Char.Print(cout, ',');
    cout << endl << endl;

    // +operator overload
    cout << "V1 = "; V1.Print(cout, ','); cout << endl;
    cout << "V2 = "; V2.Print(cout, ','); cout << endl;
    TVector<int> V3 = V1 + V2;
    cout << "V3 ( V1 + V2 ) = "; V3.Print(cout, ',');
    cout << endl << endl;

    // Remove Back Function (int)
    for (int i = 0; i < 10; i++)
        V3.RemoveBack();
    cout << "V3 after RemoveBack (10 Removed) = "; V3.Print(cout, ',');
    cout << endl;


    // GetFirst and GetLast Functions
    cout << "GetFirst of V3 = " << V3.GetFirst() << endl;
    cout << "GetLast of V3 = " << V3.GetLast() << endl;
    // GetSize Function
    cout << "GetSize of V3 = " << V3.GetSize() << endl << endl;

    // Move Assignment Operator
    cout << "V2 before move assignment (Swapping V2 & V3) = "; V2.Print(cout, ',');
    cout << endl;
    cout << "V3 before move assignment (Swapping V2 & V3) = "; V3.Print(cout, ',');
    cout << endl;
    V2 = std::move(V3);
    cout << "V2 after move assignment (Swapping V2 & V3) = "; V2.Print(cout, ',');
    cout << endl;
    cout << "V3 after move assignment (Swapping V2 & V3) = "; V3.Print(cout, ',');
    cout << endl << endl;

    // Move Constructor
    cout << "V2 before move constructor = "; V2.Print(cout, ',');
    cout << endl;
    TVector<int>V2Move = std::move(V2);
    cout << "V2Move after move constructor (Swapping default V2Move & V2) = "; V2Move.Print(cout, ',');
    cout << endl;
    cout << "V2 after move constructor (Should be default vector) = "; V2.Print(cout, ',');
    cout << endl << endl;

    // Clear Function
    V2Move.Clear();
    cout << "V2Move after Clear = "; V2.Print(cout, ',');
    cout << endl << endl;

    cout << "******************************" << endl
         << "**** Iterator Class Tests ****" << endl
         << "******************************" << endl;

    // GetIterator function
    TVectorIterator<char> itr1char;
    cout << "Itr1char Default Data = " << itr1char.GetData() << endl;
    itr1char = V1CharCopy.GetIterator();
    cout << "Itr1char after V1CharCopy.GetIterator = " << itr1char.GetData() << endl;

    // GetIteratorEnd function
    TVectorIterator<int> itr1;
    cout << "Itr1 Default Data = " << itr1.GetData() << endl;
    itr1 = V1.GetIteratorEnd();
    cout << "Itr1 after V1.GetIteratorEnd = " << itr1.GetData() << endl << endl;

    // Print using iterators

    cout << "V1 listed backwards using iterator ... " << endl;
    while (itr1.HasPrevious())
    {
        cout << itr1.GetData() << ", ";
        itr1.Previous();
    }
    cout << itr1.GetData() << endl << endl;

    cout << "V1CharCopy listed using iterator ... " << endl;
    cout << itr1char.GetData() << ", ";
    while (itr1char.HasNext())
    {
        itr1char.Next();
        cout << itr1char.GetData() << ", ";
    }
    cout << endl << endl;

    // Two Param Insert Function
    for (int i = 0; i < 7; i++)     // moves iterator up to 7th vector slot
        itr1.Next();
    cout << "V1 before 10 iterator inserts before 8th element = "; V1.Print(cout, ','); cout << endl;

    for (int i = 0; i < 11; i++)    // inserts ints into middle of vector
    {
        itr1 = V1.Insert(itr1, 300 + i);
        itr1.Next();
    }
    cout << "V1 after 10 iterator inserts before 8th element = "; V1.Print(cout, ','); cout << endl << endl;

    // Remove Function
    for (int i = 0; i < 11; i++)     // moves char iterator down to 1st vector spot
        itr1char.Previous();
    cout << "V1CharCopy before iterator removes every element except for l = ";
    V1CharCopy.Print(cout, ','); cout << endl;


    for (int i = 0; i < 11; i++)        // removes char's from the beginning of the vector until the very last element
        itr1char = V1CharCopy.Remove(itr1char);
    cout << "V1CharCopy after iterator removes every element except for l = ";
    V1CharCopy.Print(cout, ','); cout << endl << endl;

    // Two Param Remove Function
    TVectorIterator<int> itr2 = V1.GetIteratorEnd();

    while (itr2.GetData() != 7)     // decrement iterators to range of removal [300 - 7)
        itr2.Previous();

    while (itr1.GetData() != 300)
        itr1.Previous();

    cout << "V1 before 300 -> 310 is removed = "; V1.Print(cout, ','); cout << endl;

    itr1 = V1.Remove(itr1, itr2);

    cout << "V1 after 300 -> 310 is removed = "; V1.Print(cout, ','); cout << endl;

    return 0;
}
