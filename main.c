#include <iostream>

#include <SQLite/FileHeader.hpp>

int main(int argn, char* argv[]){
  
  auto database_header = new SQLite::FileHeader();
  database_header->LoadFromFile(std::string(argv[1]));
  database_header->PrintInfo();

  return 0;
}