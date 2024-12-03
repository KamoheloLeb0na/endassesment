//
// Created by lebona on 2024/10/25.
//
#include <iostream>

using namespace std;


// Function to mask child full names
string maskFullName(const string& first_name, const string& middle_name, const string& last_name) {
    string masked_full_name;

    // Mask first name
    masked_full_name += first_name[0]; // Keep the first letter of the first name
    if (first_name.length() > 1) {
        masked_full_name += string(first_name.length() - 1, '*'); // Mask the rest of the first name
    }

    // Mask middle name fully
    if (!middle_name.empty()) {
        masked_full_name += " " + string(middle_name.length(), '*'); // Fully mask the middle name
    }

    // Mask last name, keep the last three characters
    if (last_name.length() > 3) {
        masked_full_name += " " + string(last_name.length() - 3, '*') + last_name.substr(last_name.length() - 3);
    } else {
        masked_full_name += " " + string(last_name.length(), '*'); // Fully mask if the last name is too short
    }

    return masked_full_name;
}

// Function to mask guardian names
string maskParentName(const string& guardian_name) {
    if (guardian_name.empty()) return ""; // No name to mask
    return guardian_name[0] + string(guardian_name.length() - 1, '*'); // Mask all but the first character
}

// Function to mask Date of Birth
string maskDOB(const string& date_of_birth) {
    return "**/**/20**"; // Fixed masking format
}

// Function to mask vaccination information
string maskVacc(const string& vaccination) {
    return string(vaccination.length(), '*'); // Mask entire vaccine/treatment name
}

vector<child> readChildCSV(const string& filename) {
    vector<child> children;
    ifstream file(filename);
    string line;
    while (getline(file, line)) {
        if (line.substr(0, 5) == "child") {
            istringstream iss(line);
            string temp;
            child c;
            getline(iss, temp, ','); // Skip the "child" tag
            getline(iss, temp, ','); // Skip the number
            getline(iss, c.first_name, ',');
            getline(iss, c.last_name, ',');
            getline(iss, c.middle_name, ',');
            getline(iss, c.date_of_birth, ','); // Date of Birth
            getline(iss, c.mother, ',');
            getline(iss, c.father, ',');
            getline(iss, c.village, ',');
            getline(iss, c.chief, ',');
            getline(iss, c.district, ',');
            getline(iss, temp, ','); // Skip the password
            getline(iss, c.child_record_id, ','); // Record ID
            children.push_back(c);
        }
    }
    return children;
}

vector<vaccination> readVaccineCSV(const string& filename) {
    vector<vaccination> vaccines;
    ifstream file(filename);
    string line;
    while (getline(file, line)) {
        istringstream iss(line);
        vaccination v;
        getline(iss, v.treatment, ','); // Treatment name
        getline(iss, v.vaccine, ',');   // Vaccine name
        getline(iss, v.child_record_id, ',');
        getline(iss, v.weight, ',');
        getline(iss, v.height, ',');
        getline(iss, v.nurse, ',');
        getline(iss, v.clinic, ',');
        getline(iss, v.clinic_date, ',');
        getline(iss, v.next_clinic_date, ',');
        vaccines.push_back(v);
    }
    return vaccines;
}

void generateReport(const string& child_record_id, const vector<child>& childRecords, const vector<vaccination>& vaccineRecords) {
    // Find the child record by child_record_id
    child selected_child;
    bool found = false;
    for (const auto& record : childRecords) {
        if (record.child_record_id == child_record_id) {
            selected_child = record;
            found = true;
            break;
        }
    }
    if (!found) {
        cout << "Child record not found!" << endl;
        return;
    }

    // Create report string
    ostringstream report;
    report << string(60, '#') << endl;
    report << "Child's Vaccination Report:\n" << endl;
    report << string(60, '#') << endl;
    report << "Child Fullname: " << maskFullName(selected_child.first_name, selected_child.middle_name, selected_child.last_name) << endl;
    report << "Guardian/Parent(s) Name(s): "
           << maskParentName(selected_child.mother) << " and "
           << maskParentName(selected_child.father) << endl;
    report << "Date of Birth: " << maskDOB(selected_child.date_of_birth) << endl;
    report << "Village: " << selected_child.village << " | Chief: " << selected_child.chief << " | District: " << selected_child.district << endl;

    // Output the vaccination details for the child
    report << "\nVaccinations Administered:" << endl;
    for (const auto& vaccine : vaccineRecords) {
        if (vaccine.child_record_id == child_record_id) {
            report << "-> Vaccine: " << maskVacc(vaccine.vaccine)
                   << " | Weight: " << vaccine.weight
                   << " | Height: " << vaccine.height
                   << " | Date: " << vaccine.clinic_date
                   << " | By: " << vaccine.nurse
                   << " | Clinic: " << vaccine.clinic << endl;
        }
    }

    // Find the next clinic date
    string next_clinic_date = "";
    for (const auto& vaccine : vaccineRecords) {
        if (vaccine.child_record_id == child_record_id) {
            next_clinic_date = vaccine.next_clinic_date;
        }
    }
    report << "\nDate for Next Vaccine: " << next_clinic_date << endl;
    report << string(60, '#') << endl;

    // Print report to console
    cout << report.str();

    // Prompt user for confirmation
    cout << "Do you want to print this report to a text file? (yes/no): ";
    string input;
    cin >> input;
    if (input == "yes") {
        ofstream outFile(child_record_id + ".txt");
        outFile << report.str();
        outFile.close();
        cout << child_record_id << ".txt" << endl;
    } else {
        cout << "Report not printed." << endl;
    }
}
vector<child> children = readChildCSV("users.csv");
vector<vaccination> vaccines = readVaccineCSV("vaccination_table.csv");
