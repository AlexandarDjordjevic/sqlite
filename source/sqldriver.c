#include "../include/sqldriver.h"

const char HEADER_STRING[]={"SQLite format 3\x0"};

void SQLite_PrintDatabaseInfo(const sql_header_t* const sql_header){
    printf("SQLite data: \n");
    printf("\tHeader String ............... %s\n", sql_header->header_string);
    printf("\tPage Size ................... %d\n", sql_header->db_page_size);
    printf("\tWrite Version ............... %d\n", sql_header->write_version);
    printf("\tRead Version ................ %d\n", sql_header->read_version);
    printf("\tDatabase size in pages ...... %d\n", sql_header->db_size_in_pages);
    printf("\tMaximum Payload Fraction .... %d\n", sql_header->maximum_payload_fraction);
    printf("\tMinumum Payload Fraction .... %d\n", sql_header->minimum_payload_fraction);
    printf("\tLeaf payload fraction ....... %d\n", sql_header->leaf_payload_fraction);
    printf("\tFile change counter ......... %d\n", sql_header->file_change_counter);
    printf("\tVersion Number .............. %08x\n", sql_header->sqlite_version_number);
    printf("\tVersion Valid ............... %d\n", sql_header->version_valid_for);
}

bool SQLite_ParseHeader(sql_header_t* header_context, const uint8_t* header_buffer){
    sql_header_t* sql_header = (sql_header_t*) header_buffer;
    memcpy(header_context, header_buffer, sizeof(sql_header_t));
    if (strcmp(HEADER_STRING, sql_header->header_string) != 0) 
        return false;

    if ( IsLittleEndian() ){
        header_context->db_page_size = ChangeEndian_U16(sql_header->db_page_size);
        header_context->file_change_counter = ChangeEndian_U32(sql_header->file_change_counter);    
        header_context->db_size_in_pages = ChangeEndian_U32(sql_header->db_size_in_pages);
        header_context->version_valid_for = ChangeEndian_U32(sql_header->version_valid_for);
    }

    return true;
}

bool SQLite_ParseFile(const char* file_path){
    FILE* db = fopen(file_path, "rb");
    if (db == NULL){
        perror("Fail to open file");
        return false;
    }

    printf("SQLite file: %s is ready!\n", file_path);

    sql_header_t sql_header;
    uint8_t data[sizeof(sql_header_t)];
    size_t fetched = fread(data, 1, sizeof(sql_header_t), db);

    printf("Fetched %ld bytes from database file\n", fetched);
    if (sizeof(sql_header_t) == fetched){    
        SQLite_ParseHeader(&sql_header, data);
        SQLite_PrintDatabaseInfo(&sql_header);
    }
}