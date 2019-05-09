    #include <iostream>
    #include <ratio>

    int main() {
        std::cout << std::ratio<1, 3>::num << std::endl;
        std::cout << std::ratio<1, 3>::den << std::endl;

        std::cout << std::ratio<2, 3>::num << " / " << std::ratio<2, 3>::den << std::endl;
        std::cout << std::ratio<4, 6>::num << " / " << std::ratio<4, 6>::den << std::endl;

        std::cout << "2/3 == 3/4 ? " << std::boolalpha;
        std::cout << std::ratio_equal<std::ratio<2, 3>, std::ratio<3, 4>>::value << std::endl;

        std::cout << "2/3 == 4/6 ? " << std::boolalpha;
        std::cout << std::ratio_equal<std::ratio<2, 3>, std::ratio<4, 6>>::value << std::endl;
    }

