#include <iostream>
#include <string>

class Variant
{
public:
    Variant();
    Variant(const int &arg);
    Variant(const float &arg);
    Variant(const double &arg);
    Variant(const char &arg);
    Variant(std::string &arg);

    template<typename T>
    void putValue(T &variable) const;

private:

    enum type { INT = 1, FLOAT, DOUBLE, CHAR, STRING };
    type        m_type;
    int         m_int;
    float       m_float;
    double      m_double;
    char        m_char;
    std::string m_string;
};

int main()
{
    Variant objInt;
    //Variant objStr("hello world");
    Variant objChar('A');
    int i;
    std::string s;
    char c;
    objInt.putValue(i);
    objChar.putValue(c);

    std::cout << "int = " << i << std::endl
              << "char = " << c << std::endl;
    return 0;
}


Variant::Variant() :
    m_int(0),
    m_type(INT)
    {}

Variant::Variant(const int &arg) :
    m_int(arg),
    m_type(INT)
    {}

Variant::Variant(const float &arg) :
    m_float(arg),
    m_type(FLOAT)
    {}

Variant::Variant(const double &arg) :
    m_double(arg),
    m_type(DOUBLE)
    {}

Variant::Variant(const char &arg) :
    m_char(arg),
    m_type(CHAR)
    {}

Variant::Variant(std::string &arg) :
    m_string(arg),
    m_type(STRING)
    {}

template<typename T>
void Variant::putValue(T &variable) const
{
    switch(m_type)
    {
    case INT:
        variable = m_int;
        break;

    case FLOAT:
        variable = m_float;
        break;

    case DOUBLE:
        variable = m_double;
        break;

    case CHAR:
        variable = m_char;
        break;
    }
}

