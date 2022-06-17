#include "GlobalEnvironment.hpp"

namespace Toy::Engine
{
static GlobalEnvironment& GetEnv()
{
    static GlobalEnvironment g_env;
    return g_env;
}
}  // namespace Toy::Engine