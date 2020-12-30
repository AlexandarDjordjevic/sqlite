#pragma once

#include <stdint.h>
#include <stdbool.h>

namespace Helpers
{
// class Helpers{
/**
 * @brief change endian of uint32_t variable
 * 
 * @param value 
 * @return uint16_t 
 */
extern uint32_t ChangeEndian_U32(uint32_t value);

/**
 * @brief change endian of uint16_t variable
 * 
 * @param value 
 * @return uint16_t 
 */
extern uint16_t ChangeEndian_U16(uint16_t value);

/**
 * @brief Check if host machine is little endian
 * 
 * @return true little endian
 * @return false big endian
 */
extern bool IsLittleEndian();  
// };  
} // namespace Helpers

