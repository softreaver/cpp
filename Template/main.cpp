#include <iostream>

using namespace std;

template<typename T>
class Rectangle
{
public:
    Rectangle(T longueur, T largeur, T pX, T pY);
    T longueur() const;
    T largeur() const;
    T surface() const;
    void afficherPosition() const;
    bool operator<(Rectangle const& rhs) const;

private:

    T m_longueur;
    T m_largeur;
    T m_pX;
    T m_pY;
};

int main()
{
    Rectangle<float> r1(10,5,0,0);
    Rectangle<float> r2(11.5,5.0,0.,0.);

    cout << r1.longueur() << " / " << r1.largeur() << endl;
    r1.afficherPosition();
    cout << r2.longueur() << " / " << r2.largeur() << endl;
    r2.afficherPosition();

    cout << r2.surface() << endl;

    if(r1 < r2)
        cout << "r1 plus petit que r2.\n";
    else
        cout << "r1 n'est pas plus petit que r2.\n";

    return 0;
}

template<typename T>
Rectangle<T>::Rectangle(T longueur, T largeur, T pX, T pY):
        m_largeur(largeur),
        m_longueur(longueur),
        m_pX(pX),
        m_pY(pY)
{}

template<typename T>
T Rectangle<T>::longueur() const
{
    return m_longueur;
}

template<typename T>
T Rectangle<T>::largeur() const
{
    return m_largeur;
}

template<typename T>
T Rectangle<T>::surface() const
{
    return m_longueur * m_largeur;
}

template<typename T>
void Rectangle<T>::afficherPosition() const
{
    cout << "px = " << m_pX << " py = " << m_pY << endl;
}

template<typename T>
bool Rectangle<T>::operator<(Rectangle const& rhs) const
{
    return this->surface() < rhs.surface();
}

