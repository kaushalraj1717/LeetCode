# Write your MySQL query statement below
select x,y,z,
case when x+y <=z or x+z<=y or y+z<=x then 'No' else 'Yes' END as triangle from Triangle