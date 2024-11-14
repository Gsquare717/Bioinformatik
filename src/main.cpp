#include "Sequence.h"
#include "DNA.h" // Klassen DNA, RNA und Peptide müssen implementiert sein
#include "Assembler.h"
#include "Graph.h"
#include <iostream>
#include <fstream>
#include <stdexcept>
#include <vector>
#include <string>
#include <limits>

void processFastaFile(const std::string& fastaFileName)
{
    const std::string& type = "dna";
    std::ifstream fastaFile(fastaFileName);
    if (!fastaFile)
    {
        std::cerr << "Error opening file: " << fastaFileName << std::endl;
        return;
    }

    std::vector<Sequence<Alphabet::DNA>> dnaSequences;
    
    std::string line;
    std::string comment;
    Sequence<Alphabet::DNA> seq;
    std::string currentSequence;  // To store the sequence lines

    while (std::getline(fastaFile, line)) {
        if (line.empty()) continue;     // Überspringe leere line

        if (line[0] == '>') {           // Neue Sequenz 
        comment = line.substr(1);
            if (!currentSequence.empty()) {
                seq = Sequence<Alphabet::DNA>::fromString(currentSequence);
                /**
                 * TODO 
                 * Sequenz wird Assembler-Assembler() hinzugefügt
                 * Overlap-Edges wird über Assembler-buildEdges() hinzugefügt
                 * Ausgabe über Graph-operator<<
                 * */
            }
            currentSequence.clear();    // Reset for the next sequence
        } else {
            currentSequence += line;    // Append
        }
    }
}

// Hauptprogramm
int main(int argc, char* argv[])
{
    if (argc < 3)
    {
        std::cerr << "Usage: " << argv[0] << " <fasta_file> <output.dot>" << std::endl;
        return 1;
    }

    // Datei einlesen
    std::ifstream fastaFile(argv[1]);
    if (!fastaFile)
    {
        std::cerr << "Error: Could not open file " << argv[1] << std::endl;
        return 1;
    }

    // Es wird nur DNA akzeptiert, da "./convert fragments.fasta fragments.dot" Alphabet nicht spezifiziert wird
    std::ofstream out(argv[2]);
    if (!out.is_open()) {
        std::cerr << "Fehler beim Öffnen der Datei zum Schreiben: " << argv[2] << std::endl;
        return 1;
    }

    processFastaFile(argv[1]);

    return 0;
}


/* Alte Version

template <typename Alpha>
double calculateBasePercentage(const Sequence<Alpha>& seq, typename Alpha::Characters base)
{
    auto stats = seq.statistics();
    size_t baseCount = stats[base];
    return static_cast<double>(baseCount) / seq.size() * 100;
}

void processFastaFile(const std::string& fastaFileName, const std::string& type)
{
    std::ifstream fastaFile(fastaFileName);
    if (!fastaFile)
    {
        std::cerr << "Error opening file: " << fastaFileName << std::endl;
        return;
    }

    std::vector<Sequence<Alphabet::DNA>> dnaSequences;
    size_t sequenceCount = 0;
    size_t seqLength = 0;
    size_t longestSeq = 0;
    size_t shortestSeq = std::numeric_limits<size_t>::max();
    size_t totalA = 0, totalC = 0, totalT = 0, totalG = 0;
    
    std::string line;
    std::string comment;
    Sequence<Alphabet::DNA> seq;
    std::string currentSequence;  // To store the sequence lines

    while (std::getline(fastaFile, line)) {
        if (line.empty()) continue;  // Skip empty lines

        if (line[0] == '>') { // Found a new sequence starting 
            comment = line.substr(1);
            sequenceCount++;
            seqLength = 0;
            if (!currentSequence.empty()) { // Process the previous sequence
                seq = Sequence<Alphabet::DNA>::fromString(currentSequence);
                dnaSequences.push_back(seq);
                seqLength += seq.size();
                longestSeq = std::max(longestSeq, seqLength);
                shortestSeq = std::min(shortestSeq, seqLength);
                totalA += calculateBasePercentage<Alphabet::DNA>(seq, Alphabet::DNA::Characters::A);
                totalC += calculateBasePercentage<Alphabet::DNA>(seq, Alphabet::DNA::Characters::C);
                totalT += calculateBasePercentage<Alphabet::DNA>(seq, Alphabet::DNA::Characters::T);
                totalG += calculateBasePercentage<Alphabet::DNA>(seq, Alphabet::DNA::Characters::G);
            }
            currentSequence.clear();  // Reset for the next sequence
        } else {
            currentSequence += line;  // Append sequence line
        }
    }

    // Process the last sequence in the file
    if (!currentSequence.empty()) {
        seq = Sequence<Alphabet::DNA>::fromString(currentSequence);
        dnaSequences.push_back(seq);
        size_t seqLength = seq.size();
        sequenceCount++;
        longestSeq = std::max(longestSeq, seqLength);
        shortestSeq = std::min(shortestSeq, seqLength);
        totalA += calculateBasePercentage<Alphabet::DNA>(seq, Alphabet::DNA::Characters::A);
        totalC += calculateBasePercentage<Alphabet::DNA>(seq, Alphabet::DNA::Characters::C);
        totalT += calculateBasePercentage<Alphabet::DNA>(seq, Alphabet::DNA::Characters::T);
        totalG += calculateBasePercentage<Alphabet::DNA>(seq, Alphabet::DNA::Characters::G);
    }

    // Output the results
    std::cout << "Number of sequences: " << sequenceCount << std::endl;
    std::cout << "Longest sequence length: " << longestSeq << std::endl;
    std::cout << "Shortest sequence length: " << shortestSeq << std::endl;
    std::cout << "Percentage of A bases: " << (totalA / static_cast<double>(sequenceCount)) << "%" << std::endl;
    std::cout << "Percentage of C bases: " << (totalC / static_cast<double>(sequenceCount)) << "%" << std::endl;
    std::cout << "Percentage of T/U bases: " << (totalT / static_cast<double>(sequenceCount)) << "%" << std::endl;
    std::cout << "Percentage of G bases: " << (totalG / static_cast<double>(sequenceCount)) << "%" << std::endl;
}

// Hauptprogramm
int main(int argc, char* argv[])
{
    if (argc < 3)
    {
        std::cerr << "Usage: " << argv[0] << " <fasta_file> <dna|rna|peptide>" << std::endl;
        return 1;
    }

    // Datei einlesen
    std::ifstream fastaFile(argv[1]);
    if (!fastaFile)
    {
        std::cerr << "Error: Could not open file " << argv[1] << std::endl;
        return 1;
    }

    // Sequenztyp festlegen
    std::string type = argv[2];
    
    if (type == "dna") {
        processFastaFile(argv[1], "dna");
    } else if (type == "rna") {
        processFastaFile(argv[1], "rna");
    } else if (type == "peptide") {
        processFastaFile(argv[1], "peptide");
    } else {
        std::cerr << "Error: Unknown sequence type. Please use 'dna', 'rna', or 'peptide'." << std::endl;
        return 1;
    }

    return 0;
}*/