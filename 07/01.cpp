#include <fstream>
#include <string>
#include <vector>
#include <iostream>

using namespace std;

int main()
{
    fstream f = fstream("input.txt");
    string line;
    vector<string> input;
    while (getline(f, line))
    {
        input.push_back(line);
    }
    int count = 0;
    vector<int> beams(input[0].length(), 0);
    for (int i = 0; i < input[0].length(); ++i)
    {
        if (input[0][i] == 'S')
        {
            beams[i] = 1;
        }
    }
    for (int row = 1; row < input.size(); ++row)
    {
        vector<int> nextRow(input[0].length(), 0);
        for (int col = 0; col < input[0].length(); ++col)
        {
            if (beams[col] == 1)
            {
                if (input[row][col] == '^')
                {
                    count++;
                    cout << count << endl;
                    if (col - 1 >= 0)
                    {
                        nextRow[col - 1] = 1;
                    }
                    if (col + 1 < input[0].length())
                    {
                        nextRow[col + 1] = 1;
                    }
                }
                else
                    nextRow[col] = 1;
            }
        }
        beams = nextRow;
    }
}