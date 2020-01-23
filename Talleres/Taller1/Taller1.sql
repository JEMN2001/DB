create table unid_acad
(nombre_unid varchar (20) , edificio varchar (15) not null , presupuesto numeric (12,2) ,
primary key (nombre_unid));

create table curso
(curso_cod varchar (7) , nombre varchar (50) , nombre_unid varchar (20) , creditos numeric (2,0) ,
primary key (curso_cod) , foreign key (nombre_unid) references unid_acad);

create table instructor
(inst_ID varchar (5), nombre varchar (20) not null, nombre_unid varchar (29), salario numeric (8,2),
primary key (inst_ID), foreign key (nombre_unid) references unid_acad);

create table grupo
(curso_cod varchar (8), grupo_cod varchar (8), semestre varchar (6), ano numeric (4,0),
primary key (curso_cod, grupo_cod, semestre, ano), foreign key (curso_cod) references curso);

create table dicta
(inst_ID varchar (5), curso_cod varchar (8), grupo_cod varchar (8), semestre varchar (6), ano numeric (4,0),
primary key (inst_ID, curso_cod, grupo_cod, semestre, ano),
foreign key (curso_cod, grupo_cod, semestre, ano) references grupo,
foreign key (inst_ID) references instructor);

insert into unid_acad values ('MACC', 'Cabal', 100.0);
insert into curso values ('MA001', 'Algoritmos', 'MACC', 3.0);
insert into instructor values ('0000', 'Julian', 'MACC', 18);
insert into grupo values ('MA001', '1', '4', 2019);
insert into dicta values ('0000', 'MA001', '1', '4', 2019);

insert into unid_acad values ('Jurisprudencia', 'Jockey', 350.0);
insert into curso values ('JU001', 'Procesal', 'Jurisprudencia', 4.0);
insert into instructor values ('0001', 'Alvarez', 'Jurisprudencia', 25);
insert into grupo values ('JU001', '1', '6', 2019);
insert into dicta values ('0001', 'JU001', '1', '6', 2019);

insert into curso values ('MA002', 'Bases de datos', 'MACC', 3.0);
insert into instructor values ('0002', 'Juan Fernando', 'MACC', 22);
insert into grupo values ('MA002', '1', '4', 2019);
insert into dicta values ('0002', 'MA002', '1', '4', 2019);




