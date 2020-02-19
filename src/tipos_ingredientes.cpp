#include <iostream>
#include "ingrediente.h"
#include "ingredientes.h"
//#include "VD.h"
#include <fstream>
#include <vector>
using namespace std;
void MuestraParametros(){
	
	cout<<"1.- Dime el nombre del fichero con los ingredientes y el tipo a buscar"<<endl;
}

int main(int argc, char *argv[])
{
  vector<int> test(5);
  if (argc!=3){
	  MuestraParametros();
	  return 0;
 }	
 /******************************************************************************************/	
 //SECTION 1: Test sobre la lectura de un ingrediente
 //Ingrediente debe tener operadores de consulta y de modificacion por cada parametros
 //ademas de sobrecarga de lectura y escritura
 string nf =argv[1];
 ifstream f(nf);
 if (!f){
    cout<<"No puedo abrir "<<nf<<endl;
    return 0;
 }
 //Quitamos la primera linea
 string linea;
 getline(f,linea);
 f.seekg(0);


//creamos el objeto all_ingre con todos los ingredientes.
 Ingredientes all_ingre;

 cout<<endl<<"Lectura de todos los ingredientes"<<endl<<endl;
 f>>all_ingre;
 
 cout<<"Pulse una tecla para continuar..."<<endl<<endl;
 cin.get();
}
