// Copyright 2015-2019 Elviss Strazdins. All rights reserved.

#include <cstdlib>
#include "EngineTVOS.hpp"
#include "utils/Log.hpp"

int main(int argc, char* argv[])
{
    try
    {
        ouzel::EngineTVOS engine(argc, argv);
        engine.run();
        return EXIT_SUCCESS;
    }
    catch (const std::exception& e)
    {
        ouzel::engine->log(ouzel::Log::Level::Error) << e.what();
        return EXIT_FAILURE;
    }
}
