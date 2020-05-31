set(libsrc 
   "cpptinytools/StringTools.cpp" 
   )
set(libinclude 
   "cpptinytools/StringTools.hpp"
   "cpptinytools/StoppableTask.hpp"
   "cpptinytools/Resumabletask.hpp"
   )

add_library(CppTinyTools STATIC ${libsrc})

