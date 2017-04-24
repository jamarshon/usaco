import math
from fractions import gcd

class Edge:
    def __init__(self, v=-1, n=None):
        self.v = v
        self.n = n

def get_maximum_matching(edges, n):
    M, pool, top, adj, match, q, father, base, qh, qt, inq, inb, ed = initialize()
    V = n

    # construct graph
    for i in range(len(edges)):
        u = edges[i][0]
        v = edges[i][1]
        if not ed[u-1][v-1]:
            top = add_edge(u-1, v-1, pool, adj, top)
            ed[u-1][v-1]= True
            ed[v-1][u-1] = True

    # for i in range(V): 
        # if i < match[i]: print str(i+1) + " " + str(match[i] + 1)
    # run edmonds blossom algorithm to find matching pairs
    return edmonds(inq, V, base, qh, qt, q, adj, match, father, inb, M)

def should_add_edge(x, y):
    z = (x + y) / gcd(x, y)
    return z & (z - 1)

def answer(banana_list):
    n = len(banana_list)
    edges = []
    for i in range(n):
        for j in range(i+1, n):
            if should_add_edge(banana_list[i], banana_list[j]):
                edges.append([i + 1, j + 1])

    maximum_matching = get_maximum_matching(edges, n)
    return n - maximum_matching*2

def initialize():
    M = 101 # maximum number of nodes is 100
    pool = [Edge() for i in range(M*M*2)]
    top = 0
    adj = [Edge() for i in range(M)]
    match = [0 for i in range(M)]
    q = [0 for i in range(M)]
    father = [0 for i in range(M)]
    base = [0 for i in range(M)]
    qh = 0
    qt = 0
    inq = [False for i in range(M)]
    inb = [False for i in range(M)]
    ed = [[False for i in range(M)] for j in range(M)]
    return M, pool, top, adj, match, q, father, base, qh, qt, inq, inb, ed

def add_edge(u, v, pool, adj, top):
    pool[top].v = v
    pool[top].n = adj[u]
    adj[u] = pool[top]
    top += 1

    pool[top].v = u
    pool[top].n = adj[v]
    adj[v] = pool[top]
    top += 1
    return top

def LCA(root, u, v, base, father, match, M):
    inp = [False for i in range(M)]
    while True:
        u = base[u]
        inp[u] = True
        if u == root: break
        u = father[match[u]]

    while True:
        v = base[v]
        if inp[v]: return v
        else: v = father[match[v]]

def mark_blossom(lca, u, match, inb, base, father):
    while base[u] != lca:
        v = match[u]
        inb[base[u]] = True
        inb[base[v]] = True
        u = father[v]
        if base[u] != lca: father[u] = v

def blossom_contraction(s, u, v, base, father, match, inb, inq, q, qt, M, V):
    lca = LCA(s, u, v, base, father, match, M)
    for i in range(len(inb)): inb[i] = False
    mark_blossom(lca, u, match, inb, base, father)
    mark_blossom(lca, v, match, inb, base, father)
    if base[u] != lca:
        father[u] = v
    if base[v] != lca:
        father[v] = u
    for u in range(V):
        if inb[base[u]]:
            base[u] = lca
        if not inq[u]:
            qt += 1
            q[qt] = u
            inq[q[qt]] = True
    return qt

def find_augmenting_path(s, inq, V, base, qh, qt, q, adj, match, father, inb, M):
    for i in range(len(inq)): inq[i] = False
    for i in range(len(father)): father[i] = -1
    for i in range(V): base[i] = i
    qh = 0
    qt = 0
    q[qh] = s
    inq[q[qh]] = True

    while qh <= qt:
        u = q[qh]
        qh += 1
        e = adj[u]
        while e:
            v = e.v
            if base[u] != base[v] and match[u] != v:
                if v == s or (match[v] != -1 and father[match[v]] != -1):
                    qt = blossom_contraction(s, u, v, base, father, match, inb, inq, q, qt, M, V)
                elif father[v] == -1:
                    father[v] = u
                    if match[v] == -1:
                        return (v, qh, qt)
                    elif not inq[match[v]]:
                        qt += 1
                        q[qt] = match[v]
                        inq[q[qt]] = True
            e = e.n
    return (-1, qh, qt)

def augment_path(s, t, father, match):
    u = t
    while u != -1:
        v = father[u]
        w = match[v]
        match[v] = u
        match[u] = v
        u = w
    return t != -1

def edmonds(inq, V, base, qh, qt, q, adj, match, father, inb, M):
    matchc = 0
    for i in range(len(match)): match[i] = -1
    for u in range(V):
        if match[u] == -1:
            path, qh, qt = find_augmenting_path(u, inq, V, base, qh, qt, q, adj, match, father, inb, M)
            matchc += augment_path(u, path, father, match)
    return matchc;


print answer([1,1])
print answer([1, 7, 3, 21, 13, 19])