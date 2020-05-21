//CCO 2017 P3 - Vera and Modern Art
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
struct Event {ll x, yt, yb; int v, t;};
bool cmp (Event a, Event b){
    return (a.x<b.x||(a.x==b.x&&a.t>b.t));
}
ll bit[600005], bit1[600005], ans[200005];
int N, Q, cnt = 1;
set<ll> s;
map<ll, int> m;
vector<Event> events;

void update1(int i, ll v){
    for (;i<=cnt;i+=(i&-i)) bit[i]=(bit[i]+v);
}
void update2(int i, long v){
    for (;i<=cnt;i+=(i&-i)) bit1[i]=(bit1[i]+v);
}
void update(int l, int r, ll v){
    update1(l, v);
    update1(r+1, -v);
    update2(l, v*(l-1));
    update2(r+1, -v*r);
}
ll query1(int i){
   ll ans = 0;
   for (;i>0; i-=(i&-i)) ans=(ans+bit[i]);
   return ans;
}
ll query2(int i){
   ll ans = 0;
    for (;i>0;i-=(i&-i)) ans=(ans+bit1[i]);
    return ans;
}
ll query(int i){
    return ((query1(i)*i)-query2(i));
}
ll rev (ll x){
    ll ans = 0;
    while(x){
        ans<<=1;
        ans|=x&1;
        x>>=1;
    }
    return ans;
}
ll f0 (ll i){
    ll ans = rev(i);
    ans>>=1;
    ans<<=(60-(int)(floor(log2(i))));
    return ans;
}
ll f1 (ll i){
    ll ans = f0(i);
    ll t = ((ll)1<<(ll)((60-(int)(floor(log2(i)))))) -1;
    ans += t;
    return ans;
}
ll f2 (ll i){
    ll ans = rev(i);
    ans<<=(60-(int)(floor(log2(i)+1)));
    return ans;
}
int main()
{
    scanf("%d%d", &N, &Q);
    for (int i = 0; i<N; i++){
        ll x, y; int v;
        scanf("%lld%lld%d", &x, &y, &v);
        ll left = f0(x)+1, right = f1(x)+1, bot = f0(y)+1, top = f1(y);
        //printf("%lld\n%lld\n%lld\n%lld\n", left, right, bot, top);
        events.push_back(Event{left, top, bot, v, 1});
        events.push_back(Event{right, top, bot, -v, 1});
        s.insert(bot);
        s.insert(top);
    }
    for (int i = 0; i<Q; i++){
        ll x, y;
        scanf("%lld%lld", &x, &y);
        x = f2(x);
        y = f2(y);
        //printf("%lld %lld\n", x, y);
        events.push_back(Event{x, y, 0, i , 0});
        s.insert(y);
    }
    //cout<<"a"<<endl;
    for (ll i: s){
        //cout<<i<<" "<<cnt<<endl;
        m[i] = cnt++;
    }
    sort(events.begin(), events.end(), cmp);
    for (Event e: events){
        //printf("%lld %lld %lld %d %d\n", e.x, e.yt, e.yb, e.v, e.t);
        if(e.t == 1){
            update(m[e.yb], m[e.yt], e.v);
        }
        else{
            ans[e.v] = query(m[e.yt]) - query(m[e.yt]-1);
        }
    }
    for (int i = 0; i<Q; i++){
        printf("%lld\n", ans[i]);
    }
}
