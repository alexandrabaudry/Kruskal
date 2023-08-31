import numpy as np
import matplotlib.pyplot as plt
import random
import math
import time
# Une classe pour représenter un ensemble disjoint
class Ensemble_Disjoint:
    parent = {}
 
    # effectue l'opération creation
    def creation(m, n):
        # créer `n` ensembles disjoints (un pour chaque sommet)
        for i in range(n):
            m.parent[i] = i
 
    # Trouver la racine de l'ensemble auquel appartient l'élément `k`
    def Trouver_Racine(m, k):
        # si `k` est racine
        if m.parent[k] == k:
            return k
 
        # se reproduisent pour le parent jusqu'à ce que nous trouvions la racine
        return m.Trouver_Racine(m.parent[k])
 
    # Perform Union de deux sous-ensembles
    def union(m, a, b):
        # trouver la racine des ensembles auxquels appartiennent les éléments `x` et `y`
        x = m.Trouver_Racine(a)
        y = m.Trouver_Racine(b)
 
        m.parent[x] = y
 
 
def Kruskal(aretes, n):
    MST = []
    ds = Ensemble_Disjoint()
    ds.creation(n)

    index = 0

    # trier les arêtes par poids croissant
    aretes.sort(key=lambda x: x[2])

    while len(MST) != n - 1:
        if index < len(aretes):
            (src, dest, weight) = aretes[index]
            index = index + 1
            x = ds.Trouver_Racine(src)
            y = ds.Trouver_Racine(dest)

          
            if x != y:
                MST.append((src, dest, weight))
                ds.union(x, y)
        else:
            break

    return MST

if __name__ == '__main__':
    # Nombre d'exécutions que vous souhaitez effectuer
    nombre_executions = 50

    # Liste pour stocker les temps d'exécution
    execution_times = []

    # Boucle pour effectuer plusieurs exécutions
    for _ in range(nombre_executions):
        start = time.time()
        
      
        nombre_sommets = 7
        aretes = []
        for _ in range(7):  # Nombre d'arêtes que vous voulez générer
            u = random.randint(0, nombre_sommets - 1)  # Sommet u aléatoire
            v = random.randint(0, nombre_sommets - 1)  # Sommet v aléatoire
            while u == v:
                 v = random.randint(0, nombre_sommets - 1)  # Assurer que u et v sont différents
            w = random.randint(1, 20)  # Poids aléatoire entre 1 et 20
            aretes.append((u, v, w))
        
        # nombre total de nœuds dans le graphe (étiquetés de 0 à 6)
        n = 7
        
        # graphe de construction
        e = Kruskal(aretes, n)
        print(e)
        
        # Enregistrez le temps d'exécution
        execution_times.append(time.time() - start)

    # Affichage des temps d'exécution
    print("Temps d'exécution pour chaque itération:", execution_times)

    # Tracé du graphique du temps d'exécution
    plt.figure(figsize=(15, 10))
    plt.plot(range(len(execution_times)), execution_times, marker='+')
    plt.xlabel('Exécution')
    plt.ylabel('Temps (s)')
    plt.title("Évolution du temps d'exécution")
    plt.grid(True)
    plt.show()
