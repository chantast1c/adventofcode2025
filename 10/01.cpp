#include <sstream>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <bitset>

using namespace std;

struct Light
{
    int bits;
    bitset<13> target;
    vector<bitset<13>> buttons;
};

// Recursive function to find smallest number of buttons
vector<bitset<13>> buildSolution(const bitset<13> &target, const vector<bitset<13>> &buttons, int k = 0)
{
    int n = buttons.size();
    vector<bitset<13>> solutions;

    // loop over all subsets of size k
    for (int mask = 0; mask < (1 << n); mask++)
    {
        if (__builtin_popcount(mask) != k)
            continue;

        bitset<13> state;
        for (int i = 0; i < n; i++)
            if (mask & (1 << i))
                state ^= buttons[i];

        if (state == target)
        {
            solutions.push_back(bitset<13>(mask));
            return solutions;
        }
    }

    // if found any solutions at this k, return them
    if (!solutions.empty())
        return solutions;

    // otherwise, try next k (increase number of buttons)
    if (k < n) // only go up to n buttons
        return buildSolution(target, buttons, k + 1);

    // no solution exists
    return {};
}

int main()
{
    string token;
    vector<vector<string>> input;
    vector<Light> lights;
    fstream f = fstream("input.txt");

    while (getline(f, token))
    {
        vector<string> words;
        stringstream ss(token);
        string s;
        while (getline(ss, s, ' '))
        {
            words.push_back(s);
        }
        input.push_back(words);
    }

    for (auto &str : input)
    {
        string sequence = str[0];
        bitset<13> v;
        bitset<13> state;
        vector<bitset<13>> buttons;
        Light l;
        l.bits = sequence.length() - 2;
        int index = 0;
        for (char c : sequence)
        {
            if (c == '[' || c == ']')
                continue;
            if (c == '#')
                v.set(l.bits - 1 - index);
            index++;
        }
        l.target = v;
        l.buttons = buttons;

        for (int j = 1; j < str.size() - 1; j++)
        {
            bitset<13> state;
            string current = str[j];
            for (int i = 0; i < current.length(); i++)
            {
                if (current[i] == '(' || current[i] == ')' || current[i] == ',')
                    continue;
                else
                    state.set(l.bits - 1 - (current[i] - '0'));
            }
            l.buttons.push_back(state);
        }
        lights.push_back(l);
    }

    int totalPresses = 0;
    for (auto &l : lights)
    {
        cout << "Target state: " << l.target << endl;
        for (auto &b : l.buttons)
        {
            cout << "Buttons: " << endl;
            cout << b << endl;
        }
        cout << endl;
        vector<bitset<13>> answer = buildSolution(l.target, l.buttons);
        for (const auto &a : answer)
        {
            cout << "Solution: " << endl;
            cout << a.to_string() << endl;
            cout << a.count() << endl;
            totalPresses += a.count();
        }
        cout << endl;
    }
    cout << "Total Presses: " << totalPresses;
}