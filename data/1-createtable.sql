DROP TABLE IF EXISTS employee;
DROP TABLE IF EXISTS tax;



CREATE TABLE  employee(
ID INTEGER PRIMARY KEY AUTOINCREMENT,
name TEXT NOT NULL ,
gender char(6),
marital_status char(8),
position VARCHAR(40) ,
phone VARCHAR(10) ,
salaryform char(18) NOT NULL,
salaryamount  DECIMAL(11,2),
birth_date DATE,
hire_date DATE
);



CREATE TABLE tax(
employee_id INTEGER PRIMARY KEY AUTOINCREMENT,
emoployer_cost NUMERIC NOT NULL,
social NUMERIC,
medicare NUMERIC,
FOREIGN KEY(employee_id) REFERENCES employee(ID) ON DELETE CASCADE
);







