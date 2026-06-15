use sem2dbms;

DROP TABLE IF EXISTS Employee;

CREATE TABLE Employee (
    emp_no INT PRIMARY KEY,
    name VARCHAR(50),
    skill VARCHAR(50),
    pay_rate DECIMAL(10,2)
);

CREATE TABLE JobPosition (
    posting_no INT PRIMARY KEY,
    skill VARCHAR(50)
);

CREATE TABLE Duty_allocation (
    posting_no INT,
    emp_no INT,
    day DATE,
    shift VARCHAR(20),
    PRIMARY KEY (posting_no, emp_no, day, shift),
    FOREIGN KEY (posting_no) REFERENCES JobPosition(posting_no),
    FOREIGN KEY (emp_no) REFERENCES Employee(emp_no)
);


INSERT INTO Employee (emp_no, name, skill, pay_rate)
VALUES
(1001, 'Alice Johnson', 'Electrician', 30.00),
(1002, 'Bob Smith', 'Plumber', 28.50),
(1003, 'Charlie Lee', 'Carpenter', 26.75),
(1004, 'Diana Patel', 'Electrician', 32.00),
(1005, 'Evan Chen', 'Painter', 25.00);

INSERT INTO JobPosition (posting_no, skill)
VALUES
(2001, 'Electrician'),
(2002, 'Plumber'),
(2003, 'Carpenter'),
(2004, 'Painter');

INSERT INTO Duty_allocation (posting_no, emp_no, day, shift)
VALUES
(2001, 1001, '2025-11-13', 'Morning'),
(2001, 1004, '2025-11-13', 'Evening'),
(2002, 1002, '2025-11-13', 'Morning'),
(2003, 1003, '2025-11-13', 'Day'),
(2004, 1005, '2025-11-13', 'Night');

-- ==============================
-- ADDITIONAL SAMPLE DATA
-- ==============================

-- More Employees
INSERT INTO Employee (emp_no, name, skill, pay_rate)
VALUES
(1006, 'Fatima Ali', 'Electrician', 31.00),
(1007, 'George Brown', 'Plumber', 27.50),
(1008, 'Hannah Davis', 'Carpenter', 26.00),
(1009, 'Ian Wright', 'Painter', 24.50),
(1010, 'Julia Kim', 'Welder', 33.00),
(1011, 'Kevin Scott', 'Mason', 29.00),
(1012, 'Laura Green', 'Welder', 34.00),
(1013, 'Michael Torres', 'Electrician', 30.50),
(1014, 'Nina Lopez', 'Plumber', 28.25),
(1015, 'Oscar Reed', 'Carpenter', 27.00);

-- More Positions (some with no employees yet)
INSERT INTO JobPosition (posting_no, skill)
VALUES
(2005, 'Welder'),
(2006, 'Mason'),
(2007, 'Electrician'),
(2008, 'Carpenter'),
(2009, 'Painter'),
(2010, 'Plumber');

-- Duty allocations (spread across multiple days to help test filtering)
INSERT INTO Duty_allocation (posting_no, emp_no, day, shift)
VALUES
-- 2025-11-14 (new day to test filtering)
(2002, 1007, '2025-11-14', 'Evening'),
(2003, 1008, '2025-11-14', 'Day'),
(2004, 1009, '2025-11-14', 'Morning'),
(2005, 1012, '2025-11-14', 'Day'),
(2006, 1011, '2025-11-14', 'Night'),
(2007, 1013, '2025-11-14', 'Morning'),
(2009, 1009, '2025-11-14', 'Evening'),
(2010, 1014, '2025-11-14', 'Day'),

-- 2025-11-15 (to add variety)
(2001, 1001, '2025-11-15', 'Morning'),
(2005, 1010, '2025-11-15', 'Night'),
(2008, 1015, '2025-11-15', 'Day'),
(2003, 1003, '2025-11-15', 'Evening'),
(2009, 1009, '2025-11-15', 'Morning');



-- Q1
SELECT
	e.name AS Employee_Name,
    da.posting_no,
    da.shift
FROM Employee e
JOIN Duty_allocation da ON e.emp_no = da.emp_no WHERE da.day = '2025-11-13';

-- Q2
SELECT
	e.name AS EmployeeName,
    da.posting_no,
    da.day,
    da.shift
FROM Employee e
LEFT JOIN Duty_allocation da ON e.emp_no = da.emp_no WHERE da.day = '2025-11-14';

-- Q3
SELECT
	p.posting_no,
    e.name AS employee_name,
    da.shift
FROM JobPosition p
LEFT JOIN Duty_allocation da ON p.posting_no = da.posting_no AND da.day = '2025-11-14'
LEFT JOIN Employee e ON da.emp_no = e.emp_no;

SHOW TABLES;

-- Q4
SELECT
	e.name As EmployeeName,
    p.posting_no,
    da.shift
FROM Employee e
LEFT JOIN Duty_allocation da ON e.emp_no = da.emp_no AND da.day = '2025-11-14'
LEFT JOIN JobPosition p ON da.posting_no = p.posting_no

UNION

SELECT
	e.name AS employee_name,
	p.posting_no,
    da.shift
FROM JobPosition p
LEFT JOIN Duty_allocation da ON da.posting_no = p.posting_no AND da.day = '2025-11-14'
LEFT JOIN Employee e ON da.emp_no = e.emp_no;
    
SELECT 
    e1.name AS employee_1,
    e2.name AS employee_2,
    e1.skill
FROM Employee e1
JOIN Employee e2 
    ON e1.skill = e2.skill 
   AND e1.emp_no < e2.emp_no
ORDER BY e1.skill;

