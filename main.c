#include <iostream>

#include <SQLite/Database.hpp>

int main(int argn, char* argv[]){
  
  auto database = new SQLite::Database();
  database->LoadFromFile(std::string(argv[1]));

  return 0;
}