cmake_minimum_required(VERSION 3.14)

project(cncdata
  LANGUAGES NONE
  DESCRIPTION "Creates installers for the freeware C&C titles for multiple platforms."
)

if(WIN32)
    if(CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)
      set(CMAKE_INSTALL_PREFIX "C:/" CACHE PATH "..." FORCE)
    endif()
endif()

set(TD1 ${CMAKE_CURRENT_BINARY_DIR}/CNC95_GDI.iso)
set(TD2 ${CMAKE_CURRENT_BINARY_DIR}/CNC95_Nod.iso)
set(TD3 ${CMAKE_CURRENT_BINARY_DIR}/CD3_Covertops.bin)
set(RA1 ${CMAKE_CURRENT_BINARY_DIR}/CD1_ALLIES.iso)
set(RA2 ${CMAKE_CURRENT_BINARY_DIR}/CD2_SOVIET.iso)
set(RA3 ${CMAKE_CURRENT_BINARY_DIR}/CD3_Counterstrike.bin)
set(RA4 ${CMAKE_CURRENT_BINARY_DIR}/CD4_Aftermath.bin)
set(TD1ZIP ${CMAKE_CURRENT_BINARY_DIR}/gdi.zip)
set(TD2ZIP ${CMAKE_CURRENT_BINARY_DIR}/nod.zip)
set(TD3ZIP ${CMAKE_CURRENT_BINARY_DIR}/cov.zip)
set(RA1ZIP ${CMAKE_CURRENT_BINARY_DIR}/all.zip)
set(RA2ZIP ${CMAKE_CURRENT_BINARY_DIR}/sov.zip)
set(RA3ZIP ${CMAKE_CURRENT_BINARY_DIR}/cs.zip)
set(RA4ZIP ${CMAKE_CURRENT_BINARY_DIR}/am.zip)

# TD GDI disc
if(NOT EXISTS ${TD1})
    if(NOT EXISTS ${TD1ZIP})
        file(DOWNLOAD https://bigdownloads.cnc-comm.com/cnc1/CNC95_GDI.zip ${TD1ZIP}
             SHOW_PROGRESS
             EXPECTED_HASH MD5=f0f576c73221816e714a890901186bdf)
    endif()
    
    # this is OS-agnostic
    if(CMAKE_VERSION VERSION_LESS 3.18)
        execute_process(COMMAND ${CMAKE_COMMAND} -E tar -xf ${TD1ZIP} WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR})
    else()
        file(ARCHIVE_EXTRACT INPUT ${TD1ZIP} DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
    endif()
endif()

# TD Nod disc
if(NOT EXISTS ${TD2})
    if(NOT EXISTS ${TD2ZIP})
        file(DOWNLOAD https://bigdownloads.cnc-comm.com/cnc1/CNC95_Nod.zip ${TD2ZIP}
             SHOW_PROGRESS
             EXPECTED_HASH MD5=bb2cda261ede745cab8df5035ed5da57)
    endif()
    
    # this is OS-agnostic
    if(CMAKE_VERSION VERSION_LESS 3.18)
        execute_process(COMMAND ${CMAKE_COMMAND} -E tar -xf ${TD2ZIP} WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR})
    else()
        file(ARCHIVE_EXTRACT INPUT ${TD2ZIP} DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
    endif()
endif()

# TD Covert Ops disc
if(NOT EXISTS ${TD3})
    if(NOT EXISTS ${TD3ZIP})
        file(DOWNLOAD https://bigdownloads.cnc-comm.com/cnc1/CNC_Covertops.zip ${TD3ZIP}
             SHOW_PROGRESS
             EXPECTED_HASH MD5=0d2f9e9934cb8c99222fee574ef0cd9f)
    endif()
    
    # this is OS-agnostic
    if(CMAKE_VERSION VERSION_LESS 3.18)
        execute_process(COMMAND ${CMAKE_COMMAND} -E tar -xf ${TD3ZIP} WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR})
    else()
        file(ARCHIVE_EXTRACT INPUT ${TD3ZIP} DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
    endif()
endif()

# RA Allied disc
if(NOT EXISTS ${RA1})
    if(NOT EXISTS ${RA1ZIP})
        file(DOWNLOAD https://bigdownloads.cnc-comm.com/ra/RA_Allies.zip ${RA1ZIP}
             SHOW_PROGRESS
             EXPECTED_HASH MD5=3e5537577d7ff3884142695cc968dae7)
    endif()
    
    # this is OS-agnostic
    if(CMAKE_VERSION VERSION_LESS 3.18)
        execute_process(COMMAND ${CMAKE_COMMAND} -E tar -xf ${RA1ZIP} WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR})
    else()
        file(ARCHIVE_EXTRACT INPUT ${RA1ZIP} DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
    endif()
endif()

#RA Soviet disc
if(NOT EXISTS ${RA2})
    if(NOT EXISTS ${RA2ZIP})
        file(DOWNLOAD https://bigdownloads.cnc-comm.com/ra/RA_Soviet.zip ${RA2ZIP}
             SHOW_PROGRESS
             EXPECTED_HASH MD5=cb728df4ff5a81fde60799763a78d1d9)
    endif()
    
    # this is OS-agnostic
    if(CMAKE_VERSION VERSION_LESS 3.18)
        execute_process(COMMAND ${CMAKE_COMMAND} -E tar -xf ${RA2ZIP} WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR})
    else()
        file(ARCHIVE_EXTRACT INPUT ${RA2ZIP} DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
    endif()
endif()

# RA Counterstrike disc
if(NOT EXISTS ${RA3})
    if(NOT EXISTS ${RA3ZIP})
        file(DOWNLOAD https://bigdownloads.cnc-comm.com/ra/RA_Counterstrike.zip ${RA3ZIP}
             SHOW_PROGRESS
             EXPECTED_HASH MD5=e823a3ed12691f7434f878d3672a69e9)
    endif()
    
    # this is OS-agnostic
    if(CMAKE_VERSION VERSION_LESS 3.18)
        execute_process(COMMAND ${CMAKE_COMMAND} -E tar -xf ${RA3ZIP} WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR})
    else()
        file(ARCHIVE_EXTRACT INPUT ${RA3ZIP} DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
    endif()
endif()

# RA Aftermath disc
if(NOT EXISTS ${RA4})
    if(NOT EXISTS ${RA4ZIP})
        file(DOWNLOAD https://bigdownloads.cnc-comm.com/ra/RA_Aftermath.zip ${RA4ZIP}
             SHOW_PROGRESS
             EXPECTED_HASH MD5=a1a5f46b667fd2de71abc9832583e13a)
    endif()
    
    # this is OS-agnostic
    if(CMAKE_VERSION VERSION_LESS 3.18)
        execute_process(COMMAND ${CMAKE_COMMAND} -E tar -xf ${RA4ZIP} WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR})
    else()
        file(ARCHIVE_EXTRACT INPUT ${RA4ZIP} DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
    endif()
endif()
