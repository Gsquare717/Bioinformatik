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
	Assembler(const std::vector<Assembler::Seq>& sequences);

	/**
	 * Getter for graph_
	 * TODO-done
	 */
	OGraph& getGraph();

	/**
	 * Initializes the appropriate Edges between the given nodes to create
	 * the Overlay-Graph.
	 * TODO-done
	 */
	void buildEdges();

	/**
	 * Zeigen Start- und Zielknoten der übergebenen Kante noch auf entsprechende Knoten im Graphen?
	 * TODO in Assembler.cpp
	 */
	bool isValid(const OGraph::Edge& e);

	/**
	 * Start- und Zielknoten der Kante mit maximalem Kantengewicht zu einem Knoten zusammenfassen (contractEdge).
	 * Neuer Knoten soll die assemblierte Sequenz zugewiesen werden.
	 * TODO in Assembler.cpp
	 */
	void joinLargestEdge();

	/**
	 * Wendet Greedy-Algorithmus an und liefert die entstandene Sequenz zurück.
	 * TODO in Assembler.cpp
	 */
	Seq assemble();

private:
	OGraph graph_;

	std::vector<OGraph::Edge> edges_;
	std::unordered_map<OGraph::Node*, bool> valid_nodes_;
};

#endif // BIOINFO1_ASSEMBLER_H