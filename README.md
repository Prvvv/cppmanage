# cppmanage
A simple but efficient local password manager written in C++

## About 

cppmanage is a simple but efficient password manager for almost any ***windows*** system that automatically stores login and password data to the local system using a clean & minimalist terminal via the windows system, it uses 3 layers off security to get to the passwords:

- Keyfile
- Hardcoded password
- Hardcoded Encryption key

## Features

#### Encryption
cppmanage automatically encrypts saved login data to a text file using an ***encryption key*** client/server method stored locally on the machine and decrypt the login information application side when viewing.

#### Management
cppmanage can view, remove, update and add new username and password entires in the format of ***username:password*** and due to the encrypted state, filelogged memory the program uses can store all data for an indefinite amount of time until manual deleteion of the entry by the user

```
[1] View account and passwords
[2] Add account & password
[3] Remove account by index
[0] Exit

Select an option:
```

#### Portability
Due to the simple nature of the programming behind cppmanage you can completely transport your passwords securely without the risk of compromise to the user due to the passworded and file application side encryption/decryption methods, just copy and paste both text file and program executable along with the keyfile to move to a new system and its done! - and it does not matter if you lose the file containing passwords, unless you keep your current encryption key unguessable and safe, the contents cannot be accessed.


#### Setup

Just change the following lines of source code of the .cpp file to configure encryption key, password and keyfile key:

```
string systempassword = "";
string key = "";
string storagefile = "storage.txt";
std::string filename = "keyfile.txt";
string keyfile_contents = "";
```

Then compile the code into an executable format and run the program with the 2 files along side it:

![](https://i.ibb.co/DpZWDbh/files.png)







