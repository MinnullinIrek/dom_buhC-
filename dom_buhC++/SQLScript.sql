DROP TABLE debet_category	;
DROP TABLE debet_type		;
DROP TABLE credit_category	;
DROP TABLE credit_type		;
DROP TABLE accounts			;
DROP TABLE debet			;
DROP TABLE credit			;

CREATE TABLE debet_category(name TEXT PRIMARY KEY);
CREATE TABLE debet_type(name TEXT PRIMARY KEY, category_name TEXT, FOREIGN KEY (category_name) REFERENCES debet_category(name));
CREATE TABLE credit_category(name TEXT PRIMARY KEY);
CREATE TABLE credit_type(name TEXT PRIMARY KEY, category_name TEXT, FOREIGN KEY (category_name) REFERENCES credit_category(name));
CREATE TABLE accounts ( name TEXT PRIMARY KEY, comment TEXT);
CREATE TABLE debet (id INTEGER PRIMARY KEY AUTOINCREMENT, account_name INTEGER, dc_type_name TEXT, date TEXT, comment TEXT, summ INTEGER, name TEXT, 
		FOREIGN KEY (account_name) REFERENCES accounts(name), FOREIGN KEY (dc_type_name) REFERENCES debet_type(name));
CREATE TABLE credit    (id INTEGER PRIMARY KEY AUTOINCREMENT, account_name INTEGER, dc_type_name TEXT, summ INTEGER, 
	name TEXT, date TEXT, comment TEXT, FOREIGN KEY (account_name) REFERENCES accounts(name), FOREIGN KEY (dc_type_name) REFERENCES credit_type(name));


