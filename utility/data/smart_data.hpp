// 1 TAB = 8 SPACES // LINE LENGTH = 100 CHARACTERS //

/*	+-----------------------------------------------------------------------+
	|	    Yet Another Hardware Abstraction Layer (YAHAL)		|
	|		https://github.com/andresgongora/yahal 			|
	|									|
	|									|
	| Copyright (c) 2015 - 2016, Individual contributors, see AUTHORS file.	|
	| 									|
	| This program is free software: you can redistribute it and/or modify	|
	| it under the terms of the GNU General Public License as published by	|
	| the Free Software Foundation, either version 2 of the License, or	|
	| (at your option) any later version.					|
	|									|
	| This program is distributed in the hope that it will be useful,	|
	| but WITHOUT ANY WARRANTY; without even the implied warranty of	|
	| MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the		|
	| GNU General Public License for more details.				|
	|									|
	| You should have received a copy of the GNU General Public License	|
	| along with this program.  If not, see <http://www.gnu.org/licenses/>. |
	|									|
	+-----------------------------------------------------------------------+	*/

#ifndef __YAHAL_UTILITY_DATA_SMART_DATA_HPP_INCLUDED__
#define __YAHAL_UTILITY_DATA_SMART_DATA_HPP_INCLUDED__

#include <limits>
#include <stdint.h>
#include <cstddef>

namespace yahal{ namespace utility{ namespace data{



/***********************************************************************************************//**
 *
 **************************************************************************************************/
template<typename T>
class SmartData : public std::numeric_limits<T>
{
public:
			// CONSTRUCTOR
			SmartData(void) {}
			SmartData(T value) : value_(value) {}



			// UNDERLYING DATA TYPE ACCESS
	operator 	T() const {return getValue();}



			// UNDERLYING DATA TYPE OPERATIONS
	SmartData	operator+(const SmartData& other) const {return SmartData(getValue() + other.getValue());}
	SmartData	operator-(const SmartData& other) const {return SmartData(getValue() - other.getValue());}
	SmartData	operator*(const SmartData& other) const {return SmartData(getValue() * other.getValue());}
	SmartData	operator/(const SmartData& other) const {return SmartData(getValue() / other.getValue());}
	SmartData	operator%(const SmartData& other) const {return SmartData(getValue() % other.getValue());}
	SmartData	operator^(const SmartData& other) const {return SmartData(getValue() ^ other.getValue());}
	SmartData	operator&(const SmartData& other) const {return SmartData(getValue() & other.getValue());}
	SmartData	operator|(const SmartData& other) const {return SmartData(getValue() | other.getValue());}

	SmartData	operator~ (void) const {return SmartData(~getValue());}
	SmartData	operator! (void) const {return SmartData(!getValue());}
	SmartData	operator<<(int bits) {return SmartData(getValue()<<bits);}
	SmartData	operator>>(int bits) {return SmartData(getValue()>>bits);}

	SmartData&	operator= (const SmartData& other) {setValue(other.getValue()); return *this;}
	SmartData&	operator+=(const SmartData& other) {*this = *this + other; return *this;}
	SmartData&	operator-=(const SmartData& other) {*this = *this - other; return *this;}
	SmartData&	operator*=(const SmartData& other) {*this = *this * other; return *this;}
	SmartData&	operator/=(const SmartData& other) {*this = *this / other; return *this;}
	SmartData&	operator%=(const SmartData& other) {*this = *this % other; return *this;}
	SmartData&	operator^=(const SmartData& other) {*this = *this ^ other; return *this;}
	SmartData&	operator&=(const SmartData& other) {*this = *this & other; return *this;}
	SmartData&	operator|=(const SmartData& other) {*this = *this | other; return *this;}

	SmartData&	operator<<=(int bits) {return *this = *this << bits;}
	SmartData&	operator>>=(int bits) {return *this = *this >> bits;}
	SmartData&	operator++(void) {*this += 1; return *this;}
	SmartData&	operator--(void) {*this -= 1; return *this;}

	bool		operator==(const SmartData& other) const {return getValue() == other.getValue();}
	bool		operator!=(const SmartData& other) const {return getValue() != other.getValue();}
	bool		operator<=(const SmartData& other) const {return getValue() <= other.getValue();}
	bool		operator>=(const SmartData& other) const {return getValue() >= other.getValue();}
	bool		operator< (const SmartData& other) const {return getValue() <  other.getValue();}
	bool		operator> (const SmartData& other) const {return getValue() >  other.getValue();}
	bool		operator&&(const SmartData& other) const {return getValue() && other.getValue();}
	bool		operator||(const SmartData& other) const {return getValue() || other.getValue();}



			// BIT ACCESS
/*	SmartData&	bitSet(const T flags) {return *this |= flags;}
	SmartData&	bitUnset(const T flags) {return *this &= ~flags;}
	SmartData&	bitToggle(T flags) {return *this ^= flags;}

	SmartData&	bitSet(T flags, T mask)
			{
				T and_mask = (~mask) | flags;
				T or_mask  =   mask  & flags;
				setValue((getValue() & and_mask) | or_mask);
				return *this;
			}*/



	/**
	 * I want binary operations:
	 * -Clever names for &= and |=
	 * -Be able to binary overwrite a value but also using a mask
	 * -Be able to set/unset 1 flag at position X. Such as "value |= (1 << X)"
	 * - Also get bit at position X. Should return bool.
	 *
	 * Normal operations:
	 * - Optional increment/decrement operation with overflow/underflow protection
	 *
	 * Other:
	 * - Special type for boolean array -> regardless of array size, optimize the boolean array into a struct that with bitfield access
	 * - Error minimizin float as seen on hackaday
	 * - Prohibit all other data types other than specified manually in this file
	 */



private:
	T		getValue(void) const {return value_;}
	void		setValue(T value) {value_ = value;}

	T		value_;
};


/* =================================================================================================
	Standard integer types
================================================================================================= */
typedef SmartData<float> Float;
typedef SmartData<double> Double;



/* =================================================================================================
	Exact-width integer types
================================================================================================= */
typedef SmartData<int8_t> Int8;
typedef SmartData<uint8_t> UInt8;

typedef SmartData<int16_t> Int16;
typedef SmartData<uint16_t> UInt16;

typedef SmartData<int32_t> Int32;
typedef SmartData<uint32_t> UInt32;

typedef SmartData<int64_t> Int64;
typedef SmartData<uint64_t> UInt64;



/* =================================================================================================
	Minimum-width integer types
================================================================================================= */
typedef SmartData<int_least8_t> IntLeast8;
typedef SmartData<uint_least8_t> UIntLeast8;

typedef SmartData<int_least16_t> IntLeast16;
typedef SmartData<uint_least16_t> UIntLeast16;

typedef SmartData<int_least32_t> IntLeast32;
typedef SmartData<uint_least32_t> UIntLeast32;

typedef SmartData<int_least64_t> IntLeast64;
typedef SmartData<uint_least64_t> UIntLeast64;



/* =================================================================================================
	 Fastest minimum-width integer types
================================================================================================= */
typedef SmartData<int_fast8_t> IntFast8;
typedef SmartData<uint_fast8_t> UIntFast8;

typedef SmartData<int_fast16_t> IntFast16;
typedef SmartData<uint_fast16_t> UIntFast16;

typedef SmartData<int_fast32_t> IntFast32;
typedef SmartData<uint_fast32_t> UIntFast32;

typedef SmartData<int_fast64_t> IntFast64;
typedef SmartData<uint_fast64_t> UIntFast64;



/* =================================================================================================
	 Greatest-width integer types
================================================================================================= */
typedef SmartData<intmax_t> IntMax;
typedef SmartData<uintmax_t> UIntMax;



/* ---------------------------------------------------------------------------------------------- */
}}}	// namespace yahal::utility::data
#endif 	// __YAHAL_UTILITY_DATA_SMART_DATA_HPP_INCLUDED__
