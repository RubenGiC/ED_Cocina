#include <iostream>
#include <string>
#include <stdlib.h>
#include <string.h>
#include <sstream>
#include <iomanip>

#include "receta.h"
#include "recetas.h"
#include "ingredientes.h"
#include "acciones.h"
#include "instrucciones.h"

using namespace std;

//////////////////////////////////////////////////////////////////
/////////////////////////METODOS/////////////////////////////////
//////////////////////////////////////////////////////////////////

int recetas::size(){
	return datos.size();//metodo size del map
}

void recetas::borrar(string codigo){
	datos.erase(codigo);//metodo erase del map
}

receta recetas::buscar(string codigo){
	receta r;
	bool find = false;
	map<string, receta>::iterator pos;
    for(pos = datos.begin(); pos != datos.end() && !find; ++pos){
    	if(pos->first == codigo){
    		r =pos->second;
    		find = true;
    	}
    }

    return r;
	//return datos.find(codigo)->second;
}

void recetas::ImpremeReInfo(string codigo){
	receta r;
	bool find = false;
	map<string, receta>::iterator pos;

	//obtengo la receta
    for(pos = datos.begin(); pos != datos.end() && !find; ++pos){
    	if(pos->first == codigo){
    		r =pos->second;
    		find = true;
    	}
    }
    //si la encuentra
    if(find){
    	//muestro la información
    	cout << endl << "CODIGO: " << r.getCode() << "\t" 
        << "NOMBRE: " << r.getNombre() << "\t"
        << "PLATO: " << r.getPlato() << endl << endl;

        cout << "Ingredientes:" << endl << endl;
	    r.ImprimeReIngredientes();

	    cout << endl << endl << "Información Nutricional:" << endl << endl;
	    r.ImprimeReNutrientes();

	    cout << endl << endl << "Pasos a seguir:" << endl << endl;
	    cout << r.getInstrucciones().mostrarArbol(false);
    }else{
    	cout << "ERROR NO EXISTE LA RECETA CON EL CODIGO: " << codigo << endl;
    }
}

void recetas::addInstrucciones(string ruta){

	map<string, receta>::iterator pos;

	
    for(pos = datos.begin(); pos != datos.end(); ++pos){
		string ins =ruta + (*pos).first + "m.txt";
      	(*pos).second.addInstrucciones(ins);
    }
}

void recetas::addNuevaReceta(receta rec){
	datos[rec.getCode()] = rec;
}

///////////////////////////////////////////////////////////////////
//------------------------OPERATORS------------------------//
///////////////////////////////////////////////////////////////////


//operator []
receta & recetas::operator [](string codigo){
	return datos[codigo];
}

//operador >>
istream& operator>> (istream& is, recetas& rall){
	string line;
	
	while(getline(is, line)){
		//por cada linea tenemos una receta:
		receta re;
		//lo pasamos a stream
		stringstream linestream(line);
		
		//leemos desde el stream
		linestream >> re;//operator >> de receta
		//RECETAS
		string codigo = re.getCode();
		rall.datos[codigo] = re; //nombre receta , receta
		//si no existe la aniade :), el map lo hace auto	

		//si en recetas contiene ingredientes
	  	if(rall.all_ingredientes.size()>0){
	  		//cout << "---------------------------------------------> " << rall.all_ingredientes.size() << endl;
		 	list< pair <string,unsigned int> > ings = rall.datos[codigo].getIngredientes();
		  	list< pair <string,unsigned int> >::iterator it;
		  	for(it = ings.begin(); it != ings.end(); ++it++){//recorre los ingredientes
		  		string nom = (*it).first;
		  		unsigned int gr = (*it).second;
		  		//cout << nom << " -- " << gr << endl;
				Ingrediente ing = rall.all_ingredientes.buscarIngrediente(nom);//busca si existe ese ingrediente
			
				if(ing.getNombre() != "Undefined")//si esta añade los valores
			  		rall.datos[codigo].addValoresIng(ing, gr);//le paso el ingrediente Y los gramos
			}
		}
	}
		
	return is;
}

//operador <<
ostream& operator<< (ostream& os, recetas& rall){
	map<string, receta>::iterator pos;
    for(pos = rall.datos.begin(); pos != rall.datos.end(); ++pos){
    	os   << "CODIGO: " << (*pos).first << "\t" 
    		<< "NOMBRE: " << pos->second.getNombre() << "\t\t"
    		<< "PLATO: " << pos->second.getPlato() << endl;
    	     /*<< "RECETA: \n" << pos->second 
    	     << endl; //accedemos con -> o con (*pos).
    	//ese cout << pos->second es basicamente 
    	//el operator << de RECETA*/
    }
    os << endl;
	
	return os;
}
