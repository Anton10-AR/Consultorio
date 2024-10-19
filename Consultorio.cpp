#include <iostream>
#include <queue>
#include <list>
using namespace std;

class Paciente {
public:
	string nombre;
	int edad;
	string padecimiento;
	float costo;
};

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

void mostrarPaciente(Paciente &p) {
	cout << "Nombre: " << p.nombre << ", Edad: " << p.edad << ", Padecimiento: " << p.padecimiento << ", Costo: " << p.costo << endl;
}

void mostrarSiguiente(queue<Paciente> &p) { // Mostrar el siguiente paciente sin eliminar al primero
	if (p.size() > 1) { // Verificamos que en la cola haya mas de un paciente
		queue<Paciente> temp = p; // Cola temporal
		temp.pop(); // Eliminamos al primer paciente de la cola temporal
		mostrarPaciente(temp.front()); //Mostramos al paciente siguiente
	}
	else {
		cout << "No hay paciente siguiente al primero de la cola.\n";
	}
}

void mostrarCola(queue<Paciente> &p) {
	queue<Paciente> temp = p; // Cola temporal que se usara para mostrar cada paciente
	if (p.empty()) {
		cout << "La cola esta vacia.\n";
	}
	while (!temp.empty()) {
		Paciente m = temp.front(); // Variable de tipo Paciente que tomara el valor del primer elemento de la cola temporal
		mostrarPaciente(m); // Mostramos este paciente en cada ciclo
		temp.pop(); // Eliminamos este paciente de la cola temporal
	}
}

void infoPaciente(queue<Paciente> &p, int posicion) {
	queue<Paciente> temp = p; // Cola temporal
	int i = 1; // Iniciamos el contador en 1 y no en 0 por ser la manera natural de contar numeros (a partir del primero == 1)
	bool encontrado = false; // De mantenerse en "false", se mostrara un error "paciente no encontrado"

	if (posicion < 1 || posicion >= p.size()+1) { // Manera natural de contar numeros en contraposicion a como se cuenta en arrays (de 0 a .length()-1)
		cout << "Posicion no valida." << endl;
		return;
	}

	while (!temp.empty()) {
		Paciente actual = temp.front(); // Tomara el valor del primer elemento de la cola en cada ciclo
		temp.pop(); // Se elimina dicho elemento

		if (i == posicion) { // Si el parametro de posicion de infoPaciente() y el contador coinciden...
			mostrarPaciente(actual); // ...se muestra el elemento actual
			encontrado = true; // ...y cambiamos la booleana a True
			break;
		}
		i++;
	}

	if (!encontrado) {
		cout << "Paciente en la posicion " << posicion << " no encontrado." << endl;
	}
}

void atenderPaciente(queue<Paciente> &p, list<Paciente> &historial, float &saldo) {
	if (!p.empty()) {
		Paciente siguiente = p.front(); // Por "siguiente" se entiende el paciente actual en ser atendido, "siguiente pase"
		cout << "Atendiendo siguiente paciente:\n";
		mostrarPaciente(siguiente); // Paciente en ser atendido
		saldo += siguiente.costo; // Se suma el costo al saldo
		historial.push_back(siguiente); // Aniadimos sus datos al historial
		p.pop(); // Se elimina al paciente ya atendido
	}
	else {
		cout << "No hay pacientes en la cola para atender." << endl;
	}
}

void eliminarPaciente(queue<Paciente> &p, int posicion) {
	queue<Paciente> temp; // Cola temporal para almacenar los elementos restantes
	int i = 1;
	bool encontrado = false; // De mantenerse en "false", se mostrara un error "paciente no encontrado"

	if (posicion < 1 || posicion >= p.size()+1) { // verificar que la posicion es valida (manera natural de contar numeros)
		cout << "Posicion no valida." << endl;
		return;
	}

	while (!p.empty()) { // Recorremos la cola original
		Paciente actual = p.front(); // primer elemento de la cola temporal
		p.pop(); // Se elimina dicho elemento

		if (i == posicion) { // Si el parametro de posicion de eliminarPaciente() y el contador coinciden...
			encontrado = true;
			cout << "Paciente en la posicion " << posicion << " eliminado de la cola." << endl; // ...no se agrega a la cola temporal
		}
		else {
			temp.push(actual); // Si no coinciden, aniadimos el elemento a la cola temporal
		}
		i++;
	}

	if (!encontrado) {
		cout << "Paciente en la posicion " << posicion << " no encontrado en la cola." << endl;
	}

	p = temp; // Reemplazamos la cola original por la cola temporal (que no contendra el elemento eliminado, si se hubiese hallado)
}

void mostrarHistorial(list<Paciente> &historial) {
	if (historial.empty()) {
		cout << "Historial vacio." << endl;
	}
	else {
		for (Paciente &p : historial) { // contenedor = coleccion ordenada del mismo tipo de datos en la que cada elemento se almacena en una posicion especifica
			mostrarPaciente(p);
		}
	}
}

int main()
{
	queue<Paciente> cola;
	float saldo = 0;
	list<Paciente> historial;
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
		cout << "8. Consultar historial de atencion.\n";
		cout << "9. Salir.\n\n";
		cout << "Opcion (1-9): ";
		cin >> op;
		switch (op) {
		case 1:
			ingresarDatos(cola);
			break;
		case 2:
			atenderPaciente(cola, historial, saldo);
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
			int posicion;
			cout << "Ingrese la posicion del paciente a buscar: ";
			cin >> posicion;
			infoPaciente(cola, posicion);
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
		case 8:
			mostrarHistorial(historial);
			cout << "Oprima una tecla para continuar...\n";
			cin.ignore();
			cin.get();
			break;
		}
	}
	while (op!=9);
	return 0;
}
