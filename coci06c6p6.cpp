//COCI 2006 Contest 6 P6 - Prostor
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> pii;
#define pb push_back
#define mp make_pair
const int MAXN = 1000;
int N, bit[MAXN][MAXN][2]; //0 = start, 1 = end
ll ans;
struct Event{
	int type, b, t, l, r, time; //0 = insert, 1 = query, 2 = delete
};
vector <Event> events[3]; //x is time, y is width ; y is time, z is width ; z is time, x is width
bool cmp (Event a, Event b){
	return a.time<b.time || (a.time==b.time&&a.type<b.type);
}
void update1 (int c, int p, int v, int n){ 
	for (;p<MAXN; p+=(p&-p)) bit[c][p][n]+=v;
}
int query1 (int c, int p, int n){
	int ans = 0;
	for (;p>0; p-=(p&-p)) ans+=bit[c][p][n];
	return ans;
}
void insert (int c, int l, int r, int v){
	update1 (c, l, v, 0);
	update1 (c, r, v, 1);
}
int count (int c, int b, int t){
	return query1 (c, t, 0) - query1 (c, b-1, 1);
}
void update (int p, int b, int t, int v){
	for (;p<MAXN; p+=(p&-p)) insert (p, b, t, v);
}
int query (int l, int r, int b, int t){
	int ans = 0;
	for (;r>0;r-=(r&-r)) ans += count (r, b, t);
	l--;
	for (;l>0;l-=(l&-l)) ans -= count (l, b, t);
	return ans;
}
int main(){
	int N;
	scanf("%d", &N);
	while (N--){
		int x1, y1, z1, x2, y2, z2;
		scanf("%d%d%d%d%d%d", &x1, &y1, &z1, &x2, &y2, &z2);
		if (x1>x2) swap(x1, x2);
		if (y1>y2) swap(y1, y2);
		if (z1>z2) swap(z1, z2);
		if (x1==x2){
			events[0].pb(Event{1, z1, z2, y1, y2, x1});
			events[2].pb(Event{0, y1, y2, x1, x2, z1});
			events[2].pb(Event{2, y1, y2, x1, x2, z2});
		}
		if (y1==y2){
			events[1].pb(Event{1, x1, x2, z1, z2, y1});
			events[0].pb(Event{0, z1, z2, y1, y2, x1});
			events[0].pb(Event{2, z1, z2, y1, y2, x2});
		}
		if (z1==z2){
			events[2].pb(Event{1, y1, y2, x1, x2, z1});
			events[1].pb(Event{0, x1, x2, z1, z2, y1});
			events[1].pb(Event{2, x1, x2, z1, z2, y2});
		}
	}
	for (int i = 0; i<3; i++) sort(events[i].begin(), events[i].end(), cmp);
	for (int i = 0; i<3; i++){
		for (Event e: events[i]){
			if (e.type==0){
				ans += query (e.l, e.r, e.b, e.t);
				update(e.l, e.b, e.t, 1);
			}
			else if (e.type==1){
				ans += query (e.l, e.r, e.b, e.t);
			}
			else{
				update(e.l, e.b, e.t, -1);
			}
		}
	}
	printf("%lld\n", ans);
}
