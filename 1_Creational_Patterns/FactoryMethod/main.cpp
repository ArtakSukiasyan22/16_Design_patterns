#include <iostream>
#include <memory>
#include <vector>

class IProduction
{
public:
    virtual void release() = 0;
};

class Car : public IProduction
{
public:
    void release() override { std::cout << "Created new car\n"; }
};

class Truck : public IProduction
{
public:
    void release() override { std::cout << "Created new truck\n"; }
};

//------------------- Factory method -------------------
class IProductioFactory
{
public:
    virtual std::unique_ptr<IProduction> make_production() = 0;
};

class CarFactory : public IProductioFactory
{
public:
    std::unique_ptr<IProduction> make_production() override { return std::make_unique<Car>(); }
};

class TruckFactory : public IProductioFactory
{
public:
    std::unique_ptr<IProduction> make_production() override { return std::make_unique<Truck>(); }
};

// -------------------  Factory method parametrized  -------------------
enum ProductionType { eCar, eTruck };

class IProductionP
{
public:
    virtual void release() = 0;
    static std::unique_ptr<IProductionP> make_production_p(ProductionType aType);
};

class CarP : public IProductionP
{
    void release() override { std::cout << "Created new car\n"; }
};

class TruckP : public IProductionP
{
    void release() override { std::cout << "Created new truck\n"; }
};

class OtherP : public IProductionP
{
    void release() override { std::cout << "Created new Other\n"; }
};

std::unique_ptr<IProductionP> IProductionP::make_production_p(ProductionType aType)
{
    switch (aType) {
    case eCar:
        return std::make_unique<CarP>();
        break;
    case eTruck:
        return std::make_unique<TruckP>();
        break;
    default:
        return std::make_unique<OtherP>();
    }
}

//Without Factory
void example1()
{
    std::vector<std::unique_ptr<IProduction>> produactions;

    int size = (std::rand() % 10) + 1;

    for (int i = 0; i < size; ++i) {
        int rval = std::rand() % 2;

        switch (rval) {
        case 0:
            produactions.push_back(std::make_unique<Car>());
            break;
        case 1:
            produactions.push_back((std::make_unique<Truck>()));
            break;
        }
    }

    for (int i = 0; i < size; ++i) {
        auto &obj = produactions[i];
        obj.get()->release();
    }
}

//With Factory
void example2()
{
    std::vector<std::unique_ptr<IProduction>> produactions;

    int size = (std::rand() % 10) + 1;

    for (int i = 0; i < size; ++i) {
        int rval = std::rand() % 2;

        switch (rval) {
        case 0: {
            static CarFactory factory1;
            produactions.push_back(factory1.make_production());
            break;
        }
        case 1: {
            static TruckFactory factory2;
            produactions.push_back(factory2.make_production());
            break;
        }
        }
    }

    for (int i = 0; i < size; ++i) {
        auto &obj = produactions[i];
        obj.get()->release();
    }
}

//With Factory parametrized
void example3()
{
    std::vector<std::unique_ptr<IProductionP>> produactions;

    int size = (std::rand() % 10) + 1;

    for (int i = 0; i < size; ++i) {
        int rval = std::rand() % 2;

        switch (rval) {
        case 0: {
            produactions.push_back(IProductionP::make_production_p(ProductionType::eCar));
            break;
        }
        case 1: {
            produactions.push_back(IProductionP::make_production_p(ProductionType::eTruck));
            break;
        }
        }
    }

    for (int i = 0; i < size; ++i) {
        auto &obj = produactions[i];
        obj.get()->release();
    }
}

int main()
{
    // example1();
    example2();
    example3();
    return 0;
}
