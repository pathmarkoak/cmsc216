/* Honor Pledge: I pledge on my honor that I have not given
   or received any unauthorized assitance on this examination
   or assginment.

   Name: Omkar Pathak
   TerpConnect login ID: omkarp07
   University ID number: 119272961
   Discussion Section Number: 0106

   The purpose of this project is to implement graph methods using the
   implementation given in string-graph-datastructure.h. Graphs are stored
   using dynamically allocated memory; the implementation in
   string-graph-datastructure.h uses three structures for a graph, edge,
   and vertex. In this file, some methods are used to modify the graph
   (e.g. add vertices, edges, etc.), whereas others are used to obtain
   information about the graph (e.g. the weight of a specific edge). There
   are also some utility functions used for more efficient design. Graphs
   in this project use the adjacency list to store edges; vertices are
   stored using a dynamically-allocated array that is modified every time a
   vertex is added to the graph. It is assumed that all memory allocations
   are always successful, even if this may not be the case in practical
   scenarios. As a result, memory allocations are not freed after they are
   initially allocated.
 */

#include "string-graph.h"
#include <stdlib.h>
#include <string.h>

/* Function prototypes for three utility functions */
static void insert_vertex(String_graph *const graph, const char new_vertex[]);
static Vertex *return_vertex(const String_graph *const graph,
                             const char name[]);
static Edge *return_edge(const String_graph *const graph, const char source[],
                         const char dest[]);

/* graph_init takes in a constant pointer to a graph and initializes the
   parts of the graph (e.g. its number of vertices and the dynamically-
   allocated array of vertices). This function has no return values. This
   function is also the first function called on any String_graph variable.*/
void graph_init(String_graph *const graph) {
    /* Creating new pointer and setting it to null initially*/
    struct graph *graph_pointer = NULL;

    /* If the graph is not null, its fields are initialized and memory is
       dynamically allocated for it */
    if (graph != NULL) {
        graph_pointer = malloc(sizeof(struct graph) +
                               sizeof(struct vertex *) + sizeof(int));
        graph_pointer->vertices_array = malloc(sizeof(struct vertex *));
        graph_pointer->vertex_num = 0;

        /* graph is set equal to graph_pointer, as graph is constant*/
        *graph = *graph_pointer;
    }
}

/* add_vertex_to_graph takes in a constant pointer to a graph as a parameter
    and the name of the vertex to be added. It modifies the graph by adding
    the vertex to it (if it doesn't already exist) and returns a short
    indicating whether the graph was succesfully returned or not.*/
short add_vertex_to_graph(String_graph *const graph,
                          const char new_vertex[]) {
    short return_val = 0;

    /* If the parameters are not returned and the graph doesn't already
       contain the vertex, the utility function insert_vertex is called to
       perform the process of insertion into the graph. */
    if (graph != NULL && new_vertex != NULL &&
        !isa_vertex(graph, new_vertex)) {
        return_val = 1;
        insert_vertex(graph, new_vertex);
    }
    return return_val;
}

/* vertex_count takes in a constant pointer to a constant graph and returns
 * the number of vertices in the graph. This function does not modify the
 * graph in any way.*/
short vertex_count(const String_graph *const graph) {
    short return_val = 0;

    if (graph != NULL) {
        return_val = graph->vertex_num;
    }
    return return_val;
}

/* isa_vertex takes in a constant pointer to a constant graph and returns a
    short indicating whether or not the vertex exists in the parameter graph
   or not. This function does not modify the current graph in any way. */
short isa_vertex(const String_graph *const graph, const char name[]) {
    short return_val = 0;
    int count;

    /* If the graph and name are not null, the array of pointers to vertices
     * is iterated through to and each vertex's string_data is compared with
     * name*/
    if (graph != NULL && name != NULL) {
        for (count = 0; count < graph->vertex_num; count++) {
            if (strcmp(name, graph->vertices_array[count]->string_data) ==
                0) {
                return_val = 1;
            }
        }
    }
    return return_val;
}

/* **get_vertex_list returns an array of vertices in lexicographic order of
 * all of the vertices in the graph. This function does not modify the
 * parameter graph in any way, and the array that is returned is
 * dynamically-allocated.*/
char **get_vertex_list(const String_graph *const graph) {
    /* Initializing pointers to the array to be returned, the name of each
     * vertex, and a temp pointer for when the array sort is performed */
    char **return_array = NULL;
    char *name, *temp;
    int count, i;

    /* If the graph is not null, memory of the array is dynamically allocated
     using malloc*/
    if (graph != NULL) {
        return_array = malloc(sizeof(char *) * (graph->vertex_num + 1));

        /* Copying vertex names and then storing them into return_array*/
        for (count = 0; count < graph->vertex_num; count++) {

            /* Dynamically-allocating array for the vertex name, copying the
             * vertex name to the pointer, and setting the appropriate entry
             * in return_array to name*/
            name =
                malloc(strlen(graph->vertices_array[count]->string_data) + 1);
            strcpy(name, graph->vertices_array[count]->string_data);
            return_array[count] = name;
        }

        /* Sorting the array using a nested for loop (insertion sort)*/
        for (count = 0; count < graph->vertex_num; count++) {
            for (i = count + 1; i < graph->vertex_num; i++) {
                if (strcmp(return_array[count], return_array[i]) > 0) {
                    /* If the earlier string is "greater" than the later
                     * string, their values are switched*/
                    temp = return_array[count];
                    return_array[count] = return_array[i];
                    return_array[i] = temp;
                }
            }
        }
        /* The last entry of return_entry is set to NULL*/
        return_array[graph->vertex_num] = NULL;
    }
    return return_array;
}

/* create_graph_edge takes in a constant pointer to a graph as a parameter,
 * source and destination strings, and an int weight to create a new edge in
 * the graph. This function returns a short indicating whether or not the edge
 * was successfully added and modifies the graph if this is the case. */
short create_graph_edge(String_graph *const graph, const char source[],
                        const char dest[], int weight) {
    short return_val = 0;

    /* Using return_vertex to obtain pointers to the source and destination
     * vertices (may be NULL)*/
    Vertex *source_vertex = return_vertex(graph, source);
    Vertex *dest_vertex = return_vertex(graph, dest);

    /* Pointers to traverse through the edge_list and for the edge to be
     * added*/
    Edge *curr_edge = NULL;
    Edge *new_edge = NULL;

    /* If the weight and pointers are valid and source and dest are vertices,
     * the process of edge addition starts */
    if (weight >= 0 && graph != NULL) {
        return_val = 1;

        /* If the edge already exists in the graph, curr_edge is set to the
         * edge using utility function return_edge and the weight of curr_edge
         * is updated*/
        if (return_edge(graph, source, dest)) {
            curr_edge = return_edge(graph, source, dest);
            curr_edge->weight = weight;

            /* Otherwise, curr_edge is set to the head of edge_list and
             * new_edge is dynamically allocated */
        } else {
            if (!isa_vertex(graph, source)) {
                add_vertex_to_graph(graph, source);
                source_vertex = return_vertex(graph, source);
            } else {
                curr_edge = source_vertex->edge_list;
            }

            if (!isa_vertex(graph, dest)) {
                add_vertex_to_graph(graph, dest);
                dest_vertex = return_vertex(graph, dest);
            }

            new_edge =
                malloc(sizeof(struct edge) + sizeof(int) +
                       sizeof(struct edge *) + sizeof(struct vertex *));

            /* Iterating through the last edge of edge_list to add new_edge to
             * the graph */
            while (curr_edge != NULL && curr_edge->next_edge != NULL) {
                curr_edge = curr_edge->next_edge;
            }

            /* Dynamically allocating new edge and storing its weight */
            new_edge->destination_vertex = dest_vertex;
            new_edge->weight = weight;
            new_edge->next_edge = NULL;

            /* Adding new_edge to the graph based on whether or not it is the
             * head of edge_list or not*/
            if (curr_edge == NULL) {
                source_vertex->edge_list = new_edge;
            } else {
                curr_edge->next_edge = new_edge;
            }
        }
    }
    return return_val;
}

/*get_graph_edge_weight takes in a constant pointer to a constant graph, as
 * well as the source and dest of the edge to be created. This function
 * returns a short based on whether or not the graph weight was sucessfully
 * returned. This function does not modify the graph in any way. */
short get_graph_edge_weight(const String_graph *const graph,
                            const char source[], const char dest[]) {
    short return_val = -1;

    /* Setting pointer to the edge between source and dest (may be null)*/
    Edge *curr_edge = return_edge(graph, source, dest);

    /* If curr_edge is not NULL, return_val is set to weight */
    if (curr_edge) {
        return_val = curr_edge->weight;
    }

    return return_val;
}

/* neighbor_count takes in a constant pointer to a constant graph and the name
 * of a vertex as a parameter. This function does not modify the parameter
 * graph in any way. */
short neighbor_count(const String_graph *const graph, const char vertex[]) {
    short return_val = -1;

    /* Creating pointers for the desired vertex and edge*/
    Vertex *curr_vertex = return_vertex(graph, vertex);
    Edge *curr_edge = NULL;

    /* If curr_vertex is not NULL, edge_list iterated through and return_val
     * is incremented (after being set to 0)*/
    if (curr_vertex) {
        return_val = 0;
        curr_edge = curr_vertex->edge_list;
        while (curr_edge != NULL) {
            return_val++;
            curr_edge = curr_edge->next_edge;
        }
    }
    return return_val;
}

/* insert_vertex is a static utiliy function takes in a constant pointer to a
 * graph and the name of the vertex to be added. This function is modifies the
 * graph by inserting the vertex into the graph. */
static void insert_vertex(String_graph *const graph,
                          const char new_vertex[]) {

    /* Creating pointer to vertex to be added, allocating memory for this
     * vertex, and copying the string to new_name pointer */
    Vertex *adding_vertex;
    char *new_name = malloc(strlen(new_vertex) + 1);
    strcpy(new_name, new_vertex);

    /* Reallocating memory for graph, as a vertex is to be added */
    graph->vertices_array =
        realloc(graph->vertices_array,
                sizeof(struct vertex *) * graph->vertex_num + 1);

    /* Allocating memory for the vertex to be added, setting the
     * string_data field of the vertex to new_name, and settingg its edge_list
     * as NULL*/
    adding_vertex = malloc(sizeof(char *) + sizeof(struct edge *) +
                           sizeof(struct vertex) + sizeof(struct vertex *));
    adding_vertex->string_data = new_name;
    adding_vertex->edge_list = NULL;

    /* Adding new vertex to the dynamically-allocated array storing vertices*/
    graph->vertices_array[graph->vertex_num++] = adding_vertex;
}

/* *return_vertex takes in a constant pointer to a constant graph and a string
 * name as input, and returns the corersponding vertex in the graph; this
 * return value can also be NULL, indicating no return value. This function
 * does not modify the input graph in any way. */
static Vertex *return_vertex(const String_graph *const graph,
                             const char name[]) {

    /* Initially setting pointer vertex to NULL and initializing count
     * variable for for loop*/
    Vertex *vertex = NULL;
    int count;

    /* If the vertex exists (checked using isa_vertex), the process of
     * iteration begins and the vertex is searched for using strcmp and a for
     * loop*/
    if (isa_vertex(graph, name)) {
        for (count = 0; count < graph->vertex_num; count++) {
            if (strcmp(graph->vertices_array[count]->string_data, name) ==
                0) {
                vertex = graph->vertices_array[count];
            }
        }
    }
    return vertex;
}

/* *return_edge takes in a constant pointer to a constant graph as a parameter
 * and source and destination strings as parameters and returns a pointer to
 * the edge (if it exists); this return value could also be NULL. This
 * function does not modify the parameter graph in any way. */
static Edge *return_edge(const String_graph *const graph, const char source[],
                         const char dest[]) {

    /* Initializing pointer to edge to NULL */
    Edge *curr_edge = NULL;

    /* If the source and destination vertices exist, the process of searching
     * for the edge begins*/
    if (isa_vertex(graph, source) && isa_vertex(graph, dest)) {
        /* curr_edge is set to the head of the edge_list of the source
         * vertex*/
        curr_edge = (return_vertex(graph, source))->edge_list;

        /* Iterating through edge_list linked list and searching for the
         * edge*/
        while (curr_edge != NULL &&
               strcmp(dest, (curr_edge->destination_vertex)->string_data) !=
                   0) {
            curr_edge = curr_edge->next_edge;
        }
    }
    return curr_edge;
}
