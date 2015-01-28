/*
	questo programma trova la massima componente fortemente connessa di un grafo orientato.
	possibile input:
	8 14
	0 1
	1 2
	1 4
	1 5
	2 3
	2 6
	3 2
	3 7
	4 0
	4 5
	5 6
	6 5
	7 3
	7 6
	output: 3
*/
#include <iostream>
#include <fstream>
#include <vector>
#include <stack>
#include <list>
#include <algorithm>
using namespace std;

int risultato=0; // da scrivere nell'output

struct nodo{
  int valore;   
  vector<int> vic; //vicini
  bool visited; //è visitato?
  int idComponente; //id della componente a cui appartiene
  nodo(){
	visited=false;
	valore= -1;
	idComponente=-1;
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

stack<int> topSort(vector<nodo>& grafo){ 
	for(int c=0;c<grafo.size();c++){
		grafo[c].visited=false;
	}
	stack<int> s;
	for(int u=0;u<grafo.size();u++){
		if(grafo[u].visited==false){
			tsDfs(grafo,grafo[u],s);
		}
	}
	return s;
}

int ccdfs(vector<nodo>& grafo , int& counter, int& indice){
	grafo[indice].idComponente=counter;
	for(int t=0 ; t<grafo[indice].vic.size() ; t++){
		int posizioneVicino = grafo[indice].vic[t];
		if(grafo[posizioneVicino].idComponente==-1){
			ccdfs( grafo , counter , posizioneVicino);
		}
	}
}

void cc(vector<nodo>& grafo , stack<int>& s , int N){
	int counter=-1;
	vector<int> componenti; 
	while(!(s.empty())){
		int indice= s.top();
		s.pop();
		if(grafo[indice].idComponente==-1){
			counter=counter+1;
			ccdfs(grafo , counter , indice);
		}
	}
	
	++counter;//era partito da -1
	componenti.resize(counter); 
	
	for(int i=0;i<N;i++){
		int posizioneIdComponente = grafo[i].idComponente;
		componenti[posizioneIdComponente]+=1;
  }
	
	for(int i=0;i<componenti.size();i++){
		cout<<"la componente con id="<<i<<" ha tot nodi: ";
		cout<<componenti[i]<<"\n";
		if(componenti[i]>risultato){
			risultato=componenti[i];
		}
  }
}

void scc(vector<nodo>& grafo , vector<nodo>& grafoT , int N){ //Strongly Connected Component
	stack<int> s = topSort(grafo);
	cc(grafoT , s , N);
}

int main(){
  ifstream in("input.txt");
  ofstream out("output.txt", ios::out);
  int N,M;
  in>>N>>M;
  vector<nodo> grafo;
  vector<nodo> grafoT;//trasposto
  grafo.resize(N);
  grafoT.resize(N);
  
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
	if(grafoT[from].valore==-1){
		grafoT[from].valore=from;
	}
	if(grafoT[to].valore==-1){
		grafoT[to].valore=to;
	}	
    grafo[from].vic.push_back(to);
    grafoT[to].vic.push_back(from);   
  }
  
  scc(grafo,grafoT,N);
  cout<<endl<<risultato;
  out<<risultato;
  
  in.close();
  out.close();
  
  return 0;
}
