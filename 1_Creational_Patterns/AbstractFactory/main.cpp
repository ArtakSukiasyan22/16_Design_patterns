#include <iostream>

// ----------------------------  IBreastplate  ----------------------------
struct IBreastplate
{
    IBreastplate(int aDef)
        : mPDef(aDef)
    {}

    int pdef() { return mPDef; }
    virtual void draw() = 0;

protected:
    int mPDef{0};
};

// ----------------------------  IGauntlets  ----------------------------
struct IGauntlets
{
    IGauntlets(int aDef)
        : mPDef(aDef)
    {}

    int pdef() { return mPDef; }
    virtual void draw() = 0;

protected:
    int mPDef{0};
};

// ----------------------------  IGaiters  ----------------------------
struct IGaiters
{
    IGaiters(int aDef)
        : mPDef(aDef)
    {}

    int pdef() { return mPDef; }
    virtual void draw() = 0;

protected:
    int mPDef{0};
};

// ----------------------------  IBoots  ----------------------------
struct IBoots
{
    IBoots(int aDef)
        : mPDef(aDef)
    {}

    int pdef() { return mPDef; }
    virtual void draw() = 0;

protected:
    int mPDef{0};
};

// ----------------------------  Helmet  ----------------------------
struct IHelmet
{
    IHelmet(int aDef)
        : mPDef(aDef)
    {}

    int pdef() { return mPDef; }
    virtual void draw() = 0;

protected:
    int mPDef{0};
};

//---------------------- S80 HEAVY SET -------------------------------
struct BreastplateHeavyS80 : IBreastplate
{
    BreastplateHeavyS80()
        : IBreastplate(1000)
    {}

    void draw() override { std::cout << "S80 Breastplate Heavy\n"; }
};

struct GauntletsHeavyS80 : IGauntlets
{
    GauntletsHeavyS80()
        : IGauntlets(800)
    {}

    void draw() override { std::cout << "S80  Gauntlets Heavy\n"; }
};

struct GaitersHeavyS80 : IGaiters
{
    GaitersHeavyS80()
        : IGaiters(800)
    {}

    void draw() override { std::cout << "S80  Gaiters Heavy\n"; }
};

struct BootsHeavyS80 : IBoots
{
    BootsHeavyS80()
        : IBoots(800)
    {}

    void draw() override { std::cout << "S80  Boots Heavy\n"; }
};

struct HelmetHeavyS80 : IHelmet
{
    HelmetHeavyS80()
        : IHelmet(800)
    {}

    void draw() override { std::cout << "S80  Helmet Heavy\n"; }
};

//---------------------- S80 LIGHT SET -------------------------------
struct BreastplateLightS80 : IBreastplate
{
    BreastplateLightS80()
        : IBreastplate(100)
    {}

    void draw() override { std::cout << "S80 Breastplate Light\n"; }
};

struct GauntletsLightS80 : IGauntlets
{
    GauntletsLightS80()
        : IGauntlets(800)
    {}

    void draw() override { std::cout << "S80  Gauntlets Light\n"; }
};

struct GaitersLightS80 : IGaiters
{
    GaitersLightS80()
        : IGaiters(800)
    {}

    void draw() override { std::cout << "S80  Gaiters Light\n"; }
};

struct BootsLightS80 : IBoots
{
    BootsLightS80()
        : IBoots(800)
    {}

    void draw() override { std::cout << "S80  Boots Light\n"; }
};

struct HelmetLightS80 : IHelmet
{
    HelmetLightS80()
        : IHelmet(800)
    {}

    void draw() override { std::cout << "S80  Helmet Light\n"; }
};

struct IArmorSetFactory
{
    virtual std::unique_ptr<IBreastplate> makeBreastplate() = 0;
    virtual std::unique_ptr<IGauntlets> makeGauntlets() = 0;
    virtual std::unique_ptr<IGaiters> makeGaiters() = 0;
    virtual std::unique_ptr<IBoots> makeBoots() = 0;
    virtual std::unique_ptr<IHelmet> makeHelmet() = 0;
};

struct HeavyArmorS80Factory : IArmorSetFactory
{
    std::unique_ptr<IBreastplate> makeBreastplate() override
    {
        return std::make_unique<BreastplateHeavyS80>();
    }
    std::unique_ptr<IGauntlets> makeGauntlets() override
    {
        return std::make_unique<GauntletsHeavyS80>();
    }
    std::unique_ptr<IGaiters> makeGaiters() override { return std::make_unique<GaitersHeavyS80>(); }
    std::unique_ptr<IBoots> makeBoots() override { return std::make_unique<BootsHeavyS80>(); }
    std::unique_ptr<IHelmet> makeHelmet() override { return std::make_unique<HelmetHeavyS80>(); }
};

struct LightArmorS80Factory : IArmorSetFactory
{
    std::unique_ptr<IBreastplate> makeBreastplate() override
    {
        return std::make_unique<BreastplateLightS80>();
    }
    std::unique_ptr<IGauntlets> makeGauntlets() override
    {
        return std::make_unique<GauntletsLightS80>();
    }
    std::unique_ptr<IGaiters> makeGaiters() override { return std::make_unique<GaitersLightS80>(); }
    std::unique_ptr<IBoots> makeBoots() override { return std::make_unique<BootsLightS80>(); }
    std::unique_ptr<IHelmet> makeHelmet() override { return std::make_unique<HelmetLightS80>(); }
};

struct Hero
{
    void draw()
    {
        if (m_breastplate)
            m_breastplate->draw();
        if (m_gaiters)
            m_gaiters->draw();
        if (m_gauntlets)
            m_gauntlets->draw();
        if (m_helmet)
            m_helmet->draw();
        if (m_boots)
            m_boots->draw();
    }

    int pdef()
    {
        int res{0};
        if (m_breastplate)
            res += m_breastplate->pdef();
        if (m_gaiters)
            res += m_gaiters->pdef();
        if (m_gauntlets)
            res += m_gauntlets->pdef();
        if (m_helmet)
            res += m_helmet->pdef();
        if (m_boots)
            res += m_boots->pdef();
        return res;
    }

    std::unique_ptr<IBreastplate> m_breastplate;
    std::unique_ptr<IGaiters> m_gaiters;
    std::unique_ptr<IGauntlets> m_gauntlets;
    std::unique_ptr<IHelmet> m_helmet;
    std::unique_ptr<IBoots> m_boots;
};

void create_hero_type_A(Hero &aObj)
{
    HeavyArmorS80Factory factory;
    aObj.m_boots = factory.makeBoots();
    aObj.m_gaiters = factory.makeGaiters();
    aObj.m_gauntlets = factory.makeGauntlets();
    aObj.m_helmet = factory.makeHelmet();
    aObj.m_breastplate = factory.makeBreastplate();
}

void create_hero_type_B(Hero &aObj)
{
    LightArmorS80Factory factory;
    aObj.m_boots = factory.makeBoots();
    aObj.m_gaiters = factory.makeGaiters();
    aObj.m_gauntlets = factory.makeGauntlets();
    aObj.m_helmet = factory.makeHelmet();
    aObj.m_breastplate = factory.makeBreastplate();
}

void create_hero_type_C(Hero &aObj)
{
    LightArmorS80Factory light;
    HeavyArmorS80Factory heavy;
    aObj.m_boots = light.makeBoots();
    aObj.m_helmet = heavy.makeHelmet();
    aObj.m_breastplate = heavy.makeBreastplate();
}

int main()
{
    Hero a, b, c;

    create_hero_type_A(a);
    create_hero_type_B(b);
    create_hero_type_C(c);

    a.draw();
    b.draw();
    c.draw();

    std::cout << a.pdef() << std::endl;
    std::cout << b.pdef() << std::endl;
    std::cout << c.pdef() << std::endl;

    return 0;
}
