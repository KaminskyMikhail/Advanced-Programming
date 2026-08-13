cmake_minimum_required(VERSION 3.14) 

project(PROJ)

#ищем библиотеку для подключения Catch2 из vcpkg: 
find_package(Catch2 CONFIG REQUIRED)

#добавляем запускаемый файл с именем проекта
add_executable(PROJ Source.cpp)

#линкуем библиотеки Catch2 
target_link_libraries(PROJ PRIVATE Catch2::Catch2 Catch2::Catch2WithMain)