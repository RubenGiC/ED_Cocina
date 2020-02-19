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

Acciones Instrucciones::acc;

/*
  COMANDO PARA LLAMARLO EJEMPLO:
./bin/cocinero_integral datos/Acciones.txt datos/recetas.txt datos/ingredientes.txt datos/instrucciones/
*/


using namespace std;

/**
  *  @brief Programa Cocinero Integral
  *
  * Clase Nutricionreceta que calcula los valores nutricionales de cada receta
  *
  * @author Ruben Girela
  * @author Jorge Medina
  * @date Octubre 2019
  */
int main(int argc, char *argv[]){

  if(argc != 5){
  	perror("Error de argumentos esperados: <program> <acciones.txt> <recetas.txt> <ingredientes.txt> <instrucciones>");
  	exit(-1);
  }

  cout << "\n\t   * * * *\n\t   | | | |\n\t*************\n\t|   FELIZ   |\n    *********************\n    ";
  cout << "|CUMPLEAÑOS Cristina|\n    *********************" << endl;
  cout<<"\n Pulsa una tecla para continuar...."<<endl;
  cin.get();

  string ac =argv[1];
  ifstream f(ac);
  if (!f){
    cout<<"No puedo abrir "<<ac<<endl;
    return 0;
  }
  //cout << "Inserto las acciones" << endl;
  //cout << "********************************************************************************" << endl << endl;
  Acciones acciones;
  f>>acciones;

  f.close();

  cout << endl << "Muestro las acciones" << endl;
  cout << "********************************************************************************" << endl << endl;
  cout << acciones;

  cout<<"\n Pulsa una tecla para continuar...."<<endl;
  cin.get();

  //cout << "Añado las acciones en las instrucciones" << endl;
  //cout << "********************************************************************************" << endl << endl;
  //despues de cargar las acciones
  Instrucciones::acc = acciones;

  string ingre_f =argv[3];
  f.open(ingre_f);
  if (!f){
    cout<<"No puedo abrir "<<ac<<endl;
    return 0;
  }
  //cout << "Inserto los Ingredientes" << endl;
  //cout << "********************************************************************************" << endl << endl;
  Ingredientes ingredientes;
  f>>ingredientes;
  f.close();

  string recetas_f =argv[2];
  f.open(recetas_f);
  if (!f){
    cout<<"No puedo abrir "<<recetas_f<<endl;
    return 0;
  }
  //cout << "Inserto las recetas" << endl;
  //cout << "********************************************************************************" << endl << endl;
  recetas recets;
  recets.setIngredientes(ingredientes);
  f>>recets;
  f.close();

  //añado las instrucciones de cada receta
  recets.addInstrucciones(argv[4]);

  cout << "Muestro las recetas" << endl;
  cout << "********************************************************************************" << endl << endl;
  cout << recets;

  cout<<"Dime el codigo de una receta:";
  string c;
  cin>>c;
  //imprime la informacion de esa receta  
  recets.ImpremeReInfo(c);

  cout<<"\n Pulsa una tecla para continuar...."<<endl;
  cin.ignore();
  cin.get();

  receta r1,r2;
  string c1,c2;

  do{
    cout<<"Dime el codigo de la 1º receta:";
    cin>>c1;

    r1 = recets.buscar(c1);
    if(r1.getCode().length()==0)
      cout << "Error no existe la receta " << c1 << endl;  
  }while(r1.getCode().length()==0);

  do{
    cout<<"Dime el codigo de la 2º receta:";
    cin>>c2;

    r2 = recets.buscar(c2);
    if(r2.getCode().length()==0)
      cout << "Error no existe la receta " << c2 << endl;  
  }while(r2.getCode().length()==0);

  //llamaria a fusion de recetas....

  receta r_fusion;
  bool fusion = r_fusion.fusion(r1,r2,recets.getIngredientes());
  if(fusion){
    recets.addNuevaReceta(r_fusion);
    recets.ImpremeReInfo(r_fusion.getCode());

    cout<<"\n Pulsa una tecla para continuar...."<<endl;
    cin.ignore();
    cin.get();
    cout << "Muestro el arbol" << endl;
    cout << "********************************************************************************" << endl << endl;
    cout << endl << endl << r_fusion.getInstrucciones().mostrarArbol(true) << endl << endl; 
  }

  return 0;
}