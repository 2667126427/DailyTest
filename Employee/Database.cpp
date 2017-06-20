//
// Created by yaning on 17-6-20.
//

#include <iostream>
#include <stdexcept>
#include "Database.h"

using namespace std;

namespace Records{
    Database::Database() :mNextEmployeeNumber(kFirstEmployeeNumber) {}

    Employee& Database::addEmployee(const std::string &firstName, const std::string &lastName) {
        Employee theEmployee;
        theEmployee.setMFirstName(firstName);
        theEmployee.setMLastName(lastName);
        theEmployee.setMEmployeeNumber(mNextEmployeeNumber++);
        theEmployee.hire();
        mEmployees.push_back(theEmployee);
        return mEmployees[mEmployees.size() - 1];
    }

    Employee& Database::getEmployee(int employeeNumber) {
        for (auto&employee:mEmployees) {
            if (employee.getMEmployeeNumber() == employeeNumber){
                return employee;
            }
        }
        throw runtime_error("No employee found.");
    }

    Employee& Database::getEmployee(const std::string &firstName, const std::string &lastName){
        for(auto & employee:mEmployees){
            if(employee.getMLastName() == lastName && employee.getMFirstName() == firstName){
                return employee;
            }
        }
        throw runtime_error("No employee found.");
    }

    void Database::displayCurrent() const {
        for(const auto&employee:mEmployees){
            if (employee.getIsHired()){
                employee.display();
            }
        }
    }

    void Database::displayFormer() const {
        for(const auto&employee:mEmployees){
            if (!employee.getIsHired()){
                employee.display();
            }
        }
    }

    void Database::displayAll() const {
        for (const auto&employee:mEmployees) {
            employee.display();
        }
    }
}