#include <iostream>

using namespace std;

struct Mahasiswa
{
    char nama[50];
    int nim;
};

struct Node
{
    Mahasiswa data;
    Node *left;
    Node *right;

    Node(Mahasiswa data)
    {
        this->data = data;
        left = nullptr;
        right = nullptr;
    }
};

void insertMahasiswa(Node *&root, Mahasiswa data)
{
    if (root == nullptr)
    {
        root = new Node(data);
        return;
    }
    Node *current = root;
    while (true)
    {
        if (data.nim < current->data.nim)
        {
            if (current->left == nullptr)
            {
                current->left = new Node(data);
                return;
            }
            current = current->left;
        }
        else
        {
            if (current->right == nullptr)
            {
                current->right = new Node(data);
                return;
            }
            current = current->right;
        }
    }
}

Mahasiswa *getDetailMahasiswa(Node *root, int nim)
{
    Node *current = root;
    while (current != nullptr)
    {
        if (nim == current->data.nim)
        {
            return &current->data;
        }
        else if (nim < current->data.nim)
        {
            current = current->left;
        }
        else
        {
            current = current->right;
        }
    }
    return nullptr;
}

void tampilkanMahasiswa(Node *root)
{
    if (root == nullptr)
        return;
    tampilkanMahasiswa(root->left);
    cout << "Nama: " << root->data.nama << ", NIM: " << root->data.nim << endl;
    tampilkanMahasiswa(root->right);
}

void insertMahasiswaToFile(Mahasiswa mhs)
{
    FILE *file;
    file = fopen("mahasiswa.dat", "ab");
    if (file == nullptr)
    {
        cout << "File tidak ditemukan" << endl;
        return;
    }
    fwrite(&mhs, sizeof(Mahasiswa), 1, file);
    fclose(file);
}

void getMahasiswaFromFile(Node *&root)
{
    FILE *file;
    file = fopen("mahasiswa.dat", "rb");
    if (file == nullptr)
    {
        cout << "File tidak ditemukan" << endl;
        return;
    }
    Mahasiswa mhs;
    while (fread(&mhs, sizeof(Mahasiswa), 1, file))
    {
        if (getDetailMahasiswa(root, mhs.nim) == nullptr)
        {
            insertMahasiswa(root, mhs);
        }
    }
    fclose(file);
}

void deleteMahasiswa(Node *&root, int nim)
{
    if (root == nullptr)
        return;

    if (nim < root->data.nim)
    {
        deleteMahasiswa(root->left, nim);
    }
    else if (nim > root->data.nim)
    {
        deleteMahasiswa(root->right, nim);
    }
    else
    {
        Node *temp = root;
        if (root->left == nullptr)
        {
            root = root->right;
        }
        else if (root->right == nullptr)
        {
            root = root->left;
        }
        else
        {
            Node *successor = root->right;
            while (successor->left != nullptr)
                successor = successor->left;
            root->data = successor->data;
            deleteMahasiswa(root->right, successor->data.nim);
            return;
        }
        delete temp;
    }
}

void preOrderTraversal(Node *root, FILE *file)
{
    if (root == nullptr)
        return;
    fwrite(&root->data, sizeof(Mahasiswa), 1, file);
    preOrderTraversal(root->left, file);
    preOrderTraversal(root->right, file);
}

void deleteMahasiswaFromFile(Node *root)
{
    FILE *file = fopen("mahasiswa.dat", "wb");
    if (file == nullptr)
    {
        cout << "File tidak ditemukan" << endl;
        return;
    }
    preOrderTraversal(root, file);
    fclose(file);
}

int main()
{
    Node *root = nullptr;
    Mahasiswa mhs;
    Mahasiswa *foundMhs = nullptr;
    int choice;

    while (choice != 0)
    {
        getMahasiswaFromFile(root);
        cout << "Menu:\n";
        cout << "1. Insert Mahasiswa\n";
        cout << "2. Search Mahasiswa\n";
        cout << "3. Tampilkan Data Mahasiswa\n";
        cout << "4. Hapus Mahasiswa\n";
        cout << "0. Exit\n";
        cout << "Pilih menu: ";
        cin >> choice;
        system("clear");
        switch (choice)
        {
        case 1:
            cout << "Nama: ";
            cin.ignore();
            cin.getline(mhs.nama, 50);
            cout << "NIM: ";
            cin >> mhs.nim;
            if (getDetailMahasiswa(root, mhs.nim) != nullptr)
            {
                cout << "Mahasiswa dengan NIM " << mhs.nim << " sudah ada.\n";
                break;
            }
            insertMahasiswaToFile(mhs);
            break;

        case 2:
            int nim;
            cout << "Masukkan NIM yang dicari: ";
            cin >> nim;
            foundMhs = getDetailMahasiswa(root, nim);
            if (foundMhs != nullptr)
            {
                cout << "Mahasiswa dengan NIM " << foundMhs->nim << " ditemukan.\n";
                cout << "Detail Mahasiswa:\n";
                cout << "Nama: " << foundMhs->nama << "\n";
                cout << "NIM: " << foundMhs->nim << "\n";
            }
            else
            {
                cout << "Mahasiswa dengan NIM " << nim << " tidak ditemukan.\n";
            }
            break;

        case 3:
            cout << "Daftar Mahasiswa:\n";
            tampilkanMahasiswa(root);
            break;

        case 4:
            cout << "Masukkan NIM yang ingin dihapus: ";
            cin >> mhs.nim;
            if (getDetailMahasiswa(root, mhs.nim) == nullptr)
            {
                cout << "Mahasiswa dengan NIM " << mhs.nim << " tidak ditemukan.\n";
                break;
            }
            deleteMahasiswa(root, mhs.nim);
            deleteMahasiswaFromFile(root);
            break;

        case 0:
            cout << "Keluar dari program.\n";
            break;

        default:
            cout << "Pilihan tidak valid.\n";
        }
    }

    return 0;
}