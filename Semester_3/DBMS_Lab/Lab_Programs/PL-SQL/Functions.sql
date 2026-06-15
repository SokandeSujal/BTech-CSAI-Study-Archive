CREATE DATABASE IF NOT EXISTS endSem3;
USE endSem3;

SET GLOBAL log_bin_trust_function_creators = 1;

DELIMITER $$

CREATE FUNCTION randomNumber()
RETURNS INT
NOT DETERMINISTIC
BEGIN
	RETURN ROUND(RAND() * 10000, 0);
END $$

DELIMITER ;

SELECT randomNumber();


CREATE TABLE instructor (
    ID INT PRIMARY KEY,
    name VARCHAR(30),
    dept_name VARCHAR(20),
    salary INT
);

INSERT INTO instructor (ID, name, dept_name, salary) VALUES
(10101, 'Srinivasan', 'CompSci', 65000),
(12121, 'Wu',         'Finance', 90000),
(15151, 'Mozart',     'Music',   40000),
(22222, 'Einstein',   'Physics', 95000),
(32343, 'El Said',    'History', 62000),
(33456, 'Gold',       'CompSci', 87000),
(45565, 'Katz',       'CompSci', 75000),
(58583, 'Califieri',  'History', 62000),
(76543, 'Singh',      'Finance', 80000),
(76766, 'Crick',      'Biology', 72000);

-- Function to Count Instructor from a department
DELIMITER $$

CREATE FUNCTION countInst(dept_name VARCHAR(100))
RETURNS INT
DETERMINISTIC
BEGIN
	DECLARE d_count INT;
    
    SELECT count(*) INTO d_count
    FROM instructor WHERE
    instructor.dept_name = dept_name;
    
    RETURN d_count;
END $$

DELIMITER ;

CREATE TABLE department (
    dept_name VARCHAR(20) PRIMARY KEY,
    building VARCHAR(20),
    budget INT
);
INSERT INTO department (dept_name, building, budget) VALUES
('CompSci', 'Taylor', 100000),
('Biology', 'Watson', 90000),
('Finance', 'Painter', 120000),
('History', 'King', 85000),
('Music', 'Carnegie', 70000),
('Physics', 'Newton', 95000);

SELECT dept_name, budget
FROM department
WHERE countInst(dept_name) > 12;

-- Example 3
CREATE TABLE customers (
    customer_id INT PRIMARY KEY,
    name VARCHAR(50),
    credit_limit INT
);

INSERT INTO customers (customer_id, name, credit_limit) VALUES
(1, 'Alice Johnson', 75000),   -- Platinum
(2, 'Bob Smith',     52000),   -- Platinum
(3, 'Charlie Lee',   45000),   -- Gold
(4, 'Diana Perez',   30000),   -- Gold
(5, 'Edward Brown',  25000),   -- Silver
(6, 'Fatima Khan',   10000);   -- Silver

DELIMITER $$

CREATE FUNCTION CustomerLevel(credit_limit INT)
RETURNS VARCHAR(100)
DETERMINISTIC
BEGIN
	IF credit_limit > 50000 THEN
		RETURN 'Platinum';
	ELSEIF credit_limit >= 30000 AND credit_limit <= 50000 THEN
		RETURN 'Gold';
	ELSE 
		RETURN 'Silver';
	END IF;
END$$
DELIMITER ;

SELECT name, CustomerLevel(credit_limit) AS CustomerLevel FROM customers;