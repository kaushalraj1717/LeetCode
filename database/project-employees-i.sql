# Write your MySQL query statement below
select p.project_id, ifnull(round(sum(e.experience_years)/count(p.employee_id),2),0) as average_years from Project p left join
Employee e on p.employee_id =e.employee_id
group by project_id
