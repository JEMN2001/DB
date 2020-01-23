select country.name as country, countrylanguage.language as language
from country left outer join countrylanguage on (country.code = countrylanguage.countrycode)
where countrylanguage.language is null or countrylanguage.isofficial = true
order by country;
