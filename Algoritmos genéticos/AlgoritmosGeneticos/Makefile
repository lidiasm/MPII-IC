####### MACROS PARA LOS DIRECTORIOS, LIBRERÍAS Y COMPILADOR
AR = ar
CXX = g++ -O3 -g -std=gnu++11 -Wall -W -fPIC
QAP = ./qap
BIN = ./bin
LIB = ./lib
LDFLAGS = -L$(LIB)
LDLIBS = -lAlgoritmos

all: $(BIN)/qap

####### COMPILACIÓN DE LOS DISTINTOS MÓDULOS
$(BIN)/datosfichero.o : $(QAP)/datosfichero.h $(QAP)/datosfichero.cpp
	$(CXX) -c -o $(BIN)/datosfichero.o $(QAP)/datosfichero.cpp

$(BIN)/cromosoma.o : $(QAP)/cromosoma.h $(QAP)/cromosoma.cpp
	$(CXX) -c -o $(BIN)/cromosoma.o $(QAP)/cromosoma.cpp

###### COMPILACIÓN DE LOS OBJETOS DE LOS MÓDULOS ANTERIORES
$(BIN)/practica2.o : $(QAP)/datosfichero.h $(QAP)/cromosoma.h
	$(CXX) -c -o $(BIN)/practica2.o $(QAP)/main.cpp

###### COMPILACIÓN Y GENERACIÓN DEL EJECUTABLE FINAL
$(BIN)/qap : $(BIN)/practica2.o $(LIB)/libAlgoritmos.a
	$(CXX) -o $(BIN)/qap $(BIN)/practica2.o $(LDFLAGS) $(LDLIBS)

###### LIBRERÍAS
$(LIB)/libAlgoritmos.a : $(BIN)/datosfichero.o $(BIN)/cromosoma.o
	$(AR) rvs $(LIB)/libAlgoritmos.a $(BIN)/datosfichero.o $(BIN)/cromosoma.o

clean:
	-rm $(BIN)/*.o
	echo "Objetos eliminados."