#include <iostream>
#include <string>
#include <utility> // Pour utiliser pair
#include <tuple> //Pour utiliser tuple


struct Human {
    int age { 0 };
    std::string name { "noname" };
};

int main()
{

    //**************************TYPE PERSONNALISE**************************************
    using my_type = int; // on crée un nouveau type appelé my_type comme étant un integer
    // maintenant je peut ecrire my_type A = 2 ce qui équivaut à int A = 2
    std::cout << std::boolalpha;
    std::cout << std::is_same<my_type, int>::value << std::endl;


    //****************************STRUCT*************************************************
    Human alpha ();                    // contient 0 et "noname"
    Human bravo ( 12 );                // contient 12 et "noname"
    Human charlie ( 12, "my name" );   // contient 12 et "my name"

    Human delta { "your name" };       // invalide, impossible d'intialiser "age" avec une chaine
    Human echo { 12, "his name", 12 }; // invalide, trop d'arguments


    //***********************************PAIR**********************************************
    const auto p = std::make_pair(1, 'a');
    std::cout << p.first << ' ' << p.second << std::endl;


    //***********************************TUPLE*******************************************
    const auto t = std::make_tuple(1, 1.0, 'a', "hello");
    std::cout << std::get<0>(t) << ' ' << std::get<1>(t) << ' '
        << std::get<2>(t) << ' ' << std::get<3>(t) << std::endl;

    int i {};
    double d {};
    std::string s {};
    std::tie(i, d, std::ignore, s) = std::make_tuple(12, 12.34, 'a', "hello");
    std::cout << i << std::endl;
    std::cout << d << std::endl;
    std::cout << s << std::endl;

    return 0;
}
