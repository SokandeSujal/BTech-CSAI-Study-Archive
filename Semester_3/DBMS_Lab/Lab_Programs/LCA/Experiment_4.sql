use sem2dbms;

	CREATE TABLE customers(
		customer_id INT auto_increment PRIMARY KEY,
		first_name VARCHAR(100) not null,
		last_name VARCHAR(100) not null,
		email VARCHAR(100) not null,
		join_date DATE
	);

	CREATE TABLE orders(
		order_id INT AUTO_INCREMENT PRIMARY KEY,
		customer_id INT NOT NULL,
		order_date DATE NOT NULL,
		total_amount DECIMAL(8,2) NOT NULL CHECK (total_amount > 0),
		CONSTRAINT fk_customer FOREIGN KEY(customer_id) REFERENCES customers(customer_id) 
			ON DELETE CASCADE ON UPDATE CASCADE
	);

	CREATE TABLE products(
		product_id INT auto_increment PRIMARY KEY,
		product_name VARCHAR(100) not null,
		category ENUM('Electrical', 'Glass', 'Wood'),
		price DECIMAL(8, 2) NOT NULL CHECK (price > 0)
	);

CREATE TABLE order_items(
	item_id INT AUTO_INCREMENT PRIMARY KEY,
    order_id INT NOT NULL,
    product_id INT NOT NULL,
    quantity INT NOT NULL CHECK (quantity > 0),
    CONSTRAINT fk_orderId FOREIGN KEY(order_id) REFERENCES orders(order_id) ON DELETE CASCADE ON UPDATE CASCADE,
    CONSTRAINT fk_productId FOREIGN KEY(product_id) REFERENCES products(product_id) ON DELETE CASCADE ON UPDATE CASCADE,
    UNIQUE(order_id, product_id)
);


	CREATE TABLE employees(
		employee_id INT auto_increment PRIMARY KEY,
		first_name VARCHAR(100) not null,
		last_name VARCHAR(100) not null,
		hire_date DATE, 
		department VARCHAR(100) not null
	);
    
    
    
-- Insert sample customers
INSERT INTO customers (first_name, last_name, email, join_date) VALUES
('Alice', 'Johnson', 'alice.johnson@example.com', '2023-01-15'),
('Bob', 'Smith', 'bob.smith@example.com', '2023-02-20'),
('Charlie', 'Brown', 'charlie.brown@example.com', '2023-03-05');

-- Insert sample products
INSERT INTO products (product_name, category, price) VALUES
('LED Bulb', 'Electrical', 5.99),
('Glass Vase', 'Glass', 12.50),
('Wooden Chair', 'Wood', 75.00),
('Desk Lamp', 'Electrical', 22.99);

-- Insert sample orders
INSERT INTO orders (customer_id, order_date, total_amount) VALUES
(1, '2023-04-01', 38.48),
(2, '2023-04-05', 87.50),
(3, '2023-04-10', 98.99);

-- Insert sample order items
INSERT INTO order_items (order_id, product_id, quantity) VALUES
(1, 1, 2),  -- Alice bought 2 LED Bulbs
(1, 2, 1),  -- Alice bought 1 Glass Vase
(2, 3, 1),  -- Bob bought 1 Wooden Chair
(2, 2, 3),  -- Bob bought 3 Glass Vases
(3, 4, 2),  -- Charlie bought 2 Desk Lamps
(3, 3, 1);  -- Charlie bought 1 Wooden Chair

-- Insert sample employees
INSERT INTO employees (first_name, last_name, hire_date, department) VALUES
('Diana', 'Prince', '2020-06-15', 'Sales'),
('Ethan', 'Hunt', '2019-09-10', 'Operations'),
('Fiona', 'Gallagher', '2021-03-20', 'Customer Service');


-- Q1
SELECT 
    CONCAT(
        UPPER(LEFT(first_name, 1)), LOWER(SUBSTRING(first_name, 2)), ' ',
        UPPER(LEFT(last_name, 1)), LOWER(SUBSTRING(last_name, 2))
    ) AS full_name,
    TIMESTAMPDIFF(MONTH, join_date, CURDATE()) AS membership_duration_months,
    CONCAT(LEFT(email, 3), '...', SUBSTRING(email, LOCATE('@', email))) AS masked_email
FROM customers
WHERE YEAR(join_date) = 2023
ORDER BY join_date ASC;

-- Q2
SELECT
	p.category,
    SUM(oi.quantity * p.price) AS TOTAL_REVENUE,
    AVG(oi.quantity) AS avg_quantity_per_order,
    COUNT(DISTINCT(oi.order_id)) AS unique_orders
FROM order_items as oi
JOIN products p ON oi.product_id = p.product_id
GROUP BY p.category
HAVING SUM(oi.quantity * p.price) > (SELECT AVG(oi.quantity * p.price))
ORDER BY total_revenue DESC;
    
    
SET autocommit = 0;
START TRANSACTION;

SAVEPOINT noChange;

SELECT * FROM customers;
UPDATE customers SET customer_id = 5 WHERE customer_id = 1;
SAVEPOINT after_first_update;

UPDATE customers SET customer_id = 4 WHERE customer_id = 3;

ROLLBACK TO noChange;
COMMIT;

SEt autocommit = 1;

