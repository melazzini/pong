#pragma once
#include <string>
#include <tuple>

struct IColliderTagsManager
{
    [[nodiscard]] virtual std::string buildTag(const std::string &colliderRoleA,
                                               const std::string &colliderRoleB) const = 0;
    [[nodiscard]] virtual bool tagsAreEqual(const std::string &tagA, const std::string &tagB) const = 0;
    [[nodiscard]] virtual std::pair<std::string, std::string> getRolesForTag(const std::string &tag) const = 0;
    [[nodiscard]] virtual bool validTag(const std::string &tag) const = 0;
    virtual ~IColliderTagsManager() = default;
};

class SimpleColliderTagsManager : public IColliderTagsManager
{
  public:
    inline static const size_t NUM_SEPARATORS{1};
    inline static const size_t NUM_ROLES{2};

    inline static const std::string SEPARATOR{"_"};
    std::string buildTag(const std::string &colliderRoleA, const std::string &colliderRoleB) const override;
    bool tagsAreEqual(const std::string &tagA, const std::string &tagB) const override;
    std::pair<std::string, std::string> getRolesForTag(const std::string &tag) const override;
    bool validTag(const std::string &tag) const override;

  private:
    size_t countNumberOfSeparatorsInTag(const std::string &tag) const;
    bool validNumberOfSeparators(const std::string &tag) const;
    bool validNumberOfRoles(const std::string &tag) const;
};
