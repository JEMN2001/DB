select governmentform, count(*) as num_countries
from country
group by governmentform
order by count(*) desc
limit 5;
