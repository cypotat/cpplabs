// Ориентированный граф задан и хранится матрицей смежности.
// В файле задается вершина, с которой начинается обход.

// Построить дерево обхода с помощью bfs.
// После того, как известно дерево обхода, необходимо определить типы ребер
// направленного графа.

// Ребра древа обхода - это ребра, которые входят в дерево обхода.
// Прямые ребра - это ребра, которые ведут из родительской вершины в дочернюю.
// Обратные ребра - ребра, ведущие от потомка к предку.
// Поперечные ребра - ребра, не связывающие предков и потомков.

// Вывести на экран типы ребер.

// pseudocode from https://stackoverflow.com/a/29710587/15301038

//   foreach edge(a,b) in BFS order:
//     if !b.known then:
//       b.known = true
//       b.depth = a.depth+1
//       edge type is TREE
//       continue to next edge
//     while (b.depth > a.depth): b=parent(b)
//     while (a.depth > b.depth): a=parent(a)
//     if a==b then:
//       edge type is BACK
//     else:
//       edge type is CROSS

#include <fstream>
#include <iostream>
#include <queue>
#include <stdexcept>
#include <vector>
#include <map>

using namespace std;

class Graph {
 private:
  // Матрица смежности
  vector<vector<int>> adj;
  // Номер вершины, с которой начинается обход
  int root;
  // глубина вершины
  vector<int> depth;
  // родитель вершины
  vector<int> parent;

  // список ребер
  // ((начало, конец), тип)
  // типы ребер:
  // 0 - дерево
  // 1 - обратное
  // 2 - кросс
  // vector<vector<int>> edges;
  map<pair<int, int>, int> edges;

 public:
  // Конструктор
  Graph(string filename) {
    ifstream fin(filename);
    if (!fin.is_open()) {
      throw runtime_error("File not found");
    }
    fin >> root;
    // Инициализируем матрицу смежности
    adj.resize(0);
    // Считываем матрицу смежности
    while (!fin.eof()) {
      vector<int> row;
      int x;
      while (fin >> x) {
        row.push_back(x);
        if (fin.peek() == '\n') break;
      }
      adj.push_back(row);
    }

    depth.resize(adj.size());
    parent.resize(adj.size());
  }

  // Обход в ширину
  void bfs() {
    // Очередь для хранения вершин
    queue<int> q;
    // Вектор для хранения информации о посещении вершины
    vector<bool> visited(adj.size(), false);
    // Начинаем с корня
    q.push(root);
    visited[root] = true;
    depth[root] = 0;
    parent[root] = -1;
    // Пока очередь не пуста
    while (!q.empty()) {
      // Извлекаем вершину
      int v = q.front();
      q.pop();
      // Просматриваем все вершины, смежные с v
      for (int i = 0; i < adj[v].size(); i++) {
        // Если есть ребро и вершина еще не посещена
        if (adj[v][i] == 1 && !visited[i]) {
          // Добавляем ее в очередь
          q.push(i);
          visited[i] = true;
          depth[i] = depth[v] + 1;
          parent[i] = v;
          // Выводим ребро
          // cout << v << " " << i << " TREE" << endl;
          edges.insert({{v, i}, 0});
        }
      }
    }
  }

  void printEdgeTypes() {
    for (int i = 0; i < adj.size(); i++) {
      for (int j = 0; j < adj[i].size(); j++) {
        if (adj[i][j] == 1 && edges.find({i, j}) == edges.end()) {
          // copy of i and j
          int a = i;
          int b = j;
          // while (b.depth > a.depth): b=parent(b)
          while (depth[b] > depth[a]) {
            b = parent[b];
          }
          // while (a.depth > b.depth): a=parent(a)
          while (depth[a] > depth[b]) {
            a = parent[a];
          }
          // if a==b then:
          //   edge type is BACK
          if (a == b) {
            edges.insert({{i, j}, 1});
            // cout << i << " " << j << " BACK" << endl;
          } else {
            //   edge type is CROSS
            edges.insert({{i, j}, 2});
            // cout << i << " " << j << " CROSS" << endl;
          }
        }
      }
    }

    for (auto edge : edges) {
      cout << edge.first.first << " " << edge.first.second << " ";
      switch (edge.second) {
        case 0:
          cout << "TREE" << endl;
          break;
        case 1:
          cout << "BACK" << endl;
          break;
        case 2:
          cout << "CROSS" << endl;
          break;
      }
    }
  }
};

int main() {
  // cout << "test" << endl;
  Graph g("D:/Projects/SUAI-Labs/Semester_3/Lab_20/graph.txt");
  // cout << "test" << endl;
  g.bfs();
  g.printEdgeTypes();
  // cout << "test" << endl;

  return 0;
}
