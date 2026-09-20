select unique_id,name from Employees e left join EmployeeUNI p 
on e.id = p.id