(select country.name as country
from country)
except
(select distinct country.name as country
from country join city on (country.code = city.countrycode));