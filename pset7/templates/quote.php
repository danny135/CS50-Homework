<?php  
    $name = $stock["name"];
    $symbol = $stock["symbol"];
    $price = $stock["price"];
?>

<p>
    A share of <?= $name ?> (<?= $symbol ?>) costs <strong>$<?= format_money($price) ?></strong>.
</p>
