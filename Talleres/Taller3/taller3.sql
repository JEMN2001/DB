--PUNTO 2
DELETE from curso2 where nombre like '%4';

--PUNTO3
create table curso_all(curso_cod varchar (7), nombre varchar (50), nombre_unid varchar (20), creditos numeric (2), primary key (curso_cod));
insert into curso_all select * from curso;
INSERT INTO CURSO_ALL SELECT * FROM ((select * from curso2) EXCEPT (select * from curso)) as A;

--PUNTO4
select * from unid_acad;
UPDATE unid_acad SET presupuesto = presupuesto*1.03;
UPDATE unid_acad SET presupuesto = presupuesto+(select min(presupuesto) from unid_acad);

--PUNTO5
create view presupuesto as
SELECT round(avg(presupuesto),3) as promedio, min(presupuesto) as mínimo, max(presupuesto) as máximo, round(stddev(presupuesto),3) as desviación from unid_acad;

--PUNTO6
CREATE VIEW resumenGruposUnidad AS
select nombre_unid as unidad, nombre as curso, grupo_cod, ano as año, semestre from curso LEFT OUTER JOIN grupo on curso.curso_cod = grupo.curso_cod;
--a
INSERT INTO grupo VALUES ('003', '1', '1', 2018);
INSERT INTO grupo VALUES ('003', '1', '2', 2018);
--b
select * from resumenGruposUnidad;

--PUNTO7
CREATE MATERIALIZED VIEW instructorUbic AS
SELECT nombres, apellidos, edificio FROM instructor NATURAL JOIN unid_acad;
--a
INSERT INTO instructor VALUES ('5', 'Camilo', 'Ramirez', 'ECON', 200);
--b
SELECT * FROM instructorUbic;
--c
REFRESH MATERIALIZED VIEW instructorUbic;
--d
SELECT * FROM instructorUbic;

--PUNTO 8
BEGIN;
UPDATE unid_acad SET presupuesto =
	CASE
		WHEN presupuesto = (select min(presupuesto) from unid_acad)
		THEN presupuesto+(select round(avg(presupuesto),2) from unid_acad)
		ELSE presupuesto
	END;
update unid_acad SET presupuesto =
	CASE
		WHEN presupuesto = (select max(presupuesto) from unid_acad)
		THEN presupuesto+(select round(avg(presupuesto),2) from unid_acad)
		ELSE presupuesto
	END;
COMMIT;

--PUNTO9
--a
ALTER TABLE curso ADD constraint nombre_unico UNIQUE (nombre);
--b
CREATE TABLE examen (examen_cod varchar(7), curso_nombre varchar(20), fecha date not null,
hora_inicio time DEFAULT '00:00:00', hora_fin time DEFAULT '00:00:00', primary key (examen_cod), foreign key (curso_nombre) references curso(nombre) on delete cascade on update cascade);
--c
INSERT INTO examen VALUES ('000', 'programacion', '2019-08-31', '11:00:00', '13:00:00');
INSERT INTO examen VALUES ('100', 'arquitectura', '2019-09-5', '9:00:00', '11:00:00');
INSERT INTO examen VALUES ('101', 'arquitectura', '2019-03-24', '16:00:00', '18:00:00');
--d
UPDATE curso SET nombre =
	CASE
		WHEN nombre = 'programacion'
		THEN 'prog computadores'
		ELSE nombre
	END;
--e
CREATE VIEW duracionExamenes AS
SELECT curso_nombre as curso, EXTRACT(HOUR FROM hora_inicio) as hora_inicio, (EXTRACT(HOUR FROM hora_fin)-EXTRACT(HOUR FROM hora_inicio)) as duracion from examen;

--PUNTO10
CREATE DOMAIN credito AS INT CHECK (value >= 0);
ALTER TABLE curso
ALTER COLUMN creditos SET DATA TYPE credito;

--PUNTO11
--a
CREATE USER  ramon WITH PASSWORD 'ramon';
GRANT SELECT ON unid_acad TO ramon;
--c
CREATE ROLE planeacion;
GRANT INSERT ON unid_acad TO planeacion;
GRANT planeacion TO ramon;
--CON USER RAMON
INSERT INTO unid_acad VALUES ('JURIS', 'Jockey', 2045.76);
--d
REVOKE INSERT ON unid_acad FROM planeacion;
--CON USER RAMON
INSERT INTO unid_acad VALUES ('CELEE', 'SantaFe', 1000.19);
SELECT * FROM unid_acad;
--e
REVOKE SELECT ON unid_acad FROM ramon;
--CON USER RAMON
SELECT * FROM unid_acad;
