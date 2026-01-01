#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <limits>
#include <cmath>
#include <algorithm>
#include <unordered_map>

using namespace std;

typedef long long ll;
struct Point
{
    int x, y, z;
};
struct Edge
{
    float length;
    int first, second;
};
struct DSU
{
    vector<int> parent;
    vector<int> sizes;

    DSU(int n)
    {
        parent.resize(n);
        sizes.assign(n, 1);
        for (int i = 0; i < n; i++)
        {
            parent[i] = i;
        }
    }

    int find(int x)
    {
        return parent[x] == x ? x : find(parent[x]);
    }

    bool unionSets(int x, int y, int full)
    {
        x = find(x);
        y = find(y);
        if (x == y)
            return false;
        if (sizes[x] < sizes[y])
            swap(x, y);
        parent[y] = x;
        if (sizes[x] + sizes[y] >= full)
            return true;
        sizes[x] += sizes[y];
        return false;
    }
};

float distance(Point &p1, Point &p2)
{
    double dx = static_cast<double>(p2.x - p1.x);
    double dy = static_cast<double>(p2.y - p1.y);
    double dz = static_cast<double>(p2.z - p1.z);

    return sqrt(dx * dx + dy * dy + dz * dz);
}

int main()
{
    ifstream f("input.txt");
    string token;
    vector<Point> input;
    vector<Edge> edges;
    while (getline(f, token))
    {
        vector<int> values;
        stringstream ss(token);
        string v;
        while (getline(ss, v, ','))
        {
            values.push_back(stoi(v));
        }
        Point p;
        p.x = values[0];
        p.y = values[1];
        p.z = values[2];
        input.push_back(p);
    }

    for (int i = 0; i < input.size(); i++)
    {
        for (int j = i + 1; j < input.size(); j++)
        {
            Edge e;
            e.length = distance(input[i], input[j]);
            e.first = i;
            e.second = j;
            edges.push_back(e);
        }
    }

    sort(edges.begin(), edges.end(), [](const Edge &a, const Edge &b)
         { return a.length < b.length; });

    DSU dsu = DSU(input.size());
    for (int i = 0; i < edges.size(); i++)
    {
        int left = edges[i].first;
        int right = edges[i].second;
        if (dsu.unionSets(left, right, input.size()))
        {
            printf("Last pair: ([%d,%d,%d],[%d,%d,%d])\nAnswer: %d", input[left].x, input[left].y, input[left].z, input[right].x, input[right].y, input[right].z, input[left].x * input[right].x);
            break;
        }
    }

    sort(dsu.sizes.begin(), dsu.sizes.end(), greater<int>());
}