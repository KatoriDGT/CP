#include <bits/stdc++.h>
using namespace std;
#define ten "test"
#define io false
#define iftest false
#define pb push_back
#define fi first
#define se second
#define p(a,b) pair<a,b>
#define L 1ll * 1e18
typedef long long ll;
const int mods = 1e9 + 7;
ll bigmul(ll a, ll b, ll c = mods){
    ll ans = 0;
    while(b){
        if(b & 1) (ans += a) %= c;
        b >>= 1;
        a += a; a %= c;
    }
    return ans;
}
ll fastpow(ll a, ll b, ll c = mods){
    ll ans = 1;
    while(b){
        if(b & 1) (ans = bigmul(ans, a)) %= c;
        b >>= 1;
        a = bigmul(a, a); a %= mods;
    }
    return ans;
}


void solve()
{

}

void testGen()
{

}

void solveTest(){
    testGen();
    solve();
    cin.ignore();
    solveTest();
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    if(fopen(ten".INP", "r"))
    {
    freopen(ten".INP", "r", stdin);
    freopen(ten".OUT", "w", stdout);
    }
    if(iftest){
        solveTest();
    }
    solve();
    return 0;
}
