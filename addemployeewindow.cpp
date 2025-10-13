#include "addemployeewindow.h"
#include "ui_addemployeewindow.h"
#include <QDate>
#include <QDateEdit>
#include <QDoubleSpinBox>
#include <QRadioButton>
#include <QDebug>
#include <QGroupBox>


addemployeewindow::addemployeewindow(QWidget *parent)

    : QMainWindow(parent)
    , ui(new Ui::addemployeewindow)

{
    ui->setupUi(this);
    setWindowTitle("Add New Employee");
    setMinimumSize(700,380);
    setWindowFlag(Qt::Window);

    ui->fram1->setMinimumWidth(160);
    ui->phoneNumber->setValidator(new QIntValidator(this));
    ui->Salaryamount->setValidator(new QIntValidator(this));
    ui->genderGroupBox->setStyleSheet("max-height:30px;");
    ui->maritalGroupBox->setStyleSheet("max-height:30px;");
    ui->positonGroupBox->setStyleSheet("max-height:80px;padding-bottom:1px");
    ui->radioButton_7->setStyleSheet("margin-left:15px");
    ui->radioButton_10->setStyleSheet("margin-left:20px");
    ui->salarytypeGroupBox->setStyleSheet("padding:1px;max-height:35px");
    ui->label_13->setMaximumWidth(20);

    connect(ui->backToMain,&QPushButton::clicked,
    this,&addemployeewindow::onBackButtonClicked);
    connect(ui->Erase,&QPushButton::clicked,this,
            &addemployeewindow::onEraseButtonClicked);
    connect(ui->addbtn,&QPushButton::clicked,this,
    &addemployeewindow::onAddButtonClicked);

    genders={ui->maleB, ui->femaleB };
    maritalsradios={
        ui->marriedB,
        ui->unmarriedB
    };

    salaryTypes={
        ui->weeklyB,ui->monthlyB,ui->projectB
    };

    positions={
        ui->radioButton_5,ui->radioButton_6,
        ui->radioButton_7,ui->radioButton_8,
        ui->radioButton_9,ui->radioButton_10,
        ui->radioButton_11
    };
}

void addemployeewindow::setDataBaseHandler(std::shared_ptr<DatabaseHandler> handler){
    m_dbhandler=handler;
}


void addemployeewindow::showEvent(QShowEvent *event){
    QMainWindow::showEvent(event);

    if(m_dbhandler&&!m_dbhandler->isOpen()){
    if(!m_dbhandler->openDatabase()){
            qDebug()<<"Failed to open database in showEvent";

    };
}
}

void addemployeewindow::onBackButtonClicked(){
    cleanInputs();
    emit backToMain();
}

void addemployeewindow::cleanInputs(){
    QList<QLineEdit *> LineEdits=findChildren<QLineEdit*>();
    for (QLineEdit *lineEdit:LineEdits){
        lineEdit->clear();
    };

    QList<QDateEdit *> dateEdits=findChildren<QDateEdit*>();
    for(QDateEdit *dateEdit:dateEdits){
        dateEdit->setDate(QDate::currentDate());
    };

    QList<QDoubleSpinBox*>doublespinboxes=findChildren<QDoubleSpinBox*>();
    for (QDoubleSpinBox *doublespinbox:doublespinboxes){
        doublespinbox->setValue(0.0);
    }

    QList<QGroupBox*> groupboxes={
                                     ui->genderGroupBox,
        ui->maritalGroupBox,
        ui->positonGroupBox,
        ui->salarytypeGroupBox
    };


    QList<QRadioButton*>radiobuttons=ui->genderGroupBox->findChildren<QRadioButton *>();
    radiobuttons.append(ui->maritalGroupBox ->findChildren<QRadioButton *>() );
    radiobuttons.append(ui->positonGroupBox->findChildren<QRadioButton *>() );
    radiobuttons.append(ui->salarytypeGroupBox->findChildren<QRadioButton *>());

    for (QRadioButton *radiobutton:radiobuttons){
        radiobutton->setAutoExclusive(false);
    }
        for (QRadioButton *radiobutton:radiobuttons){
        radiobutton->setAutoExclusive(false);
        radiobutton->setChecked(false);
    }

        for (QRadioButton *radiobutton:radiobuttons){
            radiobutton->setAutoExclusive(false);
        };
}

void addemployeewindow::onEraseButtonClicked()
{
 cleanInputs();
}



void addemployeewindow::onAddButtonClicked(){

    qDebug() << "m_dbhandler exists?" << (m_dbhandler != nullptr);
    if (m_dbhandler) {
        qDebug() << "Database open?" << m_dbhandler->isOpen();
    }

    if(Userinputs().name.isEmpty()){
        qCritical()<<"Unable to add employee";
        return;
    }

    int EmployeeId=m_dbhandler->adduserdata(Userinputs());
     if(EmployeeId==-1){
        qCritical()<<"error inserting primary datas";
         return;
    };

    double employerCost=ui->employerSpinbox->value();
    double SocialSec=ui->doubleSpinBox_3->value();
    double Medicare=ui->doubleSpinBox->value();
    taxdetails taxinput(EmployeeId,employerCost,SocialSec,Medicare);
    if(!m_dbhandler->addusertaxes(taxinput)){
        return;
    }else{
        qInfo("Employee added");
    };

}


addemployeewindow::~addemployeewindow()
{
    delete ui;
}

auto genderRadio=[](QList<QRadioButton*>buttonslist){
    for (QRadioButton *radio:buttonslist){
        if(radio->isChecked()){
            return radio->text();
        }
    }

    return QString();
};
auto maritalRadio=[](QList<QRadioButton *>buttonslist){
    for (QRadioButton *radio:buttonslist){
        if(radio->isChecked()){
            return radio->text();
        }
    }
    return QString();
};

auto posRadio=[](QList<QRadioButton*>buttonslist){
    for (QRadioButton *radio:buttonslist){
        if(radio->isChecked()){
            int posvalue;
                (radio->objectName()=="radioButton_5")?posvalue=0:
                (radio->objectName()=="radioButton_6")?posvalue=1:
                (radio->objectName()=="radioButton_7")?posvalue=2:
                (radio->objectName()=="radioButton_8")?posvalue=3:
                (radio->objectName()=="radioButton_9")?posvalue=4:
                (radio->objectName()=="radioButton_10")?posvalue=5:
                posvalue=10;
            return  intToEmpPosition(posvalue);
        }
    }
    return  intToEmpPosition(0);

};

auto salaryRadio=[](QList<QRadioButton*>buttonslist){
    for (QRadioButton *radio:buttonslist){
        if(radio->isChecked()){
            int intsalary;
            (radio->objectName()=="weeklyB")?intsalary=1:
            (radio->objectName()=="monthlyB")?intsalary=2:
                                  intsalary=3;
            return intTosalarytype(intsalary);

        }
    }
    return intTosalarytype(1);
};


Userdata addemployeewindow::Userinputs(){
    QString nameLine=ui->name->text();QString gender=genderRadio(genders);
    QString marital= maritalRadio(maritalsradios);
    QDate birth_date=ui->birthdate->date();
    position inputeduser=posRadio(positions);QString phoneNum;
    salary_type salartType=salaryRadio(salaryTypes);int salaryAmount;
    QDate HireDate=ui->Hiredate->date();
    phoneNum= ui->phoneNumber->text();

    QString salaryText=ui->Salaryamount->text();
    bool S_flag;
    salaryAmount=salaryText.toInt(&S_flag);

    if(nameLine.isEmpty()||gender.isEmpty(),marital.isEmpty()||phoneNum.isEmpty()){
        inputError("Empty slot detected.");
        return Userdata();
    };


    if(!S_flag||salaryText.isEmpty()){
        inputError("Erroe storing salary amount");
        return Userdata();
    };

    Userdata Usersinputs(nameLine,gender,marital,birth_date,
     inputeduser,phoneNum,salartType,salaryAmount,HireDate);

    return Usersinputs;

}


void addemployeewindow::inputError(QString errormsg){
    qCritical()<<"Unable to add employe"+errormsg;
}








