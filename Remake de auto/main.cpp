#include <iostream>

class Variant
{
public:
    Variant();
    template<class T>
    Variant(T val);

    template<typename T>
    T value() const;
private:
    template<typename T>
    union myType_T
    {
        T val;
    };

    myType_T myType;
};

int main()
{
    Variant obj(123);
    std::cout << obj.value() << std::endl;

    return 0;
}

Variant::Variant(){}

template<class T>
Variant::Variant(T val) :
    myType<T>(val)
{}

template<typename T>
T Variant::value() const
{
    return myType.val;
}
