#include <iostream>
#include <queue>
using namespace std;

struct Paciente {
	string nombre;
	int edad;
	string padecimiento;
	float costo;
};

float saldo = 0;

void ingresarDatos(queue<Paciente> &cola) {
	Paciente p;
	cout << "Ingrese los datos del paciente:\n";
	cout << "Nombre: ";
	cin >> p.nombre;
	cout << "Edad: ";
	cin >> p.edad;
	cout << "Padecimiento: ";
	cin >> p.padecimiento;
	cout << "Costo: ";
	cin >> p.costo;
	cola.push(p);
}

void mostrarPaciente(const Paciente &p) {
	cout << "Nombre: " << p.nombre << ", Edad: " << p.edad << ", Padecimiento: " << p.padecimiento << ", Costo: " << p.costo << endl;
}

void mostrarSiguiente(queue<Paciente> &p) { //mostrar el siguiente paciente sin eliminar al primero
	if (p.size() > 1) { //verificamos que en la cola haya más de un paciente
		queue<Paciente> copia = p;
		copia.pop();
		mostrarPaciente(copia.front());
	}
}

void infoPaciente(queue<Paciente> &p, int posicion) {
	queue<Paciente> temp; //cola temporal
	int i = 0;
	bool encontrado = false;

	while (!p.empty()) {
		Paciente actual = p.front();
		p.pop();

		if (i == posicion) {
			mostrarPaciente(actual);
			encontrado = true;
			break;
		}

		temp.push(actual);
		i++;
	}

	while (!temp.empty()) { //llenar la cola original con los elementos de la cola temporal
		p.push(temp.front());
		temp.pop();
	}

	if (!encontrado) {
		cout << "Paciente en la posición " << posicion << " no encontrado." << endl;
	}
}

void atenderPaciente(queue<Paciente>& cola) {
	if (!cola.empty()) {
		Paciente siguiente = cola.front();
		cout << "Atendiendo siguiente paciente:\n";
		mostrarPaciente(siguiente);
		//se suma el costo al saldo y se elimina al paciente
		saldo += siguiente.costo;
		cola.pop();
	}
	else {
		cout << "No hay pacientes en la cola para atender." << endl;
	}
}

void eliminarPaciente(queue<Paciente> &p, int posicion) {
	queue<Paciente> temp; // Cola temporal para almacenar los elementos restantes
	int i = 0;
	bool encontrado = false;
	
    while (!p.empty()) { // Recorremos la cola original
		Paciente actual = p.front();
		p.pop();
		
		if (i == posicion) { // Si el elemento es el que queremos eliminar, lo saltamos
			encontrado = true;
			cout << "Elemento " << posicion << " eliminado de la cola." << endl;
        }
        else {
			temp.push(actual); // Si no es el elemento, lo añadimos a la cola temporal
		}
		i++;
	}

    if (!encontrado) {
		cout << "Elemento " << posicion << " no encontrado en la cola." << endl;
    }
	
	p = temp; //reemplazamos la cola original por la cola temporal
}

int main()
{
	queue<Paciente> cola;
	int op;
	do {
		system("cls");
		cout << "+++ Consultorio +++\n\n";
		cout << "Seleccione una opcion:\n";
		cout << "1. Registrar paciente.\n";
		cout << "2. Atender paciente.\n";
		cout << "3. Consultar proximo paciente.\n";
		cout << "4. Buscar paciente por posicion en cola.\n";
		cout << "5. Eliminar paciente por posicion en cola.\n";
		cout << "6. Consultar saldo.\n";
		cout << "7. Salir.\n\n";
		cout << "Opcion (1-7): ";
		cin >> op;
		switch (op) {
		case 1:
			ingresarDatos(cola);
			break;
		case 2:
			atenderPaciente(cola);
			cout << "Oprima una tecla para salir.\n";
			getchar();
			break;
		case 3:
			mostrarSiguiente(cola);
			cout << "Oprima una tecla para salir.\n";
			getchar();
			break;
		case 4:
			int posicionInfo;
			cout << "Ingrese la posicion del paciente a buscar: ";
			cin >> posicionInfo;
			infoPaciente(cola, posicionInfo);
			break;
		case 5:
			int posElim;
			cout << "Ingrese la posicion del paciente a eliminar: ";
			cin >> posElim;
			eliminarPaciente(cola, posElim);
			break;
		case 6:
			cout << "Saldo total: " << saldo << endl;
			break;
		}
	}
	while (op!=7);
	return 0;
}
