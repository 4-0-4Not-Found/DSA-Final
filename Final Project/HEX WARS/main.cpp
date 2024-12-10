#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <thread>
#include <chrono>
#include <windows.h>
#include <mmsystem.h>
#include <unistd.h>
#include <conio.h>
#include <cstdlib>

using namespace std;

// Function to display the current state of the player's army
void display(const vector<int>& tree, const string& armyName) {
    cout << "--------------------" << armyName << "--------------------" << endl;
    for (int i = 0; i < tree.size(); i++) {
        cout << "Soldier " << i + 1 << ": Power Level " << tree[i] << endl;
    }
    cout << endl;
}

// Heapify function to build max heap
void heapifyMax(vector<int>& tree, int index, int size) {
    int left = 2 * index + 1;
    int right = 2 * index + 2;
    int largest = index;

    if (left < size && tree[left] > tree[largest]) {
        largest = left;
    }

    if (right < size && tree[right] > tree[largest]) {
        largest = right;
    }

    if (largest != index) {
        swap(tree[index], tree[largest]);
        heapifyMax(tree, largest, size);
    }
}

// Min-Heapify function to maintain the Min-Heap property
void heapifyMin(vector<int>& tree, int index, int size) {
    int left = 2 * index + 1;
    int right = 2 * index + 2;
    int smallest = index;

    if (left < size && tree[left] < tree[smallest]) {
        smallest = left;
    }

    if (right < size && tree[right] < tree[smallest]) {
        smallest = right;
    }

    if (smallest != index) {
        swap(tree[index], tree[smallest]);
        heapifyMin(tree, smallest, size);
    }
}


// Build max-heap function
void buildMaxHeap(vector<int>& tree) {
    int n = tree.size();
    for (int i = n / 2 - 1; i >= 0; i--) {
        heapifyMax(tree, i, n);
    }
}

// Build min-heap function
void buildMinHeap(vector<int>& tree) {
    int n = tree.size();
    // Start from the last non-leaf node and heapify all nodes upwards
    for (int i = n / 2 - 1; i >= 0; i--) {
        heapifyMin(tree, i, n);  // Call the Min-Heapify function
    }
}

// Binary Tree Traversals
void preorderTraversal(const vector<int>& tree, int index) {
    if (index >= tree.size()) return;
    cout << tree[index] << " "; // Visit the root
    preorderTraversal(tree, 2 * index + 1); // Visit left child
    preorderTraversal(tree, 2 * index + 2); // Visit right child
}

void inorderTraversal(const vector<int>& tree, int index) {
    if (index >= tree.size()) return;
    inorderTraversal(tree, 2 * index + 1); // Visit left child
    cout << tree[index] << " "; // Visit the root
    inorderTraversal(tree, 2 * index + 2); // Visit right child
}

void postorderTraversal(const vector<int>& tree, int index) {
    if (index >= tree.size()) return;
    postorderTraversal(tree, 2 * index + 1); // Visit left child
    postorderTraversal(tree, 2 * index + 2); // Visit right child
    cout << tree[index] << " "; // Visit the root
}

// Searching for a soldier with a specific power level
bool search(const vector<int>& tree, int value) {
    for (int i = 0; i < tree.size(); i++) {
        if (tree[i] == value) {
            return true;
        }
    }
    return false;
}

// Deletion of a soldier from the army (removes from the heap)
void deleteSoldier(vector<int>& tree, int value) {
    auto it = find(tree.begin(), tree.end(), value);
    if (it != tree.end()) {
        // Swap with the last element and pop the back element
        *it = tree.back();
        tree.pop_back();
        buildMaxHeap(tree);  // Rebuild the heap after deletion
    } else {
        cout << "Soldier with power level " << value << " not found!" << endl;
    }
}

// Function to simulate the battle
void battle(vector<int>& playerArmy, vector<int>& enemyArmy) {
    int playerWins = 0;

    for (int i = 0; i < playerArmy.size(); i++) {
        if (playerArmy[i] > enemyArmy[i]) {
            playerWins++;
            cout << "Your Soldier (" << playerArmy[i] << ") overpowers Enemy's Warrior(" << enemyArmy[i] << ")!" << endl;
        } else {
            cout << "Your Soldier (" << playerArmy[i] << ") is outmatched by Enemy's Warrior(" << enemyArmy[i] << ")!" << endl;
        }
        sleep(2); // Small delay for battle excitement
    }

    sleep(3);
    cout << endl;

    if (playerWins > 2) {
        cout << "You secured the Hextech energy and defended Piltover! Victory!" << endl;
    } else {
        cout << "The enemy has overtaken your defenses. Piltover falls to the Noxians..." << endl;
    }
}

// Typing effect for displaying text
void typingEffect(const string& text, int delay) {
    for (char c : text) {
        cout << c << flush;  // Print one character at a time
        this_thread::sleep_for(chrono::milliseconds(delay));  // Delay between characters
    }
    cout << endl;  // Move to the next line after printing the text
}

int main() {
    srand(time(0));  // Initialize random number generator
    char pin; // Player input
    int choice;
    PlaySound(TEXT("bg.wav"), NULL, SND_FILENAME | SND_ASYNC);

    vector<int> playerArmy;
    vector<int> enemyArmy;
    vector<int> availableHextechDevices;

    cout << "---------------------------------------------------WELCOME TO HEX WARS--------------------------------------------------" << endl;
    cout << "------------------------------(this is a game based from the events in the TV series Arcane)----------------------------" << endl;
    sleep(4);
    system("cls");

    // Definitions (Noxus, Piltover, etc.)
    cout << "DEFINITIONS: " << endl << endl;
    cout << " NOXUS - Noxus is a ruthless and militaristic empire in Runeterra driven by the belief that strength and conquest define one's worth,where power is seized through cunning, war, and unyielding ambition."<<endl<<endl;
    sleep(2);
    cout << " PILTOVER - Piltover is a bustling, prosperous city in Runeterra, renowned for its advancements in science, trade, and \n innovation, making it a beacon of progress and culture." << endl << endl;
    sleep(2);
    cout << " HEXGEM - Hexgems are mysterious, magical crystals that serve as the core energy source for Hextech inventions, \n amplifying the magic within to power groundbreaking technologies." << endl << endl;
    sleep(2);
    cout << " HEXTECH - Hextech is a revolutionary form of magic-infused technology combining arcane power with \n mechanical ingenuity to create incredible devices and tools." << endl << endl;
    sleep(2);
    cout << " HEXGATES - Hexgates are advanced portals powered by Hextech allowing instant transportation across vast distances, \n revolutionizing travel and trade in Runeterra." << endl << endl;

    cout << "Press Space to continue...";
    while (!_kbhit()) {}

    system("cls");

    // Story
    string story = "The Noxians discovered the creation of the Hextech technology that uses the power of the Hexgems. Technology that can be weaponized and used to enslave other nations. Through espionage they concluded that the Hextech particularly beneath    the Hexgates is enough to empower every Noxian warrior and with this new power they can wage war against any country in  Runeterra. \n\n You as a general must ready your soldiers to battle and lead them to victory. Glory to the land of progress!!";
    typingEffect(story, 25);
    sleep(5);

    do {
        system("cls");
        string loading = "Generating Battle Field...";
        typingEffect(loading, 50);
        sleep(3);
        system("cls");

        // Generate 10 random Hextech devices
        for (int i = 0; i < 10; i++) {
            availableHextechDevices.push_back(rand() % 100 + 1);
        }

        // Display available Hextech Devices
        cout << "Choose 5 Piltover Soldiers (choose indices 0 to 9):" << endl;
        for (int i = 0; i < 10; i++) {
            cout << "Soldier " << i << ": Power Level " << availableHextechDevices[i] << endl;
        }

        // Player selects soldiers
        cout << "Enter 5 indices to select your soldiers:" << endl;
        for (int i = 0; i < 5; i++) {
            int index;
            cout << "Enter Soldier " << i + 1 << ": ";
            cin >> index;
            if (index >= 0 && index < 10) {
                playerArmy.push_back(availableHextechDevices[index]);
            } else {
                cout << "Invalid index. Please choose a valid number between 0 and 9." << endl;
                i--;
            }
        }

        // Build the heap for the player's army
          bool useMaxHeap = rand() % 2 == 0;

        if (useMaxHeap) {
        buildMaxHeap(playerArmy);
        } else {
        buildMinHeap(playerArmy);
        }
        do{

        system("cls");

        // Display the player's army
        cout << "\nYour Army:" << endl;
        display(playerArmy, "Piltover's Army");

            cout<<"1. Delete Soldier"<<endl;
            cout<<"2. Search for a Soldier"<<endl;
            cout<<"3. Proceed with Battle"<<endl;
            cout<<"Enter choice: ";
            cin>>choice;

             int value;
            switch (choice) {
            case 1:
                int index;
                cout << "Enter value to delete: ";
                cin >> value;
                deleteSoldier(playerArmy, value);
                system("cls");
                cout<<value<<" deleted..."<<endl<<endl;
                for (int i = 0; i < 10; i++) {
                cout << "Soldier " << i << ": Power Level " << availableHextechDevices[i] << endl;
                }
                cout<<"Enter Index to be Inserted: ";
                cin >> index;
                if (index >= 0 && index < 10) {
                playerArmy.push_back(availableHextechDevices[index]);
                cout<<"Soldier Inserted";
                } else {
                cout << "Invalid index. Please choose a valid number between 0 and 9." << endl;
                }
                break;
            case 2:
                cout << "Enter value to search: ";
                cin >> value;
               if (search(playerArmy, value)) {
               cout << "Soldier with power " << value << " found!" << endl;
               } else {
               cout << "Soldier with power " << value << " not found!" << endl;
            }
                break;
            case 3:
                break;
            default:
                cout << "Invalid option, please try again.\n";
        }
        cout<<endl<<"Are you sure about this general? [Y/N]: ";
        cin>>pin;
        }while(pin=='N');
        pin = NULL;

        sleep(4);

        cout<<endl;
        // Generate enemy army
        loading = "The Noxians are gathering their forces...";
        typingEffect(loading, 50);
        sleep(3);

        for (int i = 0; i < 5; i++) {
            enemyArmy.push_back(rand() % 100 + 1);
        }

        // Build the heap for the player's army
        if (useMaxHeap) {
        buildMaxHeap(enemyArmy);
        } else {
        buildMinHeap(enemyArmy);
        }

        // Display enemy army
        cout << "\nThe Noxians' Army:" << endl;
        display(enemyArmy, "Noxian Army");

        // Battle simulation
        sleep(6);
        system("cls");
        cout << "\nTHE HEX WARS BEGINS!" << endl;
        battle(playerArmy, enemyArmy);

        // Additional feature: Traversals
        cout << "\nPreorder Traversal of your army: ";
        preorderTraversal(playerArmy, 0);
        cout << "\nInorder Traversal of your army: ";
        inorderTraversal(playerArmy, 0);
        cout << "\nPostorder Traversal of your army: ";
        postorderTraversal(playerArmy, 0);
        cout << endl;

        sleep(2);
        cout << endl << endl;
        cout << "FIGHT AGAIN? [Y/N]: ";
        cin >> pin;

        if (pin == 'N') {
            system("cls");
            cout << "GOOD FIGHT GENERAL!";
        }

    } while (pin == 'Y');

    return 0;
}
