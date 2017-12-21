<?php

    // configuration
    require("../includes/config.php"); 

    // if form was submitted
    if ($_SERVER["REQUEST_METHOD"] == "POST")
    {
       render("quote.php", ["stock" => lookup($_POST["symbol"])]);
    }
    else
    {
        // else render form
        render("quote_form.php", ["title" => "Quote"]);
    }

?>
