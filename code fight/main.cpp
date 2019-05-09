#include <iostream>
#include <string>


bool checkPalindrome(std::string inputString)
{
    int length(inputString.length()), i2(0);

    if(length%2 != 0)
        i2 = --length;
    else
        i2 = length-1;

    for(int i(0); i < length/2; i++)
    {
        if(inputString[i] != inputString[i2]) return false;
        i2--;
    }
    return true;
}

int main()
{
    std::cout << checkPalindrome("aabaa");
    return 0;
}
