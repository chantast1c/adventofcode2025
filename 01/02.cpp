#include <fstream>
#include <iostream>
#include <string>
using namespace std;

int main()
{
    ifstream f = ifstream("input.txt");
    string line;
    int current = 50;
    int pw = 0;
    while (getline(f, line))
    {
        char direction = line[0];
        int amount = stoi(line.substr(1));
        if (direction == 'L')
        {
            while (amount > 0)
            {
                if (current - 1 == 0)
                    pw++;

                if (current - 1 < 0)
                {
                    current = 99;
                    amount--;
                }
                else
                {
                    current--;
                    amount--;
                }
            }
        }
        else
        {
            while (amount > 0)
            {
                if (current == 99)
                {
                    pw++;
                }
                if (current + 1 > 99)
                {
                    current = 0;
                    amount--;
                }
                else
                {
                    current++;
                    amount--;
                }
            }
        }
    }
    cout << pw;
}