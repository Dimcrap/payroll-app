DROP IF EXIST employee;
DROP IF EXIST tax;



CREATE TABLE  employee(
ID INTEGER PRIMARY KEY AUTOINCREMENT,
name TEXT NOT NULL ,
gender char(6),
marital-status char(8),
position VARCHAR(100) ,
phone VARCHAR(10) ,
salaryform char(18) NOT NULL,
salaryamount  DECIMAL(11,2),
hire_date DATE
);



CREATE TABLE tax(
employee_id INTEGER PRIMARY KEY,
emoployer_cost NUMERIC NOT NULL,
social NUMERIC,
medicare NUMERIC,
FOREIGN KEY(employee_id) REFERENCES employee(ID)
);







