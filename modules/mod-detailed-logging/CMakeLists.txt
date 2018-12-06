
AC_ADD_SCRIPT("${CMAKE_CURRENT_LIST_DIR}/src/KillStatTracker.cpp")
AC_ADD_SCRIPT("${CMAKE_CURRENT_LIST_DIR}/src/DeathStatTracker.cpp")
AC_ADD_SCRIPT("${CMAKE_CURRENT_LIST_DIR}/src/ZoneAreaTracker.cpp")

AC_ADD_SCRIPT_LOADER("KillStatTracker" "${CMAKE_CURRENT_LIST_DIR}/src/loader.h")
AC_ADD_SCRIPT_LOADER("DeathStatTracker" "${CMAKE_CURRENT_LIST_DIR}/src/loader.h")
AC_ADD_SCRIPT_LOADER("ZoneAreaTracker" "${CMAKE_CURRENT_LIST_DIR}/src/loader.h")

CU_ADD_HOOK(AFTER_WORLDSERVER_CMAKE "${CMAKE_CURRENT_LIST_DIR}/src/cmake/after_ws_install.cmake")
