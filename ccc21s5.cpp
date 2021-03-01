#include <bits/stdc++.h>
using namespace std;
typedef pair<int, int> pii;
typedef pair<pair<int, int>, int> piii;
#define pb push_back
#define mp make_pair
#define f first
#define s second
#define mid (seg[rt].l+seg[rt].r)/2


const int INF = 0x3f3f3f3f, MAXN = 150005;

vector<piii> conditions;
int N, M, DA[20][MAXN], ar[MAXN];

int gcd (int a, int b){
    if (b==0) return a;
    return gcd(b, a%b);
}
int lcm (int a, int b){
    return (a * b) / gcd(a, b);
}
struct Node {
    int l, r, rt, gcd;
} seg[4*MAXN];

void build (int l, int r, int rt){
    seg[rt].l = l;
    seg[rt].r = r;
    if (l == r){
        seg[rt].gcd = ar[l];
        return;
    }
    build (l, mid, 2*rt);
    build (mid+1, r, 2*rt+1);
    seg[rt].gcd = gcd(seg[2*rt].gcd, seg[2*rt+1].gcd);
}

int query (int l, int r, int rt){
    if (seg[rt].l==l && seg[rt].r == r){
        return seg[rt].gcd;
    }
    if (r<=mid) return query (l, r, 2*rt);
    else if (l > mid) return query (l , r, 2*rt+1);
    else return gcd(query(l, mid, 2*rt), query(mid+1, r, 2*rt+1));

}

int main(){
    scanf("%d%d", &N, &M);
    for (int i = 0; i<M; i++){
        int l, r, v;
        scanf("%d%d%d", &l, &r, &v);
        conditions.pb(mp(mp(l, r), v));
        DA[v][l]++;
        DA[v][r+1]--;
    }
    for (int i = 1; i<=N; i++){
        ar[i] = 1;
        for (int j = 1; j<=16; j++){
            DA[j][i]+=DA[j][i-1];
            if (DA[j][i]>0) ar[i] = lcm(ar[i], j);
        }
    }
    build (1, N, 1);
    for (auto x: conditions){
        if (query (x.f.f, x.f.s, 1) != x.s){
            printf("Impossible\n");
            return 0;
        }
    }
    for (int i = 1; i<=N; i++){
        printf("%d ", ar[i]);
    }
    printf("\n");

}
