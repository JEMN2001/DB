/*
 * Estudiante.hpp
 *
 *  Created on: 7/11/2019
 *      Author: juan
 */

#include <string>
#include <iostream>
#ifndef ESTUDIANTE_HPP_
#define ESTUDIANTE_HPP_



class Estudiante {

public:
	Estudiante();
   Estudiante(int id, std::string nombre, float promedio);

   int getID();
   std::string getNombre();
   float getPromedio();

   void setPromedio(float promedio);
   void setNombre(std::string nombre);

   void write(std::ostream& f);
   void read(std::istream& f);

private:
   int id;
   std::string nombre;
   float promedio;

};

class PaginaEstudiante {
private:
	static const std::size_t capacidad = 20;
	std::size_t count;
	Estudiante * estudiantes;

public:
	PaginaEstudiante();
	bool agregarEstudiante(Estudiante est);
	void imprimir(void);

	void write(std::ostream & archivo);
	void read(std::istream& archivo);

	std::size_t size() const;
};

#endif /* ESTUDIANTE_HPP_ */
