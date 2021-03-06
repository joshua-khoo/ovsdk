# ---------------------------------
# Finds module FS
# Adds library to target
# Adds include path
# ---------------------------------
OPTION(DYNAMIC_LINK_OPENVIBE_MODULE_FS "Dynamically link OpenViBE module FS" ON)

IF(DYNAMIC_LINK_OPENVIBE_MODULE_FS)
	SET(OPENVIBE_MODULE_FS_LINKING "")
	ADD_DEFINITIONS(-DFS_Shared)
ELSE()
	SET(OPENVIBE_MODULE_FS_LINKING "-static")
	ADD_DEFINITIONS(-DFS_Static)
ENDIF()

set(PATH_OPENVIBE_MODULES_FS "PATH_OPENVIBE_MODULES_FS-NOTFOUND")
set(SRC_DIR ${OV_BASE_DIR}/modules/fs/include)

FIND_PATH(PATH_OPENVIBE_MODULES_FS fs/defines.h PATHS ${SRC_DIR} NO_DEFAULT_PATH)
IF(PATH_OPENVIBE_MODULES_FS)
	debug_message( "  Found OpenViBE module FS... openvibe-module-fs${OPENVIBE_MODULE_FS_LINKING}")
	INCLUDE_DIRECTORIES(${PATH_OPENVIBE_MODULES_FS}/)

	TARGET_LINK_LIBRARIES(${PROJECT_NAME} openvibe-module-fs${OPENVIBE_MODULE_FS_LINKING})

	ADD_DEFINITIONS(-DTARGET_HAS_FS)
ELSE(PATH_OPENVIBE_MODULES_FS)
	MESSAGE(WARNING "  FAILED to find OpenViBE module FS...")
ENDIF(PATH_OPENVIBE_MODULES_FS)
