#include <cstdio>
#include "graphviewer.h"
#include <fstream>
#include <iostream>
#include <sstream>

void exercicio1();
void exercicio2();
void exercicio3();


void exercicio1()
{

    GraphViewer *gv = new GraphViewer(600, 600, false);
    bool working = gv->setBackground("/home/joao/Documents/CAL/Praticas/cal_fp06_CLion/fundo.png");
    gv->createWindow(600, 600);
    gv->defineVertexColor("blue");
    gv->defineEdgeColor("black");
    gv->addNode(0, 10, 10);
    gv->addNode(1, 590, 590);
    gv->addEdge(0,0,1, EdgeType::DIRECTED);
    gv->setVertexLabel(0, "Isto e um no");
    gv->setEdgeLabel(0, "Isto e uma aresta");
    gv->setVertexColor(0, "green");
    gv->setEdgeColor(0, "yellow");
    gv->rearrange();
}

void exercicio2()
{
// TODO: Implement here exercise 2!
// ...
}

void exercicio3()
{
// To read map files, use relative paths:
// Vertices data: "../resources/mapa1/nos.txt"
// Edges data: "../resources/mapa1/arestas.txt"

    GraphViewer *gv = new GraphViewer(600, 600, false);

    ifstream fileInput;
    fileInput.open("../resources/mapa1/nos.txt");
    while (!fileInput.eof()) {
        string
    }

}

int main() {
    /*
     * Uncomment the line below to run Exercise 1
     */
//    exercicio1();

    /*
      * Uncomment the line below to run Exercise 2
      */
    //exercicio2();

    /*
      * Uncomment the line below to run Exercise 3
      */
	//
	exercicio3();

	getchar();
	return 0;
}
