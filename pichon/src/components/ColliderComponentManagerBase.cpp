#include "components/ColliderComponent.h"
#include "utils.h"

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
