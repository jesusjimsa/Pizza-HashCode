principal:
	g++ src/pizza.cpp -o pizza -g -O1 -Wall -Iinclude -std=c++11
	@ echo ">> Compilación terminada."

clean: 
	rm bin/pizza
	@	echo ">> Datos de compilación borrados."	