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
