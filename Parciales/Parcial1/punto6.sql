create view ELisabethIdiomas as
select countrylanguage.language, count(*) as num_countries
from country join countrylanguage on (country.code = countrylanguage.countrycode)
where country.headofstate = 'Elisabeth II'
group by countrylanguage.language
having count(*) >= 2
order by num_countries desc;
