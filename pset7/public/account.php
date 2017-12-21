<?php

    // configuration
    require("../includes/config.php");

    // if form was submitted
    if ($_SERVER["REQUEST_METHOD"] == "POST")
    {
        if (empty($_POST["password"]))
        {
            apologize("Password cannot be empty.");
        }
        else if ($_POST["password"] != $_POST["confirmation"])
        {
            apologize("Passwords do not match.");
        }
        else
        {
            $result = query("UPDATE users SET hash = ? WHERE id = ?", crypt($_POST["password"]), $_SESSION["id"]);
            
            if ($result === false)
            {
                apologize("Failed to update password.");
            }
            else
            {
                redirect("index.php");
            }
        }
    }
    else
    {
        // else render form
        render("password_form.php", ["title" => "Account"]);
    }

?>
