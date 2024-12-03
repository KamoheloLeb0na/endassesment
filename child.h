//
// Created by lebona on 2024/10/25.
//

#ifndef CHILD_H
#define CHILD_H

void childMenu() {
    int option;
    cout << endl;
    cout << endl;
    cout << endl;
    cout << endl;
    cout << endl;
    cout << "##############################################################" << endl;
    cout << "#                        Parent's Menu                       #" << endl;
    cout << "##############################################################" << endl;
    cout << "1. Display Vaccination record";
    cout << "2. Display Record record";
    cout << "3. Exit";
    cout << endl;
    cout << "Enter option: ";
    cin >> option;
}


string child_record_id;
string generateKey(string name, string surname,string dob,int record_number) {
    if(name.length() >= 3 && surname.length() >= 3) {
        child_record_id =  name.substr(0,3) + "-" + surname.substr(0,3) + "-" + dob + "-" + to_string(record_number);
    }
    return child_record_id;
}

// Function to read child data from users_table.csv
vector<child> readChildData(const string& filename) {
    vector<child> childRecords;
    ifstream file(filename);
    string line;

    while (getline(file, line)) {
        stringstream ss(line);
        child record;

        getline(ss, record.first_name, ',');
        getline(ss, record.last_name, ',');
        getline(ss, record.middle_name, ',');
        getline(ss, record.date_of_birth, ',');
        getline(ss, record.mother, ',');
        getline(ss, record.father, ',');
        getline(ss, record.village, ',');
        getline(ss, record.chief, ',');
        getline(ss, record.district, ',');
        getline(ss, record.password, ',');

        childRecords.push_back(record);
    }
    return childRecords;
}

int getNextRecordNumber() {
    ifstream inFile("users.csv");
    string line;
    int maxRecordNumber = 0;

    if (inFile.is_open()) {
        while (getline(inFile, line)) {
            stringstream ss(line);
            string type, recordNumber;
            getline(ss, type, ',');  // Skip the type field (e.g., "child")

            if (getline(ss, recordNumber, ',')) {  // Get the record number
                try {
                    // Convert recordNumber to an integer
                    int currentRecordNumber = stoi(recordNumber);
                    if (currentRecordNumber > maxRecordNumber) {
                        maxRecordNumber = currentRecordNumber;
                    }
                } catch (invalid_argument& e) {
                    // Skip if recordNumber is not a valid integer
                    // cout << "Warning: Invalid record number in file: " << recordNumber << endl;
                    continue;
                }
            }
        }
        inFile.close();
    } else {
        cout << "Unable to open file for reading.\n";
    }
    return maxRecordNumber + 1;  // Next record number
}


void registerChildRecord() {
    child childRecord;
    cout << "##############################################################" << endl;
    cout << "#                  Registering Child Record                  #" << endl;
    cout << "##############################################################" << endl;
    // Prompt for child details
    cout << "Enter First Name: ";
    cin >> childRecord.first_name;
    cout << "Enter Last Name: ";
    cin >> childRecord.last_name;
    cout << "Enter Middle Name: ";
    cin >> childRecord.middle_name;
    cout << "Enter Date of Birth: ";
    cin >> childRecord.date_of_birth;
    cout << "Enter Mother's Name: ";
    cin >> childRecord.mother;
    cout << "Enter Father's Name: ";
    cin >> childRecord.father;
    cout << "Enter Village: ";
    cin >> childRecord.village;
    cout << "Enter Chief's Name: ";
    cin >> childRecord.chief;
    cout << "Enter District: ";
    cin >> childRecord.district;
    cout << "Enter Password: ";
    cin >> childRecord.password;
    int number = getNextRecordNumber();

    // Generate the unique key
    string childRecordId = generateKey(childRecord.first_name, childRecord.last_name, childRecord.date_of_birth, number);

    // Append to CSV file
    ofstream outFile("users.csv", ios::app);
    if (outFile.is_open()) {
        outFile << "child" << "," << number << "," << childRecord.first_name << "," << childRecord.last_name << "," << childRecord.middle_name << "," << childRecord.date_of_birth << "," << childRecord.mother << "," << childRecord.father << "," << childRecord.village << "," << childRecord.chief << "," << childRecord.district << "," << childRecord.password << "," << childRecordId << endl;
        outFile.close();

        cout << "Child record registration complete and saved!\n";
    } else {
        cout << "Unable to open file for writing.\n";
    }
}

#endif //CHILD_H
