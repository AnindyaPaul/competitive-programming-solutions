
#include <cmath>
#include <cstdio>
#include <cctype>
#include <cstdlib>
#include <cstring>
#include <climits>

#include <string>
#include <complex>
#include <iomanip>
#include <utility>
#include <sstream>
#include <iostream>
#include <algorithm>
#include <functional>

#include <map>
#include <set>
#include <list>
#include <stack>
#include <queue>
#include <deque>
#include <vector>
#include <bitset>

#include <new>
#include <limits>
#include <memory>
#include <locale>
#include <iterator>

#include <ctime>
#include <cwchar>
#include <cerrno>
#include <cfloat>
#include <clocale>
#include <ciso646>
#include <csetjmp>
#include <csignal>
#include <cstdarg>
#include <cstddef>
#include <cwctype>

#include <ios>
#include <numeric>
#include <fstream>
#include <streambuf>

using namespace std;

#ifdef __GNUC__
typedef long long LL;
typedef unsigned long long ULL;
#else
typedef __int64 LL;
typedef unsigned __int64 ULL;
#endif
typedef unsigned UI;

#define PI 3.14159265358979323846264338327950
#define RADIAN PI / 180

#define MEM( x, y ) memset( x, y, sizeof( x ) )
#define READ( file ) freopen( file, "r", stdin )
#define WRITE( file ) freopen( file, "w", stdout )

#define PB( x ) push_back( x )
#define PF( x ) push_front( x )
#define pii pair<int, int>
#define pll pair<LL, LL>

#define ndl ( '\n' )
#define scani( x ) scanf( "%d", &x )
#define scanl( x ) scanf( "%lld", &x )
#define scand( x ) scanf( "%lf", &x )
#define scans( x ) scanf( "%s", x )
#define scanii( x, y ) scanf( "%d %d", &x, &y )
#define scanll( x, y ) scanf( "%lld %lld", &x, &y )
#define scandd( x, y ) scanf( "%lf %lf", &x, &y )
#define printi( x ) printf( "%d\n", x )
#define printl( x ) printf( "%lld\n", x )
#define printd( x ) printf( "%lf\n", x )
#define printii( x, y ) printf( "%d %d\n", x, y )
#define printll( x, y ) printf( "%lld %lld\n", x, y )
#define printdd( x, y ) printf( "%lf %lf\n", x, y )

#define what_is(x) cerr << #x << " = " << x << endl;

// Debugs
template <class T> inline void debug( T x )
{ cout << "x = " << x << endl; }
template <class T1, class T2> inline void debug( T1 x, T2 y )
{ cout << "x = " << x << ", y = " << y << endl; }
template <class T1, class T2, class T3> inline void debug( T1 x, T2 y, T3 z )
{ cout << "x = " << x << ", y = " << y << ", z = " << z << endl; }

// Powers
template <class T> inline T sqr( T x ) { return x*x; }
template <class T> inline T cube( T x ) { return x*x*x; }
template <class T> inline T quad( T x ) { return x*x*x*x; }

// Bit Manipulation
template <class T> inline T setBit( T n, T pos ) { return n = n | ((T)1<<pos); }
template <class T> inline T resetBit( T n, T pos ) { return n = n & ~((T)1<<pos); }
template <class T> inline bool checkBit( T n, T pos ) { return n & ((T)1<<pos); }

// GCD, LCM
template <class T> inline T GCD( T a, T b ) { if( a < 0 ) return GCD( -a , b );
    if( b < 0 ) return GCD( a, -b ); return ( b == 0 ) ? a : GCD( b, a%b ); }
template <class T> inline T LCM( T a, T b ) { if( a < 0 ) return LCM( -a, b );
    if( b < 0 ) return LCM( a, -b ); return a * ( b / GCD( a, b ) ); }

// Prime
template <class T> inline bool isPrime( T n ) { if( n <= 1 ) return false;
    for( T i = 2; i*i <= n; i++ ) if( n % i == 0 ) return false; return true; }

// Various
template <class T> inline T abso( T x ) { return x >= 0 ? x : -x; }
template <class T> inline T mod( T n, T m ) { return ( n%m + m ) % m; }
template <class T> inline T bigmod(T b, T p, T m) { if(p == 0) return 1;
    if(p%2 == 1) return ((b%m) * (bigmod(b, p-1, m)%m))%m;
    else { T tmp = bigmod(b, p/2, m)%m; return (tmp*tmp)%m; } }

#define EPS 1e-9
#define INF 1000000000

//int dx[] = {0, 0, +1, -1};
//int dy[] = {+1, -1, 0, 0};

// Template ends, coding starts

#define MX 10010

set <int> artp;
vector <int> graph[MX];

int tme;
int root;
ULL ncnt;

int dis[MX];
int low[MX];
int parent[MX];

bool src[MX];
bool vis[MX];
bool isap[MX];

void findAP(int u, int par)
{
    vis[u] = true;
    dis[u] = tme++;
    low[u] = dis[u];

    int child = 0;
    for(int i = 0; i < graph[u].size(); i++) {
        int v = graph[u][i];

        if(v == par) continue;

        if(!vis[v]) {
            parent[v] = parent[u];
            findAP(v, u);
            child++;

            low[u] = min(low[u], low[v]);

            if(u == root && child > 1) isap[u] = true;
            if(u != root && low[v] >= dis[u]) isap[u] = true;
        }
        else {
            low[u] = min(low[u], dis[v]);
        }
    }
}

void dfs(int u, int par)
{
    ncnt++;
    vis[u] = true;

    for(int i = 0; i < graph[u].size(); i++) {
        int v = graph[u][i];
        if(v == par) continue;
        if(isap[v]) {
            artp.insert(v);
            continue;
        }
        if(!vis[v]) {
            dfs(v, u);
        }
    }
}

int main()
{
//    READ( "in.txt" );
//    WRITE( "out.txt" );
//    ios_base::sync_with_stdio(false); cin.tie(0);

    int t, cs = 1;

    scani(t);
    while(t--) {
        int n, m;
        scanii(n, m);

        for(int i = 0; i < n; i++) {
            graph[i].clear();
            isap[i] = false;
            parent[i] = i;
        }

        while(m--) {
            int u, v;
            scanii(u, v);
            graph[u].PB(v);
            graph[v].PB(u);
        }

        tme = 0;
        MEM(vis, 0);
        MEM(src, 0);
        for(int i = 0; i < n; i++) {
            if(!vis[i]) {
                root = i;
                src[i] = true;
                findAP(i, -1);
            }
        }

        MEM(vis, 0);
        ULL ans = 0;
        ULL ways = 1;
        ULL cmpcnt = 0;
        for(int i = 0; i < n; i++) {
            if(isap[i]) continue;
            if(!vis[i]) {
                ncnt = 0;
                artp.clear();
                dfs(i, -1);
                if(artp.size() < 2) {
                    cmpcnt++;
                    ways *= ncnt;
                }
            }
        }
        if(cmpcnt == 1) {
            cmpcnt++;
            ways *= (ncnt-1);
            ways /= 2;
        }
        ans += cmpcnt;

        printf("Case %d: %llu %llu\n", cs++, ans, ways);
    }

    return 0;
}
