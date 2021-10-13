#

#include <iostream>
#include "distance.h"

using namespace std;

int main() {

    Distance d1(150002);
    Distance d2(5, 5, 2, 8);
    Distance d3(5, 5, 2, 8);
    Distance d4;
    Distance d5(-5, -16, 697, -51);
    Distance d6(-159609);

    cout << ++d2;
    cout << d2 - d5;
    cout << d2 * d5;
    cout << d6 + d1;
  

    return 0;
}
