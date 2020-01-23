--Step 1
CREATE TABLE author (name varchar(20), address varchar(20), URL varchar(20), primary key (name));
CREATE TABLE book (ISBN varchar(13), title varchar(50), year varchar(4), price integer check (price >= 0), primary key (ISBN))
CREATE TABLE publisher (name varchar(20), address varchar(20), phone integer, URL varchar(20), primary key (name));
CREATE TABLE shopping_basket (basket_id integer check (basket_id >= 0), primary key (basket_id));
CREATE TABLE warehouse (code integer check (code >= 0), address varchar(20), phone integer, primary key (code));
CREATE TABLE costumer (email varchar(20), name varchar(50), address varchar(20), phone integer, primary key (email));

--Step 2
CREATE TABLE written_by (name varchar(20), ISBN varchar(13), primary key (ISBN), foreign key (name) references author (name), foreign key (ISBN) references book (ISBN));
CREATE TABLE published_by (name varchar(20), ISBN varchar(13), primary key (ISBN), foreign key (name) references publisher (name), foreign key (ISBN) references book (ISBN));
CREATE TABLE contains (basket_id integer check (basket_id >= 0), ISBN varchar(13), number integer, primary key (basket_id, ISBN), foreign key (basket_id) references shopping_basket (basket_id), foreign key (ISBN) references book (ISBN));
CREATE TABLE stocks (code integer check (code >= 0), ISBN varchar(20), number integer, primary key (code, ISBN), foreign key (code) references warehouse (code), foreign key (ISBN) references book (ISBN));
CREATE TABLE basket_of(basket_id integer check (basket_id >= 0), email varchar(20), primary key (email), foreign key (basket_id) references shopping_basket (basket_id), foreign key (email) references costumer (email));

--d
ALTER TABLE stocks DROP ISBN;
ALTER TABLE stocks RENAME code to warehouse_code;
ALTER TABLE stocks ADD article_code varchar(20);
ALTER TABLE stocks DROP CONSTRAINT stocks_code_fkey;

ALTER TABLE contains DROP ISBN;
ALTER TABLE contains ADD code varchar(20);

ALTER TABLE book DROP price;
CREATE TABLE Article (code varchar(13), price integer check (price >= 0), primary key (code));
ALTER TABLE book ADD CONSTRAINT book_isbn_fkey foreign key (ISBN) references Article (code);
CREATE TABLE electronics (serial varchar(13), primary key (serial), foreign key (serial) references Article (code));
CREATE TABLE PC (serial varchar(13), brand varchar(20), SO varchar(8), type boolean, primary key (serial), foreign key (serial) references electronics (serial));
CREATE TABLE CellPhones (serial varchar(13), brand varchar(20), SO varchar(8), network char(2), primary key (serial), foreign key (serial) references electronics(serial));

ALTER TABLE contains ADD CONSTRAINT contains_code_fkey foreign key (code) references Article(code);
ALTER TABLE stocks ADD CONSTRAINT stocks_article_code_fkey foreign key (article_code) references article(code);
ALTER TABLE stocks ADD CONSTRAINT stocks_warehouse_fkey foreign key (warehouse_code) references warehouse(code);
