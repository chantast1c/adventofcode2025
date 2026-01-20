#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>

using namespace std;

const long long DIGITS = 1000000000;

vector<pair<vector<int>, vector<int>>> vertical;
vector<pair<vector<int>, vector<int>>> horizontal;
// returns a horizontal top edge for square given pair of two points [x1, y], [x2, y]
pair<vector<int>, vector<int>> top(pair<vector<int>, vector<int>> &p)
{
    pair<vector<int>, vector<int>> upper;
    int y = min(p.first[1], p.second[1]);
    upper.first.push_back(min(p.first[0], p.second[0]));
    upper.second.push_back(max(p.first[0], p.second[0]));
    upper.first.push_back(y);
    upper.second.push_back(y);
    return upper;
}

// returns a horizontal bottom edge for a square made between the two points [x1, y], [x2, y]
pair<vector<int>, vector<int>> bottom(pair<vector<int>, vector<int>> &p)
{
    pair<vector<int>, vector<int>> lower;
    int y = max(p.first[1], p.second[1]);
    lower.first.push_back(min(p.first[0], p.second[0]));
    lower.second.push_back(max(p.first[0], p.second[0]));
    lower.first.push_back(y);
    lower.second.push_back(y);
    return lower;
}

// returns a vertical left edge for a square made between the two points [x, y1], [x, y2]
pair<vector<int>, vector<int>> left(pair<vector<int>, vector<int>> &p)
{
    pair<vector<int>, vector<int>> left;
    int x = min(p.first[0], p.second[0]);
    left.first.push_back(x);
    left.second.push_back(x);
    left.first.push_back(min(p.first[1], p.second[1]));
    left.second.push_back(max(p.first[1], p.second[1]));
    return left;
}

// returns a vertical right edge for a square made between the two points [x, y1], [x, y2]
pair<vector<int>, vector<int>> right(pair<vector<int>, vector<int>> &p)
{
    pair<vector<int>, vector<int>> right;
    int x = max(p.first[0], p.second[0]);
    right.first.push_back(x);
    right.second.push_back(x);
    right.first.push_back(min(p.first[1], p.second[1]));
    right.second.push_back(max(p.first[1], p.second[1]));
    return right;
}

// return true if rectangle intersects any vertical edges at any given Y;
// for range y1-y2, if any vertical edge exists within rectangle x1-x2, return true
// if top edge Y <= topmost horizontal Y at any range of this rectangles x1-x2, return true (out of bounds)
// if this edge x1-x2 range exceeds the biggest horizontal edge, return true -- out of bounds

bool invalid(pair<vector<int>, vector<int>> &points)
{
    auto upper = top(points);
    auto lower = bottom(points);
    auto leftmost = left(points);
    auto rightmost = right(points);

    // return true if any vertical edge intersects this rectangle
    for (auto &v : vertical)
    {
        int startY = min(v.first[1], v.second[1]);
        int endY = max(v.first[1], v.second[1]);
        if (v.first[0] > upper.first[0] && v.first[0] < upper.second[0])
        {
            if ((startY <= upper.first[1] && endY >= upper.first[1]) || (startY <= upper.second[1] && endY >= upper.second[1]))
            {
                return true;
            }
        }
    }
    // return true if any horizontal edge intersects this rectangle
    for (auto &h : horizontal)
    {
        int startX = min(h.first[0], h.second[0]);
        int endX = max(h.first[0], h.second[0]);
        if (h.first[1] > upper.first[1] && h.first[1] < lower.first[1])
        {
            if (startX <= upper.first[0] && endX > upper.first[0])
            {
                return true;
            }
        }
    }

    // There must be at least 1 horizontal edge above/below and 1 vertical edge left/right for a valid rectangle to be inside the polygon
    bool above = false;
    bool below = false;
    bool left = false;
    bool right = false;
    for (auto &h : horizontal)
    {
        if (min(h.first[1], h.second[1]) <= upper.first[1] && min(h.first[0], h.second[0]) >= upper.first[0] && min(h.first[0], h.second[0]) <= upper.second[0])
        {
            above = true;
        }
        if (max(h.first[1], h.second[1]) >= lower.first[1] && min(h.first[0], h.second[0]) >= lower.first[0] && min(h.first[0], h.second[0]) <= lower.second[0])
        {
            below = true;
        }
        if (above && below)
        {
            break;
        }
    }
    for (auto &v : vertical)
    {
        if (min(v.second[0], v.first[0]) <= upper.first[0] && min(v.first[1], v.second[1]) >= upper.first[1] && min(v.first[1], v.second[1]) <= lower.first[1])
        {
            left = true;
        }
        if (max(v.second[0], v.first[0]) >= upper.second[0] && min(v.first[1], v.second[1]) >= upper.second[1] && min(v.first[1], v.second[1]) <= lower.second[1])
        {
            right = true;
        }
        if (left && right)
        {
            break;
        }
    }
    if (!above || !below || !left || !right)
    {
        return true;
    }
    return false;
}

int main()
{
    ifstream f("sample.txt");
    string token;
    vector<vector<int>> input;
    long long area = 0;
    while (getline(f, token))
    {
        string line;
        stringstream ss(token);
        vector<int> values;
        while (getline(ss, line, ','))
        {
            values.push_back(stoi(line));
        }
        input.push_back(values);
    }

    for (int i = 0; i + 1 < input.size(); i++)
    {
        if (input[i][0] == input[i + 1][0])
            vertical.push_back({input[i], input[i + 1]});
    }
    if (input[0][0] == input[input.size() - 1][0])
    {
        vertical.push_back({input[0], input[input.size() - 1]});
    }
    for (int i = 0; i + 1 < input.size(); i++)
    {
        if (input[i][1] == input[i + 1][1])
        {
            horizontal.push_back({input[i], input[i + 1]});
        }
    }

    for (int i = 0; i < input.size(); i++)
    {
        for (int j = i + 1; j < input.size(); j++)
        {
            pair<vector<int>, vector<int>> points = make_pair(input[i], input[j]);
            if (!invalid(points))
            {
                printf("PointA: [%d, %d] PointB: [%d, %d] ", input[i][0], input[i][1], input[j][0], input[j][1]);
                long long width = abs(input[i][0] - input[j][0]) + 1;
                printf("Width: %d ", width);
                long long height = abs(input[i][1] - input[j][1]) + 1;
                printf("Height: %d ", height);
                printf("Area: %llu\n", width * height);
                area = max(area, width * height);
            }
            else
            {
                printf("PointA: [%d, %d,] PointB: [%d, %d] invalid\n", points.first[0], points.first[1], points.second[0], points.second[1]);
            }
        }
    }
    printf("%llu", area);
}
