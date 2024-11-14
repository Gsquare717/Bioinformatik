cmake_minimum_required(VERSION 3.22.1)

# Optionen an den Compiler
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -pedantic -Wall")


project(Sequence-und-Graph)

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
	src/Graph.h       	# Durch Projekt 02 Graph
    src/Assembler.h 	# Durch Projekt 02 Graph
    src/Assembler.cpp	# Durch Projekt 02 Graph
)

# Erstelle die ausführbare Datei.
# add_executable(main src/main.cpp)		# Aus dem alten Projekt
add_executable(convert src/Assembler.cpp)	# Für Projekt 02 Graph
target_link_libraries(convert sequence ${CIP_STD_LIBS})

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
	# test/test_main.cpp		# Wenn wir das brauchen?
	# test/test_sequence.cpp    # Wenn wir das brauchen? 
	src/DNA.h
	src/DNA.cpp
	src/InvalidCharacter.h
	src/InvalidCharacter.cpp
	src/Peptide.h
	src/Peptide.cpp
	src/RNA.h
	src/RNA.cpp
	src/Sequence.h
	src/Graph.h      	# Durch Projekt 02 Graph
    src/Assembler.h   	# Durch Projekt 02 Graph
    src/Assembler.cpp	# Durch Projekt 02 Graph
)
target_link_libraries(runTests gtest gtest_main)

#add_test(NAME that-test-I-made COMMAND runUnitTests)
#add_test(that-other-test-I-made runUnitTests)

