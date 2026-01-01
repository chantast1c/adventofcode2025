#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <algorithm>
#include <vector>
#include <queue>

using namespace std;

int main()
{
    long long total = 0;
    ifstream f = ifstream("input.txt");
    string token;
    while (getline(f, token, '\n'))
    {
        int start = 0;
        int digitsNeeded = 12;
        string number;
        while (digitsNeeded > 0)
        {
            int max = 0;
            int left = start;
            for (int i = left; i < token.length() - digitsNeeded + 1; i++)
            {
                if (token[i] - '0' > max)
                {
                    max = token[i] - '0';
                    left = i;
                }
            }
            number += '0' + max;
            start = left + 1;
            digitsNeeded--;
        }
        cout << number << endl;
        total += stoll(number);
    }
    cout << total;
}