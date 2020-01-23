select continent, sum(population) as population
from country
group by continent
order by population desc;