cmake_minimum_required(VERSION 3.14)

project(cncdata
  LANGUAGES C CXX
  DESCRIPTION "Creates installers for the freeware C&C titles for multiple platforms."
)

if(WIN32)
    if(CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)
      set(CMAKE_INSTALL_PREFIX "C:/" CACHE PATH "..." FORCE)
    endif()
endif()

option(BUILD_FULL "Build the full data set instead of just officially reelased freeware." OFF)

set(TD1 ${CMAKE_CURRENT_BINARY_DIR}/CNC95_GDI.iso)
set(TD2 ${CMAKE_CURRENT_BINARY_DIR}/CNC95_Nod.iso)
set(TD3 ${CMAKE_CURRENT_BINARY_DIR}/CD3_Covertops.bin)
set(RA1 ${CMAKE_CURRENT_BINARY_DIR}/CD1_ALLIES.iso)
set(RA2 ${CMAKE_CURRENT_BINARY_DIR}/CD2_Soviet.iso)
set(RA3 ${CMAKE_CURRENT_BINARY_DIR}/CD3_Counterstrike.bin)
set(RA4 ${CMAKE_CURRENT_BINARY_DIR}/CD4_Aftermath.bin)
set(TD1ZIP ${CMAKE_CURRENT_BINARY_DIR}/gdi.zip)
set(TD2ZIP ${CMAKE_CURRENT_BINARY_DIR}/nod.zip)
set(TD3ZIP ${CMAKE_CURRENT_BINARY_DIR}/cov.zip)
set(RA1ZIP ${CMAKE_CURRENT_BINARY_DIR}/all.zip)
set(RA2ZIP ${CMAKE_CURRENT_BINARY_DIR}/sov.zip)
set(RA3ZIP ${CMAKE_CURRENT_BINARY_DIR}/cs.zip)
set(RA4ZIP ${CMAKE_CURRENT_BINARY_DIR}/am.zip)
set(RAPATCH ${CMAKE_CURRENT_BINARY_DIR}/ra303eng.zip)
set(TDDIR ${CMAKE_CURRENT_BINARY_DIR}/vanillatd)
set(RADIR ${CMAKE_CURRENT_BINARY_DIR}/vanillara)

if(BUILD_FULL)
    # We only need bin/cue extraction for the expansion packs.
    add_executable(bchunk bchunk-1.2.1/bchunk.c bchunk-1.2.1/getopt.c)
    target_link_libraries(bchunk)
endif()

# We need this to extract TD installation data.
add_executable(isextract isextract/blast.cpp isextract/dostime.cpp isextract/isextract.cpp isextract/getopt.c isextract/main.cpp)

# this is OS-agnostic
if(CMAKE_VERSION VERSION_LESS 3.18)
    execute_process(COMMAND ${CMAKE_COMMAND} -E make_directory ${TDDIR} ${RADIR})
else()
    file(MAKE_DIRECTORY ${TDDIR} ${RADIR}) 
endif()

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
        execute_process(COMMAND ${CMAKE_COMMAND} -E tar -xf ${TD1} INSTALL/SETUP.Z WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR})
        execute_process(COMMAND ${CMAKE_COMMAND} -E make_directory ${TDDIR}/gdi)
    else()
        file(ARCHIVE_EXTRACT INPUT ${TD1ZIP} DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
        file(ARCHIVE_EXTRACT INPUT ${TD1} DESTINATION ${CMAKE_CURRENT_BINARY_DIR} PATTERNS INSTALL/SETUP.Z)
        file(MAKE_DIRECTORY ${TDDIR}/gdi)
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
        execute_process(COMMAND ${CMAKE_COMMAND} -E make_directory ${TDDIR}/nod)
    else()
        file(ARCHIVE_EXTRACT INPUT ${TD2ZIP} DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
        file(MAKE_DIRECTORY ${TDDIR}/nod)
    endif()
endif()

# TD Covert Ops disc
if(BUILD_FULL)
    if(NOT EXISTS ${TD3})
        if(NOT EXISTS ${TD3ZIP})
            file(DOWNLOAD https://bigdownloads.cnc-comm.com/cnc1/CNC_Covertops.zip ${TD3ZIP}
                 SHOW_PROGRESS
                 EXPECTED_HASH MD5=0d2f9e9934cb8c99222fee574ef0cd9f)
        endif()
    
        # this is OS-agnostic
        if(CMAKE_VERSION VERSION_LESS 3.18)
            execute_process(COMMAND ${CMAKE_COMMAND} -E tar -xf ${TD3ZIP} WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR})
            execute_process(COMMAND ${CMAKE_COMMAND} -E make_directory ${TDDIR}/covertops)
        else()
            file(ARCHIVE_EXTRACT INPUT ${TD3ZIP} DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
            file(MAKE_DIRECTORY ${TDDIR}/covertops)
        endif()

        add_custom_command(OUTPUT CD3_Covertops.iso
            COMMAND bchunk CD3_Covertops.bin CD3_Covertops.cue CD3_Covertops
            WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
            DEPENDS bchunk)
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
        execute_process(COMMAND ${CMAKE_COMMAND} -E tar -xf ${RA1} INSTALL/REDALERT.MIX WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR})
        execute_process(COMMAND ${CMAKE_COMMAND} -E make_directory ${RADIR}/allied)
    else()
        file(ARCHIVE_EXTRACT INPUT ${RA1ZIP} DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
        file(ARCHIVE_EXTRACT INPUT ${RA1} DESTINATION ${CMAKE_CURRENT_BINARY_DIR} PATTERNS INSTALL/REDALERT.MIX)
        file(MAKE_DIRECTORY ${RADIR}/allied)
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
        execute_process(COMMAND ${CMAKE_COMMAND} -E make_directory ${RADIR}/soviet)
    else()
        file(ARCHIVE_EXTRACT INPUT ${RA2ZIP} DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
        file(MAKE_DIRECTORY ${RADIR}/soviet)
    endif()
endif()

# RA Counterstrike disc
if(BUILD_FULL)
    if(NOT EXISTS ${RA3})
        if(NOT EXISTS ${RA3ZIP})
            file(DOWNLOAD https://bigdownloads.cnc-comm.com/ra/RA_Counterstrike.zip ${RA3ZIP}
                 SHOW_PROGRESS
                 EXPECTED_HASH MD5=e823a3ed12691f7434f878d3672a69e9)
        endif()
    
        # this is OS-agnostic
        if(CMAKE_VERSION VERSION_LESS 3.18)
            execute_process(COMMAND ${CMAKE_COMMAND} -E tar -xf ${RA3ZIP} WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR})
            execute_process(COMMAND ${CMAKE_COMMAND} -E make_directory ${RADIR}/counterstrike)
        else()
            file(ARCHIVE_EXTRACT INPUT ${RA3ZIP} DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
            file(MAKE_DIRECTORY ${RADIR}/counterstrike)
        endif()
    endif()
endif()

# RA Aftermath disc
if(BUILD_FULL)
    if(NOT EXISTS ${RA4})
        if(NOT EXISTS ${RA4ZIP})
            file(DOWNLOAD https://bigdownloads.cnc-comm.com/ra/RA_Aftermath.zip ${RA4ZIP}
                 SHOW_PROGRESS
                 EXPECTED_HASH MD5=a1a5f46b667fd2de71abc9832583e13a)
        endif()
    
        # this is OS-agnostic
        if(CMAKE_VERSION VERSION_LESS 3.18)
            execute_process(COMMAND ${CMAKE_COMMAND} -E tar -xf ${RA4ZIP} WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR})
            execute_process(COMMAND ${CMAKE_COMMAND} -E make_directory ${RADIR}/aftermath)
        else()
            file(ARCHIVE_EXTRACT INPUT ${RA4ZIP} DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
            file(MAKE_DIRECTORY ${RADIR}/aftermath)
        endif()
    endif()
endif()

# RA Expansion Files
# These files are present in the disk images but are in an RTPatch file.
if(BUILD_FULL)
    if(NOT EXISTS ${RAPATCH})
        file(DOWNLOAD http://nyerguds.arsaneus-design.com/cncstuff/ra303eng.zip ${RAPATCH}
             SHOW_PROGRESS 
             EXPECTED_HASH MD5=32ee995c25caf81f788f552fc782e117)
    endif()
endif()

add_custom_target(td_data ALL
    COMMAND isextract -x -d ${TDDIR} -f CCLOCAL.MIX -f DESEICNH.MIX -f LOCAL.MIX -f SPEECH.MIX -f TEMPICNH.MIX f TRANSIT.MIX -f UPDATE.MIX -f UPDATEC.MIX -f WINTICNH.MIX ${CMAKE_CURRENT_BINARY_DIR}/INSTALL/SETUP.Z
    COMMAND ${CMAKE_COMMAND} -E tar -xf ${TD1} CONQUER.MIX DESERT.MIX SOUNDS.MIX TEMPERAT.MIX WINTER.MIX
    WORKING_DIRECTORY ${TDDIR}
)

add_custom_target(td_disc1 ALL
    COMMAND ${CMAKE_COMMAND} -E tar -xf ${TD1} GENERAL.MIX MOVIES.MIX SCORES.MIX
    WORKING_DIRECTORY ${TDDIR}/gdi
)

add_custom_target(td_disc2 ALL
    COMMAND ${CMAKE_COMMAND} -E tar -xf ${TD2} GENERAL.MIX MOVIES.MIX SCORES.MIX
    WORKING_DIRECTORY ${TDDIR}/nod
)

if(BUILD_FULL)
    add_custom_target(td_disc3_iso
        COMMAND bchunk CD3_Covertops.bin CD3_Covertops.cue CD3_Covertops
        COMMAND ${CMAKE_COMMAND} -E tar -xf ${CMAKE_CURRENT_BINARY_DIR}/CD3_Covertops01.iso INSTALL/SC-000.MIX INSTALL/SC-001.MIX
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
        DEPENDS bchunk
        BYPRODUCTS CD3_Covertops01.iso CD3_Covertops02.cdr CD3_Covertops03.cdr CD3_Covertops04.cdr CD3_Covertops05.cdr CD3_Covertops06.cdr CD3_Covertops07.cdr CD3_Covertops08.cdr
    )

    add_custom_target(td_disc3 ALL
        COMMAND ${CMAKE_COMMAND} -E tar -xf ${CMAKE_CURRENT_BINARY_DIR}/CD3_Covertops01.iso GENERAL.MIX MOVIES.MIX SCORES.MIX
        WORKING_DIRECTORY ${TDDIR}/covertops
        DEPENDS td_disc3_iso
    )
    
    add_custom_target(td_data_ex ALL
        COMMAND ${CMAKE_COMMAND} -E copy_if_different ${CMAKE_CURRENT_BINARY_DIR}/INSTALL/SC-000.MIX SC-000.MIX
        COMMAND ${CMAKE_COMMAND} -E copy_if_different ${CMAKE_CURRENT_BINARY_DIR}/INSTALL/SC-001.MIX SC-001.MIX
        WORKING_DIRECTORY ${TDDIR}
        DEPENDS td_disc3_iso
    )
endif()

add_custom_target(ra_data ALL
    COMMAND ${CMAKE_COMMAND} -E copy_if_different ${CMAKE_CURRENT_BINARY_DIR}/INSTALL/REDALERT.MIX REDALERT.MIX  
    WORKING_DIRECTORY ${RADIR}
)

add_custom_target(ra_disc1 ALL
    COMMAND ${CMAKE_COMMAND} -E tar -xf ${RA1} MAIN.MIX
    WORKING_DIRECTORY ${RADIR}/allied
)

add_custom_target(ra_disc2 ALL
    COMMAND ${CMAKE_COMMAND} -E tar -xf ${RA2} MAIN.MIX
    WORKING_DIRECTORY ${RADIR}/soviet
)

if(BUILD_FULL)
    add_custom_target(ra_data_ex ALL
        COMMAND ${CMAKE_COMMAND} -E tar -xf ${RAPATCH} EXPAND.MIX EXPAND2.MIX HIRES1.MIX
        WORKING_DIRECTORY ${RADIR}
    )

    add_custom_target(ra_disc3_iso
        COMMAND bchunk CD3_Counterstrike.bin CD3_Counterstrike.cue CD3_Counterstrike
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
        DEPENDS bchunk
        BYPRODUCTS CD3_Counterstrike01.iso CD3_Counterstrike02.cdr CD3_Counterstrike03.cdr CD3_Counterstrike04.cdr CD3_Counterstrike05.cdr CD3_Counterstrike06.cdr
    )

    add_custom_target(ra_disc3 ALL
        COMMAND ${CMAKE_COMMAND} -E tar -xf ${CMAKE_CURRENT_BINARY_DIR}/CD3_Counterstrike01.iso MAIN.MIX
        WORKING_DIRECTORY ${RADIR}/counterstrike
        DEPENDS ra_disc3_iso
    )

    add_custom_target(ra_disc4_iso
        COMMAND bchunk CD4_Aftermath.bin CD4_Aftermath.cue CD4_Aftermath
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
        DEPENDS bchunk
        BYPRODUCTS CD4_Aftermath01.iso CD4_Aftermath02.cdr CD4_Aftermath03.cdr CD4_Aftermath04.cdr CD4_Aftermath05.cdr CD4_Aftermath06.cdr
    )

    add_custom_target(ra_disc4 ALL
        COMMAND ${CMAKE_COMMAND} -E tar -xf ${CMAKE_CURRENT_BINARY_DIR}/CD4_Aftermath01.iso MAIN.MIX
        WORKING_DIRECTORY ${RADIR}/aftermath
        DEPENDS ra_disc4_iso
    )
endif()