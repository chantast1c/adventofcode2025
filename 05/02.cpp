#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <map>
#include <algorithm>
#include <sstream>

using namespace std;

int main()
{
    long long total = 0;
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

    sort(ranges.begin(), ranges.end());
    vector<pair<long long, long long>> merged;
    merged.push_back(ranges[0]);
    for (int i = 0; i < ranges.size(); i++)
    {
        auto &last = merged.back();
        auto &curr = ranges[i];
        if (curr.first <= last.second)
        {
            last.second = max(last.second, curr.second);
        }
        else
            merged.push_back(curr);
    }
    for (auto p : merged)
    {
        total += p.second - p.first + 1;
    }
    cout << total;
}