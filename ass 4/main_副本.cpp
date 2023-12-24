#include <iostream> 
#include <cstdio> 
#include <cstring> 
#include <cstdlib> 
#include <vector> 
#include <string> 
#include <algorithm>
#include <sstream>

using namespace std; 



struct disjoin_set{ 
  int parent[100], seniorty[100]; 
  
  int Find(int x){ 
    if (parent[x] != x)  parent[x] = Find(parent[x]); 
    return parent[x]; 
  } 
  
  void MakeSet(int vertice){ 
    parent[vertice] = vertice; 
    seniorty[vertice] = 1; 
  } 
  
  void Union(int x, int y){ 
    int xRoot = Find(x); 
    int yRoot = Find(y); 
    if (xRoot == yRoot) return; 
    if (seniorty[xRoot] < seniorty[yRoot]) 
      parent[xRoot] = yRoot; 
    else if (seniorty[yRoot] < seniorty[xRoot]) 
      parent[yRoot] = xRoot; 
    else{ 
      parent[yRoot] = xRoot; 
      seniorty[xRoot]++; 
    } 
  }
}; 


struct node{ 
  int x, y, e; 
  node(){} 
  node(int vertice1, int vertice2, int cost){ 
    x = vertice1; y = vertice2; e = cost; 
  } 
}; 

bool cmp1(const node &a, const node &b){ 
  return a.e > b.e; 
} 

bool cmp2(const node &a, const node &b){  
  return a.e < b.e; 
} 


class CountryReorganization{ 
public: 
  int cost(char ch){ 
    if ('A' <= ch && ch <= 'Z') 
      return ch - 'A'; 
    else 
      return ch - 'a' + 26; 
  }

  int getCost(vector <string> country, vector <string> build, vector <string> destroy){ 
    vector<node> DestroyRoad, BuildRoad; 
    int n = country.size(); 
    for (int i = 0; i < n; i++) 
      for (int j = 0; j < i; j++) 
        if (country[i][j] == '1'){
            DestroyRoad.push_back(node(i, j, cost(destroy[i][j])));
        } 
        else {
            BuildRoad.push_back(node(i, j, cost(build[i][j])));
        }
           
    disjoin_set S; 
    for (int i = 0; i < n; i++) 
      S.MakeSet(i); 
    vector<node>::iterator NewSet; 
    int cost = 0; 
    sort(DestroyRoad.begin(), DestroyRoad.end(), cmp1); 
    for (NewSet = DestroyRoad.begin(); NewSet != DestroyRoad.end(); NewSet++) 
      if (S.Find(NewSet->x) != S.Find(NewSet->y)) 
        S.Union(NewSet->x, NewSet->y); 
      else 
        cost += NewSet->e; 
    sort(BuildRoad.begin(), BuildRoad.end(), cmp2); 
    for (NewSet = BuildRoad.begin(); NewSet != BuildRoad.end(); NewSet++) 
      if (S.Find(NewSet->x) != S.Find(NewSet->y)){ 
        S.Union(NewSet->x, NewSet->y); 
        cost += NewSet->e; 
      } 
    return cost; 
  } 
};


int main(){

    string input1, input2, input3;
    cin >> input1 >> input2 >> input3;
    vector<string> country, build, destroy;
    istringstream c1(input1);
    istringstream b1(input2);
    istringstream d1(input3);

    string part;
    while (getline(c1, part, ',')) {
        country.push_back(part);
    }
    while (getline(b1, part, ',')) {
        build.push_back(part);
    }
    while (getline(d1, part, ',')) {
        destroy.push_back(part);
    }

    CountryReorganization NewRoad;
    int cost = NewRoad.getCost(country, build, destroy);

    cout << cost << endl;

    return 0;
}


