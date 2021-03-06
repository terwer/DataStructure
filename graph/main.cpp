//
//  main.cpp
//  graph
//
//  Created by Terwer Green on 16/5/31.
//  Copyright © 2016年 Terwer Green. All rights reserved.
//

#include <iostream>

#include <stdio.h>
#include <stdlib.h>
#include "graph.h"
#include "priority_queue.h"
#include "queue.h"

int main(int argc, char **argv)
{
    if (argc != 2) {
        fprintf(stderr, "usage: %s filename\n", argv[0]);
        exit(EXIT_FAILURE);
    }
    
    char *filename = argv[1];
    graph_t *G = read_graph(filename);
    print_graph(G);
    
    search_tree_t *dfs_tree = dfs(G);
    fprintf(stderr, "DFS:\n");
    print_search_tree(dfs_tree);
    
    search_tree_t *bfs_tree = bfs(G);
    fprintf(stderr, "BFS:\n");
    print_search_tree(bfs_tree);
    
    dist_tree_t *dij_tree = dijkstra(G, 0);
    print_dist_tree(dij_tree);
    
    // queue and priority queue testing
    /*
     pq_t *PQ = create_empty_pq(5);
     int i;
     for (i = 0; i < 5; i++) {
     pq_push(PQ, (void *) NULL, 100 - i);
     print_pq(PQ);
     }
     for (i = 0; i < 5; i++) {
     pq_pop(PQ);
     print_pq(PQ);
     }
     queue_t *Q = create_empty_queue();
     int A[5] = {0, 1, 2, 3, 4};
     int *a;
     q_push(Q, A);
     print_queue(Q);
     q_pop(Q);
     print_queue(Q);
     for (i = 0; i < 5; i++) {
     q_push(Q, A+i);
     print_queue(Q);
     }
     for (i = 0; i < 5; i++) {
     a = q_pop(Q);
     print_queue(Q);
     }
     */
    
    return 0;
}
