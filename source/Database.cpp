#include <SQLite/Database.hpp>
#include <string.h>

namespace SQLite
{
    Database::Database(){

    }
    void Database::LoadFromFile(const std::string& file_path) 
    {
        FILE* db = fopen(file_path.c_str(), "rb");
        if (db == NULL){
            perror("Fail to open file");
            return;
        }
        printf("Database file: %s is ready!\n", file_path.c_str());

        uint8_t data[sizeof(header)];
        size_t fetched = fread(data, 1, sizeof(header), db);

        printf("Fetched %ld bytes from database file\n", fetched);
        if (sizeof(header) == fetched){    
            ParseHeader(data);
            PrintInfo();
        }
    }

    bool Database::ParseHeader(const uint8_t* header_buffer){
        memcpy((void *)&header, header_buffer, sizeof(header));
        if (strcmp(Database::HEADER_STRING.c_str(), header.header_string) != 0) 
            return false;

        // if ( IsLittleEndian() ){
        //     header_context->db_page_size = ChangeEndian_U16(header.db_page_size);
        //     header_context->file_change_counter = ChangeEndian_U32(header.file_change_counter);    
        //     header_context->db_size_in_pages = ChangeEndian_U32(header.db_size_in_pages);
        //     header_context->version_valid_for = ChangeEndian_U32(header.version_valid_for);
        // }

        return true;
    }

    void Database::PrintInfo(){
        printf("Database data: \n");
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
    }
}