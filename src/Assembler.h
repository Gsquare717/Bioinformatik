#ifndef BIOINFO1_ASSEMBLER_H
#define BIOINFO1_ASSEMBLER_H

#include "Graph.h"
#include "Sequence.h"
#include "DNA.h"

#include <unordered_map>

class Assembler
{
  public:
  	/**
  	 * Make things pretty.
  	 */
	using Seq = Sequence<Alphabet::DNA>;
	using OGraph = Graph<Seq>;

	/**
	 * Creates an overlap graph.
	 * TODO-done
	 */
	Assembler(const std::vector<Assembler::Seq>& sequences) {
		for (const auto& seq : sequences) {
			graph_.addNode(seq);
		}
		buildEdges();
	}	

	/**
	 * Getter for graph_
	 * TODO-done
	 */
	OGraph& getGraph(){
		return graph_;
	}

  private:
	/**
	 * Initializes the appropriate Edges between the given nodes to create
	 * the Overlay-Graph.
	 * TODO-done
	 */
	void buildEdges() {
    for (auto n1 = graph_.beginNodes(); n1 != graph_.endNodes(); ++n1) {
        for (auto n2 = graph_.beginNodes(); n2 != graph_.endNodes(); ++n2) {
            // Berechne die Überlappung zwischen den Sequenzen
            size_t overlap_len = n1->label.overlap(n2->label);

            if (overlap_len > 0) {
                graph_.addEdge(&(*n1), &(*n2), overlap_len);
            }
        }
    }
}

	OGraph graph_;

	std::vector<OGraph::Edge> edges_;
	std::unordered_map<OGraph::Node*, bool> valid_nodes_;
};

#endif // BIOINFO1_ASSEMBLER_H

