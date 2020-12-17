#include "Mode.h"
#include <iostream>

mode::Normal::Normal()
{
    std::cout << "Henlo, world!\n";
}

mode::Normal::~Normal()
{
    std::cout << "Henlo, world!\n";
}

void mode::Normal::init() const
{
    std::cout << "Henlo, world!\n";
}

void mode::Normal::exit() const
{
    std::cout << "Henlo, world!\n";
}
