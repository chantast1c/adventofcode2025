#include <fstream>
#include <string>
#include <vector>
#include <iostream>
#include <stack>
#include <algorithm>
#include <chrono>

using namespace std;

vector<string> input;
vector<vector<long long>> memo;

long long dfs(int row, int col)
{
    if (row + 1 >= input.size())
        return 1;

    if (memo[row][col] != -1)
        return memo[row][col];

    long long result;
    if (input[row][col] == '^')
    {
        result = dfs(row + 1, col + 1) + dfs(row + 1, col - 1);
    }
    else
    {
        result = dfs(row + 1, col);
    }
    return memo[row][col] = result;
}

int main()
{

    long long total = 0;
    fstream f = fstream("input.txt");
    string line;
    while (getline(f, line))
    {
        input.push_back(line);
    }
    int start;
    vector<pair<int, int>> visited;
    for (int col = 0; col < input[0].length(); col++)
    {
        if (input[0][col] == 'S')
        {
            start = col;
        }
    }

    memo.assign(input.size(), vector<long long>(input[0].size(), -1));
    total = dfs(0, start);
    cout << total;
}