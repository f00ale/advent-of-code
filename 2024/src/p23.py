import networkx

def solve(data):
    ans1 = 0
    ans2 = ''
    nodes = {}
    nodenames = ['']
    edges = []
    maxnode = 0
    for line in data:
        (a,b) = line.split('-')
        if not a in nodes:
            maxnode = maxnode + 1
            nodes[a] = maxnode
            nodenames.append(a)
        if not b in nodes:
            maxnode = maxnode + 1
            nodes[b] = maxnode
            nodenames.append(b)
        edges.append((nodes[a],nodes[b]))

    G = networkx.Graph()
    G.add_nodes_from([*range(1,maxnode+1)])
    G.add_edges_from(edges)
    #cliques = networkx.find_cliques(G)
    cliques = networkx.enumerate_all_cliques(G)
    maxclique = []
    for c in cliques:
        if len(c) == 3:
            for n in c:
                if nodenames[n][0] == 't':
                    ans1 = ans1 + 1
                    break
        if len(c) > len(maxclique):
            maxclique = c

    names = []
    for n in maxclique:
        names.append(nodenames[n])
    names.sort()
    ans2 = ','.join(names)

    print(ans1)
    print(ans2)

def main():
    with open('data/p23.txt') as fp:
        data = fp.readlines()
        cleaned = [ line.strip() for line in data ]
        solve(cleaned)


if __name__ == '__main__':
    main()