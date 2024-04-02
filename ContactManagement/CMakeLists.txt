cmake_minimum_required(VERSION 3.27)
project(ContactManagement)

set(CMAKE_CXX_STANDARD 17)

add_executable(ContactManagement main.cpp
        backend/structures/HashTable.cpp
        backend/structures/HashTable.h
        backend/structures/Node.cpp
        backend/structures/Node.h
        backend/structures/AVLTree.cpp
        backend/structures/AVLTree.h
        backend/structures/HashTableData.cpp
        backend/structures/HashTableData.h
        backend/Parser.cpp
        backend/Parser.h
        backend/Reports.cpp
        backend/Reports.h
        backend/Menu.cpp
        backend/Menu.h
)
