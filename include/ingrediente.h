/**
  * @file ingrediente.h
  * @brief Fichero cabecera del TDA Ingrediente
  *
  */
#ifndef __INGREDIENTE
#define __INGREDIENTE

#include <iostream>
#include <string>
using namespace std;

/**
  *  @brief T.D.A Ingrediente
  *
  * Clase Ingrediente que contiene los datos de un ingrediente
  *
  * @author Ruben Girela
  * @author Jorge Medina
  * @date Octubre 2019
  */

class Ingrediente{

private:
	/**
	  * @page repIngrediente Rep del TDA Ingrediente
	  *
	  * @section invIngrediente Ingrediente
	  *
	  * Es un TDA que nos permite almacenar tanto el nombre de un ingrediente como los valores nutricionales de un incrediente, es decir, sus calorias, y macronutrientes principales (hidratos de carbono, grasas, proteinas y fibra) asi como el tipo de alimento, por ejemplo, fruta, verdura, carnes entre otros.
	  
	  * @section faIngrediente Resumen Atributos Ingrediente
	  * 
	  * - @c Nombre del Alimento 			(string)
	  * - @c Calorias			 			(float)
	  * - @c Macronutrientes principales	(float)
	  * 		- @c Hidratos de Carbono
	  * 		- @c Grasas
	  * 		- @c Proteinas
	  * 		- @c Fibra
	  * - @c Tipo de alimento				(string)
	  *
	  *
	  * @section faIngredienteMetodos Principales metodos y sobrecargas :
	  *
	  * - @c Tanto gets como sets
	  *
	  * - @c operator >> ( capaz de leer un ingrediente completo )
	  * - @c operator << ( nos permite escribir los valores de un ingrediente al completo )
	  * 
	  */
	
	string nombre;/**< Indica el nombre del ingrediente */
	float calorias;/**< Indica las calorias del ingrediente cada 100 gramos */
	float hidratos_de_carbono; /**< Indica en % los hidratos de carbono */
	float proteinas; /**< Indica en % las proteinas */
	float grasas; /**< Indica en % las grasas */
	float fibra; /**< Indica en % la fibra */
	string tipo; /**< Indica el tipo de alimento que es (pescado,verdura, carne, ...) */

public:
	/**
	  * @brief Constructor por defecto
	  * @note
	  *   Este es el constructor por defecto, que inicializa los valores por defecto.
	*/
	Ingrediente();
	/**
	  * @brief Constructor por parametros
	  * @param nom (Nombre del ingrediente)
	  * @param cal (Calorias)
	  * @param hid_carb (Hidratos de Carbono)
	  * @param prot (Proteinas)
	  * @param gras (Grasas)
	  * @param fib (Fibra)
	  * @param tip (Tipo)
	  * @note
	  *   Este constructor tabien corresponde al constructor por defecto.
	*/
	Ingrediente(string nom, float cal, float hid_carb, float prot, float gras, float fib, string tip);
	/**
	  * @brief Constructor de copia
	  * @param original (objeto Ingrediente en el que se copiaran los datos)
	  * @note
	  *   Este constructor hace una copia del vector pasado por parametro y lo guarda en el otro.
	*/
	Ingrediente(const Ingrediente& original);

	/**
	  * @brief Metodo que devuelve el nombre del ingrediente
	  * @return string nombre del ingrediente
	*/
	string getNombre() const{
		return nombre;
	}

	/**
	  * @brief Metodo que devuelve las calorias del ingrediente
	  * @return float calorias del ingrediente
	*/
	float getCalorias() const{
		return calorias;
	}

	/**
	  * @brief Metodo que devuelve los hidratos de carbono del ingrediente
	  * @return float hidratos_de_carbono del ingrediente
	*/
	float getHc() const{
		return hidratos_de_carbono;
	}

	/**
	  * @brief Metodo que devuelve las proteinas del ingrediente
	  * @return float proteinas del ingrediente
	*/
	float getProteinas() const{
		return proteinas;
	}

	/**
	  * @brief Metodo que devuelve las grasas del ingrediente
	  * @return float grasas del ingrediente
	*/
	float getGrasas() const{
		return grasas;
	}

	/**
	  * @brief Metodo que devuelve la fibra del ingrediente
	  * @return float fibra del ingrediente
	*/
	float getFibra() const{
		return fibra;
	}

	/**
	  * @brief Metodo que devuelve el tipo de ingrediente
	  * @return float tipo del ingrediente
	*/
	string getTipo() const{
		return tipo;
	}

	/**
	  * @brief Metodo que cambia el valor de las calorias del ingrediente
	  * @param cal (Calorias)
	*/
	void setCalorias(float cal){calorias=cal;}

	/**
	  * @brief Metodo que cambia el valor de los hidratos de carbono del ingrediente
	  * @param hdc (Hidratos de Carbono)
	*/
	void setHC(float hdc){hidratos_de_carbono=hdc;}

	/**
	  * @brief Metodo que cambia el valor de las proteinas del ingrediente
	  * @param prot (Proteinas)
	*/
	void setProteinas(float prot){proteinas=prot;}

	/**
	  * @brief Metodo que cambia el valor de las grasas del ingrediente
	  * @param gras (Grasas)
	*/
	void setGrasas(float gras){grasas=gras;}

	/**
	  * @brief Metodo que cambia el valor de la fibra del ingrediente
	  * @param fib (Fibra)
	*/
	void setFibra(float fib){fibra = fib;}

	/**
	  * @brief Metodo que cambia el tipo del ingrediente
	  * @param tip (Tipo)
	*/
	void setTipo(string tip){tipo=tip;}

	/**
	  * @brief Metodo que cambia el nombre del ingrediente
	  * @param nom (Nombre)
	*/
	void setNombre(string nom){nombre = nom;}

	/**
	  * @brief Metodo que por pantalla los datos del ingrediente
	*/
	void imprimir();

	/**
	  * @brief Operador (=)
	  * @param original (objeto Ingrediente a copiar)
	  * @note
	  *   reemplaza el contenido de un objeto por el de otro 
	*/
	Ingrediente& operator=(const Ingrediente& original);

	/**
	  * @brief Operador (>>)
	  * @param is (Buffer de entrada)
  	  * @param ing (Objeto Ingrediente donde se guardara los datos del buffer)
	  * @note
	  *   lee el archivo y guarda los datos cada uno en su variable
	*/
	friend istream& operator>> (istream& is, Ingrediente& ing);
	/**
	  * @brief Operador (<<)
	  * @param os (Buffer de salida que contendra la info del ingrediente)
  	  * @param ing (objeto Ingrediente que le pasara la informacion al buffer)
	  * @note
	  *   lee el objeto y lo pasa al buffer
	*/
	friend ostream& operator<< (ostream& os, Ingrediente& ing);
	/**
	  * @brief Operador (==) compara si 2 Ingredientes son iguales
  	  * @param ing (objeto Ingrediente a comparar)
	*/
	bool operator==( const Ingrediente ing ) const;
};
#endif
