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
		queue<Paciente> temp = p;
		temp.pop();
		mostrarPaciente(temp.front());
	}
	else {
		cout << "No hay paciente siguiente al primero de la cola.\n";
	}
}

void mostrarCola(queue<Paciente>& p) {
	queue<Paciente> temp = p; //cola temporal que se usará para mostrar cada paciente
	while (!temp.empty()) {
		Paciente m = temp.front();
		mostrarPaciente(m);
		temp.pop();
	}
}

void infoPaciente(queue<Paciente> &p, int posicion) {
	queue<Paciente> temp = p; //cola temporal
	int i = 1;
	bool encontrado = false;

	if (posicion < 1 || posicion >= p.size()+1) {
		cout << "Posicion no valida." << endl;
		return;
	}

	while (!temp.empty()) {
		Paciente actual = temp.front();
		temp.pop();

		if (i == posicion) {
			mostrarPaciente(actual);
			encontrado = true;
			break;
		}
		i++;
	}

	if (!encontrado) {
		cout << "Paciente en la posicion " << posicion << " no encontrado." << endl;
	}
}

void atenderPaciente(queue<Paciente> &p) {
	if (!p.empty()) {
		Paciente siguiente = p.front();
		cout << "Atendiendo siguiente paciente:\n";
		mostrarPaciente(siguiente);
		//se suma el costo al saldo y se elimina al paciente
		saldo += siguiente.costo;
		p.pop();
	}
	else {
		cout << "No hay pacientes en la cola para atender." << endl;
	}
}

void eliminarPaciente(queue<Paciente>& p, int posicion) {
	queue<Paciente> temp; //cola temporal para almacenar los elementos restantes
	int i = 1;
	bool encontrado = false;

	if (posicion < 1 || posicion >= p.size()+1) { //verificar que la posición es válida
		cout << "Posición no válida." << endl;
		return;
	}

	while (!p.empty()) { //recorremos la cola original
		Paciente actual = p.front();
		p.pop();

		if (i == posicion) {
			encontrado = true;
			cout << "Paciente en la posición " << posicion << " eliminado de la cola." << endl; //no se agrega a la cola temporal
		}
		else {
			temp.push(actual); //si no es el elemento, lo añadimos a la cola temporal
		}
		i++;
	}

	if (!encontrado) {
		cout << "Paciente en la posición " << posicion << " no encontrado en la cola." << endl;
	}

	p = temp; // Reemplazamos la cola original por la cola temporal
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
		cout << "4. Mostrar la cola entera de pacientes.\n";
		cout << "5. Buscar paciente por posicion en cola.\n";
		cout << "6. Eliminar paciente por posicion en cola.\n";
		cout << "7. Consultar saldo.\n";
		cout << "8. Salir.\n\n";
		cout << "Opcion (1-8): ";
		cin >> op;
		switch (op) {
		case 1:
			ingresarDatos(cola);
			break;
		case 2:
			atenderPaciente(cola);
			cout << "Oprima una tecla para continuar...\n";
			cin.ignore(); // Limpiar el buffer de entrada
			cin.get();    // Esperar a que el usuario presione una tecla
			break;
		case 3:
			mostrarSiguiente(cola);
			cout << "Oprima una tecla para continuar...\n";
			cin.ignore();
			cin.get();
			break;
		case 4:
			mostrarCola(cola);
			cout << "Oprima una tecla para continuar...\n";
			cin.ignore();
			cin.get();
			break;
		case 5:
			int posicionInfo;
			cout << "Ingrese la posicion del paciente a buscar: ";
			cin >> posicionInfo;
			infoPaciente(cola, posicionInfo);
			cout << "Oprima una tecla para continuar...\n";
			cin.ignore();
			cin.get();
			break;
		case 6:
			int posElim;
			cout << "Ingrese la posicion del paciente a eliminar: ";
			cin >> posElim;
			eliminarPaciente(cola, posElim);
			cout << "Oprima una tecla para continuar...\n";
			cin.ignore();
			cin.get();
			break;
		case 7:
			cout << "Saldo total: " << saldo << endl;
			cout << "Oprima una tecla para continuar...\n";
			cin.ignore();
			cin.get();
			break;
		}
	}
	while (op!=8);
	return 0;
}
