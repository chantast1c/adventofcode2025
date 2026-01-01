#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <map>
#include <sstream>

using namespace std;

int main()
{
    int total = 0;
    ifstream f = ifstream("input.txt");
    vector<string> input;
    string token, current;
    while (getline(f, token))
    {
        if (token.empty())
        {
            if (!current.empty())
            {
                input.push_back(current);
                current.clear();
            }
        }
        else
            current += token + "\n";
    }

    if (!current.empty())
    {
        input.push_back(current);
    }
    vector<pair<long long, long long>> ranges;
    stringstream ss(input[0]);
    while (getline(ss, token))
    {
        int dash = token.find('-');
        long long begin = stoll(token.substr(0, dash));
        long long end = stoll(token.substr(dash + 1));
        ranges.push_back(make_pair(begin, end));
    }
    stringstream dd(input[1]);
    while (getline(dd, token))
    {
        long long value = stoll(token);
        for (auto p : ranges)
        {
            if (value >= p.first && value <= p.second)
            {
                total++;
                break;
            }
        }
    }
    cout << total;
}