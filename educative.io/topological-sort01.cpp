using namespace std;

#include <iostream>
#include <queue>
#include <unordered_map>
#include <vector>

class TaskScheduling {
 public:
  static bool isSchedulingPossible(int tasks, const vector<vector<int>>& prerequisites) {

    vector<int> tasksOrder; // final result of all scheduled items in order
    unordered_map<int/*node #*/, int /*current indegree*/> indegree;

    // 1. build graph/adjancency list
    // 2. build a map of indegree
    unordered_map<int, vector<int>> graph;
    for (int i = 0; i < prerequisites.size(); i++)
    {
      // prereq: [[0]->[x, y], [1] -> [a, b, x]]
      // [0, x], [0, y], [1, a], [1, b], [1, x]]
      graph[prerequisites[i][0]].push_back(prerequisites[i][1]);

      // update indegree also side by side
      indegree[prerequisites[i][1]]++;
    }

    // 3. start processing
    // select indegree with zero and push into the queue
    queue<int> q;

    // -> first pass to select entry point of graph - once
    for (int i = 0; i < indegree.size(); i++)
    {
      if (indegree[i] == 0)
      {
        q.push(i);
      }
    }

    // -> next selection will be in loop while processing the quuee
    while (!q.empty())
    {
      /// take out of quuee (indegree is already zero), add to tasksOrder .. so dequeque order is task schedule order

      int v = q.front();
      q.pop();
      tasksOrder.push_back(v);

      // -> change the indegree of all reachable vertices from v
      vector<int>& children = graph[v];
      for (int c = 0; c < children.size(); c++)
      {
        int& child = children[c];
        if (indegree[child] <= 0)
        {
          continue;
        }

        indegree[child]--;

        // -> add those vertices if their indegree has reached to 0 to quuee for next roundf of processing
        if (indegree[child] == 0)
        {
          q.push(child);
        }
      }
    }

    // 4. if stil some items left in in-degree map then we have cycles and we cannot schedule the tasks
    return tasksOrder.size() == tasks;
  }
};

int main(int argc, char* argv[]) {
  bool result = TaskScheduling::isSchedulingPossible(
      3, vector<vector<int>>{vector<int>{0, 1}, vector<int>{1, 2}});
  cout << "Tasks execution possible: " << result << endl;

  result = TaskScheduling::isSchedulingPossible(
      3, vector<vector<int>>{vector<int>{0, 1}, vector<int>{1, 2}, vector<int>{2, 0}});
  cout << "Tasks execution possible: " << result << endl;

  result = TaskScheduling::isSchedulingPossible(
      6, vector<vector<int>>{vector<int>{2, 5}, vector<int>{0, 5}, vector<int>{0, 4},
                             vector<int>{1, 4}, vector<int>{3, 2}, vector<int>{1, 3}});
  cout << "Tasks execution possible: " << result << endl;
}
