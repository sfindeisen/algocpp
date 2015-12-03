typedef struct {
    long nn;            // neighbour node number
    long backPtr;       // address of this node entry in nn's predecessors/successors list
    long bfEdgeIndex;   // bfEdges index
    long prev;          // prev neighbour (or 0) (doubly linked list)
    long next;          // next neighbour (or 0) (doubly linked list)
} TNodeNeighbour;

typedef struct {
    char  deleted;
    long  connCompo;       // connected component ID [1..connCompoCount]

    TDoubleLinkedList predList;
    TDoubleLinkedList succList;
} TNode;

TNodeNeighbour neighbours[MaxE2 + 3];       // node neighbours buffer [1..neighCnt]
TNode          nodes     [MaxN  + 2];       // nodes [1..N]
long neighCnt       = 0;

void printNode(long n) {
    cerr << "    node " << n << ((nodes[n].deleted) ? " (deleted)" : "") << " has " << (nodes[n].predList.itemCount) << " preds:";
    for (long p = nodes[n].predList.firstItem; p; p = neighbours[p].next)
        cerr << " " << p << "->" << neighbours[p].nn << "";
    cerr << std::endl;
    cerr << "    node " << n << ((nodes[n].deleted) ? " (deleted)" : "") << " has " << (nodes[n].succList.itemCount) << " succs:";
    for (long p = nodes[n].succList.firstItem; p; p = neighbours[p].next)
        cerr << " " << p << "->" << neighbours[p].nn << "";
    cerr << std::endl;
}

/**
 * Dodaje wierzcholek n2 na koniec listy poprzednikow wierzcholka n1.
 * This leaves graph in inconsistent state!
 */
void addNodePredecessor_basic(long n1, long n2, long item, long backPtr) {
    neighbours[item].nn      = n2;
    neighbours[item].backPtr = backPtr;
    double_list_insert_last(nodes[n1].predList, item);
}

/**
 * Dodaje wierzcholek n2 na koniec listy nastepnikow wierzcholka n1.
 * This leaves graph in inconsistent state!
 */
void addNodeSuccessor_basic(long n1, long n2, long item, long backPtr) {
    neighbours[item].nn      = n2;
    neighbours[item].backPtr = backPtr;
    double_list_insert_last(nodes[n1].succList, item);
}

/** [TOP LEVEL PROCEDURE] Adds directed edge from n1 to n2. */
void addEdge(long n1, long n2) {
    const long ncnt = neighCnt;
    addNodeSuccessor_basic  (n1, n2, ++neighCnt, ncnt + 2);
    addNodePredecessor_basic(n2, n1, ++neighCnt, ncnt + 1);
}

/**
 * Removes neighIndex from its list. It must be a predecessor of its node.
 * This leaves graph in inconsistent state!
 */
void removeNodePredecessor_basic(const long nn, const long neighIndex) {
    double_list_delete(nodes[nn].predList, neighIndex);
    neighbours[neighIndex].nn      = 0;
    neighbours[neighIndex].backPtr = 0;
}

/**
 * Removes neighIndex from its list. It must be a successor of its node.
 * This leaves graph in inconsistent state!
 */
void removeNodeSuccessor_basic(const long nn, const long neighIndex) {
    double_list_delete(nodes[nn].succList, neighIndex);
    neighbours[neighIndex].nn      = 0;
    neighbours[neighIndex].backPtr = 0;
}

/** [TOP LEVEL PROCEDURE] Removes all incoming edges of node n1. */
void removePredEdges(long n1) {
    for (long p = nodes[n1].predList.firstItem; p; p = neighbours[p].next) {
        removeNodeSuccessor_basic(neighbours[p].nn, neighbours[p].backPtr);
    }

    ER += nodes[n1].predList.itemCount;
    double_list_clear(nodes[n1].predList);
}

/** [TOP LEVEL PROCEDURE] Removes all outgoing edges of node n1. */
void removeSuccEdges(long n1) {
    for (long p = nodes[n1].succList.firstItem; p; p = neighbours[p].next) {
        removeNodePredecessor_basic(neighbours[p].nn, neighbours[p].backPtr);
    }

    ER += nodes[n1].succList.itemCount;
    double_list_clear(nodes[n1].succList);
}

/** [TOP LEVEL PROCEDURE] Removes given node from the graph. */
void removeNode(long n1, long bfLevel=0) {
    removePredEdges(n1, bfLevel);
    removeSuccEdges(n1, bfLevel);
    nodes[n1].deleted = 1;
    ++NR;
}
