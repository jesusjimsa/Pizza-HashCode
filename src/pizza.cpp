#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cmath>

using namespace std;

class Pizza {
private:
	vector< vector<char> > pizza;
	unsigned nfilas;
	unsigned ncolumnas;
	unsigned min_ingr;
	unsigned max_slice;

	// Una forma es una estructura auxiliar que solo tiene
	// sentido dentro del contexto de la clase.
	struct Forma{
		Coordenada inicio;
		unsigned int fil;
		unsigned int cols;
	};

	typedef pair<unsigned int, unsigned int> Coordenada;

public:
	// Constructor desde archivo.
	Pizza( string filename ){
		ifstream in_file;
		string line;
		vector<char> aux;

		in_file.open(filename);

		if(!in_file){
			cerr << "Error while opening file" << endl;
			return 0;
		}

		in_file >> nfilas;
		in_file >> ncolumnas;
		in_file >> min_ingr;
		in_file >> max_slice;

		//char pizza[nfilas][ncolumnas];

		getline(in_file, line);

		while(getline(in_file, line)){
			for(unsigned int i = 0; i < line.length(); i++){
				if(line[i] == 'M' || line[i] == 'T'){
					aux.push_back(line[i]);
				}
			}

			pizza.push_back(aux);
			aux.clear();
		}

		in_file.close();
	}

	// Comprueba si una forma es enclausulable.
	bool compruebaForma(Forma forma){
		bool forma_valida = true;
		int num_champi = 0,
		num_tomate = 0; 
		unsigned int x, y, tope_x, tope_y;

		x = forma.inicio.first;
		y = forma.inicio.second;

		tope_x = forma.inicio.first + forma.cols;
		tope_y = forma.inicio.second + forma.fil;

		// Comprobación inicial por si accedemos a una dirección no permitida
		if( tope_x > ncolumas || tope_y > nfilas ){
			forma_valida = false;
		}
		else{
			while(x < tope_x){

				while(y < tope_y){
					if( pizza[x][y] == 'M' )
						num_champi++;
					else if(pizza[x][y] == 'T')
						num_tomate++;

					y++;
				}

				x++;
			}

			if( num_champi < min_ingr || num_tomate < min_ingr ){
				forma_valida = false;
			}
		}

		return forma_valida;
	}

	// Determina donde seguir recorriendo la pizza.
	Coordenada siguienteInicio(vector<vector<char>> pizza_copia){
		int i, j;
		encontrado = false;
		Coordenada coords(0, 0);

		for(j = 0; !encontrado && j < nfil; j++ ){
			for(i = 0; !encontrado && i < ncol; i++){
				if( pizza_copia[i][j] != 'X'){
					encontrado = true;
					coords.first = i;
					coords.second = j;
				}
			}
		}

		return coords;
	}

	// Comprueba si alguna de las n formas posibles es enclausulable.
	Forma comprobarFormas( Coordenada inicio ) {

		vector<unsigned> divisores;

		// Calculamos los divisores del número.
		int raiz = (int) sqrt( max_slice );
	    if ( max_slice != 1 )
	    {
		    for ( unsigned i = 1; i < raiz; i++ ) 
		    {
		        if ( max_slice % i == 0 ) {
		        	divisores.push_back( i );
		        }
		    }
	    }
	    else
	    	divisores.push_back( 1 );

		// El se divide a si mismo, lo añadimos como divisor.
	    divisores.push_back( max_slice );

	    // Comprobamos todas las formas posibles.
		for ( unsigned i = 0; i < divisores; i++ )
		{
			Forma forma;
			auto iter = divisores.end();
			iter--;

			forma.inicio = inicio;
			forma.fil = *iter;
			forma.cols = divisores[i];
			encapsulado = true;

			if ( compruebaForma( forma ) )
				return forma;
		}

		// Si ninguna a cumplido con las condiciones,
		// sale del bucle y devolvemos una forma inclausulable.
		forma.inicio = inicio;
		forma.fil  = 1;
		forma.cols = 1;
		encapsulado = false;

		return forma;
	}

	// En construccion.
	/*string cortaPizza() {

		stack<forma> pila, cool_pila;
		int nerrores, min_nerrores;
		int x, y;

		while ( x < nfilas )
		{
			while ( y < ncolumnas )
			{
				Forma forma;


			}
		}
	}*/
};

int main(int argc, char *argv[]){
	if(argc != 2){
		cerr << "The program needs two arguments: ./pizza <input file>" << endl;
		return 0;
	}
	else{
		Pizza pizza(argv[1]);
		ofstream output;
		string cortada;

		/*output.open("output.txt");
		if(){
			cerr << "Error while creating the output file" << endl;
			return 0;
		}*/
		try {
		    output.open ("output.txt");
		}
	 	catch ( const ifstream::failure& e ) {
	    	cerr << "Exception creating the output file.";
	    	return 0;
	  	}

		cortada = pizza.cortaPizza();
		output << cortada;

		output.close();
	}
}
