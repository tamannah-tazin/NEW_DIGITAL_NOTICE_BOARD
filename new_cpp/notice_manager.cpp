#include <iostream>
#include <fstream>
#include <string>
#include <cstdio>      // for remove()
#include <sys/stat.h>  // for mkdir()

using namespace std;

string base_folder = "notices/";

void createFolder() {
    struct stat info;
    if (stat(base_folder.c_str(), &info) != 0) {
#ifdef _WIN32
        system("mkdir notices");
#else
        mkdir("notices", 0777);
#endif
    }
}

void insertNotice() {
    string filename, line;
    cout << "Enter notice filename (without extension): ";
    cin >> filename;
    cin.ignore();

    ofstream out(base_folder + filename + ".txt");
    if (!out) {
        cout << "❌ Failed to create file.\n";
        return;
    }

    cout << "Enter notice content (type 'END' in a new line to finish):\n";
    while (true) {
        getline(cin, line);
        if (line == "END") break;
        out << line << "\n";
    }

    out.close();
    cout << "✅ Notice inserted: " << filename << ".txt\n";
}

void updateNotice() {
    string filename, line;
    cout << "Enter filename to update (without extension): ";
    cin >> filename;
    cin.ignore();

    string filepath = base_folder + filename + ".txt";
    ifstream in(filepath);
    if (!in) {
        cout << "❌ File not found.\n";
        return;
    }

    cout << "🔹 Existing content:\n";
    while (getline(in, line)) {
        cout << line << "\n";
    }
    in.close();

    cout << "\n🔄 Enter new content (type 'END' to finish):\n";
    ofstream out(filepath);
    while (true) {
        getline(cin, line);
        if (line == "END") break;
        out << line << "\n";
    }
    out.close();
    cout << "✅ Notice updated: " << filename << ".txt\n";
}

void deleteNotice() {
    string filename;
    cout << "Enter filename to delete (without extension): ";
    cin >> filename;

    string filepath = base_folder + filename + ".txt";
    if (remove(filepath.c_str()) == 0) {
        cout << "✅ Notice deleted: " << filename << ".txt\n";
    } else {
        cout << "❌ Could not delete. File may not exist.\n";
    }
}

int main() {
    createFolder();

    int choice;
    while (true) {
        cout << "\n======== Digital Notice Board (C++) ========\n";
        cout << "1. Insert Notice\n";
        cout << "2. Update Notice\n";
        cout << "3. Delete Notice\n";
        cout << "4. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore();

        if (choice == 1) insertNotice();
        else if (choice == 2) updateNotice();
        else if (choice == 3) deleteNotice();
        else if (choice == 4) break;
        else cout << "❗ Invalid choice. Try again.\n";
    }

    return 0;
}
