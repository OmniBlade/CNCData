This is a CMake script to build archives and installers for the Command & Conquer and Red Alert games from resources freely available on the internet.

The intended use is to build data sets for use with [Vanilla Conquer](https://github.com/TheAssemblyArmada/Vanilla-Conquer).

To ensure the build can be done on various platforms, you will need a compiler installed to build the extraction tools.

To configure and build the data use the following command:

`cmake -DCMAKE_BUILD_TYPE=Release -DBUILD_X=ON -B build`  
`cmake --build build`

At this point you will have a .zip file for your chosen data set. If you want installers for your platforms as well run the following:  

`cd build`  
`cpack`

`BUILD_X` can be `BUILD_DEMO` `BUILD_FREEWARE` or `BUILD_FULL`.

`BUILD_DEMO` is the default and will only use the data from the downloadable demos. This data is probably the most freely distributable but is also the least functional. When run with Vanilla Conquer it provides and authentic single player demo experience and also supports limited multiplayer 

`BUILD_FREEWARE` uses data from the disk images that were released for free on EA's website. This data is more questionable as to how distributable it is as no specific license was really specified though it is widely mirrored. This data provides an experience similar to how the games were originally released.

`BUILD_FULL` uses the same data as `BUILD_FREEWARE` and also includes the expansion packs that were released. This data is really unclear how distributable it is as it was never officially distributed for free by EA. Despite this many community installers for the original games include this data as well. This data provides an experience similar to the final state the games were in before official support for them ended.
