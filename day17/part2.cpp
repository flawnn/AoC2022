/* Optimization Stuff
#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,fma")
#pragma GCC optimize("unroll-loops")
*/

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

int max_height(vector<vector<pair<int,int>>>::iterator begin, vector<vector<pair<int,int>>>::iterator end){
  int highest = 0;
  for(;begin != end; begin++){
    if((*begin).back().second > highest){
      highest = (*begin).back().second;
    }
  }

  return highest;
}

pair<int,int> max_height(vector<vector<pair<int,int>>>::iterator begin, vector<vector<pair<int,int>>>::iterator end, int height){
  pair<int,int> highest = {0,0};
  for(;begin != end; begin++){
    vector<pair<int,int>> relev;

    // copy only positive numbers:
    copy_if((*begin).begin(), (*begin).end(), std::back_inserter(relev), [&height = height](pair<int,int> i){return i.first <= height;} );

    if((relev).back().second > highest.second){
      highest = (relev).back();
    }
  }

  return highest;
}

int main()
{
  #ifndef ONLINE_JUDGE
  freopen("input.txt","r",stdin);
  #endif
  string input = "";
  getline(cin, input);
  int counter = 0;
  vector<vector<pair<int,int>>> rockHeights = {{{0,0}},{{0,0}},{{0,0}},{{0,0}},{{0,0}},{{0,0}},{{0,0}}};
  // iterate through string as iterator
  auto it = input.begin();
  while(counter < 2022){
    // get highest int from vector of integers
    int highestRock = max_height(rockHeights.begin(), rockHeights.end());
    int turn = counter % 5;
    int height = highestRock + 4;

    switch(turn){
      /* #### */
      case 0:
       { pair<int, int> expansion = {2, 5};
        int highest =  max_height(rockHeights.begin() + expansion.first, rockHeights.begin() + expansion.second + 1);
        while(height > highest){
          if(it == input.end()){
            it = input.begin();
          }

          if(*it == '<'){
            if(expansion.first - 1 >= 0 && max_height(rockHeights.begin() + expansion.first - 1, rockHeights.begin() + expansion.first, height) < height){
              expansion.first--;
              expansion.second--;
            }
          } else if(expansion.second + 1 < 7  && max_height(rockHeights.begin() + expansion.second + 1, rockHeights.begin() + expansion.second + 2, height) < height){
            expansion.first++;
            expansion.second++;
          }

          highest = max_height(rockHeights.begin() + expansion.first, rockHeights.begin() + expansion.second + 1, height);

          if(height - 1 <= highest){
            for(auto iit = rockHeights.begin() + expansion.first; iit != rockHeights.begin() + expansion.second + 1;iit++){
              if(height > (*(iit)).back().second){
                (*iit).push_back({height,height});
              }
            }
          }
          

          height--;
          it++;
        }
        break;}
      /* 

      .#.
      ###
      .#.

      */
      case 1:
       { pair<int, int> expansion = {2, 4};
        int highest =  max_height(rockHeights.begin() + expansion.first, rockHeights.begin() + expansion.second + 1);
        while(height > highest){
          if(it == input.end()){
            it = input.begin();
          }
          
          if(*it == '<'){
            if(expansion.first - 1 >= 0 && max_height(rockHeights.begin() + expansion.first - 1, rockHeights.begin() + expansion.first, height + 1) < height + 1){
              expansion.first--;
              expansion.second--;
            }
          } else if(expansion.second + 1 < 7 && max_height(rockHeights.begin() + expansion.second + 1, rockHeights.begin() + expansion.second + 2, height + 1) < height + 1){
            expansion.first++;
            expansion.second++;
          }

          highest = max_height(rockHeights.begin() + expansion.first, rockHeights.begin() + expansion.second + 1, height + 1);

          if(height - 1 <= highest){
            auto iit = rockHeights.begin() + expansion.first;
            if(height > (*(iit)).back().second){
              (*(iit)).push_back({height + 1, height + 1});
            }

            iit = rockHeights.begin() + expansion.first + 1;
            if(height > (*(iit)).back().second){
              (*(iit)).push_back({height, height+2});
            }
            
            iit = rockHeights.begin() + expansion.second;
            if(height > (*(iit)).back().second){
              (*(iit)).push_back({height + 1, height + 1});
            }
          }

          height--;
          it++;
        }
        break;}
      /*

      ..#
      ..#
      ###

      */
      case 2:
        {pair<int, int> expansion = {2, 4};
        int highest =  max_height(rockHeights.begin() + expansion.first, rockHeights.begin() + expansion.second + 1);
        while(height > highest){
          if(it == input.end()){
            it = input.begin();
          }
          
          if(*it == '<'){
            if(expansion.first - 1 >= 0 && max_height(rockHeights.begin() + expansion.first - 1, rockHeights.begin() + expansion.first, height) < height){
            expansion.first--;
            expansion.second--;
            }
          } else if(expansion.second + 1 < 7 && max_height(rockHeights.begin() + expansion.second + 1, rockHeights.begin() + expansion.second + 2, height + 2) < height){
            expansion.first++;
            expansion.second++;
          }

          highest = max_height(rockHeights.begin() + expansion.first, rockHeights.begin() + expansion.second + 1, height);

          if(height - 1 <= highest){
              auto iit = rockHeights.begin() + expansion.first;
              if(height > (*(iit)).back().second){
                (*(iit)).push_back({height, height});
              }

              iit = rockHeights.begin() + expansion.first + 1;
              if(height > (*(iit)).back().second){
                (*(iit)).push_back({height, height});
              }
              
              iit = rockHeights.begin() + expansion.second;
              if(height > (*(iit)).back().second){
                (*(iit)).push_back({height, height + 2});
              }
          }

          height--;
          it++;
        }
        break;} 
      /*
      
      #
      #
      #
      #
      
      */
      case 3:
       { pair<int, int> expansion = {2, 2};
        int highest =  max_height(rockHeights.begin() + expansion.first, rockHeights.begin() + expansion.second + 1);
        while(height > highest){
          if(it == input.end()){
            it = input.begin();
          }

          if(*it == '<'){
            if(expansion.first - 1 >= 0 && max_height(rockHeights.begin() + expansion.first - 1, rockHeights.begin() + expansion.first, height + 3) < height){
              expansion.first--;
              expansion.second--;
            }
          } else if(expansion.second + 1 < 7 && max_height(rockHeights.begin() + expansion.second + 1, rockHeights.begin() + expansion.second + 2, height + 3) < height){
            expansion.first++;
            expansion.second++;
          }

          highest = max_height(rockHeights.begin() + expansion.first, rockHeights.begin() + expansion.second + 1, height);

          if(height - 1 <= highest){
            auto iit = rockHeights.begin() + expansion.first;
            if(height > (*(iit)).back().second){
              (*(iit)).push_back({height, height + 3});
            }
          }

          height--;
          it++;
        }
        break; }
      /*
      
      ##
      ##
    
      */
      case 4:
       { pair<int, int> expansion = {2, 3};
        int highest = max_height(rockHeights.begin() + expansion.first, rockHeights.begin() + expansion.second + 1);
        while(height > highest){
          if(it == input.end()){
            it = input.begin();
          }

          if(*it == '<'){
            if(expansion.first - 1 >= 0 && max_height(rockHeights.begin() + expansion.first - 1, rockHeights.begin() + expansion.first, height + 1) < height){
              expansion.first--;
              expansion.second--;
            }
          } else if(expansion.second + 1 < 7 && max_height(rockHeights.begin() + expansion.second + 1, rockHeights.begin() + expansion.second + 2, height + 1) < height){
            expansion.first++;
            expansion.second++;
          }
          
          highest = max_height(rockHeights.begin() + expansion.first, rockHeights.begin() + expansion.second + 1, height);

          if(height - 1 <= highest){
            auto iit = rockHeights.begin() + expansion.first;
            if(height > (*(iit)).back().second){
              (*(iit)).push_back({height, height + 1});
            }

            iit = rockHeights.begin() + expansion.second;
            if(height > (*(iit)).back().second){
              (*(iit)).push_back({height, height+1});
            }
          }

          height--;
          it++;
        }
        break; }
    }
    
    counter++;
  }

  cout << max_height(rockHeights.begin(), rockHeights.end());
}

// didn't get to finish