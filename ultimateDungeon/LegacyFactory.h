#ifndef LEGACYFACTORY_H
#define LEGACYFACTORY_H


#include <string>


namespace dg {


class LegacyItem {
public:
    std::string name;
    LegacyItem(const std::string& n) : name(n) {}
};


class LegacyItemFactory {
public:
    // educational: returns raw pointer allocated with new; caller must delete
    static LegacyItem* create(const std::string& name) { return new LegacyItem(name); }
};


} // namespace dg


#endif // LEGACYFACTORY_H
