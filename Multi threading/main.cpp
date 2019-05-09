#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <iterator>
#include <string>

typedef std::ostream_iterator<std::string> myIterator;

template<typename T>
void display(T arg)
{
    myIterator it(std::cout);
    std::cout << arg << std::endl;
}

void op1()
{
    for(int i = 0; i < 11; ++i)
    {
        display(i);
    }
}

void op2()
{
    for(int i = 64; i < 91; ++i)
    {
        display<char>('a'+i);
    }
}

class test
{
public:

    static void op3()
    {
        display("string");
    }
};

class testObj
{
public:
    template<typename T>
    void disp(T arg) const
    {
        display(arg);
    }
};
int main()
{
int compteur = 0;
std::mutex lock;
do
{

    std::cout << "op1" << std::endl;
    std::thread T1(op1);

    std::cout << "op2" << std::endl;
    std::thread T2(op2);

    std::cout << "op3" << std::endl;
    std::thread T3(test::op3); //ici pas besoins d'objet pour utiliser la méthode car celle ci est static

    std::cout << "op4" << std::endl;
    std::string arg("Ceci est un test de ouf !"); testObj obj;
    std::thread T4(&testObj::disp<decltype(arg)>, &obj, arg); //ici on passe par un objet afin d'utiliser la méthode

    T1.join();
    T2.join();
    T3.join();
    T4.join();
    compteur++;
}while(compteur < 10);

    return 0;
}
