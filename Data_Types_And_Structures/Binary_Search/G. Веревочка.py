def good(x):
    cnt = 0
    for ln in a:
        cnt += int(ln // x)
    return cnt >= k


n, k = map(int, input().split())
a = [int(input()) for _ in range(n)]
l, r = 0, 10 ** 7 + 1
for i in range(100):
    m = (l + r) // 2
    if good(m):
        l = m
    else:
        r = m
print(l)


"""
#include <iostream>
#include <vector>

using namespace std;

bool good(long long x, const vector<long long>& a, long long k)
{
    long long cnt = 0;
    for (long long ln : a) 
    {
        cnt += ln / x; 
    }
    return cnt >= k;
}

int main() 
{
    long long n, k;
    cin >> n >> k;

    vector<long long> a(n);
    long long max_value = 0; 
    for (long long i = 0; i < n; i++) 
    {
        cin >> a[i];
        if (a[i] > max_value) 
        {
            max_value = a[i]; 
        }
    }

    long long l = 1, r = max_value + 1; 
    
    while (l < r) 
    {
        long long m = (l + r) / 2;
        if (good(m, a, k)) 
        {
            l = m + 1; 
        } else 
        {
            r = m; 
        }
    }

    cout << l - 1 << endl; 

    return 0;
}
"""