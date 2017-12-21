<?php

    // configuration
    require("../includes/config.php"); 

    // if form was submitted
    if ($_SERVER["REQUEST_METHOD"] == "POST")
    {
       $stock = lookup($_POST["symbol"]);
       $shares = query("SELECT shares FROM stocks WHERE id = {$_SESSION["id"]} AND symbol = '{$_POST["symbol"]}'")[0]["shares"];
       $cash = $stock["price"] * $shares;
       
       //Attempt to sell the stock and give the user the money
       if ($shares === false || query("UPDATE users SET cash = cash + {$cash} WHERE id = {$_SESSION["id"]}") === false)
       {
            apologize("Failed to sell stock.");
       }
       else
       {
            //Delete the stock from the user's portfolio
            query("DELETE FROM stocks WHERE id = {$_SESSION["id"]} AND symbol = '{$_POST["symbol"]}'");
            
            //Add the transaction to history
            query("INSERT INTO history (id, transaction, symbol, shares, price)
                   VALUES(?, 'SELL', ?, ?, ?)", $_SESSION["id"], $_POST["symbol"], $shares, $cash);
       }
       
       redirect("index.php");
    }
    else
    {
        $rows = query("SELECT * FROM stocks WHERE id = " . $_SESSION["id"]);
        $cash = query("SELECT cash FROM users WHERE id = " . $_SESSION["id"])[0]["cash"];

        if ($rows === false || $cash === false)
        {
            apologize("Failed to load stocks.");
        }
        else
        {
            $stocks = [];
            foreach ($rows as $row)
            {
                $stock = lookup($row["symbol"]);
                if ($stock !== false)
                {
                    $stocks[] = [
                        "name" => $stock["name"],
                        "price" => $stock["price"],
                        "shares" => $row["shares"],
                        "symbol" => $row["symbol"]
                    ];
                }
            }

            render("sell_form.php", ["title" => "Sell", "stocks" => $stocks, "cash" => $cash]);
        }
    }
?>
