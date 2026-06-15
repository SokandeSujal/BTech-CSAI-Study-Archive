CREATE DATABASE plsql_db;
USE plsql_db;

CREATE TABLE users (
	id INT auto_increment primary key,
    username varchar(50) not null,
    email varchar(100) NOT NULL,
    updated_at TIMESTAMP
);

CREATE TABLE user_audit_log (
	audit_log INT AUTO_INCREMENT PRIMARY KEY,
    user_id INT,
    action VARCHAR(50),
    old_email VARCHAR(100),
    new_email VARCHAR(100),
    changed_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP
);

INSERT INTO users(username, email) VALUES ('Sujal', 'sujalsokande@gmail.com');

SELECT * FROM users;

DELIMITER $$
	CREATE TRIGGER after_user_update
	AFTER UPDATE ON users
    FOR EACH ROW
    BEGIN
		INSERT INTO user_audit_log (user_id, action, old_email, new_email, changed_at)
        VALUES (OLD.id, 'UPDATE', OLD.email, NEW.email, NOW());
END $$

SHOW triggers;

UPDATE users SET email = 'sokandesujal@gmail.com' WHERE id = 1;

SELECT * FROM users;
SELECT * FROM user_audit_log;


-- ASSIGNMENT NO. 07: CREATE TRIGGERS USING PL/SQL

DROP DATABASE Assignment7;
CREATE DATABASE Assignment7;

USE Assignment7;

CREATE TABLE student (
    prn VARCHAR(15) PRIMARY KEY,
    name VARCHAR(50) NOT NULL,
    address VARCHAR(100),
    dob DATE NOT NULL,
    fees DECIMAL(10,2) NOT NULL
);

CREATE TABLE transaction_master (
    transaction_id INT PRIMARY KEY AUTO_INCREMENT,
    prn VARCHAR(15) NOT NULL,
    transaction_date DATE DEFAULT (CURRENT_DATE),
    amount DECIMAL(10,2) NOT NULL,
    transaction_type VARCHAR(20)
);

INSERT INTO student VALUES ('2021BTCS001', 'Rajesh Kumar', 'Shivaji Nagar, Pune', '2003-03-15', 75000);
INSERT INTO student VALUES ('2021BTEC002', 'Priya Sharma', 'Kothrud, Pune', '2004-07-22', 68000);
INSERT INTO student VALUES ('2021BTME003', 'Amit Patel', 'Deccan, Pune', '2003-01-10', 72000);
INSERT INTO student VALUES ('SHORT123', 'Test User', 'Pune', '2003-05-10', 50000);

DELIMITER $$
CREATE TRIGGER check_prn_length
BEFORE INSERT ON transaction_master
FOR EACH ROW
BEGIN
    IF LENGTH(NEW.prn) < 10 THEN
        SIGNAL SQLSTATE '45000' 
        SET MESSAGE_TEXT = 'PRN length must be at least 10 characters';
    END IF;
END $$
DELIMITER ;

SHOW triggers;

INSERT INTO transaction_master (prn, amount, transaction_type) 
VALUES ('2021BTCS001', 25000, 'FEES_PAYMENT');

INSERT INTO transaction_master (prn, amount, transaction_type) 
VALUES ('2021BTEC002', 22000, 'FEES_PAYMENT');

INSERT INTO transaction_master (prn, amount, transaction_type) 
VALUES ('SHORT123', 15000, 'FEES_PAYMENT');

INSERT INTO transaction_master (prn, amount, transaction_type) 
VALUES ('ABC12', 10000, 'FEES_PAYMENT');

INSERT INTO transaction_master (prn, amount, transaction_type) 
VALUES ('2021BTME003', 24000, 'HOSTEL_FEES');

SELECT * FROM student;
SELECT * FROM transaction_master;

SHOW TRIGGERS;