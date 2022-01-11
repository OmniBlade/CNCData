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

option(BUILD_DEMO "Build the demo data set." ON)
option(BUILD_FREEWARE "Build the freeware data set." OFF)
option(BUILD_FULL "Build the full data set." OFF)

set(TD1 ${CMAKE_CURRENT_BINARY_DIR}/CNC95_GDI.iso)
set(TD2 ${CMAKE_CURRENT_BINARY_DIR}/CNC95_Nod.iso)
set(TD3 ${CMAKE_CURRENT_BINARY_DIR}/CD3_Covertops.bin)
set(RA1 ${CMAKE_CURRENT_BINARY_DIR}/CD1_ALLIES.iso)
set(RA2 ${CMAKE_CURRENT_BINARY_DIR}/CD2_Soviet.iso)
set(RA3 ${CMAKE_CURRENT_BINARY_DIR}/CD3_Counterstrike.bin)
set(RA4 ${CMAKE_CURRENT_BINARY_DIR}/CD4_Aftermath.bin)
set(TDDEMO1ZIP ${CMAKE_CURRENT_BINARY_DIR}/cc1demo1.zip)
set(TDDEMO2ZIP ${CMAKE_CURRENT_BINARY_DIR}/cc1demo2.zip)
set(RADEMOZIP ${CMAKE_CURRENT_BINARY_DIR}/ra95demo.zip)
set(TD1ZIP ${CMAKE_CURRENT_BINARY_DIR}/gdi.zip)
set(TD1ZIP ${CMAKE_CURRENT_BINARY_DIR}/gdi.zip)
set(TD2ZIP ${CMAKE_CURRENT_BINARY_DIR}/nod.zip)
set(TD3ZIP ${CMAKE_CURRENT_BINARY_DIR}/cov.zip)
set(RA1ZIP ${CMAKE_CURRENT_BINARY_DIR}/all.zip)
set(RA2ZIP ${CMAKE_CURRENT_BINARY_DIR}/sov.zip)
set(RA3ZIP ${CMAKE_CURRENT_BINARY_DIR}/cs.zip)
set(RA4ZIP ${CMAKE_CURRENT_BINARY_DIR}/am.zip)
set(RAPATCH ${CMAKE_CURRENT_BINARY_DIR}/ra303eng.zip)

if(BUILD_DEMO)
    set(DATASET_NAME "demo")
    set(DATASET_ZIP_DEPENDS td_demo_data ra_demo_data)
endif()

if(BUILD_FREEWARE)
    set(BUILD_DEMO OFF)
    set(DATASET_NAME "freeware")
    set(DATASET_ZIP_DEPENDS td_data td_disc1 td_disc2 ra_data ra_disc1 ra_disc2)
endif()

if(BUILD_FULL)
    # We only need bin/cue extraction for the expansion packs.
    add_executable(bchunk bchunk-1.2.1/bchunk.c bchunk-1.2.1/getopt.c)
    target_link_libraries(bchunk)
    set(BUILD_DEMO OFF)
    set(BUILD_FREEWARE OFF)
    set(DATASET_NAME "full")
    set(DATASET_ZIP_DEPENDS td_data td_disc1 td_disc2 ra_data ra_disc1 ra_disc2 tdex_data tdex_disc3 raex_data raex_disc3 raex_disc4)
endif()

if(BUILD_FREEWARE OR BUILD_FULL)
    # We need this to extract TD installation data.
    add_executable(isextract isextract/blast.cpp isextract/dostime.cpp isextract/isextract.cpp isextract/getopt.c isextract/main.cpp)
endif()

if(BUILD_DEMO)
    if(NOT EXISTS ${TDDEMO1ZIP})
        file(DOWNLOAD https://archive.org/download/CommandConquerDemo/cc1demo1.zip ${TDDEMO1ZIP}
                SHOW_PROGRESS
                EXPECTED_HASH MD5=7d770d38618e20796fbe642037f08de5)
    endif()

    if(NOT EXISTS ${TDDEMO2ZIP})
        file(DOWNLOAD https://archive.org/download/CommandConquerDemo/cc1demo2.zip ${TDDEMO2ZIP}
                SHOW_PROGRESS
                EXPECTED_HASH MD5=bbe489d259c4e6d6cadb4a2544b764aa)
    endif()

    if(NOT EXISTS ${RADEMOZIP})
        file(DOWNLOAD https://archive.org/download/CommandConquerRedAlert_1020/ra95demo.zip ${RADEMOZIP}
                SHOW_PROGRESS
                EXPECTED_HASH MD5=b44ab9ec1bc634ea755587d1988e3722)
    endif()
endif()

if(BUILD_FREEWARE OR BUILD_FULL)
    # TD GDI disc
    if(NOT EXISTS ${TD1ZIP})
        file(DOWNLOAD https://bigdownloads.cnc-comm.com/cnc1/CNC95_GDI.zip ${TD1ZIP}
                SHOW_PROGRESS
                EXPECTED_HASH MD5=f0f576c73221816e714a890901186bdf)
    endif()

    # TD Nod disc
    if(NOT EXISTS ${TD2ZIP})
        file(DOWNLOAD https://bigdownloads.cnc-comm.com/cnc1/CNC95_Nod.zip ${TD2ZIP}
                SHOW_PROGRESS
                EXPECTED_HASH MD5=bb2cda261ede745cab8df5035ed5da57)
    endif()

    # RA Allied disc
    if(NOT EXISTS ${RA1ZIP})
        file(DOWNLOAD https://bigdownloads.cnc-comm.com/ra/RA_Allies.zip ${RA1ZIP}
                SHOW_PROGRESS
                EXPECTED_HASH MD5=3e5537577d7ff3884142695cc968dae7)
    endif()

    # RA Soviet disc
    if(NOT EXISTS ${RA2ZIP})
        file(DOWNLOAD https://bigdownloads.cnc-comm.com/ra/RA_Soviet.zip ${RA2ZIP}
                SHOW_PROGRESS
                EXPECTED_HASH MD5=cb728df4ff5a81fde60799763a78d1d9)
    endif()
endif()

if(BUILD_FULL)
    # TD Covert Ops disc
    if(NOT EXISTS ${TD3ZIP})
        file(DOWNLOAD https://bigdownloads.cnc-comm.com/cnc1/CNC_Covertops.zip ${TD3ZIP}
                SHOW_PROGRESS
                EXPECTED_HASH MD5=0d2f9e9934cb8c99222fee574ef0cd9f)
    endif()

    # RA Counterstrike disc
    if(NOT EXISTS ${RA3ZIP})
        file(DOWNLOAD https://bigdownloads.cnc-comm.com/ra/RA_Counterstrike.zip ${RA3ZIP}
                SHOW_PROGRESS
                EXPECTED_HASH MD5=e823a3ed12691f7434f878d3672a69e9)
    endif()
    
    # RA Aftermath disc
    if(NOT EXISTS ${RA4ZIP})
        file(DOWNLOAD https://bigdownloads.cnc-comm.com/ra/RA_Aftermath.zip ${RA4ZIP}
                SHOW_PROGRESS
                EXPECTED_HASH MD5=a1a5f46b667fd2de71abc9832583e13a)
    endif()

    # RA Expansion Files
    # These files are present in the disk images but are in an RTPatch file.
    if(NOT EXISTS ${RAPATCH})
        file(DOWNLOAD http://nyerguds.arsaneus-design.com/cncstuff/ra303eng.zip ${RAPATCH}
             SHOW_PROGRESS 
             EXPECTED_HASH MD5=32ee995c25caf81f788f552fc782e117)
    endif()
endif()

add_custom_target(clear_old
    COMMAND ${CMAKE_COMMAND} -E rm -Rf ${CMAKE_CURRENT_BINARY_DIR}/vanillatd
    COMMAND ${CMAKE_COMMAND} -E rm -Rf ${CMAKE_CURRENT_BINARY_DIR}/vanillara
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
)

if(BUILD_DEMO)
    add_custom_target(directory_setup
        COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_CURRENT_BINARY_DIR}/vanillatd
        COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_CURRENT_BINARY_DIR}/vanillara
        COMMAND ${CMAKE_COMMAND} -E tar -xf ${RADEMOZIP} ra95demo/INSTALL/REDALERT.MIX ra95demo/INSTALL/MAIN.MIX
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
        DEPENDS clear_old
    )

    add_custom_target(td_demo_data ALL
        BYPRODUCTS DEMO.MIX DEMOL.MIX DEMOM.MIX SOUNDS.MIX SPEECH.MIX WIN1.AUD MAP1.AUD
        COMMAND ${CMAKE_COMMAND} -E tar -xf ${TDDEMO1ZIP} DEMO.MIX DEMOL.MIX SOUNDS.MIX SPEECH.MIX WIN1.AUD MAP1.AUD
        COMMAND ${CMAKE_COMMAND} -E tar -xf ${TDDEMO2ZIP} DEMOM.MIX
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/vanillatd
        DEPENDS directory_setup
    )

    add_custom_target(ra_demo_data ALL
        BYPRODUCTS REDALERT.MIX MAIN.MIX
        COMMAND ${CMAKE_COMMAND} -E copy_if_different ${CMAKE_CURRENT_BINARY_DIR}/ra95demo/INSTALL/REDALERT.MIX REDALERT.MIX
        COMMAND ${CMAKE_COMMAND} -E copy_if_different ${CMAKE_CURRENT_BINARY_DIR}/ra95demo/INSTALL/MAIN.MIX MAIN.MIX
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/vanillara
        DEPENDS directory_setup
    )
endif()

if(BUILD_FREEWARE OR BUILD_FULL)
    # Build Tiberian Dawn data.
    add_custom_target(td_iso
        BYPRODUCTS CNC95_GDI.iso CNC95_Nod.iso INSTALL/SETUP.Z
        COMMAND ${CMAKE_COMMAND} -E tar -xf ${TD1ZIP}
        COMMAND ${CMAKE_COMMAND} -E tar -xf ${TD2ZIP}
        COMMAND ${CMAKE_COMMAND} -E tar -xf ${TD1} INSTALL/SETUP.Z
        COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_CURRENT_BINARY_DIR}/vanillatd
        COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_CURRENT_BINARY_DIR}/vanillatd/gdi
        COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_CURRENT_BINARY_DIR}/vanillatd/nod
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
        DEPENDS clear_old
    )

    add_custom_target(td_data ALL
        BYPRODUCTS CCLOCAL.MIX DESEICNH.MIX LOCAL.MIX SPEECH.MIX TEMPICNH.MIX TRANSIT.MIX UPDATE.MIX UPDATEC.MIX WINTICNH.MIX CONQUER.MIX DESERT.MIX SOUNDS.MIX TEMPERAT.MIX WINTER.MIX
        COMMAND isextract -x -d ${CMAKE_CURRENT_BINARY_DIR}/vanillatd -f CCLOCAL.MIX -f DESEICNH.MIX -f LOCAL.MIX -f SPEECH.MIX -f TEMPICNH.MIX -f TRANSIT.MIX -f UPDATE.MIX -f UPDATEC.MIX -f WINTICNH.MIX ${CMAKE_CURRENT_BINARY_DIR}/INSTALL/SETUP.Z
        COMMAND ${CMAKE_COMMAND} -E tar -xf ${TD1} CONQUER.MIX DESERT.MIX SOUNDS.MIX TEMPERAT.MIX WINTER.MIX
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/vanillatd
        DEPENDS td_iso isextract
    )

    add_custom_target(td_disc1 ALL
        BYPRODUCTS GENERAL.MIX MOVIES.MIX SCORES.MIX
        COMMAND ${CMAKE_COMMAND} -E tar -xf ${TD1} GENERAL.MIX MOVIES.MIX SCORES.MIX
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/vanillatd/gdi
        DEPENDS td_iso
    )

    add_custom_target(td_disc2 ALL
        BYPRODUCTS GENERAL.MIX MOVIES.MIX SCORES.MIX
        COMMAND ${CMAKE_COMMAND} -E tar -xf ${TD2} GENERAL.MIX MOVIES.MIX SCORES.MIX
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/vanillatd/nod
        DEPENDS td_iso
    )

    # Build Red Alert data.
    add_custom_target(ra_iso
        BYPRODUCTS CD1_ALLIES.iso CD2_Soviet.iso INSTALL/REDALERT.MIX
        COMMAND ${CMAKE_COMMAND} -E tar -xf ${RA1ZIP}
        COMMAND ${CMAKE_COMMAND} -E tar -xf ${RA2ZIP}
        COMMAND ${CMAKE_COMMAND} -E tar -xf ${RA1} INSTALL/REDALERT.MIX
        COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_CURRENT_BINARY_DIR}/freeware
        COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_CURRENT_BINARY_DIR}/vanillara
        COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_CURRENT_BINARY_DIR}/vanillara/allied
        COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_CURRENT_BINARY_DIR}/vanillara/soviet
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
        DEPENDS clear_old
    )

    add_custom_target(ra_data ALL
        BYPRODUCTS REDALERT.MIX
        COMMAND ${CMAKE_COMMAND} -E copy_if_different ${CMAKE_CURRENT_BINARY_DIR}/INSTALL/REDALERT.MIX REDALERT.MIX  
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/vanillara
        DEPENDS ra_iso
    )

    add_custom_target(ra_disc1 ALL
        BYPRODUCTS MAIN.MIX
        COMMAND ${CMAKE_COMMAND} -E tar -xf ${RA1} MAIN.MIX
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/vanillara/allied
        DEPENDS ra_iso
    )

    add_custom_target(ra_disc2 ALL
        BYPRODUCTS MAIN.MIX
        COMMAND ${CMAKE_COMMAND} -E tar -xf ${RA2} MAIN.MIX
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/vanillara/soviet
        DEPENDS ra_iso
    )
endif()

if(BUILD_FULL)
    # Build Tiberian Dawn expansion data.
    add_custom_target(tdex_iso
        BYPRODUCTS CD3_Covertops01.iso INSTALL/SC-000.MIX INSTALL/SC-001.MIX INSTALL/SPEECH.MIX CD3_Covertops02.cdr CD3_Covertops03.cdr CD3_Covertops04.cdr CD3_Covertops05.cdr CD3_Covertops06.cdr CD3_Covertops07.cdr CD3_Covertops08.cdr
        COMMAND ${CMAKE_COMMAND} -E tar -xf ${TD3ZIP}
        COMMAND ${CMAKE_COMMAND} -E make_directory vanillatd/covertops
        COMMAND bchunk CD3_Covertops.bin CD3_Covertops.cue CD3_Covertops
        COMMAND ${CMAKE_COMMAND} -E tar -xf ${CMAKE_CURRENT_BINARY_DIR}/CD3_Covertops01.iso INSTALL/SC-000.MIX INSTALL/SC-001.MIX INSTALL/SPEECH.MIX
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
        DEPENDS bchunk td_data
    )

    add_custom_target(tdex_disc3 ALL
        BYPRODUCTS GENERAL.MIX MOVIES.MIX SCORES.MIX
        COMMAND ${CMAKE_COMMAND} -E tar -xf ${CMAKE_CURRENT_BINARY_DIR}/CD3_Covertops01.iso GENERAL.MIX MOVIES.MIX SCORES.MIX
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/vanillatd/covertops
        DEPENDS tdex_iso
    )
    
    add_custom_target(tdex_data ALL
        BYPRODUCTS SPEECH.MIX SC-000.MIX SC-001.MIX
        COMMAND ${CMAKE_COMMAND} -E copy_if_different ${CMAKE_CURRENT_BINARY_DIR}/INSTALL/SC-000.MIX SC-000.MIX
        COMMAND ${CMAKE_COMMAND} -E copy_if_different ${CMAKE_CURRENT_BINARY_DIR}/INSTALL/SC-001.MIX SC-001.MIX
        COMMAND ${CMAKE_COMMAND} -E copy_if_different ${CMAKE_CURRENT_BINARY_DIR}/INSTALL/SPEECH.MIX SPEECH.MIX
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/vanillatd
        DEPENDS tdex_iso
    )
    
    # Build Red Alert expansion data.
    add_custom_target(raex_iso
        BYPRODUCTS CD3_Counterstrike01.iso CD4_Aftermath01.iso CD3_Counterstrike02.cdr CD3_Counterstrike03.cdr CD3_Counterstrike04.cdr CD3_Counterstrike05.cdr CD3_Counterstrike06.cdr CD4_Aftermath02.cdr CD4_Aftermath03.cdr CD4_Aftermath04.cdr CD4_Aftermath05.cdr CD4_Aftermath06.cdr
        COMMAND ${CMAKE_COMMAND} -E tar -xf ${RA3ZIP}
        COMMAND ${CMAKE_COMMAND} -E tar -xf ${RA4ZIP}
        COMMAND bchunk CD3_Counterstrike.bin CD3_Counterstrike.cue CD3_Counterstrike
        COMMAND bchunk CD4_Aftermath.bin CD4_Aftermath.cue CD4_Aftermath
        COMMAND ${CMAKE_COMMAND} -E make_directory vanillara/counterstrike
        COMMAND ${CMAKE_COMMAND} -E make_directory vanillara/aftermath
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
        DEPENDS bchunk ra_data
    )

    add_custom_target(raex_disc3 ALL
        BYPRODUCTS MAIN.MIX
        COMMAND ${CMAKE_COMMAND} -E tar -xf ${CMAKE_CURRENT_BINARY_DIR}/CD3_Counterstrike01.iso MAIN.MIX
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/vanillara/counterstrike
        DEPENDS raex_iso
    )

    add_custom_target(raex_disc4 ALL
        BYPRODUCTS MAIN.MIX
        COMMAND ${CMAKE_COMMAND} -E tar -xf ${CMAKE_CURRENT_BINARY_DIR}/CD4_Aftermath01.iso MAIN.MIX
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/vanillara/aftermath
        DEPENDS raex_iso
    )

    add_custom_target(raex_data ALL
        BYPRODUCTS EXPAND.MIX EXPAND2.MIX HIRES1.MIX LORES1.MIX
        COMMAND ${CMAKE_COMMAND} -E tar -xf ${RAPATCH} EXPAND.MIX EXPAND2.MIX HIRES1.MIX LORES1.MIX
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/vanillara
        DEPENDS raex_iso
    )
endif()

if(WIN32)
    if(CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)
        set(CMAKE_INSTALL_PREFIX "$ENV{ProgramFiles\(x86\)}/VanillaConquer" CACHE PATH "Default data installation path." FORCE)
    endif(CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)
endif()

add_custom_target(create_zip ALL
    COMMAND ${CMAKE_COMMAND} -E tar "cfv" "vanilla-conquer-data-installer-${DATASET_NAME}.zip" --format=zip vanillara vanillatd
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
    DEPENDS ${DATASET_ZIP_DEPENDS}
)

message("Install prefix for data is ${CMAKE_INSTALL_PREFIX}")

# Use these for the install destinations.
include(GNUInstallDirs)

install(DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/vanillatd
    DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}
    COMPONENT VanillaTDData
)

install(DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/vanillara
    DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}
    COMPONENT VanillaRAData
)

# CPack settings.
set(CPACK_SOURCE_GENERATOR "TGZ") # This file format is used to package source code ("make package_source")
set(CPACK_INSTALL_CMAKE_PROJECTS "${CMAKE_CURRENT_BINARY_DIR};${CMAKE_PROJECT_NAME};ALL;/")
set(CPACK_PACKAGE_VENDOR "Assembly Armada")
set(CPACK_PACKAGE_INSTALL_DIRECTORY "VanillaConquer")
set(CPACK_COMPONENTS_GROUPING ONE_PER_GROUP)
set(CPACK_COMPONENTS_ALL VanillaTDData VanillaRAData)
set(CPACK_COMPONENT_VANILLATDDATA_DISPLAYNAME "TD Data")
set(CPACK_COMPONENT_VANILLARADATA_DISPLAYNAME "RA Data")
set(CPACK_PACKAGE_FILE_NAME "vanilla-conquer-data-installer-${DATASET_NAME}")

if(WIN32)
    set(CPACK_GENERATOR "NSIS")

    set(CPACK_NSIS_ENABLE_UNINSTALL_BEFORE_INSTALL ON)
    set(CPACK_NSIS_DISPLAY_NAME "Vanilla Conquer")
    set(CPACK_NSIS_PACKAGE_NAME "Vanilla Conquer")
endif()

if(UNIX)
  if(CMAKE_SYSTEM_NAME MATCHES "Linux")
    set(SPECIFIC_SYSTEM_VERSION_NAME "${CMAKE_SYSTEM_NAME}")
    set(CPACK_GENERATOR "TGZ")
    if(EXISTS "/etc/redhat-release")
      set(LINUX_NAME "")
      file(READ "/etc/redhat-release" LINUX_ISSUE)
    elseif(EXISTS "/etc/issue")
      set(LINUX_NAME "")
      file(READ "/etc/issue" LINUX_ISSUE)
    endif()
    if(DEFINED LINUX_ISSUE)
      # Fedora case
      if(LINUX_ISSUE MATCHES "Fedora")
        string(REGEX MATCH "release ([0-9]+)" FEDORA "${LINUX_ISSUE}")
        set(LINUX_NAME "FC${CMAKE_MATCH_1}")
        set(CPACK_GENERATOR "RPM")
      endif(LINUX_ISSUE MATCHES "Fedora")
      # Red Hat case
      if(LINUX_ISSUE MATCHES "Red")
        string(REGEX MATCH "release ([0-9]+\\.[0-9]+)" REDHAT "${LINUX_ISSUE}")
        set(LINUX_NAME "RHEL_${CMAKE_MATCH_1}")
        set(CPACK_GENERATOR "RPM")
      endif(LINUX_ISSUE MATCHES "Red")
      # CentOS case
      if(LINUX_ISSUE MATCHES "CentOS")
        string(REGEX MATCH "release ([0-9]+\\.[0-9]+)" CENTOS "${LINUX_ISSUE}")
        set(LINUX_NAME "CentOS_${CMAKE_MATCH_1}")
        set(CPACK_GENERATOR "RPM")
      endif(LINUX_ISSUE MATCHES "CentOS")
      # Ubuntu case
      if(LINUX_ISSUE MATCHES "Ubuntu")
        string(REGEX MATCH "buntu ([0-9]+\\.[0-9]+)" UBUNTU "${LINUX_ISSUE}")
        set(LINUX_NAME "Ubuntu_${CMAKE_MATCH_1}")
        set(CPACK_GENERATOR "DEB")
      endif(LINUX_ISSUE MATCHES "Ubuntu")
      # Debian case
      if(LINUX_ISSUE MATCHES "Debian")
        string(REGEX MATCH "Debian .*ux ([a-zA-Z]*/?[a-zA-Z]*) .*" DEBIAN "${LINUX_ISSUE}")
        set(LINUX_NAME "Debian_${CMAKE_MATCH_1}")
        string(REPLACE "/" "_" LINUX_NAME ${LINUX_NAME})
        set(CPACK_GENERATOR "DEB")
      endif(LINUX_ISSUE MATCHES "Debian")
      # Open SuSE case
      if(LINUX_ISSUE MATCHES "SUSE")
        string(REGEX MATCH "SUSE  ([0-9]+\\.[0-9]+)" SUSE "${LINUX_ISSUE}")
        set(LINUX_NAME "openSUSE_${CMAKE_MATCH_1}")
        string(REPLACE "/" "_" LINUX_NAME ${LINUX_NAME})
        set(CPACK_GENERATOR "RPM")
      endif(LINUX_ISSUE MATCHES "SUSE")
    endif(DEFINED LINUX_ISSUE)
  endif(CMAKE_SYSTEM_NAME MATCHES "Linux")
endif(UNIX)

set(CPACK_STRIP_FILES TRUE)

file(GLOB_RECURSE DOT_FILES_BEGIN ".*") # To be ignored by Cpack
file(GLOB_RECURSE TILD_FILES "*~*") # To be ignored by Cpack

set(CPACK_SOURCE_IGNORE_FILES "/CVS/;/.svn/;/.swp$/;cscope.*;/.git/;${CMAKE_CURRENT_BINARY_DIR}/;/.bzr/;/.settings/;${DOT_FILES_BEGIN};${TILD_FILES}")

# PACKAGING OPTIONS: DEB
set(CPACK_DEBIAN_PACKAGE_MAINTAINER "Assembly Armada")
set(CPACK_DEBIAN_PACKAGE_ARCHITECTURE "noarch")
set(CPACK_DEBIAN_PACKAGE_DEPENDS "vanilla-conquer")

# PACKAGING OPTIONS: RPM
set(CPACK_RPM_PACKAGE_LICENSE "Unknown License")
set(CPACK_RPM_PACKAGE_VENDOR "Assembly Armada")

include(CPack)
