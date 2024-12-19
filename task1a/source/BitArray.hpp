#ifndef BITARRAY_H
#define BITARRAY_H

#include <vector>
#include <string>
#include <stdexcept>


// Класс для представления динамического битового массива с поддержкой битовых операций.
class BitArray {
private:
    std::vector<unsigned char> bits; // Хранилище битов в байтах.
    int num_bits;                    // Текущее количество битов в массиве.

public:
    /** Default constructor.
     * Constructs an empty bit array with no elements. */
    BitArray();

    /** Default destructor. */
    ~BitArray();

    /** Constructs a bit array of specified size.
     * All bits are initialized to `false`, unless the `value` is provided.
     * @param num_bits The number of bits in the array.
     * @param value The initial value for the first `sizeof(long)` bits (optional).
     * @throws std::invalid_argument if `num_bits` is negative.
     */
    explicit BitArray(int num_bits, unsigned long value = 0);

    /** Copy constructor.
     * Creates a new bit array as a copy of the given bit array.
     * @param other Another BitArray instance to copy. */
    BitArray(const BitArray& other);

    /** Swaps the contents of this array with another one.
     * This is a constant time operation.
     * @param other Another BitArray to swap with. */
    void swap(BitArray& other);

    /** Assignment operator.
     * Replaces the contents of this array with those of another one.
     * @param other Another BitArray instance.
     * @return Reference to the updated bit array. */
    BitArray& operator=(const BitArray& other);

    /** Resizes the bit array to contain a specified number of bits.
     * New bits, if added, are initialized to the specified value.
     * @param new_num_bits The desired size of the bit array.
     * @param value The value for new bits (optional, defaults to `false`). */
    void resize(int new_num_bits, bool value = false);

    /** Clears the bit array, making it empty. */
    void clear();

    /** Appends a bit to the end of the bit array.
     * @param bit The value of the bit to append (true or false). */
    void push_back(bool bit);

    // Bitwise operations

    /** Bitwise AND assignment (operator &=).
     * Performs an AND operation element-wise between this array and another.
     * Arrays must be of the same size.
     * @param other Another BitArray instance.
     * @return Reference to the updated bit array.
     * @throws std::invalid_argument if arrays differ in size. */
    BitArray& operator&=(const BitArray& other);

    /** Bitwise OR assignment (operator |=).
     * Performs an OR operation element-wise between this array and another.
     * Arrays must be of the same size.
     * @param other Another BitArray instance.
     * @return Reference to the updated bit array.
     * @throws std::invalid_argument if arrays differ in size. */
    BitArray& operator|=(const BitArray& other);

    /** Bitwise XOR assignment (operator ^=).
     * Performs an XOR operation element-wise between this array and another.
     * Arrays must be of the same size.
     * @param other Another BitArray instance.
     * @return Reference to the updated bit array.
     * @throws std::invalid_argument if arrays differ in size. */
    BitArray& operator^=(const BitArray& other);

    // Bit shifting

    /** Left shift assignment (operator <<=).
     * Shifts all bits in the array to the left by the specified number of positions.
     * Zeros are filled on the right.
     * @param n Number of positions to shift.
     * @return Reference to the updated bit array. */
    BitArray& operator<<=(int n);

    /** Right shift assignment (operator >>=).
     * Shifts all bits in the array to the right by the specified number of positions.
     * Zeros are filled on the left.
     * @param n Number of positions to shift.
     * @return Reference to the updated bit array. */
    BitArray& operator>>=(int n);

    /** Left shift (operator <<).
     * Creates a new bit array with all bits shifted to the left.
     * Zeros are filled on the right.
     * @param n Number of positions to shift.
     * @return New BitArray instance with shifted bits. */
    BitArray operator<<(int n) const;

    /** Right shift (operator >>).
     * Creates a new bit array with all bits shifted to the right.
     * Zeros are filled on the left.
     * @param n Number of positions to shift.
     * @return New BitArray instance with shifted bits. */
    BitArray operator>>(int n) const;

    // State modification

    /** Sets the bit at the specified index to the provided value.
     * @param n Index of the bit.
     * @param val Value to assign (true or false, defaults to `true`).
     * @return Reference to the updated bit array.
     * @throws std::out_of_range if the index is invalid. */
    BitArray& set(int n, bool val = true);

    /** Sets all bits in the array to 1 (true).
     * @return Reference to the updated bit array. */
    BitArray& set();

    /** Resets (clears) the bit at the specified index.
     * @param n Index of the bit.
     * @return Reference to the updated bit array.
     * @throws std::out_of_range if the index is invalid. */
    BitArray& reset(int n);

    /** Resets all bits in the array to 0 (false).
     * @return Reference to the updated bit array. */
    BitArray& reset();

    // State inspection

    /** Checks if any bit in the array is set (true).
     * @return `true` if at least one bit is true, otherwise `false`. */
    bool any() const;

    /** Checks if all bits in the array are clear (false).
     * @return `true` if all bits are false, otherwise `false`. */
    bool none() const;

    /** Bitwise NOT (operator ~).
     * Produces a new array with all bits inverted.
     * @return New BitArray instance. */
    BitArray operator~() const;

    /** Counts the number of bits set to 1 (true) in the array.
     * @return Number of true bits. */
    int count() const;

    /** Accesses a bit at the specified index (read-only).
     * @param n Index of the bit.
     * @return The value of the bit (true or false).
     * @throws std::out_of_range if the index is invalid. */
    bool operator[](int n) const;

    /** Retrieves the number of bits in the array.
     * @return Number of bits. */
    int size() const;

    /** Checks if the array is empty (contains no bits).
     * @return `true` if empty, otherwise `false`. */
    bool empty() const;

    /** Converts the bit array to its string representation.
     * Example: "101010"
     * @return String representation of the bit array. */
    std::string to_string() const;

    // Friends for comparison
    /** Compares two bit arrays for equality. */
    friend bool operator==(const BitArray& a, const BitArray& b);

    /** Compares two bit arrays for inequality. */
    friend bool operator!=(const BitArray& a, const BitArray& b);
};

/** Compares two bit arrays for equality.
 * Two bit arrays are considered equal if they have the same size
 * and identical bit values for all indices.
 * @param a The first BitArray to compare.
 * @param b The second BitArray to compare.
 * @return `true` if the arrays are equal, otherwise `false`.
 */
bool operator==(const BitArray& a, const BitArray& b);

/** Compares two bit arrays for inequality.
 * Two bit arrays are considered unequal if they differ in size
 * or in any bit value.
 * @param a The first BitArray to compare.
 * @param b The second BitArray to compare.
 * @return `true` if the arrays are not equal, otherwise `false`.
 */
bool operator!=(const BitArray& a, const BitArray& b);

/** Performs a bitwise AND operation between two bit arrays.
 * Produces a new bit array where each bit is the result of the AND
 * operation on the corresponding bits of the input arrays.
 * Both arrays must be of the same size.
 * @param b1 The first BitArray operand.
 * @param b2 The second BitArray operand.
 * @return A new BitArray containing the result of the AND operation.
 * @throws std::invalid_argument if the arrays are of different sizes.
 */
BitArray operator&(const BitArray& b1, const BitArray& b2);

/** Performs a bitwise OR operation between two bit arrays.
 * Produces a new bit array where each bit is the result of the OR
 * operation on the corresponding bits of the input arrays.
 * Both arrays must be of the same size.
 * @param b1 The first BitArray operand.
 * @param b2 The second BitArray operand.
 * @return A new BitArray containing the result of the OR operation.
 * @throws std::invalid_argument if the arrays are of different sizes.
 */
BitArray operator|(const BitArray& b1, const BitArray& b2);

/** Performs a bitwise XOR operation between two bit arrays.
 * Produces a new bit array where each bit is the result of the XOR
 * operation on the corresponding bits of the input arrays.
 * Both arrays must be of the same size.
 * @param b1 The first BitArray operand.
 * @param b2 The second BitArray operand.
 * @return A new BitArray containing the result of the XOR operation.
 * @throws std::invalid_argument if the arrays are of different sizes.
 */
BitArray operator^(const BitArray& b1, const BitArray& b2);


#endif // BITARRAY_H

