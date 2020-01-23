select continent, region, count(*) as num_countries
from country
group by continent, region
order by num_countries desc;