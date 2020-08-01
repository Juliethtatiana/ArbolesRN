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
    public: arbolB(){raiz = NULL;
    					listInorden = new pila<int>; 
                        listPreorden = new pila<int>;
                        listPosorden = new pila<int>;}

        void insertar(int dato);
        Nodo *buscarpadre(int dato);
        void eliminar(int dato);
        Nodo *buscar_nodo(int dato);
        void inorden();
        void preorden();
        void posorden();
        void rotarIzquierda(int clave);
        void rotarDerecha(int clave);
        void imprimir();
       	~arbolB();
};

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
	Nodo *eliminado= buscar_nodo(dato);
	Nodo *padre, *padreR, *hijoR =NULL;
	//cout<<eliminado->info<<endl;
	if(eliminado->der == NULL && eliminado->izq == NULL){
		//padre= buscar padre(dato o eliminado);
		if(eliminado->info > padre->info){
			padre->der = NULL;
		}else{
			padre->izq = NULL;
		}
	}else if(eliminado->der != NULL && eliminado->izq == NULL){
		padre->der = eliminado->der;
		delete eliminado;
	} else if(eliminado->der == NULL && eliminado->izq != NULL){
		padre->izq = eliminado->izq;
		delete eliminado;
	}else  if(eliminado->der != NULL && eliminado->izq != NULL){
		
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
