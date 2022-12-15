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

class Info{
  public:
    array<int, 2> sensorPos;
    array<int, 2> baconPos;
    int maxDistance;

    Info(array<int, 2> sensorPos, array<int, 2> baconPos){
      this->sensorPos = sensorPos;
      this->baconPos = baconPos;
      this->maxDistance = abs(sensorPos[0] - baconPos[0]) + abs(sensorPos[1] - baconPos[1]);
    }
};

int main()
{
  #ifndef ONLINE_JUDGE
  freopen("input.txt","r",stdin);
  #endif

  string input = "";
  vector<Info*> relevantInfos;
  vector<array<int,2>> spotsCoveredRanges = {};
  vector<int> relevantBacons = {};
  const int toBeCheckedY = 2000000;
  while(getline(cin, input)){
      vector<string> split = tokenize(input, '=');
      Info *info = new Info({stoi(split[1]), stoi(split[2])}, {stoi(split[3]), stoi(split[4])});
      
      if(info->baconPos[1] == toBeCheckedY){
        if(!contains(relevantBacons, info->baconPos[0])){
          relevantBacons.push_back(info->baconPos[0]);
        }
      }

      if(info->sensorPos[1] + info->maxDistance >= toBeCheckedY && info->sensorPos[1] - info->maxDistance <= toBeCheckedY){
        int availableXSteps = info->maxDistance - abs(info->sensorPos[1] - toBeCheckedY);
        int pos1Max = info->sensorPos[0] + availableXSteps;
        int pos2Min = info->sensorPos[0] - availableXSteps;

        bool alreadyCovered = false;
        for(vector<array<int,2>>::iterator rangee = spotsCoveredRanges.begin(); rangee != spotsCoveredRanges.end(); ){
          array<int,2> range = *rangee;
          if(range[1] >= pos2Min && range[1] <= pos1Max){
            if(range[0] > pos1Max){
              pos1Max = range[0];
            }

            rangee = spotsCoveredRanges.erase(rangee);
            // remove that range from the register and just add pos1max, pos2min
          } else if(range[0] >= pos2Min && range[0] <= pos1Max){
            if(range[1] < pos2Min){
              pos2Min = range[1];
            }

            rangee = spotsCoveredRanges.erase(rangee);
            // remove that range from the register and just add pos1max, pos2min
          } else {
            if(range[1] < pos2Min && range[0] > pos1Max){
              alreadyCovered = true;
              break;
            }

            rangee++;
          }
        }

        if(!alreadyCovered){
          spotsCoveredRanges.push_back({pos1Max, pos2Min});
        }
      }
	}

  int coveredSpots = 0;

  for(auto &range: spotsCoveredRanges){
    coveredSpots += abs(range[0] - (range[1] - 1));
  }

  cout << coveredSpots - relevantBacons.size() << endl;
}