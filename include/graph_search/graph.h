#ifndef GRAPH_SEARCH_GRAPH_H
#define GRAPH_SEARCH_GRAPH_H

#include <graph_search/node.h>

namespace graph_search{
  class Planner{
  public:
    bool search();
    void addNodes2Graph(std::vector<std::shared_ptr<Node> > nodes);
    std::shared_ptr<Node> goal() {return this->goal_;}
    int& maxExtendNum() {return this->maxExtendNum_;}

    virtual bool isGoalSatisfied(std::shared_ptr<Node> node) = 0;
    virtual void calcHeuristic(std::shared_ptr<Node> node) = 0;
    virtual std::vector<std::shared_ptr<Node> > gatherAdjacentNodes(std::shared_ptr<Node> extend_node) = 0;
  private:
    std::vector<std::shared_ptr<Node> > graph_;
    std::shared_ptr<Node> goal_;
    int maxExtendNum_ = 1e3;
  };
}

#endif
