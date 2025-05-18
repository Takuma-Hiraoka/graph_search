#ifndef GRAPH_SEARCH_NODE_H
#define GRAPH_SEARCH_NODE_H

#include <memory>
#include <vector>

namespace graph_search{
  class Node{
  public:
    const std::weak_ptr<Node>& parent() const {return this->parent_;}
    std::weak_ptr<Node>& parent() {return this->parent_;}
    const double& heuristic() const {return heuristic_;}
    double& heuristic() {return heuristic_;}
  private:
    std::weak_ptr<Node> parent_;
    double heuristic_ = 1.0; // smaller better
  };
}

#endif
