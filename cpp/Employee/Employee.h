//
// Created by yaning on 17-6-20.
//

#ifndef EMPLOYEE_EMPLOYEE_H
#define EMPLOYEE_EMPLOYEE_H

#endif //EMPLOYEE_EMPLOYEE_H
#pragma once

#include <string>

namespace Records {
    const int kDefaultStartingSalary = 30000;

    class Employee {
    public:
        Employee();

        void promote(int raiseAmount = 1000);

        void demote(int demeritAmount = 1000);

        void hire();

        void fire();

        void display() const;

        const std::string &getMFirstName() const;

        void setMFirstName(const std::string &mFirstName);

        const std::string &getMLastName() const;

        void setMLastName(const std::string &mLastName);

        int getMEmployeeNumber() const;

        void setMEmployeeNumber(int mEmployeeNumber);

        int getMSalary() const;

        void setMSalary(int mSalary);

        bool getIsHired() const;

    private:
        std::string mFirstName;
        std::string mLastName;
        int mEmployeeNumber;
        int mSalary;
        bool mHired;
    };

}
