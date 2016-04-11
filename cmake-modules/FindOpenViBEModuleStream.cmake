# ---------------------------------
# Finds module Stream
# Adds library to target
# Adds include path
# ---------------------------------
OPTION(DYNAMIC_LINK_OPENVIBE_MODULE_STREAM "Dynamically link OpenViBE module Stream" ON)

IF(DYNAMIC_LINK_OPENVIBE_MODULE_STREAM)
	SET(OPENVIBE_MODULE_STREAM_LINKING "")
ELSE(DYNAMIC_LINK_OPENVIBE_MODULE_STREAM)
	SET(OPENVIBE_MODULE_STREAM_LINKING "-static")
ENDIF(DYNAMIC_LINK_OPENVIBE_MODULE_STREAM)

IF(OV_BRANCH_MODULES_STREAM)
	set(SRC_DIR ${OV_BASE_DIR}/openvibe-modules/stream/${OV_BRANCH_MODULES_STREAM})
ELSE(OV_BRANCH_MODULES_STREAM)
	set(SRC_DIR ${OV_BASE_DIR}/openvibe-modules/stream/${OV_TRUNK})
ENDIF(OV_BRANCH_MODULES_STREAM)

FIND_PATH(PATH_OPENVIBE_MODULES_STREAM src/stream/defines.h PATHS ${OV_BASE_DIR}/openvibe-modules/stream)
IF(PATH_OPENVIBE_MODULES_STREAM)
	MESSAGE(STATUS "  Found OpenViBE module Stream...")
	INCLUDE_DIRECTORIES(${PATH_OPENVIBE_MODULES_STREAM}/include)

	TARGET_LINK_LIBRARIES(${PROJECT_NAME} openvibe-module-stream${OPENVIBE_MODULE_STREAM_LINKING})

	ADD_DEFINITIONS(-DTARGET_HAS_Stream)
ELSE(PATH_OPENVIBE_MODULES_STREAM)
	MESSAGE(STATUS "  FAILED to find OpenViBE module Stream...")
ENDIF(PATH_OPENVIBE_MODULES_STREAM)