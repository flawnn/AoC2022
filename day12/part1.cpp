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

struct not_digit {
    bool operator()(const char c) {
        return c != ' ' && !std::isdigit(c);
    }
};


class Node {
  public:
  // Constructor for Node
    Node(char data, array<int, 2> location) {
        this->data = data;
        this->location = location;
        this->parent = NULL;
    }

    Node(char data, array<int, 2> location, Node &parent) {
        this->data = data;
              this->location = location;
      this->parent = &parent;
    }

    vector<Node*> children;
    Node *parent;
    array<int, 2> location;
    int move = -1;
    char data;

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
  string ascii_lowercase = "abcdefghijklmnopqrstuvwxyzE";
  vector<vector<Node*>> maze;
  Node* startingNode;
  Node* goalNode;
  Node* winningNode;
  int i = 0;
  deque<Node*> frontier;
  while(getline(cin, input)){
    vector<Node*> row;
    Node *node;

    int j = 0;
    for(char& c : input) {
      if(c == 'S'){
        node = new Node('a', {i, j});
		node->move = 0;
        startingNode = node;
      } else if(c == 'E'){
        node = new Node('E', {i, j});
        goalNode = node;
      } else {
          node = new Node(c, {i, j});
      }
	  row.push_back(node);
      j++;
    }
    maze.push_back(row);
    i++;
  }

  frontier.push_back(startingNode);

  while(frontier.size() != 0){
    // get first item in froniter
    Node *last = frontier.front();
    frontier.pop_front();
	
    // checking if win condition
    if(last->data == 'E'){
        winningNode = last;
        break;
    }

    // then finding new moves and pushing to frontier
    for(int ii = -1; ii < 2; ii++){
		if(ii != 0){
			int row = last->location[0];
			int column = last->location[1];

			if((row + ii >= 0 && row + ii < maze.size())){
				Node *next = maze[row + ii][column];
				if(next->move == -1){
					if(ascii_lowercase.find(last->data) + 1 >= ascii_lowercase.find(next->data)){
					next->parent = last;
					next->move = last->move + 1;
					frontier.push_back(next);
					}
				}
			}

			if((column + ii >= 0 && column + ii < maze[row].size())){
				Node *next = maze[row][column + ii];
				if(next->move == -1){
					if(ascii_lowercase.find(last->data) + 1 >= ascii_lowercase.find(next->data)){
						next->parent = last;
						next->move = last->move + 1;
						frontier.push_back(next);
					}
				}
			}
		}
    }
  }

    cout << winningNode->move;
}