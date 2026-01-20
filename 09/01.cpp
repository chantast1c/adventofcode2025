#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>

using namespace std;

int main()
{
    ifstream f("input.txt");
    string token;
    vector<pair<int, int>> input;
    while (getline(f, token))
    {
        string line;
        stringstream ss(token);
        vector<int> values;
        while (getline(ss, line, ','))
        {
            values.push_back(stoi(line));
        }
        input.push_back(make_pair(values[0], values[1]));
    }

    for (auto s : input)
    {
        printf("[%d, %d]\n", s.first, s.second);
    }
    long long area = 0;
    for (int i = 0; i < input.size(); i++)
    {
        for (int j = i + 1; j < input.size(); j++)
        {
            long long width = abs(input[i].first - input[j].first) + 1;
            long long height = abs(input[i].second - input[j].second) + 1;
            area = max(area, height * width);
        }
    }
    cout << area;
}