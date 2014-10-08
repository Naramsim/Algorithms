/*
	alias del topSort in pseudocodice delle slide di Montresor,
	basato su dfs-stack,
	viene dato in input un DAG (grafo diretto aciclico),
	stampa un ordinameto topologico.
	
	possibile input:
	5 5
	3 4
	3 2
	2 0
	2 4
	0 1
*/

#include <iostream>
#include <fstream>
#include <vector>
#include <stack>
using namespace std;

struct nodo{
  int valore;   
  vector<int> vic;
  bool visited;
  nodo(){
		visited=false;
		valore= -1;
  }
};

void tsDfs(vector<nodo>& grafo , nodo& u , stack<int>& s){
	
	u.visited=true;
	
	for(int t=0;t<u.vic.size();t++){
		int posizioneVicino = u.vic[t];
		if(grafo[posizioneVicino].visited==false){
			tsDfs(grafo,grafo[posizioneVicino],s);
		}
	}
	
	s.push(u.valore);
}

stack<int> topSort(vector<nodo>& grafo){ //tipo stack, per ora non serve
	//i nodi sono già tutti marcati come non visitati, ma meglio essere sicuri
	for(int c=0;c<grafo.size();c++){
		grafo[c].visited=false;
	}
	
	stack<int> s;// NOTA: meglio creare stack<int> , è più leggero
	
	for(int u=0;u<grafo.size();u++){//per tutti i nodi...
		if(grafo[u].visited==false){
			tsDfs(grafo,grafo[u],s);
		}
	}
	
	return s;
}


int main(){
  ifstream in("input.txt");
  ofstream out("output.txt", ios::out);
  int N,M;
  in>>N>>M;
  vector<nodo> grafo;
  grafo.resize(N);
  //solo DAG!!!!
  
  for(int i=0;i<N;i++){
	grafo[i].valore=i;
  }
  
  for(int i=0;i<M;i++){
	int from, to;
	in>>from>>to;
		
	if(grafo[from].valore==-1){
		grafo[from].valore=from;
	}
	if(grafo[to].valore==-1){
		grafo[to].valore=to;
	}
		
	grafo[from].vic.push_back(to);
	   
  }

  stack<int> s = topSort(grafo);
  
  while (s.empty() == false){
		int nodoDaPrintare = s.top();
		out<<nodoDaPrintare<< " ";
		s.pop();
	}
  
  cout<<endl;
  /*
  for(int i=0;i<N;i++){
	cout<<"Nodo "<<grafo[i].valore<<" ha "<<grafo[i].vic.size()<<" vicini: ";
		for(int j=0;j<grafo[i].vic.size();j++){
				int posizioneVicino= grafo[i].vic[j];
				cout<<grafo[posizioneVicino].valore<<" ";
		}
		cout<<endl;
	
  }*/
  return 0;
}
