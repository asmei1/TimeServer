set(libsrc 
   "cpptinytools/StringTools.cpp" 
   "cpptinytools/BasicLogger.cpp"
   )
set(libinclude 
   "cpptinytools/StringTools.hpp"
   "cpptinytools/StoppableTask.hpp"
   "cpptinytools/Resumabletask.hpp"
   "cpptinytools/ILogger.hpp"
   "cpptinytools/BasicLogger.hpp"
   )

add_library(CppTinyTools STATIC ${libsrc})

