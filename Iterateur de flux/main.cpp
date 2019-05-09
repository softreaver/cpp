#include <iostream>
#include <string>
#include <iterator>
#include <fstream>

using namespace std;

int main()
{

    ostream_iterator<string> it(cout, "\n");

    *it = "Hello";
    *it = "world!";

    ifstream fichier("data.txt");
    istream_iterator<string> it2(fichier);
    istream_iterator<string> end;

    while(it2 != end)
    {
        *it = *it2;
        ++it2;
    }

    return 0;
}
