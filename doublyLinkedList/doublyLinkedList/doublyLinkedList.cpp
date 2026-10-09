#include <iostream>
#include <conio.h>

using namespace std;

struct Node {
	int id;
	int data;
	Node* next;
	Node* prev;

	Node(int id = 0, int value = 0, Node* pNext = nullptr, Node* pPrev = nullptr) : id(id), data(value), next(pNext), prev(pPrev) {
	}
};

int randomId = 0;

static void logList(Node* node) {
	if (node == nullptr) {
		cout << "List is empty" << endl << endl;
		return;
	}
	Node* current = node;
	while (current != nullptr) {
		cout << "Node ID: " << current->id << endl;
		cout << "Node data: " << current->data << endl;

		if (current->next != nullptr) {
			cout << "Next node data: " << current->next->data << endl;
		}
		else {
			cout << "Next node data: nullptr" << endl;
		}
		if (current->prev != nullptr) {
			cout << "Previous node data: " << current->prev->data << endl;
		}
		else {
			cout << "Previous node data: nullptr" << endl;
		}
		current = current->next;
		cout << endl;
	}
}

static void freeList(Node*& head, Node*& tail) {
	Node* current = head;
	while (current != nullptr) {
		Node* nextNode = current->next;
		delete current;
		current = nextNode;
	}
	head = nullptr;
	tail = nullptr;
}

static void pushNode(Node*& head, Node*& tail, int data) {
	Node* newNode = new Node(randomId, data, nullptr, tail);
	randomId++;

	if (head == nullptr) {
		head = newNode;
		tail = newNode;
	}
	else {
		tail->next = newNode;
		tail = newNode;
	}
}

static Node* findNodeByID(Node* head, int id) {
	Node* current = head;
	while (current != nullptr) {
		if (current->id == id) {
			return current;
		}
		current = current->next;
	}
	return nullptr;
}

static void editNode(Node* node, int data) {
	if (node != nullptr) {
		node->data = data;
	}
}

static void deleteNode(Node*& head, Node*& tail, int id) {
	Node* nodeToDelete = findNodeByID(head, id);
	if (nodeToDelete != nullptr) {
		if (nodeToDelete->prev != nullptr) {
			nodeToDelete->prev->next = nodeToDelete->next;
		}
		else {
			head = nodeToDelete->next;
		}

		if (nodeToDelete->next != nullptr) {
			nodeToDelete->next->prev = nodeToDelete->prev;
		}
		else {
			tail = nodeToDelete->prev;
		}

		delete nodeToDelete;
	}
}

int main()
{
	Node* head = nullptr;
	Node* tail = nullptr;

	while (true) {
		cout << "=== LIST ===" << endl;
		logList(head);

		cout << endl << "1. Push Node" << endl;
		cout << "2. Edit Node" << endl;
		cout << "3. Delete Node" << endl;
		cout << "4. Exit" << endl << endl;
		cout << "Enter choice: ";

		char key = _getch();
		cout << key << endl << endl;

		switch (key) {
		case '1': {
			cout << "Enter node data (number): ";
			int number;
			cin >> number;
			pushNode(head, tail, number);
			break;
		}
		case '2': {
			cout << "Enter node ID to edit: ";
			int id;
			cin >> id;
			Node* nodeToEdit = findNodeByID(head, id);
			if (nodeToEdit != nullptr) {
				cout << "Enter new node data (number): ";
				int newData;
				cin >> newData;
				editNode(nodeToEdit, newData);
			}
			break;
		}
		case '3': {
			cout << "Enter node ID to delete: ";
			int id;
			cin >> id;
			deleteNode(head, tail, id);
			break;
		}
		case '4':
			freeList(head, tail);
			return 0;
		default:
			cout << "Invalid choice!" << endl;
			break;
		}
		cout << "\n---------------------------------\n" << endl;

		system("cls");
	}

	return 0;
}
