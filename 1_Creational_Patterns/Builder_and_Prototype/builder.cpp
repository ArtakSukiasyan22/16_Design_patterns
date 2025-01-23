#include <array>
#include <iostream>
#include <memory>
#include <string>
#include <vector>

namespace creational_builder {

struct IBase
{
    enum class eProperty {
        START,
        MATTACK,
        MDEF,
        PATTACK,
        PDEF,
        HEALTH,
        PATTACK_RANGE,
        MATTACK_RANGE,
        END
    };

    using ibase_property = std::pair<eProperty, float>;

    static std::string stringPropertyValue(eProperty aType)
    {
        switch (aType) {
        case eProperty::MATTACK: {
            return "Magic attack";
        }
        case eProperty::MDEF: {
            return "Magic deffence";
        }
        case eProperty::PATTACK: {
            return "Physical attack";
        }
        case eProperty::PDEF: {
            return "Physical deffence";
        }
        case eProperty::HEALTH: {
            return "Health";
        }
        case eProperty::PATTACK_RANGE: {
            return "Physical attack range";
        }
        case eProperty::MATTACK_RANGE: {
            return "Magic attack range";
        }
        case eProperty::START:
        case eProperty::END: {
            return "Unknown";
        }
            return "Unknown";
        }
    }

    IBase(std::initializer_list<ibase_property> aInitList)
    {
        m_properties.reserve(aInitList.size());
        for (auto property : aInitList)
            m_properties.push_back(property);
    }

    void setName(std::string aName) { m_name = aName; }

    const std::string &name() { return m_name; }

    float property_value(eProperty aType)
    {
        for (const auto &p : m_properties)
            if (aType == p.first)
                return p.second;
        return 0.f;
    }

protected:
    void apply_by_rate(const ibase_property &aVal)
    {
        for (auto &p : m_properties) {
            if (p.first == aVal.first) {
                p.second = p.second * aVal.second;
                return;
            }
        }
    }

protected:
    std::vector<ibase_property> m_properties;
    std::string m_name;
};

//----------------------- CAP ------------------------------------------------
struct Cap : IBase
{
    Cap(std::initializer_list<ibase_property> a_initList)
        : IBase(a_initList)
    {}

    void setPDefRate(float a_defRate)
    {
        m_PDefRate.second = a_defRate;
        apply_by_rate(m_PDefRate);
    }

private:
    ibase_property m_PDefRate{IBase::eProperty::PDEF, 1.f};
};
//----------------------- SHIRT ----------------------------------------------
struct Shirt : IBase
{
    Shirt(std::initializer_list<ibase_property> a_initList)
        : IBase(a_initList)
    {}

    void setPDefRate(float a_rate)
    {
        m_PDefRate.second = a_rate;
        apply_by_rate(m_PDefRate);
    }

    void setMDefRate(float a_rate)
    {
        m_MDefRate.second = a_rate;
        apply_by_rate(m_MDefRate);
    }

    void setHealthRate(float a_rate)
    {
        m_MHealthRate.second = a_rate;
        apply_by_rate(m_MHealthRate);
    }

private:
    ibase_property m_PDefRate{IBase::eProperty::PDEF, 1.f};
    ibase_property m_MDefRate{IBase::eProperty::MDEF, 1.f};
    ibase_property m_MHealthRate{IBase::eProperty::HEALTH, 1.f};
};
//----------------------- BRIEFS ---------------------------------------------
struct Briefs : IBase
{
    Briefs(std::initializer_list<ibase_property> aInitList)
        : IBase(aInitList)
    {}

    void setPDefRate(float a_rate)
    {
        m_PDefRate.second = a_rate;
        apply_by_rate(m_PDefRate);
    }

    void setMDefRate(float a_rate)
    {
        m_MDefRate.second = a_rate;
        apply_by_rate(m_MDefRate);
    }

private:
    ibase_property m_PDefRate{IBase::eProperty::PDEF, 1.f};
    ibase_property m_MDefRate{IBase::eProperty::MDEF, 1.f};
};

//----------------------- WEAPON ---------------------------------------------
struct Weapon : IBase
{
    Weapon(std::initializer_list<ibase_property> aInitList)
        : IBase(aInitList)
    {}

    void setPAttackRate(float a_rate)
    {
        m_PAttackRate.second = a_rate;
        apply_by_rate(m_PAttackRate);
    }

    void setMAttackRate(float a_rate)
    {
        m_MAttackRate.second = a_rate;
        apply_by_rate(m_MAttackRate);
    }

    void setPAttackRangeRate(float a_rate)
    {
        m_PAttackRangeRate.second = a_rate;
        apply_by_rate(m_PAttackRangeRate);
    }

    void setMAttackRangeRate(float a_rate)
    {
        m_MAttackRangeRate.second = a_rate;
        apply_by_rate(m_MAttackRangeRate);
    }

private:
    ibase_property m_PAttackRate{IBase::eProperty::PATTACK, 1.f};
    ibase_property m_MAttackRate{IBase::eProperty::MATTACK, 1.f};
    ibase_property m_PAttackRangeRate{IBase::eProperty::PATTACK_RANGE, 1.f};
    ibase_property m_MAttackRangeRate{IBase::eProperty::MATTACK_RANGE, 1.f};
};

//------------------------------- FINAL PRODUCT ------------------------------
struct Equipment
{
    float pattack_range()
    {
        float res{0.f};
        auto property = IBase::eProperty::PATTACK_RANGE;
        if (mupCap)
            res += mupCap->property_value(property);
        if (mupShirt)
            res += mupShirt->property_value(property);
        if (mupBriefs)
            res += mupBriefs->property_value(property);
        if (mupWeapon1)
            res += mupWeapon1->property_value(property);
        if (mupWeapon2)
            res += mupWeapon2->property_value(property);
        return res;
    }

    float mattack_range()
    {
        float res{0.f};
        auto property = IBase::eProperty::MATTACK_RANGE;
        if (mupCap)
            res += mupCap->property_value(property);
        if (mupShirt)
            res += mupShirt->property_value(property);
        if (mupBriefs)
            res += mupBriefs->property_value(property);
        if (mupWeapon1)
            res += mupWeapon1->property_value(property);
        if (mupWeapon2)
            res += mupWeapon2->property_value(property);
        return res;
    }

    float health()
    {
        float res{0.f};
        auto property = IBase::eProperty::HEALTH;
        if (mupCap)
            res += mupCap->property_value(property);
        if (mupShirt)
            res += mupShirt->property_value(property);
        if (mupBriefs)
            res += mupBriefs->property_value(property);
        if (mupWeapon1)
            res += mupWeapon1->property_value(property);
        if (mupWeapon2)
            res += mupWeapon2->property_value(property);
        return res;
    }

    float mattack()
    {
        float res{0.f};
        auto property = IBase::eProperty::MATTACK;
        if (mupCap)
            res += mupCap->property_value(property);
        if (mupShirt)
            res += mupShirt->property_value(property);
        if (mupBriefs)
            res += mupBriefs->property_value(property);
        if (mupWeapon1)
            res += mupWeapon1->property_value(property);
        if (mupWeapon2)
            res += mupWeapon2->property_value(property);
        return res;
    }

    float pattack()
    {
        float res{0.f};
        auto property = IBase::eProperty::PATTACK;
        if (mupCap)
            res += mupCap->property_value(property);
        if (mupShirt)
            res += mupShirt->property_value(property);
        if (mupBriefs)
            res += mupBriefs->property_value(property);
        if (mupWeapon1)
            res += mupWeapon1->property_value(property);
        if (mupWeapon2)
            res += mupWeapon2->property_value(property);
        return res;
    }

    float pdef()
    {
        float res{0.f};
        auto property = IBase::eProperty::PDEF;
        if (mupCap)
            res += mupCap->property_value(property);
        if (mupShirt)
            res += mupShirt->property_value(property);
        if (mupBriefs)
            res += mupBriefs->property_value(property);
        if (mupWeapon1)
            res += mupWeapon1->property_value(property);
        if (mupWeapon2)
            res += mupWeapon2->property_value(property);
        return res;
    }

    float mdef()
    {
        float res{0.f};
        auto property = IBase::eProperty::MDEF;
        if (mupCap)
            res += mupCap->property_value(property);
        if (mupShirt)
            res += mupShirt->property_value(property);
        if (mupBriefs)
            res += mupBriefs->property_value(property);
        if (mupWeapon1)
            res += mupWeapon1->property_value(property);
        if (mupWeapon2)
            res += mupWeapon2->property_value(property);
        return res;
    }

    void print_info()
    {
        std::cout << "<<" << mName << ">>" << std::endl;

        if (mupCap)
            std::cout << mupCap->name() << std::endl;
        if (mupShirt)
            std::cout << mupShirt->name() << std::endl;
        if (mupBriefs)
            std::cout << mupBriefs->name() << std::endl;
        if (mupWeapon1)
            std::cout << mupWeapon1->name() << std::endl;
        if (mupWeapon2)
            std::cout << mupWeapon2->name() << std::endl;

        std::cout << "All properties:" << std::endl;
        std::cout << "  " << IBase::stringPropertyValue(IBase::eProperty::MATTACK) << " = "
                  << mattack() << std::endl;
        std::cout << "  " << IBase::stringPropertyValue(IBase::eProperty::MDEF) << " = " << mdef()
                  << std::endl;
        std::cout << "  " << IBase::stringPropertyValue(IBase::eProperty::PATTACK) << " = "
                  << pattack() << std::endl;
        std::cout << "  " << IBase::stringPropertyValue(IBase::eProperty::PDEF) << " = " << pdef()
                  << std::endl;
        std::cout << "  " << IBase::stringPropertyValue(IBase::eProperty::HEALTH) << " = "
                  << health() << std::endl;
        std::cout << "  " << IBase::stringPropertyValue(IBase::eProperty::MATTACK_RANGE) << " = "
                  << mattack_range() << std::endl;
        std::cout << "  " << IBase::stringPropertyValue(IBase::eProperty::PATTACK_RANGE) << " = "
                  << pattack_range() << std::endl;
        std::cout << std::endl;
    }

    std::string mName;

    std::unique_ptr<Cap> mupCap;
    std::unique_ptr<Shirt> mupShirt;
    std::unique_ptr<Briefs> mupBriefs;
    std::unique_ptr<Weapon> mupWeapon1;
    std::unique_ptr<Weapon> mupWeapon2;
};

//------------------------------- IBUILDER -----------------------------------
struct IBuilder
{
    virtual std::unique_ptr<Cap> make_cap() = 0;
    virtual std::unique_ptr<Shirt> make_shirt() = 0;
    virtual std::unique_ptr<Briefs> make_briefs() = 0;

    virtual std::unique_ptr<Weapon> make_weapon_1() = 0;
    virtual std::unique_ptr<Weapon> make_weapon_2() = 0;
    std::string m_name{};
};

//------------------------------- DIRECTOR -----------------------------------
struct Director
{
    void setBuilder(std::unique_ptr<IBuilder> apBuilder) { m_builder = std::move(apBuilder); }

    std::unique_ptr<Equipment> make_equipment()
    {
        std::unique_ptr<Equipment> res = std::make_unique<Equipment>();

        res->mName = m_builder->m_name;
        res->mupCap = m_builder->make_cap();
        res->mupShirt = m_builder->make_shirt();
        res->mupBriefs = m_builder->make_briefs();
        res->mupWeapon1 = m_builder->make_weapon_1();
        res->mupWeapon2 = m_builder->make_weapon_2();
        return res;
    }

    std::unique_ptr<IBuilder> m_builder;
};

//------------------------------- MAGIC BUILDER ------------------------------
struct MagicDirtyAnt : IBuilder
{
    using property_list = std::initializer_list<IBase::ibase_property>;

    MagicDirtyAnt() { m_name = "Magic dirty ant"; }
    std::unique_ptr<Cap> make_cap()
    {
        property_list list{{IBase::eProperty::MDEF, 40}, {IBase::eProperty::PDEF, 10}};

        std::unique_ptr<Cap> cap = std::make_unique<Cap>(list);
        cap->setName("Torn cap");
        return cap;
    }

    std::unique_ptr<Shirt> make_shirt()
    {
        property_list list{{IBase::eProperty::MDEF, 230},
                           {IBase::eProperty::PDEF, 20},
                           {IBase::eProperty::HEALTH, 200}};

        std::unique_ptr<Shirt> shirt = std::make_unique<Shirt>(list);
        shirt->setName("Vest of an ant");
        return shirt;
    }

    std::unique_ptr<Briefs> make_briefs()
    {
        property_list list{{IBase::eProperty::MDEF, 350},
                           {IBase::eProperty::PDEF, 30},
                           {IBase::eProperty::HEALTH, 150}};

        std::unique_ptr<Briefs> briefs = std::make_unique<Briefs>(list);
        briefs->setName("Red briefs");
        return briefs;
    }

    std::unique_ptr<Weapon> make_weapon_1()
    {
        property_list list{{IBase::eProperty::PATTACK, 50},
                           {IBase::eProperty::MATTACK, 500},
                           {IBase::eProperty::MATTACK_RANGE, 50},
                           {IBase::eProperty::PATTACK_RANGE, 5}};

        std::unique_ptr<Weapon> weapon = std::make_unique<Weapon>(list);
        weapon->setName("Left eye");
        return weapon;
    }

    std::unique_ptr<Weapon> make_weapon_2()
    {
        property_list list{{IBase::eProperty::MDEF, 500},
                           {IBase::eProperty::HEALTH, 100},
                           {IBase::eProperty::MATTACK_RANGE, 250}};

        std::unique_ptr<Weapon> weapon = std::make_unique<Weapon>(list);
        weapon->setName("Right eye");
        return weapon;
    }
};

//------------------------------- PHYSICAL BUILDER ---------------------------
struct PhysicalDirtyAnt : IBuilder
{
    using property_list = std::initializer_list<IBase::ibase_property>;

    PhysicalDirtyAnt() { m_name = "Physical dirty ant"; }
    std::unique_ptr<Cap> make_cap() override
    {
        property_list list{{IBase::eProperty::MDEF, 5}, {IBase::eProperty::PDEF, 80}};

        std::unique_ptr<Cap> cap = std::make_unique<Cap>(list);
        cap->setName("Torn cap");
        return cap;
    }

    std::unique_ptr<Shirt> make_shirt()
    {
        property_list list{{IBase::eProperty::MDEF, 20},
                           {IBase::eProperty::PDEF, 400},
                           {IBase::eProperty::HEALTH, 500}};

        std::unique_ptr<Shirt> shirt = std::make_unique<Shirt>(list);
        shirt->setName("Vest of an ant");
        return shirt;
    }

    std::unique_ptr<Briefs> make_briefs()
    {
        property_list list{{IBase::eProperty::MDEF, 50},
                           {IBase::eProperty::PDEF, 300},
                           {IBase::eProperty::HEALTH, 250}};

        std::unique_ptr<Briefs> briefs = std::make_unique<Briefs>(list);
        briefs->setName("Red briefs");
        return briefs;
    }

    std::unique_ptr<Weapon> make_weapon_1()
    {
        property_list list{{IBase::eProperty::PATTACK, 250},
                           {IBase::eProperty::MATTACK, 0},
                           {IBase::eProperty::MATTACK_RANGE, 0},
                           {IBase::eProperty::PATTACK_RANGE, 10}};

        std::unique_ptr<Weapon> weapon = std::make_unique<Weapon>(list);
        weapon->setName("Left eye");
        return weapon;
    }

    std::unique_ptr<Weapon> make_weapon_2()
    {
        property_list list{{IBase::eProperty::MDEF, 50}, {IBase::eProperty::HEALTH, 500}};

        std::unique_ptr<Weapon> weapon = std::make_unique<Weapon>(list);
        weapon->setName("Right eye");
        return weapon;
    }
};

void builder_main()
{
    Director dir;

    dir.setBuilder(std::make_unique<MagicDirtyAnt>());
    std::unique_ptr<Equipment> magic_dirty_ant(std::make_unique<Equipment>());
    magic_dirty_ant = dir.make_equipment();
    magic_dirty_ant->print_info();

    dir.setBuilder(std::make_unique<PhysicalDirtyAnt>());
    std::unique_ptr<Equipment> physical_dirty_ant(std::make_unique<Equipment>());
    physical_dirty_ant = dir.make_equipment();
    physical_dirty_ant->print_info();
}

} // namespace creational_builder
