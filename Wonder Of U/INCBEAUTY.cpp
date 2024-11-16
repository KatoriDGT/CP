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
int l, h;
int n; ll k;
ll dp[12][12][12];
ll dp2[1005][1005];
int numberOfSeight(int x){
    int ans = 0;
    while(x > 0){
        int k = x % 10;
        x /= 10;
        if( k == 6 || k == 8)
            ans++;
    } return ans;
}
ll presetupSub1(int id, int last, int lim)
{
    if(id == 0)
    {
        for(int i = 1; i <= 10; i++)
            presetupSub1(1, 0, i);
        return 0;
    }
    ll tong = 0;
    for(int i = l; i <= h; i++)
    {
        if(dp[i][id][lim] == 0)
        {
            if(id < lim)
                dp[i][id][lim] = presetupSub1(id + 1, i, lim);
            else dp[i][id][lim] = 1;
        }
        if((last != 6 && last != 8) || i == 6 || i == 8)
            tong += dp[i][id][lim];
    }
    return tong;
}
ll presetupSub2(int id, int last)
{
    ll tong = 0;
    for(int i = l; i <= h; i++)
    {
        if(numberOfSeight(last) > numberOfSeight(i))
            continue;
        if(dp2[i][id] == 0)
        {
            if(id == n)
                dp2[i][id] = 1;
            else dp2[i][id] = presetupSub2(id + 1, i);
        }
        if(k - tong <= dp2[i][id])
            return k;
        else tong += dp2[i][id];
    }
    return tong;
}
vector<int> rs;
void sub3f(int id, int &k2, int last, vector<int> &rs)
{
    int tong = 0;
    if(id == n + 1)
    {
        k2++;
        return;
    }
    for(int i = l; i <= h; i++)
    {
        if(numberOfSeight(last) > numberOfSeight(i))
            continue;
        rs.pb(i);
        sub3f(id + 1, k2, i, rs);
        if(k2 >= k)
        {
            int sz = rs.size();
            for(int i = 0; i < sz; i++)
            {
                cout << rs[i] << " ";
            }
            exit(0);
        }
        rs.pop_back();
    }
}
void sub1(){
    ll k2 = 0;
    bool done = 1;
    int id = 1;
    int last = 0;
    for(int i = l; i <= h; i++)
    {
        if(numberOfSeight(last) > numberOfSeight(i)) continue;
        ll now = dp[i][id][n];
        k2 += now;
        if(k2 >= k)
        {
            cout << i << " ";
            done = 0;
            k2 = k2 - now;
            last = i;
            id++;
            i = l - 1;
            if(id > n) break;
        }
    }
    if(done)
        cout << -1;
    cout << "\n";
}
void sub2()
{
    presetupSub2(1, 0);
    ll k2 = 0;
    int id = 1;
    int last = 0;
    bool done = 1;
    for(int i  = l; i <= h; i++)
    {
        if(numberOfSeight(last) > numberOfSeight(i))
            continue;
        ll now = dp2[i][id];
        if(k - now <= k2)
        {
            cout << i << "\n";
            done = 0;
            last = i;
            i = l - 1;
            if(id == n)
            break;
            id++;
        }
        else k2 += now;
    }
    if(done)
        cout << -1;
}
void sub3()
{
    int k2 = 0;
    sub3f(1, k2, 0, rs);
    cout << -1;
}
void subDriven1()
{
    cin >> n >> k;
    if(n <= 1000 && h <= 1000)
        sub2();
    else if(k <= (int)1e6)
        sub3();
}
void solve()
{
    int t;
    cin >> l >> h >> t;
    if(t == 1)
        subDriven1();
    else{
        if(h <= 10)
                presetupSub1(0, 0, 0);
    while(t--)
    {
        cin >> n >> k;
        if(h > 10 || n > 10) return;
        sub1();
    }
    }
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
