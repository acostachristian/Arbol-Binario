#include <iostream>
#include <string>

using namespace std;

struct Nodo {
	int dato;
	Nodo* izquierda;
	Nodo* derecha;
};

void Insertar(Nodo*& raiz, int valor)
{
	if (raiz == NULL) { //Si el arbol (o subarbol) esta vacio, aqui va el nuevo nodo
		Nodo* nuevoNodo = new Nodo;
		nuevoNodo->dato = valor;
		nuevoNodo->izquierda = NULL;
		nuevoNodo->derecha = NULL;
		raiz = nuevoNodo;
		cout << "El nodo de valor " << valor << " se inserto correctamente en el arbol\n";
		return;
	}
	if (valor > raiz->dato) { //Si el valor es mayor que el nodo actual, va al subarbol derecho
		Insertar(raiz->derecha, valor);
	}
	else if (valor < raiz->dato) { //Si el valor es menor que el nodo actual, va al subarbol izquierdo
		Insertar(raiz->izquierda, valor);
	}
	else {
		cout << "El nodo de valor " << valor << " ya existe en el arbol\n";
	}
}

Nodo* Buscar(Nodo* raiz, int valor)
{
	Nodo* nodoActual = raiz;

	while (nodoActual != NULL && nodoActual->dato != valor)
	{
		if (nodoActual->dato > valor) {
			nodoActual = nodoActual->izquierda;
		}
		else {
			nodoActual = nodoActual->derecha;
		}
	}

	if (nodoActual == NULL) {
		cout << "El nodo de valor " << valor << " no existe\n";
	}
	else {
		cout << "El nodo de valor " << valor << " fue encontrado\n";
	}

	return nodoActual; // Devuelve el puntero al nodo si existe, o NULL si no existe
}


void ElimNodoCon1o0Hijos(Nodo* nodoAEliminar, Nodo* nodoPadre, Nodo*& raiz) 
//|||Elimina nodos con UN HIJO o SIN HIJOS|||
{
	// Verificar que el nodo tiene UN SOLO hijo o NINGUNO
	bool tieneHijoIzquierdo = (nodoAEliminar->izquierda != NULL);
	bool tieneHijoDerecho = (nodoAEliminar->derecha != NULL);
	
	// El nodo reemplazo es el hijo que tenga (o NULL si no tiene)
	Nodo* nodoReemplazo = NULL;
	
	if (tieneHijoIzquierdo) {
		nodoReemplazo = nodoAEliminar->izquierda;
	}
	else if (tieneHijoDerecho) {
		nodoReemplazo = nodoAEliminar->derecha;
	}
	
	// CASO 1: Si el nodo a eliminar es la raiz
	if (nodoAEliminar == raiz) {
		raiz = nodoReemplazo; // El reemplazo (o NULL) es la nueva raiz
	}
	// CASO 2: Si el nodo a eliminar NO es la raiz
	else {
		if (nodoPadre->izquierda == nodoAEliminar) {
			nodoPadre->izquierda = nodoReemplazo;
		}
		else if (nodoPadre->derecha == nodoAEliminar) {
			nodoPadre->derecha = nodoReemplazo;
		}
	}
	
	delete nodoAEliminar;
}

void ElimNodoCon2Hijos(Nodo* nodoAEliminar, Nodo*& raiz) //|||SOLO USAR SI EL NodoAEliminar TIENE HIJOS|||
{
	Nodo* nodoPadreDeReemplazo = nodoAEliminar;
	Nodo* nodoReemplazo = nodoAEliminar->derecha;
	if (nodoReemplazo->izquierda != NULL) {
		while (nodoReemplazo->izquierda != NULL)
		{
			nodoPadreDeReemplazo = nodoReemplazo;
			nodoReemplazo = nodoReemplazo->izquierda;
		}
	}
	else {
		nodoReemplazo = nodoAEliminar->izquierda;
		while (nodoReemplazo->derecha != NULL)
		{
			nodoPadreDeReemplazo = nodoReemplazo;
			nodoReemplazo = nodoReemplazo->derecha;
		}
	}
	nodoAEliminar->dato = nodoReemplazo->dato;

	ElimNodoCon1o0Hijos(nodoReemplazo, nodoPadreDeReemplazo, raiz);
}

void Eliminar(Nodo*& raiz, int datoNodoEliminar)
{
	Nodo* nodoActual = raiz;
	Nodo* nodoPadre = NULL;

	while (nodoActual != NULL && nodoActual->dato != datoNodoEliminar)
	{
		nodoPadre = nodoActual;
		if (nodoActual->dato > datoNodoEliminar) {
			nodoActual = nodoActual->izquierda;
		}
		else {
			nodoActual = nodoActual->derecha;
		}
	}

	if (nodoActual == NULL) {
		cout << "El nodo de valor " << datoNodoEliminar << " no existe\n"; 
		return;
	}
	if (nodoActual->izquierda != NULL && nodoActual->derecha != NULL)
	{
		ElimNodoCon2Hijos(nodoActual, raiz);
	}
	else
	{
		ElimNodoCon1o0Hijos(nodoActual, nodoPadre, raiz);
	}
}

void Mostrar(Nodo* raiz, int nivel)
{
	if (raiz == NULL)
	{
		return;
	}

	Mostrar(raiz->derecha, nivel + 1);

	for (int i = 0; i < nivel; i++)
	{
		cout << "\t";
	}

	cout << raiz->dato << endl;
	Mostrar(raiz->izquierda, nivel + 1);
}

int main()
{
  return 0;
}
