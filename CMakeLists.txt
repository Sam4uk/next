cmake_minimum_required(VERSION 3.14)

project(    e2promtools
            VERSION 0.0.0.1
            DESCRIPTION "")

                                                                              
set(CMAKE_CXX_STANDARD 20)  

add_compile_options(
#   -Werror
#   -pedantic-errors

  -Wpedantic

  -Wcast-align
#   -Wcast-qual
#   -Wconversion
#   -Wextra-semi
#   -Wfloat-equal

#   -Wnon-virtual-dtor
#   -Wold-style-cast
#   -Woverloaded-virtual
#   -Wredundant-decls
#   -Wsign-promo
#   -Wall
#   -Wextra  
)


file(WRITE "${PROJECT_BINARY_DIR}/.gitignore" [=[
# this .gitignore file
*.*
*
]=])

add_executable(e2serial
source/main.cxx
)
                                                                       


