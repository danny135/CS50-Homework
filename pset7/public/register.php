<?php

    // configuration
    require("../includes/config.php");

    // if form was submitted
    if ($_SERVER["REQUEST_METHOD"] == "POST")
    {
        if (empty($_POST["username"]) || empty($_POST["password"]))
        {
            apologize("Username and password cannot be empty.");
        }
        else if ($_POST["password"] != $_POST["confirmation"])
        {
            apologize("Passwords do not match.");
        }
        else
        {
            $result = query("INSERT INTO users (username, hash, cash) VALUES(?, ?, 10000.00)", $_POST["username"], crypt($_POST["password"]));
            if ($result === false)
            {
                apologize("Registration failed.");
            }
            else
            {
                $rows = query("SELECT LAST_INSERT_ID() AS id");
                
                if ($rows === false)
                {
                    redirect("login.php");
                }
                else
                {
                    $_SESSION["id"] = $rows[0]["id"];
                    
                    redirect("index.php");
                }
            }
        }
    }
    else
    {
        // else render form
        render("register_form.php", ["title" => "Register"]);
    }

?>
