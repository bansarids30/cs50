<table class = "table table-striped">
        <thead>
                <tr>
                    <th>Transaction</th>
                    <th>Date/Time</th>
                    <th>Symbols</th>
                    <th>Shares</th>
                    <th>Price</th>
                </tr>
            </thead>
<?php
foreach ( $rows as $row)
    {
            print("<tr>");
            print("<td>{$row["type"]}</td>");
            print("<td>{$row["timestamp"]}</td>");
            print("<td>{$row["symbol"]}</td>");
            print("<td>{$row["shares"]}</td>");
            print("<td>{$row["price"]}</td>");
            print("</tr>");
    }
    
?>
</table>    
