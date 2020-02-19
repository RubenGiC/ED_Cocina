#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <string.h>
#include <sstream>
#include <iomanip>

#include "ingrediente.h"
#include "ingredientes.h"

#include "receta.h"
#include "recetas.h"
#include "acciones.h"
#include "instrucciones.h"

#include <vector>
#include <algorithm> //para el sort
//#include <pair>


using namespace std;

Acciones Instrucciones::acc;

/**
  *  @brief Programa Nutricionreceta
  *
  * Clase Nutricionreceta que calcula los valores nutricionales de cada receta
  *
  * @author Ruben Girela
  * @author Jorge Medina
  * @date Octubre 2019
  */

//ordenamos en funcion del float (primer valor del pair
//y de mayor a menor, por ello el > :)
bool sort_pred(const pair<float, receta>& left, 
				  const pair<float, receta>& right){
	return left.first > right.first;
}


int main(int argc, char *argv[]){

  if(argc != 4){
  	perror("Error de argumentos esperados: <program> <recetas.txt> <ingredientes.txt> <calorias>(float)");
  	exit(-1);
  }
  

	string nf =argv[2];//recibo el fichero de ingredientes.txt
	float calorias = atof(argv[3]);//recibo el maximo de calorias
	ifstream f(nf);
	if (!f){
	  cout<<"No puedo abrir "<<nf<<endl;
	  return 0; 
	}
	//Quitamos la primera linea
	string linea;
	getline(f,linea);

	f.seekg(0);
	Ingredientes all_ingre;

	/////////////////////////////////////////////////////////////////////////////////////////
	cout<<"Lectura de todos los ingredientes"<<endl;
	f>>all_ingre;

	nf =argv[1];//recibo el fichero de recetas.txt
	ifstream f2(nf);
	if (!f2){
	  cout<<"No puedo abrir "<<nf<<endl;
	  return 0; 
	}
	//NO SE QUITA
	//Quitamos la primera linea
	//getline(f2,linea);

	f2.seekg(0);
	recetas all_recet;
	cout<<"Lectura de todos las recetas"<<endl;
	f2 >> all_recet;

	/////////////////////////////////////////////////////////////////////////////////////////

	//AÑADO LAS CALORIAS, HIDRATOS, FIBRA ... DE CADA RECETA
	recetas::iterador it;//recorre las recetas

	//list< pair <string,unsigned int> >::iterator it2;//recorre los ingredientes de receta
	receta::iterador it2;

	//receta re;//guardo el iterador NO SE USA!

	Ingrediente ing;//guardo el ingrediente

	list< pair <string,unsigned int> > ings;

	for (it = all_recet.begin(); it != all_recet.end(); ++it){//recorre las recetas
	  //re = *it; NO SE PUEDE!!!!
	  ings = (*it).getIngredientes();
	  
	  for(it2 = (*it).begin(); it2 != (*it).end(); ++it2){//recorre los ingredientes
	  	string nom = (*it2).first;
	  	unsigned int gr = (*it2).second;
	  	
		ing = all_ingre.buscarIngrediente(nom);//busca si existe ese ingrediente
		
		if(ing.getNombre() != "Undefined")//si esta añade los valores
		  (*it).addValoresIng(ing, gr);//le paso el ingrediente Y los gramos
	  }
	}

	cout<<"Pulse una tecla para continuar..."<<endl<<endl;
	cin.get();

	/////////////////////////////////////////////////////////////////////////////////////////

	cout<<"Imprimimos las recetas con los nutrientes calculados "<<endl;

	//int max_cal=0;//obtiene las calorias mas altas
	vector< pair<float, receta> > sub_re;//guarda las subrecetas con su ratio... el ratio lo calculamos con receta.CalcRatio();
	
	//re temporal para imprimir valores
	receta re;
	//float cal=0,hc=0,grasas=0,prot=0,fibra=0;
	for (it=all_recet.begin(); it!=all_recet.end(); ++it){
	  re = *it;
	  
	  //cout << "CALORIAS FUERA BUCLE QUE ADDS : " << re.getCals() << endl;
	  //si las calorias de la receta es mayor que max_cal y no supere el tope de calorias
	  //permitidas lo guarda
	  
	  cout << "Valores nutricionales de la receta: " << re.getNombre() << " son: " << endl;
	  cout << re << endl;
	  re.ImprimeReNutrientes();//muestra Nutrientes
	  
	  ////FILTRAMOS POR LAS CALORIAS MINIMAS
	  if(re.getCals() <= calorias){
	    pair<float, receta> par_leido (re.CalcRatio(), re);
	    
	    //insertamos el pair de forma ordenada!!
	    //de acuerdo al valor de first
	    //es decir, el ratio
	    vector< pair<float, receta> >::iterator itera;
	   // itera = lower_bound(sub_re.begin(), sub_re.end(), re.CalcRatio());
	    
	    sub_re.push_back(par_leido);//ya que es un vector
	    									 //de ratio, receta
	  }//if
	}//for
	///TRAS EL FOR HACEMOS SORT DEL LIST PAIR
	sort(sub_re.begin(), sub_re.end(), sort_pred);
	
	cout<<"Pulse una tecla para continuar..."<<endl<<endl;
	cin.get();

	/////////////////////////////////////////////////////////////////////////////////////////
	
	cout<<"Imprimos las recetas que no supere mas de " << calorias << " calorias:"<<endl;
	
	int contador = 0;
	vector< pair<float, receta> >::iterator i;
	for (i=sub_re.begin(); i!=sub_re.end(); ++i){
		//cout << (i->second).getCals() << endl;
		cout << "RATIO RECETA: " << i->first << endl
			 << "RECETA: " << i->second << endl;
		contador++;
	}
	cout << "NUM RECETAS FILTRADAS: " << contador << " igual a size: " << sub_re.size() << endl;

/////////////////////////////////////////////////////////////////////////////////////////

//una vez las tenemos ordenadas segun el ratio,
//vamos sumando las calorias del primero con el resto hasta
//conseguir que se hacerque al maximo a calorias dadas de tope.
	//VECTOR FINAL CON RECETAS
	vector < receta > re_final;
	float cals_totales = 0.0;
	float protes_totales = 0.0;
	
	//REUTILIZAMOS EL ITERADOR I DE VECTOR
	//vector< pair<float, receta> >::iterator i;
	for (i=sub_re.begin(); i!=sub_re.end(); ++i){
		
		float cals_leidas = i->second.getCals();
		cout << "CALS LEIDAS: " << cals_leidas << endl;
		
		float cals_tmp = cals_totales + cals_leidas;
		//si la receta alcanza calorias maximas, 
		//no lo lee y punto		
		if(cals_tmp <= calorias){
			//ACTUALIZAMOS PROTES Y CALS
			cals_totales = cals_tmp; //las leidas + las totales;
			protes_totales += i->second.getProtes();
			
			//RECOGEMOS CADA RECETA VALIDA EN EL VECTOR FINAL
			re_final.push_back(i->second);
		}
	}
	
	//MENSAJE SALIDA
	cout << "Las recetas escogidas son: " << endl;
	
	//IMPRIMIMOS RE_FINAL
	vector< receta >::iterator j;
	for (j=re_final.begin(); j!=re_final.end(); ++j){
		cout << "CALS DE LA RECETA: " << (*j).getCals() << endl
			 << (*j) << endl;
			 
	}
	
	//IMPRIMIMOS VALORES NUTRITIVOS FINALES:
	cout << "Calorias Totales: " << cals_totales 
	     << " Proteinas Totales: " << protes_totales 
	     << endl;

	return 0;
}
