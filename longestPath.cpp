/*
	find the longest path in a DAG graph 
*/

#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

struct nodo{
  int valore; 
  vector<int> vic; //vicini
  bool entraArco;
  int livello;// distanza del nodo sorgente
  nodo(){
  entraArco=false;
  valore= -1;
  livello=0;
  }
};

int daPrintare=0;

int camminolungo(vector<nodo>& grafo, nodo& u, int liv){
	if(u.livello<liv){
		u.livello=liv;
	}
	if(u.livello>daPrintare){
		daPrintare=u.livello;
	}
	int valore= u.valore;
	
	for(int t=0;t<u.vic.size();t++){
		int posizioneVicino=u.vic[t];
			camminolungo(grafo,grafo[posizioneVicino],liv+1);		
	}
}


int main(){
  ifstream in("input.txt");
  ofstream out("output.txt",ios::out);
  int N,M;
  in>>N>>M;
  vector<nodo> grafo; //DAG
  grafo.resize(N);
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
		grafo[to].entraArco=true;
	}

	grafo[from].vic.push_back(to);
  
  }

  for(int i=0; i<grafo.size();i++){
  	if(grafo[i].entraArco==false){
  		camminolungo(grafo, grafo[i], 0);
  	}
  }
  
  out<<daPrintare;
  in.close();
  out.close();
  
  return 0;
}
