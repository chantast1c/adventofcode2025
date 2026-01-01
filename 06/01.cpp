#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <map>
#include <sstream>

using namespace std;
typedef long long ll;

bool is_all_digits(const string &str)
{
    if (str.empty())
    {
        return false;
    }
    for (char c : str)
    {
        if (!isdigit(c))
        {
            return false;
        }
    }
    return true;
}

ll result(string op, vector<string> &values)
{
    if (op == "*")
    {
        ll product = 1;
        for (string v : values)
        {
            if (is_all_digits(v))
            {
                product *= stoll(v);
            }
        }
        return product;
    }
    else
    {
        ll sum = 0;
        for (string v : values)
        {
            if (is_all_digits(v))
            {
                sum += stoll(v);
            }
        }
        return sum;
    }
}

int main()
{
    long long total = 0;
    ifstream f = ifstream("input.txt");
    vector<vector<string>> input;
    string token;
    while (getline(f, token))
    {
        stringstream ss(token);
        vector<string> values;
        while (ss >> token)
        {
            values.push_back(token);
        }
        input.push_back(values);
    }

    vector<vector<string>> results;
    int rows = input.size();
    int cols = input[0].size();
    for (int col = 0; col < cols; col++)
    {
        vector<string> current;
        for (int row = rows - 1; row >= 0; row--)
        {
            current.push_back(input[row][col]);
        }
        results.push_back(current);
    }

    for (int i = 0; i < results.size(); i++)
    {
        total += result(results[i][0], results[i]);
    }
    cout << total;
}