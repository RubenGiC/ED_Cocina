###########################################################################################
# File: Makefile
# Builds: Programa Practica 2 E.D.
#
# Version: 0.0
# Author: Medina Romero Jorge & Girela Castellón Ruben
############################################################################################

HOMEDIR = .
BIN = $(HOMEDIR)/bin
SRC = $(HOMEDIR)/src
OBJ = $(HOMEDIR)/obj
INCLUDE = $(HOMEDIR)/include
LIB = $(HOMEDIR)/lib
DOC = $(HOMEDIR)/doc
CXX = g++

#............................................................

all : intro $(BIN)/test_ingredientes \
			$(BIN)/tipos_ingredientes \
			$(BIN)/test_receta \
			$(BIN)/nutricion_receta \
			$(BIN)/cocinero_integral \
			documentacion
	  
	@echo Done!
#$(BIN)/cocinero_integral \
#..........................EJECUTABLES...........................

#..........................test_ingredientes...................................

$(BIN)/test_ingredientes : $(OBJ)/ingrediente.o $(OBJ)/ingredientes.o \
							$(OBJ)/test_ingredientes.o
	$(CXX) $^ -o $@ 
	@echo Linking...

#..........................tipos_ingredientes...................................

$(BIN)/tipos_ingredientes : $(OBJ)/ingrediente.o $(OBJ)/ingredientes.o \
							$(OBJ)/tipos_ingredientes.o
	$(CXX) $^ -o $@ 
	@echo Linking...

#..........................test_receta...................................
	
$(BIN)/test_receta : $(OBJ)/ingrediente.o $(OBJ)/ingredientes.o \
						  $(OBJ)/receta.o $(OBJ)/recetas.o \
						  $(OBJ)/acciones.o $(OBJ)/instrucciones.o $(OBJ)/test_receta.o
	$(CXX) $^ -o $@ 
	@echo Linking...

#..........................nutricion_receta.................................

$(BIN)/nutricion_receta : $(OBJ)/receta.o $(OBJ)/recetas.o \
						  $(OBJ)/ingrediente.o $(OBJ)/ingredientes.o \
						  $(OBJ)/acciones.o $(OBJ)/instrucciones.o $(OBJ)/nutricion_receta.o
	$(CXX) $^ -o $@ 
	@echo Linking...

#..........................cocinero_integral.................................

$(BIN)/cocinero_integral:  $(OBJ)/receta.o $(OBJ)/recetas.o \
							$(OBJ)/ingrediente.o $(OBJ)/ingredientes.o \
							$(OBJ)/acciones.o $(OBJ)/instrucciones.o $(OBJ)/cocinero_integral.o
	$(CXX) $^ -o $@ 
	#$(CXX) -o $(BIN)/cocinero_integral	$(OBJ)/cocinero_integral.o  $(OBJ)/receta.o $(OBJ)/recetas.o $(OBJ)/ingrediente.o $(OBJ)/ingredientes.o $(OBJ)/acciones.o
	@echo Linking...

#..........................OBJETOS...........................

#..........................VD...........................

#$(OBJ)/VD.o : $(SRC)/VD.cpp $(INCLUDE)/VD.h
#	@g++ -c $< -o $@ -I $(INCLUDE) -std=c++11
#	@echo Compiling...
#..........................ingrediente...........................

$(OBJ)/ingrediente.o : $(SRC)/ingrediente.cpp $(INCLUDE)/ingrediente.h
	$(CXX) -c $< -o $@ -I $(INCLUDE) -std=c++11
	@echo Compiling...

#..........................ingredientes...........................

$(OBJ)/ingredientes.o : $(SRC)/ingredientes.cpp $(INCLUDE)/ingredientes.h \
						$(INCLUDE)/ingrediente.h 
						

	$(CXX) -c $< -o $@ -I $(INCLUDE) -std=c++11
	@echo Compiling...

#..........................test_ingredientes...........................

$(OBJ)/test_ingredientes.o : $(SRC)/test_ingredientes.cpp $(INCLUDE)/ingrediente.h \
							$(INCLUDE)/ingredientes.h
	$(CXX) -c $< -o $@ -I $(INCLUDE) -std=c++11
	@echo Compiling...

$(OBJ)/tipos_ingredientes.o : $(SRC)/tipos_ingredientes.cpp $(INCLUDE)/ingrediente.h \
							$(INCLUDE)/ingredientes.h
	$(CXX) -c $< -o $@ -I $(INCLUDE) -std=c++11
	@echo Compiling...
	
#..........................receta...........................

$(OBJ)/receta.o : $(SRC)/receta.cpp $(INCLUDE)/receta.h \
				  $(INCLUDE)/ingrediente.h $(INCLUDE)/instrucciones.h
	$(CXX) -c $< -o $@ -I $(INCLUDE) -std=c++11
	@echo Compiling...
	
#..........................recetas...........................

$(OBJ)/recetas.o : $(SRC)/recetas.cpp $(INCLUDE)/receta.h $(INCLUDE)/ingredientes.h $(INCLUDE)/instrucciones.h
	$(CXX) -c $< -o $@ -I $(INCLUDE) -std=c++11
	@echo Compiling...

#..........................acciones...........................
$(OBJ)/acciones.o: $(SRC)/acciones.cpp $(INCLUDE)/acciones.h
	$(CXX) -c $< -o $@ -I $(INCLUDE) -std=c++11
	@echo Compiling...

#..........................Instrucciones...........................
$(OBJ)/instrucciones.o: $(SRC)/instrucciones.cpp $(INCLUDE)/instrucciones.h \
					$(INCLUDE)/acciones.h $(INCLUDE)/arbolbinario.h
	$(CXX) -c $< -o $@ -I $(INCLUDE) -std=c++11
	@echo Compiling...

#..........................test_receta...........................
$(OBJ)/test_receta.o : $(SRC)/test_receta.cpp \
					$(INCLUDE)/ingrediente.h $(INCLUDE)/ingredientes.h \
					$(INCLUDE)/receta.h $(INCLUDE)/recetas.h \
					$(INCLUDE)/acciones.h $(INCLUDE)/instrucciones.h
	$(CXX) -c $< -o $@ -I $(INCLUDE) -std=c++11
	@echo Compiling...

#..........................nutricion_receta...........................

$(OBJ)/nutricion_receta.o : $(SRC)/nutricion_receta.cpp \
					$(INCLUDE)/receta.h $(INCLUDE)/recetas.h \
					$(INCLUDE)/ingrediente.h $(INCLUDE)/ingredientes.h \
					$(INCLUDE)/acciones.h $(INCLUDE)/instrucciones.h
	$(CXX) -c $< -o $@ -I $(INCLUDE) -std=c++11
	@echo Compiling...

#..........................cocinero_integral...........................
$(OBJ)/cocinero_integral.o: $(SRC)/cocinero_integral.cpp \
					$(INCLUDE)/receta.h $(INCLUDE)/recetas.h \
					$(INCLUDE)/ingrediente.h $(INCLUDE)/ingredientes.h \
					$(INCLUDE)/acciones.h $(INCLUDE)/instrucciones.h
	$(CXX) -c $< -o $@ -I $(INCLUDE) -std=c++11
	@echo Compiling...


#....................Generación de documentación ...............

#para ver el html, vete a la carpeta del html y pincha en el index.html
documentacion:
	doxygen $(DOC)/doxys/Doxyfile
	@echo Generating documentation...

#...........................Limpieza............................................

clean :
	@echo Deleting object files...
	@-rm $(OBJ)/*.o
clean_doxy :
	@echo Deleting doxy html...
	@-rm $(DOC)/html/*

mr.proper : clean clean_doxy
	@echo Deleting bin folder...
	@-rm $(BIN)/*
	@echo Done!

#clean_library :
#	@echo Deleting the library...
#	-rm $(LIB)/*.a

#...............................................................................

intro :
	@echo Reading files...
