#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
using namespace std;
#include "projectclasses.h"
#include "generateReport.h"
#include "generateMedicalRecord.h"

void searchMedicalRecordsByID(const string& child_record_id);
void searchVaccinationRecordsByID(const string& child_record_id);
void searchRecordsByNameAndDOB(const string& first_name, const string& surname, const string& date_of_birth);
//Menus of characters

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

    switch (option) {
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

//registration of characters
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
            registerMedication();
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

//registration of vaccine and meds
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


// Signup function with role selection
void signup() {
    int roleChoice;
    cout << "##############################################################" << endl;
    cout << "\nSign up as: ";
    cout << "##############################################################" << endl;
    cout << "1. Nurse \n";
    cout << "2. Doctor \n";
    cout << "3. Child \n";
    cout << "##############################################################" << endl;
    cout << "\nEnter your role choice: ";
    cin >> roleChoice;

    if (roleChoice == 1) {
        registerNurse();
    } else if (roleChoice == 2) {
        registerDoctor();
    } else if (roleChoice == 3) {
        registerChildRecord();
    } else {
        cout << "Invalid role choice.\n";
    }
}

// login of characters
void parent_login() {
    string input_username, input_password;

    cout << "Enter Username: ";
    cin >> input_username; // Assuming the username is the first name or record number (you may adjust this as needed)
    cout << "Enter Password: ";
    cin >> input_password;

    // Open the CSV file to check for the user
    ifstream inFile("users_table.csv");
    string line;
    bool login_success = false;

    while (getline(inFile, line)) {
        istringstream iss(line);
        string role,record_number, first_name, surname, middle_name, date_of_birth, mother, father, village, chief, district, password, child_record_id;
        getline(iss, role, ',');
        getline(iss, record_number, ','); // 1st field (assuming this is the record number or username)
        getline(iss, first_name, ',');
        getline(iss, surname, ',');
        getline(iss, middle_name, ',');
        getline(iss, date_of_birth, ',');
        getline(iss, mother, ',');
        getline(iss, father, ',');
        getline(iss, village, ',');
        getline(iss, chief, ',');
        getline(iss, district, ',');
        getline(iss, password, ','); // 11th field (password)
        getline(iss, child_record_id, ','); // Last field (child record id)

        // Check if the input username and password match
        if ((first_name == input_username || record_number == input_username) && password == input_password) {
            login_success = true; // Successful login
            break; // Exit the loop
        }
    }
    inFile.close(); // Close the input file

    // Check the login result
    if (login_success) {
        cout << "Login successful! Welcome, " << input_username << "!\n";

    } else {
        cout << "Login failed! Invalid username or password. Please try again.\n";
    }
}

bool login() {
    const int NURSE_ROLE = 1;
    const int DOCTOR_ROLE = 2;

    int roleChoice;
    cout << endl;
    cout << "##############################################################" << endl;
    cout << "#                     Login as                               #" << endl;
    cout << "##############################################################" ;
    cout << "\n1. Nurse\n2. Doctor\n3. Child\n ";
    cout << "##############################################################" << endl;
    cout << "Enter your role choice: ";
    cin >> roleChoice;

    string password;
    bool loginSuccess = false;

    ifstream inFile("users.csv");
    string line, role, filePassword;

    if (!inFile.is_open()) {
        cout << "Unable to open file for reading.\n";
        return false; // Early return on file open error
    }

    if (roleChoice == NURSE_ROLE || roleChoice == DOCTOR_ROLE) {
        string practice_number;
        cout << "Enter Practice Number: ";
        cin >> practice_number;
        cout << "Enter Password: ";
        cin >> password;

        while (getline(inFile, line)) {
            stringstream ss(line);
            getline(ss, role, ',');  // Read role (nurse/doctor)

            // Skip fields until we reach password
            string field;
            for (int i = 0; i < 5; i++) getline(ss, field, ','); // Skip first five fields

            getline(ss, filePassword, ',');  // Password (assuming it's saved as the last field)

            // Check for nurse match
            if (roleChoice == NURSE_ROLE && role == "nurse" && password == filePassword) {
                loginSuccess = true;
                cout << "Login successful! Welcome Nurse " << endl; // Assuming field holds the name
                nurseMenu();
                // Display nurse menu options here
                break; // Exit the loop since login is successful
            }

            // Check for doctor match
            if (roleChoice == DOCTOR_ROLE && role == "doctor" && password == filePassword) {
                loginSuccess = true;
                cout << "Login successful! Welcome Doctor "<< endl; // Assuming field holds the name
                doctor_main_menu();
                // Display doctor menu options here
                break; // Exit the loop since login is successful
            }
        }
    }else {
        cout << "Invalid role choice.\n";
    }

    if (!loginSuccess) {
        cout << "Login failed. Please check your credentials.\n";
    }

    return loginSuccess;
}


int main() {

    int choice;
    cout << "############################################################" << endl;
    cout << "#                     Main Menu                            #"<<endl;
    cout << "############################################################" << endl;
    cout << "1. Signup                                                  #" << endl;
    cout << "2. Login                                                   #" << endl;
    cout << "############################################################" << endl;
    cout << endl;
    cout << "Enter your choice: ";
    cin >> choice;

    if (choice == 1) {
        signup();
    } else if (choice == 2) {
        login();
    } else {
        cout << "Invalid choice.\n";
    }
    // string child_record_id = "Kam-Leb-30082005-1"; // Replace with actual child record ID to search for
    // generateReport(child_record_id, children, vaccines);
    // generateMedicalReport(child_record_id, children, consultations);
    return 0;
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
