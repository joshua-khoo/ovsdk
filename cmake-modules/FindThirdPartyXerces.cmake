# ---------------------------------
# Finds Xerces dependency
# ---------------------------------

IF(WIN32)
	FIND_PATH(XERCES_ROOT lib PATHS ${OV_CUSTOM_DEPENDENCIES_PATH} PATH_SUFFIXES xerces-c NO_DEFAULT_PATH)
	SET(CMAKE_INCLUDE_PATH ${CMAKE_INCLUDE_PATH} "${XERCES_ROOT}/include")
	SET(CMAKE_LIBRARY_PATH ${CMAKE_LIBRARY_PATH} "${XERCES_ROOT}/lib")

	INSTALL(
		DIRECTORY ${XERCES_ROOT}/lib/
		DESTINATION ${DIST_BINDIR}
		FILES_MATCHING PATTERN "*.dll")
ENDIF()

FIND_PACKAGE(XercesC REQUIRED)

IF(XercesC_FOUND)
	MESSAGE(STATUS "  Found xerces...")

	INCLUDE_DIRECTORIES(${XercesC_INCLUDE_DIRS})

	TARGET_LINK_LIBRARIES(${PROJECT_NAME} ${XercesC_LIBRARIES})
	ADD_DEFINITIONS(-DTARGET_HAS_ThirdPartyXERCES)

ELSE()
	MESSAGE(STATUS "  FAILED to find xerces...")
ENDIF()


