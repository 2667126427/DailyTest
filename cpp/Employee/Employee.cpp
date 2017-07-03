//
// Created by yaning on 17-6-20.
//
#include <iostream>
#include "Employee.h"

using namespace std;

namespace Records {
    Employee::Employee()
            : mFirstName(""), mLastName(""), mEmployeeNumber(-1), mSalary(kDefaultStartingSalary), mHired(false) {}

    void Employee::promote(int raiseAmount) {
        setMSalary(getMSalary() + raiseAmount);
    }

    void Employee::demote(int demeritAmount) {
        setMSalary(getMSalary() - demeritAmount);
    }

    void Employee::hire() {
        mHired = true;
    }

    void Employee::fire() {
        mHired = false;
    }

    void Employee::display() const {
        cout << "Employee: " << getMLastName() << ", " << getMFirstName() << endl;
        cout << "--------------------------" << endl;
        cout << (mHired ? "Current Employee" : "Former Employee") << endl;
        cout << "Employee Number: " << getMEmployeeNumber() << endl;
        cout << "Salary: $" << getMSalary() << endl;
        cout << endl;
    }

    const std::string &Employee::getMFirstName() const {
        return mFirstName;
    }

    void Employee::setMFirstName(const std::string &mFirstName) {
        this->mFirstName = mFirstName;
    }

    void Employee::setMLastName(const std::string &mLastName) {
        this->mLastName = mLastName;
    }

    const std::string &Employee::getMLastName() const {
        return mLastName;
    }

    void Employee::setMEmployeeNumber(int mEmployeeNumber) {
        this->mEmployeeNumber = mEmployeeNumber;
    }

    int Employee::getMEmployeeNumber() const {
        return mEmployeeNumber;
    }

    void Employee::setMSalary(int mSalary) {
        this->mSalary = mSalary;
    }

    int Employee::getMSalary() const {
        return mSalary;
    }

    bool Employee::getIsHired() const {
        return mHired;
    }
}
