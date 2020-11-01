/*
* 7. Да се напише функция, която чрез рекурсивен метод намира НОД на две числа.
*/

#include <iostream>
#include "Validation.h"

using namespace std;

unsigned int gcd(unsigned int m, unsigned int n);

int main()
{
    //get both natural numbers
    unsigned int m = getValidNumberInput<unsigned int, unsigned int>("natural number (>0)");
    unsigned int n = getValidNumberInput<unsigned int, unsigned int>("natural number (>0)");

    //and print out their GCD :)
    cout << "Greatest common divisor (GCD) of " << m << " and " << n << " is " << gcd(m, n) << "! :)\n";

    return 0;
}

//classical euclidian algorithm boy
//we won't be proving its validity, it's been done thousands of years ago :P
unsigned int gcd(unsigned int m, unsigned int n)
{
    return n == 0 ? m : gcd(n, m % n);
}