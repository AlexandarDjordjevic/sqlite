#include <Helpers.hpp>

namespace Helpers{

    uint16_t ToBigEndian_U16(uint16_t value) 
    {
        return IsLittleEndian() ? ChangeEndian_U16(value) : value;
    }

    uint32_t ToBigEndian_U32(uint32_t value) 
    {
        return IsLittleEndian() ? ChangeEndian_U32(value) : value;
    }
    /**
     * @brief change endian of uint32_t variable
     * 
     * @param value 
     * @return uint16_t 
     */
    uint32_t ChangeEndian_U32(uint32_t value){
        return ((value & 0x000000ff) << 24) + 
            ((value & 0x0000ff00) << 8) +
            ((value & 0x00ff0000) >> 8) + 
            ((value & 0xff000000) >> 24);
    }

    /**
     * @brief change endian of uint16_t variable
     * 
     * @param value 
     * @return uint16_t 
     */
    uint16_t ChangeEndian_U16(uint16_t value){
        return ((value & 0x00ff) << 8) + 
            ((value & 0xff00) << 8);
    }

    /**
     * @brief Check if host machine is little endian
     * 
     * @return true little endian
     * @return false big endian
     */
    bool IsLittleEndian(){
        uint32_t value = 0x01;
        uint8_t* ptr = (uint8_t*) &value;
        return *ptr == 0x01;
    }   
} //namsespace Helpers
