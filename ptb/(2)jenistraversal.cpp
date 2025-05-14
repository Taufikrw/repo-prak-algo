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

int main() {
    PtbNode *root = new PtbNode(15);
    root->left = new PtbNode(10);
    root->right = new PtbNode(20);
    root->left->left = new PtbNode(8);
    root->left->right = new PtbNode(12); 

    cout << "Preorder: ";
    preorder(root);
    cout << "\nInorder: ";
    inorder(root);
    cout << "\nPostorder: ";
    postorder(root);

    return 0;
}
