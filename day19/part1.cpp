/* Optimization Stuff */
#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,fma")
#pragma GCC optimize("unroll-loops")

/********   All Required Header Files ********/
#include <bits/stdc++.h>
#include <ranges>
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

template<typename T>
vector<int> getKeys(map<int, T> &items){
  std::vector<int> itemKeys;

  for (const auto& [key, _] : items) {
      itemKeys.push_back(key);
  }

  return itemKeys;
}

vector<int> getAvailableSteps(vector<int> &blueprint, vector<int> &stock, vector<int> &robots){
  vector<int> possibleMoves = {};

  if(stock[0] >= blueprint[1]){
    if(robots[0] < blueprint[2] && robots[0] < blueprint[3] && robots[0] < blueprint[5]){
     possibleMoves.push_back(0);
    }
  }

  if(stock[0] >= blueprint[2]){
    if(robots[1] < blueprint[4]){
      possibleMoves.push_back(1);
    }
  }

  if(stock[0] >= blueprint[3] && stock[1] >= blueprint[4]){
    if(robots[2] < blueprint[6]){
      possibleMoves.push_back(2);
    }
  } 

  if(stock[0] >= blueprint[5] && stock[2] >= blueprint[6]){
    possibleMoves.push_back(3);
  } 

  return possibleMoves;
}


int calculateNextSteps(vector<int> &blueprint, vector<int> stock, vector<int> robots, int timeRemaining){
  if(timeRemaining > 0){
    timeRemaining = timeRemaining - 1;
    vector<int> possibleMoves = getAvailableSteps(blueprint, stock, robots);
    
    int ind = 0;
    for(int &robotAmount: robots){ 
      stock[ind] += robotAmount;
      ind++;
    }

    ind = 0;
    vector<int> crackedGeodesEach;
    if(possibleMoves.size() > 0 && possibleMoves.back() == 3){
        stock[0] = stock[0] - blueprint[5];
        stock[2] = stock[2] - blueprint[6];
        robots[3] += 1;
        crackedGeodesEach.push_back(calculateNextSteps(blueprint, stock, robots, timeRemaining));
    } else if(possibleMoves.size() > 0){
      for(int &movePossible: possibleMoves){
        vector<int> tempStock = stock;
        vector<int> tempRobots = robots;
          switch(movePossible){
            case 0: {
              tempStock[0] -= blueprint[1];
              robots[movePossible] += 1;
              break;
            }

            case 1: {
              tempStock[0] -= blueprint[2];
              tempRobots[movePossible] += 1;
              break;
            }

            case 2: {
              tempStock[0] -= blueprint[3];
              tempStock[1] -= blueprint[4];
              tempRobots[movePossible] += 1;
              break;
            }
        }
        crackedGeodesEach.push_back(calculateNextSteps(blueprint, tempStock, tempRobots, timeRemaining));
      }
    }

    crackedGeodesEach.push_back(calculateNextSteps(blueprint, stock, robots, timeRemaining));

    int max = *max_element(begin(crackedGeodesEach), end(crackedGeodesEach));

    return max;
  } else {
    return stock[3];
  }
}

int main()
{
  #ifndef ONLINE_JUDGE
  freopen("input.txt","r",stdin);
  #endif
  string input = "";
  vector<vector<int>> costs;
  while(getline(cin, input)){
      vector<string> split = tokenize(input, ' ');
      vector<int> info = {stoi(split[1])};
      for(int i = 1; i <= 2; i++){
        info.push_back(stoi(split[i * 6]));
      }
      info.push_back(stoi(split[18]));
      info.push_back(stoi(split[21]));
      info.push_back(stoi(split[27]));
      info.push_back(stoi(split[30]));
      costs.push_back(info);
  }

  vector<int> qualityLevels = {};
  for(vector<int> (&blueprint): costs){
    vector<int> stock = {0,0,0,0};
    vector<int> robots = {1,0,0,0};
    int timeRemaining = 24;

    qualityLevels.push_back((blueprint)[0] * calculateNextSteps(blueprint, stock, robots, timeRemaining));
  }

  cout << *max_element(begin(qualityLevels), end(qualityLevels));
}