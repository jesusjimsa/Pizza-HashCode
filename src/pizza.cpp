#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

typedef pair<unsigned int, unsigned int> Coordenada;

struct Forma{
	Coordenada inicio;
	unsigned int fil;
	unsigned int cols;
};

class Pizza{
private:
	vector< vector<char> > pizza;
	unsigned int nfilas, ncolumnas, min_ingr, max_slice;
public:
	Pizza(string filename){
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

		output.open("output.txt");
		if(){
			cerr << "Error while creating the output file" << endl;
			return 0;
		}

		cortada = pizza.cortaPizza();
		output << cortada;

		output.close();
	}
}
