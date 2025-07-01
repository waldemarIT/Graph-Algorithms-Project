#pragma once
#include "Queue.h"
#include "Vector.h"
#include <iostream>
using namespace std;

class Graph {
private:
    Vector<Vector<int>> graph;
    Vector<bool> visited;
    Vector<int> color;
    Vector<int> degrees;
    Vector<Vector<bool>> adjacencyMatrix;  // Adjacency matrix for the graph
    
public:
    Graph(int vertices) : graph(vertices), visited(vertices, false), color(vertices, 0), degrees(vertices, 0), adjacencyMatrix(vertices, false) {}

    //Graph(int vertices) : adjacencyMatrix(vertices, Vector<bool>(vertices, false)) {}

    void dfs(int v) {
        visited[v] = true;
        for (int u : graph[v]) {
            if (!visited[u])
                dfs(u);
        }
    }

    int countComponents(int vertices) {
        visited.assign(vertices, false);
        int componentCount = 0;
        for (int i = 0; i < vertices; i++) {
            if (!visited[i]) {
                dfs(i);
                componentCount++;
            }
        }
        return componentCount;
    }

    void merge(Vector<int>& arr, int left_idx, int middle_idx, int right_idx) {

        int left_sub_array = middle_idx - left_idx + 1;
        int right_sub_array = right_idx - middle_idx;

        Vector<int> Left_temporary_array(left_sub_array), Right_temporary_array(right_sub_array);

        for (int i = 0; i < left_sub_array; i++)
            Left_temporary_array[i] = arr[left_idx + i];

        for (int j = 0; j < right_sub_array; j++)
            Right_temporary_array[j] = arr[middle_idx + 1 + j];

        int i = 0, j = 0, k = left_idx;
        while (i < left_sub_array && j < right_sub_array) {
            if (Left_temporary_array[i] >= Right_temporary_array[j]) {
                arr[k] = Left_temporary_array[i];
                i++;
            }
            else {
                arr[k] = Right_temporary_array[j];
                j++;
            }
            k++;
        }

        while (i < left_sub_array) {
            arr[k] = Left_temporary_array[i];
            i++;
            k++;
        }

        while (j < right_sub_array) {
            arr[k] = Right_temporary_array[j];
            j++;
            k++;
        }
    }

    void mergeSort(Vector<int>& arr, int l_start_idx, int r_end_idx) {
        if (l_start_idx >= r_end_idx) {
            return;
        }
        int middle_idx = l_start_idx + (r_end_idx - l_start_idx) / 2;
        mergeSort(arr, l_start_idx, middle_idx);
        mergeSort(arr, middle_idx + 1, r_end_idx);
        merge(arr, l_start_idx, middle_idx, r_end_idx);
    }

    long long countComplementEdges(int vertices) {
        long long totalEdges = 0;
        long long maxEdges = (long long)vertices * (vertices - 1);

        for (int i = 0; i < vertices; ++i) {
            totalEdges += graph[i].size(); // summary edges from adj list
        }
        totalEdges /= 2;

        return (maxEdges - totalEdges) / 2;
    }

    bool isBipartite_BFS(int start) {
        Queue q;
        q.push(start);
        color[start] = 1; // Starting vertices has 1 - paint

        while (!q.empty()) {
            int v = q.front();
            q.pop();

            for (int i = 0; i < graph[v].size(); i++) {
                int neighbour_vertices_for_v = graph[v][i];
                if (color[neighbour_vertices_for_v] == 0) { // vertices is not painted
                    color[neighbour_vertices_for_v] = -color[v]; // 1 -> -1
                    q.push(neighbour_vertices_for_v);
                }
                else if (color[neighbour_vertices_for_v] == color[v]) { // if neighbour has the same color -> graph is not bipartite
                    return false;
                }
            }
        }
        return true;
    }

    bool isConnected(int u, int v) {
        for (int neighbor : graph[u]) {
            if (neighbor == v) {
                return true;
            }
        }
        return false;
    }

    bool formsC4(int a, int b, int c, int d) {
        // Check for direct connections forming a cycle
        return isConnected(a, b) && isConnected(b, c) && isConnected(c, d) && isConnected(d, a);
    }

    long long countC4Subgraphs(int vertices) {
        int count = 0;
        // Check every combination of four distinct vertices
        for (int a = 0; a < vertices; ++a) {
            for (int b : graph[a]) {
                if (b == a) continue;
                for (int c : graph[b]) {
                    if (c == b || c == a) continue;
                    for (int d : graph[c]) {
                        if (d == c || d == b || d == a) continue;
                        if (isConnected(d, a) && formsC4(a, b, c, d)) {
                            count++;  // Valid C4 cycle found
                        }
                    }
                }
            }
        }
        return count / 64;
    }

    void Coloring(int vertices) {
        Vector<int> colors(vertices, -1);  // Initialize all vertices as uncolored
        colors[0] = 0;  // Assign the first color to the first vertex

        Vector<bool> available(vertices, true);  // Availability of colors

        for (int i = 1; i < vertices; ++i) {
            // local list for save color which's need reset
            Vector<int> toReset;

            // Check colors of all adjacent vertices and mark unavailable colors
            for (int adj : graph[i]) {
                if (colors[adj] != -1 && available[colors[adj]]) {
                    available[colors[adj]] = false;  // Mark the color as used
                    toReset.push_back(colors[adj]);  // add to list for reset 
                }
            }

            // Find the first available color
            int cr;
            for (cr = 0; cr < vertices; cr++) {
                if (available[cr]) break;
            }

            colors[i] = cr; // Assign the found color

            // ????????? ???? ??????????? ???????
            for (int j = 0; j < toReset.size(); ++j) {
                available[toReset[j]] = true;
            }
        }

        // Print the colors assigned to the vertices
        for (int u = 0; u < vertices; ++u) {
            printf("%d ", colors[u] + 1);
        }
        printf("\n");
    }

    int partition(Vector<int>& vertices, int low, int high) {
        int pivot = graph[vertices[high]].size();  // Use last element as pivot
        int i = (low - 1);  // Index of smaller element

        for (int j = low; j <= high - 1; j++) {
            // If current element has a higher degree or same degree but smaller index
            if (graph[vertices[j]].size() > pivot ||
                (graph[vertices[j]].size() == pivot && vertices[j] < vertices[high])) {
                i++;
                swap(vertices[i], vertices[j]);
            }
        }
        swap(vertices[i + 1], vertices[high]);
        return (i + 1);
    }

    void quickSortVerticesByDegree(Vector<int>& vertices, int low, int high) {
        if (low < high) {
            int pivot = partition(vertices, low, high);
            quickSortVerticesByDegree(vertices, low, pivot - 1);
            quickSortVerticesByDegree(vertices, pivot + 1, high);
        }
    }

    void sortVerticesByDegree(Vector<int>& vertices, int size) {
        quickSortVerticesByDegree(vertices, 0, size - 1);
    }

    void LargestFirstColor(int vertices) {
        Vector<int> degreeOrder(vertices);
        for (int i = 0; i < vertices; i++) {
            degreeOrder[i] = i;  // writing indexes
        }

        sortVerticesByDegree(degreeOrder, vertices);

        color.assign(vertices, -1);
        color[degreeOrder[0]] = 0;  // first color for vertices with largest degree

        Vector<bool> available;
        available.resize(vertices, true);

        for (int i = 1; i < vertices; i++) {
            int u = degreeOrder[i];
            for (int adj : graph[u]) {
                if (color[adj] != -1) {
                    available[color[adj]] = false;
                }
            }

            // finding first avaliable color
            int cr;
            for (cr = 0; cr < vertices; cr++) {
                if (available[cr]) break;
            }

            color[u] = cr;  // painted

            // Reseting
            for (int i = 0; i < graph[u].size(); i++) {
                int adj = graph[u][i];
                if (color[adj] != -1) {
                    available[color[adj]] = true;
                }
            }
        }

        for (int i = 0; i < vertices; i++) {
            cout << color[i] + 1 << " ";
        }
        cout << endl;
    }

    void sortVerticesByDegreeAscending(Vector<int>& degreeOrder) {
        bool swapped;
        for (int i = 0; i < degreeOrder.size() - 1; i++) {
            swapped = false;
            for (int j = 0; j < degreeOrder.size() - i - 1; j++) {
                if (graph[degreeOrder[j]].size() > graph[degreeOrder[j + 1]].size() ||
                    (graph[degreeOrder[j]].size() == graph[degreeOrder[j + 1]].size() && degreeOrder[j] > degreeOrder[j + 1])) {
                    int temp = degreeOrder[j];
                    degreeOrder[j] = degreeOrder[j + 1];
                    degreeOrder[j + 1] = temp;
                    swapped = true;
                }
            }
            if (!swapped) break; // No swaps mean the vector is sorted
        }
    }

    void SLFColoring(int vertices) {
        Vector<int> degreeOrder(vertices); // przechowuje indeksy wierzcho?ków
        for (int i = 0; i < vertices; i++) {
            degreeOrder[i] = i;
        }

        // Sortowanie wierzcho?ków wed?ug stopnia rosn?co
        sortVerticesByDegreeAscending(degreeOrder);

        color.assign(vertices, -1); // -1 oznacza, ?e wierzcho?ek nie jest jeszcze pokolorowany
        Vector<bool> available(vertices, true); // dost?pne kolory

        for (int i = 0; i < vertices; i++) {
            int u = degreeOrder[i]; // bie??cy wierzcho?ek do pokolorowania

            // Resetowanie dost?pnych kolorów
            for (int j = 0; j < vertices; j++) {
                available[j] = true;
            }

            // Sprawdzanie kolorów s?siadów wierzcho?ka u
            for (int adj : graph[u]) {
                if (color[adj] != -1) { // je?li s?siad jest ju? pokolorowany
                    available[color[adj]] = false; // ten kolor jest ju? zaj?ty
                }
            }

            // Znajdowanie pierwszego dost?pnego koloru
            int cr;
            for (cr = 0; cr < vertices; cr++) {
                if (available[cr]) break;
            }

            color[u] = cr; // Pokoloruj wierzcho?ek u dost?pnym kolorem
        }

        // Wydrukuj kolory dla ka?dego wierzcho?ka
        for (int i = 0; i < vertices; i++) {
            cout << color[i] + 1 << " ";
        }
        cout << endl;
    }

    void processGraph(int vertices)  {
        graph.clear();
        graph.resize(vertices);
        color.assign(vertices, 0); // Reset kolorów wierzcho?ków
        Vector<int> degrees(vertices, 0); // Wektor stopni wierzcho?ków

        for (int i = 0; i < vertices; ++i) {
            int count;
            cin >> count;
            degrees[i] = count;  // Przypisz liczb? s?siadów jako stopie? wierzcho?ka
            for (int j = 0; j < count; ++j) {
                int neighbor;
                cin >> neighbor;
                graph[i].push_back(neighbor - 1);
                graph[neighbor - 1].push_back(i);
            }
        }

        // Sortind degrees of vertices
        mergeSort(degrees, 0, degrees.size() - 1);
        cout << endl;
        for (int deg : degrees) {
            cout << deg << " ";
        }
        cout << endl;

        int components = countComponents(vertices);
        cout << components << endl;

        bool bipartite = true;
        for (int i = 0; i < vertices; ++i) {
            if (color[i] == 0) {
                if (!isBipartite_BFS(i)) {
                    bipartite = false;
                    break;
                }
            }
        }
        cout << (bipartite ? "T" : "F") << endl;

        for (int i = 0; i < 2; i++) {
            cout << "?" << endl;
        }

        Coloring(vertices);

        LargestFirstColor(vertices);

        //SLFColoring(vertices);

        for (int i = 0; i < 2; i++) {
            cout << "?" << endl;
        }

        //long long c4Count = countC4Subgraphs(vertices);
        //cout << c4Count << endl;

        long long complementEdges = countComplementEdges(vertices);
        cout << complementEdges << endl;
    }

};

