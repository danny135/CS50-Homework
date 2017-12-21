<?php

    // configuration
    require("../includes/config.php");

    $rows = query("SELECT * FROM stocks WHERE id = " . $_SESSION["id"]);
    $cash = query("SELECT cash FROM users WHERE id = " . $_SESSION["id"])[0]["cash"];

    if ($cash === false)
    {
        $cash = "Not Found";
    }

    if ($rows === false)
    {
        apologize("Failed to load portfolio.");
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

        // render portfolio
        render("portfolio.php", ["title" => "Portfolio", "stocks" => $stocks, "cash" => $cash]);
    }
?>
