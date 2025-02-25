#include <bits/stdc++.h>
using namespace std;
using ll = long long;
int main ( ) 
{
    int t;
    cin >> t;
    while ( t-- ) {
        int n;
        ll x,k;
        cin >> n >> x >> k;
        char a[n];
        int cnt_l = 0,cnt_r = 0,cnt = 0;
        int t = 0;
        int ans = 0;
        for ( int i=0; i<n; i++ ) {
            cin >> a[i];
            if ( a[i] == 'L' ) cnt_l++;
            if ( a[i] == 'R' ) cnt_r++;
            if ( cnt_l == cnt_r ) cnt = cnt_l * 2;
        }
        
        //第一次到0
        for ( int i=0; i<n; i++,t++ ) {
            if ( a[i] == 'L' ) {
                x++;
            }else {
                x--;
            }
            if ( x == 0 && t <= k ) {
                ans++;
                k -= t;
                break;
            }
        }
        if ( ans == 0 ) {
            cout << ans << endl;
            continue;
        }
        //可以重复走
        if ( cnt ) {
            ans += k / cnt;
        }

        cout << ans << endl;
    } 
    return 0;
}