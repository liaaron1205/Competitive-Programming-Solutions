#include <bits/stdc++.h>
#define pb push_back
#define mid (seg[rt].l+seg[rt].r)/2
using namespace std;

const int INF = 0x3f3f3f3f, MAXN = 200005;

vector<int> adj[MAXN];
int N, W, D, dis[MAXN], ar[MAXN];

struct Node {
    int l, r, rt, min;
} seg[4*MAXN];

void build (int l, int r, int rt){
    seg[rt].l = l;
    seg[rt].r = r;
    if (l==r){
        seg[rt].min = dis[ar[l]] + l - 1;
        return;
    }
    build (l, mid, 2*rt);
    build (mid+1, r, 2*rt+1);
    seg[rt].min = min(seg[2*rt].min, seg[2*rt+1].min);
}

void upd (int x, int rt){
    if (seg[rt].l==x && seg[rt].r == x){
        seg[rt].min = dis[ar[x]] + x - 1;
        return;
    }
    if (x<=mid) upd(x, 2*rt);
    else upd (x, 2*rt+1);
    seg[rt].min = min(seg[2*rt].min, seg[2*rt+1].min);
}

void bfs(int u){
    queue<int> q;
    dis[N] = 0;
    q.emplace(N);
    while(!q.empty()){
        int u = q.front();
        q.pop();
        for (int v: adj[u]){
            if (dis[u]+1 < dis[v]){
                dis[v] = dis[u]+1;
                q.emplace(v);
            }
        }
    }
}
int main(){
    scanf("%d%d%d", &N, &W, &D);
    for (int i = 0; i<W; i++){
        int a, b;
        scanf("%d%d", &a, &b);
        adj[b].pb(a);
    }
    memset(dis, INF, sizeof dis);
    bfs(N);
    for (int i = 1; i<=N; i++){
        scanf ("%d", &ar[i]);
    }
    build(1, N, 1);
    for (int i = 0; i<D; i++){
        int a, b;
        scanf("%d%d", &a, &b);
        swap (ar[a], ar[b]);
        upd(a, 1);
        upd(b, 1);
        printf("%d\n", seg[1].min);
    }
}
