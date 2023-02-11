/**
 * @file functions.cpp
 * @author Maciej Jarnot (mj300741@student.polsl.pl)
 * @version 0.1
 * @date 26.01.2023
 *
 */

#include "functions.h"

std::ostream &operator<<(std::ostream &_stream, const person &_person)
{
    _stream << _person.name << " " << _person.age;
    return _stream;
}

std::istream &operator>>(std::istream &in, person &_person)
{
    in >> _person.name >> _person.age;
    return in;
}

void gap()
{
    std::cout << "\n\n----------------------------\n\n";
}

void person::setName(std::string _name)
{
    name = _name;
}

std::string person::getName()
{
    return name;
}

void person::setAge(int _age)
{
    age = _age;
}

int person::getAge()
{
    return age;
}

bool person::operator<(const person &other)
{
    if (age == other.age)
    {
        if (name == other.name)
        {
            return false;
        }
        else if (name < other.name)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    else if (age < other.age)
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool person::operator>(const person &other)
{
    if (age == other.age)
    {
        if (name == other.name)
        {
            return false;
        }
        else if (name > other.name)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    else if (age > other.age)
    {
        return true;
    }
    else
    {
        return false;
    }
}
