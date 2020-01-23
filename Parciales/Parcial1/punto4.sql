select city.name as city_name, country.name as country_name, country.population as country_pop, city.population as city_pop, round((city.population/cast(country.population as decimal)),4) as fraction_pop
from country join city on (country.code = city.countrycode)
order by fraction_pop desc;
