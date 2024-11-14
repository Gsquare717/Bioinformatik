#include "Assembler.h"

Assembler::Assembler(const std::vector<Assembler::Seq>& sequences) {
    for (const auto& seq : sequences) { // Erstellt einen graph wobei die einzelnen sequencen nodes sind.
        graph_.addNode(seq);
    }

    buildEdges(); // Kanten zwischen Nodes mit Overlap werden hinzugefügt.
}

Assembler::OGraph& Assembler::getGraph() {
    return graph_;
}

void Assembler::buildEdges() {
    for (auto it1 = graph_.beginNodes(); it1 != graph_.endNodes(); ++it1) {
        for (auto it2 = graph_.beginNodes(); it2 != graph_.endNodes(); ++it2) {
            if (it1 == it2) { // Kante wäre zwischen dem selben Knoten
                continue; // überspringen
            }

            size_t overlap_length = it1->label.overlap(it2->label); // Overlap berechnnen

            if (overlap_length > 0) {
                graph_.addEdge(&*it1, &*it2, overlap_length); // Kante hinzufügen
            }
        }
    }
}