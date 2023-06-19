/* Honor Pledge: I pledge on my honor that I have not given
   or received any unauthorized assitance on this examination
   or assginment.

   Name: Omkar Pathak
   TerpConnect login ID: omkarp07
   University ID number: 119272961
   Discussion Section Number: 0106

   The purpose of this header file is to serve as the framework for the
   graph implementation used in this project -- it extends upon the
   framework used by the last project by implementing conditional
   compilation. This framework consists of three structures: graph, edge,
   and vertex. The graph implementation is based on the adjacency list
   graph representation. A dynamically-allocated array is used to store
   the vertices of the graph.
 */

/* String_graph stores the number of vertices and a dynamically-allocated
 * array of the graph's vertices*/

#if !defined(STRING_GRAPH_DATASTRUCTURE_H)
#define STRING_GRAPH_DATASTRUCTURE_H

typedef struct graph {
    int vertex_num;
    struct vertex **vertices_array;
} String_graph;

/* This implementation of the edge structure was adapted from a slide given in
 * lecture when linked data structures were being discussed. Edge contains
 * fields for the weight of the edge, the destination vertex, and the next
 * edge (as part of the adacency list)*/

typedef struct edge {
    int weight;
    struct vertex *destination_vertex;
    struct edge *next_edge;
} Edge;

/* The implementation of the vertex structure was adapted from a slide given
 * in lecture when linked data structure were being discussed. Vertex contains
 * fields for the name of the vertex and a pointer to the head of the
 * adjacency list corresponding to each vertex*/

typedef struct vertex {
    char *string_data;
    Edge *edge_list;
} Vertex;

#endif
