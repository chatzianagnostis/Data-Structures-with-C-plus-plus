# Τεχνική Έκθεση Υλοποίησης Δομών Δεδομένων

## Περιεχόμενα

0. [Οδηγίες Μεταγλώττισης (Compilation)]()
1. [Εισαγωγή](#εισαγωγή)
2. [Σωρός Ελαχίστων (MinHeap)](#σωρός-ελαχίστων-minheap)
3. [Σωρός Μεγίστων (MaxHeap)](#σωρός-μεγίστων-maxheap)
4. [Δυαδικό Δέντρο Αναζήτησης AVL](#δυαδικό-δέντρο-αναζήτησης-avl)
5. [Γράφημα](#γράφημα)
6. [Πίνακας Κατακερματισμού (HashTable)](#πίνακας-κατακερματισμού-hashtable)
7. [Κύριο Πρόγραμμα και Μέτρηση Χρόνου](#κύριο-πρόγραμμα-και-μέτρηση-χρόνου)
8. [Ανάλυση Απόδοσης](#ανάλυση-απόδοσης)
9. [Συμπεράσματα](#συμπεράσματα)

## Οδηγίες Μεταγλώττισης (Compilation)

Υπάρχουν δύο κύριοι τρόποι για τη μεταγλώττιση του προγράμματος:

### Μέθοδος 1: Απευθείας μέσω της γραμμής εντολών (CLI)

Μπορείτε να μεταγλωττίσετε το πρόγραμμα χρησιμοποιώντας απευθείας τον compiler της C++, με την ακόλουθη εντολή:

```bash
g++ -std=c++11 -Wall -O2 -o data_structures main.cpp MinHeap.cpp MaxHeap.cpp AVLTree.cpp Graph.cpp HashTable.cpp
```

Η εντολή αυτή μεταγλωττίζει όλα τα αρχεία πηγαίου κώδικα και δημιουργεί ένα εκτελέσιμο αρχείο με το όνομα `data_structures` (ή `data_structures.exe` στα Windows).

### Μέθοδος 2: Χρησιμοποιώντας το Makefile

Εναλλακτικά, μπορείτε να χρησιμοποιήσετε το παρεχόμενο Makefile, το οποίο αυτοματοποιεί τη διαδικασία μεταγλώττισης:

1. Ανοίξτε ένα τερματικό/γραμμή εντολών και πλοηγηθείτε στον φάκελο αυτό
2. Εκτελέστε την εντολή:

```bash
make
```

Το Makefile περιλαμβάνει επίσης χρήσιμες εντολές όπως:

```bash
# Καθαρισμός των αντικειμενικών αρχείων και του εκτελέσιμου
make clean

# Μεταγλώττιση και άμεση εκτέλεση του προγράμματος
make run

# Καθαρισμός και επαναμεταγλώττιση
make rebuild

# Εμφάνιση των διαθέσιμων εντολών
make help
```

**Σημείωση για Windows:** Εάν χρησιμοποιείτε Windows και δεν έχετε εγκατεστημένο το make, μπορείτε:
1. Να εγκαταστήσετε το MinGW με το MSYS που περιλαμβάνει το make
2. Να εγκαταστήσετε το Chocolatey και να εκτελέσετε `choco install make`
3. Να χρησιμοποιήσετε απευθείας τη μέθοδο μεταγλώττισης μέσω γραμμής εντολών


## Εισαγωγή

Στο πλαίσιο της εργασίας αυτής, υλοποιήθηκε μια βιβλιοθήκη δομών δεδομένων σε C++. Η βιβλιοθήκη περιλαμβάνει τις ακόλουθες δομές:

- Σωρός ελαχίστων (MinHeap)
- Σωρός μεγίστων (MaxHeap)
- Δυαδικό δέντρο αναζήτησης AVL
- Γράφημα χωρίς κατευθύνσεις με βάρη στις ακμές
- Πίνακας κατακερματισμού (HashTable)

Για κάθε δομή δεδομένων, υλοποιήθηκαν οι βασικές λειτουργίες που απαιτούνται για την αποτελεσματική χρήση της. Το πρόγραμμα διαβάζει εντολές από ένα αρχείο εισόδου, εκτελεί τις αντίστοιχες λειτουργίες και καταγράφει τα αποτελέσματα μαζί με τους χρόνους εκτέλεσης σε ένα αρχείο εξόδου.

## Σωρός Ελαχίστων (MinHeap)

### Περιγραφή και Βασικές Λειτουργίες

Ο σωρός ελαχίστων είναι μια δομή δεδομένων που επιτρέπει την εύρεση του ελάχιστου στοιχείου σε σταθερό χρόνο O(1) και την αφαίρεση του ελάχιστου στοιχείου σε λογαριθμικό χρόνο O(log n). Η υλοποίηση βασίζεται σε ένα πλήρες δυαδικό δέντρο που αποθηκεύεται σε μορφή πίνακα (vector).

### Σημαντικά Σημεία της Υλοποίησης

#### Αναπαράσταση

```cpp
// MinHeap.h
class MinHeap {
private:
    std::vector<int> heap;
    
    // Helper functions
    void heapifyUp(int index);
    void heapifyDown(int index);
    int parent(int index) const { return (index - 1) / 2; }
    int leftChild(int index) const { return 2 * index + 1; }
    int rightChild(int index) const { return 2 * index + 2; }
    
public:
    MinHeap();
    
    // Main operations
    int buildFromFile(const std::string& filename);
    int getSize() const;
    int findMin() const;
    void insert(int value);
    int deleteMin();
};
```

#### Βασικές Μέθοδοι

Η κατασκευή του σωρού από αρχείο γίνεται με μια αποδοτική τεχνική που έχει πολυπλοκότητα O(n), σε αντίθεση με την επαναληπτική εισαγωγή που θα είχε πολυπλοκότητα O(n log n):

```cpp
// Heapify down - ρύθμιση της ιδιότητας του σωρού
void MinHeap::heapifyDown(int index) {
    int smallest = index;
    int left = leftChild(index);
    int right = rightChild(index);
    int size = heap.size();
    
    if (left < size && heap[left] < heap[smallest]) {
        smallest = left;
    }
    
    if (right < size && heap[right] < heap[smallest]) {
        smallest = right;
    }
    
    if (smallest != index) {
        std::swap(heap[index], heap[smallest]);
        heapifyDown(smallest);
    }
}
```

Η εισαγωγή στοιχείου χρησιμοποιεί τη μέθοδο heapifyUp για να διατηρήσει την ιδιότητα του σωρού:

```cpp
// Εισαγωγή στοιχείου
void MinHeap::insert(int value) {
    heap.push_back(value);
    heapifyUp(heap.size() - 1);
}

// Heapify up - ρύθμιση της ιδιότητας του σωρού μετά από εισαγωγή
void MinHeap::heapifyUp(int index) {
    if (index == 0) return;
    
    int parentIndex = parent(index);
    if (heap[parentIndex] > heap[index]) {
        std::swap(heap[parentIndex], heap[index]);
        heapifyUp(parentIndex);
    }
}
```

## Σωρός Μεγίστων (MaxHeap)

### Περιγραφή και Βασικές Λειτουργίες

Ο σωρός μεγίστων είναι παρόμοιος με το σωρό ελαχίστων, αλλά επιτρέπει την εύρεση του μέγιστου στοιχείου σε σταθερό χρόνο. Η υλοποίηση είναι παρόμοια με του σωρού ελαχίστων, με τις κατάλληλες προσαρμογές στις συγκρίσεις.

### Σημαντικά Σημεία της Υλοποίησης

Η κύρια διαφορά σε σχέση με το σωρό ελαχίστων βρίσκεται στις συναρτήσεις σύγκρισης:

```cpp
// Heapify down για MaxHeap
void MaxHeap::heapifyDown(int index) {
    int largest = index;
    int left = leftChild(index);
    int right = rightChild(index);
    int size = heap.size();
    
    // Αντίθετη συνθήκη σε σχέση με το MinHeap
    if (left < size && heap[left] > heap[largest]) {
        largest = left;
    }
    
    if (right < size && heap[right] > heap[largest]) {
        largest = right;
    }
    
    if (largest != index) {
        std::swap(heap[index], heap[largest]);
        heapifyDown(largest);
    }
}
```

## Δυαδικό Δέντρο Αναζήτησης AVL

### Περιγραφή και Βασικές Λειτουργίες

Το δυαδικό δέντρο αναζήτησης AVL είναι ένα αυτο-ισορροπούμενο δυαδικό δέντρο αναζήτησης. Η διαφορά ύψους μεταξύ αριστερού και δεξιού υποδέντρου οποιουδήποτε κόμβου δεν υπερβαίνει το 1, γεγονός που εξασφαλίζει λογαριθμικό χρόνο O(log n) για τις βασικές λειτουργίες.

### Σημαντικά Σημεία της Υλοποίησης

#### Δομή Κόμβου

```cpp
// Δομή κόμβου AVL
struct AVLNode {
    int value;
    AVLNode* left;
    AVLNode* right;
    int height;
    
    AVLNode(int val) : value(val), left(nullptr), right(nullptr), height(1) {}
};
```

#### Περιστροφές

Οι περιστροφές είναι βασικές λειτουργίες που διατηρούν την ισορροπία του δέντρου:

```cpp
// Δεξιά περιστροφή
AVLNode* AVLTree::rightRotate(AVLNode* y) {
    AVLNode* x = y->left;
    AVLNode* T2 = x->right;
    
    // Εκτέλεση περιστροφής
    x->right = y;
    y->left = T2;
    
    // Ενημέρωση υψών
    y->height = std::max(height(y->left), height(y->right)) + 1;
    x->height = std::max(height(x->left), height(x->right)) + 1;
    
    return x;
}

// Αριστερή περιστροφή
AVLNode* AVLTree::leftRotate(AVLNode* x) {
    // Παρόμοια υλοποίηση με τη δεξιά περιστροφή
    // ...
}
```

#### Εισαγωγή

Η εισαγωγή κόμβου περιλαμβάνει την τυπική εισαγωγή BST και επιπλέον την ενημέρωση των υψών και την εκτέλεση περιστροφών όπου χρειάζεται:

```cpp
// Εισαγωγή κόμβου με ισορροπία AVL
AVLNode* AVLTree::insertNode(AVLNode* node, int value) {
    // Τυπική εισαγωγή BST
    if (node == nullptr) {
        size++;
        return new AVLNode(value);
    }
    
    if (value < node->value)
        node->left = insertNode(node->left, value);
    else if (value > node->value)
        node->right = insertNode(node->right, value);
    else // Δεν επιτρέπονται διπλότυπες τιμές
        return node;
    
    // Ενημέρωση ύψους του τρέχοντος κόμβου
    node->height = 1 + std::max(height(node->left), height(node->right));
    
    // Έλεγχος ισορροπίας και εκτέλεση περιστροφών όπου χρειάζεται
    int balance = getBalance(node);
    
    // Περίπτωση Left Left
    if (balance > 1 && value < node->left->value)
        return rightRotate(node);
    
    // Περίπτωση Right Right
    if (balance < -1 && value > node->right->value)
        return leftRotate(node);
    
    // Περίπτωση Left Right
    if (balance > 1 && value > node->left->value) {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }
    
    // Περίπτωση Right Left
    if (balance < -1 && value < node->right->value) {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }
    
    return node;
}
```

## Γράφημα

### Περιγραφή και Βασικές Λειτουργίες

Το γράφημα υλοποιείται ως ένα μη κατευθυνόμενο γράφημα με βάρη στις ακμές. Χρησιμοποιείται η αναπαράσταση λίστας γειτνίασης (adjacency list) για την αποθήκευση του γραφήματος, η οποία είναι αποδοτική για αραιά γραφήματα.

### Σημαντικά Σημεία της Υλοποίησης

#### Αναπαράσταση

```cpp
// Graph.h
class Graph {
private:
    // Λίστα γειτνίασης: κορυφή -> λίστα από (γείτονας, βάρος)
    std::unordered_map<int, std::vector<std::pair<int, int>>> adjList;
    int numEdges;
    
    // Βοηθητικές συναρτήσεις
    void dfs(int vertex, std::unordered_map<int, bool>& visited);
    
public:
    Graph();
    
    // Κύριες λειτουργίες
    std::pair<int, int> buildFromFile(const std::string& filename);
    std::pair<int, int> getSize() const;
    int computeShortestPath(int source, int target);
    int computeSpanningTree();
    int findConnectedComponents();
    void insertEdge(int u, int v, int weight);
    bool removeEdge(int u, int v);
};
```

#### Αλγόριθμος Dijkstra για Συντομότερα Μονοπάτια

```cpp
// Υπολογισμός συντομότερου μονοπατιού (Dijkstra)
int Graph::computeShortestPath(int source, int target) {
    const int INF = std::numeric_limits<int>::max();
    std::unordered_map<int, int> dist;  // κορυφή -> απόσταση από αρχή
    
    // Αρχικοποίηση αποστάσεων
    for (const auto& pair : adjList) {
        dist[pair.first] = INF;
    }
    dist[source] = 0;
    
    // Ουρά προτεραιότητας για τον αλγόριθμο Dijkstra
    std::priority_queue<std::pair<int, int>, 
                         std::vector<std::pair<int, int>>, 
                         std::greater<std::pair<int, int>>> pq;
    pq.push(std::make_pair(0, source));
    
    // Κυρίως αλγόριθμος
    while (!pq.empty()) {
        int u = pq.top().second;
        int d = pq.top().first;
        pq.pop();
        
        if (u == target) {
            return d;
        }
        
        if (d > dist[u]) {
            continue;
        }
        
        // Εξερεύνηση γειτόνων
        for (const auto& neighbor : adjList[u]) {
            int v = neighbor.first;
            int weight = neighbor.second;
            
            // Χαλάρωση ακμής
            if (dist[u] + weight < dist[v]) {
                dist[v] = dist[u] + weight;
                pq.push(std::make_pair(dist[v], v));
            }
        }
    }
    
    return -1; // Δεν είναι προσβάσιμος ο προορισμός
}
```

#### Αλγόριθμος Prim για Ελάχιστο Εκτεινόμενο Δέντρο

```cpp
// Υπολογισμός ελάχιστου εκτεινόμενου δέντρου (Prim)
int Graph::computeSpanningTree() {
    if (adjList.empty()) {
        return 0;
    }
    
    const int INF = std::numeric_limits<int>::max();
    int totalWeight = 0;
    std::unordered_map<int, bool> inMST;
    std::unordered_map<int, int> key;
    
    // Αρχικοποίηση
    for (const auto& pair : adjList) {
        key[pair.first] = INF;
        inMST[pair.first] = false;
    }
    
    // Αρχή από οποιαδήποτε κορυφή
    int start = adjList.begin()->first;
    key[start] = 0;
    
    // Ουρά προτεραιότητας για τον αλγόριθμο Prim
    std::priority_queue<std::pair<int, int>, 
                         std::vector<std::pair<int, int>>, 
                         std::greater<std::pair<int, int>>> pq;
    pq.push(std::make_pair(0, start));
    
    // Κυρίως αλγόριθμος
    while (!pq.empty()) {
        // Επιλογή κορυφής με ελάχιστο κλειδί
        int u = pq.top().second;
        pq.pop();
        
        if (inMST[u]) {
            continue;
        }
        
        // Προσθήκη στο MST
        inMST[u] = true;
        totalWeight += key[u];
        
        // Ενημέρωση κλειδιών γειτονικών κορυφών
        for (const auto& neighbor : adjList[u]) {
            int v = neighbor.first;
            int weight = neighbor.second;
            
            if (!inMST[v] && weight < key[v]) {
                key[v] = weight;
                pq.push(std::make_pair(key[v], v));
            }
        }
    }
    
    // Έλεγχος αν το MST συνδέει όλες τις κορυφές
    for (const auto& pair : inMST) {
        if (!pair.second) {
            // Το γράφημα δεν είναι συνεκτικό
            return -1;
        }
    }
    
    return totalWeight;
}
```

#### Εύρεση Συνεκτικών Συνιστωσών με DFS

```cpp
// DFS για την εύρεση συνεκτικών συνιστωσών
void Graph::dfs(int vertex, std::unordered_map<int, bool>& visited) {
    visited[vertex] = true;
    
    for (const auto& neighbor : adjList[vertex]) {
        if (!visited[neighbor.first]) {
            dfs(neighbor.first, visited);
        }
    }
}

// Εύρεση αριθμού συνεκτικών συνιστωσών
int Graph::findConnectedComponents() {
    std::unordered_map<int, bool> visited;
    
    // Αρχικοποίηση
    for (const auto& pair : adjList) {
        visited[pair.first] = false;
    }
    
    int count = 0;
    
    // Εκτέλεση DFS από κάθε μη επισκεφθείσα κορυφή
    for (const auto& pair : adjList) {
        int vertex = pair.first;
        if (!visited[vertex]) {
            dfs(vertex, visited);
            count++;
        }
    }
    
    return count;
}
```

## Πίνακας Κατακερματισμού (HashTable)

### Περιγραφή και Βασικές Λειτουργίες

Ο πίνακας κατακερματισμού υλοποιείται με τη μέθοδο αλυσιδωτής διασύνδεσης (chaining) για την αντιμετώπιση των συγκρούσεων. Κάθε θέση του πίνακα περιέχει μια λίστα από στοιχεία που έχουν την ίδια τιμή κατακερματισμού.

### Σημαντικά Σημεία της Υλοποίησης

#### Αναπαράσταση

```cpp
// HashTable.h
class HashTable {
private:
    static const int DEFAULT_SIZE = 1024;
    std::vector<std::list<int>> table;
    int count;
    
    // Συνάρτηση κατακερματισμού
    int hash(int key) const;
    
public:
    HashTable(int size = DEFAULT_SIZE);
    
    // Κύριες λειτουργίες
    int buildFromFile(const std::string& filename);
    int getSize() const;
    bool search(int key) const;
    void insert(int key);
};
```

#### Συνάρτηση Κατακερματισμού

```cpp
// Απλή συνάρτηση κατακερματισμού
int HashTable::hash(int key) const {
    return key % table.size();
}
```

#### Αναζήτηση και Εισαγωγή

```cpp
// Αναζήτηση στοιχείου
bool HashTable::search(int key) const {
    int index = hash(key);
    const std::list<int>& list = table[index];
    
    for (int value : list) {
        if (value == key) {
            return true;
        }
    }
    
    return false;
}

// Εισαγωγή στοιχείου
void HashTable::insert(int key) {
    // Έλεγχος αν το κλειδί υπάρχει ήδη
    if (search(key)) {
        return;
    }
    
    int index = hash(key);
    table[index].push_back(key);
    count++;
}
```

## Κύριο Πρόγραμμα και Μέτρηση Χρόνου

### Περιγραφή

Το κύριο πρόγραμμα διαβάζει εντολές από το αρχείο commands.txt, εκτελεί τις αντίστοιχες λειτουργίες και καταγράφει τα αποτελέσματα και τους χρόνους εκτέλεσης στο αρχείο output.txt.

### Υλοποίηση

#### Μέτρηση Χρόνου Εκτέλεσης

```cpp
// Μέτρηση χρόνου εκτέλεσης
template<typename Func>
std::pair<typename std::result_of<Func()>::type, long long> measureExecutionTime(Func func) {
    auto start = high_resolution_clock::now();
    auto result = func();
    auto end = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(end - start).count();
    return std::make_pair(result, duration);
}
```

#### Επεξεργασία Εντολών

```cpp
// Παράδειγμα επεξεργασίας εντολής BUILD
if (command == "BUILD") {
    string filename;
    iss >> filename;
    
    if (structure == "MINHEAP") {
        auto result_pair = measureExecutionTime([&]() {
            return minHeap.buildFromFile(filename);
        });
        int result = result_pair.first;
        long long duration = result_pair.second;
        outputFile << "MINHEAP built with " << result << " elements. (" 
                  << duration << " μs)" << endl;
    }
    // Επεξεργασία για άλλες δομές...
}
```

## Ανάλυση Απόδοσης

### Πολυπλοκότητα Χρόνου

| Δομή Δεδομένων | Λειτουργία | Πολυπλοκότητα |
|----------------|------------|---------------|
| MinHeap/MaxHeap | Build | O(n) |
| MinHeap/MaxHeap | Insert | O(log n) |
| MinHeap/MaxHeap | DeleteMin/DeleteMax | O(log n) |
| MinHeap/MaxHeap | FindMin/FindMax | O(1) |
| AVL Tree | Build | O(n log n) |
| AVL Tree | Insert | O(log n) |
| AVL Tree | Delete | O(log n) |
| AVL Tree | Search | O(log n) |
| Graph | Shortest Path (Dijkstra) | O((V+E) log V) |
| Graph | Minimum Spanning Tree (Prim) | O((V+E) log V) |
| Graph | Connected Components | O(V+E) |
| HashTable | Insert | O(1) μέση περίπτωση, O(n) χειρότερη περίπτωση |
| HashTable | Search | O(1) μέση περίπτωση, O(n) χειρότερη περίπτωση |

### Μετρήσεις Απόδοσης

Από το αρχείο output.txt παρατηρούμε ότι οι χρόνοι εκτέλεσης των λειτουργιών εξαρτώνται από το μέγεθος των δεδομένων και τη φύση της λειτουργίας:

1. Οι λειτουργίες στους σωρούς είναι πολύ γρήγορες, με την κατασκευή και τις λειτουργίες εισαγωγής/διαγραφής να έχουν ελάχιστο κόστος.
2. Οι λειτουργίες στο AVL δέντρο έχουν ελαφρώς υψηλότερο κόστος λόγω των περιστροφών που απαιτούνται για τη διατήρηση της ισορροπίας.
3. Οι λειτουργίες στο γράφημα, όπως η εύρεση συντομότερου μονοπατιού και ο υπολογισμός ελάχιστου εκτεινόμενου δέντρου, έχουν υψηλότερο κόστος, ιδιαίτερα για μεγάλα γραφήματα.
4. Η κατασκευή του πίνακα κατακερματισμού φαίνεται να είναι πιο χρονοβόρα λειτουργία, πιθανώς λόγω της αρχικοποίησης των λιστών.

## Συμπεράσματα

Η υλοποίηση των δομών δεδομένων σε αυτή την εργασία παρέχει μια ολοκληρωμένη βιβλιοθήκη που μπορεί να χρησιμοποιηθεί για την επίλυση διαφόρων προβλημάτων. Κάθε δομή δεδομένων έχει συγκεκριμένα πλεονεκτήματα και μειονεκτήματα:

1. Οι σωροί παρέχουν αποδοτική πρόσβαση στο ελάχιστο ή μέγιστο στοιχείο και είναι χρήσιμοι σε αλγορίθμους όπως η ταξινόμηση σωρού (heapsort) και η χρονοδρομολόγηση.
2. Το AVL δέντρο προσφέρει ισορροπημένη αναζήτηση, εισαγωγή και διαγραφή με εγγυημένη λογαριθμική πολυπλοκότητα.
3. Το γράφημα επιτρέπει την αναπαράσταση πολύπλοκων σχέσεων και την εφαρμογή αλγορίθμων για συντομότερα μονοπάτια και ελάχιστα εκτεινόμενα δέντρα.
4. Ο πίνακας κατακερματισμού παρέχει πολύ γρήγορη αναζήτηση και εισαγωγή για τυχαία δεδομένα.