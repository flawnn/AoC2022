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


bool compare(vector<array<int,2>> p1_elms, vector<array<int,2>> p2_elms){
     bool right = true;
      int i = 0;
      for(i = 0; i < (p2_elms.size() > p1_elms.size() ? p1_elms.size() : p2_elms.size()); i++){
        if(p1_elms[i][0] != p2_elms[i][0]){
          if(p1_elms[i][0] > p2_elms[i][0]){
            right = false;
          }   

          break;
        } else if(p1_elms[i][0] == -1){
          if(p1_elms[i][1] > p2_elms[i][1]){
            right = false;
            break;
          } else if(p1_elms[i][1] < p2_elms[i][1]){                      
            break;
          }
        } else {
          if(p1_elms[i][1] > p2_elms[i][1]){
            right = false;
            break;
          }   
        }
      }

      if(i == (p2_elms.size() > p1_elms.size() ? p1_elms.size() : p2_elms.size()) && p1_elms.size() > p2_elms.size()){
          right = false;
      }

      return right;
}

int main()
{
  #ifndef ONLINE_JUDGE
  freopen("input.txt","r",stdin);
  #endif

  string p1 = "";
  string p2 = "";
  vector<int> right_order;
  int pair_indice = 1;
  array<int,2> distress = {1,2};
  while(getline(cin, p1)){
    if(p1 != ""){
      
      getline(cin, p2);

      int p1_depth = 0;
      int p2_depth = 0;
      vector<array<int,2>> p1_elms;
      vector<array<int,2>> p2_elms;
    
      vector<array<int,2>> current_depth;
      for(int i = 0; i < p1.size(); i++){
        if(p1[i] == '['){
          if(current_depth.size() != 0){
            p1_elms.insert(p1_elms.end(), current_depth.begin(), current_depth.end());
            current_depth.clear();
          }
          
          p1_depth++;
        } else if(p1[i] == ']'){
          if(current_depth.size() == 0){
            current_depth.push_back({-1, p1_depth});
          }

          if((i + 1 < p1.size() && p1[i + 1] != ']') || i + 1 >= p1.size()){
            p1_elms.insert(p1_elms.end(), current_depth.begin(), current_depth.end());
            current_depth.clear();
          }

          p1_depth--;
        } else if(p1[i] != ','){
          string gg = "";
          gg.push_back(p1[i]);
          int j = 1;

          while(p1[i+j] != ',' && p1[i+j] != ']'){
            gg += p1[i+j];
            j++;
            i++;
          }

          current_depth.push_back({stoi(gg), p1_depth});
        } 
      }

      for(int i = 0; i < p2.size(); i++){
        if(p2[i] == '['){
          if(current_depth.size() != 0){
            p2_elms.insert(p2_elms.end(), current_depth.begin(), current_depth.end());
            current_depth.clear();
          }
          
          p2_depth++;
        } else if(p2[i] == ']'){
          if(current_depth.size() == 0){
            current_depth.push_back({-1, p2_depth});
          }

          if((i + 1 < p2.size() && p2[i + 1] != ']') || i + 1 >= p2.size()){
            p2_elms.insert(p2_elms.end(), current_depth.begin(), current_depth.end());
            current_depth.clear();
          }

          p2_depth--;
        } else if(p2[i] != ','){
          string gg = "";
          gg.push_back(p2[i]);
          int j = 1;

          while(p2[i+j] != ',' && p2[i+j] != ']'){
            gg += p2[i+j];
            j++;
            i++;
          }

          current_depth.push_back({stoi(gg), p2_depth});
        } 
      }

   
      bool right = compare(p1_elms, p2_elms);

      if(right){
        right_order.push_back(pair_indice);
      }

      for(auto &elms: {p1_elms, p2_elms}){
        if(compare(elms, {{2,2}})){
          distress[0]++;
        }

        if(compare(elms, {{6,2}})){
          distress[1]++;
        }
      }

      pair_indice++;
    }
	}

  int sum = 0;  
  for(auto &ind : right_order){
    sum += ind;
  }

  cout << sum << endl;
  cout << distress[0] * distress[1] << endl;
}