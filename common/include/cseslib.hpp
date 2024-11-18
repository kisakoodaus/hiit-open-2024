#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>
#include <set>

using namespace std;

#define MAX_SIZE 50000000

typedef long long ll;

string _az = "abcdefghijklmnopqrstuvwxyz";
string _AZ = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
string _09 = "0123456789";

char buffer[MAX_SIZE];
int s, k;

bool ready = false;

[[noreturn]] void fail()
{
    puts("0");
    exit(0);
}

void init()
{
    s = fread(buffer, 1, MAX_SIZE, stdin);
    ready = true;
}

void read_space()
{
    if (k == s)
        fail();
    if (buffer[k] != 32)
        fail();
    k++;
}

void read_newline()
{
    if (k == s)
        fail();
    if (buffer[k] != 10)
        fail();
    k++;
}

string read_str()
{
    if (!ready)
        init();
    string token;
    while (k < s && buffer[k] >= 33 && buffer[k] <= 126)
    {
        token += buffer[k++];
    }
    if (token == "")
        fail();
    return token;
}

ll read_int()
{
    try
    {
        string str = read_str();
        size_t read;
        ll x = stoll(str, &read);
        if (str.size() != read)
            fail();
        return x;
    }
    catch (...)
    {
        fail();
    }
}

double read_dbl()
{
    try
    {
        string str = read_str();
        size_t read;
        double x = stod(str, &read);
        if (str.size() != read)
            fail();
        return x;
    }
    catch (...)
    {
        fail();
    }
}

vector<string> read_strs(int n, int minl, int maxl, string chars)
{
    int c[128] = {0};
    for (auto u : chars)
        c[int(u)] = 1;
    vector<string> v;
    if (n == 0)
    {
        while (true)
        {
            string x = read_str();
            if (x.size() < unsigned(minl) || x.size() > unsigned(maxl))
                fail();
            for (auto u : x)
                if (!c[int(u)])
                    fail();
            v.push_back(x);
            if (k == s)
                fail();
            if (buffer[k] == 10)
            {
                k++;
                break;
            }
            if (buffer[k] == 32)
            {
                k++;
                continue;
            }
            fail();
        }
    }
    else
    {
        for (int i = 0; i < n; i++)
        {
            string x = read_str();
            if (x.size() < unsigned(minl) || x.size() > unsigned(maxl))
                fail();
            for (auto u : x)
                if (!c[int(u)])
                    fail();
            v.push_back(x);
            if (i != n - 1)
                read_space();
        }
        read_newline();
    }
    return v;
}

string read_str(int minl, int maxl, string chars)
{
    string x = read_str();
    if (x.size() < unsigned(minl) || x.size() > unsigned(maxl))
        fail();
    int c[128] = {0};
    for (auto u : chars)
        c[int(u)] = 1;
    for (auto u : x)
        if (!c[int(u)])
            fail();
    read_newline();
    return x;
}

vector<ll> read_ints(int n, ll minv, ll maxv)
{
    vector<ll> v;
    if (n == 0)
    {
        while (true)
        {
            ll x = read_int();
            if (x < minv || x > maxv)
                fail();
            v.push_back(x);
            if (k == s)
                fail();
            if (buffer[k] == 10)
            {
                k++;
                break;
            }
            if (buffer[k] == 32)
            {
                k++;
                continue;
            }
            fail();
        }
    }
    else
    {
        for (int i = 0; i < n; i++)
        {
            ll x = read_int();
            if (x < minv || x > maxv)
                fail();
            v.push_back(x);
            if (i != n - 1)
                read_space();
        }
        read_newline();
    }
    return v;
}

ll read_int(ll minv, ll maxv)
{
    ll x = read_int();
    if (x < minv || x > maxv)
        fail();
    read_newline();
    return x;
}

vector<double> read_dbls(int n, double minv, double maxv)
{
    vector<double> v;
    if (n == 0)
    {
        while (true)
        {
            double x = read_dbl();
            if (x < minv || x > maxv)
                fail();
            v.push_back(x);
            if (k == s)
                fail();
            if (buffer[k] == 10)
            {
                k++;
                break;
            }
            if (buffer[k] == 32)
            {
                k++;
                continue;
            }
            fail();
        }
    }
    else
    {
        for (int i = 0; i < n; i++)
        {
            double x = read_dbl();
            if (x < minv || x > maxv)
                fail();
            v.push_back(x);
            if (i != n - 1)
                read_space();
        }
        read_newline();
    }
    return v;
}

double read_dbl(double minv, double maxv)
{
    double x = read_dbl();
    if (x < minv || x > maxv)
        fail();
    read_newline();
    return x;
}

void end(bool ok = false)
{
    if (!ok && k != s)
        fail();
    puts("1");
    exit(0);
}

void end_groups(vector<int> g, bool ok = false)
{
    if (!ok && k != s)
        fail();
    puts("1");
    int u = 0;
    for (auto x : g)
        u |= (1 << x);
    printf("%i\n", u);
    exit(0);
}
