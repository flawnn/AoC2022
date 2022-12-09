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

vector<string> tokenize(std::string const &str, const char delim)
{
    // construct a stream from the string
    std::stringstream ss(str);

	vector<string> command;
 
    std::string s;
	
    while (std::getline(ss, s, delim)) {
        command.push_back(s);
    }

	return command;
}

int main()
{
	#ifndef ONLINE_JUDGE
	freopen("input.txt","r",stdin);
	#endif

	string input = "";
	vector<int> displacement{0,0};
	vector<vector<int>> steps{{0,0}};
	int uniqueSteps = 0;
	while(getline(cin, input)){
		vector<string> inp = tokenize(input, ' ');
		
		if(inp[0] == "R" || inp[0] == "L"){
			displacement[0] += (inp[0] == "R" ? 1 : -1) * stoi(inp[1]);
		} else {
			displacement[1] += (inp[0] == "D" ? 1 : -1) * stoi(inp[1]);
		}

		int i = 0;
		while(i < 2){
			if(abs(displacement[i]) > 1){
				vector<int> currentPos = steps.back();

				for(int ii = 1; ii < abs(displacement[i]); ii++){
					vector<int> nextStep{currentPos[0], currentPos[1]};
					nextStep[i] = currentPos[i] + (displacement[i] > 0 ? ii : -ii);
					
					// If there is some other displacement in the other coordinate
					if(displacement[1 - i] != 0){
						nextStep[1 - i] = currentPos[1 - i] + (displacement[1 - i] / abs(displacement[1-i]));
					}

					steps.push_back(nextStep);
				}
				
				displacement[i] = displacement[i] / abs(displacement[i]);

				if(abs(displacement[1 - i]) == 1){
					displacement[1 - i] = (abs(displacement[1 - i]) - 1) * (displacement[1-i] > 0 ? 1 : -1);
				}
			}

			i++;
		}
	}

	for(int j = 0; j < 8; j++){
		vector<vector<int>> tempSteps{{0,0}};
		vector<int> lastInstruct{0,0};
		vector<int> displacement2{0,0};
		for(auto &step: steps){
			displacement2[0] += step[0] - lastInstruct[0];
			displacement2[1] += step[1] - lastInstruct[1];
			int i = 0;
			while(i < 2){
				if(abs(displacement2[i]) > 1){
					vector<int> currentPos = tempSteps.back();

					for(int ii = 1; ii < abs(displacement2[i]); ii++){
						vector<int> nextStep{currentPos[0], currentPos[1]};
						nextStep[i] = currentPos[i] + (displacement2[i] > 0 ? ii : - ii);
						
						// If there is some other displacement in the other coordinate
						if(displacement2[1 - i] != 0){
							nextStep[1 - i] = currentPos[1 - i] + (displacement2[1 - i] / abs(displacement2[1-i]));
						}

						tempSteps.push_back(nextStep);
					}
					
					displacement2[i] = displacement2[i] / abs(displacement2[i]);

					if(abs(displacement2[1 - i]) != 0){
						displacement2[1 - i] = (abs(displacement2[1 - i]) - 1) * (displacement2[1-i] > 0 ? 1 : -1);
					}
				}

				i++;
			}

			lastInstruct = step;
		}

		// FEHLER ZWISCHEN 4 und 5 bei TESTINPUT!
		steps = tempSteps;
	}

	
	set<vector<int>> ss( steps.begin(), steps.end() );

	cout << ss.size() << "\n";

}