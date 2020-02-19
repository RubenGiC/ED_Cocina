/**
  * @file instrucciones.h
  * @brief Fichero cabecera del TDA Instrucciones
  *
  */

#ifndef __INSTRUCCIONES
#define __INSTRUCCIONES

#include<iostream>
#include<string>
#include <fstream>

#include "acciones.h"
#include "arbolbinario.h"
#include "ingredientes.h"

using namespace std;

/**
  *  @brief T.D.A Instrucciones
  *
  * Almacenara todas las instrucciones.
  *
  * @author Ruben Girela
  * @date Octubre 2019
  */

class Instrucciones{
	private:

		/**
		  * @page repInstrucciones Rep del TDA Instrucciones
		  *
		  * @section invInstrucciones Instrucciones
		  *
		  * Consiste en almacenar las instrucciones de cada receta.
	      *
		  * Sus principales metodos son los siguientes:
		  *		- @c Operadores de entrada (>>) y salida (<<)
		  *		- @c mostrarArbol, Imprime el arbol con las instrucciones (true or false)
		  *			- @c (false) ComoElFichero, Imprime el arbol como en el archivo viene
		  *			- @c (true) Esquema, Imprime el arbol de forma grafica de como es el arbol
		  * 	- @c getArbol devuelve el arbol que tiene
		  *		- @c combinarInstrucciones combina 2 arboles en 1
		  *
		  *
		  * @section faInstruccionesAtrib Los Atributos de Instrucciones
		  * 	- @c @e datos , un arbol binario (string) que guarda las acciones y los ingredientes
		  *		- @c @e acc, guarda las acciones para el arbol binario
		  */
		ArbolBinario<string> datos;

	public:
		static Acciones acc;

		/**
		  * @brief Metodo que devuelve un string del arbol, es decir un string que contiene un esquema
		  * grafico de como es el arbol.
		  * @param n (nodo por donde empieza)
		  * @param pre (parametro auxiliar que hace la estructura del arbol de forma grafica)
		  * @return string grafico del arbol
		*/
		string Esquema(ArbolBinario<string>::nodo n, string& pre);

		/**
		  * @brief Metodo que devuelve un string del arbol mostrandolo como viene en el archivo
		  * @param n (nodo por donde empieza)
		  * @return string de las instrucciones
		*/
		string ComoElFichero(ArbolBinario<string>::nodo n);

		/**
		  * @brief Metodo que devuelve un string del arbol ya sea de forma grafica o como en el archivo
		  * @param tip (booleano) (true)--> Esquema (fasle)--> ComoElFichero
		  * @return string del arbol
		*/
		string mostrarArbol(bool tip);

		/**
		  * @brief Metodo que combina 2 arboles en 1, recibiendo como parametro 2 instrucciones, 
		  * para acceder a sus arboles.
		  * @param i1 (Instucciones)
		  * @param i2 (Instucciones)
		*/
		void combinarInstrucciones(Instrucciones i1, Instrucciones i2);

		/**
		  * @brief Metodo que devuelve el arbol
		  * @return ArbolBinario<string>
		*/
		ArbolBinario<string> getArbol(){return datos;}

		/**
		  * @brief Metodo que devuelve un bool si existen o no los ingredientes de instrucciones
		  * @param ing (Ingredientes)
		  * @return bool (true) se puede hacer la fusion (false) no se puede hacer la fusion
		*/
		bool existeIngredientes(Ingredientes ing);
		/**
		  * @brief Metodo que devuelve un bool si existen o no un ingrediente de instrucciones
		  * @param ing (Ingredientes) para comparar
		  * @param n (nodo) para recorrer el arbol
		  * @return bool (true) se puede hacer la fusion (false) no se puede hacer la fusion
		*/
		bool existeIngrediente(Ingredientes ing, ArbolBinario<string>::nodo n);

		/**
		* @brief Operador (>>)
		* @param is (Buffer de entrada)
	  	* @param ins (Objeto Instrucciones donde se guardara todas las instrucciones del buffer)
		* @note
		*   lee el archivo y guarda las instrucciones
		*/
	    friend istream& operator>> (istream& is, Instrucciones& ins);

	    /**
		  * @brief Operador (<<)
		  * @param os (Buffer de salida que contendra la info de las instrucciones)
	  	  * @param ins (Objeto Instrucciones donde contiene todas las instrucciones a devolver en el buffer)
		  * @note
		  *   lee el objeto y lo pasa al buffer
		*/
		friend ostream& operator<< (ostream& os, Instrucciones& ins);
};
#endif
