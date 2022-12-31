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

template <typename t> void move(std::vector<t>& v, size_t oldIndex, size_t newIndex)
{
    if (oldIndex > newIndex)
        std::rotate(v.rend() - oldIndex - 1, v.rend() - oldIndex, v.rend() - newIndex);
    else        
        std::rotate(v.begin() + oldIndex, v.begin() + oldIndex + 1, v.begin() + newIndex + 1);
}

int main()
{
  #ifndef ONLINE_JUDGE
  freopen("input.txt","r",stdin);
  #endif
  
  string input = "";
  vector<string> field;
  while(getline(cin, input)){
    if(input == "") { 
      getline(cin, input);
      break;
    }

    field.push_back(input);
  }

  int row = 0;
  pair<int, int> leftMostUpperField;
  while(row < field.size()){
    auto rField = find_if(field[row].begin(), field[row].end(), [](char el ){return el != ' ' && el != '#';});

    if(rField != field[row].end()){
      leftMostUpperField = {row, abs(distance(rField, field[row].begin()))};
      break;
    }

    row++;
  }
  
  int orientation = 0;
  int num = 0;
  pair<int, int> position = leftMostUpperField;
  for (int i = 0; i < input.size(); i++) {
    if (isdigit(input[i])) {
      num = atoi(input.substr(i).c_str());
      i += std::to_string(num).size() - 1;

      row = position.first;
      int column = position.second;
      switch(orientation){
        case 0: {
          for(int ii = 0; ii < num; ii++){
            column++;

            if(column > field[row].size() - 1){
              string::iterator leftMostIndex = find_if(field[row].begin(), field[row].end(), [](char el ){return el != ' ';});
             
              if(*leftMostIndex == '#'){
                column--;
                break;
              } else {
                column = abs(distance(leftMostIndex, field[row].begin()));
                continue;
              }
            }

            if(field[row][column] == '#'){
              column--;
              break;
            }
          }

          break;
        }

        case 1: {
          for(int ii = 0; ii < num; ii++){
            vector<string> reverse;
            reverse_copy(field.begin(), field.end(), back_inserter(reverse));
            vector<string>::iterator downMostIndex = find_if(reverse.begin(), reverse.end(), [&column](string el ){return el[column] != ' ';});
            row++;

            if(row > field.size() - 1 - abs(distance(downMostIndex, reverse.begin()))){
              vector<string>::iterator upMostIndex = find_if(field.begin(), field.end(), [&column](string el ){return el[column] != ' ';});
             
              if((*upMostIndex)[column] == '#'){
                row--;
                break;
              } else {
                row = abs(distance(upMostIndex, field.begin()));
                continue;
              }
            }

            if(field[row][column] == '#'){
              row--;
              break;
            }
          }
          break;
        }

        case 2: {
          for(int ii = 0; ii < num; ii++){
            string::iterator leftMostIndex = find_if(field[row].begin(), field[row].end(), [](char el ){return el != ' ';});
            column--;

            if(column < abs(distance(leftMostIndex, field[row].begin()))){
              int rightMostIndex = field[row].size() - 1;
              if(field[row][rightMostIndex] == '#'){
                column++;
                break;
              } else {
                column = rightMostIndex;
                continue;
              }
            }

            if(field[row][column] == '#'){
              column++;
              break;
            }
          }

          break;
        }

        case 3: {
          for(int ii = 0; ii < num; ii++){
            vector<string>::iterator upMostIndex = find_if(field.begin(), field.end(), [&column](string el ){return el[column] != ' ';});
            row--;

            if(row < abs(distance(upMostIndex, field.begin()))){    
              vector<string> reverse;
              reverse_copy(field.begin(), field.end(), back_inserter(reverse));
              vector<string>::iterator downMostIndex = find_if(reverse.begin(), reverse.end(), [&column](string el ){return el[column] != ' ';});
        
              if(field[field.size() - 1 - abs(distance(downMostIndex, reverse.begin()))][column] == '#'){
                row++;
                break;
              } else {
                row = field.size() - 1 - abs(distance(downMostIndex, reverse.begin()));
                continue;
              }
            }

            if(field[row][column] == '#'){
              row++;
              break;
            }
          }
          break;
        }
      }

      position = {row, column};
    } else {
      switch(input[i]){
        case 'R':
          orientation++;
          orientation %= 4;
          break;
        case 'L':
          orientation--;
          if(orientation < 0) orientation = 3;
          break;
      }
    }
  }

  position = {position.first + 1, position.second + 1};
  cout << position.first << " " << position.second << ": " << position.first * 1000 + position.second * 4 + orientation <<  endl;
}