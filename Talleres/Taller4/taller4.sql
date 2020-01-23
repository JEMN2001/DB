--PUNTO2
CREATE OR REPLACE FUNCTION actualizarGrupos()
RETURNS TRIGGER AS 
$$
BEGIN
	UPDATE curso SET num_grupos = 
	CASE
		WHEN curso_cod = new.curso_cod
		THEN num_grupos+1
		ELSE num_grupos
	END;
	RETURN new;
END;
$$
LANGUAGE 'plpgsql';

CREATE TRIGGER actualizarGrupos
AFTER INSERT ON grupo
FOR EACH ROW
EXECUTE PROCEDURE actualizarGrupos();

CREATE OR REPLACE FUNCTION actualizarGrupos1()
RETURNS TRIGGER AS
$$
BEGIN
	UPDATE curso SET num_grupos = 
	CASE
		WHEN curso_cod = old.curso_cod
		THEN num_grupos-1
		ELSE num_grupos
	END;
	RETURN old;
END;
$$
LANGUAGE 'plpgsql';

CREATE TRIGGER actualizarGrupos1
AFTER DELETE ON grupo
FOR EACH ROW
EXECUTE PROCEDURE actualizarGrupos1();
--PUNTO 3
CREATE OR REPLACE FUNCTION actualizarCarga()
RETURNS TRIGGER AS
$$
BEGIN
	UPDATE instructor SET carga_creditos =
	CASE
		WHEN instructor.inst_id = new.INST_ID
		THEN carga_creditos+(select creditos from curso where curso_cod = new.curso_cod)
		ELSE carga_creditos
	END;
	RETURN new;
END;
$$
LANGUAGE 'plpgsql';

CREATE TRIGGER actualizarCarga
AFTER INSERT ON dicta
FOR EACH ROW
EXECUTE PROCEDURE actualizarCarga();

CREATE OR REPLACE FUNCTION actualizarCarga1()
RETURNS TRIGGER AS
$$
BEGIN
	UPDATE instructor SET carga_creditos =
	CASE
		WHEN instructor.inst_id = old.inst_id
		THEN carga_creditos-(select creditos from curso where curso_cod = old.curso_cod)
		ELSE carga_creditos
	END;
	RETURN old;
END;
$$
LANGUAGE 'plpgsql';

CREATE TRIGGER actualizarCarga1
AFTER DELETE ON dicta
FOR EACH ROW
EXECUTE PROCEDURE actualizarCarga1();

--PUNTO4
CREATE OR REPLACE FUNCTION excesoCreditos()
RETURNS TRIGGER AS
$$
BEGIN
	IF (SELECT carga_creditos from instructor WHERE inst_id = new.inst_id) +
	   (SELECT creditos from curso where curso_cod = new.curso_cod) > 18
	THEN RAISE EXCEPTION 'This instructure cant teach this course';
	END IF;
	RETURN new;
END;
$$
LANGUAGE 'plpgsql';

CREATE TRIGGER excesoCreditos
BEFORE INSERT ON dicta
FOR EACH ROW
EXECUTE PROCEDURE excesoCreditos();
