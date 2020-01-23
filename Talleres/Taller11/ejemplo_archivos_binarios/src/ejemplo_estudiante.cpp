/*
 * ejemplo_estudiante.cpp
 *
 *  Created on: 7/11/2019
 *      Author: juanferna.perez
 */


#include<iostream>
#include<fstream>
#include<string>
#include"Estudiante.hpp"

int main() {

	// flujo de salida: escribir archivo
   std::ofstream wf("estudiante.dat", std::ios::out | std::ios::binary);
   if(!wf) {
	   std::cout << "No se puede abrir el archivo!" << std::endl;
      return 1;
   }

   // arreglo de Estudiantes a almacenar
   Estudiante* est_esc[3];
   est_esc[0] = new Estudiante(1, "Ana", 4.5);
   est_esc[1] = new Estudiante(2, "Antonio", 4.1);
   est_esc[2] = new Estudiante(3, "Bonifacio", 4.3);

   // escribir archivos binarios
   for(int i = 0; i < 3; i++)
	   est_esc[i]->write(wf);
      //wf.write((char *) &(*est_esc[i]), sizeof(Estudiante));
   wf.close();

   if(!wf.good()) {
	   std::cout << "Error occurred at writing time!" << std::endl;
      return 1;
   }
   std::cout << "Archivo escrito exitosamente" << std::endl;

   // flujo de entrada: leer archivo
   std::ifstream rf("estudiante.dat", std::ios::in | std::ios::binary);
   if(!rf) {
	   std::cout << "No se puede abrir el archivo!" << std::endl;
      return 1;
   }

   std::cout << "Archivo de lectura abierto exitosamente" << std::endl;

   // leer y cargar en memoria contenidos del archivo
   Estudiante* est_leer[3];
   for(int i = 0; i < 3; i++){
	   est_leer[i] = new Estudiante();
	   est_leer[i]->read(rf);
   }
   rf.close();

   std::cout << "Archivo de lectura cargado exitosamente" << std::endl;
   if(!rf.good()) {
	   std::cout << "Error occurred at reading time!" << std::endl;
      return 1;
   }

   // imprimir en consola contenidos cargados en memoria
   std::cout<<"Información de estudiantes:"<<std::endl;
   for(int i=0; i < 3; i++) {
	  std::cout << "ID: " << est_leer[i]->getID() << std::endl;
	  std::cout << "Nombre: " << est_leer[i]->getNombre() << std::endl;
	  std::cout << "Promedio: " << est_leer[i]->getPromedio() << std::endl;
	  std::cout << std::endl;
   }
   return 0;
}
