/**
* Assignment:
* Read integers M and N from the console, then let the user input an MxN matrix.
* Print the entries of the matrix spirally starting from the top left and proceeding to the right (then down, left, up, right again, and so on).
* Boundaries: 2 <= M, N <= 100
*
* Example input:
* 4 4
* 1 2 3 4
* 6 10 8 9
* 11 2 3 4
* 3 7 4 5
*
* Output:
* 1 2 3 4 9 4 5 4 7 3 11 6 10 8 3 2
*
* I know the solution is not the most comprehensive nor the most efficient in terms of procedure steps or execution time,
* but that was the desired algorithm I challenged myself to program for it.
*
* The main idea was to just resemble what a normal person would do:
* - start at the top left and go right until you reach the last element on the first row;
* - move start from the next index below and proceed until the end of the last column;
* - keep circulating until you've run through all ements.
*
* Now, while a human can find it relatively easy to trace the pattern, the computer needed some more clarification than I thought. :D
* The code ended up being not as straightforward or easy readable, but it has two main advantages:
* - it doesn't alter the matrix (nor instantiates a copy): the challenge was to only instruct the computer where to read from, not altering anything from the content;
* -
*
*/
#include <iostream>
#include <vector>

using namespace std;

const int directions[4][2] = {
    {0, 1},     //right
    {1, 0},     //down
    {0, -1},    //left
    {-1, 0},    //up
};

template <typename T>
T getValidNumberInput(bool displayInstructions = false, string placeholder = "decimal number");

int defaultStart[2] = { 0, 0 };
void printSpiralMatrix(vector<vector<int>> matrix, int directionIndex = 0, int* start = defaultStart);

int main()
{
    //yeah, since I guess it's gonna be humans playing around with that file
    //I just prefer to let you cycle with various examples and tests rather than restart the program for every try, so... just quit if you want to exit :D 
    while (true)
    {
        int M, N;
        do {
            M = getValidNumberInput<int>();
        } while (M < 2 || M > 100);
        do {
            N = getValidNumberInput<int>();
        } while (N < 2 || N > 100);

        vector<vector<int>> matrix = vector<vector<int>>(M);

        for (int i = 0; i < M; i++)
        {
            matrix[i] = vector<int>(N);
            for (int j = 0; j < N; j++)
            {
                cin >> matrix[i][j];
            }
        }

        //In case you'd like to verify that your input is being saved correctly
        /*cout << "\nYour matrix is:\n";
        for (int i = 0; i < M; i++)
        {
            for (int j = 0; j < N; j++)
            {
                cout << matrix[i][j] << " ";
            }
        }*/

        //print(matrix, true, 0, 0, M - 2);
        defaultStart[0] = 0;
        defaultStart[1] = 0;

        printSpiralMatrix(matrix);
        cout << '\n';
    }

    return 0;
}


void printSpiralMatrix(vector<vector<int>> matrix, int directionIndex, int* start)
{
    //get some general info in variables for easier ues
    int M = matrix.size();
    int N = matrix[0].size();
    const int* direction = directions[directionIndex];

    //make some conclusions about the direction we're moving in
    bool horizontal = direction[0] == 0; //are we moving on the x axis?
    bool rightOrDown = directionIndex < 2; //are we moving in a "regular" (right or down) or "reversed" (left or up) direction

    //That's the most crucial part - the minimalistic determining core,
    //which parses the strategy for the current iteration based solely on the start coordinates and the direction
    //Yeah, big deal, it's actually pretty standart symmetric coordinate mirroring :D 
    //The whole pain was caused due to the offsets, which, I mention again, are a flaw of comprehenensiveness for this algorithm, but hey
    //I just really insisted on instructing the processor to do EXACTLY WHAT I WOULD DO! :D 
    int end[2] = { 0 };
    switch (directionIndex)
    {
    case 0: //right
        end[0] = start[0];
        end[1] = (N - 1 - start[1]);
        break;

    case 1: //down
        end[0] = (M - 1 - start[0]) + 1; //+1 offset because of the start, which is not symmetric to the end in this case :D
        end[1] = start[1];
        break;
    case 2: //left
        end[0] = start[0];
        end[1] = (N - 1 - start[1]) - 1;//-1 offset for the same reason as above
        break;
    case 3: //up
        end[0] = (M - 1 - start[0]);
        end[1] = start[1];
        break;
    }

    //if we've reached an overlap, it's time to stop. Stop... STOP! STAAAAHP, PLEZ. Damn it! :D
    //This mechanism was a painful discovery, and it doesn't even work properly when either M or N is equal to 1... Which, fortunately, is excluded from the task.
    if (direction[0] * (start[0] - end[0]) > 0 || direction[1] * (start[1] - end[1]) > 0)
        return;

    //let's finally do what we came from - print the entries! :D 
    int* iterator = start;
    while (!(iterator[0] == end[0] && iterator[1] == end[1]))
    {
        cout << matrix[iterator[0]][iterator[1]] << " ";

        //increment our composed iterator
        iterator[0] += direction[0];
        iterator[1] += direction[1];
    }

    //additionally print the end as well, since the loop does not execute for that last case
    cout << matrix[end[0]][end[1]] << " ";

    //prepare the data for the next iteration
    int nextDirectionIndex = (directionIndex + 1) % 4;
    int nextStart[2] = {
        end[0] + directions[nextDirectionIndex][0],
        end[1] + directions[nextDirectionIndex][1],
    };

    //and just keep swimming :)
    printSpiralMatrix(matrix, nextDirectionIndex, nextStart);
}

template <typename T>
T getValidNumberInput(bool displayInstructions, string placeholder)
{
    T input;

    if (displayInstructions)
        cout << "Enter " << placeholder << ": ";

    while (!(cin >> input))
    {
        cin.clear();
        cin.ignore(1000, '\n');

        if (displayInstructions)
            cout << "Invalid input!\nEnter " << placeholder << ": ";
    }

    return input;
}