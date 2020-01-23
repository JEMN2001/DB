CREATE TABLE hotel(nombre varchar(20), ciudad varchar(20), estrellas smallint, num_habitaciones int,direccion varchar(20), primary key (nombre, ciudad));
CREATE TABLE habitación(numero int unique, capacidad int, bano_privado bool, televisor bool, minibar bool);
CREATE TABLE usuario(id_usuario varchar(10), nombre varchar(20), apellido varchar(20), edad int, genero char(1), primary key (id_usuario));
CREATE TABLE medio_pago(id_medio varchar(10), yipo varchar(10), numero int, primary key (id_medio));
CREATE TABLE ofrece(nombre_hotel varchar(20),
					ciudad_hotel varchar(20),
					numero_habitacion int,
					primary key (nombre_hotel, ciudad_hotel, numero_habitacion),
					foreign key (nombre_hotel, ciudad_hotel) references hotel (nombre, ciudad) on delete cascade on update cascade,
					foreign key (numero_habitacion) references habitación (numero) on delete cascade on update cascade
);
CREATE TABLE arrienda(numero_habitacion int,
					  id_usuario varchar(10),
					  fecha_entrada date, fecha_salida date,
					  num_invitados int,
					  costo int,
					  primary key (numero_habitacion, id_usuario),
					  foreign key (numero_habitacion) references habitación (numero) on delete cascade on update cascade,
					  foreign key (id_usuario) references usuario (id_usuario) on delete cascade on update cascade
);
CREATE TABLE paga_con(id_medio varchar(10),
					  id_usuario varchar(10),
					  primary key (id_medio, id_usuario),
					  foreign key (id_medio) references medio_pago (id_medio) on delete cascade on update cascade,
					  foreign key (id_usuario) references usuario (id_usuario) on delete cascade on update cascade
);
