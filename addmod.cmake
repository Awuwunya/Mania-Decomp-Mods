if(EXISTS ${INI_DIR}/src/${TARGET_NAME}/mod.ini)
	file(COPY ${INI_DIR}/src/${TARGET_NAME}/mod.ini DESTINATION ${GAME_DIR}/mods/${TARGET_NAME})
	message("COPY ${INI_DIR}/src/${TARGET_NAME}/mod.ini -> ${GAME_DIR}/mods/${TARGET_NAME}/mod.ini")
endif()

if(EXISTS ${CMAKE_BINARY_DIR}/${TARGET_NAME}.dll)
	file(COPY ${CMAKE_BINARY_DIR}/${TARGET_NAME}.dll DESTINATION ${GAME_DIR}/mods/${TARGET_NAME})
	message("COPY ${CMAKE_BINARY_DIR}/${TARGET_NAME}.dll -> ${GAME_DIR}/mods/${TARGET_NAME}//${TARGET_NAME}.dll")
endif()
