#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <fstream>
#include <ctime>
#include <iomanip>
#include <cstdlib>

using namespace std;

class Student {
public:
    string name;
    int id_no;
    string stream;
    string book1, book2;
    int book_no;

    Student(string name, int id_no, string stream) {
        this->name = name;
        this->id_no = id_no;
        this->stream = stream;
        this->book_no = 0;
        this->book1 = "";
        this->book2 = "";
    }
};

class Node {
public:
    string key;
    Node* left;
    Node* right;

    Node(string item) {
        key = item;
        left = right = nullptr;
    }
};

class LibraryManagement {
private:
    Node* root;

public:
    LibraryManagement() {
        root = nullptr;
    }

    void insert(string key) {
        root = insertRec(root, key);
    }

    Node* insertRec(Node* root, string key) {
        if (root == nullptr) {
            return new Node(key);
        }
        if (key < root->key) {
            root->left = insertRec(root->left, key);
        } else if (key > root->key) {
            root->right = insertRec(root->right, key);
        }
        return root;
    }

    void deleteKey(string key) {
        root = deleteRec(root, key);
    }

    Node* deleteRec(Node* root, string key) {
        if (root == nullptr) return root;

        if (key < root->key) {
            root->left = deleteRec(root->left, key);
        } else if (key > root->key) {
            root->right = deleteRec(root->right, key);
        } else {
            if (root->left == nullptr) {
                Node* temp = root->right;
                delete root;
                return temp;
            } else if (root->right == nullptr) {
                Node* temp = root->left;
                delete root;
                return temp;
            }

            root->key = minValue(root->right);
            root->right = deleteRec(root->right, root->key);
        }
        return root;
    }

    string minValue(Node* root) {
        string minv = root->key;
        while (root->left != nullptr) {
            minv = root->left->key;
            root = root->left;
        }
        return minv;
    }

    bool containsNode(string key) {
        return containsNodeRecursive(root, key);
    }

    bool containsNodeRecursive(Node* current, string key) {
        if (current == nullptr) {
            return false;
        }
        if (key == current->key) {
            return true;
        }
        return key < current->key ? containsNodeRecursive(current->left, key) : containsNodeRecursive(current->right, key);
    }

    void printInorder(Node* node) {
        if (node == nullptr) return;
        printInorder(node->left);
        cout << node->key << "		";
        printInorder(node->right);
    }

    void printTree(Node* node, int space) {
        if (node == nullptr) return;
        space += 5;
        printTree(node->right, space);
        cout << endl;
        for (int i = 5; i < space; i++) cout << " ";
        cout << "[" << node->key << "]";
        printTree(node->left, space);
    }

    Node* getRoot() {
        return root;
    }

    void printInorder() {
        printInorder(root);
    }

    void printTree() {
        printTree(root, 0);
    }
};

int main() {
    LibraryManagement tree;
    map<string, int> hashmapping;
    vector<Student> students;
    students.emplace_back("Rajvi", 1741078, "B.Tech-ICT");
    students.emplace_back("Krushna", 1741086, "B.Tech-ICT");
    students.emplace_back("Kalagee", 1741052, "B.Tech-ICT");

    // Create file streams
    ofstream br("append.txt", ios::app);
    ifstream reader("x.txt");
    ifstream reader2("y.txt");
    ifstream reader3("z.txt");

    // Store book quantities
    vector<vector<int>> arr(100, vector<int>(2, 0));
    string line;
    int i = 0;

    while (true) {
        cout << "\n....................................." << endl;
        cout << "1. Librarian Login." << endl;
        cout << "2. User Login." << endl;
        cout << "3. Exit." << endl;
        cout << "\n....................................." << endl;

        cout << "\nEnter Your choice: ";
        int ch1;
        cin >> ch1;

        switch (ch1) {
            case 1: {
                string pwd1 = "abc123";
                string id1 = "dsa@1";
                string id2, pwd2;

                cout << "\nEnter UserId: ";
                cin >> id2;
                cout << "\nEnter Password: ";
                cin >> pwd2;

                if (id1 != id2) {
                    cout << "Invalid Userid." << endl;
                } else if (pwd1 != pwd2) {
                    cout << "Invalid Password." << endl;
                } else {
                    cout << "Login successful." << endl;
                    bool e2 = false;

                    while (!e2) {
                        cout << "\n....................................." << endl;
                        cout << "1. Add book." << endl;
                        cout << "2. Delete book." << endl;
                        cout << "3. Update book." << endl;
                        cout << "4. Print Books Details." << endl;
                        cout << "5. Print Books in-order." << endl;
                        cout << "6. Print tree." << endl;
                        cout << "7. Exit" << endl;
                        cout << "\n....................................." << endl;

                        cout << "\nEnter Your choice: ";
                        int ch2;
                        cin >> ch2;

                        switch (ch2) {
                            case 1: {
                                while (getline(reader, line)) {
                                    tree.insert(line);
                                    hashmapping[line] = i;
                                    i++;
                                }

                                int j = i;
                                string number;

                                while (getline(reader2, number)) {
                                    int result = stoi(number);
                                    if (j != i) {
                                        arr[i][0] = result;
                                    }
                                    i++;
                                }

                                string number1;

                                while (getline(reader3, number1)) {
                                    int result1 = stoi(number1);
                                    if (j != i) {
                                        arr[i][1] = result1;
                                    }
                                    i++;
                                }

                                cout << "\nEnter name of book: ";
                                string name;
                                cin >> name;
                                if (tree.containsNode(name)) {
                                    cout << "\nIt already exists." << endl;
                                } else {
                                    cout << "\nEnter quantity of book: ";
                                    int quantity;
                                    cin >> quantity;
                                    br << name << endl; // Append to file
                                    arr[i][0] += quantity; // Total quantity of books
                                    arr[i][1] += quantity; // Available quantity of books
                                    tree.insert(name);
                                    hashmapping[name] = i;
                                    i++;
                                }
                                break;
                            }

                            case 2: {
                                cout << "\nEnter name of book: ";
                                string b1;
                                cin >> b1;

                                if (tree.containsNode(b1)) {
                                    tree.deleteKey(b1);
                                    hashmapping.erase(b1);
                                }
                                break;
                            }

                            case 3: {
                                cout << "\nEnter name of book: ";
                                string b2;
                                cin >> b2;

                                if (tree.containsNode(b2)) {
                                    int a = hashmapping[b2];
                                    cout << "\nEnter quantity of book to add more: ";
                                    int q;
                                    cin >> q;
                                    arr[a][0] += q;
                                }
                                break;
                            }

                            case 4: {
                                for (const auto& entry : hashmapping) {
                                    int r = entry.second;
                                    cout << "Name of book is: " << entry.first << endl;
                                    cout << "Total Quantity of book is: " << arr[r][0] << endl;
                                    cout << "Available Quantity of book is: " << arr[r][1] << endl << endl;
                                }
                                break;
                            }

                            case 5:
                                tree.printInorder();
                                break;

                            case 6:
                                tree.printTree(tree.getRoot(), 0);
                                break;

                            case 7:
                                e2 = true;
                                break;
                        }
                    }
                }
                break;
            }

            case 2: {
                bool e3 = false;

                while (!e3) {
                    cout << "\n....................................." << endl;
                    cout << "1. Issue book." << endl;
                    cout << "2. Return book." << endl;
                    cout << "3. Exit" << endl;
                    cout << "\n....................................." << endl;

                    cout << "\nEnter Your choice: ";
                    int ch3;
                    cin >> ch3;

                    switch (ch3) {
                        case 1: {
                            int id;
                            cout << "\nEnter your ID number: ";
                            cin >> id;
                            string name;
                            cout << "\nEnter your name: ";
                            cin >> name;

                            for (auto& student : students) {
                                if (student.id_no == id) {
                                    if (student.book_no < 2) {
                                        cout << "\nEnter name of book: ";
                                        string b3;
                                        cin >> b3;

                                        if (tree.containsNode(b3)) {
                                            int r = hashmapping[b3];

                                            if (arr[r][1] > 0) {
                                                arr[r][1] -= 1; // Reduce available quantity
                                                if (student.book_no == 0) {
                                                    student.book1 = b3;
                                                    student.book_no++;
                                                } else {
                                                    student.book2 = b3;
                                                    student.book_no++;
                                                }
                                            } else {
                                                cout << "\nSorry, Book not available." << endl;
                                            }
                                        } else {
                                            cout << "\nBook not found." << endl;
                                        }
                                    } else {
                                        cout << "\nYou cannot issue more than 2 books." << endl;
                                    }
                                    break;
                                }
                            }
                            break;
                        }

                        case 2: {
                            int id;
                            cout << "\nEnter your ID number: ";
                            cin >> id;

                            for (auto& student : students) {
                                if (student.id_no == id) {
                                    string b4;
                                    cout << "\nEnter the name of the book you want to return: ";
                                    cin >> b4;

                                    if (student.book1 == b4) {
                                        student.book1 = "";
                                        student.book_no--;
                                        int r = hashmapping[b4];
                                        arr[r][1] += 1; // Increase available quantity
                                    } else if (student.book2 == b4) {
                                        student.book2 = "";
                                        student.book_no--;
                                        int r = hashmapping[b4];
                                        arr[r][1] += 1; // Increase available quantity
                                    } else {
                                        cout << "\nYou have not issued this book." << endl;
                                    }
                                    break;
                                }
                            }
                            break;
                        }

                        case 3:
                            e3 = true;
                            break;
                    }
                }
                break;
            }

            case 3:
                exit(0);
        }
    }

    return 0;
}
