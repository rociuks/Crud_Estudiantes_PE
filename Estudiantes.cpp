#include <iostream>
#include <stdlib.h> 
#include <string.h> 

using namespace std;
const char *nombre_archivo = "archivo.dat";
const char *nombre_archivo_temp = "archivo_aux.dat";
int opc = 0;

struct Estudiante{
	int codigo;
	string *nombres;
	string *apellidos;
	string *direccion;
	int telefono;
};

void menu();
void crear();
void leer();
void actualizar();
void delete_line();

main(){
menu();	
}
	
	void menu(){
	system("cls");
	
cout<<"1. Insertar estudiante"<<endl;
cout<<"2. ver estudiantes"<<endl;
cout<<"3. Actualizar estudiante"<<endl;
cout<<"4. eliminar estudiante"<<endl;
cout<<"5. Salir"<<endl<<endl;
cout<<"Digite su opcion: ";
cin>>opc; 
			
	system("cls");
	
	switch(opc)
	{
		case 1: crear();		 		;break;
 		case 2: leer();					;break;
 		case 3: actualizar();	 		;break;
 		case 4: delete_line();	 		;break;
 		case 5: exit(-1);				;break;  
		default:cout<<"Opcion no valida";  
	}	
}

void leer(){
		system("cls");
		FILE* archivo = fopen(nombre_archivo,"rb");	
		if (!archivo){
			archivo = fopen(nombre_archivo,"w+b");	
		}
		Estudiante estudiante;
		int id=0;	
		fread(&estudiante,sizeof(Estudiante),1,archivo);
		cout<<"____________________________________________"<<endl;
		cout<<"id"<<"|"<<"Codigo"<<"|"<<"Nombres"<<"|"<<"Apellidos"<<"|"<<"Direccion"<<"|"<<"Telefono"<<endl;
		do{
		cout<<"____________________________________________"<<endl;
		cout<<id<<"|"<<estudiante.codigo<<"|"<<estudiante.nombres<<"|"<<estudiante.apellidos<<"|"<<estudiante.direccion<<"|"<<estudiante.telefono<<endl;	
		fread(&estudiante,sizeof(Estudiante),1,archivo);
		id+=1;	
		}while(feof(archivo)==0);
		fclose(archivo);
		cout<<endl;
		
		system("pause");
		
		menu();
}

void actualizar(){
	FILE* archivo = fopen(nombre_archivo,"r+b");
	int id;
	Estudiante estudiante;
	string nombre,apellido,direccion;
	cout<<"Ingres el ID que desa Modificar:";
	cin>>id;
	fseek(archivo,id * sizeof(Estudiante),SEEK_SET);
	cout<<"Ingrese el Codigo:";
		cin>>estudiante.codigo;
		cin.ignore();
		
		cout<<"Ingrese los Nombres:";
		getline(cin,nombre);
		
		cout<<"Ingrese los Apellidos:";
		getline(cin,apellido);
		
		cout<<"Ingrese la Direccion: ";
		getline(cin,direccion);
		
		cout<<"Ingrese el Telefono:";
		cin>>estudiante.telefono;
		cin.ignore();
	
	fwrite(&estudiante,sizeof(Estudiante),1,archivo);
	fclose(archivo);
	leer();
}

void crear(){
	char continuar;
	FILE* archivo = fopen(nombre_archivo,"ab");
	
	Estudiante estudiante;
	
	string nombre,apellido,direccion;
	do{
		fflush(stdin);
		cout<<"Ingrese el Codigo: ";
		cin>>estudiante.codigo;
		cin.ignore();
		
		cout<<"Ingrese los Nombres: ";
		getline(cin,nombre);
		
		cout<<"Ingrese los Apellidos: ";
		getline(cin,apellido);
		
		cout<<"Ingrese la Direccion: ";
		getline(cin,direccion);
		
		cout<<"Ingrese el Telefono: ";
		cin>>estudiante.telefono;
		cin.ignore();
		
		fwrite(&estudiante,sizeof(Estudiante),1,archivo);
		cout<<"Desea agregar otro Estudiante (s/n): ";
		cin>>continuar;
		cout<<"___________________________________________________________"<<endl;
		cout<<endl;
	} while ( (continuar=='s') || (continuar=='S') );
	fclose(archivo);
	leer();
}

void delete_line(){
 	
FILE *archivo, *archivo_temp; //declaramos las variables donde tendremos el archivo principal y el archivo auxiliar para sobreescribir
int codigo; //declaramos un int para poder almacenar el codigo del estudiante
Estudiante estudiante; //declaramos la estructura de los estudiantes

archivo_temp=fopen(nombre_archivo_temp,"w+b"); //abrimos un archivo temporal para posteriormente escribir en el
archivo=fopen(nombre_archivo,"rb"); //abrimos el archivo principal para tener la informacion de el
                      				                
cout<<"codigo del estudiante a eliminar:"<<endl; 
cin>>codigo; //ingresamos el codigo del estudiante
                                                                                
	while(fread(&estudiante,sizeof(Estudiante),1,archivo)){	//leemos el archivo para saber su contenido
		if (estudiante.codigo != codigo) //hacemos el if dentro del while para leer los registros del archivo menos el codigo escrito
		fwrite(&estudiante,sizeof(Estudiante),1,archivo_temp); //escribimos en el archivo auxiliar todo menos el codigo que se escribio
		}
                
	fclose(archivo_temp); //cerramos el archivo temporal
	fclose(archivo); //cerramos el archivo principal
                
	archivo_temp=fopen(nombre_archivo_temp,"rb"); //abrimos el archivo auxiliar
	archivo=fopen(nombre_archivo,"wb"); //abrimos el archivo principal
 
	while(fread(&estudiante,sizeof(Estudiante),1, archivo_temp)){ //recorremos el archivo temporal con su informacion
		fwrite(&estudiante,sizeof(Estudiante),1, archivo); //escribimos en el archivo principal todo el contenido del archivo temporal
	}
                
fclose(archivo_temp); //cerramos el archivo temporal
fclose(archivo); //cerramos el archivo principal

leer(); // mostramos los registros del archivo

}
