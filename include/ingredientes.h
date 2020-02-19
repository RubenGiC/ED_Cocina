/**
  * @file ingredientes.h
  * @brief Fichero cabecera del TDA Ingredientes
  *
  */
#ifndef __INGREDIENTES
#define __INGREDIENTES

#include <iostream>
#include <string>
#include <vector>
//#include "VD.h"
#include "ingrediente.h"
using namespace std;

/**
  *  @brief T.D.A Ingredientes
  *
  * Almacenara todos los ingredientes.
  *
  * @author Ruben Girela
  * @author Jorge Medina
  * @date Octubre 2019
  */

class Ingredientes{

private:
	/**
	  * @page repIngredientes Rep del TDA Ingredientes
	  *
	  * @section invIngredientes Ingredientes
	  *
	  * Consiste en almacenar cada ingrediente en un vector dinamico de ingredientes, 
	  * es decir va a ser una
      * coleccion de objetos de Ingrediente y el indice ordenado por nombre y tipo, tambien borrar, modificar y demas.
      *
      * @section faIngredientesMetodos Metodos de Ingredientes
	  * La clase ingredientes a parte de almacenar ingredientes de todo tipo tambien calcula valores Estadisticos como la media, la desviacion tipica, el maximo y el minimo de los valores de cada uno de los campos de cada uno de ellos:
	  * 	- @c Media: Sumatoria de todos los valores de un campo (Calorias, Fibra, etc.) de entre el total de elementos que hay.
	  * 	- @c Desviacion: (Sumatoria de cada (dato - la media del dato)²) / (n-1), siendo n el numero total de elementos.
	  * 	- @c Valor Maximo y Valor Minimo de un campo contreto.
	  *
	  * Aunque sus principales metodos son los siguientes:
	  *		- @c Filtrar ingredientes por Tipo de alimento
	  *		- @c Imprimir todos los tipos existentes
	  *		- @c Buscar un un ingrediente concreto por nombre
	  * 	- @c Imprimir un ingrediente al completo
	  *		- @c Aniadir un ingrediente por orden alfabetico
	  *
	  *
	  * @section faIngredientesAtrib Los Atributos de Ingredientes
	  * 	- @c @e datos, un VD de ingrediente, es decir, almacena cada uno de los alimentos
	  *	- @c @e indice, un VD de enteros que contiene los indices de cada no de los ingredientes de datos para apuntar de forma ordenada a sus tipos, y asi poder filtrar por tipo de alimento de forma comoda.
  	  * Un ejemplo de su uso puede ser el propio programa test_ingredientes en el que se ponen a prueba tanto la clase Ingrediente e Ingredientes como la del Vector Dinamico(VD) :
  	  * @include test_ingredientes.cpp
	  */

//contiene todos los ingredientes
  vector<Ingrediente> datos;

//contiene los indices segun el orden de sus tipos:
//Fruta va a antes que Molusco y en caso de mismo tipo
//Moluscos, almeja vs mejillon, iria antes la almeja.
//alamcenando el indice de la posicion en la que aparece
//en el vector de datos
  vector<int> indice;

public:

	/** @page Iteradores
	  * @section Iterador 
	  * que realiza las operaciones de incrementar, decrementar, comparar si son iguales o no
	  * sustituir, consultar y añadir
	  */
	class iterador{
		private:
			vector<Ingrediente>::iterator it;
		public:
			/**
			  * @brief Constructor por defecto
			*/
			iterador(): it(0){}
			/**
			  * @brief Constructor que recibe por parametro un iterador
			  * @param v (iterador a sustituir)
			  * @note
			  *   Este es el constructor de copia
			*/
			iterador(const iterador& v): it(v.it){}
			/**
			  * @brief Destructor
			*/
			~iterador(){}

			/**
			  * @brief Operador =
			  * @param v (iterador a remplazar)
			  * @return iterador
			*/
			iterador& operator=(const iterador& orig){
				it = orig.it;
				return *this;
			}
			/**
			  * @brief Operador *
			  * @return (Este devuelve un ingrediente del iterador)
			*/
			Ingrediente& operator*() const{
				//assert(it!=0);
				return *it;
			}
			/**
			  * @brief Operador ++
			  * @note
			  *   Este avanza hacia la derecha el contenido del iterador
			  * @return iterador+1 (el siguiente iterador)
			*/
			iterador& operator++(){
				//assert(it!=0);
				it++;
				return *this;
			}
			/**
			  * @brief Operador --
			  * @note
			  *   Desplaza hacia la izquierda el iterador
			  * @return iterador-1 (el anterior iterador)
			*/
			iterador& operator--(){
				//assert(it!=0);
				it--;
				return *this;
			}
			/**
			  * @brief Operador !=
			  * @param v (iterador a comparar)
			  * @note
			  *   Este es el constructor que compara el iterador al que llama al operador con
			  *   el que recibe por parametro, si no son iguales true y si son false.
			  * @return true si son distintos, false en caso contrario
			*/
			bool operator!=(const iterador& v) const{ return it!=v.it;}
			
			/**
			  * @brief Operador ==
			  * @param v (iterador a comparar)
			  * @note
			  *   Este es el constructor que compara el iterador al que llama al operador con
			  *   el que recibe por parametro, si son iguales true y si no false.
			  * @return true si son iguales, false en caso contrario
			*/
			bool operator==(const iterador& v) const{ return it==v.it;}
			friend class Ingredientes;
	};
	/** 
	  * @section Iterador constante
	  * que realiza las operaciones de incrementar, decrementar, comparar si son iguales o no
	  * sustituir, consultar y añadir
	  */
	class const_iterador{
		private:
			vector<Ingrediente>::const_iterator it;
			const_iterador(vector<Ingrediente>::iterator it2): it(it2){}
		public:
			/**
			  * @brief Constructor por defecto
			*/
			const_iterador(): it(0){}
			/**
			  * @brief Constructor que recibe por parametro un iterador constante
			  * @param v (iterador a sustituir)
			  * @note
			  *   Este es el constructor de copia
			*/
			const_iterador(const const_iterador& v): it(v.it){}
			/**
			  * @brief Constructor que recibe por parametro un iterador
			  * @param v (iterador a sustituir)
			  * @note
			  *   Este es el constructor de copia
			*/
			const_iterador(const iterador& v): it(v.it){}
			/**
			  * @brief Destructor
			*/
			~const_iterador(){}
			/**
			  * @brief Operador ==
			  * @param v (iterador a comparar)
			  * @note
			  *   Este es el constructor que compara el iterador al que llama al operador con
			  *   el que recibe por parametro, si son iguales true y si no false.
			  * @return true si son iguales, false en caso contrario
			*/
			const_iterador& operator==(const const_iterador& orig){
				it = orig.it;
				return *this;
			}
			/**
			  * @brief Operador *
			  * @note
			  *   Este devuelve un ingrediente del iterador
			  * @return (Este devuelve un ingrediente del iterador)
			*/
			const Ingrediente& operator*() const{
				//assert(it!=0);
				return *it;
			}
			/**
			  * @brief Operador ++
			  * @note
			  *   Este avanza hacia la derecha el contenido del iterador
			  * @return iterador+1 (el siguiente iterador)
			*/
			const_iterador& operator++(){
				//assert(it!=0);
				it++;
				return*this;
			}
			/**
			  * @brief Operador --
			  * @note
			  *   Desplaza hacia la izquierda el iterador
			*/
			const_iterador& operator--(){
				//assert(it!=0);
				it--;
				return *this;
			}
			/**
			  * @brief Operador !=
			  * @param v (iterador a comparar)
			  * @note
			  *   Este es el constructor que compara el iterador al que llama al operador con
			  *   el que recibe por parametro, si no son iguales true y si son false.
			  * @return true si son distintos, false en caso contrario
			*/
			bool operator!=(const const_iterador& v){
				return it!=v.it;
			}
			friend class Ingredientes;

	};
	/**
	  * @brief Iterador de inicio
	  * @note
	  *   devuelve el primer iterador del vector
	  * @return iterador
	*/
	iterador begin(){
		iterador i;
		i.it = datos.begin();
		return i;
	}
	/**
	  * @brief Iterador de fin
	  * @note
	  *   devuelve el ultimo iterador del vector
	  * @return iterador
	*/
	iterador end(){
		iterador i;
		i.it = datos.end();
		return i;
	}
	/**
	  * @brief Iterador de inicio constante
	  * @note
	  *   devuelve el primer iterador del vector
	  * @return const_iterador
	*/
	const_iterador begin1(){return const_iterador(datos.begin());}
	/**
	  * @brief Iterador de fin constante
	  * @note
	  *   devuelve el ultimo iterador del vector
	  * @return const_iterador
	*/
	const_iterador end1(){  return const_iterador(datos.end());	}

	/**
	  * @brief Constructor por defecto
	  * @note
	  *   Este es el constructor por defecto, que inicializa los valores por defecto.
	*/
	Ingredientes();

	/**
	  * @brief Constructor que recibe por parametro el tamaño del vector
	  * @param tam (Tamaño del vector)
	  * @note
	  *   Este es el constructor reserva el tamaño indicado por parametro al atributo datos.
	  * @pre (tam) tiene que ser > 0
	*/
	Ingredientes(int tam);

	/**
	  * @brief Constructor de copia
	  * @param original (Objeto Ingredientes a copiar)
	  * @note
	  *   Este constructor hace una copia del vector pasado por parametro y lo guarda en el otro.
	*/
	Ingredientes(const Ingredientes& original);

	/**
	  * @brief Metodo que devuelve un ingrediente
	  * @param n (Indice del Ingrediente a devolver)
	  * @pre (n) tiene que estar dentro del rango 0 >= n < k-1, siendo k el total de celdas usadas
	  * @return Ingrediente
	*/
	Ingrediente getIngrediente(int n) const;

	/**
	  * @brief Devuelve VD<string> con los tipos de ingrediente
	  * @return un VD<string> con cada tipo de ingrediente
	*/
	vector<string> getTipos();

	/**
	 * @brief Devuelve un objeto ingredientes con ingredientes de un tipo concreto
	 * @param tipo_ingr (Tipo de ingrediente de tipo string)
	 * @return devuelve el objeto ingredientes con los ingredientes q sean del mismo tipo
	*/
	Ingredientes getIngredientesTipo(string tipo_ingr);

	/**
	  * @brief Metodo que devuelve un ingrediente si coincide con el nombre, si no coincide devuelve null
	  * @param n (nombre del ingrediente a buscar)
	  * @return Ingrediente si existe, en caso contrario devuelve un ingrediente por defecto
	*/
	Ingrediente get(string n) const;

	/**
	  * @brief Metodo que devuelve un ingrediente si coincide con el nombre, si no coincide devuelve null
	  * @param n (nombre del ingrediente a buscar)
	  * @return Ingrediente si existe, en caso contrario devuelve un ingrediente por defecto
	*/
	Ingrediente buscarIngrediente(string n) const;

	/**
	 * @brief Metodo que hace operaciones estadisticas con los ingredientes de un mismo tipo
	*/
	void EstadisticosTipo() const;

	/**
	 * @brief Metodo que imprime la informacion de un ingrediente, que recibe por parametro el nombre
	 * @param nombre (Nombre del ingrediente a imprimir)
	*/
	void imprimeIngrediente(string nombre) const;
	
	/**
	  * @brief Metodo que devuelve el numero de ingredientes
	  * @return int devuelve un entero
	*/
	int size() const{return datos.size();}

	/**
	  * @brief Metodo que añade un nuevo ingrediente que recibe por parametro dato y lo añade en la ultima posicion libre del vector
	  * @param ingrediente (Objero Ingrediente a añadir)
	*/
	void add(Ingrediente ingrediente);

	/**
	 * @brief a partir de una posicion dada, se suman 1 a los valores de datos
	 * @param pos_inicial (Posicion inicial del vector)
	*/
	void actualizar_por_add(int pos_inicial);

	/**
	 * @brief Devuelve la posicion en la que se encuentra el elemento a buscar
	 * @param elemento_a_buscar (Objeto T a buscar en el vector de objetos T)
	 * @return devuelve la posicion en la que se encuentra el parametro que buscamos
	*/
	int devuelveIndice(int elemento_a_buscar);

private:
	/**
	 * @brief Metodo que encuentra la posicion ordenada segun nombre en la que insertar el ingrediente
	 * @param ingr (Objeto Ingrediente a buscar en el vector de Ingredientes, por nombre)
	 * @return entero con la posicion a insertar
	*/
	int BuscaPosNombre(Ingrediente ingr) const;

	/**
	 * @brief Metodo que encuentra la posicion ordenada segun tipo en la que insertar el ingrediente
	 * @param ingr (Objeto Ingrediente a buscar en el vector de Ingredientes, por Tipo)
	 * @return entero con la posicion a insertar
	*/
	int BuscaPosTipo(Ingrediente ingr) const;

	/**
	  * @brief Metodo que borra un ingrediente que se le pasa por parametro
	  * @param ingr (Objeto Ingrediente a eliminar del vector de Ingredientes)
	*/
	void elimina(Ingrediente ingr);

	/**
	 * @brief Calcula la media de cada dato segun el nombre que tengan
	 * @param info (String tipo a calcular [grasas, fibra,...])
	 * @return float con la media
	*/
	float CalculaMedia(string info) const;

	/**
	 * @brief Calcula la desviacion estandar de cada dato segun el nombre que tengan
	 * @param info (String tipo a calcular [grasas, fibra,...])
	 * @return float con la desviacion tipica
	*/
	float CalculaDesviacion(string info) const;

	/**
	 * @brief Calcula el maximo valor de la info que te pasen como paremetro
	 * @param info (String tipo a calcular [grasas, fibra,...])
	 * @return float con el valor maximo de todos los valores
	*/
	float CalculaMaxVal(string info) const;

	/**
	 * @brief Calcula el minimo valor de la info que te pasen como paremetro
	 * @param info (String tipo a calcular [grasas, fibra,...])
	 * @return float con el valor minimo de todos los valores
	*/
	float CalculaMinVal(string info) const;

	/**
	 * @brief Calcula el maximo NOMBRE de la info que te pasen como paremetro
	 * @param info (String tipo a calcular [grasas, fibra,...])
	 * @return string con el valor nombre del ingrediente con el valor maximo en ese info 
	*/
	string CalculaMaxNombre(string info) const;

	/**
	 * @brief Calcula el minimo NOMBRE de la info que te pasen como paremetro
	 * @param info (String tipo a calcular [grasas, fibra,...])
	 * @return string con el valor nombre del ingrediente con el valor minimo en ese info 
	*/
	string CalculaMinNombre(string info) const;



public:
	/**
	  * @brief Metodo que borra un ingrediente a traves de la posicion que recibe por parametro pos
	  * @param pos (Posicion a eliminar un objeto Ingrediente en el vector de Ingredientes)
	  * @pre (pos) tiene que estar dentro del rango 0 >= pos < k-1, siendo k el total de celdas usadas
	*/
	void eliminar(int pos);

	/**
	  * @brief Metodo que borra un ingrediente a traves del numbre que recibe por parametro nom
	  * @param nom (nombre del ingredeinte a borrar en el vector de Ingredientes)
	*/
	void borrar(string nom);

	/**
	  * @brief Metodo que muestra por pantalla los Igredientes
	*/
	void imprimir();

	/**
	 * @brief Metodo que imprime todos los ingredientes segun su tipo en orden alfabetico
	 * @param os (Buffer de salida que contendra la info de los ingredientes)
	*/
	void ImprimirPorTipo(ostream& os);

	/**
	  * @brief Operador (>>)
	  * @param is (Buffer de entrada)
  	  * @param ings (Objeto Ingredientes donde se guardara todos los ingredientes que contenga el buffer)
	  * @note
	  *   lee el archivo y guarda los datos cada uno en su variable
	*/
	friend istream& operator>> (istream& is, Ingredientes& ings);
	/**
	  * @brief Operador (<<)
	  * @param os (Buffer de salida que contendra la info de los ingredientes)
  	  * @param ings (Objeto Ingredientes donde contiene los Ingredientes a devolver en el buffer)
	  * @note
	  *   lee el objeto y lo pasa al buffer
	*/
	friend ostream& operator<< (ostream& os, Ingredientes& ings);
};

#endif
