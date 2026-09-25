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

int main()
{
	Nodo* raiz = NULL;
	int opcion;
	int valor;

	do
	{
		system("cls"); 

		cout << "\n------------------------------\n";
		cout << "\nMENU ARBOL BINARIO DE BUSQUEDA\n";
		cout << "1. Insertar \n";
		cout << "2. Buscar \n";
		cout << "3. Eliminar \n";
		cout << "4. Salir \n";

		cout << "Seleccione una opcion: ";
		cin >> opcion;

		switch (opcion)
		{
		case 1:
			cout << "Ingrese el dato a insertar: ";
			cin >> valor;
			Insertar(raiz, valor);
			break;

		case 2:
			if (raiz == NULL)
			{
				cout << "\nArbol vacio.\n";
			}
			else
			{
				cout << "Ingrese el dato a buscar: ";
				cin >> valor;
				Buscar(raiz, valor);
			}
			break;

		case 3:
			if (raiz == NULL)
			{
				cout << "\nArbol vacio.\n";
			}
			else
			{
				cout << "Ingrese el dato a eliminar: ";
				cin >> valor;
				Eliminar(raiz, valor);
			}
			break;

		case 4:
			cout << "Saliendo del programa...\n";
			break;

		default:
			cout << "Opcion invalida. Intente de nuevo.\n";
			break;
		}

		if (opcion != 4)
		{
			cout << "\nPresione cualquier tecla para continuar...";
			cin.ignore(numeric_limits<streamsize>::max(), '\n'); // limpia el buffer
			cin.get(); 
		}

	} while (opcion != 4);

	return 0;
}
