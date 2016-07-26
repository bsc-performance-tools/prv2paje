# prvreader

## Dependencies

- poti (automatically managed by git clone --recursive)
- Boost

## Get the sources

    $ git clone --recursive https://github.com/bsc-performance-tools/prvreader.git

## Go into the directory

    $ cd prvreader

##Generate makefile##

    $ mkdir build
    $ cd build
    $ cmake ..

You may want to install prvreader in a custom location:

    $ cmake -DCMAKE_INSTALL_PREFIX=/your/installation/directory/ ..

## Compile

    $ make

## Install

    $ make install

## prv2paje

This tools converts a paraver trace to a Pajé trace file

    $ prv2paje [options] input.prv
    
Options:

    - -o --output [output-trace]: output Pajé trace
    - -f --filter [filter-file]: filtering configuration file
    -	--old-header: old Pajé header
    - --basic-header: basic Pajé header
    -	-s --strict: check more strictly the trace integrity (increases computation duration and memory consumption)
