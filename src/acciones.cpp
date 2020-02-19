#include <iostream>
#include <string>
#include <stdlib.h>
#include <string.h>
#include <sstream>
#include <iomanip>
#include <map>

#include "acciones.h"

using namespace std;

unsigned char Acciones::buscar(string orden){
	auto it = datos.find(orden);
	return it->second;
}

istream& operator>> (istream& is, Acciones& acc){
	string line;
	
	//recorre el archivo
	while(getline(is, line)){
		//lo pasamos a stream
		stringstream linestream(line);

		string dato;//guarda la orden
		string aux;
		char n;//guarda la ariedad

		getline(linestream, dato, ' ');//recibe la orden
		getline(linestream, aux, ' ');//recibe la ariedad
		n=aux[0];
		//strcpy(n,aux.c_str());
		acc.datos.insert({ dato, n });//lo añado al map
		
	}
	return is;
}

ostream& operator<< (ostream& os, Acciones& acc){
	map<string, unsigned char>::iterator pos;
    for(pos = acc.datos.begin(); pos != acc.datos.end(); ++pos){
    	os   << "Orden: " << (*pos).first << "\t" 
    	     << "Ariedad: " << (*pos).second
    	     << endl;
    }
    os << endl;
	
	return os;
}