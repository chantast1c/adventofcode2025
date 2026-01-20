#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <map>

using namespace std;

struct Point
{
    int x;
    int y;
};

struct Vertical
{
    int start;
    int end;
    int x;
    string direction;
};

struct Horizontal
{
    int start;
    int end;
    int y;
    string direction;
};

long long area = 0;
map<pair<int, int>, char> border;
vector<Vertical> vertical;
vector<Horizontal> horizontal;

void outline(Point &first, Point &second, map<pair<int, int>, char> &border)
{
    // outline along y axis
    if (first.x == second.x)
    {
        int start = min(first.y, second.y);
        int end = max(first.y, second.y);
        // top -> bottom, outside to the right (x+1)
        if (first.y < second.y)
        {
            vertical.push_back({start, end, first.x, "DOWN"});
            for (int y = first.y + 1; y < second.y; y++)
            {
                border[{first.x + 1, y}] = '*';
            }
        }
        // bottom -> top, outside to the left (x-1)
        else
        {
            vertical.push_back({start, end, first.x, "UP"});
            for (int y = first.y - 1; y > second.y; y--)
            {
                border[{first.x - 1, y}] = '*';
            }
        }
    }

    if (first.y == second.y)
    {
        int start = min(first.x, second.x);
        int end = max(first.x, second.x);
        // left -> right, outside is (y-1)
        if (first.x < second.x)
        {
            horizontal.push_back({start, end, first.y, "RIGHT"});
            for (int x = first.x + 1; x < second.x; x++)
            {
                border[{x, first.y - 1}] = '*';
            }
        }
        // right -> left, outside is (y+1)
        else
        {
            horizontal.push_back({start, end, first.y, "LEFT"});
            for (int x = first.x - 1; x > second.x; x--)
            {
                border[{x, first.y + 1}] = '*';
            }
        }
    }
}

bool isValid(Point &first, Point &second, map<pair<int, int>, char> &border)
{
    Point topleft;
    Point topright;
    Point bottomright;
    Point bottomleft;
    int minX = min(first.x, second.x);
    int maxX = max(first.x, second.x);
    int minY = min(first.y, second.y);
    int maxY = max(first.y, second.y);
    topleft.x = minX;
    topleft.y = minY;
    topright.x = maxX;
    topright.y = minY;
    bottomright.x = maxX;
    bottomright.y = maxY;
    bottomleft.x = minX;
    bottomleft.y = maxY;
    // traverse top left -> top right
    for (int x = topleft.x; x <= topright.x; x++)
    {
        if (border[{x, topleft.y}] == '*')
        {
            // printf("[%d, %d] [%d, %d] top border invalid at [%d, %d]\n", first.x, first.y, second.x, second.y, x, topleft.y);
            return false;
        }
    }
    // traverse top right -> bottom right
    for (int y = topright.y; y <= bottomright.y; y++)
    {
        if (border[{topright.x, y}] == '*')
        {
            // printf("[%d, %d] [%d, %d] right border invalid at [%d, %d]\n", first.x, first.y, second.x, second.y, topright.x, y);
            return false;
        }
    }
    // traverse bottom right -> bottom left
    for (int x = bottomright.x; x >= bottomleft.x; x--)
    {
        if (border[{x, bottomright.y}] == '*')
        {
            // printf("[%d, %d] [%d, %d] bottom border invalid at [%d, %d]\n", first.x, first.y, second.x, second.y, x, bottomright.y);
            return false;
        }
    }
    // traverse bottom left -> top left
    for (int y = bottomleft.y; y >= topleft.y; y--)
    {
        if (border[{bottomleft.x, y}] == '*')
        {
            // printf("[%d, %d] [%d, %d] left border invalid at [%d, %d]\n", first.x, first.y, second.x, second.y, bottomleft.x, y);
            return false;
        }
    }
    return true;
}

long long getArea(Point &a, Point &b)
{
    return (abs(a.x - b.x) + 1) * (abs(a.y - b.y) + 1);
}

int main()
{
    ifstream f("input.txt");
    string token;
    vector<Point> input;
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
        Point a;
        a.x = values[0];
        a.y = values[1];
        input.push_back(a);
    }
    for (int i = 0; i < input.size() - 1; i++)
    {
        Point a = input[i];
        Point b = input[i + 1];
        outline(a, b, border);
    }
    Point a = input[input.size() - 1];
    Point b = input[0];
    outline(a, b, border);

    // mark corners in outer edge
    for (auto &e : vertical)
    {
        if (e.direction == "UP")
        {
            border[{e.x - 1, e.start}] = '*';
            border[{e.x - 1, e.end}] = '*';
        }
        else
        {
            border[{e.x + 1, e.start}] = '*';
            border[{e.x + 1, e.end}] = '*';
        }
    }

    // mark corners in outer edge
    for (auto &e : horizontal)
    {
        if (e.direction == "RIGHT")
        {
            border[{e.start, e.y - 1}] = '*';
            border[{e.end, e.y - 1}] = '*';
        }
        else
        {
            border[{e.start, e.y + 1}] = '*';
            border[{e.start, e.y + 1}] = '*';
        }
    }

    // remove any "border" squares that lie on the actual polygon perimeter
    for (auto &h : horizontal)
    {
        for (int x = h.start; x <= h.end; x++)
        {
            border.erase({x, h.y});
        }
    }
    for (auto &v : vertical)
    {
        for (int y = v.start; y <= v.end; y++)
        {
            border.erase({v.x, y});
        }
    }

    // check all possible squares
    int count = 0;
    for (int i = 0; i < input.size(); i++)
    {
        for (int j = i + 1; j < input.size(); j++)
        {
            Point a = input[i];
            Point b = input[j];
            printf("\rChecking rectangle %d", count);
            if (isValid(a, b, border))
            {
                // printf("Valid rectangle found between: [%d, %d] [%d, %d]\n", a.x, a.y, b.x, b.y);
                area = max(area, getArea(a, b));
            }
            count++;
        }
    }
    printf("\nBiggest: %llu", area);
}
