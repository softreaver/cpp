#include <iostream>
#include <algorithm>
#include <vector>
#include <ctime>
#include <cstdlib>


using namespace std;

class moyenne
{
public:
    moyenne(int nombre) : m_moyenne(0.0), m_nombreNotes(nombre), m_totalNotes(0.0)
    {}

    void operator()(float const& value)
    {
        m_totalNotes += value;
    }

    float calcule() const
    {
        return m_totalNotes/m_nombreNotes;
    }

private:
    float m_moyenne;
    float m_totalNotes;
    int m_nombreNotes;
};

class gen
{
public:
    int operator()()
    {
        return rand() % 10;
    }
};

class decroissant
{
public:
    bool operator()(int const& avant, int const& apres)
    {
        return avant > apres;
    }
};

int main()
{
    srand(time(0));

    vector<int> tab(10);

    generate(tab.begin(), tab.end(), gen());

    cout << "Il y a " << count(tab.begin(), tab.end(), 5) << " \"5\" dans la liste." << endl;

    for(vector<int>::iterator it = tab.begin(); it != tab.end(); ++it)
        cout << *it << endl;

    sort(tab.begin(), tab.end(), decroissant());

    for(vector<int>::iterator it = tab.begin(); it != tab.end(); ++it)
        cout << *it << endl;

    moyenne note(tab.size());

    note = for_each(tab.begin(),tab.end(),note);

    cout << "La moyenne des nombres est egale a : " << note.calcule() << "." << endl;
    return 0;
}
