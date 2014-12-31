<?php

    // configuration
    require("../includes/config.php");

    // if form was submitted
    if ($_SERVER["REQUEST_METHOD"] == "POST")
    {
        if (empty($_POST["password"]))
        {
            apologize("You must provide your password.");
        }
        else if (empty($_POST["confirmation"]))
        {
            apologize("You must provide your password confirmation.");
        }
        else if (($_POST["password"]) != ($_POST["confirmation"]))
        {
            apologize("Passwords donot match.");
        }
        //insert into tables
        $result = query("Update users SET hash = ? WHERE id = ?", crypt($_POST["password"]) , $_SESSION["id"]);
        if($result === false)
        {
            apologize("Write unique username");
        }
        redirect("/");
        
    }
    else
    {
        // else render form
        render("newpassword_form.php", ["title" => "Change Password"]);
    }

?>
