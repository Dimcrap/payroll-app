#include "userdata.h"

salary_type intTosalarytype(int value){
    switch (value) {
    case 1:
        return  salary_type::monthly;
        break;
    case 2:
        return salary_type::weekly;
        break;
    case 3:
        return salary_type::project;
    default:
        qWarning() << "Invalid value:" << value;
        return salary_type::monthly;
        break;
    }

}
int salarytypeToint(salary_type Stype){
    switch (Stype) {
    case salary_type::monthly:
        return 1;
        break;
    case salary_type::weekly:
        return 2;
        break;
    case salary_type::project:
        return 3;
        break;
    default:
        qWarning() << "Invalid value:" <<salarytypeTostring(Stype);
        return 1;
        break;
    }
}

QString salarytypeTostring(salary_type Stype){
    switch (Stype) {
    case salary_type::monthly:
        return "Monthly";
        break;
    case salary_type::weekly:
        return "Weekly";
        break;
    case salary_type::project:
        return "Project";
        break;
    default:
        qWarning() << "Invalid value input";
        return "Monthly";
        break;
    }
}

position intToEmpPosition(int value){
    switch (value) {
    case 1:
        return position::temprory;
        break;
    case 2:
        return position::mid;
        break;
    case 3:
        return position::senior;
        break;
    case 4:
        return position::leadership;
        break;
    case 5:
        return position::executive;
        break;
    case 10:
        return position::supportSpecialist;
        break;
    default:
        qWarning()<<"Invalid value input:"<<QString::number(value);
        return position::temprory;
        break;
    }
}
int postiontoInt(position pos){
    switch (pos) {
    case position::entry:
        return 1;
        break;
    case position::mid:
        return 2;
        break;
    case position::senior:
        return 3;
        break;
    case position::leadership:
        return 4;
        break;
    case position::executive:
        return 5;
        break;
    default:
        qWarning()<<"Invalid postion input:"<<postionTostring(pos)  ;
        return 1;
        break;
    }
}
QString postionTostring(position pos){
    switch (pos) {
    case position::entry:
        return "Entry";
        break;
    case position::mid:
        return "Mid";
        break;
    case position::senior:
        return "Senior";
        break;
    case position::leadership:
        return "Leadership";
        break;
    case position::executive:
        return "Executive";
        break;
    case position::supportSpecialist:
        return "SupportSpecialist";
        break;
    default:
        qWarning()<<"invalid position enterd";
        return "Entry";
        break;
    }
}


