#include <iostream>

class Mere
{
public:

    Mere()
    {
        std::cout << "construction mere" << std::endl;
    }

    ~Mere()
    {
        std::cout << "destruction mere" << std::endl;
    }
};

class Fille1 : public Mere
{
public:

    Fille1()
    {
        std::cout << "construction fille1" << std::endl;
    }

    ~Fille1()
    {
        std::cout << "destruction fille1" << std::endl;
    }
};

class Fille2 : public Fille1
{
public:

    Fille2()
    {
        std::cout << "construction fille2" << std::endl;
    }

    ~Fille2()
    {
        std::cout << "destruction fille2" << std::endl;
    }
};

int main()
{
    Fille2 test;
    return 0;
}
