/**
 * @author Aleksnadar Djordjevic (alexandar1608@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2021-01-03
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#pragma once

#include <stdint.h>

/*
**   OFFSET   SIZE     DESCRIPTION
**      0       1      Flags. 1: intkey, 2: zerodata, 4: leafdata, 8: leaf
**      1       2      byte offset to the first freeblock
**      3       2      number of cells on this page
**      5       2      first byte of the cell content area
**      7       1      number of fragmented free bytes
**      8       4      Right child (the Ptr(N) value).  Omitted on leaves.
*/

namespace SQLite
{
    class PageHeader{
    private:
        struct __attribute__((__packed__)) header_t{
            uint8_t flags;                              /* B-tree page type*/
            uint16_t offset_to_the_first_freeblock;     /* First freeblock on the page, or is zero */
            uint16_t number_of_cells_on_page;           /* Number of cells on the page */
            uint16_t first_byte_of_content_area;        /* Start of the cell content area */
            uint8_t number_of_fragmented_free_bytes;    /* Number of fragmented free bytes within the cell content area */
            uint32_t right_child;                       /* Right-most pointer. This value appears in the header of interior b-tree pages only */
        };

    public:
        enum btree_page_t : uint8_t {
            InteriorIndex = 0x02,
            InteriorTable = 0x05,
            LeafIndex = 0x0a,
            LeafTable = 0x0d
        };
        
        /**
         * @brief Default contstructor
         * 
         */
        PageHeader();

        /**
         * @brief Default destructor
         * 
         */
        ~PageHeader();

        PageHeader(const PageHeader &) = delete;
        PageHeader &operator=(const PageHeader &) = delete;
        PageHeader(PageHeader &&) = delete;
        PageHeader &operator=(const PageHeader &&) = delete;


        bool Deserialize(uint8_t* data);

    private:
        header_t header_ctx;
    };

} // namespace SQLite
