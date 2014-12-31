<?php
    require("../includes/config.php");
    
    $rows = query("SELECT type, timestamp, symbol, shares, price FROM history WHERE id = ? ", $_SESSION["id"]);
    render("history_table.php",["title" => "History", "rows" => $rows]);
    
?>

