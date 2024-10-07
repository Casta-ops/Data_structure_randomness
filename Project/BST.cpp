#include <iostream>
#include "Vector.hh"
#include <string>
#include <cstdlib>
#include <ctime>
#include <fstream>

using namespace std;

template <typename K, typename V>
class BST {
    private: 
    class Node {
        private:
            K key;
            V value;
            Node* Left;
            Node* Right;
        public:
            Node(): key(), value(), Left(nullptr), Right(nullptr) {}
            Node(K k, V v): key(k), value(v), Left(nullptr), Right(nullptr) {}
            K getKey() { return key; }
            bool hasLeft(){ return Left != nullptr;}
            bool hasRight() { return Right != nullptr;}
            bool isLeaf() { return !hasLeft() && !hasRight(); }
            void setLeft(Node *n) { Left = n; }
            void setRight(Node *n) { Right = n; }
            V getValue() { return value; }
            Node * getLeft() { return Left; }
            Node * getRight() { return Right; }
    };
        private:
            Node* root;
            unsigned int size;

        public:
            BST() : root(nullptr), size(0) {}
            unsigned int getSize() { return size; }
            bool empty() { return root == nullptr; }
            void insert(K key, V value) {
                if (empty()) {
                root = new Node(key, value);
                size++;
                } else {
                insert(key, value, root);
                }
            }
            void printInOrder() {
                printInOrder(root);
                cout << endl;
            }
            unsigned int height() {
                return height(root);
            }
            void generateDot(const char* filename) {
                ofstream file(filename);
                file << "digraph G {" << endl;
                generateDot(root, file);
                file << "}";
                file.close();
            }
            bool validateDotFile(const string& filename) {
                ifstream file(filename);
                string line;
                while (getline(file, line)) {
                    if (line.find("-> ;") != string::npos || line.find("->") == 0) {
                        return false;  // Encontramos una conexión incompleta
                    }
                }
                    return true;
            }
            void terminal() {
                //escribir en la terminal "dot -Tpng movies.dot -o movies.png"
                system("dot -Tpng movies.dot -o movies.png");
            }
            unsigned int leaves() {
                return leaves(root);
            }
        private:
            void insert(K key, V value, Node* n) {
                if (key < n->getKey()) {
                    if (n->hasLeft()) {
                        insert(key, value, n->getLeft());
                    } else {
                        Node* x = new Node(key, value);
                        n->setLeft(x);
                        size++;
                    }
                } else if (n->getKey() < key) {
                    if (n->hasRight()) {
                        insert(key, value, n->getRight());
                    } else {
                        Node* x = new Node(key, value);
                        n->setRight(x);
                        size++;
                    }
                } else {
                    // Evitar insertar claves duplicadas
                }
            }
            void remove (K key) {
                root = remove(key, root);
            }
            void printInOrder(Node* n) {
                if (n != nullptr) {
                    printInOrder(n->getLeft());
                    cout << n->getKey() << " ";
                    printInOrder(n->getRight());
                }
            }
            unsigned int height(Node* n) {
                if (n == nullptr) {
                    return 0;
                }
                return 1 + max(height(n->getLeft()), height(n->getRight()));
            }
            unsigned int leaves(Node* n) {
                if (n == nullptr) {
                    return 0;
                }
                if (n->isLeaf()) {
                    return 1;
                }
                return leaves(n->getLeft()) + leaves(n->getRight());
            }
            void generateDot(Node* n, ofstream& file) {
                if (n != nullptr) {
                    // Crear el nodo actual
                    if (n->getKey() == "") {
                        //Conecta con el nodo siguiente
                    } else {
                        file << n->getKey() << ";\n";  // Genera el nodo actual
                    }

                    // Solo generar conexiones si el nodo tiene hijos válidos
                    if (n->hasLeft()) {
                        // if (n->getKey() -> "") que conecte con el nodo siguiente
                        if (n->getLeft()->getKey() == "") {
                            if (n->getKey() == n->getLeft()->getKey()) {
                                //omitir
                            }
                        } else {
                            file << n->getKey() << " -> " << n->getLeft()->getKey() << ";\n";
                            generateDot(n->getLeft(), file); // Llamada recursiva
                        }
                    }

                    if (n->hasRight()) {
                        // if (n->getKey() -> "") que conecte con el nodo siguiente
                        if (n->getRight()->getKey() == "") {
                            if (n->getKey() == n->getRight()->getKey()) {
                                //omitir
                            }
                        } else {
                            file << n->getKey() << " -> " << n->getRight()->getKey() << ";\n";
                            generateDot(n->getRight(), file); // Llamada recursiva
                        }
                    }   
                }
            }
};

int main () {
    //Lista de 100 peliculas
    string movies[100] = {
        "Inception", "Interstellar", "Gladiator", "Titanic", "Avatar", "Pulp", "Fight", "Forrest", "Star", "Jurassic",
        "Alien", "Blade", "Schindlers", "Braveheart", "Memento", "Se7en", "Goodfellas", "Psycho", "Vertigo", "Jaws",
        "Rocky", "Taxi", "Birdman", "Amelie", "Akira", "Paprika", "Summer", "Wolf", "Your", "Matrix",
        "Gravity", "Frozen", "Coco", "Up", "Cars", "Ratatouille", "Shrek", "Moana", "Zootopia", "Tangled",
        "Brave", "Bolt", "Hercules", "Tarzan", "Mulan", "Aladdin", "Pocahontas", "Bambi", "Dumbo", "Pinocchio",
        "Cinderella", "Fantasia", "Frozen", "Tangled", "Brave", "Bolt", "Hercules", "Tarzan", "Mulan", "Aladdin",
        "Pocahontas", "Bambi", "Dumbo", "Pinocchio", "Cinderella", "Fantasia", "Frozen", "Tangled", "Brave", "Bolt",
        "Hercules", "Tarzan", "Mulan", "Aladdin", "Pocahontas", "Bambi", "Dumbo", "Pinocchio", "Cinderella", "Fantasia",
        "Frozen", "Tangled", "Brave", "Bolt", "Hercules", "Tarzan", "Mulan", "Aladdin", "Pocahontas", "Bambi"
    };
    //insercion de los elementos en el vector de mi archivo Vector.hh
    Vector<string> v;
    for (int i = 0; i < 100; i++) {
        v.push_back(movies[i]);
    }
    // v.print(); //imprimir el vector
    v.sort(); //ordenar el vector
    BST<string, int> bst; //creacion de un arbol binario de busqueda
    //seleccion de los elementos aleatorios del vector
    srand(time(0));
    for (int i = 0; i < 100; i++) {
        int index = rand() % v.getSize();
        bst.insert(v.at(index), i);
        v.remove(index);
    }
    // bst.printInOrder(); //imprimir el arbol en orden
    cout << "Height: " << bst.height() << endl; //imprimir la altura del arbol
    cout << "Leaves: " << bst.leaves() << endl; //imprimir las hojas del arbol
    bst.generateDot("movies.dot"); //generar el archivo .dot
    if (bst.validateDotFile("movies.dot")) {
        cout << "El archivo .dot es valido." << endl;
    } else {
        cout << "El archivo .dot no es valido." << endl;
    }
    bst.terminal(); //generar la imagen .png
    return 0;
}