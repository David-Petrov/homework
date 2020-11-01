/*
Даден е лабиринт под формата на матрица NxM, където свободно квадратче се
отбелязва с ‘.’, а стена – с ‘-’. Намерете има ли път от квадратче 0x0 до квадратче (N1)x(M-1), движейки се в четирите основни посоки.
Пример:
Вход:
4 4
. - - .
. . - -
. - . .
. . . .
Изход:
Yes
Вход:
3 5
. - - . .
- . - - -
. . . . .
Изход:
No

*/

#include <iostream>
#include <vector>
#include "Validation.h"

using namespace std;

bool checkPath(vector<vector<char>> grid, int* start, unsigned int* end, int previousDirection);

int main()
{
    //get the boundaries of our grid nxm
    unsigned int n = getValidNumberInput<unsigned int, unsigned int>("a natural number N (> 0)");
    unsigned int m = getValidNumberInput<unsigned int, unsigned int>("a natural number M (> 0)");

    //initialize the grid
    vector<vector<char>> grid = vector<vector<char>>(n);
    //and fill it
    for (size_t i = 0; i < n; i++)
    {
        grid[i] = vector<char>(m);

        for (size_t j = 0; j < m; j++)
        {
            cin >> grid[i][j];
        }
    }

    //define our start cell
    int start[2] = { 0, 0 };
    //define our desired end cell
    unsigned int end[2] = { n - 1, m - 1 };

    //let's find out whether or not we can reach the end cell from the start cell
    cout << (checkPath(grid, start, end, NULL) ? "Yes" : "No") << '\n';

    return 0;
}

bool checkPath(vector<vector<char>> grid, int* start, unsigned int* end, int previousDirection)
{
    //just for ease - mark the current row index with i and the current column index with j
    int i = start[0];
    int j = start[1];

    //if we reached the end - congratulations! success!
    if (i == end[0] && j == end[1])
    {
        return true;
    }

    //if we're out of the grid boundaries, no need to check anything
    if (i < 0 || i >= grid.size() || j < 0 || j >= grid[0].size())
    {
        return false;
    }

    //if we reach a wall, then we return a sad false for failure
    if (grid[i][j] == '-')
    {
        return false;
    }

    //define the four next cells to check
    //note: the positioning of the next cells to check is very important - must be symmetric for us to be able to recognize the previous cell we came from!
    int nextCells[4][2] = {
        {i - 1, j}, //up
        {i, j - 1}, //left
        {i, j + 1}, //right
        {i + 1, j}, //down
    };

    //and iterate over them
    for (int k = 0; k < 4; k++)
    {
        //if we're about to check the cell we came from, don't do it
        if (previousDirection != NULL && k == 3 - previousDirection)
        {
            continue;
        }

        int next[2] = {nextCells[k][0], nextCells[k][1]};

        //let's check the neighbouring cells one by one
        if (checkPath(grid, next, end, k))
        {
            //if we found success, no need for further checking! just let everybody know!
            return true;
        }
    }

    return false;
}