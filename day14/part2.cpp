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

int main()
{
  #ifndef ONLINE_JUDGE
  freopen("input.txt","r",stdin);
  #endif

  string input = "";
  map<int,vector<int>> m;
  int lowest = 0;
  while(getline(cin, input)){
    stringstream ss(input);
    string x,y;
    array<int, 2> last = {-1 , -1};

    while(getline(ss, x, ',')){
      getline(ss, y, '>');

      if(stoi(y) > lowest) lowest = stoi(y);

      if(last[0] != -1){
        if(last[0] == stoi(x)){
          for(int i = (last[1] < stoi(y) ? last[1] : stoi(y)); i <= (last[1] < stoi(y) ? stoi(y) : last[1]);i++){
            if(!(m.count(stoi(x)))){
              m[stoi(x)] = vector<int>();
            }

            m[stoi(x)].push_back(i);
          }
        } else {
          for(int i = (last[0] < stoi(x) ? last[0] : stoi(x)); i <= (last[0] < stoi(x) ? stoi(x) : last[0]); i++){
            if(!(m.count(i))){
              m[i] = vector<int>();
            }

            m[i].push_back(stoi(y));
          }
        }
      }

      last = {stoi(x), stoi(y)};
    }
	}

  bool comingToHalt = true;
  int sandcounter = 0;
  while(comingToHalt){
    array<int, 2> sand = {500, 0};
    bool moving = true;
    while(moving){
      if(!(m.count(sand[0] - 1))){
        m[sand[0] - 1] = vector<int>();
      }

      if(!(m.count(sand[0] + 1))){
        m[sand[0] + 1] = vector<int>();
      }

      if(sand[1] + 1 < lowest + 2){
        if(!contains(m[sand[0]], sand[1] + 1)){
          sand[1]++;
        } else if(!(contains(m[sand[0] - 1], sand[1] + 1))){
          sand[0]--;
          sand[1]++;
        } else if(!(contains(m[sand[0] + 1], sand[1] + 1))){
          sand[0]++;
          sand[1]++;
        } else {
          moving = false;
          if(sand[0] == 500 && sand[1] == 0) 
            comingToHalt = false;
          m[sand[0]].push_back(sand[1]);
        }
      } else {
        m[sand[0]].push_back(sand[1]);
        moving = false;
      }
    }

    sandcounter++;
  }

  cout << sandcounter << endl;
}