
#ifndef GENERATEMEDICALREPORT_H
#define GENERATEMEDICALREPORT_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

using namespace std;

// Function to mask data
string maskChildFullName(const string& first_name, const string& middle_name, const string& last_name) {
    string masked_full_name;

    // Mask the first name, keeping its first character
    masked_full_name += first_name[0]; // First character of the first name
    if (first_name.length() > 1) {
        masked_full_name += string(first_name.length() - 1, '*'); // Mask the rest of the first name
    }

    // Add the masked middle name if it exists
    if (!middle_name.empty()) {
        masked_full_name += " " + string(middle_name.length(), '*'); // Fully mask the middle name
    }

    // Mask the last name, keeping its last three characters
    if (last_name.length() > 3) {
        masked_full_name += " " + string(last_name.length() - 3, '*') + last_name.substr(last_name.length() - 3);
    } else {
        masked_full_name += " " + string(last_name.length(), '*'); // Fully mask if last name is too short
    }
    return masked_full_name;
}

// Masking Guardian Names
string maskGuardianName(const string& guardian_name) {
    if (guardian_name.length() <= 1) {
        return guardian_name; // Return the name as is if it is one character
    }
    return guardian_name[0] + string(guardian_name.length() - 1, '*'); // Mask all but the first character
}


string maskTreatment(const string& treatment) {
    return string(treatment.length(), '*');
}

vector<child> readChildFile(const string& filename) {
    vector<child> children;
    ifstream file(filename);
    string line;
    while (getline(file, line)) {
        if (line.substr(0, 5) == "child") { // Check if the line starts with "child"
            istringstream iss(line);
            string temp;
            child c;

            getline(iss, temp, ','); // Skip the "child" tag
            getline(iss, temp, ','); // Skip the number
            getline(iss, c.first_name, ',');
            getline(iss, c.last_name, ',');
            getline(iss, c.middle_name, ',');
            getline(iss, c.date_of_birth, ',');
            getline(iss, c.mother, ',');
            getline(iss, c.father, ',');
            getline(iss, c.village, ',');
            getline(iss, c.chief, ',');
            getline(iss, c.district, ',');
            getline(iss, temp, ','); // Skip the password
            getline(iss, c.child_record_id, ',');
            children.push_back(c);
        }
    }
    return children;
}

// Read medic CSV function (same as original)
vector<medic> readMedicCSV(const string& filename) {
    vector<medic> medics;
    ifstream file(filename);
    string line;
    while (getline(file, line)) {
        istringstream iss(line);
        medic m;
        getline(iss, m.treatment, ',');
        getline(iss, m.medication, ',');
        getline(iss, m.child_record, ',');
        getline(iss, m.weight, ',');
        getline(iss, m.height, ',');
        getline(iss, m.doctor, ',');
        getline(iss, m.clinic, ',');
        getline(iss, m.consultation_date, ',');
        getline(iss, m.checkup_date, ',');
        medics.push_back(m);
    }
    return medics;
}

// Generate medical report
void generateMedicalReport(const string& child_record_id, const vector<child>& childRecords, const vector<medic>& medicRecords) {
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
    report << "Child's Medical Report:\n" << endl;
    report << string(60, '#') << endl;

    // Mask the names and treatment
    report << "Child Fullname: " << maskChildFullName(selected_child.first_name, selected_child.middle_name, selected_child.last_name) << endl;
    report << "Guardian/Parent(s) Name(s): " << maskGuardianName(selected_child.mother) << " and " << maskGuardianName(selected_child.father) << endl;
    report << "Date of Birth: " << selected_child.date_of_birth << endl;
    report << "Village: " << selected_child.village << " | Chief: " << selected_child.chief << " | District: " << selected_child.district << endl;

    // Output the medical consultation details for the child
    report << "\nMedical Consultations:" << endl;
    for (const auto& medic : medicRecords) {
        if (medic.child_record == child_record_id) {
            report << "-> Treatment: " << maskTreatment(medic.treatment)
                   << " | Medication: " << medic.medication
                   << " | Weight: " << medic.weight
                   << " | Height: " << medic.height
                   << " | Date: " << medic.consultation_date
                   << " | By: " << medic.doctor
                   << " | Clinic: " << medic.clinic << endl;
        }
    }

    // Find the next checkup date
    string next_checkup_date = "";
    for (const auto& medic : medicRecords) {
        if (medic.child_record == child_record_id) {
            next_checkup_date = medic.checkup_date;
        }
    }
    report << "\nDate for Next Checkup: " << next_checkup_date << endl;
    report << string(60, '#') << endl;

    // Print report to console
    cout << report.str();

    // Prompt user for confirmation
    cout << "Do you want to print this report to a text file? (yes/no): ";
    string input;
    cin >> input;
    if (input == "yes") {
        ofstream outFile(child_record_id + ".txt");
        outFile << report.str(); // Exporting the full report without masking
        outFile.close();
        cout << child_record_id << ".txt" << endl;
    } else {
        cout << "Report not printed." << endl;
    }
}

vector<child> people = readChildFile("users.csv");
vector<medic> consultations = readMedicCSV("medical_table.csv");

#endif // GENERATEMEDICALREPORT_H