#ifndef __Curso_hpp__
#define __Curso_hpp__

#include <vector>
#include <string>
#include<iostream>

class TablaCurso {
private:

  class TuplaCurso {
  private:
      string curso_cod;
      string nombre;
      string nombre_unid;
      std::size_t creditos;
      std::size_t num_grupos;

      printTuple();
  };  

  static const std::size_t primaryKey = 0;
  std::vector<TuplaCurso> table;
  string name;

public:

  insert(string curso_cod, string nombre, string nombre_unid, std::size_t creditos, std::size_t num_grupos = 0)
  delete(string primaryKey);
  search(string primaryKey);

  readTable(std::ifstream & f);
  printTable();
  saveTable(std::ofstream & f);
};

#endif //_Curso_hpp_
