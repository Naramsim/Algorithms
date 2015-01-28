#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
using namespace std;

struct nodo{
  int valore; //valore, in realtà non servirebbe, il valore è l'indice del vector grafo iniziale  
  vector<int> vic; //vicini
  bool visited;
  int livello;// distanza del nodo sorgente
  nodo(){
  visited=false;//per sicurezza
  valore= -1;
  }
  
};



int intraDiametro( vector<nodo> grafo , nodo s , int posizioneIniziale , int numeroNodi ){
  
  for(int i=0 ; i<numeroNodi ; i++){//marco tutti i nodi come non visitati
    grafo[i].visited=false;
    grafo[i].livello=-1;
  }
  
  int distanzaDalPiuLontano=0;
  queue<nodo> coda; //creo la coda per il BFS
  
  grafo[posizioneIniziale].visited=true; //segno s visitato e lo metto in coda (è il primo e unico elemento, per ora)
  grafo[posizioneIniziale].livello=0; //livello iniziale=0
  coda.push(s);//da notare che s è un nodo mentre posizioneIniziale è il valore del nodo
  
  while(!(coda.empty())){
    nodo u = (coda.front());
    
    int valore = u.valore;
    //cout<<valore<<" ";
    coda.pop();
    
    //cout<<"distanza dal nodo pari a: "<<u.livello<<endl;
    if(u.livello>distanzaDalPiuLontano){
      distanzaDalPiuLontano=u.livello;
    }
    
    for(int t=0 ; t<u.vic.size() ; t++){
      
      int posizioneVicino = grafo[valore].vic[t]; //prendo la posizione del primo vicino
      
      if(grafo[posizioneVicino].visited==false){
        grafo[posizioneVicino].visited=true; //marco il vicino come visitato
        grafo[posizioneVicino].livello=grafo[valore].livello +1;
        coda.push(grafo[posizioneVicino]); 
      }
    }
  }
  //cout<<"distanza massima"<<distanzaDalPiuLontano<<endl;
  return distanzaDalPiuLontano;
}


int main(){
  ifstream in("input.txt");
  int N,M;
  in>>N>>M;
  vector<nodo> grafo;
  grafo.resize(N);
  
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
  grafo[to].vic.push_back(from);
  }

  int diametro=0;
  for(int i=0;i<N;i++){
    int intraD = intraDiametro(grafo,grafo[i],i,N);
    if( intraD > diametro){
      diametro=intraD;
    }
  }
  
  ofstream out("output.txt",ios::out);
  out<<diametro;
  cout<<diametro;
  in.close();
  out.close();
  
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
