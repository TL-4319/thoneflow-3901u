# v3.14 required for FetchContent_MakeAvailable
cmake_minimum_required(VERSION 3.14)
if (DEFINED MCU)
  include(FetchContent)
	FetchContent_Declare(
		mcu_support
		GIT_REPOSITORY https://github.com/bolderflight/mcu-support.git
		GIT_TAG v1.0.0
	)
	FetchContent_MakeAvailable(mcu_support)
  # Setting up the toolchain
  set(CMAKE_TOOLCHAIN_FILE "${mcu_support_SOURCE_DIR}/cmake/cortex.cmake")
	# Project information
	project(Thoneflow_3901u
		VERSION 1.0.0
		DESCRIPTION "ThoneFlow_3901U Driver"
		LANGUAGES CXX
	)
	# Grab the processor and set up definitions and compile options
	include(${mcu_support_SOURCE_DIR}/cmake/config_mcu.cmake)
	configMcu(${MCU} ${mcu_support_SOURCE_DIR})
	# Fetch core
	FetchContent_Declare(
		core
		GIT_REPOSITORY https://github.com/bolderflight/core.git
		GIT_TAG v3.0.2
	)
	FetchContent_MakeAvailable(core)
	# Add the library target
	add_library(thoneflow_3901u
		src/thoneflow_3901u.h
		src/thoneflow_3901u.cpp
	)
	# Link libraries
	target_link_libraries(thoneflow_3901u
		PUBLIC
			core
	)
	# Setup include directories 
	target_include_directories(thoneflow_3901u PUBLIC 
		$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src>
		$<INSTALL_INTERFACE:include>
	)
endif()
