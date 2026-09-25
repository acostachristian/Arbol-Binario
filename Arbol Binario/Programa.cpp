#include <iostream>
#include <string>
#include <limits>

using namespace std;

struct Nodo {
	int dato;
	Nodo* izquierda;
	Nodo* derecha;
};

void Insertar(Nodo*& nodoActual, int valor) //Al inicio, nodoActual es la raiz
{
	if (nodoActual == NULL) { //Si el arbol (o subarbol) esta vacio, aqui va el nuevo nodo
		Nodo* nuevoNodo = new Nodo;
		nuevoNodo->dato = valor;
		nuevoNodo->izquierda = NULL;
		nuevoNodo->derecha = NULL;
		nodoActual = nuevoNodo;
		cout << "El nodo de valor " << valor << " se inserto correctamente en el arbol\n";
		return;
	}
	if (valor > nodoActual->dato) { //Si el valor es mayor que el nodo actual, va al subarbol derecho
		Insertar(nodoActual->derecha, valor);
	}
	else if (valor < nodoActual->dato) { //Si el valor es menor que el nodo actual, va al subarbol izquierdo
		Insertar(nodoActual->izquierda, valor);
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
	cout << "\nEl nodo de valor " << datoNodoEliminar << " fue eliminado.\n";
}

void MostrarArbol(Nodo* nodoActual, int nivel)
{
    if (nodoActual == NULL)
    {
        return;
    }

    // Primero mostramos la derecha
    MostrarArbol(nodoActual->derecha, nivel + 1);

    // Dejamos espacios dependiendo del nivel
    for (int i = 0; i < nivel; i++)
    {
        cout << "    ";
    }

    cout << nodoActual->dato << endl;

    // Después mostramos la izquierda
    MostrarArbol(nodoActual->izquierda, nivel + 1);
}

// Pide un entero por consola y NO deja continuar hasta que el usuario escriba
// un numero entero valido (sin letras en ninguna parte de la entrada).
// pDato se pasa por referencia para devolver el valor ya validado.
void leerEntero(string mensaje, int& pDato)
{
	string datoString;
	size_t position;
	bool error;

	do
	{
		try
		{
			cout << mensaje;
			cin >> datoString;
			pDato = stoi(datoString, &position);

			if (datoString.length() != position)
			{
				error = true;
				cout << "Entrada invalida, ingrese un numero entero\n" << endl;
			}
			else
			{
				error = false;
			}
		}
		catch (const exception&)
		{
			error = true;
			cout << "Entrada invalida, ingrese un numero entero\n" << endl;
		}
	} while (error);
}

int main()
{
	Nodo* raiz = NULL;
	int opcion;
	int valor;

	do
	{
		system("cls");

		cout << "------------------------------\n";
		cout << "MENU ARBOL BINARIO DE BUSQUEDA\n\n";
		cout << "1. Mostrar arbol\n";
		cout << "2. Insertar \n";
		cout << "3. Buscar \n";
		cout << "4. Eliminar \n";
		cout << "5. Salir \n\n";

		leerEntero("Seleccione una opcion: ", opcion);

		switch (opcion)
		{
		case 1:
			if (raiz == NULL)
			{
				cout << "\nArbol vacio.\n";
			}
			else
			{
				cout << "\n";
				MostrarArbol(raiz, 0);
			}
			break;
		case 2:
			leerEntero("Ingrese el dato a insertar: ", valor);
			Insertar(raiz, valor);
			break;

		case 3:
			if (raiz == NULL)
			{
				cout << "\nArbol vacio.\n";
			}
			else
			{
				leerEntero("Ingrese el dato a buscar: ", valor);
				Buscar(raiz, valor);
			}
			break;

		case 4:
			if (raiz == NULL)
			{
				cout << "\nArbol vacio.\n";
			}
			else
			{
				leerEntero("Ingrese el dato a eliminar: ", valor);
				Eliminar(raiz, valor);
			}
			break;

		case 5:
			cout << "Saliendo del programa...\n";
			break;

		default:
			cout << "Opcion invalida. Intente de nuevo.\n";
			break;
		}

		if (opcion != 5)
		{
			cout << "\nPresione cualquier tecla para continuar...";
			cin.ignore(numeric_limits<streamsize>::max(), '\n'); // limpia el buffer
			cin.get();
		}

	} while (opcion != 5);

	return 0;
}
