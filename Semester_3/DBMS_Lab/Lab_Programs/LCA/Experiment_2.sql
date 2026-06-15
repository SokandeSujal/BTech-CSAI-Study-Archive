CREATE DATABASE sem2DBMS;
USE sem2DBMS;

CREATE TABLE Suppliers(
	SupplierID INT AUTO_INCREMENT PRIMARY KEY,
    Name VARCHAR(100) NOT NULL,
    Status ENUM('Active', 'Inactive', 'Pending') DEFAULT 'Active',
    City VARCHAR(100) NOT NULL
);

CREATE TABLE Parts(
	PartsID INT AUTO_INCREMENT PRIMARY KEY,
    Pname VARCHAR(100) NOT NULL,
	Colour ENUM('Red', 'White', 'Yellow'),
    Weight DECIMAL(8,2) NOT NULL CHECK (Weight > 0),
    City VARCHAR(100) NOT NULL
);

INSERT INTO Parts (Pname, Colour, Weight, City) VALUES
("Motor", "White", "30", "Kalyan"),
("Engine", "Yellow", "50", "Mumbai");

CREATE TABLE Projects(
	ProjectID INT AUTO_INCREMENT PRIMARY KEY,
    Jname VARCHAR(100) NOT NULL UNIQUE,
    City VARCHAR(100) NOT NULL
);

INSERT INTO Projects (Jname, City) VALUES
("Car", "Pune"),
("Space Rocket", "Delhi");

CREATE TABLE Shipment(
	SupplierID INT NOT NULL,
    PartsID INT NOT NULL,
    ProjectID INT NOT NULL,
    Qty FLOAT NOT NULL,
    PRIMARY KEY(SupplierID, PartsID, ProjectID),
    CONSTRAINT fk_supplier FOREIGN KEY(SupplierID) REFERENCES Suppliers(SupplierID) ON DELETE CASCADE ON UPDATE CASCADE,
    CONSTRAINT fk_part FOREIGN KEY(PartsID) REFERENCES Parts(PartsID) ON DELETE CASCADE ON UPDATE CASCADE,
    CONSTRAINT fk_project FOREIGN KEY(ProjectID) REFERENCES Projects(ProjectID) ON DELETE CASCADE ON UPDATE CASCADE
);

INSERT INTO Shipment VALUES
(3, 1, 2, 40);

INSERT INTO Suppliers (SupplierID, Name, Status, City) VALUES
(1, "Sujal Sokande", "Active", "Pune"),
(2, "Aayush Sokande", "Active", "Murbad"),
(3, "Sarthak Kakad", "Inactive", "Nashik");

SELECT * FROM Shipment;



CREATE TABLE employee(
	empName VARCHAR(100) PRIMARY KEY,
    empAddress VARCHAR(100) NOT NULL,
    city VARCHAR(100) NOT NULL
);

CREATE TABLE company (
	companyName VARCHAR(100) PRIMARY KEY,
    city VARCHAR(100) NOT NULL
);

CREATE TABLE works(
	empName VARCHAR(100),
    companyName VARCHAR(100),
    salary INT NOT NULL CHECK (salary > 0),
    PRIMARY KEY (empName, companyName),
	CONSTRAINT fk_empName FOREIGN KEY(empName) REFERENCES employee(empName),
    CONSTRAINT fk_companyName FOREIGN KEY(companyName) REFERENCES company(companyName)
);

CREATE TABLE manages (
    empName VARCHAR(100) PRIMARY KEY,
    managerName VARCHAR(100),
    CONSTRAINT fk_emp FOREIGN KEY (empName) REFERENCES employee(empName) ON DELETE CASCADE ON UPDATE CASCADE,
    CONSTRAINT fk_mgr FOREIGN KEY (managerName) REFERENCES employee(empName) ON DELETE SET NULL ON UPDATE CASCADE
);

SELECT USER FROM mysql.user;

CREATE USER sampleuser@localhost IDENTIFIED BY '729654';

GRANT ALL PRIVILEGES ON sem2DBMS.* TO sampleuser@localhost;

REVOKE ALL PRIVILEGES ON *.* FROM sampleuser@localhost;

SHOW GRANTS FOR sampleuser@localhost;