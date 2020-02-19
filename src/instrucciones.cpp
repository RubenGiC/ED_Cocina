#include<iostream>
#include<string>
#include <stack>
#include <iomanip>      // std::setw
#include <sstream>      // std::stringstream
#include <string.h>

#include "instrucciones.h"
#include "acciones.h"
#include "arbolbinario.h"
#include "ingredientes.h"

using namespace std;

//operador >>
istream& operator>> (istream& is, Instrucciones& ins){
	string line;
	stack<ArbolBinario<string>> pilaArbol;
	int cont=0;
	
	while(!is.eof()) {
		
		string instruccion;
		string ingr;

		getline(is, line);//recibe la linea

		//si no esta vacia
		if(line.length()>0){

			//recorro la linea para saber el numero de espacios
			for(int i=0;i<line.length();i++){
				if(line[i]==' ')
					cont++;
			}
			//cojo la primera que es la instrucción
			line = strtok((char *) line.c_str()," ");
			
			if(line.length()>0)
				instruccion = line;
			else
				instruccion = "";

			//si hay más de 0 espacios es que hay un ingrediente
			if(cont>0){
				line = strtok(NULL,"\n");

				ingr = line;
			}

			//cout << "instruccion: " << instruccion << " ingrediente: " << ingr << endl;
			
			//creo un miniarbol
			ArbolBinario<string> aux(instruccion);

			//busco la ariedad
			unsigned char ariedad = ins.acc.buscar(instruccion);

			//si es 1 la ariedad
			if(ariedad=='1'){

				//si contiene un ingrediente
				if(ingr.length()>0)
					//inserto a la izquierda el ingrediente
					aux.Insertar_Hi(aux.getRaiz(),ingr);

				//si no tiene ingrediente
				else{
					//inserto el subarbol de la pila al arbol
					aux.Insertar_Hi(aux.getRaiz(),pilaArbol.top());
					//borro el subarbol de la pila
					pilaArbol.pop();
				}
				//guardo el arbol completo
				pilaArbol.push(aux);

			//si la ariedad es 2
			}else{

				if(instruccion.compare("Add")==0){
					//inserto el ingrediente
					aux.Insertar_Hd(aux.getRaiz(),ingr);
					//inserto el subarbol
					aux.Insertar_Hi(aux.getRaiz(),pilaArbol.top());
					pilaArbol.pop();
				}else{
					//inserta los 2 subarboles
					aux.Insertar_Hd(aux.getRaiz(),pilaArbol.top());
					pilaArbol.pop();
					aux.Insertar_Hi(aux.getRaiz(),pilaArbol.top());
					pilaArbol.pop();
				}

				//guarda el arbol completo
				pilaArbol.push(aux);
			}
			cont = 0;		
			/*cout << "-------------------------------------------------------------------" << endl;
			cout << aux << endl;
			cout << "-------------------------------------------------------------------" << endl;*/
		}
	}
	ins.datos=pilaArbol.top();
	
	return is;
}

string Instrucciones::Esquema(ArbolBinario<string>::nodo n, string& pre){
  int i;
  string arbol="";
  
  if (n.nulo())
  	arbol += pre + "-- x\n"; 
    //cout << pre << "-- x" << endl;
  else {
  	arbol += pre + "-- " + *n;
  	//cout << pre << "-- " << *n;
  	if(n!=datos.getRaiz()){//si no es la raiz

  		if(!n.padre().hd().nulo()){// si no es nula el hijo derecha

	  		if(n.padre().hd()==n){//y son iguales
	  			arbol += "(DR)";
	  			//cout << " (DR)";
	    		//cout << pre << "D-- " << *n << endl;
	  		}
	  	}
	  	//lo mismo pero con izquierda
	    if(!n.padre().hi().nulo())
	    	if(n.padre().hi()==n)
	    		arbol += "(IZ)";
	    		//cout << " (IZ)";
	    		//cout << pre << "I-- " << *n << endl;
    	/*else
  			cout << pre << "S-- " << *n << endl;*/
  	}/*else{
  		cout << pre << "-- " << *n << endl;
  	}*/
	arbol += "\n";
	//cout << endl;
	    	
    if (!n.hd().nulo() || !n.hi().nulo()) {// Si no es una hoja
      pre += "   |";
      arbol += Esquema(n.hd(), pre);
      pre.replace(pre.size()-4, 4, "    ");
      arbol += Esquema (n.hi(), pre);
      pre.erase(pre.size()-4, 4);    
    }
  }
  return arbol;
}

string Instrucciones::ComoElFichero(ArbolBinario<string>::nodo n){
	int i;
  	string arbol="";
  	string ingre="";
  	char aux;
  
  
	if (!n.nulo()){
	  	
  		if(!n.hd().nulo()){// si no es nula el hijo derecha
  			aux = acc.buscar(*(n.hd()));//busco si es una accion el hijo de la derecha
		    if(aux == '\0')//si no es una accion, es decir NULL
  				ingre = *(n.hd());//guardo el ingrediente
	  	}
	  	//lo mismo pero con izquierda
	    if(!n.hi().nulo()){

	    	aux = acc.buscar(*(n.hi()));//busco si es una accion el hijo de la izquierda
		    if(aux == '\0'){//si no es una accion (NULL)
  				ingre = *(n.hi());//guardo el ingrediente
  			}
  		}
		
		    	
	    if (!n.hd().nulo() || !n.hi().nulo()) {// Si no es una hoja

	    	arbol += ComoElFichero(n.hi());//recorro el hijo de la izquierda

	    	arbol += ComoElFichero (n.hd());//y despues el de la derecha
	    }

	    aux = acc.buscar(*n);//busco si es una accion el nodo actual

	    bool encontrado = false;

	    //si es una accion entra
	    if(aux != '\0'){

	    	if(!n.hd().nulo()){// si no es nula el hijo derecha
	  			aux = acc.buscar(*(n.hd()));//busco si es una accion
			    if(aux == '\0')//si no es una accion
	  				encontrado = true;
		  	}
		  	//lo mismo pero con izquierda
		    if(!n.hi().nulo())
		    	aux = acc.buscar(*(n.hi()));//busco si es una accion
			    if(aux == '\0')//si no es una accion
	  				encontrado = true;

	  		//si encuentra en alguno de sus hijos un ingrediente
	  		if(encontrado)
	  			//muestro la instruccion y el ingrediente
	    		arbol += *n + " " + ingre + "\n";
	    	else
	    		arbol += *n + "\n";//en caso contrario solo muestro la instruccion
	    }
	}
  return arbol;
}

string Instrucciones::mostrarArbol(bool tip){
	ArbolBinario<string>::nodo nod(datos.getRaiz());
	string arbol="";
	if(tip)
		arbol = Esquema(nod,arbol);
	else
		arbol = ComoElFichero(nod);
	return arbol;
}

void Instrucciones::combinarInstrucciones(Instrucciones i1, Instrucciones i2){
	ArbolBinario<string> aux("Acompañar");
	ArbolBinario<string> arb1(i1.getArbol());
	ArbolBinario<string> arb2(i2.getArbol());

	aux.Insertar_Hi(aux.getRaiz(),arb1);
	aux.Insertar_Hd(aux.getRaiz(),arb2);

	datos = aux;
}

bool Instrucciones::existeIngrediente(Ingredientes ing, ArbolBinario<string>::nodo n){
	
	bool existe=true;//por defecto existe el ingrediente
	char aux;//para obtener el ingrediente de instrucciones
	string ingre="";//guarda el ingrediente
	  	
  		if(!n.hd().nulo()){// si no es nula el hijo derecha
  			aux = acc.buscar(*(n.hd()));//busco si es una accion el hijo de la derecha
		    if(aux == '\0'){//si no es una accion, es decir NULL
  				ingre = *(n.hd());//guardo el ingrediente
		     }
	  	}
	  	//lo mismo pero con izquierda
	    if(!n.hi().nulo()){
	    	aux = acc.buscar(*(n.hi()));//busco si es una accion el hijo de la izquierda
		    if(aux == '\0'){//si no es una accion (NULL)
  				ingre = *(n.hi());//guardo el ingrediente
  			}
  		}
  		//si es un ingrediente
		if(ingre.length()>0){
			//compruebo si no existe en ingredientes pasada por parametro
			if(ing.buscarIngrediente(ingre).getNombre()=="Undefined")
				return false;//si no existe devuelvo false
		}
		    	
	    if (!n.hi().nulo()) {// Si es una hoja
	    	//llamo recussivamente al mismo metodo pero con el hijo de la izquierda
	    	//pasandile ing y el hijo izquierdo de n
	    	existe = existeIngrediente(ing,n.hi());
	    }
	    if(!n.hd().nulo()){// Si es una hoja
	    	//llamo recussivamente al mismo metodo pero con el hijo de la derecha
	    	//pasandile ing y el hijo derecha de n
	    	existe = existeIngrediente(ing,n.hd());
	    }
	    return existe;
}

bool Instrucciones::existeIngredientes(Ingredientes ing){
	//llamo al metodo que recorrera el arbol, pasandole el objeto Ingredientes y el nodo raiz
	bool existe=existeIngrediente(ing,this->datos.getRaiz());
	//si despues de recorrer el arbol devuelve el resultado
	return existe;
}

//operador <<
ostream& operator<< (ostream& os, Instrucciones& ins){
    
    string arbol = ins.mostrarArbol(true);
    os << "MUESTRO EL ARBOL BINARIO: \n";
    os << arbol;

    //ArbolBinario<string>::nodo i_nodo(ins.datos.getRaiz());
    //ins.datos.RecorridoPostOrden(os);
    //os << ins.arbolEspacios(nod,0);
	
	return os;
}
