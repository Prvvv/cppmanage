#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cstring>

using namespace std;

string storagefile = "storage.txt";
std::string filename = "keyfile.txt";

string systempassword = "your-password";
string key = "your-secret-key";
string keyfile_contents = "contents-of-keyfile";


int check_system_key() {

    std::ifstream file(filename);

    if (file.is_open()) {

    } else {
        exit(0);
    }

    std::string line;
    while (getline(file, line)) {
        if(line == keyfile_contents){
            cout<<"\nKeyfile valid\n\n";
            string inp;
            cout<<"Password: ";
            cin >> inp;

            if(inp == systempassword){
                bool loggedin = true;
                continue;
            }
            else{
                cout<<"\nInvalid password\n\n";
                system("pause");
                exit(0);
            }
            }

        else{

            cout<<"\nInvalid keyfile contents!\n\n";
            system("PAUSE");
            exit(0);
        }
        }
    }

std::string XOREncryptDecrypt(const std::string& input, const std::string& key) {
    std::string result = input;
    for (size_t i = 0; i < input.length(); ++i) {
        result[i] = input[i] ^ key[i % key.length()];
    }
    return result;
}

std::string LoadAndDecryptData(const std::string& fileName, const std::string& key) {
    ifstream inputFile(fileName);
    if (!inputFile.is_open()) {
        cerr << "Error opening the file." << endl;
        return "";
    }

    string fileContents;
    string line;
    while (getline(inputFile, line)) {
        fileContents += line + "\n";
    }
    inputFile.close();

    return XOREncryptDecrypt(fileContents, key);
}
void SaveEncryptedData(const std::string& fileName, const std::string& data, const std::string& key) {
    std::string encryptedData = XOREncryptDecrypt(data, key);
    ofstream outputFile(fileName, ios::trunc);
    if (!outputFile.is_open()) {
        cerr << "Error opening the file." << endl;
        return;
    }

    outputFile << encryptedData;
    outputFile.close();
}

int menu() {
    cout << "\n[1] View account and passwords\n";
    cout << "[2] Add account & password\n";
    cout << "[3] Remove account by index\n";
    cout << "[0] Exit\n";
    cout << "\nSelect an option: ";
    int choice;
    cin >> choice;
    return choice;
}

void DisplayAccounts(const std::vector<std::string>& accounts) {
    if (accounts.empty()) {
        cout << "\n\nNo accounts found.\n\n" << endl;
        return;
    }

    cout << "\n\nStored Accounts:\n\n";
    for (size_t i = 0; i < accounts.size(); ++i) {
        cout << "[" << i << "] " << accounts[i] << endl;
    }
}

int main() {

    check_system_key();
    system("cls");

    string decryptedData = LoadAndDecryptData(storagefile, key);
    vector<string> accounts;
    size_t startPos = 0;
    size_t endPos;
    while ((endPos = decryptedData.find('\n', startPos)) != string::npos) {
        string account = decryptedData.substr(startPos, endPos - startPos);
        if (!account.empty()) {
            accounts.push_back(account);
        }
        startPos = endPos + 1;
    }

    while (true) {
        int choice = menu();

        if (choice == 0) {
            break;
        } else if (choice == 1) {
            DisplayAccounts(accounts);
        } else if (choice == 2) {
            string newAccount;
            cout << "\nEnter the new account (format: username:password): ";
            cin.ignore();
            getline(cin, newAccount);
            accounts.push_back(newAccount);

            decryptedData = "";
            for (const string& account : accounts) {
                decryptedData += account + "\n";
            }
            SaveEncryptedData(storagefile, decryptedData, key);

            cout << "\n\nAccount added successfully.\n\n";
        } else if (choice == 3) {
            DisplayAccounts(accounts);
            int accountIndex;
            cout << "\n\nEnter the index of the account to remove: ";
            cin >> accountIndex;

            if (accountIndex >= 0 && accountIndex < static_cast<int>(accounts.size())) {
                accounts.erase(accounts.begin() + accountIndex);
                decryptedData = "";
                for (const string& account : accounts) {
                    decryptedData += account + "\n";
                }

                SaveEncryptedData(storagefile, decryptedData, key);

                cout << "\n\nAccount removed successfully.\n\n";
            } else {
                cout << "\nInvalid account index.\n";
            }
        } else {
            cout << "\n\nInvalid choice. Please select a valid option.\n";
        }
    }
    return 0;
}
