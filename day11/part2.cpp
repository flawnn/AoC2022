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

int LCM = 1;
class Monkey{
	public:
	// create constructor
	Monkey(vector<long long> items, array<string, 2> operation, array<int, 3> test, vector<Monkey*> *monkeyFriends){
		this->items = items;
		this->operation = operation;
		this->test = test;
		this->monkeyFriends = monkeyFriends;
	}

	vector<long long> items;
	vector<long long> newItems;
	array<int, 3> test;
	array<string, 2> operation;
	int inspectCount = 0;
	vector<Monkey*> *monkeyFriends;

	void startRound(){
		incorporateNewItems();
		inspectCount += items.size();

		for(long long &item: items){
			int newWorry = startOp(item) % LCM;
			
			Monkey *monkey = (*monkeyFriends).at(newWorry % test[0] == 0 ? test[1] : test[2]);
			(*monkey).newItems.push_back(newWorry);
		}

		items.clear();
	}

	void incorporateNewItems(){		
		items.insert(items.end(), newItems.begin(), newItems.end());
		newItems.clear();
	}

	long long startOp(long long inp){
		if(operation[1] == "old"){
			switch(operation[0].at(0)){
			case '+':
				return (inp * 2);
				break;
			case '*':
				return pow(inp, 2);
				break;
			}
		} else {
			switch(operation[0].at(0)){
				case '+':
					return (stoi(operation[1]) + inp);
					break;
				case '*':
					return (stoi(operation[1]) * inp);
					break;
			}
		}
	}
};

struct not_digit {
    bool operator()(const char c) {
        return c != ' ' && !std::isdigit(c);
    }
};

vector<Monkey*> *currMonks = new vector<Monkey*>();
int main()
{
	#ifndef ONLINE_JUDGE
	freopen("input.txt","r",stdin);
	#endif

	string input = "";
	vector<string> splitted;
	not_digit not_a_digit;
	while(getline(cin, input)){
		if(input[0] == 'M'){
			int monkeyNum = stoi(tokenize(input, ' ')[1]);
			getline(cin, input);

			std::string::iterator end = std::remove_if(input.begin(), input.end(), not_a_digit);
			std::stringstream ss(string(input.begin(), end));
			vector<long long> items;
			for(int i = 0; ss >> i; ) {
				items.push_back(i);
    		}
			getline(cin, input);

			array<string, 2> operation;
			splitted = tokenize(input, ' '); 
			operation[1] = splitted[7];

			operation[0] = splitted[6];
			getline(cin, input);

			array<int, 3> test;
			end = std::remove_if(input.begin(), input.end(), not_a_digit);
			test[0] = stoi(string(input.begin(), end));
			LCM *= test[0];
			getline(cin, input);
			end = std::remove_if(input.begin(), input.end(), not_a_digit);
			test[1] = stoi(string(input.begin(), end));
			getline(cin, input);
			end = std::remove_if(input.begin(), input.end(), not_a_digit);
			test[2] = stoi(string(input.begin(), end));

			Monkey *monk = new Monkey(items, operation, test, currMonks);
			(*currMonks).push_back(monk);
		}
	}

	for(int i = 0; i < 10000;i++){
		for(Monkey* &monkey: (*currMonks)){
			monkey->startRound();
		}
	}

	vector<long long> inspects;
	for(Monkey* &monkey: (*currMonks)){
		inspects.push_back(monkey->inspectCount);
	}

	std::sort(inspects.begin(), inspects.end(), greater<long long>());
	cout << (inspects[0] * inspects[1]);
}