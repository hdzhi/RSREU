def good(cnt, q, s, t):
    return t // q + t // s >= cnt


n, quisk, slow = map(int, input().split())
if quisk > slow:
    quisk, slow = slow, quisk
l = 0
r = (n - 1) * slow

while r - l > 1:
    m = (l + r) // 2
    if not good(n - 1, quisk, slow, m):
        l = m
    else:
        r = m
print(r + quisk)

"""
#include <iostream>
using namespace std;

bool good(long int cnt, long int q, long int s, long int t) 
{
    return t / q + t / s >= cnt;
}

int main() 
{
    long int n, quisk, slow;
    cin >> n >> quisk >> slow;

    if (quisk > slow) 
    {
        swap(quisk, slow);
    }

    long int l = 0;
    long int r = (n - 1) * slow;

    while (r - l > 1) {
        long int m = (l + r) / 2;
        if (!good(n - 1, quisk, slow, m))
        {
            l = m;
        } else 
        {
            r = m;
        }
    }

    cout << r + quisk << endl;

    return 0;
}

"""