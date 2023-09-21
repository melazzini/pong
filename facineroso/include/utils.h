#pragma once
#include <string>
#include <vector>

enum class ArrowKey
{
    LEFT,
    RIGHT,
    UP,
    DOWN
};

/**
 * @brief Splits the given string into a vector of substrings using the provided separators.
 *
 * For example:
 *
 *          "Player_@Uses@10!@Laser  Projectiles!"
 *
 *              is splitted into four substrings
 *
 *          "Player", "Uses", "10", and "Laser Projectiles"
 *
 * @param str The source string to be splitted.
 * @param sep The list of separators.
 * @return std::vector<std::string>
 */
std::vector<std::string> splitByListOfCharSeparators(const std::string &str, const std::string &sep);

// A hash function used to hash a pair of any kind
// Copied this piece of code from https://www.geeksforgeeks.org/how-to-create-an-unordered_map-of-pairs-in-c/
// to enable having an unordered_map<pair<string,ColliderComponent*>,size_t>.
// I haven't tested this functor!
struct hash_pair
{
    template <class T1, class T2> size_t operator()(const std::pair<T1, T2> &p) const
    {
        auto hash1 = std::hash<T1>{}(p.first);
        auto hash2 = std::hash<T2>{}(p.second);

        if (hash1 != hash2)
        {
            return hash1 ^ hash2;
        }

        // If hash1 == hash2, their XOR is zero.
        return hash1;
    }
};

template <typename InputIterator, typename TPredicate, typename TCallable>
void forEachIf(InputIterator first, InputIterator last, TPredicate pred, TCallable callable)
{
    for (; first != last && pred(); first++)
    {
        callable(*first);
    }
}
