USE endsem3;

DROP TABLE employee, department;

CREATE TABLE employee (
    emp_id INT PRIMARY KEY,
    name VARCHAR(50),
    dept_no INT,
    job_id INT,
    salary INT
);

CREATE TABLE department (
    dept_no INT PRIMARY KEY,
    dept_name VARCHAR(30),
    budget INT
);

CREATE TABLE jobs (
    job_id INT PRIMARY KEY,
    job_title VARCHAR(50),
    min_salary INT,
    max_salary INT
);

INSERT INTO employee (emp_id, name, dept_no, job_id, salary) VALUES
(1, 'Alice', 1, 101, 45000),
(2, 'Bob', 1, 102, 55000),
(3, 'Charlie', 2, 103, 60000),
(4, 'Diana', 2, 104, 40000),
(5, 'Edward', 3, 105, 30000),
(6, 'Fatima', 3, 101, 35000),
(7, 'George', 1, 102, 50000),
(8, 'Hannah', 2, 103, 65000),
(9, 'Ian', 3, 104, 28000),
(10, 'Julia', 1, 101, 47000);

INSERT INTO department (dept_no, dept_name, budget) VALUES
(1, 'HR', 200000),
(2, 'Finance', 300000),
(3, 'IT', 150000);

INSERT INTO jobs (job_id, job_title, min_salary, max_salary) VALUES
(101, 'Analyst', 30000, 50000),
(102, 'Manager', 50000, 70000),
(103, 'Consultant', 40000, 65000),
(104, 'Clerk', 25000, 45000),
(105, 'Technician', 20000, 40000);





SELECT * FROM employee;
SELECT * FROM department;
SELECT * FROM jobs;

-- Task: Determine employee level based on salary.
DELIMITER $$
CREATE PROCEDURE empLevel(IN emp_id INT, OUT empLevel VARCHAR(50))
BEGIN
	DECLARE sal INT;
    SELECT salary INTO sal FROM employee WHERE employee.emp_id = emp_id;
    
    IF sal > 60000 THEN
		SET empLevel = 'Platinum';
	ELSEIF sal BETWEEN 40000 AND 60000 THEN
		SET empLevel = 'Gold';
	ELSE
        SET empLevel = 'Silver';
    END IF;
END$$
DELIMITER ;

CALL empLevel(3, @lvl);
SELECT @lvl;


-- Categorize departments based on budget.
DROP PROCEDURE deptBudgetCategory;

DELIMITER $$

CREATE PROCEDURE deptBudgetCategory(IN p_dept_no INT, OUT category VARCHAR(20))
BEGIN
    DECLARE budget INT;

    -- Get the budget into the variable
    SELECT d.budget
    INTO budget
    FROM department d
    WHERE d.dept_no = p_dept_no;

    -- Categorize the budget
    CASE 
        WHEN budget > 250000 THEN
            SET category = 'Large';
        WHEN budget BETWEEN 150000 AND 250000 THEN
            SET category = 'Medium';
        ELSE
            SET category = 'Small';
    END CASE;
END$$

DELIMITER ;

CALL deptBudgetCategory(1, @depLvl);
SELECT @depLvl;

SELECT * FROM department;


-- Total Salary While

DELIMITER $$
CREATE PROCEDURE totalDeptSalary(IN DeptNumber INT, OUT total_salary INT)
BEGIN
	DECLARE i INT DEFAULT 1;
    DECLARE sal INT DEFAULT 0;
    DECLARE empCount INT;
    
    Select COUNT(*) INTO empCount FROM employee WHERE dept_no = DeptNumber;
    
    WHILE i<= empCount DO
		SET i = i - 1;
		SELECT salary INTO @S FROM employee WHERE dept_no = DeptNumber LIMIT i, 1;
        SET sal = sal + @S;
        SET i = i + 1;
        SET i = i + 1;
	END WHILE;
    
    SET total_salary = sal;
END$$

DELIMITER ;

CALL totalDeptSalary(1, @T);
SELECT @T;

SELECT @T, SUM(salary) FROM employee WHERE dept_no = 1;