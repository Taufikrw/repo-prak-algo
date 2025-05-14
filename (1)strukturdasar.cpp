#include <iostream>
using namespace std;

struct PtbNode {
    int data;    // Menyimpan nilai PtbNode
    PtbNode *left;  // Pointer ke anak kiri
    PtbNode *right; // Pointer ke anak kanan

    // untuk inisialisasi PtbNode baru
    PtbNode(int val) {
        data = val;
        left = right = nullptr; // awalnya ga punya anak
    }
};

int main() {
    // Membuat PtbNode secara manual
    PtbNode *root = new PtbNode(15);
    root->left = new PtbNode(10);
    root->right = new PtbNode(20);
    root->left->left = new PtbNode(8);
    root->left->right = new PtbNode(12); 

    // Output untuk cek pohon
    cout << "Root: " << root->data << endl;
    cout << "Anak kiri root: " << root->left->data << endl;
    cout << "Anak kanan root: " << root->right->data << endl;
    cout << "Anak kiri dari PtbNode 2: " << root->left->left->data << endl;
    cout << "Anak kanan dari PtbNode 2: " << root->left->right->data << endl;

    return 0;
}

