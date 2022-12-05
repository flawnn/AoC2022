/* Optimization Stuff */
#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,fma")
#pragma GCC optimize("unroll-loops")

/********   All Required Header Files ********/
#include <bits/stdc++.h>
using namespace std;

/*******  All Required define Pre-Processors and typedef Constants *******/
#define SCD(t) scanf("%d",&t)
#define SCLD(t) scanf("%ld",&t)
#define SCLLD(t) scanf("%lld",&t)
#define SCC(t) scanf("%c",&t)
#define SCS(t) scanf("%s",t)
#define SCF(t) scanf("%f",&t)
#define SCLF(t) scanf("%lf",&t)
#define MEM(a, b) memset(a, (b), sizeof(a))
#define FOR(i, j, k, in) for (int i=j ; i<k ; i+=in)
#define RFOR(i, j, k, in) for (int i=j ; i>=k ; i-=in)
#define REP(i, j) FOR(i, 0, j, 1)
#define RREP(i, j) RFOR(i, j, 0, 1)
#define all(cont) cont.begin(), cont.end()
#define rall(cont) cont.end(), cont.begin()
#define FOREACH(it, l) for (auto it = l.begin(); it != l.end(); it++)
#define IN(A, B, C) assert( B <= A && A <= C)
#define MP make_pair
#define PB push_back
#define INF (int)1e9
#define EPS 1e-9
#define PI 3.1415926535897932384626433832795
#define MOD 1000000007
#define read(type) readInt<type>()
const double pi=acos(-1.0);
typedef pair<int, int> PII;
typedef vector<int> VI;
typedef vector<string> VS;
typedef vector<PII> VII;
typedef vector<VI> VVI;
typedef map<int,int> MPII;
typedef set<int> SETI;
typedef multiset<int> MSETI;
typedef long int int32;
typedef unsigned long int uint32;
typedef long long int int64;
typedef unsigned long long int  uint64;

/****** Template of some basic operations *****/
template<typename T, typename U> inline void amin(T &x, U y) { if(y < x) x = y; }
template<typename T, typename U> inline void amax(T &x, U y) { if(x < y) x = y; }
/**********************************************/

/****** Template of Fast I/O Methods *********/
template <typename T> inline void write(T x)
{
	int i = 20;
	char buf[21];
	// buf[10] = 0;
	buf[20] = '\n';

	do
	{
		buf[--i] = x % 10 + '0';
		x/= 10;
	}while(x);
	do
	{
		putchar(buf[i]);
	} while (buf[i++] != '\n');
}

template <typename T> inline T readInt()
{
	T n=0,s=1;
	char p=getchar();
	if(p=='-')
		s=-1;
	while((p<'0'||p>'9')&&p!=EOF&&p!='-')
		p=getchar();
	if(p=='-')
		s=-1,p=getchar();
	while(p>='0'&&p<='9') {
		n = (n<< 3) + (n<< 1) + (p - '0');
		p=getchar();
	}

	return n*s;
}

void tokenize(std::string const &str, const char delim,
            std::vector<std::string> &out)
{
    // construct a stream from the string
    std::stringstream ss(str);
 
    std::string s;
    while (std::getline(ss, s, delim)) {
        out.push_back(s);
    }
}

int main()
{
	#ifndef ONLINE_JUDGE
	freopen("input.txt","r",stdin);
	#endif

    int count = 0;
	string input = "";
	vector<vector<char>> args;
	bool fin = false;
	while(getline(cin, input)){
		if(fin){
			vector<string> inp;
			tokenize(input, ' ', inp);

			vector<char> tba;
			for(int i = 0; i < stoi(inp[1]); i++){
				char val = args[stoi(inp[3]) - 1].back();
				args[stoi(inp[3]) - 1].pop_back();
				tba.push_back(val);
			}

			reverse(tba.begin(), tba.end());
			args[stoi(inp[5]) - 1].insert(args[stoi(inp[5]) - 1].end(), tba.begin(), tba.end());
		} else {
			if(std::any_of(input.begin(), input.end(), ::isdigit)){
				fin = true;
				getline(cin, input);
				std::for_each(args.begin(), args.end(), [](vector<char> &n){ std::reverse(n.begin(), n.end()); });
				continue;
			}

			if(args.empty()){
				for(int i = 0; i < (input.size() + 1) / 4; i++){
					string cargo = input.substr(4*i, 4*i + 3);
					args.push_back(vector<char>{});	

					if(cargo[1] != ' '){
						args[i].push_back(cargo[1]);
					}
				}								
			} else {
				for(int i = 0; i < (input.size() + 1) / 4; i++){
					string cargo = input.substr(4*i, 4*i + 3);	

					if(cargo[1] != ' '){
						args[i].push_back(cargo[1]);
					}
				}	
			}
		}
	}

	string output = "";
	for(vector<char> &vec: args){
		output.push_back(vec.back());
	}

	cout << output;
}