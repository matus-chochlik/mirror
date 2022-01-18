CREATE TABLE person (
	person_id integer primary key autoincrement,
	given_name varchar,
	family_name varchar,
	email_address varchar);

INSERT INTO person (given_name, family_name, email_address)
VALUES("Matúš", "Chochlík", "user@example.com");
