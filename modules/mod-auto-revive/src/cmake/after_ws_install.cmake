if(WIN32)
  if (MSVC)
    add_custom_command(TARGET worldserver
      POST_BUILD
      COMMAND ${CMAKE_COMMAND} -E copy ${CUR_DIR_MODULE_AUTO_REVIVE}/conf/AutoRevive.conf.dist ${CMAKE_BINARY_DIR}/bin/$(ConfigurationName)/
    )
  elseif (MINGW)
    add_custom_command(TARGET worldserver
      POST_BUILD
      COMMAND ${CMAKE_COMMAND} -E copy ${CUR_DIR_MODULE_AUTO_REVIVE}/conf/AutoRevive.conf.dist ${CMAKE_BINARY_DIR}/bin/
    )
  endif()
endif()

install(FILES "${CUR_DIR_MODULE_AUTO_REVIVE}/conf/AutoRevive.conf.dist" DESTINATION ${CONF_DIR})