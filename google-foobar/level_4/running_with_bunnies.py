import sys
from heapq import heappush, heappop

inf = sys.maxint
neg_inf = -(inf - 1)

# General pseudocode:
# - Run Johnson algorithm to find the shortest paths between all pairs of vertices in a 
#   sparse, edge weighted, directed graph.
# - Bellman Ford is used to detect negative cycles if there is one then just return all integers from 0 to n-2
# - The distances are used to reweight the edges so that an edge (u,v) becomes original weight + h(u) - h(v)
# - Run Dijsktra on reweighted graph as it no longer has negative edges
# - Use breadth first search (BFS) and reconstruct original path to find the original weight
# - Based on shortest path given by Johnson algorith, you would not need to visit the same vertex more than once
#   in the BFS
# - During BFS, keep track of the maximum number of visited nodes between the start and destination node

def add_source_vertex(times, n):
    source_vertex = [0 for i in range(n)]
    times.append(source_vertex)
    return times

def run_bellman_ford(times, n):
    # times is a n + 1 row and n col array where a row i corresponds to all the edges the vertex i has
    source_index = n

    # all vertices have a weight of infinity and null predecessor
    distance = [inf for i in range(n + 1)] 
    predecessor = [None for i in range(n + 1)] 

    distance[source_index] = 0

    # relax edges
    for k in range(n + 1):
        for u in range(n + 1):
            for v in range(n):
                w = times[u][v]
                if w != inf and distance[u] != inf and distance[u] + w < distance[v]:
                    distance[v] = distance[u] + w
                    predecessor[v] = u

    has_negative_cycle = False
    # check for negative cycles
    for u in range(n):
        for v in range(n):
            w = times[u][v]
            if w != inf and distance[u] != inf and distance[u] + w < distance[v]:
                has_negative_cycle = True

    return has_negative_cycle, distance, predecessor

def reweight_graph(g_prime, distance, n):
    weighted_g = []
    for i in range(n):
        temp = []
        for j in range(n):
            new_weight = g_prime[i][j] + distance[i] - distance[j]
            temp.append(new_weight)
        weighted_g.append(temp)
    return weighted_g

def run_dijsktra(weighted_g, src, n):
    visited = [False for i in range(n)]
    distance = {i: inf for i in range(n)}
    path = {src: None}
    nodes = []
    for i in range(n): heappush(nodes, (0 if i == src else inf, i))
    while nodes:
        current = heappop(nodes)
        current_distance, current_node = current

        distance[current_node] = current_distance
        visited[current_node] = True

        new_set = []
        for node_distance, node_key in nodes:
            if not visited[node_key]:
                w = weighted_g[current_node][node_key]
                if w != inf and current_distance + w < distance[node_key]:
                    distance[node_key] = current_distance + w
                    path[node_key] = current_node
                heappush(new_set, (distance[node_key], node_key))
        nodes = new_set
    return distance, path

def reconstruct_path(paths, times, current_node, branch_node, n):
    path = paths[current_node]
    full_path = [False for i in range(n)]
    cost = 0
    while path[branch_node] != None:
        full_path[branch_node] = True
        cost += times[path[branch_node]][branch_node]
        branch_node = path[branch_node]
    return full_path, cost


def answer(times, time_limit):
    n = len(times[0])
    if n <= 2: return []
    g_prime = add_source_vertex(times, n)
    has_negative_cycle, distance, predecessor = run_bellman_ford(g_prime, n)

    if has_negative_cycle: return [i-1 for i in range(1, n-1)]

    weighted_g = reweight_graph(g_prime, distance, n)
    distances = []
    paths = []

    for i in range(n):
        distance, path = run_dijsktra(weighted_g, i, n)
        distances.append(distance)
        paths.append(path)

    q = [{'current_node': 0, 'distance': 0, 'completed': [i == 0 or i == n-1 for i in range(n)]}]
    i = 0

    best_cost = neg_inf
    best_completed = []

    while i != len(q):
        front = q[i]
        current_node = front['current_node']

        new_items = []

        for j in range(1, n - 1):
            if not front['completed'][j]:
                new_path, new_cost = reconstruct_path(paths, times, current_node, j, n)
                completed = [front['completed'][k] or new_path[k] for k in range(n)]
                new_item = {'current_node': j, 'distance': front['distance'] + new_cost, 'completed': completed}
                new_items.append(new_item)
        
        new_items.sort(key=lambda x: x['distance'])
        for item in new_items:
            q.append(item)

        new_path, new_cost = reconstruct_path(paths, times, current_node, n - 1, n)
        completed = [front['completed'][k] or new_path[k] for k in range(n)]
        new_count = 0
        for j in completed: 
            if j: new_count += 1

        if front['distance'] + new_cost <= time_limit and new_count > best_cost:
            best_completed = completed
            best_cost = new_count

        i += 1
    return [i - 1 for i in range(n) if i != 0 and i != n-1 and best_completed[i]]

times = [[0, 1, 1, 1, 1], [1, 0, 1, 1, 1], [1, 1, 0, 1, 1], [1, 1, 1, 0, 1], [1, 1, 1, 1, 0]]
time_limit = 3
print answer(times, time_limit)
# [0, 1]

times = [[0, 2, 2, 2, -1], [9, 0, 2, 2, -1], [9, 3, 0, 2, -1], [9, 3, 2, 0, -1], [9, 3, 2, 2, 0]]
time_limit = 1
print answer(times, time_limit)
# [1, 2]