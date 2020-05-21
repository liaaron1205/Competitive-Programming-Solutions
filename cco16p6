//CCO 2016 P6 - Pirates
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> pii;
#define pb push_back
#define mp make_pair
struct Node{
	ll v, sum;
	int size, freq, p;
	Node *c[2];
	Node(ll a, int b){
		v = a;
		size = b;
		freq = b;
		sum = freq*a;
		p = rand();
		c[0] = c[1] = 0;
	}
} *rt;
void push_up (Node *n){
	n->size = n->freq;
	n->sum = n->freq * n->v;
	if (n->c[0]){	
		n-> size += n->c[0]->size;
		n-> sum += n->c[0]-> sum;
	}
	if (n->c[1]){
		n-> size += n-> c[1] ->size;
		n-> sum += n-> c[1] -> sum;
	}
}
void rotate (Node *&n, bool d){
	Node *tmp = n->c[d];
    n->c[d] = tmp->c[!d];
    tmp->c[!d] = n;
    push_up(n); 
    push_up(tmp); 
    n = tmp;
}
void insert (Node *&n, ll a, int b){ //val, freq
	if (b==0) return;
	if (!n){
		n = new Node (a, b);
		return;
	}
	else if (n->v==a){
		n-> freq += b;
	}
	else{
		bool d = n->v < a;
		insert (n->c[d], a, b);
		if (n->c[d]->p < n->p) 
			rotate (n, d); 
	}
	push_up(n);
}
ll findFirstK (Node *n, int k){
	if (k==0) return 0;
	//if (n->size==k) return n->sum;
	if (n->c[0]&&n->c[0]->size>=k) return findFirstK (n->c[0], k);
	ll ans = 0;
	if (n->c[0]){
		ans += n->c[0]->sum;
		k -= n->c[0]->size;
	}
	//cout<<ans<<endl;
	int tmp = min (k, n->freq);
	ans += n->v * tmp;
	k-= tmp;
	ans += findFirstK(n->c[1], k);
	return ans;
}
void remove (Node *&n, int k){
	if (k==0) return;
	if (n->size == k){
		n = 0;
		return;
	}
	if (n->c[1]&&n->c[1]->size >= k) remove (n->c[1], k);
	else{
		if (n->c[1]){
			k -= n->c[1]->size;
			n->c[1] = 0;		
		}
		int tmp = min (n->freq, k);
		n->freq -= tmp;
		k -= tmp;
		if (n->freq==0){
			n = n->c[0];
			remove (n, k);
		}
	}
	push_up(n);
}
void traverse (Node *n){
	if (!n) return;
	traverse (n->c[0]);
	printf("%lld %d %lld %d\n", n->v, n->freq, n->sum, n->size);
	traverse (n->c[1]);
}
int n;
ll K, reference = 0;
int main(){
	//freopen ("in.txt", "r", stdin);
	//freopen ("out.txt", "w", stdout);
	scanf("%d%lld", &n, &K);
	for (int i = 1, v; i<=n; i++){
		scanf("%d", &v);
		ll tot = findFirstK(rt, v-1);
		tot -= reference*(v-1);
		tot += v-1;
		if (tot<=K){
			printf("%lld\n", K-tot);
			remove(rt, i-v);
			reference--;
			insert (rt, K-tot+reference, 1);
			insert (rt, reference, i-v);
		}	
		else{
			printf("-1\n");
			insert (rt, -1+reference, 1);
		}
		//traverse(rt);
		//cout<<reference<<"\n\n";
	}	
}
