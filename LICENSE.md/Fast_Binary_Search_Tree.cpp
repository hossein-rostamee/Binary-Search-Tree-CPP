#include<iostream>
#include<algorithm>
#include<vector>
using namespace std;

class BST {

	struct Node {
		int index;
		Node* left; Node* right;
		Node(int index) : index(index), left(NULL), right(NULL) { }
	};

	struct Range { int a, b; int size; Range(int a, int b) : a(a), b(b), size(b-a+1) {} };

public:
	Node* root = NULL;

	void Create() {
		if (!buffer.size()) return;
		sort(buffer.begin(), buffer.end(), this->CMP);

		int v = buffer.size() / 2;
		root = &buffer[v];
		BST_REC(root, v, Range(0, v-1), Range(v+1, buffer.size()-1));
	}

	void BST_REC(Node* parent, int parentPlace, Range r1, Range r2) {
		if (r1.size > 0) {
			int v = r1.a + r1.size / 2; parent->left = &buffer[v];
			if (r1.size > 1) {
				BST_REC(&buffer[v], v, Range(r1.a, v - 1), Range(v + 1, r1.b));
			}
		}
		else { parent->left = NULL; }
		if (r2.size > 0) {
			int v = r2.a + r2.size / 2; parent->right = &buffer[v];
			if (r2.size > 1) {
				BST_REC(&buffer[v], v, Range(r2.a, v - 1), Range(v + 1, r2.b));
			}
		}
		else { parent->right = NULL; }
	}

	//00000000000000000000000000000000000000000000

	bool ContainsKey(int v) {
		Node* n = root;
		while (n != NULL) {
			if (n->index == v) return true;
			if (v > n->index) n = n->right;
			else n = n->left;
		}
		return false;
	}

	//00000000000000000000000000000000000000000000

	//--------------------------------------------

	void Display() { cout << "---------------------\nROOT "; Display_REC(root); cout << "---------------------\n"; }

	void Display_REC(Node* n) {
		if (n == NULL) return; cout << "index: " << n->index << " }-> ";
		if (n->right) {
			cout << "right: " << n->right->index << " , ";
		}
		if (n->left) {
			cout << "left: " << n->left->index;
		}
		cout << "\n";
		if (n->right) Display_REC(n->right);
		if (n->left) Display_REC(n->left);
	}

	//--------------------------------------------

	void ADD(int value) { buffer.push_back(Node(value)); }
	void Remove(int value) {
		auto it = buffer.begin();
		for (; it != buffer.end(); it++) { if (it->index == value) { buffer.erase(it); break; } }
	}

	void ADD_Create(int value) { ADD(value); Create(); }
	void Remove_Create(int value) { Remove(value); Create(); }

private:
	vector<Node> buffer;

	static bool CMP(const Node& A, const Node& B) { return A.index < B.index; }
};


int main() {
	BST bst;
	bst.ADD(77);
	bst.ADD(5);
	bst.ADD(3);
	bst.ADD(6);
	bst.ADD(7);
	bst.ADD(2);
	bst.ADD(1);
	bst.ADD(10);
	bst.ADD(11);
	bst.ADD(777);

	bst.Remove(11);
	cout << "11 was removed\n";

	bst.Create();
	cout << "BST Created\n";

	bst.Display();
	//---------------------------
	cout << (bst.ContainsKey(11) ? "Value Found\n" : "Not Found\n");
	cout << (bst.ContainsKey(77) ? "Value Found\n" : "Not Found\n");
}
