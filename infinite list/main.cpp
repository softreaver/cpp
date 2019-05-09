#include <iostream>
#include <cassert>

template<class T>
struct Line
{
    Line  *prev;
    T       val;
    Line  *next;
};

template<class NewLine>
class Infinit_List
{
    unsigned int   m_elementsCount;   //Nombre d'elements présents dans la liste.
    Line<NewLine>* m_Line;            //Représente une ligne dans le tableau.
    Line<NewLine>* m_firstLine;       //Première ligne, important de la garder!
    Line<NewLine>* m_lastLine;        //Dernière ligne créée


public:
    Infinit_List();
    Infinit_List(const NewLine& arg);

    template<class... U>
    Infinit_List(const NewLine &arg, const U&... init);
    ~Infinit_List();

    inline NewLine operator[](const unsigned int& index);

private:
    void makeLine(Line<NewLine> *from, const NewLine &arg);

    template<typename... U>
    void makeLine(Line<NewLine> *from, const NewLine &arg, const U&... listArg);

public:


};

int main()
{
    Infinit_List<int> myList(1, 2, 3, 4);
    std::cout << myList[3] << std::endl;
    return 0;
}




template<class NewLine>
Infinit_List<NewLine>::Infinit_List() : m_Line(nullptr)
{
    m_firstLine = new Line<NewLine>;
    m_elementsCount   = 0;
    m_firstLine->prev = nullptr;
    m_firstLine->next = nullptr;
}

template<class NewLine>
Infinit_List<NewLine>::Infinit_List(const NewLine& arg) : m_Line(nullptr)
{
    m_firstLine = new Line<NewLine>;
    m_elementsCount   = 0;
    m_firstLine->prev = nullptr;
    m_firstLine->val  = arg;
    m_firstLine->next = nullptr;
    std::cout << "construction simple" << std::endl;
}

template<class NewLine>
template<class... U>
Infinit_List<NewLine>::Infinit_List(const NewLine& arg, const U&... init) : m_Line(nullptr)
{
    m_firstLine = new Line<NewLine>;
    m_elementsCount   = 1;
    m_firstLine->prev = nullptr;
    m_firstLine->val  = arg;
    m_firstLine->next = nullptr;
    makeLine(m_firstLine, init...);
    std::cout << "construction multiple" << std::endl;
}

template<class NewLine>
void Infinit_List<NewLine>::makeLine(Line<NewLine> *from, const NewLine &arg)
{
    m_elementsCount++;
    Line<NewLine> *This = new Line<NewLine>;
    from->next = This;
    This->prev = from;
    This->val  = arg;
    This->next = nullptr;
    m_lastLine = This;
}

template<class NewLine>
template<typename... U>
void Infinit_List<NewLine>::makeLine(Line<NewLine> *from, const NewLine &arg, const U&... listArg)
{
    m_elementsCount++;
    Line<NewLine> *This = new Line<NewLine>;
    from->next = This;
    This->prev = from;
    This->val  = arg;
    This->next = nullptr;
    makeLine(This, listArg...);
}

template<class NewLine>
Infinit_List<NewLine>::~Infinit_List()
{
    m_Line = m_lastLine;
    for(unsigned int i(0); i < m_elementsCount; ++i)
    {
        Line<NewLine> *next = m_Line->prev;
        delete m_Line;
        m_Line = next;
    }
    std::cout << "destruction de " << m_elementsCount << " elements" << std::endl;
}

template<class NewLine>
inline NewLine Infinit_List<NewLine>::operator[](const unsigned int& index)
{
    assert(index < m_elementsCount);
    unsigned int i(0);
    m_Line = m_firstLine;
    while(i != index) { i++ ; m_Line = m_Line->next; }
    return m_Line->val;
}
