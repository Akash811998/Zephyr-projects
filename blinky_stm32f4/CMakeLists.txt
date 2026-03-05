# File: CMakeLists.txt
 
cmake_minimum_required(VERSION 3.20.0)
 
# Locate Zephyr. ZEPHYR_BASE is set automatically by West.
find_package(Zephyr REQUIRED HINTS $ENV{ZEPHYR_BASE})
 
project(blinky)
 
# Add your source file to the 'app' target (always named 'app' in Zephyr)
target_sources(app PRIVATE src/main.c)
