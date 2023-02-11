/**
 * @file bidirectional-list.cpp
 * @author Maciej Jarnot (mj300741@student.polsl.pl)
 * @version 0.1
 * @date 26.01.2023
 *
 */

#include "functions.h"

int main()
{
    // list<std::string> testList;
    // testList.push_back("123");
    // testList.push_back("234");
    // testList.push_back("r");
    // testList.push_back("e");
    // testList.push_back("d");
    // testList.push_back("c");
    // testList.push_back("b");
    // testList.push_back("a");

    // for(auto &a : testList){
    //     a += "ad";
    //     std::cout << a << "\n";
    // }

    // list<std::string> lista = std::move(testList);
    // testList.display();
    // gap();
    // lista.display();
    // gap();

    // list<person> people;
    // people.push_back({"Kamil", 4});
    // people.push_back({"Maciej", 8});
    // people.push_back({"Adam", 16});
    // people.push_front({});
    // people.push_front({});
    // people.push_front({});
    // people.display();
    // std::cout << people.front() << "\n";
    // people.search({"Jan Kowalski", 32});
    // people.sort();
    // gap();
    // people.pop_back();
    // people.pop_front();
    // people.display();
    // gap();
    list<person> pepl;
    pepl.open("pepl.txt");
    // for(auto a : pepl){
    //     a.setAge(12);
    //     std::cout << a << "\n";
    // }
    // pepl.display();
    // std::cout << people.empty();

    menu(pepl);

    // pepl.display();
    // gap();
    // std::cout << "Deleted element: " << pepl.pop_specified_position(4) << "\n";
    // pepl.display();

    return 0;
}