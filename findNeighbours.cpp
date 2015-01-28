/*
	find all nodes that a node can reach
*/

#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

struct nodo{
	nodo(){
		visited=false;
	}
	vector<int> vic;
	bool visited;
};

vector<nodo> grafo;
static int count=0;



int trovaVicini(vector<nodo>& grafo , int step){
	
	if(grafo[step].visited==true){
		count--;
	}else if(grafo[step].vic.empty()==true){
		grafo[step].visited=true;
	}else{
		grafo[step].visited=true;
		for(int v:grafo[step].vic){
			++count;cout<<"count++";
			trovaVicini(grafo,v);
  		}
	}
}



int main(){
	ifstream in("input.txt");
	ofstream out("output.txt");
	int N,M,P;
	in>>N>>M>>P;
	grafo.resize(N);
  
	for(int i=0;i<M;i++){
		int from, to;
		in>>from>>to;
		grafo[from].vic.push_back(to);
	}
	
	count++;//raggiungo me stesso
	trovaVicini(grafo,P);

	cout<<"input ha tot raggiungibilità: "<<count<<"\n\n\n";
	out<<count;
	  
  return 0;
}
