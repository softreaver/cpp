#include <iostream>
#include <typeinfo>
#include <stack>
#include <string>


template<typename T>
std::string binary(T arg)
{
    std::stack<char> pile;
    for(int8_t i(0); i < sizeof(arg) * 8; i++)
    {
        if(arg & (1<<i))
            pile.push('1');
        else
            pile.push('0');
    }
    std::string str("");
    while(!pile.empty())
    {
        str += pile.top();
        pile.pop();
    }
    return str;
}


template<typename T> inline
void display_range_of(T arg)
{
    arg = arg^arg;
    std::cout << typeid(arg).name() << " : Valeur min = "
              << (decltype(arg))arg << "\nValeur max = "
              << (decltype(arg))(~arg) << "\nCode sur " << sizeof(arg) << " octet." << std::endl;
}

int main() {

    int var(8);
    std::cout << binary(var) << std::endl;
    display_range_of(var);

  return 0;
}
