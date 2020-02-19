/**
  * @file recetas.h
  * @brief Fichero cabecera del TDA Recetas
  *
  */
#ifndef __RECETAS
#define __RECETAS


#include "receta.h"
#include <string>
#include <map>
#include "ingredientes.h"
#include "receta.h"
#include "acciones.h"
#include "instrucciones.h"

using namespace std;

/**
  *  @brief T.D.A Recetas
  *
  * Almacenara todas las recetas.
  *
  * @author Ruben Girela
  * @author Jorge Medina
  * @date Octubre 2019
  */

class recetas{
    private:
        map<string, receta> datos;
        Ingredientes all_ingredientes;
        
	public:

///////////////////////////////////////////////////////////////////
//------------------------CLASES ITERADOR------------------------//
///////////////////////////////////////////////////////////////////

	class iterador{
        private:

/**
* @page repRecetas Rep del TDA Recetas
*
* @section invRecetas Recetas
*
* Consiste en almacenar cada receta en un map, almacenando el codigo y el objeto Receta
*
* @section faRecetasMetodos Metodos de Recetas
* La clase recetas a parte de almacenar recetas borra una receta especifica y contiene los iteradores, tanto
* constantes como no constantes.
*
* @section faRecetasAtrib Los Atributos de Recetas
* 	- @c @e its, un map de <string,receta>, siendo el (string) el codigo, es decir, almacena cada receta
*	
*/

            map<string, receta>::iterator its;
        
        
        public:
        	
        	/**
			  * @brief Constructor por defecto
			*/
		    iterador(): its(0){}
		    
		     /**
			  * @brief Constructor que recibe por parametro un iterador
			  * @param ittr (iterador a sustituir)
			  * @note
			  *   Este es el constructor de copia
			*/
		    iterador(const iterador& ittr): its(ittr.its){}
		    
		    /**
			  * @brief Destructor
			*/
		    ~iterador(){}
		    
		     /**
			  * @brief Operador =
			  * @param orig (iterador a remplazar)
			  * @return iterador
			*/
		    iterador& operator=(const iterador& orig){
				its = orig.its;
				return *this;
			}
			
			/**
			  * @brief Operador *
			  * @return (Este devuelve una receta del iterador)
			*/
			receta& operator*() const{
				return its->second; //devolvemos las recetas
			}
			
			/**
			  * @brief Operador ++
			  * @note
			  *   Este avanza hacia la derecha el contenido del iterador
			  * @return iterador+1 (el siguiente iterador)
			*/
			iterador& operator++(){
				its++;
				return *this;
			}
			
			/**
			  * @brief Operador --
			  * @note
			  *   Desplaza hacia la izquierda el iterador
			  * @return iterador-1 (el anterior iterador)
			*/
			iterador& operator--(){
				its--;
				return *this;
			}
		    
		    /**
			  * @brief Operador !=
			  * @param ittr (iterador a comparar)
			  * @note
			  *   Este es el constructor que compara el iterador al que llama al operador con
			  *   el que recibe por parametro, si no son iguales true y si son false.
			  * @return true si son distintos, false en caso contrario
			*/
		    bool operator!=(const iterador& ittr) const{ return its != ittr.its; }
		     
		     /**
			  * @brief Operador ==
			  * @param v (iterador a comparar)
			  * @note
			  *   Este es el constructor que compara el iterador al que llama al operador con
			  *   el que recibe por parametro, si son iguales true y si no false.
			  * @return true si son iguales, false en caso contrario
			*/
		     bool operator==(const iterador& v) const{ return its == v.its; }
        
        
        friend class recetas;
        
    };
    
///////////////////////////////////////////////////////////////////
//------------------------CLASES CONST_ITERADOR------------------//
///////////////////////////////////////////////////////////////////
    
    class const_iterador{
        private:
            map<string, receta>::const_iterator its;
        
        
        public:
        	
        	/**
			  * @brief Constructor por defecto
			*/
		    const_iterador(): its(0){}
		    
		    /**
			  * @brief Constructor que recibe por parametro un iterador constante
			  * @param v (iterador a sustituir)
			  * @note
			  *   Este es el constructor de copia
			*/
		    const_iterador(const const_iterador& ittr): its(ittr.its){}

		    /**
			  * @brief Constructor que recibe por parametro un iterador
			  * @param ittr (iterador a sustituir)
			  * @note
			  *   Este es el constructor de copia
			*/
	        const_iterador(const iterador& ittr): its(ittr.its){}
		    
		    /**
			  * @brief Destructor
			*/
		    ~const_iterador(){}
		    
		    /**
			  * @brief Operador =
			  * @param orig (iterador a remplazar)
			  * @return iterador
			*/
		    const_iterador& operator=(const const_iterador& orig){
				its = orig.its;
				return *this;
			}
			
			
			/**
			  * @brief Operador *
			  * @note
			  *   Este devuelve una receta del iterador
			  * @return (Este devuelve una receta del iterador)
			*/
			const receta& operator*() const{
				return its->second; //devolvemos las recetas
			}
			
			/**
			  * @brief Operador ++
			  * @note
			  *   Este avanza hacia la derecha el contenido del iterador
			  * @return iterador+1 (el siguiente iterador)
			*/
			const_iterador& operator++(){
				its++;
				return *this;
			}
			
			/**
			  * @brief Operador --
			  * @note
			  *   Desplaza hacia la izquierda el iterador
			  * @return iterador-1 (el anterior iterador)
			*/
			const_iterador& operator--(){
				its--;
				return *this;
			}
		    
		    /**
			  * @brief Operador !=
			  * @param ittr (iterador a comparar)
			  * @note
			  *   Este es el constructor que compara el iterador al que llama al operador con
			  *   el que recibe por parametro, si no son iguales true y si son false.
			  * @return true si son distintos, false en caso contrario
			*/
		    bool operator!=(const const_iterador& ittr) const{ return its != ittr.its; }
		     
		     /**
			  * @brief Operador ==
			  * @param v (iterador a comparar)
			  * @note
			  *   Este es el constructor que compara el iterador al que llama al operador con
			  *   el que recibe por parametro, si son iguales true y si no false.
			  * @return true si son iguales, false en caso contrario
			*/
		     bool operator==(const const_iterador& v) const{ return its == v.its; }
        
        
        friend class recetas;
        
    };

	//BEGIN Y END
	
	/**
	  * @brief Iterador de inicio
	  * @note
	  *   devuelve el primer iterador del vector
	  * @return iterador
	*/
	iterador begin()
    {
     	//creamos un iterador propio
     	iterador ittr;
     	
     	//en el atributo iterator its, le asignamos el begin
     	ittr.its = datos.begin();
     	
     	//devolvemos el iterador propio
     	return ittr;
    }
    
    /**
	  * @brief Iterador de fin
	  * @note
	  *   devuelve el ultimo iterador del vector
	  * @return iterador
	*/
    iterador end() 
    {
	 	iterador ittr;
	 	ittr.its = datos.end();
	 	return ittr;
	}
	
	//CONST BEGIN Y END
	
	/**
	  * @brief Iterador de inicio constante
	  * @note
	  *   devuelve el primer iterador del vector
	  * @return const_iterador
	*/
	const_iterador begin() const
    {
     	//creamos un iterador propio
     	const_iterador ittr;
     	
     	//en el atributo iterator its, le asignamos el begin
     	ittr.its = datos.begin();
     	
     	//devolvemos el iterador propio
     	return ittr;
    }
    
    /**
	  * @brief Iterador de fin constante
	  * @note
	  *   devuelve el ultimo iterador del vector
	  * @return const_iterador
	*/
    const_iterador end() const
    {
	 	const_iterador ittr;
	 	ittr.its = datos.end();
	 	return ittr;
	}

//////////////////////////////////////////////////////////////////
/////////////////////////FUNCIONES PRIVADAS///////////////////////
//////////////////////////////////////////////////////////////////
/*
private:
	float CalcSumaRatio(const receta& r1, const receta& r2);
*/
	
//////////////////////////////////////////////////////////////////
/////////////////////////METODOS/////////////////////////////////
//////////////////////////////////////////////////////////////////

	/**
	  * @brief devuelve el numero de recetas que hay
	  * @return (int)
	*/
	int size();
	/**
	  * @brief Borra una receta especifica a traves del codigo
	  * @param codigo (string que contiene el codigo de la receta a borrar)
	*/
	void borrar(string codigo);

	/**
	  * @brief Busca una receta especifica a traves del codigo
	  * @param codigo (string que contiene el codigo de la receta a buscar)
	*/
	receta buscar(string codigo);
	/**
	  * @brief imprime la informacion de una receta especifica a traves del codigo
	  * @param codigo (string que contiene el codigo de la receta a buscar)
	*/
	void ImpremeReInfo(string codigo);

	/**
	  * @brief añade las instrucciones a cada receta
	  * @param ruta donde se encuentra las instrucciones
	*/
	void addInstrucciones(string ruta);

	/**
	  * @brief añade una nueva receta
	  * @param rec (receta) la nueva receta a insertar
	*/
	void addNuevaReceta(receta rec);

	/**
	  * @brief setIngredientes modifica los ingredientes
	  * @param ings (Ingredientes) los nuevos ingredientes a sustituir
	*/
	void setIngredientes(Ingredientes ings){ all_ingredientes = ings;}

	/**
	  * @brief Metodo constante que devuelve los ingredientes que tiene recetas
	  * @return Ingredientes (objeto ingredientes)
	*/
	Ingredientes getIngredientes(){ return all_ingredientes;}
	

///////////////////////////////////////////////////////////////////
//------------------------OPERATORS------------------------//
///////////////////////////////////////////////////////////////////

	/**
	  * @brief Operador ([]), que devuelve una receta
  	  * @param codigo (string que contiene el codigo de la receta a buscar)
	  * @return devuelve la receta a buscar
	*/
	receta & operator [](string codigo);

   /**
	* @brief Operador (>>)
	* @param is (Buffer de entrada)
  * @param rall (Objeto Recetas donde se guardara todas las recetas del buffer)
	* @note
	*   lee el archivo y guarda las recetas
	*/
    friend istream& operator>> (istream& is, recetas& rall);

    /**
	  * @brief Operador (<<)
	  * @param os (Buffer de salida que contendra la info de las recetas)
  	  * @param rall (Objeto Recetas donde contiene todas las recetas a devolver en el buffer)
	  * @note
	  *   lee el objeto y lo pasa al buffer
	*/
	friend ostream& operator<< (ostream& os, recetas& rall);
};

#endif
