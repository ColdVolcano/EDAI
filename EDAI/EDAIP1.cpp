#include <iostream>

using namespace std;

const int CANTIDAD_ALUMNOS = 50;

struct tipo_fecha
{
	int dia, mes, anio;
};

struct tipo_nombre
{
	char app[20], apm[20], nom[30];

};

struct tipo_alumno
{
	char codigo[10];
	tipo_nombre nombre;
	char carrera[25];
	tipo_fecha fec_nac;
	float promedio;
	tipo_fecha fec_ing;
}alumnos[CANTIDAD_ALUMNOS];

bool EsIndiceValido(int indice)
{
	return indice >= 0 && indice < CANTIDAD_ALUMNOS;
}

int ObtenerIndiceValido()
{
	int indice;
	do
	{
		cin >> indice;
		if (!EsIndiceValido(indice))
			cout << "El valor debe estar en el rango [0.." << CANTIDAD_ALUMNOS
			<< ")";
	} while (!EsIndiceValido(indice));
	return indice;
}

bool IndiceTieneDatos(int indice)
{
	return EsIndiceValido(indice) && alumnos[indice].codigo[0] != '\0';
}

void Registrar()
{
	cout << "Introduce el indice en el que se guardará el alumno" << endl;
	int indice = ObtenerIndiceValido();

	cout << "Introduce el codigo del alumno" << endl;
	cin.getline(alumnos[indice].codigo, 10);
	do
	{
		cin.getline(alumnos[indice].codigo, 10);
		if (!IndiceTieneDatos(indice))
			cout << "El valor no puede estar vacio" << endl;
	} while (!IndiceTieneDatos(indice));

	cout << "Introduce el apellido paterno del alumno" << endl;
	cin.getline(alumnos[indice].nombre.app, 20);

	cout << "Introduce el apellido materno del alumno" << endl;
	cin.getline(alumnos[indice].nombre.apm, 20);

	cout << "Introduce el nombre del alumno" << endl;
	cin.getline(alumnos[indice].nombre.nom, 30);

	cout << "Introduce la carrera que cursa el alumno" << endl;
	cin.getline(alumnos[indice].carrera, 25);

	cout << "Introduce el dia de la fecha de nacimiento del alumno" << endl;
	cin >> alumnos[indice].fec_nac.dia;

	cout << "Introduce el mes de la fecha de nacimiento del alumno" << endl;
	cin >> alumnos[indice].fec_nac.mes;

	cout << "Introduce el año de la fecha de nacimiento del alumno" << endl;
	cin >> alumnos[indice].fec_nac.anio;

	cout << "Introduce el promedio actual del alumno" << endl;
	cin >> alumnos[indice].promedio;

	cout << "Introduce el dia de la fecha de ingreso del alumno" << endl;
	cin >> alumnos[indice].fec_ing.dia;

	cout << "Introduce el mes de la fecha de ingreso del alumno" << endl;
	cin >> alumnos[indice].fec_ing.mes;

	cout << "Introduce el año de la fecha de ingreso del alumno" << endl;
	cin >> alumnos[indice].fec_ing.anio;
}

void Imprimir(int indice, bool extendido)
{
	if (!IndiceTieneDatos(indice))
	{
		cout << "Alumno no registrado" << endl;
		return;
	}

	cout << "Alumno en indice " << indice << ':' << endl;
	cout << "Codigo: " << alumnos[indice].codigo << endl;
	cout << "Nombre: " << alumnos[indice].nombre.app << ' ' <<
		alumnos[indice].nombre.apm << ", " << alumnos[indice].nombre.nom << endl;
	cout << "Carera: " << alumnos[indice].carrera << endl;

	if (extendido)
	{
		cout << "Fecha de nacimiento: " << alumnos[indice].fec_nac.dia << '/'
			<< alumnos[indice].fec_nac.mes << '/' << alumnos[indice].fec_nac.anio << endl;
		cout << "Promedio: " << alumnos[indice].promedio << endl;
		cout << "Fecha de ingreso: " << alumnos[indice].fec_ing.dia << '/' <<
			alumnos[indice].fec_ing.mes << '/' << alumnos[indice].fec_ing.anio << endl;
	}
}

void Consultar()
{
	cout << "Ingrese el indice del alumno que desea consultar" << endl;
	int indice = ObtenerIndiceValido();
	Imprimir(indice, true);
}

void Limpiar(int indice)
{
	if (!EsIndiceValido(indice))
		return;

	alumnos[indice] = tipo_alumno();
	alumnos[indice].codigo[0] = '\0';
}

void Borrar()
{
	cout << "Ingrese el indice del alumno que desea eliminar" << endl;
	int indice = ObtenerIndiceValido();

	if (!IndiceTieneDatos(indice))
		cout << "Alumno no registrado" << endl;
	else
		Limpiar(indice);
}

void ImprimirLista()
{
	for (int i = 0; i < CANTIDAD_ALUMNOS; i++)
		if (IndiceTieneDatos(i))
			Imprimir(i, false);
}

int main()
{
	setlocale(LC_ALL, "es_MX");

	for (int i = 0; i < CANTIDAD_ALUMNOS; i++)
		Limpiar(i);

	int opc;
	do
	{
		cout << " Seleccione una opcion:\n\n 1.- Registrar alumno \n 2.-
			Consultar alumno\n 3. - Borrar alumno\n 4. - Imprimir lista \n 5. - Salir\n\n > ";
			cin >> opc;
		switch (opc)
		{
		case 1:
			Registrar();
			break;
		case 2:
			Consultar();
			break;
		case 3:
			Borrar();
			break;
		case 4:
			ImprimirLista();
			break;
		case 5:
			return 0;
		default:
			cout << "No se encuentra la opción" << endl;
			break;
		}
	} while (opc != 5);
}