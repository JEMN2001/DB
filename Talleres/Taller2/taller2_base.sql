create table unid_acad
  (nombre_unid varchar (20),
  edificio varchar (15) not null,
  presupuesto numeric (12,2),
  primary key (nombre_unid));

create table curso
  (curso_cod varchar (7),
  nombre varchar (50),
  nombre_unid varchar (20),
  creditos numeric (2,0),
  primary key (curso_cod),
  foreign key (nombre_unid) references unid_acad);
			 
create table instructor
  (inst_ID varchar (5),
  nombres varchar (20) not null,
  apellidos varchar (20) not null,
  nombre_unid varchar (20),
  salario numeric (8,2),
  primary key (inst_ID),
  foreign key (nombre_unid) references unid_acad);	
			   
create table grupo
  (curso_cod varchar (8),
  grupo_cod varchar (8),
  semestre varchar (6),
  ano numeric (4,0),
  primary key (curso_cod, grupo_cod, semestre, ano),
  foreign key (curso_cod) references curso);
			   
create table dicta
  (inst_ID varchar (5),
  curso_cod varchar (8),
  grupo_cod varchar (8),
  semestre varchar (6),
  ano numeric (4,0),
  primary key (inst_ID, curso_cod, grupo_cod, semestre, ano),
  foreign key (curso_cod, grupo_cod, semestre, ano) references grupo,
  foreign key (inst_ID) references instructor);
			   
insert into unid_acad values('MACC', 'Cabal', 100.0);
insert into unid_acad values('ECON', 'Pedro', 800.0);
insert into unid_acad values('BIOL', 'QM', 500.0);
insert into curso values('000', 'programacion', 'MACC', 4 );
insert into curso values('001', 'arquitectura', 'MACC', 4 );
insert into curso values('002', 'algoritmos', 'MACC', 4 );
insert into curso values('003', 'laboratorio', 'BIOL', 5 );
insert into instructor values('1', 'Juan', 'Perez', 'MACC', 100);
insert into instructor values('2', 'Ana', 'Gutierrez', 'MACC', 200);
insert into instructor values('3', 'Ernerto', 'Huertas', 'ECON', 500);
insert into instructor values('4', 'Reinaldo', 'Rondon', 'MACC', 300);
insert into grupo values('000', '1','1', 2018);			   
insert into grupo values('001', '1','2', 2018);			   
insert into grupo values('002', '1','1', 2018);			   
insert into grupo values('002', '2','1', 2018);		
insert into dicta values('1', '000', '1', '1', 2018);
insert into dicta values('2', '001', '1', '2', 2018);
insert into dicta values('3', '002', '1', '1', 2018);
insert into dicta values('4', '002', '2', '1', 2018);
			   



