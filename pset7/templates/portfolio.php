<div class="container">

<ul class="nav nav-pills">
    <li><a href="quote.php">Quote</a></li>
    <li><a href="buy.php">Buy</a></li>
    <li><a href="sell.php">Sell</a></li>
    <li><a href="history.php">History</a></li>
    <li><a href="change.php">Change Passsword</a></li>
    <li><a href="logout.php"><strong>Log Out</strong></a></li>
</ul>

        <table class = "table table-striped">
        <thead>
                <tr>
                    <th>Name</th>
                    <th>Symbol</th>
                    <th>Shares</th>
                    <th>Price</th>
                    <th>Total</th>
                </tr>
            </thead>
<?php
        $cashs = query("SELECT cash FROM users WHERE id = ?", $_SESSION["id"]);
        $cash = $cashs[0]["cash"];
        $cash = number_format($cash , 2);
        foreach ($positions as $position)
        {
            $value = $position["price"] * $position["shares"];
            $value =  number_format($value , 2);
            $position["price"] = number_format($position["price"] , 2);
            
            print("<tr>");
            print("<td>{$position["name"]}</td>");
            print("<td>{$position["symbol"]}</td>");
            print("<td>{$position["shares"]}</td>");
            print("<td>{$position["price"]}</td>");
            print("<td>{$value}</td>");
            print("</tr>");
        }
        print("<tr>"); ?>

        <td colspan="4" style="text-align:left"><b>Cash</b></td>
        <?php
        
        // print the final cash balalnce
        print("<td><b>$ {$cash}</b></td>");
        print("</tr>");
        
    ?>
</table>
</div>

<?php
//<div>
  //  <a href="logout.php">Log Out</a>
//</div>
?>

