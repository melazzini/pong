#include "components/ColliderComponent.h"
#include "utils.h"
#include <utility>

std::string SimpleColliderTagsManager::buildTag(const std::string &colliderRoleA,
                                                const std::string &colliderRoleB) const
{
    return colliderRoleA + SEPARATOR + colliderRoleB;
}
bool SimpleColliderTagsManager::tagsAreEqual(const std::string &tagA, const std::string &tagB) const
{
    std::vector<std::string> rolesTagsA{splitByListOfCharSeparators(tagA, SEPARATOR)};
    std::vector<std::string> rolesTagsB{splitByListOfCharSeparators(tagB, SEPARATOR)};
    return (rolesTagsA[0] == rolesTagsB[0] && rolesTagsA[1] == rolesTagsB[1]) ||
           (rolesTagsA[0] == rolesTagsB[1] && rolesTagsA[1] == rolesTagsB[0]);
}

std::pair<std::string, std::string> SimpleColliderTagsManager::getRolesForTag(const std::string &tag) const
{
    std::vector<std::string> roles{splitByListOfCharSeparators(tag, SEPARATOR)};
    return {std::string{roles[0]}, std::string{roles[1]}};
}

bool SimpleColliderTagsManager::validTag(const std::string &tag) const
{
    std::vector<std::string> roles{splitByListOfCharSeparators(tag, SEPARATOR)};
    size_t numOfSeparators{};
    for (auto character : tag)
    {
        if (std::string(1, character) == SEPARATOR)
        {
            ++numOfSeparators;
        }
    }
    if (roles.size() == 2 && numOfSeparators == 1)
    {
        return true;
    }
    return false;
}
