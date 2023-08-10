from graph import Graph
from grafo_a import movies_by_id, actors_by_movie, actor_names_by_id
from collections import deque

def create_graph_b(movies_by_id, actors_by_movie, actor_names_by_id): 
    graph = Graph()

    for actor_id, actor_name in actor_names_by_id.items(): 
        graph.add_vertex(actor_id, actor_name)
    
    for movie_id, _ in movies_by_id.items():
        graph.add_vertex(movie_id, movies_by_id[movie_id]['primaryTitle'])

    for movie, actors in actors_by_movie.items(): 
        for actor in actors: 
            if graph.vertex_exists(actor): 
                graph.add_edge(movie, actor, ['a'])

    return graph

graph = create_graph_b(movies_by_id, actors_by_movie, actor_names_by_id)
#graph.print_graph()

def BFS(graph, start):
    queue = deque()
    queue.append(start)

    visited = set()
    visited.add(start)

    dictionary = {start: (None,0)}  # Almacena el nodo anterior y la distancia

    while queue:
        current = queue.popleft()

        for neighbor in graph.get_neighbors(current):
            if neighbor not in visited:
                queue.append(neighbor)
                visited.add(neighbor)
                
                dictionary[neighbor] = (current, dictionary[current][1] + 1)

    distances = {}
    for artist, (_, distance) in dictionary.items(): 
        distances[artist] = int(distance/2)

    return distances

#Ejercicio 2 ------------------------------

def separation_degree(actor1, actor2, graph): 
    if not graph.vertex_exists(actor1) or not graph.vertex_exists(actor2):
        return -1 

    distances = BFS(graph, actor1)

    if actor2 in distances:
        return distances[actor2]  

    return -1

actor1 = 'nm0000051'
actor2 = 'nm0000231'
degree = separation_degree(actor1, actor2, graph)
print(f"El grado de separación entre {graph.get_vertex_data(actor1)} y {graph.get_vertex_data(actor2)} es {degree}")


#Ejercicio 3 ------------------------------

def Kevin_Bacon(graph):
    distances = BFS(graph, 'nm0000102')
    max_distance = 0
    max_actor = ''

    for actor, distance in distances.items():
        if distance > max_distance:
            max_distance = distance
            max_actor = graph.get_vertex_data(actor)

    return [max_actor, max_distance]


kb = Kevin_Bacon(graph)
print("Actor a mayor grado de separacion de Kevin Bacon:", kb) 
