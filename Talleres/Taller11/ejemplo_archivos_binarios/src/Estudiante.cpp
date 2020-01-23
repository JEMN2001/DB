/*
 * Estudiante.cpp
 *
 *  Created on: 7/11/2019
 *      Author: juan
 */

#include"Estudiante.hpp"
#include<iostream>

#ifdef ESTUDIANTE_HPP_
	Estudiante::Estudiante(){
	   this->id=0;
	   this->nombre = "";
	   this->promedio = 0;
   }

   Estudiante::Estudiante(int id, std::string nombre, float promedio){
	   this->id=id;
	   this->nombre = nombre;
	   this->promedio = promedio;
   }

   int Estudiante::getID(){
	   return this->id;
   }

   std::string Estudiante::getNombre(){
	   return this->nombre;
   }

   float Estudiante::getPromedio(){
	   return this->promedio;
   }

   void Estudiante::setPromedio(float promedio){
	   this->promedio = promedio;
   }

   void Estudiante::setNombre(std::string nombre){
   	   this->nombre = nombre;
   }

   void Estudiante::write(std::ostream& f){
	   f.write( (char*)&this->id, sizeof(int) );

	   size_t size;
       size = nombre.size();
	   f.write( (char*)&size, sizeof(size_t) );
	   f.write( (char*)nombre.c_str(), size );

	   f.write( (char*)&this->promedio, sizeof(float) );
   }

   void Estudiante::read(std::istream& f){
	   f.read( (char*)&this->id, sizeof(int) );

	   size_t size;
	   char *data;
	   f.read( (char*)&size, sizeof(size_t) );

	   data = new char[size+1];
	   f.read( data, size );
	   data[size]='\0';
	   nombre = data;
	   delete data;

	   f.read( (char*)&this->promedio, sizeof(float) );
   }



#endif

