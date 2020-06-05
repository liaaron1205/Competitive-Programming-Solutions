//Solution to Codeforces 1328E Tree Queries
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> pii;
#define pb push_back 
#define mp make_pair
const int MAXN = 200005;

int N, Q, k;
vector<int> adj[MAXN];
int depth[MAXN];
int par[MAXN][20]; //par[i][j] = is 2^j th parent

bool cmp (int u, int v){
    return depth[u]<depth[v];
}
void dfs (int u, int p, int d){
    depth[u] = d;
    par[u][0] = p;
    for (int v: adj[u]){
        if (v==p) continue;
        dfs (v, u, d+1);
    }
}
int nthPar (int u, int n){
    int ret = u;
    while(n>0){
        int k = 0;
        for (; (1<<(k+1))<=n; k++);
        ret = par[ret][k];
        n-=(1<<k);
    }
    return ret;
}

int main(){
    scanf("%d%d", &N, &Q);
    for (int i = 1; i<N; i++){
        int u, v; 
        scanf("%d%d", &u, &v);
        adj[u].pb(v);
        adj[v].pb(u);
    }
    dfs(1, -1, 1);
    for (int i = 1; (1<<i)<N; i++){
        for (int j = 1; j<=N; j++){
            if (par[j][i-1]==-1) par[j][i]=-1;
            else par[j][i] = par[par[j][i-1]][i-1];
        }
    }
    while (Q--){
        scanf("%d", &k);
        vector<int> v;
        assert(v.empty());
        for (int i = 1, x; i<=k; i++){
            scanf("%d", &x);
            v.pb(x);
        }
        sort(v.begin(), v.end(), cmp);
        int cur = 1;
        int ans = 1;
        while(!v.empty()){
            if (cur==v[0]){
                v.erase(v.begin());
                continue;
            }
            if (nthPar(v[0], depth[v[0]]-depth[cur])!=cur){
                ans = 0;
                break;
            }
            cur = par[v[0]][0];
            v.erase(v.begin());
        }
        printf(ans?"YES\n":"NO\n");
    }
}
