#include <iostream>
#include <queue>
#include <list>

class Paciente {
public:
	std::string nombre;
	int edad;
	std::string padecimiento;
	float costo;
};

void ingresarDatos(std::queue<Paciente> &cola) {
	Paciente p;
	std::cout << "Ingrese los datos del paciente:\n";
	std::cout << "Nombre: ";
	std::cin >> p.nombre;
	std::cout << "Edad: ";
	std::cin >> p.edad;
	std::cout << "Padecimiento: ";
	std::cin >> p.padecimiento;
	std::cout << "Costo: ";
	std::cin >> p.costo;
	cola.push(p);
}

void mostrarPaciente(Paciente &p) {
	std::cout << "Nombre: " << p.nombre << ", Edad: " << p.edad << ", Padecimiento: " << p.padecimiento << ", Costo: " << p.costo << std::endl;
}

void mostrarSiguiente(std::queue<Paciente> &p) { 
	if (p.size() > 1) { 
		std::queue<Paciente> temp = p;
		temp.pop(); 
		mostrarPaciente(temp.front());
	}
	else {
		std::cout << "No hay paciente siguiente al primero de la cola.\n";
	}
}

void mostrarCola(std::queue<Paciente> &p) {
	std::queue<Paciente> temp = p;
	if (p.empty()) {
		std::cout << "La cola esta vacia.\n";
	}
	while (!temp.empty()) {
		Paciente m = temp.front();
		mostrarPaciente(m);
		temp.pop();
	}
}

void infoPaciente(std::queue<Paciente> &p, int posicion) {
	std::queue<Paciente> temp = p;
	int i = 1;
	bool encontrado = false;
	
	if (posicion < 1 || posicion >= p.size()+1) {
		std::cout << "Posicion no valida." << std::endl;
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
		std::cout << "Paciente en la posicion " << posicion << " no encontrado." << std::endl;
	}
}

void atenderPaciente(std::queue<Paciente> &p, std::list<Paciente> &historial, float &saldo) {
	if (!p.empty()) {
		Paciente siguiente = p.front();
		std::cout << "Atendiendo siguiente paciente:\n";
		mostrarPaciente(siguiente);
		saldo += siguiente.costo;
		historial.push_back(siguiente);
		p.pop();
	}
	else {
		std::cout << "No hay pacientes en la cola para atender." << std::endl;
	}
}

void eliminarPaciente(std::queue<Paciente> &p, int posicion) {
	std::queue<Paciente> temp;
	int i = 1;
	bool encontrado = false;
	
	if (posicion < 1 || posicion >= p.size()+1) {
		std::cout << "Posicion no valida." << std::endl;
		return;
	}
	
	while (!p.empty()) {
		Paciente actual = p.front();
		p.pop();
		
		if (i == posicion) {
			encontrado = true;
			std::cout << "Paciente en la posicion " << posicion << " eliminado de la cola." << std::endl;
		}
		else {
			temp.push(actual);
		}
		i++;
	}
	
	if (!encontrado) {
		std::cout << "Paciente en la posicion " << posicion << " no encontrado en la cola." << std::endl;
	}
	
	p = temp;
}

void mostrarHistorial(std::list<Paciente> &historial) {
	if (historial.empty()) {
		std::cout << "Historial vacio." << std::endl;
	}
	else {
		for (Paciente &p : historial) {
			mostrarPaciente(p);
		}
	}
}

int main() {
	std::queue<Paciente> cola;
	float saldo = 0;
	std::list<Paciente> historial;
	int op;
	
	do {
		system("cls");
		std::cout << "+++ Consultorio +++\n\n";
		std::cout << "Seleccione una opcion:\n";
		std::cout << "1. Registrar paciente.\n";
		std::cout << "2. Atender paciente.\n";
		std::cout << "3. Consultar proximo paciente.\n";
		std::cout << "4. Mostrar la cola entera de pacientes.\n";
		std::cout << "5. Buscar paciente por posicion en cola.\n";
		std::cout << "6. Eliminar paciente por posicion en cola.\n";
		std::cout << "7. Consultar saldo.\n";
		std::cout << "8. Consultar historial de atencion.\n";
		std::cout << "9. Salir.\n\n";
		std::cout << "Opcion (1-9): ";
		std::cin >> op;
		
		switch (op) {
		case 1:
			ingresarDatos(cola);
			break;
		case 2:
			atenderPaciente(cola, historial, saldo);
			std::cout << "Oprima una tecla para continuar...\n";
			std::cin.ignore();
			std::cin.get();
			break;
		case 3:
			mostrarSiguiente(cola);
			std::cout << "Oprima una tecla para continuar...\n";
			std::cin.ignore();
			std::cin.get();
			break;
		case 4:
			mostrarCola(cola);
			std::cout << "Oprima una tecla para continuar...\n";
			std::cin.ignore();
			std::cin.get();
			break;
		case 5:
			int posicion;
			std::cout << "Ingrese la posicion del paciente a buscar: ";
			std::cin >> posicion;
			infoPaciente(cola, posicion);
			std::cout << "Oprima una tecla para continuar...\n";
			std::cin.ignore();
			std::cin.get();
			break;
		case 6:
			int posElim;
			std::cout << "Ingrese la posicion del paciente a eliminar: ";
			std::cin >> posElim;
			eliminarPaciente(cola, posElim);
			std::cout << "Oprima una tecla para continuar...\n";
			std::cin.ignore();
			std::cin.get();
			break;
		case 7:
			std::cout << "Saldo total: " << saldo << std::endl;
			std::cout << "Oprima una tecla para continuar...\n";
			std::cin.ignore();
			std::cin.get();
			break;
		case 8:
			mostrarHistorial(historial);
			std::cout << "Oprima una tecla para continuar...\n";
			std::cin.ignore();
			std::cin.get();
			break;
		}
	} while (op != 9);
	
	return 0;
}
