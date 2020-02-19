#include <iostream>
#include <string.h>
#include <stdio.h>
#include <cstddef>
#include "ingredientes.h"
#include "ingrediente.h"
#include <vector>
#include <cmath> //para pow
#include <algorithm>    // std::sort

using namespace std;
//hay que ordenar los ingredientes por tipo y por nombre
//recomendable busqueda binaria
//pos_d
//pos_i

//VARIABLE GLOBAL PARA HACER SALIDAS
string nom_info[5] = {"Calorias", "Hidratos de Carb", "Proteinas", "Grasas", "Fibra"};

//constructor por defecto
Ingredientes::Ingredientes(){
	//ambos atributos a cero
	datos = vector<Ingrediente>(0);
	indice = vector<int> (0);
}

//constructor que recibe el tamanio del vector
Ingredientes::Ingredientes(int tam){

	datos = vector<Ingrediente>(tam);
	indice = vector<int>(tam);

}

//constructor de copia
Ingredientes::Ingredientes(const Ingredientes& original){
	datos = original.datos; //este this->datos llama al datos de VD
							//pero deveria llamar a los datos de ingredientes
	indice = original.indice;
}

Ingrediente Ingredientes::getIngrediente(int n) const{

	Ingrediente ing=Ingrediente();

	if(n>=0 && n<datos.size()){
		ing = datos[n];
	}

	return ing;
}

vector<string> Ingredientes::getTipos(){

	vector<string> tipos;

	if(indice.size()){ //si hay elementos recoge el primero
		Ingrediente ingr_primero = datos[indice[0]];
		string tipo_ingr_primero = ingr_primero.getTipo();
		//lo aniadimos
		tipos.insert(tipos.end(),tipo_ingr_primero);
	}
	//ahora, recorremos todos los tipos y cuando cambien de tipo
	//lo aniadimos
	int i = 0;//indice que recorrera VD<string> tipos
	int j = 1; //indice q recore indice.usados()
			   //empieza en 1 porq ya hemos insertado el primero
	while(j < indice.size()){ 
		Ingrediente ingr = datos[indice[j]];
		string tipo_ingr = ingr.getTipo();

		if(tipos[i].compare(tipo_ingr) != 0){//si son diferentes, lo aniade
			tipos.insert(tipos.end(),tipo_ingr);
			i++; //actualizamos i, para que compare con ese.
			     //recordemos q de esta forma de recorrer, todos los de un mismo tipo
				 //estan seguidos, por lo q solo hay tipo nuevo si cambia 
		}
		j++; //acutalizamos para que siga el bucle

	}

	return tipos;
}

Ingredientes Ingredientes::getIngredientesTipo(string tipo_ingr){

	Ingredientes salida;
	for(int i=0; i<indice.size(); i++){

		Ingrediente ingr = datos[indice[i]]; //usamos el operator = de ingrediente
		string str1 = ingr.getTipo(), str2 = tipo_ingr;
		
		//para quitarle el retorno de carro
		//str1.pop_back();//OJO SINO CONSIDERA Q SON IGUALES!!

		if(str1.compare(str2) == 0){
			salida.add(ingr);
		}

	}

	return salida;
}

Ingrediente Ingredientes::get(string n) const{
	return (buscarIngrediente(n));
}

Ingrediente Ingredientes::buscarIngrediente(string n) const{
	int elementos = datos.size();
	Ingrediente ing;
	bool find=false;
	for (int i=0;i<elementos && !find;i++){
		if(datos[i].getNombre()==n){
			ing = datos[i];
			find = true;
		}
	}
	return ing;
}

void Ingredientes::EstadisticosTipo() const{
	cout << endl << endl << "Estadistica__________________________________________" << endl;
	//devuelve el tipo del primer alimento, ya que todos son del mismo tipo
	cout << "Tipo de Alimento  " << getIngrediente(0).getTipo() << endl;

	cout << "Promedio +- Desviacion" << endl;

	cout << endl << "Calorias\t\tHidratos de Carb\tProteinas\t\tGrasas\t\t\tFibra" << endl; //\t\tTipo\t\t\tNombre";

	//VARIABLE PARA TODOS
	float salida;
//////////////////////////////////////////////////////
	//Media y desviacion de cada info
	
	for(int i=0; i<5; i++){
		salida = CalculaMedia(nom_info[i]);
		cout << to_string(salida) << "+-" << to_string(CalculaDesviacion(nom_info[i])) << "\t";
	}
	cout << endl << endl;

//////////////////////////////////////////////////////
	//MAX VALORES
	cout << "Maximo Valores" << endl;
	cout << endl << "Calorias (Alimento)\tHidratos de Carb (Alimento)\tProteinas (Alimento)\t\tGrasas (Alimento)\t\tFibra (Alimento)" << endl; //\t\tTipo\t\t\tNombre";

	//Valor Maximo y nombre del alimento
	for(int i=0; i<5; i++){
		salida = CalculaMaxVal(nom_info[i]);
		cout << salida << "\t" << CalculaMaxNombre(nom_info[i]) << "\t  ";
	}
	cout << endl << endl;

//////////////////////////////////////////////////////
	//MIN VALORES
	cout << "Minimo Valores" << endl;
	cout << endl << "Calorias (Alimento)\t\tHidratos de Carb (Alimento)\tProteinas (Alimento)\t\tGrasas (Alimento)\t\tFibra (Alimento)" << endl; //\t\tTipo\t\t\tNombre";

	//Valor Maximo y nombre del alimento
	//OJO AHORA SALDRA CON LOS \T SIN CORRESPONDER
	for(int i=0; i<5; i++){
		salida = CalculaMinVal(nom_info[i]);
		cout << salida << "\t" << CalculaMinNombre(nom_info[i]) << "\t  ";
	}
	cout << endl;

}



void Ingredientes::imprimeIngrediente(string nombre) const{
	//buscarIngrediente(nombre).imprimir();
	Ingrediente ing = buscarIngrediente(nombre);
	cout << ing;
}

//borra segun el nombre
//llamando a eliminar pasando la posicion en la que esta ese nombre
void Ingredientes::borrar(string nom){
	elimina(buscarIngrediente(nom) ); //elimina recibe un ingrediente y lo elimina.
}

void Ingredientes::actualizar_por_add(int pos_inicial){
	for(int i = 0; i<indice.size(); i++)
		if(indice[i] >= pos_inicial) indice[i]++;
}

void Ingredientes::add(Ingrediente ingrediente){
	//buscamos y aniadimos el ingrediente en la posicion correcta del VD datos.
	int pos_nombre = BuscaPosNombre(ingrediente);

	datos.insert(datos.begin()+pos_nombre,ingrediente);	

	//hallamos la posicion necesaria y en ella insertamos LA POSICION SEGUN EL NOMBRE
	//en el VD indice

	//ACTUALIZAR (+ 1 )VALORES DEL INDICE A PARTIR DE LA INSERCION pos_nombre;
	actualizar_por_add(pos_nombre);
	
	int pos_tipo = BuscaPosTipo(ingrediente);
	
	indice.insert(indice.begin() + pos_tipo, pos_nombre);

}

//METODO PRIVADO
int Ingredientes::BuscaPosNombre(Ingrediente ingr) const{

	int pos_insercion = 0;

	bool antes_del_fin = false;
	int i = 0;
	//si no hay ningun elemento aun, no entra y devuelve cero
	for(i; i<datos.size() && !antes_del_fin; i++){
		if( (ingr.getNombre()).compare(datos[i].getNombre()) < 0 ){
			pos_insercion = i;
			antes_del_fin = true;
		}
	}
	//si ha llegado al final sin ser < se recoge la ultima pos libre
	if(!antes_del_fin) //i == datos.usados()) //tmb vale if(!antes_del_fin)
		pos_insercion = i;
	
	
	return(pos_insercion);
}

//METODO PRIVADO
int Ingredientes::BuscaPosTipo(Ingrediente ingr) const{
	//asignamos los valores a comparar
	string tipo_nuevo = ingr.getTipo(); //datos.get(pos_cambiada).getTipo();
	string nombre_nuevo = ingr.getNombre(); //datos.get(pos_cambiada).getNombre();

/////////////////////////////////////
	int pos_insercion = 0;

	bool antes_del_fin = false;
	int i = 0;
	//si no hay ningun elemento aun, no entra y devuelve cero
	for(i; i<indice.size() && !antes_del_fin; i++){
		string tipo_a_comparar = datos[indice[i]].getTipo();
		string nombre_a_comparar = datos[indice[i]].getNombre();

		if( tipo_nuevo.compare(tipo_a_comparar) < 0 ){
			pos_insercion = i;
			antes_del_fin = true;
		}
		if( tipo_nuevo.compare(tipo_a_comparar) == 0 ){ //mismo tipo
			if( nombre_nuevo.compare(nombre_a_comparar) < 0){ //comparamos segun nombre
				pos_insercion = i;
				antes_del_fin = true;
			}
		}
	}

	//si ha llegado al final sin ser < se recoge la ultima pos libre
	if(!antes_del_fin) //i == datos.usados()) //tmb vale if(!antes_del_fin)
		pos_insercion = i;
	
	
	return(pos_insercion);
}


void Ingredientes::elimina(Ingrediente ingr){
	bool encontrado = false;
	int pos = 0;
	for(int i=0; i<datos.size(); i++){
		if(datos[i] == ingr){
			encontrado = true;
			pos = i;
		}
	}
	datos.erase(datos.begin() + pos - 1); //eliminamos esa posicion

	//buscamos donde se encuentra el valor (pos) dentro de VD indices
	//y eliminamos esa posicion.
	indice.erase(indice.begin() + devuelveIndice(pos) -1);

	//ahora -- a los que sean > que la pos eliminada
	//indice.erase(indice.begin()+pos-1); //actualizamos los valores
}

int Ingredientes::devuelveIndice(int elemento_a_buscar){
	int salida = 0;
	bool find = false;
	for(int i = 0; i<indice.size() && !find; i++)
		if(indice[i] == elemento_a_buscar){ 
			salida = i;
			find=true;
		}
	
	return salida;
}

//metodo privado
float Ingredientes::CalculaMedia(string info) const{
	float salida = 0.0, cals =0.0, hc = 0.0, protes = 0.0,
		  grasas = 0.0, fibra = 0.0;

	//calculamos todos los valores
	for(int i=0; i<datos.size(); i++){
		cals += datos[i].getCalorias();
		hc += datos[i].getHc();
		protes += datos[i].getProteinas();
		grasas += datos[i].getGrasas();
		fibra += datos[i].getFibra();
	}
	
	//recogemos los datos en un array	
	float datos_info[5] = {cals, hc, protes, grasas, fibra};

	//comprobamos el tipo que nos han pedido
	for(int i=0; i<5; i++){
		if(info.compare(nom_info[i]) == 0){
			salida = datos_info[i];
		}
	}

	return (salida / datos.size()); //suma todos 
								      //y divide por el 
									  //numero de iteraciones

}


//metodo privado
float Ingredientes::CalculaDesviacion(string info) const{
	float salida = 0.0, cals =0.0, hc = 0.0, protes = 0.0,
		  grasas = 0.0, fibra = 0.0;

	//calculamos cada una de las desviaciones (valor - media)
	for(int i=0; i<datos.size(); i++){
		cals += pow( ( datos[i].getCalorias() ) - CalculaMedia("Calorias"), 2);
		hc += pow ( ( datos[i].getHc() ) - CalculaMedia("Hidratos de Carb"), 2);
		protes += pow (  (datos[i].getProteinas()) - CalculaMedia("Proteinas"), 2);
		grasas += pow ( ( datos[i].getGrasas() ) - CalculaMedia("Grasas"), 2);
		fibra += pow (  (datos[i].getFibra()) - CalculaMedia("Fibra"), 2);
	}

	//recogemos los datos en un array	
	float datos_info[5] = {cals, hc, protes, grasas, fibra};

	//comprobamos el tipo que nos han pedido
	for(int i=0; i<5; i++){
		if(info.compare(nom_info[i]) == 0){
			salida = datos_info[i];
		}
	}

	return sqrt(salida / datos.size()); //suma todos 
								      //y divide por el 
									  //numero de iteraciones
									  //y raiz de eso

	
}


//privado
float Ingredientes::CalculaMaxVal(string info) const{
	float salida = 0.0, cals =0.0, hc = 0.0, protes = 0.0,
		  grasas = 0.0, fibra = 0.0;

	//calculamos cada una de las desviaciones (valor - media)
	for(int i=0; i<datos.size(); i++){
		//actualizamos segun leamos los valores
		if(datos[i].getCalorias() > cals) cals = datos[i].getCalorias();
		if(datos[i].getHc() > hc) hc = datos[i].getHc();
		if(datos[i].getProteinas() > protes) protes = datos[i].getProteinas();
		if(datos[i].getGrasas() > grasas) grasas = datos[i].getGrasas();
		if(datos[i].getFibra() > fibra) fibra = datos[i].getFibra();
	}

	//recogemos los datos en un array	
	float datos_info[5] = {cals, hc, protes, grasas, fibra};

	//comprobamos el tipo que nos han pedido
	for(int i=0; i<5; i++){
		if(info.compare(nom_info[i]) == 0){
			salida = datos_info[i];
		}
	}
	
	return salida;
}

//metodo privado
float Ingredientes::CalculaMinVal(string info) const{
	//Inicializamos a los valores maximos
	float salida = 0.0, cals =CalculaMaxVal("Calorias"), hc =CalculaMaxVal("Hidratos de Carb"), 
	protes =CalculaMaxVal("Proteinas"), grasas =CalculaMaxVal("Grasas"), fibra =CalculaMaxVal("Fibra");

	//calculamos cada una de las desviaciones (valor - media)
	for(int i=0; i<datos.size(); i++){
		//actualizamos segun leamos los valores
		if(datos[i].getCalorias() < cals) cals = datos[i].getCalorias();
		if(datos[i].getHc() < hc) hc = datos[i].getHc();
		if(datos[i].getProteinas() < protes) protes = datos[i].getProteinas();
		if(datos[i].getGrasas() < grasas) grasas = datos[i].getGrasas();
		if(datos[i].getFibra() < fibra) fibra = datos[i].getFibra();
	}

	//recogemos los datos en un array	
	float datos_info[5] = {cals, hc, protes, grasas, fibra};

	//comprobamos el tipo que nos han pedido
	for(int i=0; i<5; i++){
		if(info.compare(nom_info[i]) == 0){
			salida = datos_info[i];
		}
	}
	
	return salida;
}

//privado
string Ingredientes::CalculaMaxNombre(string info) const{
	float 	cals = CalculaMaxVal("Calorias"), hc = CalculaMaxVal("Hidratos de Carb"), 
			protes = CalculaMaxVal("Proteinas"), grasas = CalculaMaxVal("Grasas"), 
			fibra = CalculaMaxVal("Fibra");
	
	int index_cals, index_hc, index_protes, index_grasas, index_fibra;

	string salida;
		
	//aqui tmb calculamos desde el final al principio, para que
	//asi el nombre quede ordenado por orden alfabetico ;)
	for(int i= datos.size() - 1; i>= 0; i--){
		//si el valor coincide con el valor que se le ha pasado
		//actuailzamos el valor el nombre de esa info por el de esa posicon.
		if(datos[i].getCalorias() == cals) index_cals = i;
		if(datos[i].getHc() == hc) index_hc = i;
		if(datos[i].getProteinas() == protes) index_protes = i;
		if(datos[i].getGrasas() == grasas) index_grasas = i;
		if(datos[i].getFibra() == fibra) index_fibra = i;
	}

	//recogemos los datos en un array	
	int datos_info[5] = {index_cals, index_hc, index_protes, index_grasas, index_fibra};

	//comprobamos el tipo que nos han pedido
	for(int i=0; i<5; i++){
		if(info.compare(nom_info[i]) == 0){
			salida = datos[datos_info[i]].getNombre();
		}
	}
	
	return salida;
}


//privado
string Ingredientes::CalculaMinNombre(string info) const{
	float 	cals = CalculaMinVal("Calorias"), hc = CalculaMinVal("Hidratos de Carb"), 
			protes = CalculaMinVal("Proteinas"), grasas = CalculaMinVal("Grasas"), 
			fibra = CalculaMinVal("Fibra");
	
	int index_cals, index_hc, index_protes, index_grasas, index_fibra;

	string salida;

	//empezamos desde el final al principio para que asi queden ordenados
	for(int i=datos.size() - 1; i>=0; i--){
		//si el valor coincide con el valor que se le ha pasado
		//actuailzamos el valor el nombre de esa info por el de esa posicon.
		if(datos[i].getCalorias() == cals) index_cals = i;
		if(datos[i].getHc() == hc) index_hc = i;
		if(datos[i].getProteinas() == protes) index_protes = i;
		if(datos[i].getGrasas() == grasas) index_grasas = i;
		if(datos[i].getFibra() == fibra) index_fibra = i;
	}
	//recogemos los datos en un array	
	int datos_info[5] = {index_cals, index_hc, index_protes, index_grasas, index_fibra};

	//comprobamos el tipo que nos han pedido
	for(int i=0; i<5; i++){
		if(info.compare(nom_info[i]) == 0){
			salida = datos[datos_info[i]].getNombre();
		}
	}
	
	return salida;
}


void Ingredientes::eliminar(int pos){
	datos.erase(datos.begin()+pos-1);
}

void Ingredientes::imprimir(){
	for(int i=0;i<datos.size();i++){
		datos[i].imprimir();
	}
}


void Ingredientes::ImprimirPorTipo(ostream& os){
	os<<indice.size();
	for(int i=0; i<indice.size(); i++){
		os << "\nhola\n";
		Ingrediente ingr = datos[indice[i]]; //usamos el operator = de ingrediente
		os << ingr; 
	}
}


//operador >>
istream& operator>> (istream& is, Ingredientes& ings){

	string aux="";
	getline(is,aux);
	Ingrediente ing;
	//cout << "/" << ings.datos.usados() << "/" << ings.datos.size() << endl;

	while(!is.eof()) {
		
			is >> ing;
			//ing.imprimir();
			
			ings.add(ing); //ahora, aniade tanto en "datos" como en "indice"
	}
	//te muestra los usados y la reserva
	//cout << "/" << ings.datos.usados() << "/" << ings.datos.size() << endl;
	return is;
}

//operador <<
ostream& operator<< (ostream& os, Ingredientes& ings){
	
	for(int i=0;i<ings.datos.size();i++){
		//cout << "entra en el for de << ingredientes" << endl;
		//ing = ings.datos.get(i);
		//os << ing;
		Ingrediente ing = ings.datos[i];
		os << ing;
		
	}
	
	return os;
}

/*
Ingrediente & Ingredientes :: operator [] (int i)
{
	return datos[i];
}
*/
//T & VD<T>:: operator [](int i) {
//	return datos[i];
