#include "Assembler.h"
#include "Sequence.h"

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

// Für die Übung 4
using Seq = Sequence<Alphabet::DNA>;
using OGraph = Graph<Seq>;

/**
* Zeigen Start- und Zielknoten der übergebenen Kante noch auf entsprechende Knoten im Graphen?
* TODO
*/
bool Assembler::isValid(const OGraph::Edge& e) {
    for (auto it = graph_.beginNodes(); it != graph_.endNodes(); ++it) {
        if (&(*it) == e.source || &(*it) == e.target) {
            return true; // Quell- und Zielknoten existieren noch
        }
    }
    return false; // Einer der Knoten wurde entfernt
}

/**
 * Start- und Zielknoten der Kante mit maximalem Kantengewicht zu einem Knoten zusammenfassen (contractEdge).
 * Neuer Knoten soll die assemblierte Sequenz zugewiesen werden.
 * TODO
 */
void Assembler::joinLargestEdge() {
    if (graph_.numNodes() <= 1) {
        std::cout << "Keine Knoten zum verknüpfen! Anzahl an verfügbaren Knoten: " << graph_.numNodes() << std::endl;
        return;
    }
    OGraph::Edge* largest_edge = nullptr;
    size_t max_weight = 0;

    // Sucht die Kante mit dem größten Gewicht
    for (auto node_it = graph_.beginNodes(); node_it != graph_.endNodes(); ++node_it) {
        for (const auto& edge : node_it->out_edges) {
            if (edge.second > max_weight) {
                largest_edge = new OGraph::Edge(&(*node_it), edge.first, edge.second);
                max_weight = edge.second;
            }
        }
    }

    if (!largest_edge) {
        std::cout << "Keine gültige Kante gefunden" << std::endl;
        return; // Keine Kante gefunden
    }

    // Am Ende entfernen
    // Für Debugging:  std::cout << "Verarbeite größte Kante: " << largest_edge->source->label.toString()
    // Für Debugging:            << " -> " << largest_edge->target->label.toString()
    // Für Debugging:            << " Gewicht: " << largest_edge->weight << std::endl;


    // Assemblierte Sequenz erstellen
    Seq new_sequence = Seq::fromString(largest_edge->source->label.toString() + largest_edge->target->label.toString().substr(max_weight));

    // Kantenkontraktion durchführen
    OGraph::Node* new_node = graph_.contractEdge(*largest_edge);
    new_node->label = new_sequence; // Neue Sequenz dem neuen Knoten zuweisen

    // Für Debugging:  std::cout << "Knotenanzahl nach Kantenkontraktion: " << graph_.numNodes() << std::endl;  // Am Ende entfernen

    delete largest_edge; // Speicher freigeben
}

/**
 * Wendet Greedy-Algorithmus an und liefert die entstandene Sequenz zurück.
 * TODO
 */
Seq Assembler::assemble() {
    while (graph_.numNodes() > 1) {         // Reduziere den Graphen durch Kantenkontraktion
        joinLargestEdge(); 
    }

    if (graph_.numNodes() == 1) {           // Letzter Knoten
        return graph_.beginNodes()->label;  
    }
    return Seq();                           // Falls der Graph leer ist
}