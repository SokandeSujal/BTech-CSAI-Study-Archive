CREATE TABLE students (
    student_id INT PRIMARY KEY AUTO_INCREMENT,
    name       VARCHAR(50),
    department VARCHAR(30),
    marks      INT,
    created_at DATETIME,
    updated_at DATETIME
);

CREATE TABLE students_audit (
    audit_id     INT PRIMARY KEY AUTO_INCREMENT,
    student_id   INT,
    action       VARCHAR(20),
    old_name     VARCHAR(50),
    new_name     VARCHAR(50),
    action_time  DATETIME
);

CREATE TABLE dept_summary (
    department     VARCHAR(30) PRIMARY KEY,
    total_students INT
);

INSERT INTO dept_summary (department, total_students)
VALUES ('CSE', 0),
       ('IT', 0),
       ('ENTC', 0);

INSERT INTO students (name, department, marks, created_at, updated_at)
VALUES ('Amit', 'CSE', 80, NOW(), NOW()),
       ('Riya', 'IT',  90, NOW(), NOW());

-- Before INSERT

DELIMITER $$

CREATE TRIGGER update_created_updatedTime
BEFORE INSERT ON students
FOR EACH ROW
BEGIN
	SET NEW.created_at = NOW();
    SET NEW.updated_at = NOW();
END $$

DELIMITER ;

INSERT INTO students (name, department, marks)
VALUES ('Aayush', 'CSE', 89);

SELECT * FROM students;


-- 2. After Insert

CREATE TRIGGER update_dept_summary
AFTER INSERT ON students
FOR EACH ROW
UPDATE dept_summary
SET total_students = total_students + 1
WHERE department = NEW.department;

SELECT * FROM dept_summary;

-- INSERT INTO students (name, department, marks) VALUES ('Neha', 'IT', 88);



-- 3. BEFORE UPDATE Trigger
DELIMITER $$

CREATE TRIGGER checkmarks
BEFORE UPDATE ON students
FOR EACH ROW
BEGIN
	IF NEW.marks < 0 THEN
		SET NEW.marks = 0;
	ELSEIF NEW.marks > 100 THEN
		SET NEW.marks = 100;
	END IF;
END$$

DELIMITER ;

UPDATE students
SET marks = 120
WHERE student_id = 1;


SELECT * FROM students;

-- 4. AFTER UPDATE Trigger
-- 4. AFTER UPDATE Trigger
DELIMITER $$

CREATE TRIGGER updateAuditTable
AFTER UPDATE ON Students
FOR EACH ROW
BEGIN
	INSERT INTO students_audit
			(student_id, action, old_name, new_name, action_time)
        VALUES
			(OLD.student_id, 'UPDATE', OLD.name, NEW.name, NOW());
END$$

DELIMITER ;

UPDATE students
SET name = 'Amit Kumar'
WHERE student_id = 1;

    
-- SELECT * FROM students_audit;

-- 5. BEFORE DELETE Trigger

DELIMITER $$

CREATE TRIGGER bd_students_log_delete
BEFORE DELETE ON students
FOR EACH ROW
BEGIN
	INSERT INTO students_audit
			(student_id, action, old_name, action_time)
		VALUES
			(OLD.student_id, 'DELETE', OLD.name, NOW());
END$$

DELIMITER ;  

DELETE FROM students
WHERE student_id = 2;

SELECT * FROM students_audit;


-- 6. AFTER DELETE Trigger

CREATE TRIGGER ad_students_update_dept_count
AFTER DELETE ON students
FOR EACH ROW
UPDATE dept_summary
SET total_students = total_students - 1 WHERE department = OLD.department;

SELECT * FROM dept_summary;

DELETE FROM students
WHERE student_id = 3;
