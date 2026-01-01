#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip>
#include <string>

using namespace std;

ifstream f = ifstream("input.txt");
vector<vector<char>> input;
string token;

bool inBounds(vector<vector<char>> &mat, int x, int y)
{
    if (x < 0)
        return false;
    if (y < 0)
        return false;
    if (x >= mat.size())
        return false;
    if (y >= mat[0].size())
        return false;
    return true;
}

bool getAnds(vector<vector<char>> &mat, int x, int y)
{
    int count = 0;
    for (int i = x - 1; i <= x + 1; i++)
    {
        for (int j = y - 1; j <= y + 1; j++)
        {
            if (i == x && j == y)
                continue;
            if (inBounds(mat, i, j) && mat[i][j] == '@')
                ++count;
        }
    }
    if (count < 4)
    {
        return true;
    }
    return false;
}

int main()
{
    int count = 0;
    while (getline(f, token))
    {
        vector<char> line;
        for (int i = 0; i < token.length(); i++)
        {
            line.push_back(token[i]);
        }
        input.push_back(line);
    }
    bool incremented = true;
    int prev = count;
    while (incremented)
    {
        for (int i = 0; i < input.size(); i++)
        {
            for (int j = 0; j < input[0].size(); j++)
            {
                if (input[i][j] == '@')
                {
                    if (getAnds(input, i, j))
                    {
                        input[i][j] = '.';
                        count++;
                    }
                }
            }
        }
        if (count == prev)
        {
            incremented = false;
        }
        else
            prev = count;
    }
    cout << count;
}