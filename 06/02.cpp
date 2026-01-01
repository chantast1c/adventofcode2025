#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <map>
#include <sstream>

using namespace std;
typedef long long ll;

ll result(vector<string> vals)
{
    ll prod = 1;
    ll sum = 0;
    if (vals.back() == "*")
    {
        for (int i = 0; i < vals.size() - 1; i++)
        {
            prod *= stoll(vals[i]);
        }
        return prod;
    }
    else
    {
        for (int i = 0; i < vals.size() - 1; i++)
        {
            sum += stoll(vals[i]);
        }
        return sum;
    }
    return 0;
}

int main()
{
    ll total = 0;
    ifstream f = ifstream("sample.txt");
    vector<string> nums;
    string s;
    while (getline(f, s))
    {
        nums.push_back(s);
    }

    vector<vector<string>> results;
    for (int col = 0; col < nums[0].size(); col++)
    {
        // problem always starts in column where operator exists
        char op = nums.back()[col];
        // find next set
        if (op != '+' && op != '*')
            continue;
        // problem start
        vector<string> values;
        int c = col;
        while (c < nums[0].size())
        {
            string val;
            bool found = false;
            for (int row = 0; row < nums.size() - 1; row++)
            {
                // found valid number, not an empty col
                if (c < nums[row].size() && isdigit(nums[row][c]))
                {
                    val += nums[row][c];
                    found = true;
                }
            }
            // found empty column, problem done
            if (!found)
            {
                break;
            }
            // push num, increment
            values.push_back(val);
            c++;
        }
        // push operator
        values.push_back(string(1, op));
        total += result(values);
    }
    cout << total;
}
