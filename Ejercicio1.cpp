#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <cstring>
#include <errno.h>
#include <iomanip>
#include <string>
#include <sstream>
using namespace std;

#define C 7
#define N 30
#define A 15

struct Materia
{
	char codigo[C];
	char nombre[N];
	short int unidadesDeCredito;
};

char nombreArchivo[A] = "materias.dat";
char codigoMateriaConsultar[C];
char codigoMateriaModificar[C];
char codigoMateriaEliminar[C];

void crearArchivo(char nombreArchivo[A]);
void agregarMateria(Materia nuevaMateria);
void consultarMateria(char codigoMateriaConsultar[N]);
void modificarMateria(char codigoMateriaModificar[N]);
void listarMaterias();
void eliminarMateria(char codigoMateriaEliminar[N]);

int main()
{
	int opcion;

	do
	{
		do
		{
			system("cls");
			cout << "***** REGISTRO DE MATERIAS *****\n\n";
			cout << "1. Crear archivo vacio\n";
			cout << "2. Agregar materia\n";
			cout << "3. Consultar materia\n";
			cout << "4. Listar materias\n";
			cout << "5. Modificar materia\n";
			cout << "6. Eliminar materia\n";
			cout << "7. Salir\n";

			cout << "\n\nEscoja una de las siguientes opciones: ";
			fflush(stdin);
			cin >> opcion;

			if (opcion < 1 || opcion > 7)
			{
				system("cls");
				cout << "Opcion invalida\n\n";
				fflush(stdin);
				system("pause");
				system("cls");
			}
		} while (opcion < 1 || opcion > 7);

		if (opcion == 1)
		{

			cout << "Como desea llamar el archivo: ";
			fflush(stdin);
			cin.getline(nombreArchivo, 15);

			crearArchivo(nombreArchivo);

			system("pause");
		}
		else if (opcion == 2)
		{
			Materia nuevaMateria;

			cout << "Cual es el nombre de la nueva materia: ";
			fflush(stdin);
			cin.getline(nuevaMateria.nombre, N);

			cout << "Cual es el codigo de la materia: ";
			fflush(stdin);
			cin.getline(nuevaMateria.codigo, C);

			cout << "Cuantas unidades de credito: ";
			fflush(stdin);
			cin >> nuevaMateria.unidadesDeCredito;

			agregarMateria(nuevaMateria);
			system("pause");
		}
		else if (opcion == 3)
		{
			cout << "Escriba el codigo de la materia que desea consultar: ";
			fflush(stdin);
			cin.getline(codigoMateriaConsultar, C);

			consultarMateria(codigoMateriaConsultar);
		}
		else if (opcion == 4)
		{
			listarMaterias();
		}
		else if (opcion == 5)
		{
			cout << "Escriba el codigo de la materia que desea modificar: ";
			fflush(stdin);
			cin.getline(codigoMateriaModificar, C);

			modificarMateria(codigoMateriaModificar);
		}
		else if (opcion == 6)
		{
			cout << "Escriba el codigo de la materia que desea eliminar: ";
			fflush(stdin);
			cin.getline(codigoMateriaEliminar, C);
			eliminarMateria(codigoMateriaEliminar);
		}

	} while (opcion != 7);

	return EXIT_SUCCESS;
}

void crearArchivo(char nombreArchivo[A])
{
	ofstream archivo;
	archivo.open(nombreArchivo, ios::out | ios::binary); // Abren archivo

	if (archivo.fail())
	{
		cout << "No se pudo crear el archivo: " << strerror(errno);
		EXIT_FAILURE;
	}

	cout << "Archivo " << nombreArchivo << " ha sido creado exitosamente!\n\n";
	archivo.close();
}

void agregarMateria(Materia nuevaMateria)
{
	ofstream archivo;
	archivo.open(nombreArchivo, ios::app);

	if (archivo.fail())
	{
		cout << "No se pudo abrir el archivo: " << strerror(errno);
		EXIT_FAILURE;
	}

	archivo.write((char *)&nuevaMateria, sizeof(Materia));

	cout << "Se ha agregado la nueva materia " << nuevaMateria.nombre;
	archivo.close();
}

void listarMaterias()
{
	system("cls");
	cout << "***** REGISTRO DE MATERIAS *****\n\n";
	cout << setiosflags(ios::left) << setw(N + 2) << "NOMBRE" << setw(C + 2) << "CODIGO" << setw(3) << "UC\n\n";

	Materia materia;
	ifstream archivo;
	archivo.open(nombreArchivo, ios::in | ios::binary);

	if (archivo.fail())
	{
		cout << "No se pudo abrir el archivo: " << strerror(errno);
		EXIT_FAILURE;
	}

	while (archivo.read((char *)&materia, sizeof(Materia)))
	{
		cout << setiosflags(ios::left) << setw(N + 2) << materia.nombre << setw(C + 2) << materia.codigo << setw(3) << materia.unidadesDeCredito << endl;
	}

	cout << endl;
	system("pause");
	archivo.close();
}

void consultarMateria(char codigoMateriaConsultar[C])
{
	system("cls");
	cout << "***** REGISTRO DE MATERIAS *****\n\n";
	cout << setiosflags(ios::left) << setw(N + 2) << "NOMBRE" << setw(C + 2) << "CODIGO" << setw(3) << "UC\n\n";

	Materia materia;
	bool encontrado = false;
	ifstream archivo;
	archivo.open(nombreArchivo, ios::in | ios::binary);

	if (archivo.fail())
	{
		cout << "No se pudo abrir el archivo: " << strerror(errno);
		EXIT_FAILURE;
	}

	while (archivo.read(reinterpret_cast<char *>(&materia), sizeof(Materia)))
	{
		if (strcasecmp(codigoMateriaConsultar, materia.codigo) == 0)
		{
			cout << setw(N + 2) << materia.nombre << setw(C + 2) << materia.codigo << setw(3) << materia.unidadesDeCredito << endl;
			encontrado = true;
			break;
		}
	}

	if (!encontrado)
	{
		cout << "No se ha encontrado esa materia." << endl;
	}

	cout << endl;
	archivo.close();
	system("pause");
}

void modificarMateria(char codigoMateriaModificar[C])
{
	system("cls");
	cout << "***** REGISTRO DE MATERIAS *****\n\n";
	cout << setiosflags(ios::left) << setw(N + 2) << "NOMBRE" << setw(C + 2) << "CODIGO" << setw(3) << "UC\n\n";

	Materia materia;
	bool encontrado = false;
	fstream archivo;
	archivo.open(nombreArchivo, ios::in | ios::binary | ios::out);

	if (archivo.fail())
	{
		cout << "No se pudo abrir el archivo: " << strerror(errno);
		EXIT_FAILURE;
	}

	while (archivo.read(reinterpret_cast<char *>(&materia), sizeof(Materia)))
	{
		if (strcasecmp(codigoMateriaModificar, materia.codigo) == 0)
		{
			cout << setw(N + 2) << materia.nombre << setw(C + 2) << materia.codigo << setw(3) << materia.unidadesDeCredito << endl
					 << endl;
			encontrado = true;

			cout << "Escriba el nombre a modificar: ";
			fflush(stdin);
			cin.getline(materia.nombre, N);

			cout << "Escriba el codigo a modificar: ";
			fflush(stdin);
			cin.getline(materia.codigo, C);

			cout << "Escriba la unidades de credito a modificar: ";
			fflush(stdin);
			cin >> (materia.unidadesDeCredito);

			archivo.seekp(-sizeof(Materia), ios::cur); // Retroceder al inicio del registro actual
			archivo.write((char *)&materia, sizeof(Materia));

			system("cls");
			cout << "***** REGISTRO DE MATERIAS *****\n\n";
			cout << setiosflags(ios::left) << setw(N + 2) << "NOMBRE" << setw(C + 2) << "CODIGO" << setw(3) << "UC\n\n";
			cout << "Has editado con exito la materia\n\n"
					 << setw(N + 2) << materia.nombre << setw(C + 2) << materia.codigo << setw(3) << materia.unidadesDeCredito << endl
					 << endl;
			break;
		}
	}

	if (!encontrado)
	{
		cout << "No se ha encontrado una materia existente con el codigo " << codigoMateriaModificar << endl;
	}

	cout << endl;
	archivo.close();
	system("pause");
}

void eliminarMateria(char codigoMateriaEliminar[C])
{
	ifstream archivoEntrada(nombreArchivo, ios::in | ios::binary);
	if (archivoEntrada.fail())
	{
		cerr << "No se pudo abrir el archivo de entrada: " << strerror(errno) << endl;
		EXIT_FAILURE;
	}

	const char nombreArchivoTemp[A] = "temp.dat"; // Nombre del archivo temporal
	ofstream archivoTemp(nombreArchivoTemp, ios::out | ios::binary);
	if (archivoTemp.fail())
	{
		cerr << "No se pudo abrir el archivo temporal: " << strerror(errno) << endl;
		EXIT_FAILURE;
	}

	Materia materia;
	bool eliminado = false;
	while (archivoEntrada.read((char *)(&materia), sizeof(Materia)))
	{
		if (strcasecmp(codigoMateriaEliminar, materia.codigo) != 0)
		{
			archivoTemp.write((char *)&materia, sizeof(Materia));
		}
		else
		{
			eliminado = true;
		}
	}

	archivoEntrada.close();
	archivoTemp.close();

	if (!eliminado)
	{
		cout << "No se encontr� ninguna materia con el c�digo " << codigoMateriaEliminar << endl;
		remove(nombreArchivoTemp); // Eliminar el archivo temporal si no se hizo ning�n cambio
	}
	else
	{
		remove(nombreArchivo);										// Eliminar el archivo original
		rename(nombreArchivoTemp, nombreArchivo); // Renombrar el archivo temporal al nombre del original
		cout << "La materia con el c�digo " << codigoMateriaEliminar << " ha sido eliminada exitosamente." << endl;
	}

	system("pause");
}
