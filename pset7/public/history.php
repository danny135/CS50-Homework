<?php

    // configuration
    require("../includes/config.php"); 
    
    $transactions = query("SELECT transaction, time, symbol, shares, price FROM history WHERE id = {$_SESSION["id"]}");
    
    render("history.php", ["title" => "History", "transactions" => $transactions]);
?>
