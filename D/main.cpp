#include <bits/stdc++.h>
using namespace std;
#define ten "merger"
#define ten2 "test"
#define io 0
#define iftest false
#define pb push_back
#define fi first
#define se second
#define p(a,b) pair<a,b>
#define L 1ll * 1e18
#define no {cout << 0; return;}
typedef long long ll;
const ll mods = 1e9 + 7;
const ll mods2 = 1e9 + 7;
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
        a *= a; a %= c;
    }
    return ans;
}
int n;
vector<int> w[567895];
vector<int> xet;
int dsu_p[567895];
vector<p(int, int)> edges;
bool notouch[567895];
int dp[567895][3];
void cleanW()
{
    for(int i = 1; i <= n; i++)
    {
        int sz = w[i].size();
        sort(w[i].begin(), w[i].end());
        for(int j = 0; j < sz - 1; j++)
        {
            if(w[i][j] == w[i][j + 1])
                w[i][j] = 0;
        }
    }
}
int dsu_pfind(int id)
{
    if(dsu_p[id] == id) return id;
    return (dsu_p[id] = dsu_pfind(dsu_p[id]));
}
bool dsu_join(int u, int v)
{
    int pa1 = dsu_pfind(u); int pa2 = dsu_pfind(v);
    if(pa1 != pa2)
    {
        dsu_p[pa2] = pa1;
        return 1;
    }
    else return 0;
}
void dsu_setup()
{
    for(int i = 1; i <= n; i++){
        dsu_p[i] = i;
    }
}
p(int, int) dsu_find_cy()
{
    for(p(int, int) e: edges)
    {
        int u = e.fi; int v = e.se;
        bool done = dsu_join(u, v);
        if(!done) return {u, v};
    }
}
bool dfs(int u,  int v, vector<int> &passed, int pa = 0)
{
    if(u == v)
    {
        xet = passed;
        return 1;
    }
    else{
            for(int v2: w[u])
            {
                if(pa == 0 && v2 == v){
                    xet.pb(u); xet.pb(v);
                    continue;
                }
                if(v2 == pa || v2 == 0) continue;
                passed.pb(v2);
                bool done = dfs(v2, v, passed, u);
                if(done) return 1;
                passed.pop_back();
            }
    }
    return 0;
}
int dp_c[2][2];
void dp_xenke(int u, int pa = 0)
{
    dp[u][1] = 1;
    for(int v: w[u])
    {
        if(notouch[v] || pa == v) continue;
        dp_xenke(v, u);
        dp[u][0] += dp[v][1];
        dp[u][1] += min(dp[v][0], dp[v][1]);
    }
}
void solve()
{
    cin >> n;
    for(int i = 1; i <= n; i++)
    {
        int v; cin >> v;
        w[i].pb(v);
        w[v].pb(i);
        edges.pb({i, v});
    } cleanW();
    dsu_setup();
    p(int, int) dfspair = dsu_find_cy();
    {
     vector<int> passed;
     passed.pb(dfspair.fi);
    dfs(dfspair.fi, dfspair.se, passed);
    }
    for(int v: xet)
    {
        notouch[v] = 1;
    }
    for(int v: xet)
    {
        dp_xenke(v);
    }
    int sz = xet.size();
    dp_c[0][1] = dp[xet[0]][0];
    dp_c[0][0] = dp[xet[0]][0];
    dp_c[1][1] = dp[xet[0]][1];
    dp_c[1][0] = dp[xet[0]][1];
    for(int i = 1; i < sz; i++)
    {
        int id = xet[i];
        int type = 1;
        while(type >= 0)
        {
            int chon = min(dp_c[type][0], dp_c[type][1]) + dp[id][1];
            int khong = dp_c[type][1] + dp[id][0];
            if(i == 1 && type == 0)
            {
               khong = chon;
            }
            dp_c[type][1] = chon;
            dp_c[type][0] = khong;
            //cout << dp_c[type][0] << " " << dp_c[type][1] << " ";
            type--;
        }
       // cout << "\n";
    }
    int rs = min({dp_c[0][1], dp_c[1][1], dp_c[1][0]}) - 1;
    cout << max(rs, 0);
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
    else if(fopen(ten2".INP",  "r"))
    {
    freopen(ten2".INP", "r", stdin);
    freopen(ten2".OUT", "w", stdout);
    }

    solve();
    return 0;
}
