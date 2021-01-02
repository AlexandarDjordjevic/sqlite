#include <iostream>

#include <SQLite/Header.hpp>

int main(int argn, char* argv[]){
  
  auto database_header = new SQLite::Header();
  database_header->LoadFromFile(std::string(argv[1]));

  return 0;
}