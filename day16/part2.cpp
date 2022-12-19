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

template <typename T> bool contains(vector<T> v, T x){
  return std::find(v.begin(), v.end(), x) != v.end();
}

class Node {
	public:
	// Constructor for Node
	 Node(string name, int pressure, vector<string> connectedNodes) {
    this->name = name;
		this->pressure = pressure;
    this->connectedNodes = connectedNodes;
    }

    vector<string> connectedNodes;
    int pressure;
  	string name;
    int distance = 0;
    vector<pair<string, int>> distanceToVents;
};

vector<Node*> nodes;
vector<Node*> vents;
Node* startingNode;

vector<pair<string, int>> calcDistance(Node *startingNode, vector<Node*> vents, vector<Node*> nodes){
  vector<pair<string, int>> distanceToVents;
  deque<Node*> frontier;
  vector<string> visitedNodes;
  startingNode->distance = 0;
  frontier.push_back(startingNode);

  while(frontier.size() != 0){ 
    // get first item in froniter
    Node *last = frontier.front();
    frontier.pop_front();
	
    if(contains(vents, last) && startingNode->name != last->name){
        distanceToVents.push_back({last->name, last->distance});
    }

    if(distanceToVents.size() == vents.size()){
      break;
    }

    // then finding new moves and pushing to frontier
    for(auto &nodeName: last->connectedNodes){
      if(!contains(visitedNodes, nodeName)){
        vector<Node*>::iterator it = find_if(nodes.begin(), nodes.end(), [&](Node* node) { return node->name == nodeName; });
        (*it)->distance = last->distance + 1;
        frontier.push_back(*it);
        visitedNodes.push_back(nodeName);
      }
    }
  }

  return distanceToVents;
}

pair<pair<vector<pair<Node*, int>>, int>, pair<vector<pair<Node*, int>>, int>> calcBestPath(pair<vector<pair<Node*, int>>, int> currentCombo1, pair<vector<pair<Node*, int>>, int> currentCombo2, int minutesLeft1, int minutesLeft2, bool firstTurn){
   pair<vector<pair<Node*, int>>, int> bestCombo;
   pair<vector<pair<Node*, int>>, int> bestOtherCombo;
   pair<Node*, int> lastStep;
   pair<vector<pair<Node*, int>>, int> currentCombo;
   pair<vector<pair<Node*, int>>, int> otherCombo;
   int minutesLeft;

  if(!firstTurn){
      currentCombo = currentCombo2;
      bestCombo = currentCombo2;
      bestOtherCombo = currentCombo1;
      otherCombo = currentCombo1;
      lastStep = (currentCombo2.first.back());
      minutesLeft = minutesLeft2;
  } else {
      currentCombo = currentCombo1;
      bestCombo = currentCombo1;
      bestOtherCombo = currentCombo2;
      otherCombo = currentCombo2;
      lastStep = (currentCombo1.first.back());
      minutesLeft = minutesLeft1;
  }
      if(minutesLeft > 0){
    for (auto& [name, distance] : lastStep.first->distanceToVents) {
if(distance + 1 > minutesLeft || currentCombo.first.end() != find_if(currentCombo.first.begin(), currentCombo.first.end(), 
        [&namee = name](const std::pair<Node*, int> & t) -> bool { 
            return t.first->name == namee;
        }
      ) || otherCombo.first.end() != find_if(otherCombo.first.begin(), otherCombo.first.end(), 
        [&namee = name](const std::pair<Node*, int> & t) -> bool { 
            return t.first->name == namee;
        }
      )){
        continue;
      }

      Node *vent = *find_if(vents.begin(), vents.end(), [&name = name](Node* node) { return node->name == name; });
      int potential = (minutesLeft - (distance + 1)) * vent->pressure;
      vector<pair<Node*, int>> nextCombo = currentCombo.first;
      nextCombo.push_back({vent, potential});
      pair<pair<vector<pair<Node*, int>>, int>, pair<vector<pair<Node*, int>>, int>> nextSteps;
      if(firstTurn){
        nextSteps = calcBestPath({nextCombo, currentCombo.second + potential}, currentCombo2, minutesLeft - (distance + 1), minutesLeft2, !firstTurn);
      } else {
        nextSteps = calcBestPath(currentCombo1, {nextCombo, currentCombo.second + potential}, minutesLeft1,  minutesLeft - (distance + 1), !firstTurn);
      }

      if((nextSteps.first.second + nextSteps.second.second) > (bestCombo.second + bestOtherCombo.second)){
        if(firstTurn){
          bestCombo = nextSteps.first;
          bestOtherCombo = nextSteps.second;
        } else {
          bestCombo = nextSteps.second;
          bestOtherCombo = nextSteps.first;
        }
      }
    }
  } else {
    bestCombo.second -= bestCombo.first.back().second;
    bestCombo.first.pop_back();
  }

  if(firstTurn){
    return {bestCombo, bestOtherCombo};
  } else {
    return {bestOtherCombo, bestCombo};
  }

}

int main()
{
  #ifndef ONLINE_JUDGE
  freopen("input.txt","r",stdin);
  #endif
  string input = "";

  while(getline(cin, input)){
    vector<string> command = tokenize(input, ' ');
    string name = command[1];

    vector<string> tempPres = tokenize(command[4], '=');
    int pressure = stoi(tempPres[1]);

    vector<string> connectedNodes;
    for(int i = 9; i < command.size();i++){
      string str2="";

      for (const auto c: command[i]){
          if(c != ','){
              str2.push_back(c);
          }
      }

      connectedNodes.push_back(str2);
    }

    Node *node = new Node(name, pressure, connectedNodes);
    nodes.push_back(node);

    if(name == "AA"){
      startingNode = node;
    }

    if(pressure != 0){
      vents.push_back(node);
    }
  }

  for(auto &vent: vents){
    vector<pair<string, int>> distanceToVents = calcDistance(vent, vents, nodes);

    vent->distanceToVents = distanceToVents;
  }

  // And once for the start
  vector<pair<string, int>> distanceToVents = calcDistance(startingNode, vents, nodes);
  startingNode->distanceToVents = distanceToVents;
  pair<pair<vector<pair<Node*, int>>, int>, pair<vector<pair<Node*, int>>, int>>  bestPath = calcBestPath({{{startingNode, 0}}, 0}, {{{startingNode, 0}}, 0}, 26, 26, true);
  
  cout << bestPath.first.second + bestPath.second.second<< endl;
}