public class Exercice {
    public static void main(String[] args) throws Exception {
        System.out.println("On cree le graphe de l'exercice 2.9");
        Graphe grapheHolder = new Graphe(100);
        grapheHolder.ajouterSommet('u');
        grapheHolder.ajouterSommet('A');
        grapheHolder.ajouterSommet('B');
        grapheHolder.ajouterSommet('C');
        grapheHolder.ajouterSommet('D');
        grapheHolder.ajouterSommet('E');
        grapheHolder.ajouterSommet('F');
        grapheHolder.ajouterSommet('G');
        grapheHolder.ajouterSommet('v');
        grapheHolder.ajouterArete('u','A',1);
        grapheHolder.ajouterArete('u','B',3);
        grapheHolder.ajouterArete('A','C',3);
        grapheHolder.ajouterArete('A','D',2);
        grapheHolder.ajouterArete('B','C',2);
        grapheHolder.ajouterArete('C','D',1);
        grapheHolder.ajouterArete('C','E',1);
        grapheHolder.ajouterArete('D','E',1);
        grapheHolder.ajouterArete('D','F',3);
        grapheHolder.ajouterArete('D','G',4);
        grapheHolder.ajouterArete('E','F',2);
        grapheHolder.ajouterArete('E','G',2);
        grapheHolder.ajouterArete('F','G',2);
        grapheHolder.ajouterArete('F','v',2);
        grapheHolder.ajouterArete('G','v',2);
        grapheHolder.printGraphe();

        Arbre arbreCouvrant=grapheHolder.dijkstra(grapheHolder.getGraphe(grapheHolder.sommetExiste('u')));
        arbreCouvrant.printArbreCouvrant();
    }
}
