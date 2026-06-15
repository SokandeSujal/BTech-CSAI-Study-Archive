USE endSem3;

CREATE TABLE employee (
    emp_id INT PRIMARY KEY,
    name VARCHAR(50),
    salary INT,
    dept_no INT
);

INSERT INTO employee (emp_id, name, salary, dept_no) VALUES
(1, 'Alice', 50000, 1),
(2, 'Bob', 45000, 1),
(3, 'Charlie', 55000, 1),

(4, 'David', 60000, 2),
(5, 'Emma', 65000, 2),

(6, 'Frank', 40000, 3),
(7, 'Grace', 35000, 3),
(8, 'Henry', 45000, 3);

CREATE TABLE deptsal (
    dept_no INT PRIMARY KEY,
    totalsalary INT
);

INSERT INTO deptsal (dept_no, totalsalary) VALUES
(1, NULL),
(2, NULL),
(3, NULL);


DELIMITER $$

CREATE PROCEDURE updateSalary (IN dept_no INT)
BEGIN
	UPDATE deptsal
    SET totalsalary = (
		SELECT SUM(salary) FROM employee WHERE employee.dept_no = dept_no
    ) WHERE deptsal.dept_no = dept_no;
END$$
DELIMITER ;

CALL updateSalary(3);

SELECT * FROM deptsal;

CREATE TABLE deptavg (
    dept_no INT PRIMARY KEY,
    avgsalary INT
);

INSERT INTO deptavg (dept_no, avgsalary) VALUES
(1, NULL),
(2, NULL),
(3, NULL);

DELIMITER $$

CREATE PROCEDURE avgSalary(IN dept_no INT)
BEGIN
	UPDATE deptavg 
    SET avgsalary = (
		SELECT AVG(salary) FROM employee WHERE employee.dept_no = dept_no
    ) WHERE deptavg.dept_no = dept_no;
END$$

DELIMITER ;

CALL avgSalary(1);
SELECT * FROM deptavg;
CALL avgSalary(2);


CREATE TABLE deptcount (
    dept_no INT PRIMARY KEY,
    empcount INT
);

INSERT INTO deptcount (dept_no, empcount) VALUES
(1, NULL),
(2, NULL),
(3, NULL);


DELIMITER $$

CREATE PROCEDURE countEmployees(IN dept_no INT)
BEGIN
	UPDATE deptcount SET empcount = (
		SELECT COUNT(*) FROM employee WHERE employee.dept_no = dept_no
    ) WHERE deptcount.dept_no = dept_no;
END$$

DELIMITER ;

SELECT * FROM employee;
SELECT * FROM deptcount;
CALL countEmployees(1);
CALL countEmployees(2);
CALL countEmployees(3);
SELECT * FROM deptcount;


DELIMITER $$

CREATE PROCEDURE maxSalary(OUT highest_salary INT)
BEGIN
	SELECT MAX(salary) INTO highest_salary FROM employee;
END$$

DELIMITER ;

CALL maxSalary(@MaxSalary);
SELECT @MaxSalary;



DELIMITER $$

CREATE PROCEDURE countEmployeeAboveCerSalary(IN threshold INT, OUT countEmp INT)
BEGIN
	SELECT COUNT(*) INTO countEmp FROM employee WHERE salary > threshold;
END$$

DELIMITER ;

CALL countEmployeeAboveCerSalary(50000, @CountEmp);
SELECT @CountEmp;

ALTER TABLE employee MODIFY column bonus INT default 10000;
SELECT * FROM employee;
DESC employee;

SET SQL_SAFE_UPDATES = 0;
UPDATE employee SET bonus = 10000 WHERE salary > 1000;

DELIMITER $$
CREATE PROCEDURE adjustBonus(INOUT emp_bonus INT, IN increment INT)
BEGIN
	UPDATE employee SET bonus = (bonus + increment);
    SET emp_bonus = emp_bonus + increment;
END$$

DELIMITER ;

SET @emp_bonus = 1000;
CALL adjustBonus(@emp_bonus, 500);
SELECT @emp_bonus;

SHOW PROCEDURE STATUS;

DELIMITER $$
CREATE PROCEDURE samplePro(INOUT emp_bonus INT, IN increment INT)
BEGIN
	UPDATE employee SET bonus = (bonus + increment);
    SET emp_bonus = emp_bonus + increment;
END$$

DELIMITER ;

DROP procedure samplePro;