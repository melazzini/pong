#include "utils.h"

std::vector<std::string> splitByListOfCharSeparators(const std::string &str, const std::string &sep)
{
    std::vector<std::string> v;
    std::string substr;

    for (size_t pos_left = 0, pos_right = 0;;)
    {
        pos_left = str.find_first_not_of(sep, pos_right);
        pos_right = str.find_first_of(sep, pos_left);

        if (pos_left == -1)
        {
            break;
        }
        else if (pos_right == -1)
        {
            substr = str.substr(pos_left);
            v.push_back(substr);
            break;
        }

        substr = str.substr(pos_left, pos_right - pos_left);
        v.push_back(substr);
    }

    return v;
}
