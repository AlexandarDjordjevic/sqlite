#include <SQLite/Database.hpp>
#include <string.h>
#include <Helpers.hpp>

#define COLOR_RESET "\u001b[0m"
#define COLOR_GREEN "\u001b[32m"
#define COLOR_RED "\u001b[31m"

namespace SQLite
{
    Database::Database(){

    }
    void Database::LoadFromFile(const std::string& file_path) 
    {
        database_file = file_path;
        FILE* db = fopen(file_path.c_str(), "rb");
        if (db == NULL){
            perror("Fail to open file");
            return;
        }
        printf("Database file: %s is ready!\n", file_path.c_str());

        uint8_t data[sizeof(sql_header)];
        size_t fetched = fread(data, 1, sizeof(sql_header), db);

        printf("Fetched %ld bytes from database file\n", fetched);
        if (sizeof(sql_header) == fetched){    
            printf("Parsing header\n");
            if ( ParseHeader(data) ){
                printf(COLOR_RED);
                printf("Error parsing header\n");
                printf(COLOR_RESET);
            }
            PrintInfo();
        }
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
        }

        return true;
    }

    void Database::PrintInfo(){
        printf(COLOR_GREEN);
        printf("\n*******************************************************************************\n");
        printf(" File: %s\n", database_file.c_str());
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
        printf("\tVersion Number .............. %08x\n", header.sqlite_version_number);
        printf("\tVersion Valid ............... %d\n", header.version_valid_for);
        printf("-------------------------------------------------------------------------------\n");
        printf("*******************************************************************************\n");
        printf(COLOR_RESET);
    }
}