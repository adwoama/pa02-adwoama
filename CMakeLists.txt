cmake_minimum_required(VERSION 3.14)
project(21s-auto-idx)
set (EXE_NAME indexer)

##########################################
# Students, edit the items below.  In the quotes,
# put the names of the input files as they should appear
# in the argv param to main.
# Example:
#   set (input01 "train_data.csv")
#   set (input02 "train_target.csv")
# etc....

set (input01 "input02.txt")
set (input02 "input01.txt")


#
##########################################

# Copy data files to build dir
foreach(file IN LISTS input01 input02)
    configure_file(${file} ${file} COPYONLY)
endforeach()

set(CMAKE_CXX_STANDARD 17)
#set(CMAKE_CXX_FLAGS_DEBUG "-O3")
add_executable(${EXE_NAME} main.cpp DSVector.h Indexer.cpp Indexer.h catch.hpp testDSVector.cpp IndexEntry.cpp IndexEntry.h)
