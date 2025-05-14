#include <iostream>
using namespace std;

struct PtbNode {
    int data;
    PtbNode *left;
    PtbNode *right;

    PtbNode(int val) {
        data = val;
        left = right = nullptr;
    }
};

void insert(PtbNode *&root, int value) {
    if (root == nullptr) {
        root = new PtbNode(value); // Kalau kosong, jadikan root
        return;
    }

    PtbNode *curr = root;
    while (true) { // selama belum return, dan kondisinya true, berarti sesuai
        if (value < curr->data) {
            if (curr->left == nullptr) {
                curr->left = new PtbNode(value);
                return;
            }
            curr = curr->left; // geser ke kiri
        } else {
            if (curr->right == nullptr) {
                curr->right = new PtbNode(value);
                return;
            }
            curr = curr->right; // geser ke kanan
        }
    }
}

void preorder(PtbNode *root) { // Preorder (Root → Kiri → Kanan)
    // Kalau udah nyampe leaf (daun tanpa anak), berenti
    if (root == nullptr) return;
    cout << root->data << " "; // Kunjungi root dulu
    preorder(root->left);      // Telusuri kiri
    preorder(root->right);     // Telusuri kanan
}

void inorder(PtbNode *root) { // Inorder (Kiri → Root → Kanan)
    if (root == nullptr) return;
    inorder(root->left);       // Telusuri kiri dulu
    cout << root->data << " "; // Kunjungi root
    inorder(root->right);      // Telusuri kanan
}

void postorder(PtbNode *root) { // Postorder (Kiri → Kanan → Root)
    if (root == nullptr) return;
    postorder(root->left);     // Telusuri kiri
    postorder(root->right);    // Telusuri kanan
    cout << root->data << " "; // Kunjungi root terakhir
}

// Binary Search Tree
void searchBST(PtbNode *root, int target) {
    PtbNode *curr = root;

    while (curr) { // Selama curr bukan nullptr
        if (curr->data == target) {
            cout << curr->data << " ditemukan" << endl;
            return; // Langsung berhenti setelah ketemu
        }
        curr = (target < curr->data) ? curr->left : curr->right;
    }

    cout << target << " tidak ditemukan" << endl;
}

PtbNode *search(PtbNode *root, int target) {
    PtbNode *curr = root;
    while (curr) {
        if (curr->data == target) {
            cout << target << " ditemukan\n";
            return curr;
        }
        curr = (target < curr->data) ? curr->left : curr->right;
    }
    cout << target << " tidak ditemukan\n";
    return nullptr;
}

int main() {
    PtbNode *root = nullptr;
    // Sisipkan angka
    insert(root, 15);
    insert(root, 20);
    insert(root, 10);
    insert(root, 8);
    insert(root, 12);
    insert(root, 17);
    insert(root, 25);
    searchBST(root, 17);
    search(root, 2);

    cout << "Preorder: ";
    preorder(root);
    cout << "\nInorder: ";
    inorder(root);
    cout << "\nPostorder: ";
    postorder(root);

    return 0;
}
