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

class Node {
	public:
	// Constructor for Node
	 Node(int data, bool directory, string name) {
        this->data = data;
		this->directory = directory;
		this->parent = NULL;
		this->name = name;
    }

	Node(int data, bool directory, string name, Node &parent) {
        this->data = data;
		this->directory = directory;
		this->parent = &parent;
		this->name = name;
    }

    vector<Node*> children;
    Node *parent;
	// For Directory the size of it alltogether, for files just filesize
    int data;
	string name;
	bool directory;

	// Add Child
	void addChild(Node* child){
		child->parent = this;
		this->children.push_back(child);
	}

	void setChildren(vector<Node*> children){
		this->children = children;
	}
};


int main()
{
	#ifndef ONLINE_JUDGE
	freopen("input.txt","r",stdin);
	#endif

	string input = "";
	Node *root = new Node(0, true, "/");
	Node *currentDir = root;
	vector<Node*> directoryNodes;
	while(getline(cin, input)){
		if(input[0] == '$'){
			vector<string> command = tokenize(input, ' ');

			if(command[1] == "cd"){
				// Maybe already sum up file sizes per directory before going out?
				if(command[2] == ".."){
					int sum = 0;

					for(auto &child: (*currentDir).children){
						sum += (*child).data;
					}

					(*currentDir).data = sum;
					
					directoryNodes.push_back(currentDir);

					currentDir = (*currentDir).parent;
				} else {
					string name = command[2];

					// Find in Vector of Strings element that matches other string
				
					auto it = std::find_if((*currentDir).children.begin(), (*currentDir).children.end(), [&name](Node* n) {
						return n->name == name;
					});

					if(it != (*currentDir).children.end()){
						currentDir = (*it);
					}
				}
			}

		} else {
			vector<string> obj = tokenize(input, ' ');

			if(obj[0] == "dir"){
				Node *newNode = new Node(0, true, obj[1]);
				(*currentDir).addChild(newNode);
			} else {
				Node *newNode = new Node(stoi(obj[0]), false, obj[1]);
				(*currentDir).addChild(newNode);
			}
		}
	}

	// After input ended go back to root node, to calculate all directory sizes
	while((*currentDir).name != "/"){
		int sum = 0;

		for(auto &child: (*currentDir).children){
			sum += (*child).data;
		}

		(*currentDir).data = sum;

		directoryNodes.push_back(currentDir);

		currentDir = (*currentDir).parent;
	}

	// Calculating free space on drive
	int spaceToBeFreed = 30000000 - 70000000;

	for(auto &child: (*root).children){
		spaceToBeFreed += (*child).data;
	}

    // Getting best possible directory to delete
	int smallest = 70000000;
	for(auto &child: directoryNodes){
		if((*child).data >= spaceToBeFreed && (*child).data < smallest){
			smallest = (*child).data;
		}
	}

	write(smallest);
}