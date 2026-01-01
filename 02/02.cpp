#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
#include <ranges>
#include <string_view>
#include <chrono> // Required for std::chrono

using namespace std;

int main()
{
    auto start = std::chrono::steady_clock::now();

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
                for (int j = half; j > 0; j--)
                {
                    if (s.length() % j != 0)
                        continue;
                    bool isVal = true;
                    string check = s.substr(0, j);
                    if (check[0] == '0')
                    {
                        continue;
                    }
                    int k = j;
                    while (k + check.length() <= s.length())
                    {
                        if (check == s.substr(k, check.length()))
                        {
                            k += check.length();
                        }
                        else
                        {
                            isVal = false;
                            break;
                        }
                    }
                    if (isVal)
                    {
                        total += i;
                        // cout << total << endl;
                        break;
                    }
                }
            }
        }
    }
    auto end = std::chrono::steady_clock::now();
    std::chrono::duration<double> elapsed_seconds = end - start;

    cout << total << endl;
    std::cout << "Elapsed time: " << elapsed_seconds.count() << " seconds" << std::endl;
}