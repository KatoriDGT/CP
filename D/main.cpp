#include <bits/stdc++.h>
using namespace std;
#define ten "merge"
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
        if(b & 1) (ans *= a) %= c;
        b >>= 1;
        a = bigmul(a, a); a %= mods;
    }
    return ans;
}
string s[105];
int n;
void solve()
{
    cin >> n;
    cin.ignore();
    for(int i = 1; i <= n; i++)
    {
        string line;
        getline(cin, line);
        int sz = line.length();
        string s2;
        int index = 0;
        int dem = 0;
        for(int i = 0; i < sz; i++)
        {
            if(line[i] <= '9' && line[i] >= '0')
                index = index * 10 + (line[i] - 48);
            else if(line[i] == ' ')
                {
                    s[dem] = s2;
                    dem++;
                    s2 = "";
                }
            else s2 += line[i];
        }
        cout << s[index-1] << " ";
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
