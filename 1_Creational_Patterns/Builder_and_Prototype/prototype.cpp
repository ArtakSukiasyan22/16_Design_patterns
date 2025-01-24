#include <iostream>
#include <string>

namespace create_prototype {

class Animal
{
public:
    virtual void setName(std::string *name) = 0;
    virtual std::string getName() = 0;
    virtual Animal *clone() const = 0;
};

class Sheep : public Animal
{
private:
    std::string *name;
    Sheep(const Sheep &donor) { this->name = donor.name; }

public:
    Sheep() {}
    ~Sheep() { delete name; }

    void setName(std::string *name) override { this->name = name; }
    std::string getName() override { return *name; }

    Sheep *clone() const override { return new Sheep(*this); }
};

void prototype_main()
{
    Sheep *sheeoDonor = new Sheep();
    std::string name = "Dolly";
    sheeoDonor->setName(&name);

    Sheep *sheepClone = sheeoDonor->clone();

    std::cout << sheeoDonor->getName() << "\n";
    std::cout << sheepClone->getName() << "\n";
}

} // namespace create_prototype
