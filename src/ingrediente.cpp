#include<iostream>
#include <string>
#include "ingrediente.h"
#include <stdlib.h>
#include <string.h>

using namespace std;
//constructor por defecto
Ingrediente::Ingrediente(){
	nombre = "Undefined";
	calorias = 0.0;
	hidratos_de_carbono = 0.0;
	proteinas = 0.0;
	grasas = 0.0;
	fibra =0.0;
	tipo = "Sin tipo";
}
//constructor por parameteros
Ingrediente::Ingrediente(string nom, float cal, float hid_carb, float prot, float gras, float fib, string tip){
	nombre = nom;
	calorias = cal;
	hidratos_de_carbono = hid_carb;
	proteinas = prot;
	grasas = gras;
	fibra = fib;
	tipo = tip;
}
//constructor de copia
Ingrediente::Ingrediente(const Ingrediente& original){
	
	(*this)=original;
}

//metodo que impirme los datos del ingrediente
void Ingrediente::imprimir(){
	cout << *this;
}

//operador =
Ingrediente& Ingrediente::operator=(const Ingrediente& original){

	nombre = original.nombre;
	calorias = original.calorias;
	hidratos_de_carbono = original.hidratos_de_carbono;
	proteinas = original.proteinas;
	grasas = original.grasas;
	fibra = original.fibra;
	tipo = original.tipo;

	return *this;

}

//operador >>
istream& operator>> (istream& is, Ingrediente& ing){
	
	string aux="";
	char caracter = ';';
	
	getline(is,aux);
	if(aux.size()>0){
		aux = strtok((char *) aux.c_str(),";");
		ing.setNombre(aux);
		aux = strtok(NULL,";");
		ing.setCalorias(stof(aux));
		aux = strtok(NULL,";");
		ing.setHC(stof(aux));
		aux = strtok(NULL,";");
		ing.setProteinas(stof(aux));
		aux = strtok(NULL,";");
		ing.setGrasas(stof(aux));
		aux = strtok(NULL,";");
		ing.setFibra(stof(aux));
		aux = strtok(NULL,"\n");
		aux.pop_back();
		//aux.erase(std::remove(aux.begin(), aux.end(), ' '), aux.end());
		ing.setTipo(aux.c_str());
	}
	return is;
}

//operador <<
ostream& operator<< (ostream& os, Ingrediente& ing){
	//string aux="";
	string cals = to_string(ing.getCalorias());
	string hc = to_string(ing.getHc());
	string protes = to_string(ing.getProteinas());
	string grasas = to_string(ing.getGrasas());
	string fibra = to_string(ing.getFibra());
	string tipo = ing.getTipo();
	string nom = ing.getNombre();
	
	string salida = "\n"+nom+";"+cals+";"+hc+";"+protes+";"+grasas+";"+fibra+";"+tipo;

	
	
	os << salida;
	

	return os;
}
//operador ==
bool Ingrediente::operator==( const Ingrediente ing ) const{
	if(ing.nombre==nombre && ing.tipo==tipo)
		return true;
	else
		return false;
}
