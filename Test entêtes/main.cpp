#include <iostream>
#include <string>
#include <cctype>


int main()
{
    std::string phrase;
    std::cout << "veuillez entrer une phrase :" << std::endl;

    std::getline(std::cin, phrase);

    for(int i(0); i<phrase.length(); i++)
    {
        if(isspace(phrase[i]))
            phrase[i] = '#';
    }

    std::cout << phrase << std::endl;

    return 0;
}
