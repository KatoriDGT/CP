#include <bits/stdc++.h>
using namespace std;
#define ten "thuyvan"
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
int n, k;
string s[55];
int p[5][(int)2e5+5];
int inv[5];
bool b[300];
int bases[5] = {227, 227, 227, 227, 0};
const int mods_vl[5] = {(int)1e9 + 2277, (int)1e9 + 9277, (int)1e9 + 8277, (int)1e9 + 5277, 0};
struct o{
    int hash1, hash2, hash3, hash4;
    o() {}
    o(int s1, int s2, int s3, int s4)
    {
        hash1 = s1; hash2 = s2;
        hash3 = s3; hash4 = s4;
    }
};
    bool operator<(const o& ob1, const o& ob)
    {
        if(ob1.hash1 < ob.hash1) return 1;
        else if(ob1.hash1 > ob.hash1) return 0;
        if(ob1.hash2 < ob.hash2) return 1;
        else if(ob1.hash2 > ob.hash2) return 0;
        if(ob1.hash3 < ob.hash3) return 1;
        else if(ob1.hash3 > ob.hash3) return 0;
        if(ob1.hash4 < ob.hash4) return 1;
        else return 0;
    }
void hash_build()
{
    int n = 2e5;
    srand(time(0));
    for(int i =0; i <= 3; i++)
    {
        int id = rand() % 31 + 200;
        if(b[id] == 0)
        {
            b[id] = 1;
            bases[i] = id;
        } else i--;
    }
   for(int i =0; i <= 3; i++)
   {
        p[i][0] = 1;
        int base = bases[i];
        for(int j = 1; j <= n; j++)
        {
            p[i][j] = 1ll * p[i][j-1] * base % mods_vl[i];
        }
        inv[i] = fastpow(base, mods_vl[i] - 2, mods_vl[i]);
   }
}
map<o, ll> mp;
void hash_extend(int& hashed, int next, int hash_id, int hat)
{
    hashed += 1ll * next * p[hash_id][hat] % mods_vl[hash_id];
    if(hashed > mods_vl[hash_id])
        hashed -= mods_vl[hash_id];
}
void hash_pop(int& hashed, int prev, int hash_id)
{
    hashed -= prev;
    if(hashed < 0) hashed += mods_vl[hash_id];
    hashed = 1ll * hashed * inv[hash_id] % mods_vl[hash_id];
}
int last;
int lastreal;
o check(int len)
{
    mp.clear();
    for(int i = 1; i <= n; i++)
    {
        int sz = s[i].length() - 1;
        if(sz < len) continue;
        int hashed1 = 0;
        int hashed2 = 0;
        int hashed3 = 0;
        int hashed4 = 0;
        int id = i;
        last = i;
        o ob;
        for(int i = 1; i <= sz; i++)
        {
            if(i > len)
            {
                int last = s[id][i - len];
                hash_pop(hashed1, last, 0);
                hash_pop(hashed2, last, 1);
                hash_pop(hashed3, last, 2);
                hash_pop(hashed4, last, 3);
            }
            int now = s[id][i];
            int hat = min(i - 1, len - 1);
            hash_extend(hashed1, now, 0, hat);
            hash_extend(hashed2, now, 1, hat);
            hash_extend(hashed3, now, 2, hat);
            hash_extend(hashed4, now, 3, hat);
            if(i >= len)
            {
                ob.hash1 = hashed1;
                ob.hash2 = hashed2;
                ob.hash3 = hashed3;
                ob.hash4 = hashed4;
                ll mask = mp[ob];
                mask = (mask | (1ll * 1 << (1ll * id - 1)));
                int dem = 0;
                for(int i = 1; i <= n; i++)
                {
                    bool on = ((mask >> (i-1)) & 1);
                    if(on) dem++;
                }
                if(dem >= k)
                {
                    return ob;
                }
                mp[ob] = mask;
            }
        }
    }
    return o(-1, 0,0,0);
}
void truyvet(o ob, int len)
{
    for(int i = lastreal; i <= n; i++)
    {
        int sz = s[i].length() - 1;
         if(sz < len) continue;
        int hashed1 = 0;
        int hashed2 = 0;
        int hashed3 = 0;
        int hashed4 = 0;
        int id = i;
        for(int i = 1; i <= sz; i++)
        {
            if(i > len)
            {
                int last = s[id][i - len];
                hash_pop(hashed1, last, 0);
                hash_pop(hashed2, last, 1);
                hash_pop(hashed3, last, 2);
                hash_pop(hashed4, last, 3);
            }
            int now = s[id][i];
            int hat = min(i - 1, len - 1);
            hash_extend(hashed1, now, 0, hat);
            hash_extend(hashed2, now, 1, hat);
            hash_extend(hashed3, now, 2, hat);
            hash_extend(hashed4, now, 3, hat);
            if(i >= len)
            {
                if(hashed1 == ob.hash1 && hashed2 == ob.hash2 && hashed3 == ob.hash3 && hashed4 == ob.hash4)
                {
                    for(int j = i - len + 1; j <= i; j++)
                    {
                        cout << s[id][j];
                    }
                    return;
                }
            }
        }
    }
}
void solve()
{
    hash_build();
    cin >> n >> k;
    int tong = 0;
    for(int i =1; i <= n; i++)
    {
        cin >> s[i];
        s[i] = " " + s[i];
        tong = max(tong, (int)s[i].length() - 1);
    }
    int l = 1, r = tong;
    o ans;
    int len = 0;
    while(l <= r)
    {
        int mid = (l + r) >> 1;
        o checkHash = check(mid);
        if(checkHash.hash1 != -1)
        {
            l = mid + 1;
            len = mid;
            ans = checkHash;
            lastreal = last;
        }
        else r = mid - 1;
    }
    truyvet(ans, len);
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
