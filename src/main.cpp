Das könnte für die main.cpp klappen, aber ich konnte es jetzt nicht mehr testen:


#include "Sequence.h"
#include "DNA.h"
#include "Assembler.h"
#include "Graph.h"
#include <iostream>
#include <fstream>
#include <stdexcept>
#include <vector>
#include <string>
#include <limits>

int main(int argc, char* argv[]) {
    if (argc < 3) {
        std::cerr << "Usage: " << argv[0] << " <fasta_file> <output.dot_file>" << std::endl;
        return 1;
    }

    std::ifstream fastaFile(argv[1]);
    if (!fastaFile) {
        std::cerr << "Input-Datei nicht erkannt: " << argv[1] << std::endl;
        return 1;
    }

    std::vector<Sequence<Alphabet::DNA>> dnaSequences;
    std::string line;
    std::string comment;
    Sequence<Alphabet::DNA> seq;
    std::string currentSequence;

    while (std::getline(fastaFile, line)) {
        if (line.empty()) continue;     // leere Zeilen

        if (line[0] == '>') {           // Neue Sequenz
            comment = line.substr(1);
            if (!currentSequence.empty()) {
                seq = Sequence<Alphabet::DNA>::fromString(currentSequence);
                seq.setComment(comment);
                dnaSequences.push_back(seq);
                currentSequence.clear(); // für nächste Sequenz
            }
        } else {
            currentSequence += line;   
        }
    }
    
    // Fügt die letzte gelesene Sequenz hinzu, wenn vorhanden
    if (!currentSequence.empty()) {
        seq = Sequence<Alphabet::DNA>::fromString(currentSequence);
        seq.setComment(comment);
        dnaSequences.push_back(seq);
    }

    Assembler assembler(dnaSequences); // erstellt Knoten aus Fragmenten
    assembler.buildEdges(); // Kanten werden hinzugefügt

    // Ausgabe in Datei im Format
    std::ofstream output(argv[2]);
    if (!output) {
        std::cerr << "Fehler beim generieren der Output-Datei: " << argv[2] << std::endl;
        return 1;
    }

    output << assembler.getGraph();
    output.close();

    return 0;
}
