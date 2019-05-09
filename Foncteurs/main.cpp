#include <iostream>
#include <string>
#include <map>

class longueurStr
{
public:
    bool operator()(std::string const& a, std::string const& b) const
    {
        return a.length() < b.length();
    }
};

int main()
{
    std::map<std::string, double, longueurStr> poids; //en ajoutant en 3eme paramètre le nom du foncteurs on chaznge le comportement du classement des donnés dans la map

    poids["souris"] = 0.05;
    poids["tigre"] = 200.0;
    poids["elephant"] = 850.0;
    poids["chien"] = 45.0; //chien n'appa&raitra pas car il a la même longueur que tigre, étant doné que ce n'est pas une multimap, les égalité ne sont pas prises en comptent.

    for(std::map<std::string, double>::iterator it = poids.begin(); it != poids.end(); ++it)
    {
        std::cout << it->first << " pese " << it->second << " Kg." << std::endl;
    }


    std::string str("abc");
    str[1] = 'B';
    char c = str[0];
    std::cout << str << "/" << c;
    return 0;
}
