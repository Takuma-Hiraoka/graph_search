#include <iostream>
#include <graph_search/graph.h>
#include <algorithm>

namespace graph_search{
  bool Graph::search() {
    if (this->graph_.size() < 1) {
      std::cerr << "[graph_search] error. graph is empty!" << std::endl;
      return false;
    }
    int iter = 0;
    while (iter < this->maxExtendNum_) {
      iter++;
      std::shared_ptr<Node> extend_node = this->graph_.front();
      std::vector<std::shared_ptr<Node> > adjacent_nodes = Graph::gatherAdjacentNodes(extend_node);
      std::shared_ptr<Node> goal_node = nullptr;
      for (int i=0; i<adjacent_nodes.size(); i++) {
	if(Graph::isGoalSatisfied(adjacent_nodes[i])){
	  goal_node = adjacent_nodes[i];
	  break;
	}
	adjacent_nodes[i]->calcHeuristic();
      }

      if (goal_node) {
	this->goal_ = goal_node;
	break;
      }
      Graph::addNodes(adjacent_nodes);
    }

    if (this->goal_) {
      return true;
    } else {
      return false;
    }
  }

  void Graph::addNodes(std::vector<std::shared_ptr<Node> > nodes) {
    this->graph_.insert(graph_.end(), nodes.begin(), nodes.end());
    std::sort(graph_.begin(), graph_.end(),
	      [](const std::shared_ptr<Node>& a, const std::shared_ptr<Node>& b) {
		return a->heuristic() < b->heuristic();
	      });
  }

  bool Graph::isGoalSatisfied(std::shared_ptr<Node> node) {
    return true;
  }
}
