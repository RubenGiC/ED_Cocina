#include <iostream>
#include <string>
#include <stdlib.h>
#include <string.h>
#include <sstream>
#include <iomanip>
#include <fstream>

#include "receta.h"
#include "ingrediente.h"
#include "ingredientes.h"
#include "acciones.h"
#include "instrucciones.h"

using namespace std;

//////////////////////////////////////////////////////////////////
/////////////////////////METODOS/////////////////////////////////
//////////////////////////////////////////////////////////////////

//tamanio de la listade ingredientes
int receta::ningredientes(){
	return ings.size();
}


void receta::addValoresIng(Ingrediente i,int gr){
	
	calorias += (i.getCalorias()*gr)/100;
	hc += (i.getHc()*gr)/100;
	grasas += (i.getGrasas()*gr)/100;
	proteinas += (i.getProteinas()*gr)/100;
	fibra += (i.getFibra()*gr)/100;
}

void receta::ImprimeReNutrientes(){
	  //cout << "Receta: " << nombre << endl;
	  
      cout << "Cals: "    << calorias << endl
           << "HC: "      << hc << endl
           << "Grasas: "  << grasas << endl 
           << "Protes: "  << proteinas << endl
           << "Fibra: "   << fibra << endl;
      cout << endl;
}

void receta::ImprimeReIngredientes(){
	//list<pair<string,unsigned int>>::iterador pos;
	
	for(list<pair<string,unsigned int>>::iterator pos=ings.begin();pos!= ings.end();pos++){
		cout << (*pos).first << " " << (*pos).second << endl;
	}
}

void receta::addInstrucciones(string archivo){
	ifstream f2(archivo);
    if (!f2){
    	cout<<"No puedo abrir "<<archivo<<endl;
    }else{
    
	    f2>>inst;
	    f2.close();
	}
}


float receta::CalcRatio(){
	float output = 0.0;
	
	float protes_hc = proteinas / hc;
	float hc_protes = hc / proteinas;
	
	if(protes_hc > hc_protes)
		output = protes_hc;
	else
		output = hc_protes;
	
	return output;
}


//////////////////////////////////////////////////////////////////
///////////////////GETS y SET ATRIBUTOS///////////////////////////
//////////////////////////////////////////////////////////////////

string receta::getNombre(){
	return nombre;
}

string receta::getCode(){
	return code;
}
	
unsigned int receta::getPlato(){
	return plato;
}

//SETS
/*
string& receta::setCode(){
	return code;
}

unsigned int& receta::setPlato(){
	return plato;
}
*/
void receta::setNombre(string nom){
	nombre = nom;
}
/*
list<pair <string, unsigned int>>& receta::setIngs(){
	return ings;
}
*/
	

//////////////////////////////////////////////////////////////////
///////////////////GETS y SET de ingredientes///////////////
//////////////////////////////////////////////////////////////////	
list< pair <string,unsigned int> > receta::getIngredientes(){
	return ings;
}

	
//////////////////////////////////////////////////////////////////
///////////////////GETS y SET valores nutricionales///////////////
//////////////////////////////////////////////////////////////////
	
//GETS y SET valores nutricionales
// SE USAN EN NUTRICION RECETA PARA HALLAR LOS VALORES CORRESPONDIENTES
// A LAS RECETAS QUE HACEMOS

//------------------GETS
float receta::getCals(){return calorias;}

float receta::getHC(){return hc;}

float receta::getGrasas(){return grasas;}

float receta::getProtes(){return proteinas;}

float receta::getFibra(){return fibra;}

/////////////////////////
/////CONSTS/////////////
///////////////////////

float receta::getCals() const{return calorias;}

float receta::getHC() const{return hc;}

float receta::getGrasas() const{return grasas;}

float receta::getProtes() const{return proteinas;}

float receta::getFibra() const{return fibra;}

//-------------------SETS

void receta::setCals(float cals){calorias = cals;}

void receta::setHC(float hcs){hc = hcs;}

void receta::setProtes(float protes){proteinas = proteinas;}

void receta::setGrasas(float gras){grasas = gras;}

void receta::setFibra(float fib){fibra = fib;}


bool receta::fusion(receta r1, receta r2,Ingredientes ingredientes){
	//receta rf;
	bool error_fusion = false;

	//si son el mismo plato pero distintas recetas entra
	if(r1.getPlato()==r2.getPlato() && r1.getCode()!=r2.getCode()){

		//FUSIONO LOS INGREDIENTES

		list< pair <string,unsigned int> >::iterator it;//iterador de r1 y r2
		list< pair <string,unsigned int> >::iterator it2;//iterador de this

		//guardo las listas de r2 y r1
		list< pair <string,unsigned int> > lr2=r2.getIngredientes();
		list< pair <string,unsigned int> > lr1=r1.getIngredientes();

		bool existe = false;//si existe o no el ingrediente

		for(it=lr1.begin();it!=lr1.end() && !error_fusion;it++){//recorro el ingrediente

			//busco si existe el ingrediente
			Ingrediente ing = ingredientes.buscarIngrediente((*it).first);

			//si existe lo guardo
			if(ing.getNombre()!="Undefined"){
				pair<string,unsigned int> ing; //creo un par
				ing.first=(*it).first;//guardo el nombre de la receta
				ing.second=(*it).second;//guardo los gr de la receta
				ings.push_back(ing);//lo añado a la lista
			
			//en caso contrario
			}else{
				cout << endl << "ERROR EL INGREDIENTE " << (*it).first << " NO EXISTE" << endl;
				error_fusion=true;
			}
		}

		//recorro la segunda lista de la segunda receta
		for(it=lr2.begin();it!=lr2.end() && !error_fusion;it++){

			//lo mismo busco si existe ese ingrediente
			Ingrediente ing = ingredientes.buscarIngrediente((*it).first);
			if(ing.getNombre()!="Undefined"){

				//si existe lo comparo con la lista que tengo
				for(it2=this->ings.begin();it2!=this->ings.end() && !existe;it2++){

					//si ya estaba metido de antes
					if((*it).first==(*it2).first){
						existe = true;
						(*it2).second+=(*it).second; //le sumo los gramos
					}
				}

				//si no existe el ingrediente en la lista a fusionar
				if(!existe){
					//creo el pair
					pair<string, unsigned int> ing;
					ing.first=(*it).first;
					ing.second=(*it).second;

					//y añado el nuevo ingrediente en la lista
					ings.push_back(ing);
				
				//en caso contrario resetei existe
				}else
					existe = false;
			}else{
				cout << endl << "ERROR EL INGREDIENTE " << (*it).first << " NO EXISTE" << endl;
				error_fusion=true;
			}		
			
		}

		//ings.merge(lr2);

		//FUSIONO LOS VALORES NUTRICIONALES
		if(!error_fusion){//si no ha dado error con los ingredientes o el plato
			if(r1.getInstrucciones().existeIngredientes(ingredientes) && 
				r2.getInstrucciones().existeIngredientes(ingredientes)){

				//sumo sus cantidades calorias, hc, grasas, proteinas y fibra
				calorias = r1.getCals() + r2.getCals();
				hc = r1.getHC() + r2.getHC();
				grasas = r1.getGrasas()+r2.getGrasas();
				proteinas = r1.getProtes()+r2.getProtes();
				fibra = r1.getFibra()+r2.getFibra();

				//PONGO EL NOMBRE DE LA RECETA, EL CODIGO Y EL NUMERO DE PLATO
				code = "F_" + r1.getCode() + "_" + r2.getCode();
				nombre = "Fusion " + r1.getNombre() + " y " + r2.getNombre();
				plato=r1.getPlato();

				//y por ultimo combino las instrucciones
				inst.combinarInstrucciones(r1.getInstrucciones(),r2.getInstrucciones());
			}else{
				cout << endl << "ERROR UN INGREDIENTE DE INSTRUCCIONES NO EXISTE" << endl;
				error_fusion=true;
			}
		}
	}else{
		cout << endl << "ERROR EL LAS RECETAS TIENEN QUE SER DEL MISMO PLATO Y DISTINTAS RECETAS" << endl;
		error_fusion=true;
	}
	//this->combinaIngredientes(r2);
	return !error_fusion;
}

void combinaIngredientes(receta r2){
	
}


///////////////////////////////////////////////////////////////////
//------------------------OPERATORS------------------------//
///////////////////////////////////////////////////////////////////

//operador >>
istream& operator>> (istream& is, receta& re){
	string line;
	
	//ESTAMOS EN RECETA, SINGULAR, ASI QUE NO ES NECESARIO MAS QUE LEER UNA LINEA ;)
	//while(getline(is, line)){
		getline(is, line);
		//le escribimos un ; al final para que se lean todos
		//line += ";";
		//no es necesario, solo hay que quitar el ultimo elemento
		//que es basura y punto
		stringstream linestream(line);
		
		getline(linestream, re.code, ';');
		
		string plato;
		getline(linestream, plato, ';');
		re.plato = atoll(plato.c_str());
		
		getline(linestream, re.nombre, ';');
		
		pair<string, unsigned int> ing;
		string tmp;
		
		
		//leemos todos los ingredientes:
		//no da fallo porq ya le aniadimos el ; al inicio
		
		//leemos ingrediente completo
		while(getline(linestream, tmp, ';')){
		
			//convertimos a tmp en stream y sacamos los string y el numero
			stringstream ss(tmp);
			ss >> ing.first;
			
			string lectura;
			while(ss){
				ss >> lectura;
				if(isdigit(lectura[0])){
					ing.second = atoll(lectura.c_str());
				}
				else
					ing.first += " " + lectura;
			}
			
			re.ings.push_back(ing);
		}
		//quitamos el ultimo ingrediente porq es un ; 
	return is;
}

//operador <<
ostream& operator<< (ostream& os, receta& re){
	string salida = "";
	string code = re.code;
	salida += re.code+";"+to_string(re.plato)+";"+re.nombre+";";
	
	for(list<pair<string, unsigned int>>::iterator i = re.ings.begin(); i!=re.ings.end(); ++i){
		pair<string, unsigned int> tmp;
		tmp = *i;

		salida += tmp.first+" "+to_string(tmp.second)+";";
		//salida += (*i).first; CON *I TMB VALE pero se ve mas claro con tmp
    }
	//tras imprimir el ultimo, quitamos el ultimo char
	//asi pierde el ";" como en la entrada original
	salida.pop_back();
	
	//le pasamos el string y le ponemos un endl;
	os << salida << endl;
	
	return os;
}
