#include <iostream>
#include <graph_search/graph.h>
#include <algorithm>

namespace graph_search{
  bool Planner::search() {
    if (this->graph_.size() < 1) {
      std::cerr << "[graph_search] error. graph is empty!" << std::endl;
      return false;
    }

    for (int i=0; i<this->graph_.size(); i++) this->calcHeuristic(this->graph_[i]);
    std::sort(graph_.begin(), graph_.end(),
	      [](const std::shared_ptr<Node>& a, const std::shared_ptr<Node>& b) {
		return a->heuristic() < b->heuristic();
	      });

    int iter = 0;
    while (iter < this->maxExtendNum_) {
      if (this->debugLevel_ >= 1) std::cerr << "[graph_search] search iter : " << iter << " graph size : " << this->graph_.size() << std::endl;

      iter++;
      std::shared_ptr<Node> extend_node = this->graph_.front();
      std::vector<std::shared_ptr<Node> > adjacent_nodes = this->gatherAdjacentNodes(extend_node);
      std::shared_ptr<Node> goal_node = nullptr;
      for (int i=0; i<adjacent_nodes.size(); i++) {
	if(this->isGoalSatisfied(adjacent_nodes[i])){
	  goal_node = adjacent_nodes[i];
	  break;
	}
        this->calcHeuristic(adjacent_nodes[i]);
      }

      if (goal_node) {
	this->goal_ = goal_node;
	break;
      }
      this->addNodes2Graph(adjacent_nodes);
    }

    if (this->goal_) {
      return true;
    } else {
      return false;
    }
  }

  void Planner::addNodes2Graph(std::vector<std::shared_ptr<Node> > nodes) {
    this->graph_.insert(graph_.end(), nodes.begin(), nodes.end());
    std::sort(graph_.begin(), graph_.end(),
	      [](const std::shared_ptr<Node>& a, const std::shared_ptr<Node>& b) {
		return a->heuristic() < b->heuristic();
	      });
  }
}
