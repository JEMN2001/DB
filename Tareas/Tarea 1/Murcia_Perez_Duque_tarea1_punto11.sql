alter table city add constraint non_negative_pop check (population >= 0);
insert into city values (1656, 'mycity', 'COL', 'mycity', -16);