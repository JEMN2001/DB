select language,
round(sum(percentage*(select population from country where code = countrycode)/100)) as population
from countrylanguage
group by language;