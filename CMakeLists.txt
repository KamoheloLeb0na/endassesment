cmake_minimum_required(VERSION 3.29)
project(EndAssesment)

set(CMAKE_CXX_STANDARD 20)

add_executable(EndAssesment main.cpp
        generateReport.h
        projectclasses.h
        generateMedicalRecord.h
        child.h
        nurse.h
        doctor.h
        register.h
)
