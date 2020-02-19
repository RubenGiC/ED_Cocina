#ifndef __ACCIONES
#define __ACCIONES

#include<iostream>
#include <map>
#include<string>
using namespace std;

class Acciones{

private:
	map<string,unsigned char> datos;

public:

	/**
	  * @brief Busca una oreden que recibe por parametro
	  * @param orden (string)
	*/
	unsigned char buscar(string orden);

	/**
	* @brief Operador (>>)
	* @param is (Buffer de entrada)
  	* @param acc (Objeto Acciones donde se guardara todas las acciones del buffer)
	* @note
	*   lee el archivo y guarda las acciones
	*/
    friend istream& operator>> (istream& is, Acciones& acc);

    /**
	  * @brief Operador (<<)
	  * @param os (Buffer de salida que contendra la info de las acciones)
  	  * @param acc (Objeto Acciones donde contiene todas las acciones a devolver en el buffer)
	  * @note
	  *   lee el objeto y lo pasa al buffer
	*/
	friend ostream& operator<< (ostream& os, Acciones& acc);
};

#endif
