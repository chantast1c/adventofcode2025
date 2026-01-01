#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
#include <ranges>
#include <string_view>

using namespace std;

int main()
{
    ifstream f = ifstream("input.txt");
    std::string token;
    long long total = 0;
    while (getline(f, token, ','))
    {
        size_t dash = token.find('-');
        if (dash != std::string::npos)
        {
            long long a = std::stoll(token.substr(0, dash));
            long long b = std::stoll(token.substr(dash + 1));
            for (long long i = a; i <= b; i++)
            {
                string s = to_string(i);
                int half = s.length() / 2;
                string first = s.substr(0, half);
                string second = s.substr(half);
                if (first[0] == '0' || second[0] == '0')
                {
                    continue;
                }
                else if (first == second)
                {
                    total += i;
                }
            }
        }
    }
    cout << total;
}