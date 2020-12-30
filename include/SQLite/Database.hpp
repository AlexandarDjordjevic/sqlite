/**
 * @author Aleksandar Djordjevic (alexandar1608@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2020-12-30
 * 
 * @copyright Copyright (c) 2020
 * 
 */

#pragma once

#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>
#include <string>

#include "helpers.h"

/**
 * @brief SQL Header
 * 
 * Offset	Size	Description
 * 0	    16	    The header string: "Database format 3\000"
 * 16	    2	    The database page size in bytes. Must be a power of two between 512 and 32768 inclusive, or the value 1
 * representing  a page size of 65536.
 * 18	    1	    File format write version. 1 for legacy; 2 for WAL.
 * 19	    1	    File format read version. 1 for legacy; 2 for WAL.
 * 20	    1	    Bytes of unused "reserved" space at the end of each page. Usually 0.
 * 21	    1	    Maximum embedded payload fraction. Must be 64.
 * 22	    1	    Minimum embedded payload fraction. Must be 32.
 * 23	    1	    Leaf payload fraction. Must be 32.
 * 24	    4	    File change counter.
 * 28	    4	    Size of the database file in pages. The "in-header database size".
 * 32	    4	    Page number of the first freelist trunk page.
 * 36	    4	    Total number of freelist pages.
 * 40	    4	    The schema cookie.
 * 44	    4	    The schema format number. Supported schema formats are 1, 2, 3, and 4.
 * 48	    4	    Default page cache size.
 * 52	    4	    The page number of the largest root b-tree page when in auto-vacuum or incremental-vacuum modes, or zero otherwise.
 * 56	    4	    The database text encoding. A value of 1 means UTF-8. A value of 2 means UTF-16le. A value of 3 means UTF-16be.
 * 60	    4	    The "user version" as read and set by the user_version pragma.
 * 64	    4	    True (non-zero) for incremental-vacuum mode. False (zero) otherwise.
 * 68	    4	    The "Application ID" set by PRAGMA application_id.
 * 72	    20  	Reserved for expansion. Must be zero.
 * 92	    4	    The version-valid-for number.
 * 96	    4	    SQLITE_VERSION_NUMBER
 * 
 * TestDB.db
 * sqlite> CREATE TABLE COMPANY(
 *      ID INT PRIMARY KEY     NOT NULL,
 *      NAME           TEXT    NOT NULL,
 *      AGE            INT     NOT NULL,
 *      ADDRESS        CHAR(50),
 *      SALARY         REAL
 *  );
*/

namespace SQLite
{
class Database{
private:
    /* Typedefs */
    typedef enum __attribute__((__packed__)){
        Legacy = 0x01,
        WAL    = 0x02
    }rw_version_t;

    struct __attribute__((__packed__)) sql_header{
        char header_string[16];
        uint16_t db_page_size;
        rw_version_t write_version;
        rw_version_t read_version;
        uint8_t bytes_of_unused_space;
        uint8_t maximum_payload_fraction;   //Must be 64.
        uint8_t minimum_payload_fraction;   //Must be 32.
        uint8_t leaf_payload_fraction;   //Must be 32.
        uint32_t file_change_counter;
        uint32_t db_size_in_pages;
        uint32_t first_freelist_page;
        uint32_t number_of_freelist_pages;
        uint32_t schema_cookie;
        uint32_t schema_format_number;
        uint32_t default_page_cache_size;
        uint32_t root_b_tree_page;
        uint32_t text_encoding;
        uint32_t user_version;
        uint32_t incremental_vacuum_mode;
        uint32_t application_id;
        uint8_t reserved[20];
        uint32_t version_valid_for;
        uint32_t sqlite_version_number;
    };
public:
    const std::string HEADER_STRING = "Database format 3";

    /**
     * @brief Default contstructor
     * 
     */
    Database();

    /**
     * @brief Default destructor
     * 
     */
    ~Database();

    Database(const Database &) = delete;
    Database &operator=(const Database &) = delete;
    Database(Database &&) = delete;
    Database &operator=(const Database &&) = delete;

    void LoadFromFile(const std::string& file_path);
    bool ParseHeader(const uint8_t* header_buffer);
    void PrintInfo();
private:
    sql_header header;
};

} // namespace SQLite
