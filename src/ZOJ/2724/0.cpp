#include <iostream>
#include <queue>
using namespace std;
struct Node {
  string name;
  int parameter, priority, id;
  bool operator<(const Node &oth) const {
    return priority == oth.priority ? id > oth.id : priority > oth.priority;
  }
};
priority_queue<Node> pq;
int main() {
  string op;
  int id = 0;
  while (cin >> op)
    if (op == "PUT") {
      Node s;
      cin >> s.name >> s.parameter >> s.priority;
      s.id = ++id;
      pq.push(s);
    } else {
      if (pq.empty()) cout << "EMPTY QUEUE!" << endl;
      else {
        cout << pq.top().name << " " << pq.top().parameter << endl;
        pq.pop();
      }
    }
}
