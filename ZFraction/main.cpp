#include <iostream>
#include "ZFraction.h"

using namespace std;

int main()
{
    ZFraction a(-78,-56);
    a.simplifier();
    ZFraction b(45,-3);
    b.simplifier();
    ZFraction c,d, e;      //Déclare trois fraction valant 0

    c = a-b;        //calcule 4/5 + 2/1 = 14/5
    c.simplifier();

    d = a*b;        //Calcule 4/5 * 2/1 = 8/5
    d.simplifier();

    cout << a << " - " << b << " = " << c << endl;

    cout << a << " * " << b << " = " << d << endl;

    if(a > b)
        cout << "a est plus grand que b." << endl;
    else if(a==b)
        cout << "a est egal a b." << endl;
    else
        cout << "a est plus petit que b." << endl;

    cout << e << endl;

    return 0;
}
