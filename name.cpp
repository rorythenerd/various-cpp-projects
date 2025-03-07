#include <iostream>

int main() {
    std::string fullname = "Gracie Bao";
    std::string firstname = fullname.substr(0, 6);
    std::string lastname = fullname.substr(7, 10);
    std::cout << "The full name is: " << fullname << '\n';
    std::cout << "The first name is: " << firstname << '\n';
    std::cout << "The last name is: " << lastname << '\n';
}
