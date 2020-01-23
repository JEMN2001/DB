select population from country where code = 'CHL';

create or replace function updatePopulation()
	returns trigger as
	$$
	begin
		update country set population =
		case
			when country.code = new.countrycode
			then population+new.population
			else population
		end;
		return new;
	end;
	$$
	language 'plpgsql';

create trigger updatePopulation
	after insert on city
	for each row
	execute procedure updatePopulation();

insert into city values (4080 , 'Springfield ', 'CHL ', 'Springfield ', 10000000) ;
select population from country where code = 'CHL';