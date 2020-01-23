create view top_dense_cities as
select 
	rank() over (order by population/surfacearea desc) as spot, 
	name,
	round(cast(population/surfacearea as numeric), 2) as density
from country
order by spot;
select * from top_dense_cities limit 5;