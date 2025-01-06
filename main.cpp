#include<iostream>
#include<fstream>
#include <unistd.h>
#include <vector>
#include <string>
#include <algorithm> // For find_if
#include <sstream>

using std::endl;
using std::string;
using std::cout;
using std::cin;

struct Contacts{
    int id;
    string name;
    string number;
};

const string fileNamer = "contacts.txt";

std::vector<Contacts>contact{};

int id{0};

void saveToFile(){
    std::ofstream saveFile(fileNamer, std::ios::trunc);
    for(const auto& item : contact){
        saveFile<< "Id: " << item.id  << ".  Name: " << item.name << ".  Phone number: " << item.number << endl;
    }
    saveFile.close();
}

void loadFile() {
    std::ifstream readFile(fileNamer);

    if (!readFile) {
        cout << "File not found or could not be opened!" << endl;
        return;
    }
    contact.clear();
    string line;
    while (std::getline(readFile, line)) {
        std::istringstream iss(line);
        Contacts c;

        string prefix;
        if (iss >> prefix >> c.id >> prefix >> c.name >> prefix >> prefix >> prefix >> c.number) {
            contact.push_back(c);
        }
    }

    readFile.close();
    cout << "Contacts loaded from file!" << endl;
}



void adder(){
    Contacts c;
    cout << "############################\n\n" << endl;

    cout << "Enter a name: ";
    string name{""};
    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    getline(cin, name);
    cout << "For " << name <<  " add a phone number: ";
    string phoneNumber{""};
    getline(cin, phoneNumber);
    if(phoneNumber.length() != 9){
        cout << "Phone number not valid!" << endl;
        return;
    }
    c.name = name;
    c.number = phoneNumber;
    c.id = id;
    id++;
    contact.push_back(c);
    cout << "Contact added!" << endl;
    saveToFile();

}

void remover(){
    for(const auto& item: contact){
        cout << "########################\n"
             << "Id: " << item.id << "\nName: " << item.name << "\nPhone number: " << item.number
             << "\n########################" << endl;
    }
    cout << "Enter a users id: " << endl;
    int idNum{0};
    cin >> idNum;

    auto it = std::find_if(contact.begin(),contact.end(),[idNum](Contacts& contacts){
        return contacts.id == idNum;
    });

    if(it != contact.end()){
        contact.erase(it);
        cout << "User with id: " << idNum << " was deleted!" << endl;
         saveToFile();
    }else{
        cout << "There is no user with that id!" << endl;
    }
    
   
}


void searchById(){
    cout << "Enter an id: ";
    int idFinder{0};
    cin >> idFinder;
    auto finder = std::find_if(contact.begin(),contact.end(),[idFinder](Contacts& contact){
        return contact.id == idFinder;
    });

    if(finder != contact.end()){
        Contacts v;
        cout << "User found!" << "\nName: " << finder->name  << "\nPhone number: " << finder->number  << "\nID: " << finder->id << "\n1.Delete\n2.Edit\n3.Exit\nSelect: ";
        int chooser{0};
        cin >> chooser;
        if(chooser == 1){
            contact.erase(finder);
            cout << "User with id: " << idFinder << ". Was removed!" << endl;
        }else if(chooser == 2){
           cout << "Enter a new name: (leave blank to keep the name!)\nSelect: ";
           string name{""};
           cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
           getline(cin , name);


           if(!name.empty()){
            finder->name = name;
           }

           cout << "Enter a new phone number: (Leave blank if you want to keep the old one!)\nSelect: ";
            string number{""};
            cin >> number;

            if(!number.empty()){
                finder->number = number;
            }

            cout << "Contact changed!" << endl;
            saveToFile();
        }else{
            cout << "ID not found! " << endl;
            return;
        }
            
        

    }
}
void searchByName(){
    cout << "Enter a name: ";
    string name{""};
    cin >> name;
    auto findName = std::find_if(contact.begin(),contact.end(),[name](Contacts& contact){
        return contact.name == name;
    });
    if(findName != contact.end()){
        Contacts v;
        cout << "User found!" << "\nName: " << findName->name << "\nPhone number: " << findName->number << "\nID: " << findName->id << "\n1.Delete\n2.Exit\nSelect: ";
        int chooser{0};
        cin >> chooser;
        if(chooser == 1){
            contact.erase(findName);
            cout << "User with id: " << name << ". Was removed!" << endl;
        }else if(chooser == 2){
            cout << "Enter a new name: (leave blank to keep the name!)\nSelect: ";
           string name{""};
           cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
           getline(cin, name);

           if(!name.empty()){
            findName->name = name;
           }

           cout << "Enter a new phone number: (Leave blank if you want to keep the old one!)\nSelect: ";
            string number{""};
            cin >> number;

            if(!number.empty()){
                findName->number = number;
            }

            cout << "Contact changed!" << endl;
            saveToFile();
        }else{
            cout << "ID not found! " << endl;
            return;
        }
        
    }
}
void checker(){
    for(const auto& item: contact){
        cout << "########################\n"
             << "Id: " << item.id << "\nName: " << item.name << "\nPhone number: " << item.number
             << "\n########################" << endl;
    }
    cout << "1.Search by id\n2.Search by name\n3.Back\nSelect: " ;
    int chooser{0};
    cin >> chooser;
    switch (chooser)
    {
    case 1:
        searchById();
        break;
    case 2:
        searchByName();
        break;
    default:
        break;
    } 
}

void sorter(){
    cout << "1.Sort by name\n2.Sort by id\nSelect: ";
    int chooser{0};
    cin >> chooser;
    if (chooser == 1){
        std::sort(contact.begin(),contact.end(),[](Contacts& a, Contacts& b){
            return a.name < b.name;
            saveToFile();
        });
    }else if(chooser == 2){
        std::sort(contact.begin(),contact.end(),[](Contacts& a , Contacts& b){
            return a.id < b.id;
            saveToFile();
        });
    }else{
        cout << "Unknow operator!" << endl;
        return;
    }
}

void exiter(){
    cout << "Are you sure you want to exit (y/n)\nType here: ";
    char typer{};
    cin >> typer;
    if(typer == 'y'){
        cout << "Goodbye!" << endl;
        exit(0);
    }else if(typer == 'n'){
        return;
    }
}

void openContactFile(){
    std::ifstream fileName(fileNamer);

    if(!fileName){
        cout << "File not found!" << endl;
        return;
    }

    string command = string("open ") + fileNamer;
    int result = system(command.c_str());
    if (result != 0) {
        cout << "Failed to open the file!" << endl;
    }
}

int main(){
    cout << "Contact list!" << endl;
    while(true){
    cout << "##################################" << endl;
    cout << "1.Add contact\n2.Remove contact\n3.Check contacts\n4.Sort contacts\n5.Open file\n6.Exit\nSelect here: ";
    int chooser{0};
    cin >> chooser;
    cout << "----------------------------------" << endl;
    switch(chooser){
        case 1:
        adder();
        break;

        case 2:
        remover();
        break;

        case 3:
        checker();
        break;

        case 4:
        sorter();
        break;

        case 5:
        openContactFile();
        break;

        case 6:
        exiter();
        break;
    }
    }
}