/**
  * @file receta.h
  * @brief Fichero cabecera del TDA Receta
  *
*/

#ifndef __RECETA
#define __RECETA

#include<iostream>
#include<list>
#include<string>
#include "ingrediente.h"
#include "ingredientes.h"
#include "acciones.h"
#include "instrucciones.h"
using namespace std;

/**
  *  @brief T.D.A Receta
  *
  * Representa la informacion de una receta de cocina.
  *
  * @author Ruben Girela
  * @author Jorge Medina
  * @date Octubre 2019
  */

class receta{
private:
    /**
	  * @page repReceta Rep del TDA Receta
	  *
	  * @section invReceta Receta
	  *
	  * Es un TDA que nos permite almacenar tanto los datos de una receta como los valores nutricionales 
	  * de una receta, es decir, sus calorias, hidratos de carbono, grasas, etc...
	  * 
	  
	  * @section faReceta Resumen Atributos Receta
	  * 
	  * - @c Nombre del Alimento 			(string)
	  * - @c Calorias			 			(float)
	  *
	  * - @c Nutrientes:
	  * 		- @c Hidratos de Carbono	(float)
	  * 		- @c Grasas					(float)
	  * 		- @c Proteinas				(float)
	  * 		- @c Fibra					(float)
	  *
	  * - @c Codigo 						(string)
	  * - @c Plato 							(UNSIGNED INT)
	  * - @c Listado de Ingredientes		(list< pair <string,unsigned int> >)
	  *
	  *
	  * @section faRecetaMetodos Principales metodos y sobrecargas :
	  *
	  * - @c Tanto gets como sets
	  *
	  * - @c operator >> ( capaz de leer una receta completo )
	  * - @c operator << ( nos permite escribir los valores de una receta al completo )
	  * 
	  */

    //el codigo de la receta
    string code;

    //(1, 2 o 3 ) segun el numero de plato que sea
    unsigned int plato;

    //nombre de la receta
    string nombre;

    //una lista (secuencia) de parejas, nombre ingrediente y cantidad
    //platano, 100gr por ejemplo
    list< pair <string,unsigned int> > ings;

    //instrucciones de la receta
    Instrucciones inst;
    
    //iterador de la lista de ingredientes.

    //valores nutricionales de la receta, segun sus ingredientes y cantidades
    float calorias = 0.0,hc = 0.0, grasas = 0.0, 
          proteinas = 0.0, fibra = 0.0;
    //float calorias, hc, grasas, proteinas, fibra;

public:
    //metodos acceso a los atributos:
//////////////////////////////////////////////////////////////////
/////////////////////////METODOS/////////////////////////////////
//////////////////////////////////////////////////////////////////

    /**
	  * @brief metodo que devuelve el numero de ingredientes que tiene una receta
	  * @return (int) Devuelve el numero de ingredientes que contiene el vector ings
	*/
    int ningredientes();

    /**
	 * @brief Metodo que añade los valores grasas, calorias, proteinas, hidratos de carbono
	 *  y fibra con los gramos especificados de cada ingrediente
	 * @param i (recibe un ingrediente)
	 * @param gr (recibe los gramos a los que se le aplicara el calculo)
	*/
    void addValoresIng(Ingrediente i,int gr);
    /**
	 * @brief Metodo que imprime los nutrientes que tiene la receta en total, calorias, hidratos de 
	 * carbono, grasas, proteinas y fibra.
	*/
    void ImprimeReNutrientes();

     /**
	 * @brief Metodo que imprime los ingredientes que tiene la receta con sus cantidades en gr.
	*/
    void ImprimeReIngredientes();
    /**
	 * @brief Metodo que calcula el ratio proteinas/(hidratos de carbono) o (hidratos de carbono)/proteinas
	 * @note
	 *   dependiendo de la division devuelve uno o u otro
	 * @return float (si proteinas/(hidratos de carbono) > (hidratos de carbono)/proteinas
	 * devuelve proteinas/(hidratos de carbono), en caso contrario (hidratos de carbono)/proteinas
	*/
    float CalcRatio();

    /**
	 * @brief Metodo que fusiona 2 recetas
	 * @param r1 (receta)
	 * @param r2 (receta)
	 * @return bool (si se ha fusionado bien o no)
	*/
	bool fusion(receta r1, receta r2,Ingredientes ingredientes); 

    /**
	 * @brief Metodo que combina 2 listas de ingredientes
	 * @param ings2 (list< pair <string,unsigned int> >) se combinara con la del this
	*/
    void combinaIngredientes(receta r2);

    /**
	 * @brief Metodo que añade las instrucciones
	 * @param archivo donde obtener las instrucciones
	*/
    void addInstrucciones(string archivo);
    
//////////////////////////////////////////////////////////////////
///////////////////GETS y SET ATRIBUTOS///////////////////////////
//////////////////////////////////////////////////////////////////

    /**
	  * @brief Metodo que devuelve codigo de la receta
	  * @return string (codigo de la receta)
	*/
	string getCode();
	
	/**
	  * @brief Metodo que devuelve el numero de plato
	  * @return unsigned int (nº de plato)
	*/
	unsigned int getPlato();
	
	/**
	  * @brief Metodo que devuelve el nombre de la receta
	  * @return string (nombre de la receta)
	*/
	string getNombre();

	/**
	 * @brief Metodo que modifica el nombre de la receta
	 * @param nom (Nombre de la nueva receta)
	*/
	void setNombre(string nom);
    
    
//////////////////////////////////////////////////////////////////
///////////////////GETS y SET de ingredientes///////////////
//////////////////////////////////////////////////////////////////

	/**
	  * @brief Metodo que devuelve los ingredientes que tiene la receta
	  * @return list<pair <string, unsigned int>> (lista de ingredientes)
	*/
	list< pair <string,unsigned int> > getIngredientes();

	/**
	  * @brief Metodo que devuelve las instrucciones que tiene la receta
	  * @return Instrucciones
	*/
	Instrucciones getInstrucciones(){return inst;}



//////////////////////////////////////////////////////////////////
///////////////////GETS y SET valores nutricionales///////////////
//////////////////////////////////////////////////////////////////

	//------------------GETS

	/**
	  * @brief Metodo que devuelve las calorias que tiene la receta
	  * @return float(calorias de la receta)
	*/
	float getCals();

	/**
	  * @brief Metodo que devuelve los hidratos de carbono que tiene la receta
	  * @return float(hidratos de carbono de la receta)
	*/
	float getHC();

	/**
	  * @brief Metodo que devuelve las grasas que tiene la receta
	  * @return float(grasas de la receta)
	*/
	float getGrasas();

	/**
	  * @brief Metodo que devuelve las proteinas que tiene la receta
	  * @return float(proteinas de la receta)
	*/
	float getProtes();

	/**
	  * @brief Metodo que devuelve la fibra que tiene la receta
	  * @return float(fibra de la receta)
	*/
	float getFibra();
	


	/**
	  * @brief Metodo constante que devuelve las calorias que tiene la receta
	  * @return float(calorias de la receta)
	*/
	float getCals() const;
	/**
	  * @brief Metodo constante que devuelve las calorias que tiene la receta
	  * @return float(calorias de la receta)
	*/
	float getHC() const;
	/**
	  * @brief Metodo constante que devuelve las grasas que tiene la receta
	  * @return float(grasas de la receta)
	*/
	float getGrasas() const;
	/**
	  * @brief Metodo constante que devuelve las proteinas que tiene la receta
	  * @return float(proteinas de la receta)
	*/
	float getProtes() const;
	/**
	  * @brief Metodo constante que devuelve la fibra que tiene la receta
	  * @return float(fibra de la receta)
	*/
	float getFibra() const;


	//-------------------SETS

	/**
	 * @brief Metodo que modifica las calorias de una receta
	 * @param cals (calorias)
	*/
	void setCals(float cals);
	/**
	 * @brief Metodo que modifica los hidratos de carbono de una receta
	 * @param hcs (hidratos de carbono)
	*/
	void setHC(float hcs);
	/**
	 * @brief Metodo que modifica las proteinas de una receta
	 * @param protes (proteinas)
	*/
	void setProtes(float protes);
	/**
	 * @brief Metodo que modifica las grasas de una receta
	 * @param gras (grasas)
	*/
	void setGrasas(float gras);
	/**
	 * @brief Metodo que modifica la fibra de una receta
	 * @param fib (fibra)
	*/
	void setFibra(float fib);
	   
///////////////////////////////////////////////////////////////////
//------------------------CLASES ITERADOR------------------------//
///////////////////////////////////////////////////////////////////

	/** @page Iteradores
	  * @section Iterador 
	  * que realiza las operaciones de incrementar, decrementar, comparar si son iguales o no
	  * sustituir, consultar y añadir en la receta
	  */
    class iterador{
      private:
        list< pair <string, unsigned int> >::iterator it;

      public:

      	/**
		  * @brief Constructor por defecto
		*/
        iterador(): it(0){}
        
        /**
		  * @brief Constructor que recibe por parametro un iterador
		  * @param ittr (iterador a sustituir)
		  * @note
		  *   Este es el constructor de copia
		*/
        iterador(const iterador& ittr): it(ittr.it){}
        
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
			it = orig.it;
			return *this;
		}
		
		/**
		  * @brief Operador *
		  * @return (Este devuelve un listado de ingredientes del iterador)
		*/
		pair<string, unsigned int>& operator*() const{
			return *it;
		}
		
		/**
		  * @brief Operador ++
		  * @note
		  *   Este avanza hacia la derecha el contenido del iterador
		  * @return iterador+1 (el siguiente iterador)
		*/
		iterador& operator++(){
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
			it--;
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
        bool operator!=(const iterador& ittr) const{ return it != ittr.it; }
         
         /**
		  * @brief Operador ==
		  * @param v (iterador a comparar)
		  * @note
		  *   Este es el constructor que compara el iterador al que llama al operador con
		  *   el que recibe por parametro, si son iguales true y si no false.
		  * @return true si son iguales, false en caso contrario
		*/
         bool operator==(const iterador& v) const{ return it == v.it; }
    	 
    	 friend class receta;
    };

///////////////////////////////////////////////////////////////////
//----------------------CLASES CONST_ITERADOR--------------------//
///////////////////////////////////////////////////////////////////

    class const_iterador{
      private:
        list< pair<string, unsigned int > >:: const_iterator it;

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
        const_iterador(const const_iterador& ittr): it(ittr.it){}

        /**
		  * @brief Constructor que recibe por parametro un iterador
		  * @param ittr (iterador a sustituir)
		  * @note
		  *   Este es el constructor de copia
		*/
        const_iterador(const iterador& ittr): it(ittr.it){}
        
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
			it = orig.it;
			return *this;
		}
		
		/**
		  * @brief Operador *
		  * @note
		  *   Este devuelve los ingredientes de la receta del iterador
		  * @return (Este devuelve los ingredientes de la receta del iterador)
		*/
		const pair<string, unsigned int>& operator*() const{
			return *it;
		}
		
		/**
		  * @brief Operador ++
		  * @note
		  *   Este avanza hacia la derecha el contenido del iterador
		  * @return iterador+1 (el siguiente iterador)
		*/
		const_iterador& operator++(){
			it++;
			return *this;
		}
		
		/**
		  * @brief Operador --
		  * @note
		  *   Desplaza hacia la izquierda el iterador
		  * @return iterador-1 (el anterior iterador)
		*/
		const_iterador& operator--(){
			it--;
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
        bool operator!=(const iterador& ittr) const{ return it != ittr.it; }
         
         /**
		  * @brief Operador ==
		  * @param v (iterador a comparar)
		  * @note
		  *   Este es el constructor que compara el iterador al que llama al operador con
		  *   el que recibe por parametro, si son iguales true y si no false.
		  * @return true si son iguales, false en caso contrario
		*/
         bool operator==(const iterador& v) const { return it == v.it; }
      
      friend class receta;
    };
    
    //AL MISMO NIVEL QUE LA CLASE!!!!!!!!!!!
    //porq son metodos que devuelven un iterador (de tu clase iterador)
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
     	
     	//en el atributo iterator it, le asignamos el begin
     	ittr.it = ings.begin();
     	
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
	 	ittr.it = ings.end();
	 	return ittr;
	}

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
     	
     	//en el atributo iterator it, le asignamos el begin
     	ittr.it = ings.begin();
     	
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
	 	ittr.it = ings.end();
	 	return ittr;
	}


///////////////////////////////////////////////////////////////////
//------------------------OPERATORS------------------------//
///////////////////////////////////////////////////////////////////

  /**
	* @brief Operador (>>)
	* @param is (Buffer de entrada)
  * @param re (Objeto Receta donde se guardara los datos del buffer)
	* @note
	*   lee el archivo y guarda los datos cada uno en su variable
	*/
	friend istream& operator>> (istream& is, receta& re);
	
	/**
	  * @brief Operador (<<)
	  * @param os (Buffer de salida que contendra la info de la receta)
  	  * @param re (Objeto Receta donde contiene los valores (grasas, hidratos de carbono, fibra, ...)
  	  * a devolver en el buffer)
	  * @note
	  *   lee el objeto y lo pasa al buffer
	*/
	friend ostream& operator<< (ostream& os, receta& re);
	
};

#endif
