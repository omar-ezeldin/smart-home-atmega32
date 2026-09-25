/* 
============================================
BITS_MATH
Bit Manipulation Library
============================================
Author: Omar Ezzeldin
============================================ 
*/ 

#ifndef BIT_MATH_H_
#define BIT_MATH_H_

/**
 * @brief Sets a bit in a register
 * 
 * @param REG The register
 * @param BIT The index of the bit
 */
#define SET_BIT(REG, BIT)     (REG |= (1 << BIT))

/**
 * @brief Clears a bit in a register
 * 
 * @param REG The register
 * @param BIT The index of the bit
 */
#define CLR_BIT(REG, BIT)     (REG &= ~(1 << BIT))

/**
 * @brief Toggles a bit in a register
 * 
 * @param REG The register
 * @param BIT The index of the bit
 */
#define TOG_BIT(REG, BIT)     (REG ^= (1 << BIT))

/**
 * @brief Gets a bit value from a register
 * 
 * @param REG The register
 * @param BIT The index of the bit
 */
#define GET_BIT(REG, BIT)     ((REG >> BIT) & 1)

#endif /* BIT_MATH_H_ */