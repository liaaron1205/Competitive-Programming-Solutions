#include"factories.h"
#include <bits/stdc++.h>
using namespace std;
typedef pair<int, int> pii;
typedef long long ll;
const int MAXN = 500005;
int level[MAXN], sz[MAXN], par[MAXN][20];
ll dis[MAXN][20], dis1[MAXN];
bool done[MAXN], contains[MAXN];
int N, Q;
vector<pii> adj[MAXN];
queue<int> s;
void dfs (int u, int p){
    sz[u] = 1;
    for (pii e: adj[u]){
        if (e.first==p||done[e.first]) continue;
        dfs (e.first, u);
        sz[u]+=sz[e.first];
    }
}
void dfs1(int u, int p, int l, ll d, int pa){
    dis[u][l] = d;
    par[u][l] = pa;
    for (pii e: adj[u]){
        if (e.first==p||done[e.first]) continue;
        dfs1(e.first, u, l, d+e.second, pa);
    }
}
int centroid (int u, int p, int S){
    for (pii e: adj[u]){
        if (sz[e.first]*2>S&&e.first!=p&&!done[e.first]) return centroid (e.first, u, S);
    }
    return u;
}
void build (int u, int p, int l){
    dfs (u, -1);
    u = centroid(u, -1, sz[u]);
    level[u] = l;
    dfs1(u, -1, l, 0, u);
    done[u] = true;
    for (pii e: adj[u]){
        if (!done[e.first]&&e.first!=p) build(e.first, u, l+1);
    }
}

void Init(int N, int A[], int B[], int D[]){
    for (int i = 0; i<N-1; i++){
        adj[A[i]].push_back(make_pair(B[i], D[i]));
        adj[B[i]].push_back(make_pair(A[i], D[i]));
    }
    memset (dis, -1, sizeof dis);
    memset (par, -1, sizeof par);
    memset (dis1, -1, sizeof dis1);
    build(0, -1, 1);
}

ll Query(int S, int X[], int T, int Y[]){
     while(!s.empty()){
        dis1[s.front()]=-1;
        contains[s.front()] = false;
        s.pop();
    }
    ll best = -1;
    for (int i = 0; i<S; i++){
        int A = X[i];
        int l = level[A];
        while (l){
            if (dis1[par[A][l]]==-1) dis1[par[A][l]] = dis[A][l];
            else dis1[par[A][l]]=min(dis1[par[A][l]], dis[A][l]);
            if (!contains[par[A][l]]){
                contains[par[A][l]] = true;
                s.push(par[A][l]);
            }
            l--;
        }
    }
    for (int i = 0; i<T; i++){
        int B = Y[i];
        int l = level[B];
        while (l){
            if(best==-1&&dis1[par[B][l]]!=-1)best = dis1[par[B][l]]+dis[B][l];
            else if (dis1[par[B][l]]!=-1) best = min(best, dis1[par[B][l]]+dis[B][l]);
            l--;
        }
    }
    return best;
}
