//autor Roberto Sequen

#include<iostream>
#include<stdlib.h>
#include<fstream>

using namespace std;
void menumodificar();
void pausa();
void ingresardatos();
void menubuscar();
void graficador();



//nodo central, todos los nodos que iran en medio
//de las cabeceras y los laterales
struct nodoCentral{
	int dato,x,y;
	nodoCentral* arriba;
	nodoCentral* abajo;
	nodoCentral* izquierda;
	nodoCentral* derecha;

 nodoCentral(int dato, int x, int y){
		this->dato=dato;
		this->x=x;
		this->y=y;
		arriba=NULL;
		abajo=NULL;
		izquierda=NULL;
		derecha=NULL;
	}
};

//lista columnas, los nodos que iran debajo de las cabeceras
struct listasColumna{
	nodoCentral* primero;
	nodoCentral* ultimo;

	listasColumna(){
		primero=NULL;
		ultimo=NULL;
	}

	void insertar(nodoCentral* inserta){
		if(primero == NULL){
			primero=ultimo=inserta;

		}else{
			if(inserta->y < primero->y){
				insertarFrente(inserta);

			}else if(inserta->y > ultimo->y){
				insertarFinal(inserta);

			}else{
				insertarMedio(inserta);
			}
		}
	}

	void insertarFrente(nodoCentral* inserta){
		primero->arriba = inserta;
		inserta->abajo = primero;
		primero = primero->arriba;
	}

	void insertarFinal(nodoCentral* inserta){
		ultimo->abajo = inserta;
		inserta->arriba = ultimo;
		ultimo = ultimo->abajo;
	}

	void insertarMedio(nodoCentral* inserta){
		nodoCentral* temporal1;
		nodoCentral* temporal2;
		temporal1 = primero;
		while(temporal1->y < inserta->y){
			temporal1 = temporal1->abajo;
		}
		
		temporal2 = temporal1->arriba;
		temporal2->abajo = inserta;
		temporal1->arriba = inserta;
		inserta->abajo = temporal1;
		inserta->arriba = temporal2;
	}

};

//lista horizontal, los nodos que iran en las filas
struct listaFila{

	nodoCentral* primero;
	nodoCentral* ultimo;

	listaFila(){
		primero=NULL;
		ultimo=NULL;
	}

	void insertar(nodoCentral* inserta){
		if(primero == NULL){
			primero=ultimo=inserta;
		}else{
			if(inserta->dato < primero->dato){
				primero->izquierda = inserta;
				inserta->derecha = primero;
				primero = primero->izquierda;
				
			}else if(inserta->dato > ultimo->dato){
				ultimo->derecha = inserta;
				inserta->izquierda = ultimo;
				ultimo = ultimo->derecha;
				
			}else{
				nodoCentral* temporal1;
				nodoCentral* temporal2;
				temporal1 = primero;
				while(temporal1->dato < inserta->dato){
					temporal1 = temporal1->derecha;
				}

				temporal2 = temporal1->izquierda;
				temporal2->derecha = inserta;
				temporal1->izquierda = inserta;
				inserta->derecha = temporal1;
				inserta->izquierda = temporal2;
			}
		}
	}
};

//nodos de cabecera
struct nodoCabecera{
	int x;
	nodoCabecera* siguiente;
	nodoCabecera* anterior;
	listasColumna* columna;

	nodoCabecera(int x){
		this->x=x;
		columna = new listasColumna();
		siguiente = NULL;
		anterior = NULL;
	}
};

//nodo de las cabeceras
struct cabeceras{
	nodoCabecera* primero;
	nodoCabecera* ultimo;

	cabeceras(){
		primero=NULL;
		ultimo=NULL;
	}

	void insertar(nodoCabecera* inserta){
		if(vacio()){
			primero=ultimo=inserta;
			
		}else{
			if(inserta->x < primero->x){
				insertarFrente(inserta);
				
			}else if(inserta->x > ultimo->x){
				insertarFinal(inserta);
				
			}else{
				insertarMedio(inserta);
			}
		}
	}

	bool vacio(){
		if(primero==NULL){
			return true;
		}else{
			return false;
		}
	}

	void insertarFrente(nodoCabecera* inserta){
		primero->anterior = inserta;
		inserta->siguiente = primero;
		primero = primero->anterior;
	}

	void insertarFinal(nodoCabecera* inserta){
		ultimo->siguiente = inserta;
		inserta->anterior = ultimo;
		ultimo = ultimo->siguiente;
	}

	void insertarMedio(nodoCabecera* inserta){
		nodoCabecera* temporal1;
		nodoCabecera* temporal2;
		temporal1 = primero;
		while(temporal1->x < inserta->x){
			temporal1 = temporal1->siguiente;
			}
			
		temporal2 = temporal1->anterior;
		temporal2->siguiente = inserta;
		temporal1->anterior = inserta;
		inserta->siguiente = temporal1;
		inserta->anterior = temporal2;
	}

	bool existe(int x){
		if(vacio()){
			return false;
		}else{
			nodoCabecera* temporal;
			temporal = primero;

			while(temporal!=NULL){
				if(temporal->x == x){
					//cout<<"Cabecera numero "<<temporal->x<<" ya existe"<<endl;
					return true;
				}else if(temporal->siguiente == NULL){
					//cout<<"no existe la cabecera: "<<temporal->x<<endl;
					return false;
				}

			temporal = temporal->siguiente;
			}
		}
	}

	nodoCabecera* busqueda(int x){
		if (existe(x)){
			nodoCabecera* temporal;
			temporal = primero;
				while(temporal->x != x){
					temporal = temporal->siguiente;
				}
  			return temporal;
		}else{
			cout<<"no existe cabecera"<<endl;
			return(new nodoCabecera(-1));
		}
	}
};

//nodos laterales
struct nodoLaterales{
	int y;
	nodoLaterales* siguiente;
	nodoLaterales* anterior;
	listaFila* Filas;

	nodoLaterales(int y){
		this->y=y;
		Filas = new listaFila();
		siguiente = NULL;
		anterior = NULL;
	}
};

//lista laterales
struct laterales{

	nodoLaterales* primero;
	nodoLaterales* ultimo;

	laterales(){
		primero=NULL;
		ultimo=NULL;
	}

	void insertar(nodoLaterales* inserta){
		if(vacio()){
			primero=ultimo=inserta;
			
		}else{
			if(inserta->y < primero->y){
				insertarFrente(inserta);
				
			}else if(inserta->y > ultimo->y){
				insertarFinal(inserta);
				
			}else{
				insertarMedio(inserta);
			}
		}
	}

	bool vacio(){
		if(primero==NULL){
			return true;
		}else{
			return false;
		}
	}

	void insertarFrente(nodoLaterales* inserta){
		primero->anterior = inserta;
		inserta->siguiente = primero;
		primero = primero->anterior;
	}

	void insertarFinal(nodoLaterales* inserta){
		ultimo->siguiente = inserta;
		inserta->anterior = ultimo;
		ultimo = ultimo->siguiente;
	}

	void insertarMedio(nodoLaterales* inserta){
		nodoLaterales* temporal1;
		nodoLaterales* temporal2;
		temporal1 = primero;
		while(temporal1->y < inserta->y){
			temporal1 = temporal1->siguiente;
			}
		temporal2 = temporal1->anterior;
		temporal2->siguiente = inserta;
		temporal1->anterior = inserta;
		inserta->siguiente = temporal1;
		inserta->anterior = temporal2;
	}

	bool existe(int y){
		if(vacio()){
			return false;
		}else{
			nodoLaterales* temporal;
			temporal = primero;

			while(temporal!=NULL){
				if(temporal->y == y){
					//cout<<"lateral numero "<<temporal->y<<" ya existe"<<endl;
					return true;
				}else if(temporal->siguiente == NULL){
					//cout<<"no se encontro el numero lateral "<<temporal->y<<endl;
					return false;
				}

			temporal = temporal->siguiente;
			}
		}
	}

	nodoLaterales* busqueda(int y){
		if (existe(y)){
			nodoLaterales* temporal;
			temporal = primero;
			while(temporal->y != y){
				temporal = temporal->siguiente;
			}
			return temporal;
		}else{
			cout<<"no existe lateral "<<endl;
			return(new nodoLaterales(-1));
		}
	}
};


struct MatrizOrtogonal{
	cabeceras* c;
	laterales* l;

	MatrizOrtogonal(){
		c = new cabeceras();
		l = new laterales();
	}

	void insertar(int x, int y, int inserta){

		nodoCentral* nuevonodo;
		nuevonodo = new nodoCentral(x, y, inserta);
		if(c->existe(x) == false){
			c->insertar(new nodoCabecera(x));
			cout<<"cabecera ingresada "<<x<<endl;
		}else{
			cout<<"cabecera ya existe "<<x<<endl;
		}
		
		if(l->existe(y) == false){
			l->insertar(new nodoLaterales(y));
			cout<<"lateral ingresado "<<y<<endl;
		}else{
			cout<<"lateral ya existe "<<y<<endl;
		}
		nodoCabecera* cabeceratemp;
		nodoLaterales* lateraltemp;
		cabeceratemp = c->busqueda(x);
		lateraltemp = l->busqueda(y);

		cabeceratemp->columna->insertar(nuevonodo);
		lateraltemp->Filas->insertar(nuevonodo);
		cout<<"se inserto el valor: "<<inserta<<" en la cabecera: "<<x<<" lateral: "<<y<<endl;
	}
	
	void recorrerCab(){
		if(c->primero != NULL){
			nodoCabecera* temporal = c->primero;
			while(temporal!=NULL){
				cout<<temporal->x<<"--> ";
				temporal = temporal->siguiente;
			}
		}else{
			cout<<"Lista de Cabeceras esta vacia";
		}
	}
	
	void recorrerLat(){
		if(l->primero != NULL){
			nodoLaterales* temporal = l->primero;
			while(temporal!=NULL){
				cout<<"\t"<<temporal->y<<endl;
				cout<<"\t|"<<endl;
				cout<<"\tV"<<endl;
				temporal = temporal->siguiente;
			}
		}else{
			cout<<"Lista de Laterales esta vacia";
		}
	}
	
	void recorrerLC(){
		if(c->primero != NULL){
			cout<<"\t      ";
			nodoCabecera* temporal = c->primero;
			nodoCentral* temp = temporal->columna->primero;
			while(temporal!=NULL){
				cout<<temporal->x<<" --- ";
				temporal = temporal->siguiente;
			}
			cout<<endl;
			recorrerLF();

		}else{
			cout<<"Lista de Cabeceras esta vacia";
		}
	}

	void recorrerLF(){
		if(l->primero != NULL){
			nodoLaterales* temporal = l->primero;
			while(temporal!=NULL){
				cout<<"\t"<<temporal->y;
				nodoCentral* temp = temporal->Filas->primero;
				while(temp != NULL){
					cout<<" --- "<<temp->y;
					temp = temp->derecha;
				}
				cout<<endl;
				cout<<"\t|"<<endl;
				temporal = temporal->siguiente;
			}
				
		}else{
			cout<<"Lista de Laterales esta vacia";
		}
	}
	
	void buscarcabecera(int x){
		if(c->primero != NULL){
			nodoCabecera* tempencontrado;
			tempencontrado = c->busqueda(x);
			cout<<"cabecera encontrada con exito: "<<tempencontrado->x<<endl;
		}
	}

	void buscarlateral(int y){
		if(l->primero != NULL){
			nodoLaterales* tempencont;
			tempencont = l->busqueda(y);
			cout<<"lateral encontrado con exito: "<<tempencont->y<<endl;
		}
	}

	bool buscarnodo(int inserta){
		if(c->primero != NULL){
			nodoCabecera* tempo;
			tempo = c->primero;
			while(tempo != NULL){
				nodoCentral* tempcentro;
				tempcentro = tempo->columna->primero;
				while(tempcentro->x != inserta && tempcentro != NULL){
					tempcentro = tempcentro->abajo;
				}
				if(tempcentro->x == inserta){
					return true;
				}else{
				tempo = tempo->siguiente;
				}
				return false;
			}
		}else{
			cout<<"esta vacio"<<endl;
			return false;
		}
	}
	
 	void escribirDot(){
	
	ofstream archivo;
	archivo.open("matriz.dot",ios::out);//abriendo archivo o creandolo
	archivo<<"graph matriz {"<<endl;
	archivo<<"\tlayout=dot"<<endl;
  	archivo<<"\tlabel= Matriz"<<endl;
	archivo<<"\tlabelloc = t"<<endl;
	archivo<<endl;
	if(l->primero != NULL){
			archivo<<"Inicio -- ";
			nodoLaterales* tempcabe = l->primero;
			while(tempcabe != NULL){
				archivo<<"lat"<<tempcabe->y<<" -- ";
				tempcabe = tempcabe->siguiente;
			}
			archivo<<"NULL";
			archivo<<endl;
		}
	if(c->primero != NULL){
		nodoCabecera* templat = c->primero;
		while(templat != NULL){
			archivo<<"cab"<<templat->x;
			nodoCentral* tempcent2 = templat->columna->ultimo;
			while(tempcent2 != NULL){
				archivo<<" -- c"<<tempcent2->y;
				tempcent2 = tempcent2->arriba;
			}
		templat = templat->siguiente;
		archivo<<endl;
		}
	}
	if(c->primero != NULL){
		archivo<<"rank=same {Inicio -- ";
		nodoCabecera* templat = c->primero;
		while(templat != NULL){
			archivo<<"cab"<<templat->x<<" -- ";
			templat = templat->siguiente;
		}
		archivo<<"null}"<<endl;
	}
	if(l->primero != NULL){
		nodoLaterales* tempcab = l->primero;
		while(tempcab != NULL){
			archivo<<"rank=same {lat"<<tempcab->y;
			nodoCentral* tempcent = tempcab->Filas->primero;
			while(tempcent != NULL){
				archivo<<" -- c"<<tempcent->y;
				tempcent = tempcent->derecha;
			}
		archivo<<"}"<<endl;
		tempcab = tempcab->siguiente;
		}
	}
	archivo<<"}";
	archivo.close();
	ejecutarDot();
}

	void ejecutarDot(){
	int respuesta = system("dot.exe -Tpng  matriz.dot -o matriz.png");//se crea la imagen en la ruta en donde se encuentra el programa

			if(respuesta == 0){
				system("D:\\elrober\\escritorio\\matriztarea\\matriz.png");//para abrir imagen debe poner la direccion desde donde se abrio el archivo .cpp
				cout<<"la imagen se genero exitosamente"<<endl;
			}else{
				cout<<"error en generar diagrama"<<endl;
			}

}

};




						//////////MENU DE OPCIONES////////
MatrizOrtogonal* Matriz = new MatrizOrtogonal(); // declaramos nuestra matriz principal,donde se guardaran los datos
//menu para ingresar nuevos datos
void ingresardatos(){
	char resp;
	int x,y,inserta;
	do
	{
		system("cls");
		cout<<"";
		cout<<"ingrese la cabecera: ";
		cin>>x;
		cout<<"ingrese el lateral: ";
		cin>>y;
		cout<<"ingrese nodo central: ";
		cin>>inserta;
		Matriz->insertar(x,y,inserta);
		cout<<"desea agregar mas? (s/n): ";
		cin>>resp;
	}while((resp=='s')|(resp=='S'));
}

//menu para mostrar la matriz
void menumostrar(){
	int busque;
	bool band = false;
	
	do{

		system("cls");
		cout<<"\t\t\tIngrese el valor que desea buscar"<<endl;
		cout<<"\t1. cabeceras"<<endl;
		cout<<"\t2. laterales"<<endl;
		cout<<"\t3. listas Columnas"<<endl;
		cout<<"\t4. listas Fila"<<endl;
		cout<<"\t5. regresar"<<endl;
		cin>>busque;

	switch(busque)
	{
		case 1:
			cout<<endl;
			cout<<"\t\t-------Mostrando las Cabeceras--------"<<endl;
   			Matriz->recorrerCab();
   			cout<<endl;
			pausa();
		break;

		case 2:
			cout<<endl;
			cout<<"\t\t-----Mostrando los Laterales-----"<<endl;
			Matriz->recorrerLat();
			pausa();
		break;

		case 3:
			cout<<endl;
			cout<<"\t\t-----Mostrando todas las Columnas-----"<<endl;
			Matriz->recorrerLC();
			pausa();
		break;
		case 4:
			cout<<endl;
			cout<<"\t\t-----Mostrando todas las Filas-----"<<endl;
			Matriz->recorrerLF();
			pausa();
		break;
		case 5:
			band = true;
			break;
		default:
				cout<<"El valor ingresado no esta entre las opciones"<<endl;
				break;
		}
	}while(band != true);
}


void menubuscar(){
	int busque;
	int x,y,inserta;
	bool band,nodo= false;

	do{

		system("cls");
		cout<<"\t\t\tSeleccione una opcion a buscar"<<endl;
		cout<<"\t1. Una Cabecera"<<endl;
		cout<<"\t2. Un Lateral"<<endl;
		cout<<"\t3. Un Nodo Central"<<endl;
		cout<<"\t4. regresar"<<endl;
		cin>>busque;

	switch(busque){
		case 1:
			cout<<"Ingrese la cabecera a buscar --> ";
			cin>>x;
			Matriz->buscarcabecera(x);
			pausa();
			break;
		case 2:
			cout<<"Ingrese el lateral a buscar --> ";
			cin>>y;
			Matriz->buscarlateral(y);
			pausa();
			break;
		case 3:
			cout<<"Ingrese el Nodo a Buscar--> ";
			cin>>inserta;
			if(Matriz->buscarnodo(inserta)){
				
			}else{
				cout<<"nada"<<endl;
			}
			cout<<"Nodo encontrado "<<inserta<<endl;
			pausa();
			break;
		case 4:
			band = true;
			break;
		default:
				cout<<"El valor ingresado no esta entre las opciones"<<endl;
				break;
		}
	}while(band != true);
}
//funcion para generar pausas
void pausa(){
	cout<<"pulsa una tecla para continuar...";
	getwchar();
	getwchar();
}

int main(){
	
	bool bandera=false;
	char tecla;
	int x,y,inserta;

	do
	{
		system("cls");
		cin.clear();
		cout<<"\t\t\tElija una opcion"<<endl;
		cout<<"\t1. Ingresar nuevos elementos"<<endl;
		cout<<"\t2. Buscar"<<endl;
		cout<<"\t3. Mostrar"<<endl;
		cout<<"\t4. Graficar matriz"<<endl;
		cout<<"\t5. Salir"<<endl;

		cin>>tecla;

		switch(tecla){
			case '1':
				ingresardatos();
				break;

			case '2':
				menubuscar();
				break;

			case '3':
				menumostrar();
				break;

			case '4':
				Matriz->escribirDot();
				cout<<"graficando la matriz Ortogonal ......";
				pausa();
				break;

			case '5':
				bandera=true;
				break;

			default:
				cout<<"El valor ingresado no esta entre las opciones"<<endl;
				break;

		}
	}while(bandera!=true);
 return 0;
}
