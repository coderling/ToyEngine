#pragma once
#include <string>

#include "EngineSetting.hpp"
#include "CommonDefines.hpp"

namespace Toy
{
class CommandLineParse final
{
    CommandLineParse() = delete;

   public:
    NOCOPY_AND_NOMOVE(CommandLineParse);
    static inline void Parse(Engine::EngineSetting& setting, int argc, char** argv)
    {
        for (int idx = 2; idx < argc; idx += 2)
            {
                char* option = argv[idx - 1];
                if (strcmp(option, "-DataPath") == 0)
                    {
                        setting.data_path = argv[idx];
                    }
            }
    }
};
}  // namespace Toy