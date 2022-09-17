#ifndef CABECERA_H_INCLUDED
#define CABECERA_H_INCLUDED

#include <iostream>
using namespace std;

class Estado {
public:
    int bmc[3];

    Estado() { //Constructor
        for(int i = 0; i<3; i++) {
            bmc[i]=0;
        }
        genEstadoInicial(); // se genera el estado inicial : 1 3 3
    };

    void operator=(Estado e){
      for(int i = 0 ; i<3; i++){
        bmc[i]=e.bmc[i];
      }
    };

    void operator=(int e){
      for(int i = 0 ; i<3; i++){
        bmc[i]=e;
      }
    };

    bool operator==(Estado e){
      bool flag = true;
      for(int i=0;i<3;i++){
        if(bmc[i]!=e.bmc[i]){
          flag=false;
        }
      }
      return flag;
    };

     bool operator!=(Estado e){
      bool flag = false;
      for(int i=0;i<3;i++){
        if(bmc[i]!=e.bmc[i]){
          flag=true;
        }
      }
      return flag;
    };

    void genEstadoInicial(){
      bmc[0]=1;
      bmc[1]=3;
      bmc[2]=3;
    };

    bool testEstadoObjetivo(){
      bool objetivo= true;
      int obj[3]={0,0,0};
      for(int i = 0; i < 3; i++){
        if(bmc[i]!= obj[i]){
          objetivo = false;
        }
      }
      return objetivo;
    }


    //funciones miembro
    void print() {
        for(int i = 0; i<3; i++) {
            cout << bmc[i] <<"\t" ;
        }
        cout << endl;
    }


};

class Nodo {
public:
  Nodo *p;
  Nodo **h;
  int fR;
  int n;
  Estado e;

  nodo(){
    p=NULL;
    h=NULL;
    fR=0;
    n=0;
  };

  Nodo* autoApuntador(){
    return this;
  };

  void funcionSucesor(){
    int cant_H = 5;
    int fact = -1;
    int action[3][5];
    action[0][0]=1;
    action[1][0]=1;
    action[2][0]=1;

    action[0][1]=1;
    action[1][1]=2;
    action[2][1]=0;

    action[0][2]=1;
    action[1][2]=0;
    action[2][2]=2;

    action[0][3]=1;
    action[1][3]=1;
    action[2][3]=0;

    action[0][4]=1;
    action[1][4]=0;
    action[2][4]=1;

    int actval[5]={1,1,1,1,1};


    for(int i = 0; i < 5; i++){
      Estado aux;
      if (e.bmc[0] == 1)
        fact = -1;
      else
        fact = 1;
      for(int j = 0; j < 3; j++){
        aux.bmc[j] = e.bmc[j] + (fact*action[j][i]);
      }
      if(aux.bmc[1] < aux.bmc[2] || 3 - aux.bmc[1] < 3 - aux.bmc[2] || aux.bmc[1] > 3 || aux.bmc[1] < 0 || aux.bmc[2] > 3 || aux.bmc[2] < 0){
        actval[i]=0;
        cant_H--;
      }
    }

    expansion(cant_H);

    int cont=0;
    for(int i = 0; i < 5; i++){
      if(actval[i] == 1){
        for(int j = 0; j < 3; j++){
          h[cont] -> e.bmc[j] = h[cont] -> e.bmc[j] + (fact*action[j][i]);
        }
        cont++;
      }
    }
  };

  void expansion(int nh){
    fR = nh;
    h = new Nodo* [fR];
    for(int i = 0; i < fR; i++){
      h[i] = new Nodo;
      h[i] -> p = this;
      h[i] -> n = n+1;
      h[i] -> e = e;
    }
  };

  void eliminarArbol(Nodo *pnt){
    for (int a = 0; a < pnt -> fR; a++){
      if (pnt -> h[a] != NULL)
        eliminarArbol(pnt -> h[a]);
    }
    delete pnt;
    pnt = NULL;
  };

  Nodo* hallarRaiz(Nodo *pnt){
    Nodo *Padre;
    if ( pnt -> p != NULL)
      Padre = hallarRaiz(pnt -> p);
    else
      Padre = pnt;
      pnt -> e.print();
      return Padre;
  }



};

class frontera{
public:
  Nodo **f;
  int nEf;

  frontera(){
    f = NULL;
    nEf = 0;
  };

  ~frontera(){
    for ( int C = 0; C < nEf; C++){
      f[C] = NULL;
    }
    delete [] f;
    f = NULL;
    nEf = 0;
  };

  void nuevoElemento(Nodo *n){
    Nodo **aux;
    if(nEf == 0){
      aux = new Nodo(nEf + 1);

    }


  }

};

#endif // CABECERA_H_INCLUDED
