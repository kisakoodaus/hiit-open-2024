#include <iostream>
#include <vector>
#include <queue>
#include <cassert>

using namespace std;

int median(int a, int b, int c)
{
    if (a < b)
    {
        if (b < c)
            return b;
        if (a < c)
            return c;
        return a;
    }
    else
    {
        if (a < c)
            return a;
        if (b < c)
            return c;
        return b;
    }
}

void hiit_sort_assert_pathological(int *arr, int low, int high)
{
    if (high - low > 1)
    {

        int pivot = median(arr[low], arr[low + (high - low) / 2], arr[high - 1]);
        int a = low;
        int b = high - 1;
        while (true)
        {
            while (arr[a] < pivot)
                a++;
            while (arr[b] > pivot)
                b--;
            if (a >= b)
                break;
            swap(arr[a], arr[b]);
            a++;
            b--;
        }
        assert(a + 2 >= high);
        hiit_sort_assert_pathological(arr, low, a);
        hiit_sort_assert_pathological(arr, a, high);
    }
}

void foo(std::vector<std::vector<int>> &is_greater_than, size_t *indices, int low, int high)
{
    if (high - low > 1)
    {
        // Ensure that the elements among which we choose the median are ordered
        size_t a = indices[low + (high - low) / 2];
        size_t b = indices[high - 1];
        is_greater_than[b].push_back(a);

        for (int i = low; i < high; i++)
        {
            if (indices[i] != a && indices[i] != b)
                is_greater_than[a].push_back(indices[i]);
        }

        // Now a and b are the two largest elements in the array, in that order.
        // The partitioning now swaps a with the second-to-last element.
        swap(indices[low + (high - low) / 2], indices[high - 2]);

        // The element larger than median is on the right. No need to recurse there.
        foo(is_greater_than, indices, low, high - 2);
    }
}

int main()
{
    int n;
    cin >> n;

    std::vector<std::vector<int>> is_greater_than(n);
    std::vector<size_t> indices(n);
    for (int i = 0; i < n; i++)
        indices[i] = i;
    foo(is_greater_than, indices.data(), 0, n);

    // Find the topological order
    std::vector<int> in_counts(n);
    for (int i = 0; i < n; i++)
    {
        for (int v : is_greater_than[i])
        {
            if (v != i)
                in_counts[v]++;
        }
    }
    std::queue<int> q;
    for (int i = 0; i < n; i++)
    {
        if (in_counts[i] == 0)
            q.push(i);
    }
    int largest = n;
    std::vector<int> res(n);
    while (!q.empty())
    {
        int i = q.front();
        q.pop();
        res[i] = largest--;
        for (int v : is_greater_than[i])
        {
            if (--in_counts[v] == 0)
                q.push(v);
        }
    }

    assert(largest == 0);

    std::vector<int> test_copy(res);
    hiit_sort_assert_pathological(test_copy.data(), 0, n);

    cout << res[0];
    for (int i = 1; i < n; i++)
    {
        cout << " " << res[i];
    }
    cout << "\n";
}
