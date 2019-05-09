#include <iostream>
#include <string>
#include <vector>
#include <utility> //std::forward()
#include <initializer_list>

// Utilisation des fonctions variadiques

template<class T>
void funcVector(std::vector<T> listArg)
{
    for(auto i : listArg)
    {
        std::cout << i << std::endl;
    }
}

template<class T>
void semFuncVector(T&& arg) //le double && permet de faire un move semantic (convertir une Rvalue en une Lvalue)
{
    funcVector(std::forward<T>(arg)); //forward permet de simuler un object de type <T> ayant la valeur (arg)
}

void func(){} // IMPORTANT Lors d'une itilisation recurcive la fonction surchargée permettant l'arrêt de la réittération doit être déclarée avant la fonction utilisant la recursion
template<typename T, typename... Args>
void func(T t, Args... args)
{
    std::cout << t << std::endl;
    func(args...);
}

template<typename T, typename U> // ou typename... U
void funcConstructor(T fn, U arg) // ou U... arg
{
    fn(arg); // ou (arg...)
}

void test(int x)
{
    std::cout << "Uitlisation de la fonction test, valeur du parametre : " << x << std::endl;
}


class MyClass
{
public:

    MyClass(){m_val = 110;}

    void ClassFunc(int arg)
    {
        std::cout << "Utilisation de la methode parametre : " << arg << std::endl;
    }

    int getValue() const
    {
        std::cout << "sydgkejfnjdsfb";
        return m_val;
    }

private:
    int m_val;
};

template<typename T, typename U>
void funcConst2(T fn, U &obj, int arg)
{
    (obj.*(fn))(arg);
}

template<class C>
void forwarding(C &&obj)
{
    std::cout << "Utilisation d'un move semantic, valeur : " << std::forward<C>(obj) << std::endl;
}


    void fonctionCible(int a, int b, char c, char d)
    {
        std::cout << "Appel fonctionCible, valeur des paramètre : " << a << " " << b << " "
                                                                    << c << " " << d << std::endl;
    }

    template<typename T, typename... Args>
    void starter(T fn, Args... args)
    {
        fn(args...);
    }

int main()
{
    std::vector<char> vectStr = {'a', 'b', 'c'};

    std::cout << "Utilisation de fonction SANS move semantic" << std::endl;
    funcVector(vectStr);
    funcVector({1,2,3,4,5});  //intialialisator_list ??

    std::cout << "Utilisation de fonction AVEC move semantic" << std::endl;
    semFuncVector(vectStr);
    //semFuncVector({1,2,3,4,5});

    std::cout << "Utilisation de la fonction avec multi arg" << std::endl;
    func(1,2,3,4,5.0,'a','b','c','d', "string");

    MyClass objet;
    funcConst2(&MyClass::ClassFunc, objet, 2);
    objet.ClassFunc(3);
    forwarding(objet.getValue);


    funcConstructor(test, 3);

    starter(fonctionCible, 1, 2, 'a', 'b');
    int x(4);
    starter(func<int,decltype(x), std::string>, 3, x, "str");     //  Il est obligatoire de préciser le type des arguments entre <> si la fonction cible est un template

    return 0;
}
