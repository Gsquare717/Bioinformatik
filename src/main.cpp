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
#include <filesystem> // Für Verzeichnisüberprüfung (optional)

void outputHelp() {
    std::cout << "Nutze \"./Assembler -Kommandozeilenparameter\"\n\n"
              << "Du kannst folgende Kommandozeilenparameter nutzen:\n"
              << "-h / --help: \t\t Gibt diesen Hilfstext aus.\n"
              << "-f / --fasta <FILE>:\t Liest die angegebene FASTA Datei ein.\n"
              << "-s / --save <DIRECTORY>:\t Speichert alle Zwischenschritte im angegebenen Ordner (optional).\n"
              << std::endl;
}

int main(int argc, char* argv[]) {
    bool save = false;
    std::string saveDirectory;

    if (argc <= 1) { // Kein Kommandozeilenparameter
        outputHelp();
        return 1;
    }

    if (std::string(argv[1]) != "-f" && std::string(argv[1]) != "--fasta") {
        outputHelp();
        return 1;
    }

    std::ifstream fastaFile(argv[2]);
    if (!fastaFile) {
        std::cerr << "Input-Datei nicht erkannt: " << argv[2] << std::endl;
        outputHelp();
        return 1;
    }

    if (argc > 3 && (std::string(argv[3]) == "--save" || std::string(argv[3]) == "-s")) {
        save = true;
        saveDirectory = argv[4];
        // Optional: Überprüfung, ob das Verzeichnis existiert
        if (!std::filesystem::is_directory(saveDirectory)) {
            std::cerr << "Output-Directory nicht erkannt: " << argv[4] << std::endl;
            outputHelp();
            return 1;
        }
    }

    // Verarbeite FASTA-Datei
    std::vector<Sequence<Alphabet::DNA>> dnaSequences;
    std::string line, comment, currentSequence;

    while (std::getline(fastaFile, line)) {
        if (line.empty()) continue; // leere Zeilen ignorieren

        if (line[0] == '>') { // Neue Sequenz
            comment = line.substr(1);
            if (!currentSequence.empty()) {
                auto seq = Sequence<Alphabet::DNA>::fromString(currentSequence);
                seq.setComment(comment);
                dnaSequences.push_back(seq);
                currentSequence.clear(); // Für die nächste Sequenz
            }
        } else {
            currentSequence += line; // Füge Sequenzzeilen hinzu
        }
    }

    // Füge die letzte Sequenz hinzu, falls vorhanden
    if (!currentSequence.empty()) {
        auto seq = Sequence<Alphabet::DNA>::fromString(currentSequence);
        seq.setComment(comment);
        dnaSequences.push_back(seq);
    }

    Assembler assembler(dnaSequences); // Erstellt den Overlap-Graphen
    assembler.buildEdges(); // Fügt Kanten hinzu

    std::cout << "Start-Graph: \n" << assembler.getGraph();
    int i = 0;
    while (assembler.getGraph().numNodes() > 1) { // || i < 10 Am Ende entfernen
        if (save) {
            std::string savePath = saveDirectory + "/step_" + std::to_string(i++) + ".dot";
            std::ofstream saveFile(savePath);
            if (!saveFile) {
                std::cerr << "Fehler beim Erstellen der Zwischenschritt-Datei: " << savePath << std::endl;
                return 1;
            }
            saveFile << assembler.getGraph();
            saveFile.close();
        }
        // Für Debugging:  std::cout << "\n\nDatei Schritt: " << i << " Anzahl der Knoten: " << assembler.getGraph().numNodes() << std::endl; // Am Ende entfernen
        assembler.joinLargestEdge();
        // Für Debugging:  if(i > 10) return 1; // Am Ende entfernen
    }

    // Finale assemblierte Sequenz ausgeben
    std::cout << "Assemblierte Sequenz:\n\n" << assembler.assemble().toString() << std::endl;
    return 0;
}
