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
    int total = 0;
    ifstream f = ifstream("input.txt");
    string token;
    while (getline(f, token, '\n'))
    {
        int max = 0;
        int left = 0;
        int indLeft = 0;
        while (left < token.length() - 1)
        {
            if (token[left] - '0' > max)
            {
                max = token[left] - '0';
                indLeft = left;
            }
            left++;
        }
        int l = max * 10;
        max = 0;
        int right = token.length() - 1;
        while (right > indLeft)
        {
            if (token[right] - '0' > max)
            {
                max = token[right] - '0';
            }
            right--;
        }
        int r = max;
        total += (l + r);
    }
    cout << total;
}