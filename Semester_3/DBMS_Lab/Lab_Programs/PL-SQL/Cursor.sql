USE endsem3;

-- SELECT * FROM employee;

-- DROP PROCEDURE updateSalaryAll;

DELIMITER $$
CREATE PROCEDURE updateSalaryAll()
BEGIN
	DECLARE empID INT;
    DEClARE oldsal INT;
    DECLARE done INT default 0;
    
    DECLARE deptCursor CURSOR FOR
	SELECT emp_id, salary FROM employee;
    
    DECLARE CONTINUE HANDLER FOR NOT FOUND SET done = 1;
    
    OPEN deptCursor;
    
    fetch_loop: LOOP
		FETCH deptCursor into empID, oldsal;
        
        IF done = 1 THEN
			leave fetch_loop;
		END IF;
        
        UPDATE employee SET salary = (salary + (salary * 10 / 100)) WHERE emp_id = empID;
        SELECT CONCAT('Empoyee ID: ', empID, ' | Employee Old Salary: ', oldsal, ' | Employee New Salary: ', (SELECT salary FROM employee WHERE emp_id = empID));
    END LOOP;
    
    CLOSE deptCursor;
END $$

DELIMITER ;

Call updateSalaryAll();

SELECT * FROM employee;