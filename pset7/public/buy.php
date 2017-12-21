<?php

    // configuration
    require("../includes/config.php"); 

    // if form was submitted
    if ($_SERVER["REQUEST_METHOD"] == "POST")
    {
        if (preg_match("/^\d+$/", $_POST["shares"]) == false)
        {
            apologize("Invalid number of shares.");
        }
        
        $cash = query("SELECT cash FROM users WHERE id = ?", $_SESSION["id"])[0]["cash"];
        $stock =  lookup($_POST["symbol"]);
        $price = $stock["price"] * $_POST["shares"];
        
        if ($stock === false)
        {
            apologize("Stock not found.");
        }
        else if ($cash >= $price)
        {
            //Subtract the money needed to buy the shares
            $cashResult = query("UPDATE users SET cash = cash - ? WHERE id = ?", $price, $_SESSION["id"]);
            
            if ($cashResult === false)
            {
                apologize("Failed to update cash.");
            } 
           
            //Add the shares to the user's portfolio
            $portfolioResult = query("INSERT INTO stocks (id, symbol, shares) VALUES({$_SESSION["id"]}, '{$_POST["symbol"]}', {$_POST["shares"]}) ON DUPLICATE KEY UPDATE shares = shares + VALUES(shares)");
                    
            if ($portfolioResult === false)
            {
                //Attempt to give back the money
                query("UPDATE users SET cash = cash + ? WHERE id = ?", $price, $_SESSION["id"]);
            
                apologize("Failed to update portfolio.");
            } 
            
            //Add transaction to history
            query("INSERT INTO history (id, transaction, symbol, shares, price)
                   VALUES(?, 'BUY', ?, ?, ?);", $_SESSION["id"], $_POST["symbol"], $_POST["shares"], $price);
                   
            redirect("index.php");
        }
        else
        {
            apologize("You don't have enough cash!");
        }
    }
    else
    {
        render("buy_form.php", ["title" => "Buy"]);
    }
?>
