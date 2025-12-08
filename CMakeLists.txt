###### PROJECT CONFIG ######
cmake_minimum_required(VERSION 3.24)
project(BSGDelay VERSION 0.0.1)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_XCODE_GENERATE_SCHEME OFF)
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

###### PACKAGE MANAGEMENT ######
# We're going to use CPM as our package manager to bring in JUCE
# Check to see if we have CPM installed already.  Bring it in if we don't.
set(CPM_DOWNLOAD_VERSION 0.34.0)
set(CPM_DOWNLOAD_LOCATION "${CMAKE_BINARY_DIR}/cmake/CPM_${CPM_DOWNLOAD_VERSION}.cmake")

if (NOT EXISTS ${CPM_DOWNLOAD_LOCATION})
    message(STATUS "Downloading CPM.cmake to ${CPM_DOWNLOAD_LOCATION}")
    file(DOWNLOAD https://github.com/cpm-cmake/CPM.cmake/releases/download/v${CPM_DOWNLOAD_VERSION}/CPM.cmake ${CPM_DOWNLOAD_LOCATION})
endif ()

include(${CPM_DOWNLOAD_LOCATION})

# Bring in JUCE locally
CPMAddPackage(
        NAME juce
        GIT_REPOSITORY https://github.com/juce-framework/JUCE.git
        GIT_TAG origin/master
)

###### SET UP SOURCE FILES + LIBRARIES ######
set(SourceFiles
        Source/PluginEditor.cpp
        Source/PluginEditor.h
        Source/PluginProcessor.cpp
        Source/PluginProcessor.h
)

add_library(BSGDelay_Core STATIC
        Source/DSP/GainDSP.cpp
        Source/DSP/GainDSP.h
        Source/PluginParameters.cpp
        Source/PluginParameters.h
        Source/CircularBuffer.cpp
        Source/CircularBuffer.h
        Source/DSP/DelayDSP.cpp
        Source/DSP/DelayDSP.h
        Source/GUI/DefaultSkin.cpp
        Source/GUI/DefaultSkin.h
        Source/GUI/RotaryDial.cpp
        Source/GUI/RotaryDial.h
        Source/Utils/ParameterUtils.cpp
        Source/Utils/ParameterUtils.h
)

target_link_libraries(BSGDelay_Core PRIVATE
        juce::juce_analytics
        juce::juce_audio_basics
        juce::juce_audio_devices
        juce::juce_core
        juce::juce_data_structures
        juce::juce_graphics
        juce::juce_gui_basics
        juce::juce_gui_extra
        juce::juce_audio_utils
        juce::juce_dsp
        juce::juce_recommended_config_flags
        juce::juce_recommended_lto_flags
        juce::juce_recommended_warning_flags
)

###### JUCE PLUGIN CONFIG ######
juce_add_plugin(${PROJECT_NAME}
        COMPANY_NAME bristowsoundsgood
        IS_SYNTH FALSE
        NEEDS_MIDI_INPUT FALSE
        NEEDS_MIDI_OUTPUT FALSE
        IS_MIDI_EFFECT FALSE
        EDITOR_WANTS_KEYBOARD_FOCUS FALSE
        JUCE_VST3_CAN_REPLACE_VST2 FALSE
        COPY_PLUGIN_AFTER_BUILD TRUE
        PLUGIN_MANUFACTURER_CODE BSGX
        PLUGIN_CODE Del1
        FORMATS VST3 AU Standalone
        PRODUCT_NAME "BSGDelay"
)

juce_add_binary_data(BinaryData
        SOURCES
            Assets/Quantico.ttf
            Assets/IBMPlexSans.ttf
)

# How we want our SourceFiles to appear in our IDE
source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${SourceFiles})

# Make the SourceFiles buildable
target_sources(${PROJECT_NAME} PRIVATE ${SourceFiles})

# These are some toggleable options from the JUCE CMake API
target_compile_definitions(${PROJECT_NAME}
        PUBLIC
        JUCE_WEB_BROWSER=0
        JUCE_USE_CURL=0
        JUCE_VST3_CAN_REPLACE_VST2=0
)

# JUCE libraries to bring into our project
target_link_libraries(${PROJECT_NAME}
        PUBLIC
        BSGDelay_Core
)

###### SET UP TESTING EXECUTABLES ######
ENABLE_TESTING()

Include(FetchContent)

FetchContent_Declare(
        Catch2
        GIT_REPOSITORY https://github.com/catchorg/Catch2.git
        GIT_TAG        v3.8.1 # or a later release
)

FetchContent_MakeAvailable(Catch2)

add_executable(BSGDelayTest
        Tests/CircularBufferTest.cpp
)

target_link_libraries(BSGDelayTest PRIVATE
        Catch2::Catch2WithMain
        BSGDelay_Core
        BinaryData
        juce::juce_analytics
        juce::juce_audio_basics
        juce::juce_audio_devices
        juce::juce_core
        juce::juce_data_structures
        juce::juce_graphics
        juce::juce_gui_basics
        juce::juce_gui_extra
        juce::juce_audio_utils
        juce::juce_dsp
        juce::juce_recommended_config_flags
        juce::juce_recommended_lto_flags
        juce::juce_recommended_warning_flags
)

include(CTest)
include(Catch)
catch_discover_tests(BSGDelayTest)