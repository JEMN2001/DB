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



#endif /* ESTUDIANTE_HPP_ */
