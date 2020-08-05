/*
Julieth Tatiana Riaño Mora - 20181020107
Juan David Rosero Torres - 20181020071
Cristian Camilo Martinez Rey 20181020021
*/
#include <iostream>
#include "ArbolRN.h"
using namespace std;

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

int main(int argc, char** argv) {
	arbolRN arbol;
	arbol.insertar(5);
	arbol.insertar(7);
	arbol.insertar(3);
	arbol.imprimir();
	cout<<endl;
	arbol.insertar(4);
	arbol.imprimir();
	arbol.imprimir(4);
	cout<<endl;
	arbol.insertar(2);
	arbol.imprimir();
	cout<<endl;
	arbol.imprimir(2);
	cout<<endl;
	arbol.imprimir(4);
	cout<<endl;
	arbol.insertar(9);
	arbol.imprimir(9);
	arbol.insertar(8);
	arbol.imprimir();
	cout<<endl;
	arbol.imprimir(7);
	arbol.imprimir(8);
	cout<<endl;
/*	cout<<"Eliminacion"<<endl;
	cout<<endl<<endl;
	arbol.eliminar(5);
	arbol.imprimir();
	//arbol.imprimir(3);*/
	arbol.preorden();
	arbol.inorden();
	arbol.posorden();
	return 0;
}
