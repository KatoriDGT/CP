#include <bits/stdc++.h>
using namespace std;
#define ten "thuyvan"
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
int n, k;
string s[55];
map<string, int> m;
map<string, bool> m2;

string rs = "";
int rs2 = 0;

int p[(int)2e5+5];
int inv_p[(int)2e5+5];
int tong = 0;
int ma_length = 0;
void presetup()
{
    p[0] = 1;
    for(int i = 1; i <= tong; i++)
    {
        p[i] = 1ll * p[i-1] * 31 % mods;
    }
    for(int i = 0 ; i <= tong; i++)
    {
        inv_p[i] = fastpow(p[i], mods - 2);
    }
}
void solveSub1(){
    for(int i = 1; i <= n; i++)
    {
        m2.clear();
        int sz = s[i].length();
        sz--;
        int id = i;
        for(int i = 1; i <= sz; i++)
        {
            string s2 = "";
            for(int j = i; j >= 1; j--)
            {
                s2 = s[id][j] + s2;
                if(m2[s2] == 0)
                {
                    m2[s2] = 1;
                    int fre = ++m[s2];
                    if(fre >= k)
                    {
                        int sz_s2 = i - j + 1;
                        if(sz_s2 > rs2)
                        {
                            rs2 = sz_s2;
                            rs = s2;
                        }
                    }
                }
            }
        }
    }
    cout << rs;
}
struct o{
    int id; int l, r;
    o(){}
    o(int idd, int ll, int rr){
        id = idd; l = ll; r = rr;
    }
};
map<int, int> map1;
map<int, bool> map2;
map<int, o> map3;
void solveSub3(){
    presetup();
    int l = 1, r = ma_length;
    string rs;
    int rs2 = 0;
    while(l <= r)
    {
        map1.clear();
        int mid = (l + r) >> 1;
        bool check = 0;
        for(int i = 1; i <= n; i++)
        {
            map2.clear();
            int sz = s[i].length() - 1;
            int id = i;
            int last = 1;
            int hashed = 0;
            for(int i = 1; i <= sz; i++)
            {
                //s2 += s[id][i];
                int hashed_char = 1ll * (s[id][i] - 'A' + 1) * p[min(i - 1, mid-1)] % mods;
                if(i - last + 1 > mid)
                {
                //s2 = s2.substr(1, 100);
                    int hashed_char2 = 1ll * (s[id][last] - 'A' + 1);
                    hashed -= hashed_char2; if(hashed < 0) hashed += mods;
                    last++;
                    hashed = 1ll * hashed  * inv_p[1] % mods;
                }
                hashed += hashed_char;
                hashed %= mods;
                if(i - last + 1 == mid)
                {
                    if(map2[hashed] == 0)
                    {
                        map2[hashed] = 1;
                        int fre = ++map1[hashed];
                        if(fre >= k)
                        {
                            map3[hashed] = o(id, last, i);
                            rs2 = hashed;
                            check = 1;
                            break;
                        }
                    }
                }
                //cout << s2 << " " << hashed << "\n";
                if(check) break;
            }
                if(check) break;
        }
        if(check)
        {
            l = mid + 1;
        }
        else r = mid - 1;
    }
    o ob = map3[rs2];
    int id = ob.id;  l = ob.l;  r = ob.r;
    for(int i = l; i <= r; i++)
        cout << s[id][i];
}
void solve()
{
    cin >> n >> k;
    for(int i = 1; i <= n; i++)
    {
        cin >> s[i];
        int sz = s[i].length();
        s[i] = " " + s[i];
        tong += sz;
        ma_length = max(ma_length, sz);
    }
    if(tong <= 1000)
        solveSub1();
    else solveSub3();
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
