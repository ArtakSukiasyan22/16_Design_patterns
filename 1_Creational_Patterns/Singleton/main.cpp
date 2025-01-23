#include <iostream>

using namespace std;

struct appSettings
{
    appSettings(const appSettings&) = delete;
    appSettings& operator=(const appSettings&) = delete;

    // for create object
    static appSettings& instance()
    {
        static appSettings res;
        return res;
    }

    void load()
    {
        m_screenWidth = 1024;
        m_screenHeight = 768;
    }

    const unsigned& width() { return m_screenWidth; }

    const unsigned& height() { return m_screenHeight; }

private:
    appSettings() = default; // make private default constructor

private:
    unsigned m_screenWidth{0};
    unsigned m_screenHeight{0};
};

void some_func_a()
{
    std::cout << "width = " << appSettings::instance().width() << std::endl;
}

void some_func_b()
{
    std::cout << "heigth = " << appSettings::instance().height() << std::endl;
}
void some_func_c()
{
    auto& w = appSettings::instance().width();
    auto& h = appSettings::instance().height();

    std::cout << "width = " << w << "\n";
    std::cout << "heigth = " << h << "\n";
}

int main()
{
    appSettings::instance().load();

    some_func_a();
    some_func_b();
    some_func_c();
    return 0;
}
