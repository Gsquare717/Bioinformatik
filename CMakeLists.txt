cmake_minimum_required(VERSION 3.22.1)

# Optionen an den Compiler
set(CXX_FLAGS
	-std=c++17               # Verwende den C++17 Standard
	-pedantic                # Achte auf genauere Einhaltung des Standards
	-Wall                    # Aktiviere alle Warnungen
)

project(01_Sequence)

add_definitions(${CXX_FLAGS})

# Erstelle die Bibliothek "sequence"
# Bibliotheken sind Codesammlungen, die von mehreren
# Programmen geteilt werden können.
#
# Dies ist für unser Projekt nötig, da wir sowohl
# Unittests, als auch eine ausführbare Anwendung
# erzeugen wollen.
add_library(sequence SHARED
	src/DNA.h
	src/DNA.cpp
	src/InvalidCharacter.h
	src/InvalidCharacter.cpp
	src/Peptide.h
	src/Peptide.cpp
	src/RNA.h
	src/RNA.cpp
	src/Sequence.h
)

# Erstelle die ausführbare Datei.
add_executable(main src/main.cpp)
target_link_libraries(main sequence ${CIP_STD_LIBS})

##############
# GTEST
##############
# Aktiviere die Unittestfunktionalität von CMake.
enable_testing()

# Füge die Google Test Bibliothek zum Projekt hinzu.
# Je nach Betriebssystem muss der Pfad zu gtest angepasst werden
set(GTEST_SRC_DIR /usr/src/gtest/)
add_subdirectory(${GTEST_SRC_DIR} "gtest")

include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

add_executable(runTests test/test_main.cpp test/test_sequence.cpp 
	src/DNA.h
	src/DNA.cpp
	src/InvalidCharacter.h
	src/InvalidCharacter.cpp
	src/Peptide.h
	src/Peptide.cpp
	src/RNA.h
	src/RNA.cpp
	src/Sequence.h
)
target_link_libraries(runTests gtest gtest_main)

#add_test(NAME that-test-I-made COMMAND runUnitTests)
#add_test(that-other-test-I-made runUnitTests)

