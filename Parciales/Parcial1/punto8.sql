create or replace function restriccion()
returns trigger as
$$
begin
	if (select sum(percentage) from countrylanguage where countrycode = new.countrycode group by countrycode)+new.percentage > 100
	then raise exception 'It goes over 100 percent!';
	end if;
	return new;
end;
$$
language 'plpgsql';

create trigger restriccion
before insert on countrylanguage
for each row
execute procedure restriccion();

insert into countrylanguage values ( 'AFG' , 'Spanish ' , false , 10) ;
