#include <SQLite/Database.hpp>
#include <string.h>
#include <sstream>
#include <Helpers.hpp>

#define COLOR_RESET "\u001b[0m"
#define COLOR_GREEN "\u001b[32m"
#define COLOR_RED "\u001b[31m"

namespace SQLite
{
    Database::Database(){

    }

    bool Database::LoadFromFile(const std::string& file_path) 
    {
        database_file = file_path;
        FILE* db = fopen(file_path.c_str(), "rb");
        if (db == NULL){
            perror("Fail to open database file");
            return false;
        }

        uint8_t data[sizeof(sql_header)];
        size_t fetched = fread(data, 1, sizeof(sql_header), db);
        if (sizeof(sql_header) == fetched){
            if (ParseHeader(data) == false){
                printf(COLOR_RED);
                printf("Invalid SQLite header.\n");
                printf(COLOR_RESET);
                return false;
            }
            PrintInfo();
        }
        return true;
    }

    bool Database::ParseHeader(const uint8_t* header_buffer){
        memcpy((void *)&header, header_buffer, sizeof(header));
        if (strcmp(Database::HEADER_STRING.c_str(), header.header_string) != 0)
            return false;

        if ( Helpers::IsLittleEndian() ){ 
            header.db_page_size = Helpers::ChangeEndian_U16(header.db_page_size);
            header.file_change_counter = Helpers::ChangeEndian_U32(header.file_change_counter);    
            header.db_size_in_pages = Helpers::ChangeEndian_U32(header.db_size_in_pages);
            header.version_valid_for = Helpers::ChangeEndian_U32(header.version_valid_for);
            header.sqlite_version_number = Helpers::ChangeEndian_U32(header.sqlite_version_number);
            SetSQLiteVersion(header.sqlite_version_number);
        }

        return true;
    }

    void Database::PrintInfo(){
        printf(COLOR_GREEN);
        printf("\n*******************************************************************************\n");
        printf(" Database File:   %s\n", database_file.c_str());
        printf(" SQLite Version:  %s\n", sqlite_version.c_str());
        printf("*******************************************************************************\n");
        printf("Database data: \n");
        printf("-------------------------------------------------------------------------------\n");
        printf("\tHeader String ............... %s\n", header.header_string);
        printf("\tPage Size ................... %d\n", header.db_page_size);
        printf("\tWrite Version ............... %d\n", header.write_version);
        printf("\tRead Version ................ %d\n", header.read_version);
        printf("\tDatabase size in pages ...... %d\n", header.db_size_in_pages);
        printf("\tMaximum Payload Fraction .... %d\n", header.maximum_payload_fraction);
        printf("\tMinumum Payload Fraction .... %d\n", header.minimum_payload_fraction);
        printf("\tLeaf payload fraction ....... %d\n", header.leaf_payload_fraction);
        printf("\tFile change counter ......... %d\n", header.file_change_counter);
        printf("\tSQLite Version Number ....... %d\n", header.sqlite_version_number);
        printf("\tVersion Valid ............... %d\n", header.version_valid_for);
        printf("-------------------------------------------------------------------------------\n");
        printf("*******************************************************************************\n");
        printf(COLOR_RESET);
    }
    
    std::string Database::GetSQLiteVersion() 
    {
        return sqlite_version;
    }

    void Database::SetSQLiteVersion(uint32_t numeric_version){
        auto x = numeric_version / 1000000;
        auto y = (numeric_version % 1000000) / 1000;
        auto z = numeric_version % 1000;

        std::stringstream version;
        version << std::to_string(x) << '.' << std::to_string(y) << '.' << std::to_string(z);
        sqlite_version = version.str();
    }
}