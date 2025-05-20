def good(x, w, h, n):
    return (x // w) * (x // h) >= n

w, h, n = map(int, input().split())
l, r = 0, n * max(w, h)
while r - l > 1:
    m = (l + r) // 2
    if good(m, w, h, n):
        r = m
    else:
        l = m
print(r)


"""
#include <iostream>

using namespace std;

bool good(long x, long w, long h, long n) 
{
    return (x / w) * (x / h) >= n;
}

int main() 
{
    long w, h, n;
    cin >> w >> h >> n;

    long l = 0;
    long r = 1;

    while (!good(r, w, h, n)) 
    {
     r = r*2;
    }
    while (r - l > 1)
    {
        long m = (l + r) / 2;
        if (good(m, w, h, n)) 
        {
            r = m;
        } 
  else {
            l = m;
        }
    }
    cout << r << endl;

    return 0;
}
"""
