//
// Created by lebona on 2024/10/25.
//

#ifndef DOCTOR_H
#define DOCTOR_H



void doctorMenu() {
    int option;
    cout << endl;
    cout << endl;
    cout << endl;
    cout << endl;
    cout << endl;
    cout << "##############################################################" << endl;
    cout << "#                        Doctor's Menu                       #" << endl;
    cout << "##############################################################" << endl;
    cout << "1. Display Vaccination record" << endl;
    cout << "2. Create vaccination record" << endl;
    cout << "3. Edit vaccination record" << endl;
    cout << "4. Delete vaccination record" << endl;

    cout << "5. Display Medical record" << endl;
    cout << "6. Create Medical record" << endl;
    cout << "7. Edit Medical record" << endl;
    cout << "8. Delete Medical record" << endl;
    cout << "9. Exit" << endl;
    cout << endl;
    cout << "Enter option: ";
    cin >> option;
}


// Function to register a doctor
void registerDoctor() {
    doctor doc;
    cout << "\nRegistering Doctor" << endl;
    cout << "Enter First Name: ";
    cin >> doc.first_name;
    cout << "Enter Last Name: ";
    cin >> doc.last_name;
    cout << "Enter Practice Number: ";
    cin >> doc.practice_number;
    cout << "Enter Hospital Name: ";
    cin >> doc.hospital;
    cout << "Enter Cellphone Number: ";
    cin >> doc.cellphone;
    cout << "Enter your password";
    cin >> doc.password;

    // Save to CSV file
    ofstream outFile("users.csv", ios::app);
    if (outFile.is_open()) {
        outFile << "doctor," << doc.first_name << "," << doc.last_name << "," << doc.practice_number << "," << doc.hospital << "," << doc.cellphone <<","<< doc.password<< endl;
        outFile.close();
        cout << "Doctor registration complete and saved!\n";
    } else {
        cout << "Unable to open file for writing.\n";
    }
}

void registerMedication() {
    medic medic;
    cout << "\nRegistering Medication" << endl;
    cout << "Enter treatment: ";
    cin >> medic.treatment;
    cout << "Enter medication: ";
    cin >> medic.medication;
    cout << "Enter child record: ";
    cin >> medic.child_record;
    cout << "Enter child weight: ";
    cin >> medic.weight;
    cout << "Enter height: ";
    cin >> medic.height;
    cout << "Enter Doctors name : ";
    cin >> medic.doctor;
    cout << "Enter Clinic : ";
    cin >> medic.clinic;
    cout << "Enter consultation date: ";
    cin >> medic.consultation_date;
    cout << "Enter checkup date: ";
    cin >> medic.checkup_date;

    ofstream outFile("medical_table.csv", ios::app);
    if (outFile.is_open()) {
        outFile << medic.treatment << "," << medic.medication << "," << medic.child_record << "," << medic.weight<< "," << medic.height << "," << medic.doctor << "," << medic.clinic << "," << medic.consultation_date << "," << medic.checkup_date << endl;
        outFile.close();
        cout << "Medical record registration complete and saved!\n";
    } else {
        cout << "Unable to open file for writing.\n";
    }
}

void nurse_main_menu(){
    vaccination vaccine;
    child child;
    doctor doctor;
    medic medication;
    string child_id_option;
    int main_menu_option ;
    string child_record_id;
    string name, surname, dob;

    cout << "Nurse Menu" << endl;
    cout << "1. Display vaccination report" << endl;
    cout << "2. Create vaccination record"  << endl;
    cout << "3. Display medical report" << endl;
    cout << "4. Search Child records" << endl;
    cout << "5. Search medical records" << endl;
    cout << "6. Search vaccination records" << endl;
    cout << "7. Logout" << endl;

    cout << "Choose: ";
    cin >> main_menu_option;

    switch (main_menu_option) {
    case 1:
        cout << "Enter child record id: ";
        cin >> child_record_id;
        generateReport(child_record_id, people, vaccines);
        break;
    case 2:
        registerVaccine();
        break;
    case 3:
        cout << "Enter child record id: ";
        cin >> child_record_id;
        generateMedicalReport(child_record_id, people, consultations);
        break;
    case 4:
        cout << "Enter name of kid: ";
        cin >> name;
        cout << "Enter surname of kid: ";
        cin >> surname;
        cout << "Enter their Date of Birth: ";
        cin >> dob;
        searchRecordsByNameAndDOB(name,surname,dob);
        break;

    case 5:
        cout << "Enter child record id: ";
        cin >> child_record_id;
        searchMedicalRecordsByID(child_record_id);
        break;
    case 6:
        cout << "Enter child record id: ";
        cin >> child_record_id;
        searchVaccinationRecordsByID(child_record_id);
        break;

    case 7:
        cout << "Loging out..." << endl;

        break;
    default:
        cout << "Exiting";

    }

}
void parent_main_menu(){
    vaccination vaccine;
    child child;
    string child_id;
    int main_menu_option ;
    cout << "Parent Main Menu" << endl;
    cout << "1. Display vaccination report"<< endl;
    cout << "2. Display medication report"<< endl;
    cout << "3. Edit Profile"<< endl;
    cout << "4. Delete account"<< endl;
    cout << "5. Exit"<< endl;

    switch (main_menu_option)
    {
    case 1:
        cout << "Enter your child record identification";
        cin >> child_id;
        generateReport(child_id, people, vaccines);
        break;
    case 2:
        cout << "Enter your child record identification";
        cin >> child_id;
        generateMedicalReport(child_id, people, consultations);
        break;
    case 3:
        child.updateUser();
        break;
    case 4:
        child.deleteUser();
        break;
    default:
        break;
    }
}

void doctor_main_menu() {
    vaccination vaccine;
    medic medication;
    child child;
    int main_menu_option;
    string child_record_id;
    string name;
    string surname;
    string dob;

    cout << "Doctor Menu" << endl;  // Change to "Doctor Menu" for clarity
    cout << "1. Display vaccination report" << endl;
    cout << "2. Create vaccination report" << endl;
    cout << "3. Display Medical report" << endl;
    cout << "4. Create Medication report" << endl;
    cout << "5. Search medical record by ID" << endl;
    cout << "6. Search vaccination record by ID" << endl;
    cout << "7. Search child record by Name and DOB"<< endl;
    cout << "8. Exit" << endl;

    cout << "Choose : ";
    cin >> main_menu_option;

    switch (main_menu_option) {
    case 1:
        cout << "Enter child record id: ";
        cin >> child_record_id;
        generateReport(child_record_id, people, vaccines);
        break;
    case 2:
        registerVaccine();
        break;
    case 3:
        cout << "Enter child record id: ";
        cin >> child_record_id;
        generateMedicalReport(child_record_id, people, consultations);
        break;
    case 4:
        medication.registerMedication();
        break;
    case 5:
        cout << "Enter child record id: ";
        cin >> child_record_id;
        searchMedicalRecordsByID(child_record_id);
        break;
    case 6:
        cout << "Enter child record id: ";
        cin >> child_record_id;
        searchVaccinationRecordsByID(child_record_id);
        break;
    case 7:
        cout << "Enter name of kid: ";
        cin >> name;
        cout << "Enter surname of kid: ";
        cin >> surname;
        cout << "Enter their Date of Birth: ";
        cin >> dob;
        searchRecordsByNameAndDOB(name,surname,dob);
        break;

    default:
        cout << "Exiting..." << endl;
        break;
    }
}

void searchMedicalRecordsByID(const string& child_record_id) {
    ifstream inFile("medical_table.csv");
    string line;
    bool record_found = false;

    while (getline(inFile, line)) {
        if (line.find(child_record_id) != string::npos) { // Check if record ID exists in the line
            cout << "Medical Record Found: " << line << endl; // Print found record
            record_found = true;
            break;
        }
    }
    inFile.close();

    if (!record_found) {
        cout << "No medical record found for Child Record ID: " << child_record_id << endl;
    }
}

void searchRecordsByNameAndDOB(const string& first_name, const string& surname, const string& date_of_birth) {
    ifstream inFile("medical_records.csv");
    string line;
    bool record_found = false;

    while (getline(inFile, line)) {
        // Assuming the structure of the CSV and that the fields are in the order: Record Number, First Name, Surname, ...
        istringstream iss(line);
        string record_number, child_first_name, child_surname, dob, other_fields;

        getline(iss, record_number, ',');
        getline(iss, child_first_name, ',');
        getline(iss, child_surname, ',');
        getline(iss, dob, ','); // Assuming DOB is at the 3rd position

        if (child_first_name == first_name && child_surname == surname && dob == date_of_birth) {
            cout << "Medical Record Found: " << line << endl; // Print found record
            record_found = true;
        }
    }
    inFile.close();

    if (!record_found) {
        cout << "No medical record found for Child Name: " << first_name << " " << surname << " and Date of Birth: " << date_of_birth << endl;
    }
}

void searchVaccinationRecordsByID(const string& child_record_id) {
    ifstream inFile("vaccination_table.csv");
    string line;
    bool record_found = false;

    while (getline(inFile, line)) {
        if (line.find(child_record_id) != string::npos) { // Check if record ID exists in the line
            cout << "Vaccination Record Found: " << line << endl; // Print found record
            record_found = true;
            break;
        }
    }
    inFile.close();

    if (!record_found) {
        cout << "No vaccination record found for Child Record ID: " << child_record_id << endl;
    }
}

#endif //DOCTOR_H
