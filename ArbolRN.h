#include "Cola.h"
#include "pila.h"
#include <iostream>
#ifndef ARBOLRN_H     
#define ARBOLRN_H 
using namespace std;

struct Nodo{int info;
			bool color;				//True es Negro y False Rojo
           Nodo *izq, *der;};

class arbolRN{Nodo *raiz;
    pila<int> *listInorden;
    pila<int> *listPreorden;
	pila<int> *listPosorden;
	Nodo* buscarNodo(int clave);
    public: arbolB(){raiz = NULL;
    					listInorden = new pila<int>; 
                        listPreorden = new pila<int>;
                        listPosorden = new pila<int>;}

        void insertar(int dato);
        Nodo *buscarpadre(int dato);
        void eliminar(int dato);
        void inorden();
        void preorden();
        void posorden();
        void rotarIzquierda(int clave);
        void rotarDerecha(int clave);
        void imprimir();
       	~arbolB();
};
Nodo* arbolesRN::buscarNodo(int clave){
	//Falta esta verga
}
void arbolRN::insertar(int dato){
	Nodo *arb,*pre, *aux = new Nodo;
	aux->info=dato;
	aux->izq=NULL;
	aux->der=NULL;
	if (raiz==NULL){
		raiz=aux;
	}else {
		arb=raiz;
		while(arb != NULL){
			pre=arb;
			if(dato>arb->info){
				arb=arb->der;
			}else{
				arb=arb->izq;
			}
		}
		arb=aux;
		if(dato>pre->info){
			pre->der=arb;
		}else {
			pre->izq=arb;
		}
	}
}

Nodo * arbolB::buscarpadre(int dato){
	Nodo *aux= raiz;
	pila<Nodo *> p;
	while(aux != NULL && aux->info != dato){
		p.Push(aux);
		if (dato>aux->info){
			aux=aux->der;
		} else {
			aux=aux->izq;
		}
	}
	if(aux == NULL || aux->info != dato){
		cout<<"No se encontro un nodo con ese dato"<<endl;
		aux=NULL;
		return aux;
	} else {
		return p.Pop();
	}
}

void arbolRN::imprimir(){
	Nodo *centro,*izquierda= NULL,*derecha=NULL;
	centro=raiz;
	if(centro != NULL){
	izquierda=raiz->izq;
	derecha=raiz->der;
	}
	if (centro != NULL)
	{
		cout<<"Centro "<<centro->info<<endl;
	}
	else {
		cout<<"Centro "<<"Vacio"<<endl;	
	}
	if (izquierda != NULL)
	{
		cout<<"izquierda "<<izquierda->info<<endl;
	}
	else {
		cout<<"izquierda "<<"Vacio"<<endl;	
	}
	if (derecha != NULL)
	{
		cout<<"derecha "<<derecha->info<<endl;
	}
	else {
		cout<<"derecha "<<"Vacio"<<endl;
	}
}

void arbolRN::preorden(){
	cout<<"Entro en preorden"<<endl;
	if(raiz == NULL){
		cout << "El arbol esta vacio";
	}else{
		listPreorden->Push(raiz->info);
		
		while(!listPreorden->PilaVacia()){
			listPreorden->Pop();
			
			if(raiz->der != NULL){
				listPreorden->Push(raiz->der->info);
			}
			if(raiz->izq != NULL){
				listPreorden->Push(raiz->izq->info);
			}
		}
	}
	listPreorden->recorrer();

}

void arbolRN::inorden(){
	Nodo *aux;
	aux = raiz;
	cout<<"Entro en inorden"<<endl;
	while(!listInorden->PilaVacia() || aux != NULL){
		if(aux != NULL){
			listInorden->Push(aux->info);
			aux = aux->izq;
		}else{
			listInorden->Pop();
			aux = aux->der;
		}
	}
	listInorden->recorrer();
}

void arbolRN::posorden(){
	cout<<"Entro en postorden"<<endl;
	Nodo *aux;
	Nodo *aux2;
	aux2 = raiz;
	while(!listPosorden->PilaVacia() || aux2 != NULL){
		if(aux2 != NULL){
			listPosorden->Push(aux2->info);
			aux2 = aux2->izq;
		}else{
			if(aux2->der != NULL && aux != aux2->der){
				aux2 = aux2->der;
			}else{
				listPosorden->Push(aux->info);
			}
		}     
	}	
	listPosorden->recorrer();
}

Nodo *arbolRN::buscar_nodo(int dato){
	Nodo  *buscado=NULL;
	if(raiz->info == dato){
		return raiz;
	}else{
		buscado=raiz;
		while(buscado != NULL && buscado->info != dato){
			if(dato>buscado->info){
				buscado=buscado->der;
			}else{
				if(dato<buscado->info){
					buscado=buscado->izq;
				}
			}
		}
	}
	return buscado;
	
}
void arbolRN::eliminar(int dato){
	Nodo *eliminado= buscar_nodo(dato),aux1,w;
	Nodo *padre,padre1, *padreR, *hijoR =NULL;
	int valor;
	aux1=eliminado;
	//		Ajustar SupreionRN
		while(aux1 != raiz and aux->color==true){	//Recordar True es negro y false es Rojo	Y aux1 es x en el pseudocodigo
			padre1=buscarpadre(aux1->info);
			if(padre1->izq==aux1){
				w=padre1->der;		//Que hacer si es nulo?
				if(w->color==false){
					//Caso 1
					w->color=true;
					padre1->color=false;
					rotarIzquierda(padre1->info);
					w=padre1->der;
				}
				if((w->izq==NULL || w->izq->color==true) and (w->der==NULL || w->der->color==true)){	//Los nodos hoja tiene hijos negros (por eso el null)
					//Caso 2
					w->color=false;
					aux1=padre1;
				} else {
					if(w->der== NULL || w->der->color==true){
						//Caso 3
						w->izq->color=true;
						w->color=false;
						rotarDerecha(w->info);
						w=padre1->der;
					}
					//Caso 4
					w->color=padre1->color;
					padre1->color=true;
					w->der->color=true;
					rotarIzquierda(padre1->info);
					aux1=raiz;
				}
			}
			else {
				//Codigo simetrico
				w=padre1->izq;		//Que hacer si es nulo?
				if(w->color==false){
					//Caso 1 Simetrico
					w->color=true;
					padre1->color=false;
					rotarDerecha(padre1->info);
					w=padre1->izq;
				}
				if((w->izq==NULL || w->izq->color==true) and (w->der==NULL || w->der->color==true)){	//Los nodos hoja tiene hijos negros (por eso el null)
					//Caso 2 Simetrico
					w->color=false;
					aux1=padre1;
				} else {
					if(w->izq== NULL || w->izq->color==true){
						//Caso 3 Simetrico
						w->der->color=true;
						w->color=false;
						rotarIzquierda(w->info);
						w=padre1->izq;
					}
					//Caso 4 Simetricop
					w->color=padre1->color;
					padre1->color=true;
					w->izq->color=true;
					rotarDerecha(padre1->info);
					aux1=raiz;
				}
				
			}
		}
		aux1->color=true;
	//
	
	//cout<<eliminado->info<<endl;
	if(eliminado->der == NULL && eliminado->izq == NULL){
		padre= buscar padre(dato);
		if(eliminado->info > padre->info){
			padre->der = NULL;
		}else{
			padre->izq = NULL;
		}
	}else if(eliminado->der != NULL && eliminado->izq == NULL){
		eliminado->info=eliminado->der->info;
		eliminado->der=NUll;
	} else if(eliminado->der == NULL && eliminado->izq != NULL){
		eliminado->info=eliminado->izq->info;
		eliminado->izq=NULL;
	}else  if(eliminado->der != NULL && eliminado->izq != NULL){
		Nodo *aux=eliminado->der;
		while(aux->izq != NULL){	//Busca el nodo de la derecha mas a la izquierda
			aux=aux->izq;
		}
		valor=aux->info;			//Guarda el valor del nodo de la derecha mas de la izquierda
		eliminar(valor);			//Elimina el nodo de la derecha mas a la izquierda
		eliminado->info=valor;		//Intercambia la clave con el nodo eliminado
	}
}

void arbolRN::rotarIzquierda(int clave){
	Nodo *auxP=NULL, *aux=raiz,*aux2;
	bool encontrado=false;
	if(raiz!= NULL ){
		while(!encontrado){
			if(aux==NULL)
				encontrado=true;
			else {
				if(clave==aux->info)
					encontrado=true;
				else {
					auxP=aux;
					if(clave<aux->info){
						aux=aux->izq;
					} else{
						aux=aux->der;
					}
				}
			}
		}
			if(aux!= NULL and aux->der!= NULL){
				aux2=aux->der;
				aux->der=aux2->izq;
				aux2->izq=aux;
				if(aux!=raiz){
					if(clave<auxP->info){
						auxP->izq=aux2;
					} else {
						auxP->der=aux2;
					} 
				}
				else {
					raiz=aux2;
				}
			} else {
				cout<<"No se puede rotar el arbol"<<endl;
			}
	}
}
void arbolRN::rotarDerecha(int clave){
	Nodo *auxP=NULL, *aux=raiz,*aux2;
	bool encontrado=false;
	if(raiz!= NULL ){
		while(!encontrado){
			if(aux==NULL)
				encontrado=true;
			else {
				if(clave==aux->info)
					encontrado=true;
				else {
					auxP=aux;
					if(clave<aux->info){
						aux=aux->izq;
					} else{
						aux=aux->der;
					}
				}
			}
		}
		if(aux!= NULL and aux->izq!= NULL){
				aux2=aux->izq;
				aux->izq=aux2->der;
				aux2->der=aux;
				if(aux!=raiz){
					if(clave<auxP->info){
						auxP->izq=aux2;
					} else {
						auxP->der=aux2;
					}
				} else {
					raiz=aux2;
				}
			} else {
				cout<<"No se puede rotar el arbol"<<endl;
			}
		}
}

#endif
