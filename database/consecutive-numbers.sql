WITH cte AS (
    SELECT id, num,
           CASE 
              WHEN num = LAG(num) OVER(ORDER BY id) 
              THEN 0 
              ELSE 1 
           END AS new_group
    FROM Logs
),
grp AS (
    SELECT id, num,
           SUM(new_group) OVER(ORDER BY id) AS grp_id
    FROM cte
)
SELECT DISTINCT num AS ConsecutiveNums
FROM grp
GROUP BY num, grp_id
HAVING COUNT(*) >= 3;
