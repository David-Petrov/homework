/**
* Въведете числата x от тип double и n от тип int. Да се напише програма, която
* намира стойността на израза чрез рекурсия:
* sum = ( …(((x + 2)x + 3)x + 4)x +… + (n-1))x + n;
*/

#include <iostream>
#include "Validation.h"

using namespace std;

double perform(double x, int n);

int main()
{
    //get valid double and integer
    double x = getValidNumberInput<double, double>("x (decimal)");
    int n = getValidNumberInput<int, int>("n (int, > 1)");

    //I SAID A VALID INTEGER (for the purpose of our assignment, of course :D)
    while (n < 2)
    {
        cout << "Invalid input (must be n > 1)!";
        n = getValidNumberInput<int, int>();
    }

    //print out the results
    cout << "Expression value: " << perform(x, n) << "\n";

    return 0;
}

double perform(double x, int n)
{
    //we've reached the endpoint, simply multiply x by 1
    if (n == 1)
    {
        return 1.0;
    }

    //keep expecting the result of the innermost iteration ^
    return x * perform(x, n - 1) + n;
}