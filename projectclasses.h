//
// Created by lebona on 2024/10/25.
//

#include <iostream>
#include <string>
using namespace std;

class child {
public:
    string first_name;
    string last_name;
    string middle_name;
    string date_of_birth;
    string mother;
    string father;
    string village;
    string chief;
    string district;
    string password;
    string child_record_id;
};

struct vaccination{
    string treatment;
    string vaccine;
    string child_record_id;
    string weight;
    string height;
    string nurse;
    string clinic;
    string clinic_date;
    string next_clinic_date;
} ;

struct medic{
    string treatment;
    string medication;
    string child_record;
    string weight;
    string height;
    string doctor;
    string clinic;
    string consultation_date;
    string checkup_date;
} ;

class doctor {
public:
    string first_name;
    string last_name;
    int practice_number;
    string hospital;
    int cellphone;
    string password;
};

class nurse {
public:
    string title;
    string first_name;
    string last_name;
    int practice_number;
    string hospital;
    string hospital_address;
    string cellphone;
    string password;
};

