#pragma once
using namespace std;

template <typename T, typename U>
T getValidNumberInput(string placeholder = "decimal number")
{
    //it will all be double initially, didn't really have the time to optimize that and get rid of the "implicit double to T conversion" warning
    double input;
    cout << "Enter "<< placeholder <<": ";

    while (!(cin >> input) || abs(input) > numeric_limits<U>::max())
    {
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "Invalid input!\nEnter decimal number: ";
    }


    return input;
}