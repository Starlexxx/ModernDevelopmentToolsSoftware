
#include <iostream>
#include <string>
#include <cassert>

#include <sstream>

#include "hw/l2_ApplicationLayer.h"

class TerminalOutput : public IOutput
{
public:
    virtual void Output(std::string s) const override final;
};


void TerminalOutput::Output(std::string s) const
{
    std::cout << s << std::endl;
}


int main(int , char **)
{
    TerminalOutput out;
    Application    app(out);

    for (std::string line; getline(std::cin, line); )
    {
        if (line.empty())
            break;

        std::istringstream  iss(line);
        std::vector<std::string> args;

        for(std::string str; iss.good();)
        {
            iss >> str;
            args.emplace_back(str);
        }

        if (!app.performCommand(args))
            return 1;
    }

    std::cout << "Выполнение завершено успешно" << std::endl;
    return 0;
}


