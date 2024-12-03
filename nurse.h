//
// Created by lebona on 2024/10/25.
//

#ifndef NURSE_H
#define NURSE_H

void nurseMenu() {
    int option;
    cout << endl;
    cout << endl;
    cout << endl;
    cout << endl;
    cout << endl;
    cout << "##############################################################" << endl;
    cout << "#                        Nurse's Menu                        #" << endl;
    cout << "##############################################################" << endl;
    cout << "1. Display Vaccination record" << endl;
    cout << "2. Create vaccination record" << endl;
    cout << "3. Edit vaccination record" << endl;
    cout << "4. Delete vaccination record" << endl;
    cout << "5. Exit" << endl;
    cout << endl;
    cout << "Enter option: ";
    cin >> option;
}


void registerNurse() {
    nurse nurse;
    cout << "\nRegistering Nurse" << endl;
    cout << "Enter First Name: ";
    cin >> nurse.first_name;
    cout << "Enter Last Name: ";
    cin >> nurse.last_name;
    cout << "Enter Title(Default:Sister): ";
    cin >> nurse.title;
    cout << "Practice Number: ";
    cin >> nurse.practice_number;
    cout << "Hospital Name: ";
    cin >> nurse.hospital;
    cout << "Hospital Address: ";
    cin >> nurse.hospital_address;
    cout << "Cellphone Number: ";
    cin >> nurse.cellphone;
    cout << "Enter password: ";
    cin >> nurse.password;

    // Save to CSV file
    ofstream outFile("users.csv", ios::app);
    if (outFile.is_open()) {
        outFile << "nurse" <<','<< nurse.first_name << "," << nurse.last_name << "," << nurse.practice_number << "," << nurse.hospital << "," << nurse.hospital_address <<","<< nurse.password << "," << nurse.cellphone << endl;
        outFile.close();
        cout << "Nurse registration complete and saved!\n";
    } else {
        cout << "Unable to open file for writing.\n";
    }
}

void registerVaccine() {
    vaccination vaccination;
    cout << "##############################################################" <<endl;
    cout << "#                     Registering Vaccination                #" << endl;
    cout << "##############################################################" <<endl;
    cout << "Enter treatment: ";
    cin >> vaccination.treatment;
    cout << "Enter Vaccine: ";
    cin >> vaccination.vaccine;
    cout << "Enter child's record id: ";
    cin >> vaccination.child_record_id;
    cout << "Enter child's weight: ";
    cin >> vaccination.weight;
    cout << "Enter child's height: ";
    cin >> vaccination.height;
    cout << "Enter Nurses name: ";
    cin >> vaccination.nurse;
    cout << "Enter clinic: ";
    cin >> vaccination.clinic;
    cout << "Enter clinic date: ";
    cin >> vaccination.clinic_date;
    cout << "Enter next clinic date :";
    cin >> vaccination.next_clinic_date;

    ofstream outFile("vaccination_table.csv", ios::app);
    if (outFile.is_open()) {
        outFile << vaccination.treatment << "," << vaccination.vaccine << "," << vaccination.child_record_id << "," << vaccination.weight<< "," << vaccination.height << "," << vaccination.nurse << "," << vaccination.clinic << "," << vaccination.clinic_date << "," << vaccination.next_clinic_date<< endl;
        outFile.close();
        cout << "Vaccination record registration complete and saved!\n";
    } else {
        cout << "Unable to open file for writing.\n";
    }

}

// Function to read vaccine data from vaccine_table.csv
vector<vaccination> readVaccineData(const string& filename) {
    vector<vaccination> vaccineRecords;
    ifstream file(filename);
    string line;

    while (getline(file, line)) {
        stringstream ss(line);
        vaccination record; // Directly use the vaccination struct

        getline(ss, record.treatment, ',');
        getline(ss, record.vaccine, ',');
        getline(ss, record.child_record_id, ',');
        getline(ss, record.weight, ',');
        getline(ss, record.height, ',');
        getline(ss, record.nurse, ',');
        getline(ss, record.clinic, ',');
        getline(ss, record.clinic_date, ',');
        getline(ss, record.next_clinic_date, ',');

        vaccineRecords.push_back(record);
    }
    return vaccineRecords;
}

#endif //NURSE_H
