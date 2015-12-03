/** Breadth-first-search */

inline void initConnectedComponent_BFS_push(std::queue<long>& q, const long neigh, const long ccid) {
    if ((! (nodes[neigh].deleted)) && (ccid != (nodes[neigh].connCompo)))
        q.push(neigh);
}

void initConnectedComponent_BFS(const long startNode, const long ccid) {
    long nodeCnt = 0;
    long edgeCnt = 0;
    queue<long> bfs;
    bfs.push(startNode);

    for (; (! (bfs.empty())); ++nodeCnt) {
        const long n = bfs.front();
        nodes[n].connCompo = ccid;

        for (long p = nodes[n].predList.firstItem; p; p = neighbours[p].next) {
            initConnectedComponent_BFS_push(bfs, neighbours[p].nn, ccid);
            ++edgeCnt;
        }
        for (long p = nodes[n].succList.firstItem; p; p = neighbours[p].next) {
            initConnectedComponent_BFS_push(bfs, neighbours[p].nn, ccid);
            ++edgeCnt;
        }

        bfs.pop();
    }

    connectedComponents[ccid].nodeCount = nodeCnt;
    connectedComponents[ccid].edgeCount = edgeCnt / 2;
}

void initConnectedComponents() {
    for (long i = 1; i <= N; ++i) {
        if ((! (nodes[i].deleted)) && (! (nodes[i].connCompo))) {
            //cerr << "Starting connected component with node " << i << " (connCompoCount=" << connCompoCount << ")" << std::endl;
            initConnectedComponent_BFS(i, ++connCompoCount);
        }
    }
}
